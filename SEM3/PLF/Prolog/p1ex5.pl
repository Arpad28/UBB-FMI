%sterge(lista,el,rez)(i,i,o)

sterge([],_,[]).
sterge([E|T],E,Rez):-
    !,
    sterge(T,E,Rez).
sterge([H|T],E,[H|Rez]):-
    sterge(T,E,Rez).