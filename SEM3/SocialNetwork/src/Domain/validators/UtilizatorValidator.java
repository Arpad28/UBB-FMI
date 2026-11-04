package Domain.validators;

import Domain.Utilizator;

/**
 * Validator implementation for Utilizator entities.
 */
public class UtilizatorValidator implements Validator<Utilizator> {

    /**
     * Validates a Utilizator entity.
     * @param entity the user to be validated
     * @throws ValidationException if the user attributes are invalid
     */
    @Override
    public void validate(Utilizator entity) {
        if (entity == null) {
            throw new ValidationException("Entitatea nu poate fi null!");
        }

        StringBuilder errors = new StringBuilder();

        if (entity.getId() == null || entity.getId() <= 0) {
            errors.append("ID-ul trebuie sa fie un numar pozitiv!\n");
        }

        if (entity.getFirstName() == null || entity.getFirstName().trim().isEmpty()) {
            errors.append("Prenumele nu poate fi gol!\n");
        }

        if (entity.getLastName() == null || entity.getLastName().trim().isEmpty()) {
            errors.append("Numele nu poate fi gol!\n");
        }

        if (!errors.isEmpty()) {
            throw new ValidationException(errors.toString().trim());
        }
    }
}