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
    
% inloc_aux(ListaE,Pos,Rez) (i,i,o)

inloc_aux([], _, []) :- !.

inloc_aux([H|T], Pos, [H_nou|RezT]) :-
    is_list(H), !,          
    inmultire(H, Pos, H_nou),       
    Pos1 is Pos + 1,   
    inloc_aux(T, Pos1, RezT).

inloc_aux([H|T], Pos, [H|RezT]) :-
    inloc_aux(T, Pos, RezT).

% inlocuire(Lista,Rez)(i,o)
inlocuire(Lista, Rez) :-
    inloc_aux(Lista, 1, Rez).