#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <optional>
#include <vector>

template <typename K, typename V>
class Factory {
    
public:

    V& operator[](const K key) {
        size_t index = indices_[key];
        return items_[index];
    }
    
    template <typename... Args>
    V& Add(K key, Args... args) {
        items_.emplace_back(args...);
        size_t index = items_.size() - 1;
        indices_[key] = index;
        inverse_[index] = key;
        return items_.back();
    }
    
    std::optional<std::reference_wrapper<V>> At(K key) {
        try {
            size_t index = indices_.at(key);
            return std::optional<std::reference_wrapper<V>>(items_.at(index));
        } catch (std::out_of_range exception) {
            return std::nullopt;
        }
    }
    
    void Remove(K key) {
        std::optional<std::reference_wrapper<V>> value = At(key);
        if (value) {
            size_t removeIndex = indices_[key];
            size_t swapIndex = items_.size() - 1;
            K swapKey = inverse_[swapIndex];
            std::swap(value->get(), items_[swapIndex]);
            items_.pop_back();
            indices_[swapKey] = removeIndex;
            inverse_[removeIndex] = swapKey;
            indices_.erase(key);
            inverse_.erase(items_.size());
        }
    }
    
private:

    std::vector<V> items_;
    std::map<K, size_t> indices_;
    std::map<size_t, K> inverse_;
    
};

#endif