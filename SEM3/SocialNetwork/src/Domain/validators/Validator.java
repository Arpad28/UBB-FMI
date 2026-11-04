package Domain.validators;

/**
 * Generic interface for validating entities.
 * @param <T> the type of entity to validate
 */
public interface Validator<T> {
    /**
     * Validates the given entity.
     * @param entity the entity to be validated
     * @throws ValidationException if the entity is not valid
     */
    void validate(T entity);
}