%apartine(lista,elem)(i,i)

apartine([E|_],E):-!.
apartine([_|T],E):-
    apartine(T,E).
    
%reuniune(lista,lista,rez)(i,i,o)

reuniune([],L,L).
reuniune([H|T],L,[H|Rez]):-
    \+apartine(L,H),
    !,
    reuniune(T,L,Rez).
reuniune([_|T],L,Rez):-
    reuniune(T,L,Rez).