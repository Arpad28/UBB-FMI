package Repository;

import Domain.Prietenie;
import Domain.Tuple;
import Domain.validators.Validator;

public class PrietenieDbRepository implements Repository<Tuple<Long, Long>, Prietenie> {
    private final Validator<Prietenie> validator;
    private final String url;
    private final String user;
    private final String password;

    public PrietenieDbRepository(Validator<Prietenie> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    @Override
    public Prietenie findOne(Tuple<Long, Long> id) {
        throw new UnsupportedOperationException("Persistența DB va fi implementată în Laboratorul 4.");
    }

    @Override
    public Iterable<Prietenie> findAll() {
        throw new UnsupportedOperationException("Persistența DB va fi implementată în Laboratorul 4.");
    }

    @Override
    public Prietenie save(Prietenie entity) {
        throw new UnsupportedOperationException("Persistența DB va fi implementată în Laboratorul 4.");
    }

    @Override
    public Prietenie delete(Tuple<Long, Long> id) {
        throw new UnsupportedOperationException("Persistența DB va fi implementată în Laboratorul 4.");
    }

    @Override
    public Prietenie update(Prietenie entity) {
        throw new UnsupportedOperationException("Persistența DB va fi implementată în Laboratorul 4.");
    }
}