import Domain.Prietenie;
import Domain.Tuple;
import Domain.Utilizator;
import Domain.validators.PrietenieValidator;
import Domain.validators.UtilizatorValidator;
import Repository.Repository;
import Repository.RepositoryException;
import Repository.RepositoryFactory;
import Service.ReteaService;
import UI.ConsoleUI;

public class Main {
    public static void main(String[] args) {
        try {
            UtilizatorValidator userValidator = new UtilizatorValidator();
            PrietenieValidator prietenieValidator = new PrietenieValidator();

            RepositoryFactory factory = RepositoryFactory.getInstance();
            Repository<Long, Utilizator> repoUtilizatori = factory.createUtilizatorRepository(userValidator);
            Repository<Tuple<Long, Long>, Prietenie> repoPrietenii = factory.createPrietenieRepository(prietenieValidator);

            ReteaService service = new ReteaService(repoUtilizatori, repoPrietenii);
            ConsoleUI ui = new ConsoleUI(service);
            ui.run();
        } catch (RepositoryException e) {
            System.err.println("Eroare critica la initializarea aplicatiei: " + e.getMessage());
        }
    }
}