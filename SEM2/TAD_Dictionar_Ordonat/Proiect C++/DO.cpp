#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

int DO::d_hash(TCheie c) const {
	// BC = WC = AC = General = Theta(1)
	return abs(c)%this->m;
}
void DO::redimensioneaza() {
	// BC = WC = AC = General = Theta(m)
	int mVechi = this->m;
	this->m = this->m * 2;
	Nod** lNou = new Nod*[this->m];
	for (int i = 0; i < this->m; i++) {
		lNou[i] = nullptr;
	}
	for (int i = 0; i < mVechi; i++) {
		Nod* p = this->l[i];
		while (p != nullptr) {
			Nod* urmator = p->urm;
			int posNoua = this->d_hash(p->elem.first);
			p->urm = lNou[posNoua];
			lNou[posNoua] = p;
			p = urmator;
		}
	}
	delete[] this->l;
	this->l = lNou;
}
DO::DO(Relatie r) {
	// BC = WC = AC = General = Theta(m)
	this->m=10;
	this->l=new Nod*[this->m];
	for (int i=0;i<this->m;i++) {
		this->l[i]=nullptr;
	}
	this->nrelem=0;
	this->rel=r;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n),n-nr de elemente pe pos din d_hash() amortizat
	int pos=this->d_hash(c);
	Nod *p=this->l[pos];
	while(p!=nullptr) {
		if (p->elem.first==c) {
			TValoare val=p->elem.second;
			p->elem.second=v;
			return val;
		}
		p=p->urm;
	}
	Nod* nou=new Nod;
	nou->elem.first=c;
	nou->elem.second=v;
	nou->urm=this->l[pos];
	this->l[pos]=nou;
	this->nrelem++;
	if (3*this->nrelem >= this->m) {
		this->redimensioneaza();
	}
	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n),n-nr de elemente pe pos din d_hash()
	int pos=this->d_hash(c);
	Nod *p=this->l[pos];
	while(p!=nullptr) {
		if (p->elem.first==c) {
			return p->elem.second;
		}
		p=p->urm;
	}
	return NULL_TVALOARE;	
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n),n-nr de elemente pe pos din d_hash()
	int pos=this->d_hash(c);
	Nod *p=this->l[pos];
	Nod* ant=nullptr;
	while(p!=nullptr) {
		if (p->elem.first==c) {
			TValoare destersval=p->elem.second;
			if (ant==nullptr) {
				this->l[pos]=p->urm;
			}
			else {
				ant->urm=p->urm;
			}
			delete p;
			this->nrelem--;
			return destersval;
		}
		ant=p;
		p=p->urm;
	}
	return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	// BC = WC = AC = General = Theta(1)
	return this->nrelem;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
	// BC = WC = AC = General = Theta(1)
	return this->nrelem==0;
}

Iterator DO::iterator() const {
	// BC = WC = AC = General = Theta(1)
	return  Iterator(*this);
}

DO::~DO() {
	// BC = WC = AC = General = Theta(nrelem)
	for (int i=0;i<this->m;i++) {
		Nod *p=this->l[i];
		while(p!=nullptr) {
			Nod* desters=p;
			p=p->urm;
			delete desters;
		}
	}
	delete [] this->l;
}
