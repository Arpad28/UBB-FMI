#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
	// BC = WC = AC = General = O(high)
	prim();
}

void IteratorMDO::prim(){
	// BC = WC = AC = General = O(high)
	while (!stiva.empty()) {
		stiva.pop();
	}
	Nod *p=dict.radacina;
	while (p!=nullptr) {
		stiva.push(p);
		p=p->stanga;
	}
	if (!stiva.empty()) {
		curent=stiva.top();
	}
	else {
		curent=nullptr;
	}
}

void IteratorMDO::urmator(){
	// BC = WC = AC = General = O(high)
	if (!valid())
		throw exception();
	Nod *p=stiva.top();
	stiva.pop();
	if (p->dreapta!=nullptr) {
		p=p->dreapta;
		while (p!=nullptr) {
			stiva.push(p);
			p=p->stanga;
		}
	}
	if (!stiva.empty()) {
		curent=stiva.top();
	}
	else {
		curent=nullptr;
	}
}

bool IteratorMDO::valid() const{
	// BC = WC = AC = General =Theta(1)
	return curent!=nullptr;
}

TElem IteratorMDO::element() const{
	// BC = WC = AC = General =Theta(1)
	if (!valid())
		throw exception();
	return curent->elem;
}


