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
import java.util.Properties;

/**
 * Factory class responsible for creating Repository instances based on configuration.
 */
public class RepositoryFactory {
    private static RepositoryFactory instance;
    private final Properties properties;
    private final RepositoryType repositoryType;

    private RepositoryFactory() {
        this.properties = loadProperties();
        String typeStr = getRequiredProperty("repository.type");
        try {
            this.repositoryType = RepositoryType.valueOf(typeStr.trim().toUpperCase());
        } catch (IllegalArgumentException e) {
            throw new RepositoryException("Valoare necunoscuta pentru repository.type: " + typeStr, e);
        }
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
            try (InputStream is = RepositoryFactory.class.getClassLoader().getResourceAsStream("main/resources/config.properties")) {
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
     * Creates the User Repository according to the configured persistence type.
     * @param validator the validator for Utilizator entities
     * @return the configured Repository for Utilizator
     */
    public Repository<Long, Utilizator> createUtilizatorRepository(Validator<Utilizator> validator) {
        switch (repositoryType) {
            case MEMORY:
                return new InMemoryRepository<>(validator);
            case FILE:
                String userFile = getRequiredProperty("file.utilizatori");
                return new UtilizatorFileRepository(validator, userFile);
            case DATABASE:
                String url = getRequiredProperty("db.url");
                String user = getRequiredProperty("db.user");
                String password = getRequiredProperty("db.password");
                return new UtilizatorDbRepository(validator, url, user, password);
            default:
                throw new RepositoryException("Tip de repository nesuportat: " + repositoryType);
        }
    }

    /**
     * Creates the Friendship Repository according to the configured persistence type.
     * @param validator the validator for Prietenie entities
     * @return the configured Repository for Prietenie
     */
    public Repository<Tuple<Long, Long>, Prietenie> createPrietenieRepository(Validator<Prietenie> validator) {
        switch (repositoryType) {
            case MEMORY:
                return new InMemoryRepository<>(validator);
            case FILE:
                String friendFile = getRequiredProperty("file.prietenii");
                return new PrietenieFileRepository(validator, friendFile);
            case DATABASE:
                String url = getRequiredProperty("db.url");
                String user = getRequiredProperty("db.user");
                String password = getRequiredProperty("db.password");
                return new PrietenieDbRepository(validator, url, user, password);
            default:
                throw new RepositoryException("Tip de repository nesuportat: " + repositoryType);
        }
    }
}