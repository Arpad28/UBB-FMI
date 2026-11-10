package Repository;

import Domain.Prietenie;
import Domain.Tuple;
import Domain.validators.Validator;

import java.util.Optional;

/**
 * Skeleton database repository for Prietenie entities (to be implemented in Lab 5).
 */
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
    public Optional<Prietenie> findOne(Tuple<Long, Long> id) {
        throw new UnsupportedOperationException("Persistenta DB va fi implementata in Laboratorul 5.");
    }

    @Override
    public Iterable<Prietenie> findAll() {
        throw new UnsupportedOperationException("Persistenta DB va fi implementata in Laboratorul 5.");
    }

    @Override
    public Optional<Prietenie> save(Prietenie entity) {
        throw new UnsupportedOperationException("Persistenta DB va fi implementata in Laboratorul 5.");
    }

    @Override
    public Optional<Prietenie> delete(Tuple<Long, Long> id) {
        throw new UnsupportedOperationException("Persistenta DB va fi implementata in Laboratorul 5.");
    }

    @Override
    public Optional<Prietenie> update(Prietenie entity) {
        throw new UnsupportedOperationException("Persistenta DB va fi implementata in Laboratorul 5.");
    }
}