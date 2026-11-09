%concat(lista,lista,rez)(i,i,o)

concat([],L,L):-!.
concat([H|T],L,[H|Rez]):-
    concat(T,L,Rez).
    
%inloc(lista,elem,listaelem,rez)(i,i,i,o)

inloc([],_,_,[]):-!.
inloc([H|T],E,L,Rez):-
    H=:=E,
    !,
    inloc(T,E,L,RezT),
    concat(L,RezT,Rez).
inloc([H|T],E,L,[H|Rez]):-
    inloc(T,E,L,Rez).
    
%lista(lista,lista,rez)(i,i,o)
lista([],_,[]).
lista([H|T],L,[H1|Rez]):-
    is_list(H),
    !,
    procesare_lista(H,L,H1),
    lista(T,L,Rez).
lista([H|T],L,[H|Rez]):-
    lista(T,L,Rez).
    
%procesare_lista(lista,lista,rez)(i,i,o)

procesare_lista([],_,[]):-!.
procesare_lista([H|T],L,Rez):-
    inloc([H|T],H,L,Rez).