class UI:
    def __init__(self, srv_clienti, srv_filme, srv_inchirieri, undo):
        self.ctrl_clienti = srv_clienti
        self.ctrl_filme = srv_filme
        self.ctrl_inchirieri = srv_inchirieri
        self.undo = undo
        self.comenzi_text = '''==================Comenzi disponibile==================
adauga_client <id> <nume> <cnp>
adauga_film <id> <titlu> <descriere> <gen>
genereaza_filme <numar>
sterge_client <id>
sterge_film <id>
cauta_client <id>
cauta_film <id>
lista_clienti
lista_clienti_ordonata_nume
lista_clienti_ordonata_inchirieri
lista_filme
lista_filme_ordonata_inchirieri
actualizeaza_client <id> <nume_nou> <cnp_nou>
actualizeaza_film <id> <titlu_nou> <descriere_nou> <gen_nou>
inchiriaza_film <id> <id_film> <id_client> <an_inchiriere> <luna_inchiriere> <zi_inchiriere>
sterge_inchiriere <id>
returneaza_film <id> <an_returnare> <luna_returnare> <zi_returnare>
cauta_inchiriere <id>
raport_inchiriere <procent>
lista_inchirieri
raport_legatura <primii 'numar' rapoarte>
undo
exit
========================================================\n'''


    def ruleaza(self):
        print("Scrie 'help' pentru lista de comenzi")
        while True:
            linie = input(">>> ").strip()
            if not linie:
                continue

            parti = linie.split()
            comanda = parti[0]
            args = parti[1:]

            try:
                if comanda == "adauga_client":
                    id_client, nume_client, cnp_client = args
                    self.ctrl_clienti.adauga_client(id_client, nume_client, cnp_client)
                    print("Client adăugat cu succes")

                elif comanda == "adauga_film":
                    id_film, titlu, descriere, gen = args
                    self.ctrl_filme.adauga_film(id_film, titlu, descriere, gen)
                    print("Film adăugat cu succes")

                elif comanda == "sterge_client":
                    if args:
                        self.ctrl_clienti.sterge_client(args[0])
                        print("Client șters cu succes")
                    else:
                        raise ValueError("ID nespecificiat")

                elif comanda == "sterge_film":
                    if args:
                        self.ctrl_filme.sterge_film(args[0])
                        print("Film șters cu succes")
                    else:
                        raise ValueError("ID nespecificiat")

                elif comanda == "cauta_client":
                    if args:
                        c = self.ctrl_clienti.cauta_client(args[0])
                        print(c.get_id_client(), c.get_nume_client(), c.get_cnp_client())
                    else:
                        raise ValueError("ID nespecificiat")

                elif comanda == "cauta_film":
                    if args:
                        f = self.ctrl_filme.cauta_film(args[0])
                        print(f.get_id_film(), f.get_titlu(), f.get_descriere(),
                              f.get_gen(), f.get_inchiriat())
                    else:
                        raise ValueError("ID nespecificiat")

                elif comanda == "lista_clienti":
                    for c in self.ctrl_clienti.lista_clienti():
                        print(c.get_id_client(), c.get_nume_client(),
                              c.get_cnp_client(), c.get_nr_inchiriate())

                elif comanda == "lista_clienti_ordonata_nume":
                    for c in self.ctrl_clienti.clienti_sortati_dupa_nume():
                        print(c.get_id_client(), c.get_nume_client(),
                              c.get_cnp_client(), c.get_nr_inchiriate())

                elif comanda == "lista_clienti_ordonata_inchirieri":
                    for c in self.ctrl_clienti.clienti_sortati_dupa_nr_filme_inchiriate():
                        print(c.get_id_client(), c.get_nume_client(),
                              c.get_cnp_client(), c.get_nr_inchiriate())

                elif comanda == "lista_filme":
                    for f in self.ctrl_filme.lista_filme():
                        print(f.get_id_film(), f.get_titlu(), f.get_descriere(),
                              f.get_gen(), f.get_inchiriat(), f.get_fost_inchiriat())

                elif comanda == "lista_filme_ordonata_inchirieri":
                    for f in self.ctrl_filme.filme_sortati_nr_inchirate():
                        print(f.get_id_film(), f.get_titlu(), f.get_descriere(),
                              f.get_gen(), f.get_inchiriat(), f.get_fost_inchiriat())

                elif comanda == "actualizeaza_client":
                    id_client, nume_client, cnp_client = args
                    self.ctrl_clienti.actualizare_client(id_client, nume_client, cnp_client)
                    print("Client actualizat.")

                elif comanda == "actualizeaza_film":
                    id_film, titlu, descriere, gen = args
                    self.ctrl_filme.actualizare_film(id_film, titlu, descriere, gen)
                    print("Film actualizat")

                elif comanda == "inchiriaza_film":
                    id_inchiriere, id_film, id_client, an, luna, zi = args
                    self.ctrl_inchirieri.inchireaza_film(id_inchiriere, id_film, id_client, an, luna, zi)
                    print(f"Filmul cu id-ul {id_film} a fost închiriat cu succes de clientul cu id-ul {id_client}")

                elif comanda == "sterge_inchiriere":
                    if args:
                        self.ctrl_inchirieri.sterge_inchiriere(args[0])
                        print("Închiriere ștearsă cu succes")
                    else:
                        raise ValueError("ID nespecificiat")

                elif comanda == "returneaza_film":
                    id_inchiriere, an, luna, zi = args
                    self.ctrl_inchirieri.retureaza_film(id_inchiriere, an, luna, zi)
                    print("Film returnat cu succes")

                elif comanda == "cauta_inchiriere":
                    if args:
                        inch = self.ctrl_inchirieri.cauta_inchirere(args[0])
                        print(inch.get_id_inchiriere(), inch.get_id_film(), inch.get_id_client(),
                              inch.get_data_inchirierii(), inch.get_data_returnarii())
                    else:
                        raise ValueError("ID nespecificiat")

                elif comanda == "raport_inchiriere":
                    if args:
                        procent = int(args[0])
                        clienti = self.ctrl_clienti.raport_clienti(procent)
                        for c in clienti:
                            print(c.get_id_client(), c.get_nume_client(), c.get_nr_inchiriate())
                    else:
                        raise ValueError("Procent nespecificiat")

                elif comanda == "lista_inchirieri":
                    for inch in self.ctrl_inchirieri.lista_inchirieri():
                        print(inch.get_id_inchiriere(), inch.get_id_film(), inch.get_id_client(),
                              inch.get_data_inchirierii(), inch.get_data_returnarii())

                elif comanda == "raport_legatura":
                    if args:
                        numar =int(args[0])
                        raport=self.ctrl_inchirieri.raport_legatura(numar)
                        for client,total,lista_filme in raport:
                            print(f"CLientul {client.get_nume_client()} a închiriat în total {total} filme")
                            for id_film,titlu,suma in lista_filme:
                                print(f"Filmul {id_film} cu titlul {titlu} a fost închiriat de {suma} ori")
                    else:
                        raise ValueError("Număr nespecificiat")

                elif comanda == "genereaza_filme":
                    if args:
                        numar = int(args[0])
                        self.ctrl_filme.genereaza_filme(numar)
                    else:
                        raise ValueError("Număr nespecificiat")

                elif comanda == "undo":
                    self.undo.undo()
                    print("Ultima acțiune a fost anulată")

                elif comanda == "help":
                    print(self.comenzi_text)

                elif comanda == "exit":
                    print("La revedere!")
                    break

                else:
                    print("Comandă necunoscută")

            except ValueError as eroare:
                print("Eroare:", eroare)
