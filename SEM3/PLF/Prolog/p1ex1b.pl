%adaugapar(lista,rez)(i,o)

adaugapar([],[]).
adaugapar([H|T],[H,1|Rez]):-
    H mod 2 =:= 0,!,
    adaugapar(T,Rez).
adaugapar([H|T],[H|Rez]):-
    adaugapar(T,Rez).
    