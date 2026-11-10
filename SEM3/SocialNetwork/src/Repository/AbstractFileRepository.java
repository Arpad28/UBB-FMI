package Repository;

import Domain.Entity;
import Domain.validators.ValidationException;
import Domain.validators.Validator;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

/**
 * Abstract generic file repository implementing the Template Method pattern with Java 8 Streams.
 * @param <ID> the type of entity ID
 * @param <E> the type of entity
 */
public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {
    protected final String fileName;

    /**
     * Constructs an AbstractFileRepository with the specified validator and file name.
     * @param validator the validator for entities
     * @param fileName the relative path to the file
     */
    public AbstractFileRepository(Validator<E> validator, String fileName) {
        super(validator);
        this.fileName = fileName;
    }

    /**
     * Extracts an entity from a list of string attributes (Template Method step).
     * @param attributes the parsed CSV attributes
     * @return the reconstructed entity
     */
    public abstract E extractEntity(List<String> attributes);

    /**
     * Converts an entity into its string representation for file storage (Template Method step).
     * @param entity the entity to convert
     * @return the CSV line representation
     */
    protected abstract String createEntityAsString(E entity);

    /**
     * Loads data from file using Files.lines and IntStream (no classic loops).
     */
    protected void loadData() {
        Path path = Paths.get(fileName);
        if (!Files.exists(path)) {
            return;
        }

        List<String> lines;
        try (Stream<String> stream = Files.lines(path, StandardCharsets.UTF_8)) {
            lines = stream.collect(Collectors.toList());
        } catch (IOException e) {
            throw new RepositoryException("Eroare la citirea fisierului: " + fileName, e);
        }

        IntStream.range(0, lines.size())
                .forEach(i -> {
                    String line = lines.get(i);
                    if (!line.trim().isEmpty()) {
                        try {
                            List<String> attr = Arrays.asList(line.split(";", -1));
                            E entity = extractEntity(attr);
                            super.save(entity);
                        } catch (RepositoryException | ValidationException | IllegalArgumentException e) {
                            System.err.println("Linie corupta sau invalida in [" + fileName + "] la linia " + (i + 1) + ": " + e.getMessage());
                        }
                    }
                });
    }

    /**
     * Writes all entities to the file using Stream API and Files.write.
     */
    protected void writeToFile() {
        Path path = Paths.get(fileName);
        try {
            if (path.getParent() != null && !Files.exists(path.getParent())) {
                Files.createDirectories(path.getParent());
            }
            List<String> lines = StreamSupport.stream(findAll().spliterator(), false)
                    .map(this::createEntityAsString)
                    .collect(Collectors.toList());
            Files.write(path, lines, StandardCharsets.UTF_8);
        } catch (IOException e) {
            throw new RepositoryException("Eroare la scrierea in fisierul: " + fileName, e);
        }
    }

    @Override
    public Optional<E> save(E entity) {
        Optional<E> result = super.save(entity);
        if (result.isEmpty()) {
            writeToFile();
        }
        return result;
    }

    @Override
    public Optional<E> delete(ID id) {
        Optional<E> result = super.delete(id);
        if (result.isPresent()) {
            writeToFile();
        }
        return result;
    }

    @Override
    public Optional<E> update(E entity) {
        Optional<E> result = super.update(entity);
        if (result.isEmpty()) {
            writeToFile();
        }
        return result;
    }
}