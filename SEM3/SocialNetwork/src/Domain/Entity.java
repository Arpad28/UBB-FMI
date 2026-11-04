package Domain;

import java.util.Objects;

/**
 * Base class for all domain entities.
 * @param <ID> the type of the entity identifier
 */
public class Entity<ID> {
    private ID id;

    /**
     * Returns the identifier of the entity.
     * @return the entity ID
     */
    public ID getId() {
        return id;
    }

    /**
     * Sets the identifier of the entity.
     * @param id the new entity ID
     */
    public void setId(ID id) {
        this.id = id;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Entity<?> entity = (Entity<?>) o;
        return Objects.equals(id, entity.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}