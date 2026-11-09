%descompunere(lista,rez,nrpar,nrimpar)(i,o,o,o)

descompunere([],[[],[]],0,0).

descompunere([H|T],[[H|Par],Impar],Nrpnou,Nri):-
    H mod 2 =:=0,!,
    descompunere(T,[Par,Impar],Nrp,Nri),
    Nrpnou is Nrp+1 .
    
descompunere([H|T],[Par,[H|Impar]],Nrp,Nrinou):-
    descompunere(T,[Par,Impar],Nrp,Nri),
    Nrinou is Nri+1 .

    