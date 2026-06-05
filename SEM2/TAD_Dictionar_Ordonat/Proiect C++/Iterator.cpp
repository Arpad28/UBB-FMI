#include "Iterator.h"

#include <exception>

#include "DO.h"

using namespace std;

void Iterator::sorteaza() {
	for (int i = 0; i < capacitate - 1; i++) {
		for (int j = i + 1; j < capacitate; j++) {
			if (!dict.rel(elemente[i].first, elemente[j].first)) {
				TElem aux = elemente[i];
				elemente[i] = elemente[j];
				elemente[j] = aux;
			}
		}
	}
}

Iterator::Iterator(const DO& d) : dict(d){
	// BC = WC = AC = General = Theta(nrelem) amortizat
	this->capacitate=dict.dim();
	this->elemente =new TElem[this->capacitate];
	int index = 0;

	for (int i = 0; i <this->dict.m; i++) {
		Nod* p=dict.l[i];
		while (p!=nullptr) {
			this->elemente[index++]=p->elem;
			p=p->urm;
		}
	}
	if (this->capacitate>0) {
		this->sorteaza();
	}
	this->curent=0;
}

void Iterator::prim(){
	// BC = WC = AC = General = Theta(1)
	this->curent=0;
}

void Iterator::urmator(){
	// BC = WC = AC = General = Theta(1)
	if (!this->valid()) {
		throw exception();
	}
	this->curent++;
}

bool Iterator::valid() const{
	// BC = WC = AC = General = Theta(1)
	return this->curent<this->capacitate;
}

TElem Iterator::element() const{
	// BC = WC = AC = General = Theta(1)
	if (!this->valid()) {
		throw exception();
	}
	return this->elemente[this->curent];
}
Iterator::~Iterator() {
	// BC = WC = AC = General = Theta(1)
	delete [] elemente;
}


