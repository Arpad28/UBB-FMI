%elimina(lista,poz,rez)(i,i,o)

elimina([],_,[]).
elimina([_|T],1,T):-!.
elimina([H|T],N,[H|Rez]):-
    N>1,
    N1 is N-1,
    elimina(T,N1,Rez).