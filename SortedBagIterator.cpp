#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	//TODO - Implementation
	this->i = 0;
}

TComp SortedBagIterator::getCurrent() {
	if (valid() == false) {
		exception f;
		throw f;
		return NULL_TCOMP;
	}
	else
		return this->bag.S_bag[this->i].first;
}

bool SortedBagIterator::valid() {
	//TODO - Implementation
	if (this->i < this->bag.len && this->i >= 0) {
		return true;
	}
	return false;
}

void SortedBagIterator::next() {
	//TODO - Implementation
	if (this->bag.len == 0) {
		exception f;
		throw f;
		return;
	}
	if (valid())
		this->i++;
	else
	{
		exception f;
		throw f;
		return;
	}
}

void SortedBagIterator::first() {
	//TODO - Implementation
	this->i = 0;
}

