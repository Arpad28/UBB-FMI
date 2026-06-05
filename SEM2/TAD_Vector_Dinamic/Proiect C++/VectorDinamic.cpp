#include "VectorDinamic.h"
#include "IteratorVectorDinamic.h"
#include <exception>
#include <iostream>

using namespace std;

void VectorDinamic::redim(int capacitate) {
	// BC = WC = AC = General = Theta(n)
	TElem *nou=new TElem[capacitate];
	for (int i=0; i<min(this->lungime,this->capacitate);i++)
		nou[i]=this->elems[i];
	delete[] this->elems;
	this->capacitate=capacitate;
	this->elems = nou;
}


VectorDinamic::VectorDinamic(int cp) {
	// BC = WC = AC = General = Theta(1)
	if (cp<=0)
		throw std::exception();//return -1;
	this->capacitate=cp;
	this->elems = new TElem[cp];
	this->lungime=0;
}



VectorDinamic::~VectorDinamic() {
	// BC = WC = AC = General = Theta(1)
	delete[] this->elems;
	this->elems = nullptr;
}



int VectorDinamic::dim() const{
	// BC = WC = AC = General = Theta(1)
	return this->lungime;
}



TElem VectorDinamic::element(int i) const{
	// BC = WC = AC = General = Theta(1)
	if (i>=0 && i<this->lungime)
		return this->elems[i];
	throw std::exception();
	//return -1;
}



void VectorDinamic::adaugaSfarsit(TElem e) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(1)
	// General = Theta(1) amortizat
	if (this->lungime>=0.8*this->capacitate)
		this->redim(this->capacitate*2);
	this->elems[this->lungime++]=e;
}


void VectorDinamic::adauga(int i, TElem e) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n-i)
	// General = O(n)
	if (i>=0 && i<=this->lungime) {
		if (this->lungime>=0.8*this->capacitate)
			this->redim(this->capacitate*2);
		for (int j=this->lungime;j>i;j--)
			this->elems[j]=this->elems[j-1];
		this->elems[i]=e;
		this->lungime++;
	}
	else
		throw std::exception();	//return -1;
}


TElem VectorDinamic::modifica(int i, TElem e) {
	// BC = WC = AC = General = Theta(1)
	if (i>=0 && i<this->lungime) {
		TElem vechi=this->elems[i];
		this->elems[i]=e;
		return vechi;
	}
	throw std::exception();//return -1;
}


TElem VectorDinamic::sterge(int i) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n)
	if (i>=0 && i<=this->lungime) {
		TElem sters=this->elems[i];
		for (int j=i;j<this->lungime-1;++j)
			this->elems[j]=this->elems[j+1];
		this->lungime--;
		if (this->capacitate>1 && this->lungime<0.8*this->capacitate/2)
			this->redim(this->capacitate/2);
		return sters;
	}
	throw std::exception();//return -1;
}

IteratorVectorDinamic VectorDinamic::iterator() {
	// BC = WC = AC = General = Theta(1)
	return IteratorVectorDinamic(*this);
}



