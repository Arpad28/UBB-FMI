%cmmdc(e1,e2,rez)(i,i,o)

cmmdc(A,0,A):-!.
cmmdc(A,B,Rez):-
    Rest is A mod B,
    cmmdc(B,Rest,Rez).

%cmmc(e1,e2,rez)(i,i,o)
cmmc(A,B,Rez):-
    cmmdc(A,B,D),
    Rez is (A * B) // D.

%cmmcl(lista,rez)(i,o)
cmmcl([H],H):-!.
cmmcl([H|T],Rez):-
    cmmcl(T,Temp),
    cmmc(H,Temp,Rez).
    