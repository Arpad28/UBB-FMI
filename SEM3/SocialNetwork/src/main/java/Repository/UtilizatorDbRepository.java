package Repository;

import Domain.Utilizator;
import Domain.validators.Validator;
import util.paging.Page;
import util.paging.Pageable;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/**
 * JDBC repository implementation for Utilizator entities persisted in PostgreSQL.
 */
public class UtilizatorDbRepository implements PagingRepository<Long, Utilizator> {
    private final Validator<Utilizator> validator;
    private final String url;
    private final String user;
    private final String password;

    /**
     * Constructs a UtilizatorDbRepository with database connection parameters.
     * @param validator the validator for Utilizator entities
     * @param url the JDBC connection URL
     * @param user the database username
     * @param password the database password
     */
    public UtilizatorDbRepository(Validator<Utilizator> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    /**
     * Extracts a Utilizator entity from the current row of a ResultSet.
     * @param rs the active ResultSet
     * @return the reconstructed Utilizator
     * @throws SQLException if a database access error occurs
     */
    private Utilizator extractUser(ResultSet rs) throws SQLException {
        Long id = rs.getLong("id");
        String firstName = rs.getString("first_name");
        String lastName = rs.getString("last_name");
        Utilizator u = new Utilizator(firstName, lastName);
        u.setId(id);
        return u;
    }

    /**
     * Finds a user by ID in the database.
     * @param id the ID of the user (must not be null)
     * @return an Optional containing the user if found, or empty otherwise
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if a database access error occurs
     */
    @Override
    public Optional<Utilizator> findOne(Long id) {
        if (id == null) {
            throw new IllegalArgumentException("ID-ul nu poate fi null!");
        }
        String sql = "SELECT id, first_name, last_name FROM users WHERE id = ?";
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setLong(1, id);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    return Optional.of(extractUser(rs));
                }
                return Optional.empty();
            }
        } catch (SQLException e) {
            throw new RepositoryException("Eroare DB la cautarea utilizatorului (verificati conexiunea la server): " + e.getMessage(), e);
        }
    }

    /**
     * Retrieves all users from the database.
     * @return an Iterable of all users
     * @throws RepositoryException if a database access error occurs
     */
    @Override
    public Iterable<Utilizator> findAll() {
        List<Utilizator> users = new ArrayList<>();
        String sql = "SELECT id, first_name, last_name FROM users";
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = conn.prepareStatement(sql);
             ResultSet rs = ps.executeQuery()) {
            while (rs.next()) {
                users.add(extractUser(rs));
            }
            return users;
        } catch (SQLException e) {
            throw new RepositoryException("Eroare DB la incarcarea utilizatorilor (verificati conexiunea la server): " + e.getMessage(), e);
        }
    }

    /**
     * Saves a new user in the database and populates its database-generated ID.
     * @param entity the user to save (must not be null)
     * @return Optional.empty() if saved successfully
     * @throws IllegalArgumentException if entity is null
     * @throws Domain.validators.ValidationException if entity is not valid
     * @throws RepositoryException if a database error occurs
     */
    @Override
    public Optional<Utilizator> save(Utilizator entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entitatea nu poate fi null!");
        }
        validator.validate(entity);

        String sql = "INSERT INTO users (first_name, last_name) VALUES (?, ?)";
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            ps.setString(1, entity.getFirstName());
            ps.setString(2, entity.getLastName());
            int affectedRows = ps.executeUpdate();
            if (affectedRows == 0) {
                return Optional.of(entity);
            }
            try (ResultSet generatedKeys = ps.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    entity.setId(generatedKeys.getLong(1));
                }
            }
            return Optional.empty();
        } catch (SQLException e) {
            throw new RepositoryException("Eroare DB la salvarea utilizatorului: " + e.getMessage(), e);
        }
    }

    /**
     * Deletes a user by ID from the database and returns the deleted entity.
     * @param id the ID of the user to delete (must not be null)
     * @return an Optional containing the deleted user, or empty if no user had the given ID
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if a database error occurs
     */
    @Override
    public Optional<Utilizator> delete(Long id) {
        if (id == null) {
            throw new IllegalArgumentException("ID-ul nu poate fi null!");
        }
        Optional<Utilizator> existing = findOne(id);
        if (existing.isEmpty()) {
            return Optional.empty();
        }

        String sql = "DELETE FROM users WHERE id = ?";
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setLong(1, id);
            int affected = ps.executeUpdate();
            return affected > 0 ? existing : Optional.empty();
        } catch (SQLException e) {
            throw new RepositoryException("Eroare DB la stergerea utilizatorului: " + e.getMessage(), e);
        }
    }

    /**
     * Updates an existing user in the database.
     * @param entity the user to update (must not be null and must have a non-null ID)
     * @return Optional.empty() if updated, or Optional.of(entity) if the user ID does not exist
     * @throws IllegalArgumentException if entity or its ID is null
     * @throws Domain.validators.ValidationException if entity is not valid
     * @throws RepositoryException if a database error occurs
     */
    @Override
    public Optional<Utilizator> update(Utilizator entity) {
        if (entity == null || entity.getId() == null) {
            throw new IllegalArgumentException("Entitatea si ID-ul nu pot fi null!");
        }
        validator.validate(entity);

        String sql = "UPDATE users SET first_name = ?, last_name = ? WHERE id = ?";
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setString(1, entity.getFirstName());
            ps.setString(2, entity.getLastName());
            ps.setLong(3, entity.getId());
            int affected = ps.executeUpdate();
            return affected > 0 ? Optional.empty() : Optional.of(entity);
        } catch (SQLException e) {
            throw new RepositoryException("Eroare DB la actualizarea utilizatorului: " + e.getMessage(), e);
        }
    }
    /**
     * Retrieves a page of users from the database using SQL LIMIT and OFFSET,
     * along with the total user count on the same database connection.
     *
     * @param pageable pagination parameters (page number and page size)
     * @return a Page of Utilizator entities
     * @throws IllegalArgumentException if pageable is null
     * @throws RepositoryException      if a database access error occurs
     */
    @Override
    public Page<Utilizator> findAllOnPage(Pageable pageable) {
        if (pageable == null) {
            throw new IllegalArgumentException("Pageable nu poate fi null!");
        }
        List<Utilizator> users = new ArrayList<>();
        String sqlPage = "SELECT id, first_name, last_name FROM users ORDER BY id LIMIT ? OFFSET ?";
        String sqlCount = "SELECT COUNT(*) AS count FROM users";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            try (PreparedStatement ps = connection.prepareStatement(sqlPage)) {
                ps.setInt(1, pageable.getPageSize());
                ps.setInt(2, pageable.getPageNumber() * pageable.getPageSize());
                try (ResultSet rs = ps.executeQuery()) {
                    while (rs.next()) {
                        users.add(extractUser(rs));
                    }
                }
            }

            int totalCount = 0;
            try (PreparedStatement psCount = connection.prepareStatement(sqlCount);
                 ResultSet rsCount = psCount.executeQuery()) {
                if (rsCount.next()) {
                    totalCount = rsCount.getInt("count");
                }
            }

            return new Page<>(users, totalCount);
        } catch (SQLException e) {
            throw new RepositoryException("Eroare la paginarea utilizatorilor: " + e.getMessage(), e);
        }
    }
}