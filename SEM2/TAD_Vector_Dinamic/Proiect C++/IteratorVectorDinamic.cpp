#include "IteratorVectorDinamic.h"
#include "VectorDinamic.h"
#include <exception>


IteratorVectorDinamic::IteratorVectorDinamic(const VectorDinamic& _v) :

		v(_v) {
	// BC = WC = AC = General = Theta(1)
	this->prim();
}



void IteratorVectorDinamic::prim() {
	// BC = WC = AC = General = Theta(1)
	this->poz=0;
}



bool IteratorVectorDinamic::valid() const{
	// BC = WC = AC = General = Theta(1)
	if (this->poz<this->v.dim())
		return true;
	return false;
}



TElem IteratorVectorDinamic::element() const{
	// BC = WC = AC = General = Theta(1)
	if (this->valid())
		return this->v.element(this->poz);
	throw std::exception();
}



void IteratorVectorDinamic::urmator() {
	// BC = WC = AC = General = Theta(1)
	if (!this->valid())
		throw std::exception();//return -1;
	this->poz++;
}

