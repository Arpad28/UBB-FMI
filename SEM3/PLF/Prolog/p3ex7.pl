%candidat(lista,rez)(i,o)

candidat([E|_],E).
candidat([_|T],Rez):-
    candidat(T,Rez).

%apare(lista,elem)(i,i)
apare([E|_],E):-!.
apare([_|T],E):-
    apare(T,E).
    
%aranj_back(lista,k,rez)(i,i,o)
aranj_back(L,K,Rez):-
    candidat(L,E),
    aranj_aux(L,K,Rez,1,[E]).
    
%aranj_aux(lista,k,rez,knostru,listanoastra)(i,i,o,i,i)
aranj_aux(_,K,Rez,K,Rez):-!.
aranj_aux(L,K,Rez,Lg,Col):-
    Lg<K,
    candidat(L,E),
    \+apare(Col,E),
    Lg1 is Lg+1,
    aranj_aux(L,K,Rez,Lg1,[E|Col]).

%aranjamente(lista,k,rez)(i,i,o)
aranjamente(L,K,Rez):-
    findall(RezT,aranj_back(L,K,RezT),Rez).