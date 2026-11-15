package Repository;

import Domain.Prietenie;
import Domain.Tuple;
import Domain.validators.Validator;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/**
 * JDBC repository implementation for Prietenie entities persisted in PostgreSQL.
 */
public class PrietenieDbRepository implements Repository<Tuple<Long, Long>, Prietenie> {
    private final Validator<Prietenie> validator;
    private final String url;
    private final String user;
    private final String password;

    /**
     * Constructs a PrietenieDbRepository with database connection parameters.
     * @param validator the validator for Prietenie entities
     * @param url the JDBC connection URL
     * @param user the database username
     * @param password the database password
     */
    public PrietenieDbRepository(Validator<Prietenie> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    /**
     * Extracts a Prietenie entity from the current row of a ResultSet.
     * @param rs the active ResultSet
     * @return the reconstructed Prietenie
     * @throws SQLException if a database access error occurs
     */
    private Prietenie extractFriendship(ResultSet rs) throws SQLException {
        Long id1 = rs.getLong("id1");
        Long id2 = rs.getLong("id2");
        LocalDateTime date = rs.getTimestamp("friends_from").toLocalDateTime();
        return new Prietenie(id1, id2, date);
    }

    /**
     * Normalizes a pair of IDs so that the smaller ID is always first (matching CHECK (id1 < id2)).
     * @param id the original tuple
     * @return a normalized tuple with e1 <= e2
     */
    private Tuple<Long, Long> normalizeId(Tuple<Long, Long> id) {
        if (id == null || id.getE1() == null || id.getE2() == null) {
            throw new IllegalArgumentException("ID-ul prieteniei nu poate fi null!");
        }
        Long min = Math.min(id.getE1(), id.getE2());
        Long max = Math.max(id.getE1(), id.getE2());
        return new Tuple<>(min, max);
    }

    /**
     * Finds a friendship by its composite ID.
     * @param id the composite ID (must not be null)
     * @return an Optional containing the friendship if found, or empty otherwise
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if a database access error occurs
     */
    @Override
    public Optional<Prietenie> findOne(Tuple<Long, Long> id) {
        Tuple<Long, Long> norm = normalizeId(id);
        String sql = "SELECT id1, id2, friends_from FROM friendships WHERE id1 = ? AND id2 = ?";
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setLong(1, norm.getE1());
            ps.setLong(2, norm.getE2());
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    return Optional.of(extractFriendship(rs));
                }
                return Optional.empty();
            }
        } catch (SQLException e) {
            throw new RepositoryException("Eroare DB la cautarea prieteniei: " + e.getMessage(), e);
        }
    }

    /**
     * Retrieves all friendships from the database.
     * @return an Iterable of all friendships
     * @throws RepositoryException if a database access error occurs
     */
    @Override
    public Iterable<Prietenie> findAll() {
        List<Prietenie> list = new ArrayList<>();
        String sql = "SELECT id1, id2, friends_from FROM friendships";
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = conn.prepareStatement(sql);
             ResultSet rs = ps.executeQuery()) {
            while (rs.next()) {
                list.add(extractFriendship(rs));
            }
            return list;
        } catch (SQLException e) {
            throw new RepositoryException("Eroare DB la incarcarea prieteniilor: " + e.getMessage(), e);
        }
    }

    /**
     * Saves a new friendship in the database.
     * @param entity the friendship to save (must not be null)
     * @return Optional.empty() if saved, or Optional.of(entity) if the friendship already exists
     * @throws IllegalArgumentException if entity is null
     * @throws Domain.validators.ValidationException if entity is invalid
     * @throws RepositoryException if a database constraint or connection error occurs
     */
    @Override
    public Optional<Prietenie> save(Prietenie entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entitatea Prietenie nu poate fi null!");
        }
        validator.validate(entity);

        if (findOne(entity.getId()).isPresent()) {
            return Optional.of(entity);
        }

        String sql = "INSERT INTO friendships (id1, id2, friends_from) VALUES (?, ?, ?)";
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setLong(1, entity.getId().getE1());
            ps.setLong(2, entity.getId().getE2());
            ps.setTimestamp(3, Timestamp.valueOf(entity.getDate()));
            ps.executeUpdate();
            return Optional.empty();
        } catch (SQLException e) {
            throw new RepositoryException("Eroare DB la salvarea prieteniei (verificati constrangerile): " + e.getMessage(), e);
        }
    }

    /**
     * Deletes a friendship from the database and returns the removed entity.
     * @param id the composite ID of the friendship to remove (must not be null)
     * @return an Optional containing the deleted friendship, or empty if not found
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if a database error occurs
     */
    @Override
    public Optional<Prietenie> delete(Tuple<Long, Long> id) {
        Tuple<Long, Long> norm = normalizeId(id);
        Optional<Prietenie> existing = findOne(norm);
        if (existing.isEmpty()) {
            return Optional.empty();
        }

        String sql = "DELETE FROM friendships WHERE id1 = ? AND id2 = ?";
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setLong(1, norm.getE1());
            ps.setLong(2, norm.getE2());
            int affected = ps.executeUpdate();
            return affected > 0 ? existing : Optional.empty();
        } catch (SQLException e) {
            throw new RepositoryException("Eroare DB la stergerea prieteniei: " + e.getMessage(), e);
        }
    }

    /**
     * Updates the timestamp of an existing friendship in the database.
     * @param entity the friendship to update (must not be null)
     * @return Optional.empty() if updated, or Optional.of(entity) if the friendship does not exist
     * @throws IllegalArgumentException if entity is null
     * @throws Domain.validators.ValidationException if entity is invalid
     * @throws RepositoryException if a database error occurs
     */
    @Override
    public Optional<Prietenie> update(Prietenie entity) {
        if (entity == null || entity.getId() == null) {
            throw new IllegalArgumentException("Entitatea Prietenie si ID-ul nu pot fi null!");
        }
        validator.validate(entity);

        String sql = "UPDATE friendships SET friends_from = ? WHERE id1 = ? AND id2 = ?";
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setTimestamp(1, Timestamp.valueOf(entity.getDate()));
            ps.setLong(2, entity.getId().getE1());
            ps.setLong(3, entity.getId().getE2());
            int affected = ps.executeUpdate();
            return affected > 0 ? Optional.empty() : Optional.of(entity);
        } catch (SQLException e) {
            throw new RepositoryException("Eroare DB la actualizarea prieteniei: " + e.getMessage(), e);
        }
    }
}