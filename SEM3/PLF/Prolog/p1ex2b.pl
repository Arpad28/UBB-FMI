%adauga_rec(lista,E,pozcurent,pozurm,Rez)(i,i,i,i,o)

adauga_rec([],_,_,_,[]).
adauga_rec([H|T],E,Poz,Poz,[H,E|Rez]):-!,
    Poz1 is Poz+1,
    Put1 is Poz*2,
    adauga_rec(T,E,Poz1,Put1,Rez).
adauga_rec([H|T],E,Poz,Put,[H|Rez]):-
    Poz1 is Poz+1,
    adauga_rec(T,E,Poz1,Put,Rez).

%adauga(lista,e,rez)(i,i,o)

adauga(Lista,E,Rez):-
    adauga_rec(Lista,E,1,1,Rez).