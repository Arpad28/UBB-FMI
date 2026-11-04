package Domain;

/**
 * Represents a user in the social network.
 */
public class Utilizator extends Entity<Long> {
    private String firstName;
    private String lastName;

    public Utilizator(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    @Override
    public String toString() {
        return "Utilizator{id=" + getId() + ", firstName='" + firstName + "', lastName='" + lastName + "'}";
    }
}