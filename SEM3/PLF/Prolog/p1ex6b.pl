%sterge(lista,e,rez)(i,i,o)

sterge([],_,[]):-!.
sterge([E|T],E,Rez):-
    !,
    sterge(T,E,Rez).
sterge([H|T],E,[H|Rez]):-
    sterge(T,E,Rez).
    
%maxim_rec(lista,rez)(i,o)

maxim_rec([H|T],Rez):-
    maxim(T,H,Rez).
    
%maxim(lista,elem,rez)(i,i,o)

maxim([],Rez,Rez):-!.

maxim([H|T],Maxi,Rez):-
    H>Maxi,
    !,
    maxim(T,H,Rez).
maxim([_|T],Maxi,Rez):-
    maxim(T,Maxi,Rez).
    
%elim(lista,rez)(i,o)

elim(L,Rez):-
    maxim_rec(L,Maxim),
    sterge(L,Maxim,Rez).