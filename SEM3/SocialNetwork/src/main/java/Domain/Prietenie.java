package Domain;

import java.time.LocalDateTime;

/**
 * Represents a friendship relation between two users.
 */
public class Prietenie extends Entity<Tuple<Long, Long>> {
    private final LocalDateTime date;

    public Prietenie(Long idUser1, Long idUser2) {
        this(Math.min(idUser1, idUser2), Math.max(idUser1, idUser2), LocalDateTime.now());
    }

    public Prietenie(Long idUser1, Long idUser2, LocalDateTime date) {
        if (idUser1 != null && idUser2 != null) {
            Long min = Math.min(idUser1, idUser2);
            Long max = Math.max(idUser1, idUser2);
            this.setId(new Tuple<>(min, max));
        } else {
            this.setId(new Tuple<>(idUser1, idUser2));
        }
        this.date = date;
    }

    public LocalDateTime getDate() {
        return date;
    }

    @Override
    public String toString() {
        return "Prietenie{idUser1=" + getId().getE1() + ", idUser2=" + getId().getE2() + ", date=" + date + "}";
    }
}