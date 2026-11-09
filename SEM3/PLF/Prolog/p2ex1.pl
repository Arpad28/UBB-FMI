%invers(lista,rez)(i,o)

invers(L,Rez):-
    invers_rec(L,[],Rez).
    
%invers_rec(lista,col,rez)(i,i,o)

invers_rec([],Rez,Rez):-!.
invers_rec([H|T],Col,Rez):-
    invers_rec(T,[H|Col],Rez).

%aduna_rec(lista,lista,transp,rez)(i,i,i,o)

aduna_rec([],[],0,[]):-!.
aduna_rec([],[],T,[T]):- T > 0,!.
aduna_rec([H|T],[],Tr,[Cifra|Rez]):-
    !,
    S is H+Tr,
    Cifra is S mod 10,
    Rest is S div 10,
    aduna_rec(T,[],Rest,Rez).
aduna_rec([],[H|T],Tr,[Cifra|Rez]):-
    !,
    S is H+Tr,
    Cifra is S mod 10,
    Rest is S div 10,
    aduna_rec([],T,Rest,Rez).
aduna_rec([H1|T1],[H2|T2],T,[Cifra|Rez]):-
    S is H1+H2+T,
    Cifra is S mod 10,
    Rest is S div 10,
    aduna_rec(T1,T2,Rest,Rez).

%aduna(lista,lista,rez)(i,i,o)

aduna(L,[],L):-!.
aduna([],L,L):-!.
aduna(L1,L2,Rez):-
    invers(L1,L11),
    invers(L2,L22),
    aduna_rec(L11,L22,0,RezT),
    invers(RezT,Rez).