--CREATE DATABASE ParcDistractii;
--GO
USE ParcDistractii;

CREATE TABLE Sectiuni(
	ID_sectiune INT PRIMARY KEY IDENTITY(1,1),
	Nume NVARCHAR(100) NOT NULL,
	Descriere NVARCHAR(100)
);

CREATE TABLE CategoriiVizitatori(
	ID_categorie INT PRIMARY KEY IDENTITY(1,1),
	Nume NVARCHAR(100) NOT NULL
);

CREATE TABLE Atractii(
	ID_atractie INT PRIMARY KEY IDENTITY(1,1),
	Nume NVARCHAR(100) NOT NULL,
	Descriere NVARCHAR(100),
	Varsta_Minima INT,
	ID_sectiune INT FOREIGN KEY REFERENCES Sectiuni(ID_sectiune)
);

CREATE TABLE Vizitatori(
	ID_vizitator INT PRIMARY KEY IDENTITY(1,1),
	Nume NVARCHAR(100) NOT NULL,
	Email NVARCHAR(100) UNIQUE,
	ID_categorie INT FOREIGN KEY REFERENCES CategoriiVizitatori(ID_categorie)
);

CREATE TABLE Note_Vizite(
	nota DECIMAL(4,2),
	ID_vizitator INT FOREIGN KEY REFERENCES Vizitatori(ID_vizitator),
	ID_atractie INT FOREIGN KEY REFERENCES Atractii(ID_atractie),
	CONSTRAINT ID_notevizite PRIMARY KEY(ID_vizitator,ID_atractie),
	CONSTRAINT check_nota CHECK (nota>=1 AND nota<=10)
);
