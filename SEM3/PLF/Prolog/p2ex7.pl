%inmultire_aux(lista,cifra,transport,rez) (i,i,i,o)
inmultire_aux([],_,0,[]):-!.
inmultire_aux([],_,T,[T]):- T > 0,!.
inmultire_aux([H|T],C,Trans,[CifraAcutala|RezT]):-
    Prod is H * C + Trans,
    CifraAcutala is Prod mod 10,
    Tnou is Prod div 10,
    inmultire_aux(T,C,Tnou,RezT).

%invers(lista,col,rez) (i,i,o)
invers([],Col,Col):-!.
invers([H|T],Col,Rez):-invers(T,[H|Col],Rez).

%inmultire(lista,cif,rez) (i,i,o)
inmultire(Lista,Cifra,Rez):-
    invers(Lista,[],ListaInv),
    inmultire_aux(ListaInv,Cifra,0,RezInv),
    invers(RezInv,[],Rez).