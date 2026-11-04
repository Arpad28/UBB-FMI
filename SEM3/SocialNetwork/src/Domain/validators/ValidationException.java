package Domain.validators;

/**
 * Unchecked exception thrown when an entity fails validation.
 */
public class ValidationException extends RuntimeException {
    public ValidationException(String message) {
        super(message);
    }

    public ValidationException(String message, Throwable cause) {
        super(message, cause);
    }
}