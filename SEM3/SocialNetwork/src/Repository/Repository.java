package Repository;

import Domain.Entity;
import Domain.validators.ValidationException;

/**
 * CRUD operations repository interface.
 * @param <ID> type E must have an attribute of type ID
 * @param <E> type of entities saved in repository
 */
public interface Repository<ID, E extends Entity<ID>> {

    /**
     * Finds the entity with the specified id.
     * @param id the id of the entity to be returned (must not be null)
     * @return the entity with the specified id, or null if there is no entity with the given id
     * @throws IllegalArgumentException if id is null
     */
    E findOne(ID id);

    /**
     * Returns all entities in the repository.
     * @return an iterable containing all entities
     */
    Iterable<E> findAll();

    /**
     * Saves the given entity in the repository.
     * @param entity the entity to be saved (must not be null)
     * @return null if the given entity is saved, otherwise returns the entity (if id already exists)
     * @throws ValidationException if the entity is not valid
     * @throws IllegalArgumentException if the given entity is null
     * @throws RepositoryException if a persistence error occurs
     */
    E save(E entity);

    /**
     * Removes the entity with the specified id.
     * @param id the id of the entity to be removed (must not be null)
     * @return the removed entity or null if there is no entity with the given id
     * @throws IllegalArgumentException if the given id is null
     * @throws RepositoryException if a persistence error occurs
     */
    E delete(ID id);

    /**
     * Updates the given entity.
     * @param entity the entity to be updated (must not be null)
     * @return null if the entity is updated, otherwise returns the entity (e.g. id does not exist)
     * @throws IllegalArgumentException if the given entity is null
     * @throws ValidationException if the entity is not valid
     * @throws RepositoryException if a persistence error occurs
     */
    E update(E entity);
}