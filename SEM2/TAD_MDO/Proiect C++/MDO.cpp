#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

int MDO::aloca() {
	// BC = WC = AC = General = Theta(1)
	int i=this->primLiber;
	this->primLiber=this->urmator[primLiber];
	return i;
}

void MDO::dealoca(int i) {
	// BC = WC = AC = General = Theta(1)
	this->urmator[i]=this->primLiber;
	this->primLiber=i;
}

void MDO::redimensionare() {
	// BC = WC = AC = General = Theta(n)
	int capacitateNoua=this->capacitate*2;
	TElem* elementeNou=new TElem[capacitateNoua];
	int* urmatorNou=new int[capacitateNoua];

	for (int i=0;i<this->capacitate;++i) {
		elementeNou[i]=this->elemente[i];
		urmatorNou[i]=this->urmator[i];
	}
	for (int i=this->capacitate;i<capacitateNoua-1;++i) {
		urmatorNou[i]=i+1;
	}
	urmatorNou[capacitateNoua-1]=-1;
	this->primLiber=this->capacitate;
	this->capacitate=capacitateNoua;
	delete [] this->elemente;
	delete [] this->urmator;
	this->elemente=elementeNou;
	this->urmator=urmatorNou;
}

MDO::MDO(Relatie r) {
	// BC = WC = AC = General = Theta(n)
	this->rel=r;
	this->capacitate=10;
	this->dimensiune=0;

	this->elemente=new TElem[this->capacitate];
	this->urmator=new int[this->capacitate];

	this->prim=-1;
	for (int i=0;i<this->capacitate-1;++i) {
		this->urmator[i]=i+1;
	}
	this->urmator[this->capacitate-1]=-1;
	this->primLiber=0;
}


void MDO::adauga(TCheie c, TValoare v) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n)
	if (this->primLiber==-1) {
		this->redimensionare();
	}
	int nou=this->aloca();
	this->elemente[nou]={c,v};
	int curent=this->prim;
	int prec=-1;
	while (curent!=-1 && this->rel(this->elemente[curent].first,c)) {
		prec=curent;
		curent=this->urmator[curent];
	}
	if (prec==-1) {
		this->urmator[nou]=this->prim;
		this->prim=nou;
	}
	else {
		this->urmator[nou]=curent;
		this->urmator[prec]=nou;
	}
	this->dimensiune++;
}

vector<TValoare> MDO::cauta(TCheie c) const {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n)
	vector<TValoare> valori;
	int curent=this->prim;
	while (curent!=-1 && this->rel(this->elemente[curent].first,c)) {
		if (this->elemente[curent].first==c) {
			valori.push_back(this->elemente[curent].second);
		}
		curent=this->urmator[curent];
	}
	return valori;
}

bool MDO::sterge(TCheie c, TValoare v) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n)
	int curent=this->prim;
	int prec=-1;
	while (curent!=-1 && this->rel(this->elemente[curent].first,c)) {
		if (this->elemente[curent].first==c && this->elemente[curent].second==v) {
			if (prec==-1) {
				this->prim=this->urmator[curent];
			}
			else {
				this->urmator[prec]=this->urmator[curent];
			}
			dealoca(curent);
			this->dimensiune--;
			return true;
		}
		prec=curent;
		curent=this->urmator[curent];
	}
	return false;
}

int MDO::dim() const {
	// BC = WC = AC = General = Theta(1)
	return this->dimensiune;
}

bool MDO::vid() const {
	// BC = WC = AC = General = Theta(1)
	return this->dimensiune==0;
}

IteratorMDO MDO::iterator() const {
	// BC = WC = AC = General = Theta(1)
	return IteratorMDO(*this);
}

MDO::~MDO() {
	// BC = WC = AC = General = Theta(1)
	delete [] this->elemente;
	delete [] this->urmator;
}
