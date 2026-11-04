package Repository;

import Domain.Entity;
import Domain.validators.Validator;

import java.util.HashMap;
import java.util.Map;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    protected final Validator<E> validator;
    protected final Map<ID, E> entities;

    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
        this.entities = new HashMap<>();
    }

    @Override
    public E findOne(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("ID-ul nu poate fi null!");
        }
        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    @Override
    public E save(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entitatea nu poate fi null!");
        }
        validator.validate(entity);
        if (entities.containsKey(entity.getId())) {
            return entity;
        }
        entities.put(entity.getId(), entity);
        return null;
    }

    @Override
    public E delete(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("ID-ul nu poate fi null!");
        }
        return entities.remove(id);
    }

    @Override
    public E update(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entitatea nu poate fi null!");
        }
        validator.validate(entity);
        if (!entities.containsKey(entity.getId())) {
            return entity;
        }
        entities.put(entity.getId(), entity);
        return null;
    }
}