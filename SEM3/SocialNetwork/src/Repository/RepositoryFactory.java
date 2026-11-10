package Repository;

import Domain.Prietenie;
import Domain.Tuple;
import Domain.Utilizator;
import Domain.validators.Validator;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.EnumMap;
import java.util.Map;
import java.util.Optional;
import java.util.Properties;
import java.util.function.Function;

/**
 * Factory class creating Repository instances using a Map of functional creators instead of switch.
 */
public class RepositoryFactory {
    private static RepositoryFactory instance;
    private final Properties properties;
    private final RepositoryType repositoryType;
    private final Map<RepositoryType, Function<Validator<Utilizator>, Repository<Long, Utilizator>>> userRepoCreators;
    private final Map<RepositoryType, Function<Validator<Prietenie>, Repository<Tuple<Long, Long>, Prietenie>>> friendshipRepoCreators;

    private RepositoryFactory() {
        this.properties = loadProperties();
        String typeStr = getRequiredProperty("repository.type");
        try {
            this.repositoryType = RepositoryType.valueOf(typeStr.trim().toUpperCase());
        } catch (IllegalArgumentException e) {
            throw new RepositoryException("Valoare necunoscuta pentru repository.type: " + typeStr, e);
        }

        this.userRepoCreators = new EnumMap<>(RepositoryType.class);
        this.friendshipRepoCreators = new EnumMap<>(RepositoryType.class);
        initCreators();
    }

    /**
     * Initializes the maps associating each RepositoryType with its creation function.
     */
    private void initCreators() {
        // 1. Creatorii pentru UtilizatorRepository (foloseste referinta la constructor InMemoryRepository::new)
        userRepoCreators.put(RepositoryType.MEMORY, InMemoryRepository::new);
        userRepoCreators.put(RepositoryType.FILE, validator ->
                new UtilizatorFileRepository(validator, getRequiredProperty("file.utilizatori")));
        userRepoCreators.put(RepositoryType.DATABASE, validator ->
                new UtilizatorDbRepository(
                        validator,
                        getRequiredProperty("db.url"),
                        getRequiredProperty("db.user"),
                        getRequiredProperty("db.password")
                ));

        // 2. Creatorii pentru PrietenieRepository
        friendshipRepoCreators.put(RepositoryType.MEMORY, InMemoryRepository::new);
        friendshipRepoCreators.put(RepositoryType.FILE, validator ->
                new PrietenieFileRepository(validator, getRequiredProperty("file.prietenii")));
        friendshipRepoCreators.put(RepositoryType.DATABASE, validator ->
                new PrietenieDbRepository(
                        validator,
                        getRequiredProperty("db.url"),
                        getRequiredProperty("db.user"),
                        getRequiredProperty("db.password")
                ));
    }

    /**
     * Returns the singleton instance of the RepositoryFactory.
     * @return the factory instance
     */
    public static RepositoryFactory getInstance() {
        if (instance == null) {
            instance = new RepositoryFactory();
        }
        return instance;
    }

    private Properties loadProperties() {
        Properties props = new Properties();
        Path path1 = Paths.get("src/main/resources/config.properties");
        Path path2 = Paths.get("src/config.properties");

        if (Files.exists(path1)) {
            try (InputStream is = new FileInputStream(path1.toFile())) {
                props.load(is);
                return props;
            } catch (IOException e) {
                throw new RepositoryException("Eroare la citirea config.properties!", e);
            }
        } else if (Files.exists(path2)) {
            try (InputStream is = new FileInputStream(path2.toFile())) {
                props.load(is);
                return props;
            } catch (IOException e) {
                throw new RepositoryException("Eroare la citirea config.properties!", e);
            }
        } else {
            try (InputStream is = RepositoryFactory.class.getClassLoader().getResourceAsStream("config.properties")) {
                if (is == null) {
                    throw new RepositoryException("Fisierul src/main/resources/config.properties nu a fost gasit!");
                }
                props.load(is);
                return props;
            } catch (IOException e) {
                throw new RepositoryException("Eroare la incarcarea config.properties din classpath!", e);
            }
        }
    }

    private String getRequiredProperty(String key) {
        String value = properties.getProperty(key);
        if (value == null || value.trim().isEmpty()) {
            throw new RepositoryException("Proprietatea obligatorie '" + key + "' lipseste din config.properties!");
        }
        return value.trim();
    }

    /**
     * Creates the User Repository using the mapped creator function.
     * @param validator the validator for Utilizator entities
     * @return the configured Repository for Utilizator
     */
    public Repository<Long, Utilizator> createUtilizatorRepository(Validator<Utilizator> validator) {
        return Optional.ofNullable(userRepoCreators.get(repositoryType))
                .orElseThrow(() -> new RepositoryException("Tip de repository nesuportat: " + repositoryType))
                .apply(validator);
    }

    /**
     * Creates the Friendship Repository using the mapped creator function.
     * @param validator the validator for Prietenie entities
     * @return the configured Repository for Prietenie
     */
    public Repository<Tuple<Long, Long>, Prietenie> createPrietenieRepository(Validator<Prietenie> validator) {
        return Optional.ofNullable(friendshipRepoCreators.get(repositoryType))
                .orElseThrow(() -> new RepositoryException("Tip de repository nesuportat: " + repositoryType))
                .apply(validator);
    }
}