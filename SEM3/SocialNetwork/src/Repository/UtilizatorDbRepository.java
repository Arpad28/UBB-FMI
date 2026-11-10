package Repository;

import Domain.Utilizator;
import Domain.validators.Validator;

import java.util.Optional;

/**
 * Skeleton database repository for Utilizator entities (to be implemented in Lab 5).
 */
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
    public Optional<Utilizator> findOne(Long id) {
        throw new UnsupportedOperationException("Persistenta DB va fi implementata in Laboratorul 5.");
    }

    @Override
    public Iterable<Utilizator> findAll() {
        throw new UnsupportedOperationException("Persistenta DB va fi implementata in Laboratorul 5.");
    }

    @Override
    public Optional<Utilizator> save(Utilizator entity) {
        throw new UnsupportedOperationException("Persistenta DB va fi implementata in Laboratorul 5.");
    }

    @Override
    public Optional<Utilizator> delete(Long id) {
        throw new UnsupportedOperationException("Persistenta DB va fi implementata in Laboratorul 5.");
    }

    @Override
    public Optional<Utilizator> update(Utilizator entity) {
        throw new UnsupportedOperationException("Persistenta DB va fi implementata in Laboratorul 5.");
    }
}