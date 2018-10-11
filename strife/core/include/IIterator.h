#ifndef IITERATOR_H
#define IITERATOR_H

template <typename T>
class IIterator {

public:
	IIterator() = default;
	virtual ~IIterator() = default;

	virtual void operator++() = 0;
	virtual T operator*() = 0;
	virtual bool operator==(const IIterator* iterator) const = 0;
};

#endif