%conc(lista,lista,rez)(i,i,o)

conc([],L,L):-!.
conc([H|T],L,[H|Rez]):-
    conc(T,L,Rez).
    
%perechi(lista,elem,rez)(i,i,o)

perechi([],_,[]):-!.
perechi([H|T],E,[[E,H]|Rez]):-
    perechi(T,E,Rez).

%rezolva(lista,rez)(i,o)

rezolva([],[]).
rezolva([H|T],Rez):-
    perechi(T,H,RezT),
    rezolva(T,Rest),
    conc(RezT,Rest,Rez).