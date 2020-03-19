#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;
/*
	Die Komplexitaten hier sind alle O(1)
*/
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	//initialisiert den Index des Iterators mit 0
	this->i = 0;
}

TComp SortedBagIterator::getCurrent() {
	//Wenn valid, die Funktion liefert das Element auf der gegebenen Position
	//sonst NULL
	if (valid() == false) {
		exception f;
		throw f;
		return NULL_TCOMP;
	}
	else
		return this->bag.S_bag[this->i].first;
}

bool SortedBagIterator::valid() {
	//uberpruft ob der index grosser als 0 ist und ob er kleiner als die Lenge des Bags ist
	if (this->i < this->bag.len && this->i >= 0) {
		return true;
	}
	return false;
}

void SortedBagIterator::next() {
	//Falls S_bag existiert und die Position valid() ist, dann zeigt der Iterator auf die nechste Position
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
	//tut den Index wieder auf die erste Position
	this->i = 0;
}

