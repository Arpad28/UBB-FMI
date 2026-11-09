%conc(lista1,lista2,rez)(i,i,o)

conc([],L,L).
conc([H|T],L,[H|Rez]):-
    conc(T,L,Rez).
    
%substituie(lista,e,listasub,rez)(i,i,i,o)

substituie([],_,_,[]).
substituie([E|T],E,L,Rez):-
    !,
    substituie(T,E,L,RezT),
    conc(L,RezT,Rez).
    
substituie([H|T],E,L,[H|Rez]):-
    substituie(T,E,L,Rez).