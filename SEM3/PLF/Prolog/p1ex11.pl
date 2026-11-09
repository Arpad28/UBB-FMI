% vale(lista)(i)
% vale_rec(lista,st)(i, i)

vale([H1, H2 | T]) :-
    H1 > H2,
    vale_rec([H1, H2 | T], 0).
    
vale_rec([H1, H2 | T], 0) :-
    H1 > H2,
    vale_rec([H2 | T], 0).

vale_rec([H1, H2 | T], 0) :-
    H1 < H2,
    vale_rec([H2 | T], 1).

vale_rec([H1, H2 | T], 1) :-
    H1 < H2,
    vale_rec([H2 | T], 1).

vale_rec([_], 1).
