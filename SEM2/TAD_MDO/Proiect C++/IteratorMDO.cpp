#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
	// BC = WC = AC = General = Theta(1)
	curent=dict.prim;
}

void IteratorMDO::prim(){
	// BC = WC = AC = General = Theta(1)
	curent=dict.prim;
}

void IteratorMDO::urmator(){
	// BC = WC = AC = General = Theta(1)
	if (!valid())
		throw std::exception();
	curent=dict.urmator[curent];
}

bool IteratorMDO::valid() const{
	// BC = WC = AC = General = Theta(1)
	return curent!=-1;
}

TElem IteratorMDO::element() const{
	// BC = WC = AC = General = Theta(1)
	if (!valid())
		throw std::exception();
	return dict.elemente[curent];
}


