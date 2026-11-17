package Repository;

import Domain.Entity;
import Domain.validators.ValidationException;

import java.util.List;
import java.util.Optional;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

/**
 * CRUD operations repository interface using Optional and Predicate filtering.
 * @param <ID> type E must have an attribute of type ID
 * @param <E> type of entities saved in repository
 */
public interface Repository<ID, E extends Entity<ID>> {

    /**
     * Finds the entity with the specified id.
     * @param id the id of the entity to be returned (must not be null)
     * @return an {@code Optional} encapsulating the entity with the given id, or empty if not found
     * @throws IllegalArgumentException if id is null
     */
    Optional<E> findOne(ID id);

    /**
     * Returns all entities in the repository.
     * @return an iterable containing all entities
     */
    Iterable<E> findAll();

    /**
     * Returns all entities matching the given filter predicate.
     * @param filter the predicate used to filter entities (must not be null)
     * @return a list of entities matching the predicate
     */
    default List<E> findAll(Predicate<E> filter) {
        return StreamSupport.stream(findAll().spliterator(), false)
                .filter(filter)
                .collect(Collectors.toList());
    }

    /**
     * Saves the given entity in the repository.
     * @param entity the entity to be saved (must not be null)
     * @return an {@code Optional} empty if the entity was saved, or containing the entity if id already exists
     * @throws ValidationException if the entity is not valid
     * @throws IllegalArgumentException if the given entity is null
     * @throws RepositoryException if a persistence error occurs
     */
    Optional<E> save(E entity);

    /**
     * Removes the entity with the specified id.
     * @param id the id of the entity to be removed (must not be null)
     * @return an {@code Optional} containing the removed entity, or empty if no entity was found
     * @throws IllegalArgumentException if the given id is null
     * @throws RepositoryException if a persistence error occurs
     */
    Optional<E> delete(ID id);

    /**
     * Updates the given entity.
     * @param entity the entity to be updated (must not be null)
     * @return an {@code Optional} empty if the entity was updated, or containing the entity if id does not exist
     * @throws IllegalArgumentException if the given entity is null
     * @throws ValidationException if the entity is not valid
     * @throws RepositoryException if a persistence error occurs
     */
    Optional<E> update(E entity);
}