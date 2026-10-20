CREATE DATABASE Blog226; --crearea bazei de date
GO
USE Blog226;
--crearea tabelei


CREATE TABLE Utilizatori(
	cod_u INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(100) NOT NULL,
	email NVARCHAR(100) UNIQUE,
	parola NVARCHAR(200),
	data_nasterii DATE
);

CREATE TABLE Postari(
	cod_p INT PRIMARY KEY IDENTITY(1,1),
	titlu NVARCHAR(50),
	continut NVARCHAR(50),
	data_publicarii DATETIME,
	cod_u INT FOREIGN KEY REFERENCES Utilizatori(cod_u)
);

CREATE TABLE Comentarii(
	cod_c INT PRIMARY KEY IDENTITY,
	continut NVARCHAR(400),
	data_publicarii DATETIME,
	cod_u INT FOREIGN KEY REFERENCES Utilizatori(cod_u),
	cod_p INT FOREIGN KEY REFERENCES Postari(cod_p)
);

CREATE TABLE CuvinteCheie(
	cod_cc INT PRIMARY KEY IDENTITY,
	nume VARCHAR(100)
);
/*
tabel de legatura
*/

CREATE TABLE PostariCuvinteCheie(
	cod_p INT FOREIGN KEY REFERENCES Postari(cod_p),
	cod_cc INT FOREIGN KEY REFERENCES CuvinteCheie(cod_cc),
	CONSTRAINT pk_PostariCuvinteCheie PRIMARY KEY(cod_p,cod_cc)
);