package Repository;

import Domain.Utilizator;
import Domain.validators.Validator;

public class UtilizatorDbRepository implements Repository<Long, Utilizator> {
    private final Validator<Utilizator> validator;
    private final String url;
    private final String user;
    private final String password;

    public UtilizatorDbRepository(Validator<Utilizator> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    @Override
    public Utilizator findOne(Long id) {
        throw new UnsupportedOperationException("Persistența DB va fi implementată în Laboratorul 4.");
    }

    @Override
    public Iterable<Utilizator> findAll() {
        throw new UnsupportedOperationException("Persistența DB va fi implementată în Laboratorul 4.");
    }

    @Override
    public Utilizator save(Utilizator entity) {
        throw new UnsupportedOperationException("Persistența DB va fi implementată în Laboratorul 4.");
    }

    @Override
    public Utilizator delete(Long id) {
        throw new UnsupportedOperationException("Persistența DB va fi implementată în Laboratorul 4.");
    }

    @Override
    public Utilizator update(Utilizator entity) {
        throw new UnsupportedOperationException("Persistența DB va fi implementată în Laboratorul 4.");
    }
}