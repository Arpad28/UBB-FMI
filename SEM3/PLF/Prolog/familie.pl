% Acestea sunt FAPTE (relații care sunt mereu adevărate)
% Y este mama tata lui X
mama(ion, maria).
mama(elena, maria).
tata(ion, vasile).
tata(ana, ion).
tata(andrei, ion).
tata(elena, vasile).

% Aceasta este o REGULĂ
% Y este parintele lui X
parinte(X,Y):-mama(X,Y).
parinte(X,Y):-tata(X,Y).
%Y este fratele lui X
frate(X,Y) :- parinte(X,Z),
              parinte(Y,Z),
              X\=Y.
%Y este bunicul lui X
bunici(X,Y):-parinte(X,Z),
            parinte(Z,Y).