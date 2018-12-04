#include "IStorage.h"

using namespace Strife::Core;

IStorage::Iterator::Iterator(IIterator<Type>* const iterator)
    : iterator_(iterator) {}
    
IStorage::Iterator::~Iterator() {
    delete iterator_;
}

IStorage::Iterator& IStorage::Iterator::operator++() {
    ++(*iterator_);
    return *this;
}

IStorage::Iterator& IStorage::Iterator::operator++(int) {
    ++(*iterator_);
    return *this;
}

Type IStorage::Iterator::operator*() const {
    return *(*iterator_);
}

bool IStorage::Iterator::operator==(const IStorage::Iterator& iterator) const {
    return *iterator_ == *iterator.iterator_;
}

bool IStorage::Iterator::operator!=(const IStorage::Iterator& iterator) const {
    return !(*iterator_ == *iterator.iterator_);
}

IStorage::IStorage(Scene& scene)
    : scene_(scene) {}