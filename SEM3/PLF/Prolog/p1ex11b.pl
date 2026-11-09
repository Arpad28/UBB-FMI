%suma_alt(lista,rez)(i,o)

suma_alt([],0):-!.

suma_alt([H],H):-!.

suma_alt([H1,H2|T],Rez):-
    suma_alt(T,Rezultat),
    Rez is H1-H2+Rezultat.