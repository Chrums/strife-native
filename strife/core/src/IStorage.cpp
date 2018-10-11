#include "IStorage.h"

using namespace Strife::Core;

IStorage::Iterator::Iterator(IIterator<std::pair<const Entity, Component* const>>* const iterator) :
    iterator_(iterator) {}

IStorage::Iterator::~Iterator() {
    delete iterator_;
}

IStorage::Iterator &IStorage::Iterator::operator++() {
    ++(*iterator_);
    return *this;
}

IStorage::Iterator &IStorage::Iterator::operator++(int) {
    ++(*iterator_);
    return *this;
}

std::pair<const Entity, Component* const> IStorage::Iterator::operator*() {
    return *(*iterator_);
}

bool IStorage::Iterator::operator==(const IStorage::Iterator &iterator) const {
    return (*iterator_) == iterator.iterator_;
}

bool IStorage::Iterator::operator!=(const IStorage::Iterator &iterator) const {
    return !((*iterator_) == iterator.iterator_);
}

IStorage::IStorage(Scene& scene) :
    scene_(scene) {}