#include "IStorage.h"
#include "Scene.h"
#include <boost/uuid/uuid.hpp>

using namespace Strife::Core;
using namespace boost::uuids;

IStorage::Iterator::Iterator(IIterator<std::pair<const Entity, Component* const>>* const iterator)
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

std::pair<const Entity, Component* const> IStorage::Iterator::operator*() {
	return *(*iterator_);
}

bool IStorage::Iterator::operator==(const IStorage::Iterator& iterator) const {
	return (*iterator_) == iterator.iterator_;
}

bool IStorage::Iterator::operator!=(const IStorage::Iterator& iterator) const {
	return !((*iterator_) == iterator.iterator_);
}

IStorage::IStorage(Scene& scene)
    : scene_(scene) {}

Entity IStorage::addEntity(uuid id, EntityMap& entityMap) {
    return scene_.entities.add(id, entityMap);
}
