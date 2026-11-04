package UI;

import Domain.Prietenie;
import Domain.Utilizator;
import Domain.validators.ValidationException;
import Repository.RepositoryException;
import Service.ReteaService;

import java.util.Scanner;

public class ConsoleUI {
    private final ReteaService service;
    private final Scanner scanner;

    public ConsoleUI(ReteaService service) {
        this.service = service;
        this.scanner = new Scanner(System.in);
    }

    public void run() {
        while (true) {
            System.out.println("\n--- Meniu ---");
            System.out.println("1. Adauga utilizator");
            System.out.println("2. Sterge utilizator");
            System.out.println("3. Adauga prietenie");
            System.out.println("4. Sterge prietenie");
            System.out.println("5. Afiseaza toti utilizatorii");
            System.out.println("6. Afiseaza toate prieteniile");
            System.out.println("7. Numar de comunitati");
            System.out.println("8. Cea mai sociabila comunitate");
            System.out.println("0. Iesire");
            System.out.print("Alegeti o optiune: ");

            String optiune = scanner.nextLine().trim();

            try {
                switch (optiune) {
                    case "1":
                        adaugaUser();
                        break;
                    case "2":
                        stergeUser();
                        break;
                    case "3":
                        adaugaPrietenie();
                        break;
                    case "4":
                        stergePrietenie();
                        break;
                    case "5":
                        afiseazaUtilizatori();
                        break;
                    case "6":
                        afiseazaPrietenii();
                        break;
                    case "7":
                        System.out.println("Numar comunitati: " + service.nrComunitati());
                        break;
                    case "8":
                        System.out.println("Cea mai sociabila comunitate (ID-uri): " + service.ceaMaiSociabilaComunitate());
                        break;
                    case "0":
                        return;
                    default:
                        System.out.println("Optiune invalida!");
                        break;
                }
            } catch (NumberFormatException e) {
                System.out.println("Eroare de format: ID-ul introdus trebuie sa fie un numar intreg!");
            } catch (ValidationException e) {
                System.out.println("Eroare de validare: " + e.getMessage());
            } catch (RepositoryException e) {
                System.out.println("Eroare de persistenta: " + e.getMessage());
            } catch (IllegalArgumentException | UnsupportedOperationException e) {
                System.out.println("Eroare: " + e.getMessage());
            }
        }
    }

    private void adaugaUser() {
        System.out.print("ID: ");
        Long id = Long.parseLong(scanner.nextLine().trim());
        System.out.print("Prenume: ");
        String prenume = scanner.nextLine().trim();
        System.out.print("Nume: ");
        String nume = scanner.nextLine().trim();
        service.addUtilizator(id, prenume, nume);
        System.out.println("Utilizator adaugat!");
    }

    private void stergeUser() {
        System.out.print("ID: ");
        Long id = Long.parseLong(scanner.nextLine().trim());
        service.removeUtilizator(id);
        System.out.println("Utilizator sters!");
    }

    private void adaugaPrietenie() {
        System.out.print("ID User 1: ");
        Long id1 = Long.parseLong(scanner.nextLine().trim());
        System.out.print("ID User 2: ");
        Long id2 = Long.parseLong(scanner.nextLine().trim());
        service.addPrietenie(id1, id2);
        System.out.println("Prietenie adaugata!");
    }

    private void stergePrietenie() {
        System.out.print("ID User 1: ");
        Long id1 = Long.parseLong(scanner.nextLine().trim());
        System.out.print("ID User 2: ");
        Long id2 = Long.parseLong(scanner.nextLine().trim());
        service.removePrietenie(id1, id2);
        System.out.println("Prietenie stearsa!");
    }

    private void afiseazaUtilizatori() {
        for (Utilizator u : service.getAllUtilizatori()) {
            System.out.println(u);
        }
    }

    private void afiseazaPrietenii() {
        for (Prietenie p : service.getAllPrietenii()) {
            System.out.println(p);
        }
    }
}