# Proiect Rețea de Socializare - Detalii de Implementare și Arhitectură

Acest document detaliază alegerile arhitecturale, refactorizările aplicate și principiile de design folosite în implementarea aplicației.

## 1. Refactorizare: Trecerea la Java Stream API

Pentru a îmbunătăți lizibilitatea și performanța codului, majoritatea buclelor clasice au fost înlocuite cu operații pe fluxuri de date (Stream API):

*   **`AbstractFileRepository.loadData`**: S-a înlocuit citirea clasică (`while`) cu `Files.lines()` și `IntStream.range()` pentru indexarea liniilor, permițând raportarea erorilor direct la numărul liniei corupte.
*   **`AbstractFileRepository.writeToFile`**: Bucla `for-each` a fost înlocuită cu `StreamSupport.stream()` pe `findAll()`, mapat în String-uri și salvat simplu cu `Files.write()`.
*   **`ReteaService.removeUtilizator`**: Căutarea și ștergerea prieteniilor se face folosind `findAll(Predicate)`. ID-urile sunt extrase prin `map()` și șterse printr-un `forEach()` pe lista rezultată.
*   **`ReteaService.getPrieteniUtilizator`**: Vechile instrucțiuni `if` au devenit un pipeline fluent: `filter() -> map() -> flatMap(Optional::stream) -> sorted() -> collect()`.
*   **`ReteaService.nrComunitati`**: Bucla `for` a fost înlocuită de un stream peste nodurile nevizitate folosind `filter()`, apelul de BFS adăugat prin `peek()`, finalizat cu operația terminală `count()`.
*   **`ReteaService.ceaMaiSociabilaComunitate`**: Memorarea maximului printr-un `for` clasic s-a transformat direct în `.max(Comparator.comparingInt(...))` apelat pe stream.

### Bucle păstrate justificat
*   **`ConsoleUI`**: S-a păstrat bucla `while(true)` pentru meniul interactiv, deoarece aplicația așteaptă constant input de la tastatură până la comanda explicită de exit.
*   **`ReteaService.bfs`**: Bucla `while(!coada.isEmpty())` a fost păstrată. Algoritmul Breadth-First Search depinde de modificarea dinamică a unei cozi. Forțarea înlocuirii cu un stream ar face codul ilizibil. (Parcurgerea vecinilor în interiorul ei a fost deja optimizată cu stream-uri).

## 2. Programare Funcțională

### Interfețe Funcționale Utilizate
*   **`Validator<T>`**: Adnotată cu `@FunctionalInterface`, cu o metodă default adăugată `andThen()`. Permite compunerea cu noi reguli prin expresii lambda (ex: validarea lungimii numelui direct în Main).
*   **`Predicate<E>`**: Folosită direct pentru filtrări în `Repository.findAll(Predicate)` și în clasa de utilitare `CriteriiUtilizator`.
*   **`Function<T, R>`**: Folosită în `RepositoryFactory` pentru a înlocui structura `switch` cu un `Map` curat care instanțiază repository-urile.

### Referințe la Metode
*   **Metodă statică**: `CriteriiUtilizator::areIdPar` (ca filtru în UI).
*   **Metodă de instanță a unui obiect specific**: `System.out::println` (iterări în UI), `repoPrietenii::delete`, `this::createEntityAsString`.
*   **Metodă de instanță a unui obiect de tip oarecare**: `Utilizator::getLastName`, `Prietenie::getId`, `Optional::stream`.
*   **Constructor**: `InMemoryRepository::new` (în Factory), `ArrayList::new` (în Service).

## 3. Arhitectură și Persistența Datelor

### Folosirea `Optional` în Repository
Metodele `findOne`, `save`, `delete` și `update` returnează acum `Optional<E>` în loc de entitate sau `null`. Acest lucru forțează Service-ul să trateze explicit lipsa unui obiect, prevenind erorile de tip `NullPointerException`. Extragerea se face controlat prin `.orElseThrow()` sau `.ifPresent()`.

### Funcționare Factory și Baze de Date
*   Clasa `RepositoryFactory` citește fișierul `src/main/resources/config.properties` folosind `try-with-resources`.
*   În funcție de proprietatea `repository.type`, repository-urile se instanțiază automat (ex: `MEMORY`, `DATABASE`, `FILE`).
*   Trecerea la baza de date este complet transparentă pentru `Main`, `UI`, `Service` și `Repository`. Necesită doar implementarea cerințelor funcționale DB și modificarea tipului în `config.properties` în `DATABASE`.

### Validarea și Gestiunea Fișierelor
*   Dacă fișierul nu există pe disc, aplicația pornește cu repository-ul gol. Fișierul este creat automat la primul apel reușit de `save()`.
*   Liniile corupte (sau invalide) sunt raportate în consola de erori și ignorate, permițând încărcarea restului de date valide.
*   Validarea formatului datelor se face în Repository, asigurând că nu există entități invalide. Validarea de existență logică (ex: prietenii valide) se face în `ReteaService`, deoarece implică interogarea a două repository-uri diferite.

## 4. Design Patterns și Principii SOLID

### Principii SOLID respectate
*   **SRP (Single Responsibility Principle)**: Fiecare clasă are o singură responsabilitate (ex: fiecare subclasă de `AbstractFileRepository` știe doar cum să își parseze propria entitate).
*   **OCP (Open/Closed Principle)**: Ierarhia Repository și Factory permit adăugarea de noi metode de stocare fără a modifica codul din Service sau UI.
*   **LSP (Liskov Substitution Principle)**: Orice subtip al interfeței `Repository` poate înlocui tipul de bază în `ReteaService` fără a strica funcționalitatea programului.
*   **DIP (Dependency Inversion Principle)**: Modulele de nivel înalt (`Service`) nu depind de implementări concrete, ci exclusiv de abstractizări (`Repository<ID,E>`, `Validator<E>`).

### Șabloane de Proiectare (Design Patterns)
*   **Simple Factory & Singleton**: Utilizate în clasa `RepositoryFactory`, care centralizează crearea repository-urilor pe baza fișierului de configurare.
*   **Template Method**: Aplicat în `AbstractFileRepository`. Algoritmul general de citire/scriere (procesele de I/O spre Stream API) este definit în clasa de bază, în timp ce conversia specifică este lăsată claselor copil.
*   **Strategy**: Implementat prin interfața `Validator` pentru a decupla logica de validare.
*   **Decorator**: Utilizat nativ în lucrul cu fluxurile I/O din Java (ex. `BufferedReader`, `BufferedWriter`).