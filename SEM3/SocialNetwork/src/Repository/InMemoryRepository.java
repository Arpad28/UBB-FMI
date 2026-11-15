package Repository;

import Domain.Entity;
import Domain.validators.Validator;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

/**
 * In-memory implementation of the Repository interface with automatic Long ID generation support.
 * @param <ID> the type of entity ID
 * @param <E> the type of entity
 */
public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    protected final Validator<E> validator;
    protected final Map<ID, E> entities;

    /**
     * Constructs an InMemoryRepository with the given validator.
     * @param validator the validator used to validate entities
     */
    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
        this.entities = new HashMap<>();
    }

    @Override
    public Optional<E> findOne(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("ID-ul nu poate fi null!");
        }
        return Optional.ofNullable(entities.get(id));
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    @Override
    @SuppressWarnings("unchecked")
    public Optional<E> save(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entitatea nu poate fi null!");
        }
        validator.validate(entity);

        if (entity.getId() == null) {
            Long nextId = entities.keySet().stream()
                    .filter(Long.class::isInstance)
                    .map(Long.class::cast)
                    .mapToLong(Long::longValue)
                    .max()
                    .orElse(0L) + 1L;
            entity.setId((ID) nextId);
        }

        return Optional.ofNullable(entities.putIfAbsent(entity.getId(), entity));
    }

    @Override
    public Optional<E> delete(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("ID-ul nu poate fi null!");
        }
        return Optional.ofNullable(entities.remove(id));
    }

    @Override
    public Optional<E> update(E entity) {
        if (entity == null || entity.getId() == null) {
            throw new IllegalArgumentException("Entitatea si ID-ul nu pot fi null!");
        }
        validator.validate(entity);
        if (!entities.containsKey(entity.getId())) {
            return Optional.of(entity);
        }
        entities.put(entity.getId(), entity);
        return Optional.empty();
    }
}