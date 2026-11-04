
**1.Functionare Factory+Baze de date**

-Clasa RepositoryFactory citeste fisierul src/main/resourcesconfig.properties folosind try-with-resources.
-In functie de proprietatea repository.type, metodele de creare a repository ului se instantiaza automat dupa cum se cere,de exemplu repository.type=MEMORY pentru memorie DATABASE pentru baze de date,FILE pentru Fisier
-Pentru trecerea la baze de date nu voi avea nimic de schimbat in main,ui,service,repo, numai sa implementez cerintele functionale si sa modific in config.resources type ul repositori ului in DATABASE
-Abstract Factory respecta strict OCP dar creste numarul de clase din proiect,dar este good practice pentru a putea adauga functionalitati noi,nemodificand restul functionalitatilor deja facute

**2.Validarea fisierelor corupte**

-Daca fisierul nu exista pe disc, metoda se intoarce imediat, iar aplicatia porneste cu repository-ul gol. Fisierul este creat automat la primul apel reusit de save()
-Linia corupta(sau invalida) este raportata in consola de erori, este ignorata, permitand incarcarea restului de date valide
-Validarea datelor se face in Repository ca nicio entitate invlida sa nu existe. Validarea de existenta a prieteniilor se face in ReteaService, deoarece implica verificarea a doua repository-uri diferite

**3.Principii SOLID si Sabloane de proiectare**

*Principii SOLID*

-SRP(Single Responsibility Principle)Fiecare clasa are o singura responsabilitate
-OCP(OpenClosed Principle) Ierarhia Repository permite adaugarea de noi metode de stocare fara a modifica codul din Service sau UI
-LSP(Liskov Substitution Principle) Orice subtip al interfetei Repository poate inlocui tipul de baza in ReteaService fara a strica corectitudinea programului
-DIP(Dependency Inversion Principle) Modulele de nivel inalt(Service) nu depind de implementari concrete, ci exclusiv de abstractizari(Repository ID,E,Validator<E>)

*Sabloane de proiectare*

-Simple Factory & Singleton In clasa RepositoryFactory, care centralizeaza crearea repositoryurilor pe baza fisierului de configurare
-Template Method In clasa AbstractFileRepository. Algoritmul general de citire si scriere este definit in clasa de baza, iar pasii specifici de conversie sunt lasati spre implementare subclaselor care il folosesc
-Strategy prin interfata Validator si implementarea acestuia
-Decorator utilizat in lucrul cu fluxurile IO(BufferReader/Writer)