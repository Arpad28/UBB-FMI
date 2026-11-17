package Domain.validators;

import java.util.Objects;

/**
 * Functional interface for validating domain entities.
 * @param <T> the type of entity to validate
 */
@FunctionalInterface
public interface Validator<T> {

    /**
     * Validates the given entity.
     * @param entity the entity to be validated
     * @throws ValidationException if the entity is not valid
     */
    void validate(T entity);

    /**
     * Returns a composed validator that first applies this validator to its input,
     * and then applies the {@code other} validator.
     * @param other the validator to apply after this validator is applied
     * @return a composed validator
     * @throws NullPointerException if other is null
     */
    default Validator<T> andThen(Validator<T> other) {
        Objects.requireNonNull(other);
        return entity -> {
            this.validate(entity);
            other.validate(entity);
        };
    }
}