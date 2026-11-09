%insereaza(lista,el,rez)(i,i,o)

insereaza([],E,[E]):-!.
insereaza([H|T],E,[E,H|T]):-
    E=<H,
    !.
insereaza([H|T],E,[H|Rez]):-
    insereaza(T,E,Rez).
    
%sortare(lista,rez)(i,o)

sortare([],[]).
sortare([H|T],Rez):-
    sortare(T,RezT),
    insereaza(RezT,H,Rez).