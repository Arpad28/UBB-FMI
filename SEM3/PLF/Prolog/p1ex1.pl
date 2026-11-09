%apartine(element,lista) (i,i)

apartine(E,[E|_]).
apartine(E,[_|T]):-
    apartine(E,T).
    
%diferenta(lista1,lista2,rez) (i,i,o)
diferenta([],_,[]).
diferenta([H|T],L,Rez):-
    apartine(H,L),!,
    diferenta(T,L,Rez).
diferenta([H|T],L,[H|Rez]):-
    diferenta(T,L,Rez).
