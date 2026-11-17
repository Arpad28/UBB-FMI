package Repository;

import Domain.Utilizator;
import Domain.validators.Validator;

import java.util.List;

public class UtilizatorFileRepository extends AbstractFileRepository<Long, Utilizator> {

    public UtilizatorFileRepository(Validator<Utilizator> validator, String fileName) {
        super(validator, fileName);
        loadData();
    }

    @Override
    public Utilizator extractEntity(List<String> attributes) {
        if (attributes.size() != 3) {
            throw new RepositoryException("Numar invalid de campuri pentru Utilizator (se asteptau 3, s-au gasit " + attributes.size() + ")");
        }
        try {
            Long id = Long.parseLong(attributes.get(0).trim());
            String firstName = attributes.get(1).trim();
            String lastName = attributes.get(2).trim();
            Utilizator u = new Utilizator(firstName, lastName);
            u.setId(id);
            return u;
        } catch (NumberFormatException e) {
            throw new RepositoryException("ID invalid pentru utilizator: " + attributes.get(0), e);
        }
    }

    @Override
    protected String createEntityAsString(Utilizator entity) {
        return entity.getId() + ";" + entity.getFirstName() + ";" + entity.getLastName();
    }
}