%sterge(lista,el,rez)(i,i,o)

sterge([],_,[]).
sterge([E|T],E,Rez):-
    !,
    sterge(T,E,Rez).
sterge([H|T],E,[H|Rez]):-
    sterge(T,E,Rez).
    
%numara(lista,el,rez)(i,i,o)

numara([],_,0).
numara([E|T],E,Rez):-
    !,
    numara(T,E,RezT),
    Rez is RezT+1.
    
numara([_|T],E,Rez):-
    numara(T,E,Rez).

%numar(lista,rez)(i,o)

numar([],[]).
numar([H|T],[[H,Cnt]|Rez]):-
    numara([H|T],H,Cnt),
    sterge(T,H,Tnou),
    numar(Tnou,Rez).