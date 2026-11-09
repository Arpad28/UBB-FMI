%sterge(element,lista,rez)(i,i,o)

sterge(_,[],[]):-!.
sterge(E,[E|T],Rez):-
    !,
    sterge(E,T,Rez).
sterge(E,[H|T],[H|Rez]):-
    sterge(E,T,Rez).
    
%multime(lista,rez)(i,o)

multime([],[]):-!.
multime([H|T],[H|Rez]):-
    sterge(H,T,Tnou),
    multime(Tnou,Rez).