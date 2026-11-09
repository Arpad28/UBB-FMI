%insereaza(lista,element,rez)(i,i,o)

insereaza([],E,[E]):-!.

insereaza([H|T],E,[H|T]):-
    H=:=E,
    !.
insereaza([H|T],E,[E,H|T]):-
    E<H,
    !.
insereaza([H|T],E,[H|Rez]):-
    insereaza(T,E,Rez).
    
%sortare(lista,rez)(i,o)

sortare([],[]):-!.
sortare([H|T],Rez):-
    sortare(T,RezT),
    insereaza(RezT,H,Rez).
 
%lista(lista,rez)(i,o)

lista([],[]):-!.
lista([H|T],[H1|Rez]):-
    is_list(H),
    !,
    sortare(H,H1),
    lista(T,Rez).
lista([H|T],[H|Rez]):-
    lista(T,Rez).