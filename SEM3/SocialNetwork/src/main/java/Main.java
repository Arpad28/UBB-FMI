import Domain.Prietenie;
import Domain.Tuple;
import Domain.Utilizator;
import Domain.validators.PrietenieValidator;
import Domain.validators.UtilizatorValidator;
import Domain.validators.ValidationException;
import Domain.validators.Validator;
import Repository.Repository;
import Repository.RepositoryException;
import Repository.RepositoryFactory;
import Service.ReteaService;
import UI.ConsoleUI;

public class Main {
    public static void main(String[] args) {
        try {
            Validator<Utilizator> userValidator = new UtilizatorValidator()
                    .andThen(u -> {
                        if (u.getFirstName().length() < 2 || u.getLastName().length() < 2) {
                            throw new ValidationException("Numele si prenumele trebuie sa aiba cel putin 2 caractere!");
                        }
                    });

            Validator<Prietenie> prietenieValidator = new PrietenieValidator();

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