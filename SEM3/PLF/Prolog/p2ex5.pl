%maxim(lista,rez)(i,o)

maxim([H|T],Rez):-
    maxim_aux(T,H,Rez).
    
%maxim_aux(lista,maxi,rez)(i,i,o)
maxim_aux([],Rez,Rez):-!.
maxim_aux([H|T],Maxi,Rez):-
    H>Maxi,
    !,
    maxim_aux(T,H,Rez).
maxim_aux([_|T],Maxi,Rez):-
    maxim_aux(T,Maxi,Rez).
   
%pozitii(lista,maxim,poz,rez)(i,i,i,o)

pozitii([],_,_,[]):-!.
pozitii([H|T],E,Poz,[Poz|Rez]):-
    H=:=E,
    !,
    Poz1 is Poz+1,
    pozitii(T,E,Poz1,Rez).
pozitii([_|T],E,Poz,Rez):-
    Poz1 is Poz+1,
    pozitii(T,E,Poz1,Rez).
    
%inloc_max(lista,rez)(i,o)
inloc_max([],[]):-!.
inloc_max(L,Rez):-
    maxim(L,RezT),
    pozitii(L,RezT,1,Rez).

    