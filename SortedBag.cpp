#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <utility>
using std::pair;

SortedBag::SortedBag(Relation r) {
	//Erstellen leeres S_bag-----O(1)

	this->my_relation = r;
	this->S_bag = new pair<TComp, int>[this->cap];
	this->len = 0;
}

void SortedBag::add(TComp e) {
	/*
	Besten Fall : len==0;-----O(1)
	Durchschnittlichen Fall: wenn man nur die Frequenz verendert werden muss-----O(len)
	Schlechsten Fall: Geeignete Position finden und Werte verschieben-----O(len^2)
	*/

	//Capazitat verdoppeln, wenn S_bag voll.
	if (this->len >= this->cap) {
		this->cap = this->cap * 2;
		pair<TComp, int>* S_bag2= new pair<TComp, int>[this->cap];
		for (int j = 0; j < this->len; j++) {
			S_bag2[j] = S_bag[j];
		}
		this->S_bag= new pair<TComp, int>[this->cap];
		for (int j = 0; j < this->len; j++) {
			S_bag[j] = S_bag2[j];
		}
	}
	//Wenn S_bag leer ist, dann wird das Pair auf die erste Position getan
	if (this->len == 0) {
		S_bag[0].first = e;
		S_bag[0].second = 1;
		this->len++;
		return;
	}
	//Bestimmen der Richtung
	bool relation = this->my_relation(1, 2);
	//relation = true => steigend
	//relation = false => fallend

	//Element suchen Frequenz verendern
	for (int i = 0; i < this->len; i++) {
		if (e == S_bag[i].first) {
			S_bag[i].second++;
			return;
		}
	}
	//Wenn steigend sortiert werden muss
	if (relation == true) {
		for (int i = 0; i < this->len; i++) {
			if (e < S_bag[i].first) {
				this->len++;
				for (int j = this->len - 1; j > i; j--) {
					this->S_bag[j] = this->S_bag[j - 1];
				}
				this->S_bag[i].first = e;
				this->S_bag[i].second = 1;
				return;
			}
		}
	}

	//Wenn fallend sortiert werden muss
	if (relation == false) {
		for (int i = 0; i < this->len; i++) {
			if (e > S_bag[i].first) {
				this->len++;
				for (int j = this->len - 1; j > i; j--) {
					this->S_bag[j] = this->S_bag[j - 1];
				}
				this->S_bag[i].first = e;
				this->S_bag[i].second = 1;
				return;
			}
		}
	}
	/*Wenn es hier ankommt is es das grosste/kleinste Element
	und wird am Ende eingefugt*/
	this->S_bag[this->len].first = e;
	this->S_bag[this->len].second = 1;
	this->len++;
}


bool SortedBag::remove(TComp e) {
	/*
	Besten Fall: Gesuchte Element ist auf die erste Position => O(1)
	Durschnittlichen und Schlimmsten Fall => O(len^2)
	*/

	//Algorithm fur Reduzieren der Kapazitat
	if (this->len == this->cap/4) {
		this->cap = this->cap / 2;
		pair<TComp, int>* S_bag2 = new pair<TComp, int>[this->cap];
		for (int j = 0; j < this->len; j++) {
			S_bag2[j] = S_bag[j];
		}
		this->S_bag = new pair<TComp, int>[this->cap];
		for (int j = 0; j < this->len; j++) {
			S_bag[j] = S_bag2[j];
		}
	}
	//eigentliche lossen
	for (int i = 0; i < this->len; i++) {
		if (S_bag[i].first == e) {
			this->len--;
			for (int j = i; j < this->len; j++) {
				S_bag[j] = S_bag[j + 1];
			}
			S_bag[this->len].first = 0;
			S_bag[this->len].second = 0;

			return true;
		}
	}
	return false;
}


bool SortedBag::search(TComp elem) const {/*
	Suchen mit Binary Search
	Besten Fall: S_bag leer oder das gesuchte Element steht in der Mitte-----O(1)
	Durchschnittliche Fall und Schlimmste Fall-----O(log len)
	*/
	if (this->len == 0)
		return false;
	if (this->len == 1 && this->S_bag[0].first == elem) {
		return true;
	}

	//Bestimmen der Richtung
	bool relation = this->my_relation(1, 2);
	//relation = true => steigend
	//relation = false => fallendbool relation = this->my_relation(1, 2);

	int left = 0;
	int right = this->len;
	//Wenn steigend sortiert ist
	if (relation == true) {
		while (left <= right) {
			int m = (left + right) / 2;

			if (this->S_bag[m].first == elem) {
				return true;
			}
			if (this->S_bag[m].first < elem) {
				left = m + 1;
			}
			else
				right = m - 1;
		}
	}//Wenn fallend sortiert ist
	if (relation == false) {
		while (left <= right) {
			int m = (left + right) / 2;

			if (this->S_bag[m].first == elem) {
				return true;
			}
			if (this->S_bag[m].first < elem) {
				right = m - 1;
			}
			else
				left = m + 1;
		}
	}
	
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {/*
	Suchen mit Binary Search
	Besten Fall: S_bag leer oder das gesuchte Element steht in der Mitte-----O(1)
	Durchschnittliche Fall und Schlimmste Fall-----O(log len)
	*/
	if (this->len == 1 && this->S_bag[0].first == elem) {
		return S_bag[0].second;
	}
	//Bestimmen der Richtung
	bool relation = this->my_relation(1, 2);
	//relation = true => steigend
	//relation = false => fallendbool relation = this->my_relation(1, 2);

	int left = 0;
	int right = this->len;
	//Wenn steigend sortiert ist
	if (relation == true) {
		
		while (left <= right) {
			int m = (left + right) / 2;

			if (this->S_bag[m].first == elem) {
				return S_bag[m].second;//return nrOccurrences
			}
			if (this->S_bag[m].first < elem) {
				left = m + 1;
			}
			else
				right = m - 1;
		}
	}
	//Wenn fallend sortiert ist
	if (relation == false) {
		while (left <= right) {
			int m = (left + right) / 2;

			if (this->S_bag[m].first == elem) {
				return S_bag[m].second;//return nrOccurrences
			}
			if (this->S_bag[m].first < elem) {
				right = m - 1;
			}
			else
				left = m + 1;
		}
	}
	return 0;
}



int SortedBag::size() const {
	//0(1)
	return this->len;
}


bool SortedBag::isEmpty() const {
	//0(1)
	if (this->len == 0)
		return true;
	return false;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	delete[]S_bag;
}
