package Domain;

import java.util.Objects;

/**
 * Generic class that represents a pair of two objects.
 * @param <E1> the type of the first element
 * @param <E2> the type of the second element
 */
public class Tuple<E1, E2> {
    private final E1 e1;
    private final E2 e2;

    public Tuple(E1 e1, E2 e2) {
        this.e1 = e1;
        this.e2 = e2;
    }

    public E1 getE1() {
        return e1;
    }

    public E2 getE2() {
        return e2;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Tuple<?, ?> that = (Tuple<?, ?>) obj;
        return Objects.equals(e1, that.e1) && Objects.equals(e2, that.e2);
    }

    @Override
    public int hashCode() {
        return Objects.hash(e1, e2);
    }

    @Override
    public String toString() {
        return "(" + e1 + "," + e2 + ")";
    }
}