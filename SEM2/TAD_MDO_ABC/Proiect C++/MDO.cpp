#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) {
	// BC = WC = AC = General =Theta(1)
	this->rel=r;
	this->radacina=nullptr;
	this->dimensiune=0;
}


void MDO::adauga(TCheie c, TValoare v) {
	// BC = Theta(1)
	// WC = Theta(High)
	// AC = Theta(High)
	// General = O(High)
	/* de adaugat */
	Nod* nou =new Nod;
	nou->elem.first=c;
	nou->elem.second=v;
	nou->stanga=nullptr;
	nou->dreapta=nullptr;
	if (radacina==nullptr) {
		radacina=nou;
		this->dimensiune++;
		return;
	}
	Nod* curent=radacina;
	Nod* parinte=nullptr;
	while (curent!=nullptr) {
		parinte=curent;
		if (rel(c,curent->elem.first)) {
			curent=curent->stanga;
		}
		else {
			curent=curent->dreapta;
		}
	}
	if (rel(c,parinte->elem.first)) {
		parinte->stanga=nou;
	}
	else {
		parinte->dreapta = nou;
	}
	dimensiune++;
}

vector<TValoare> MDO::cauta(TCheie c) const {
	// BC = Theta(1)
	// WC = Theta(High)
	// AC = Theta(High)
	// General = O(High)
	/* de adaugat */
	vector<TValoare>rez;
	Nod* curent=radacina;
	while (curent!=nullptr) {
		if (curent->elem.first==c) {
			rez.push_back(curent->elem.second);
		}
		if (rel(c,curent->elem.first)) {
			curent=curent->stanga;
		}
		else {
			curent=curent->dreapta;
		}
	}
	return rez;
}

Nod* MDO::minim(Nod* curent) {
	// BC = WC = AC = General =O(high)
	while (curent->stanga!=nullptr) {
		curent=curent->stanga;
	}
	return curent;
}

Nod *MDO::stergeRecursiv(Nod *curent, TCheie c, TValoare v, bool &sters) {
	// BC = Theta(1)
	// WC = Theta(High)
	// AC = Theta(High)
	// General = O(High)
	if (curent==nullptr) {
		return nullptr;
	}
	if (curent->elem.first==c && curent->elem.second==v && !sters) {
		sters=true;
		if (curent->stanga==nullptr) {
			Nod* temp=curent->dreapta;
			delete curent;
			return temp;
		}
		else if (curent->dreapta==nullptr) {
			Nod* temp=curent->stanga;
			delete curent;
			return temp;
		}
		else {
			Nod* temp=minim(curent->dreapta);
			curent->elem=temp->elem;
			bool ok=false;
			curent->dreapta = stergeRecursiv(curent->dreapta, temp->elem.first, temp->elem.second, ok);
			return curent;
		}
	}
	if (rel(c, curent->elem.first)) {
		curent->stanga = stergeRecursiv(curent->stanga, c, v, sters);
	} else {
		curent->dreapta = stergeRecursiv(curent->dreapta, c, v, sters);
	}

	return curent;
}

bool MDO::sterge(TCheie c, TValoare v) {
	// BC = Theta(1)
	// WC = Theta(High)
	// AC = Theta(High)
	// General = O(High)
	bool sters=false;
	radacina=stergeRecursiv(radacina, c, v, sters);
	if (sters) {
		dimensiune--;
	}
	return sters;
}

int MDO::dim() const {
	// BC = WC = AC = General =Theta(1)
	/* de adaugat */
	return dimensiune;
}

bool MDO::vid() const {
	// BC = WC = AC = General =Theta(1)
	/* de adaugat */
	return dimensiune==0;
}

IteratorMDO MDO::iterator() const {
	// BC = WC = AC = General =O(high)
	return IteratorMDO(*this);
}

void MDO::distruge(Nod* curent) {
	// BC = WC = AC = General =Theta(dimensiune)
	if (curent != nullptr) {
		distruge(curent->stanga);
		distruge(curent->dreapta);
		delete curent;
	}
}

MDO::~MDO() {
	// BC = WC = AC = General =Theta(dimensiune)
	distruge(radacina);
}