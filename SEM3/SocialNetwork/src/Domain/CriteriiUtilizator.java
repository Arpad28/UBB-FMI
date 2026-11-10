package Domain;

import java.util.function.Predicate;

/**
 * Utility class providing static search criteria (Predicates) for Utilizator entities.
 */
public final class CriteriiUtilizator {

    private CriteriiUtilizator() {
    }

    /**
     * Returns a predicate testing if a user has the specified last name (case-insensitive).
     * @param lastName the last name to match
     * @return a predicate for filtering users by last name
     */
    public static Predicate<Utilizator> areNumele(String lastName) {
        return u -> u.getLastName() != null && u.getLastName().equalsIgnoreCase(lastName);
    }

    /**
     * Returns a predicate testing if a user's first name starts with a given prefix.
     * @param prefix the prefix to check
     * @return a predicate for filtering users by first name prefix
     */
    public static Predicate<Utilizator> prenumeIncepeCu(String prefix) {
        return u -> u.getFirstName() != null && u.getFirstName().toLowerCase().startsWith(prefix.toLowerCase());
    }

    /**
     * Static method checking if a user has an even ID (used as a static method reference).
     * @param u the user to test
     * @return true if the user's ID is even, false otherwise
     */
    public static boolean areIdPar(Utilizator u) {
        return u != null && u.getId() != null && u.getId() % 2 == 0;
    }
}