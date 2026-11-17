package Domain.validators;

import Domain.Prietenie;

/**
 * Validator implementation for Prietenie entities.
 */
public class PrietenieValidator implements Validator<Prietenie> {

    /**
     * Validates a Prietenie entity.
     * @param entity the friendship to be validated
     * @throws ValidationException if the friendship attributes are invalid
     */
    @Override
    public void validate(Prietenie entity) {
        if (entity == null || entity.getId() == null) {
            throw new ValidationException("Prietenia sau ID-ul nu poate fi null!");
        }

        StringBuilder errors = new StringBuilder();

        Long id1 = entity.getId().getE1();
        Long id2 = entity.getId().getE2();

        if (id1 == null || id2 == null) {
            errors.append("ID-urile utilizatorilor nu pot fi null!\n");
        } else {
            if (id1 <= 0 || id2 <= 0) {
                errors.append("ID-urile utilizatorilor trebuie sa fie numere pozitive!\n");
            }
            if (id1.equals(id2)) {
                errors.append("Un utilizator nu poate fi prieten cu el insusi!\n");
            }
        }

        if (entity.getDate() == null) {
            errors.append("Data prieteniei nu poate fi null!\n");
        }

        if (!errors.isEmpty()) {
            throw new ValidationException(errors.toString().trim());
        }
    }
}