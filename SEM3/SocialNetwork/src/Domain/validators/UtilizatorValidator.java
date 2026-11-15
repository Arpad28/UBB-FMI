package Domain.validators;

import Domain.Utilizator;

/**
 * Validator for Utilizator entities.
 */
public class UtilizatorValidator implements Validator<Utilizator> {

    /**
     * Validates a user entity. ID may be null before persistence generation,
     * but if present, it must be strictly positive.
     * @param entity the user to validate
     * @throws ValidationException if first name, last name, or non-null ID is invalid
     */
    @Override
    public void validate(Utilizator entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entitatea Utilizator nu poate fi null!");
        }
        StringBuilder errors = new StringBuilder();

        if (entity.getId() != null && entity.getId() <= 0) {
            errors.append("ID-ul utilizatorului trebuie sa fie un numar strict pozitiv!\n");
        }
        if (entity.getFirstName() == null || entity.getFirstName().trim().isEmpty()) {
            errors.append("Prenumele nu poate fi vid!\n");
        }
        if (entity.getLastName() == null || entity.getLastName().trim().isEmpty()) {
            errors.append("Numele de familie nu poate fi vid!\n");
        }

        if (errors.length() > 0) {
            throw new ValidationException(errors.toString().trim());
        }
    }
}