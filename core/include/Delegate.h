// Copied from https://stackoverflow.com/questions/23973914/c-like-delegates-in-c

#ifndef DELEGATE_H
#define DELEGATE_H

template <typename Class, typename Function, typename... Args>
class Handle {
    
public:

    Handle(Class* object, Function (Class::*member)(Args...)) : 
        object_(object),
        member_(member) {};
    
    Function operator()(Args... args) {
        return (this->object_->*this->member_)(args...);
    }
    
    bool operator==(Handle const& other) const {
        return this->object_ == other.object_ && this->member_ == other.member_;
    }
    
    bool operator!=(Handle const& other) const {
        return !(*this == other);
    }
    
private:
    
    Class* object_;
    Function (Class::*member_)(Args...);
    
};

template <typename Class, typename Function, typename... Parameters>
Handle<Class, Function, Parameters...> Bind(Function (Class::*member)(Parameters...), Class& object) {
    return Handle<Class, Function, Parameters...>(&object, member);
}

template <typename T>
struct Delegate;

template <typename... Args>
class Delegate<void(Args...)> {
    
public:

    Delegate(void) {};
    
    template <typename T>
    Delegate& operator+= (T&& callback) {
        this->callbacks_.emplace_back(new Caller<T>(std::forward<T>(callback)));
        return *this;
    }
    
    template <typename T>
    Delegate& operator-= (T&& callback) {
        Caller<T> tmp(std::forward<T>(callback));
        auto it = std::remove_if(
            this->callbacks_.begin(),
            this->callbacks_.end(),
            [&](std::unique_ptr<IBase>& other) {
                return tmp.Compare(other.get());
            }
        );
        this->callbacks_.erase(it, this->callbacks_.end());
        return *this;
    }

    void operator()(Args... args) {
        for (auto& callback: this->callbacks_) {
            callback->Call(args...);
        }
    }
    
private:

    struct IBase {
        virtual ~IBase() {};
        virtual bool Compare(IBase* other) = 0;
        virtual void Call(Args... args) = 0;
    };
    
    template <typename T>
    struct Caller : IBase {
        
        T callback_;
        
        template <typename S>
        Caller(S&& callback): callback_(std::forward<S>(callback)) {};

        bool Compare(IBase* other) {
            Caller<T>* tmp = dynamic_cast<Caller<T>*>(other);
            return tmp && this->callback_ == tmp->callback_;
        }
        
        void Call(Args... args) {
            return this->callback_(args...);
        }
        
    };
    
    std::vector<std::unique_ptr<IBase>> callbacks_;

    Delegate(Delegate const&) = delete;
    void operator=(Delegate const&) = delete;
    
};

#endif