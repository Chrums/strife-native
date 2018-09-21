#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <optional>
#include <set>

namespace Strife {
    
    template <typename T>
    class Hierarchy {
        
    public:
        
        void setParent(const T parent) {
            parent_ = std::optional(parent);
        }
        
        const std::optional<T> getParent() const {
            return parent_;
        }
        
        void addChild(const T child) {
            children_.insert(child);
        }
        
        void removeChild(const T child) {
            children_.erase(child);
        }
        
        const std::set<T> getChildren() const {
            return children_;
        }
        
    private:
        
        std::optional<T> parent_;
        std::set<T> children_;
        
    };
    
}

#endif