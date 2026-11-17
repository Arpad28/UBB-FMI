package Repository;

import Domain.Prietenie;
import Domain.Tuple;
import Domain.validators.Validator;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.List;

public class PrietenieFileRepository extends AbstractFileRepository<Tuple<Long, Long>, Prietenie> {
    private static final DateTimeFormatter FORMATTER = DateTimeFormatter.ISO_LOCAL_DATE_TIME;

    public PrietenieFileRepository(Validator<Prietenie> validator, String fileName) {
        super(validator, fileName);
        loadData();
    }

    @Override
    public Prietenie extractEntity(List<String> attributes) {
        if (attributes.size() != 3) {
            throw new RepositoryException("Numar invalid de campuri pentru Prietenie (se asteptau 3, s-au gasit " + attributes.size() + ")");
        }
        try {
            Long id1 = Long.parseLong(attributes.get(0).trim());
            Long id2 = Long.parseLong(attributes.get(1).trim());
            LocalDateTime date = LocalDateTime.parse(attributes.get(2).trim(), FORMATTER);
            return new Prietenie(id1, id2, date);
        } catch (NumberFormatException e) {
            throw new RepositoryException("ID numeric invalid intr-o relatie de prietenie", e);
        } catch (DateTimeParseException e) {
            throw new RepositoryException("Format data invalid (se asteapta format ISO): " + attributes.get(2), e);
        }
    }

    @Override
    protected String createEntityAsString(Prietenie entity) {
        return entity.getId().getE1() + ";" + entity.getId().getE2() + ";" + entity.getDate().format(FORMATTER);
    }
}