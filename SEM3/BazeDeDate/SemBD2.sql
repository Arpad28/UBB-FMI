--adaugarea datelor

INSERT INTO Utilizatori(nume,email,parola,data_nasterii)
VALUES
(N'Andrei',N'andrei@gmail.com',N'csefre543rrfv','2006-12-23'),
(N'Tom',N'tom@gmail.com',N'f3t54c3fe3s','2000-09-09'),
(N'Jane',NULL,N'qwerty32ews','2000-11-23');

SELECT * FROM Utilizatori;
SELECT cod_u,nume,email,parola,data_nasterii FROM Utilizatori;
SELECT nume,email FROM Utilizatori;
SELECT nume  AS utilizator,email FROM Utilizatori;

SELECT * FROM Utilizatori WHERE data_nasterii='2000-11-23';
SELECT * FROM Utilizatori WHERE email IS NULL;
SELECT * FROM Utilizatori WHERE email IS NOT NULL;

--actualizarea datelor
UPDATE Utilizatori SET nume=N'',email=N'jane@gmail.com'
WHERE cod_u=3;

UPDATE Utilizatori SET nume=N'Jane' WHERE cod_u=3;

--stergerea datelor

DELETE FROM Utilizatori WHERE cod_u=1;