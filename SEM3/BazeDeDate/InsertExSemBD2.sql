INSERT INTO Sectiuni (Nume, Descriere) VALUES 
(N'Tărâmul de Poveste', N'Zone pentru copii'),
(N'Aventura Extremă', N'Adrenalină pură'),
(N'Zona Acvatică', N'Piscine și tobogane'),
(N'Lumea Dinozaurilor', N'Atractii tematice'),
(N'Tărâmul Viitorului', N'VR și simulatoare'),
(N'Satul Haiducilor', N'Zona traditională'),
(N'Insula Piraților', N'Jocuri cu apă'),
(N'Grădina Zoologică', N'Animale blânde'),
(N'Zona Galactică', N'Space coasters'),
(N'Misterele Pădurii', N'Trasee prin copaci');

INSERT INTO CategoriiVizitatori (Nume) VALUES 
(N'Adult Standard'),
(N'Copil sub 7 ani'),
(N'Student / Elev'),
(N'Pensionar'),
(N'VIP Gold'),
(N'VIP Platinum'),
(N'Grup Școlar'),
(N'Persoană cu dizabilități'),
(N'Membru Familie Mare'),
(N'Bilet Sezonier');

INSERT INTO Atractii (Nume, Descriere, Varsta_Minima, ID_sectiune) VALUES 
(N'Caruselul Magic', N'Carusel clasic', 3, 1),
(N'Roata Panoramică', N'Priveliște parțială', 0, 1),
(N'Dragonul Roșu', N'Rollercoaster rapid', 12, 2),
(N'Turnul Căderii', N'Cădere 40m', 14, 2),
(N'Anaconda', N'Tobogan acvatic', 10, 3),
(N'Râul Rapid', N'Colace pe apă', 6, 3),
(N'T-Rex Coaster', N'Dino coaster', 10, 4),
(N'HyperDrive VR', N'Simulator VR', 12, 5),
(N'Corabia Piraților', N'Leagăn gigant', 8, 7),
(N'Zborul Vulturului', N'Zip-line', 14, 10),
(N'Cascada Secreta', N'Plimbare bărcuțe', 4, 3),
(N'Labirintul Magic', N'Labirint oglinzi', 5, 1);

INSERT INTO Vizitatori (Nume, Email, ID_categorie) VALUES 
(N'Popescu Ion', 'ion.popescu@gmail.com', 1),
(N'Ionescu Maria', 'maria.ionescu@yahoo.com', 3),
(N'Georgescu Vlad', 'vlad.g@outlook.com', 2),
(N'Dumitrescu Elena', 'elena_d@gmail.com', 1),
(N'Marinescu Radu', 'radu.m@yahoo.com', 4),
(N'Vasilescu Ana', 'ana.v@gmail.com', 5),
(N'Constantin Mihai', 'mihai.c@outlook.com', 1),
(N'Stancu Andreea', 'andreea.s@yahoo.com', 3),
(N'Georgescu Cristian', 'cristian.g@gmail.com', 2),
(N'Dobre Gabriela', 'gabriela.d@yahoo.com', 6);

INSERT INTO Note_Vizite (nota, ID_vizitator, ID_atractie) VALUES 
(9.50, 1, 1),
(8.00, 1, 3),
(10.00, 2, 3),
(9.00, 2, 4),
(7.50, 3, 1),
(8.50, 3, 2),
(10.00, 4, 5),
(9.20, 4, 6),
(6.50, 5, 2),
(8.80, 5, 7),
(9.40, 6, 8),
(7.00, 7, 9),
(8.30, 8, 10),
(9.90, 9, 11),
(8.10, 10, 12);