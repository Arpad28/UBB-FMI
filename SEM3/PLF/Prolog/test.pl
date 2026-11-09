%sterge(lista,pozc,pozn,rez)(i,i,i,o)

sterge([],_,_,[]):-!.
sterge([_|T],Pos,Pos,Rez):-
    !,
    Pos1 is Pos*2+1,
    Posc is Pos+1,
    sterge(T,Posc,Pos1,Rez).
sterge([H|T],Posc,Pos,[H|Rez]):-
    Posc1 is Posc+1,
    sterge(T,Posc1,Pos,Rez).
%duplica(lista,rez)(i,o)

duplica([],[]):-!.
duplica([H|T],[H,H|Rez]):-
    H mod 2 =:= 0,
    !,
    duplica(T,Rez).
duplica([H|T],[H|Rez]):-
    duplica(T,Rez).
%main(lista,rez)(i,o)
main([],[]).
main(L,Rez):-
    sterge(L,1,1,RezT),
    duplica(RezT,Rez).