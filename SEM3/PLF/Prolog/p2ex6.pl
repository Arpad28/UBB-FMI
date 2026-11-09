%concat(lista,lista,rez)(i,i,o)

concat([],L,L).
concat([H|T],L,[H|Rez]):-
    concat(T,L,Rez).
    
%inloc(lista,elem,listelem,rez)(i,i,i,o)
inloc([],_,_,[]).
inloc([H|T],E,L,Rez):-
    H=:=E,
    !,
    inloc(T,E,L,RezT),
    concat(L,RezT,Rez).
    
inloc([H|T],E,L,[H|Rez]):-
    inloc(T,E,L,Rez).