%inter(lista,lista,rez)(i,i,o)

inter([H,H|T],L,Rez):-
    inter([H|T],L,Rez).
    
inter(L,[H,H|T],Rez):-
    inter(L,[H|T],Rez).

inter([],L,L):-!.
inter(L,[],L):-!.

inter([H|T1],[H|T2],[H|Rez]):-
    !,
    inter(T1,T2,Rez).
inter([H1|T1],[H2|T2],[H1|Rez]):-
    H1<H2,
    !,
    inter(T1,[H2|T2],Rez).
inter([H1|T1],[H2|T2],[H2|Rez]):-
    inter([H1|T1],T2,Rez).
    
%lista(lista,rez)(i,o)

lista([],[]):-!.
lista([H|T],Rez):-
    is_list(H),
    !,
    lista(T,RezT),
    inter(H,RezT,Rez).
lista([_|T],Rez):-
    lista(T,Rez).