%apare(lista,e)(i,i)

apare([E|_],E):-!.
apare([_|T],E):-
    apare(T,E).


%sterge(lista,e,rez)(i,i,o)

sterge([],_,[]):-!.
sterge([E|T],E,Rez):-
    !,
    sterge(T,E,Rez).
sterge([H|T],E,[H|Rez]):-
    sterge(T,E,Rez).
    
%elim(lista,rez)(i,o)

elim([],[]):-!.
elim([H|T],Rez):-
    apare(T,H),
    !,
    sterge(T,H,Tnou),
    elim(Tnou,Rez).
elim([H|T],[H|Rez]):-
    elim(T,Rez).