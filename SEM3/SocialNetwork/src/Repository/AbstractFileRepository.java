package Repository;

import Domain.Entity;
import Domain.validators.ValidationException;
import Domain.validators.Validator;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;

/**
 * Abstract repository that persists entities in a text file using the Template Method pattern.
 * @param <ID> the type of entity ID
 * @param <E> the type of entity
 */
public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {
    protected final String fileName;

    public AbstractFileRepository(Validator<E> validator, String fileName) {
        super(validator);
        this.fileName = fileName;
    }

    /**
     * Extracts an entity from a list of string attributes representing a CSV line.
     * @param attributes the list of string tokens
     * @return the reconstructed entity
     * @throws RepositoryException if parsing fails
     */
    public abstract E extractEntity(List<String> attributes);

    /**
     * Converts an entity into its string representation for file storage.
     * @param entity the entity to convert
     * @return a semicolon-separated string
     */
    protected abstract String createEntityAsString(E entity);

    /**
     * Loads data from the file into memory.
     * If the file does not exist, the repository starts empty.
     * Corrupted or invalid lines are reported with their line number and ignored.
     */
    protected void loadData() {
        Path path = Paths.get(fileName);
        if (!Files.exists(path)) {
            return; // Porneste cu repository-ul gol; fisierul se va crea la prima salvare
        }

        int lineNumber = 0;
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(fileName), StandardCharsets.UTF_8))) {
            String line;
            while ((line = br.readLine()) != null) {
                lineNumber++;
                if (line.trim().isEmpty()) {
                    continue;
                }
                try {
                    List<String> attr = Arrays.asList(line.split(";", -1));
                    E entity = extractEntity(attr);
                    super.save(entity);
                } catch (RepositoryException | ValidationException | IllegalArgumentException e) {
                    System.err.println("Linie corupta sau invalida in [" + fileName + "] la linia " + lineNumber + ": " + e.getMessage());
                }
            }
        } catch (IOException e) {
            throw new RepositoryException("Eroare la citirea fisierului: " + fileName, e);
        }
    }

    protected void writeToFile() {
        Path path = Paths.get(fileName);
        try {
            if (path.getParent() != null && !Files.exists(path.getParent())) {
                Files.createDirectories(path.getParent());
            }
            try (BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(fileName), StandardCharsets.UTF_8))) {
                for (E entity : findAll()) {
                    bw.write(createEntityAsString(entity));
                    bw.newLine();
                }
            }
        } catch (IOException e) {
            throw new RepositoryException("Eroare la scrierea in fisierul: " + fileName, e);
        }
    }

    @Override
    public E save(E entity) {
        E result = super.save(entity);
        if (result == null) {
            writeToFile();
        }
        return result;
    }

    @Override
    public E delete(ID id) {
        E result = super.delete(id);
        if (result != null) {
            writeToFile();
        }
        return result;
    }

    @Override
    public E update(E entity) {
        E result = super.update(entity);
        if (result == null) {
            writeToFile();
        }
        return result;
    }
}