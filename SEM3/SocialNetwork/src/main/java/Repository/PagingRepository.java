package Repository;

import Domain.Entity;
import util.paging.Page;
import util.paging.Pageable;

/**
 * Extension of Repository that supports paginated queries.
 *
 * @param <ID> the type of the entity identifier
 * @param <E>  the type of the entity
 */
public interface PagingRepository<ID, E extends Entity<ID>> extends Repository<ID, E> {

    /**
     * Retrieves a page of entities based on the given pagination parameters.
     *
     * @param pageable pagination parameters (page number and page size)
     * @return a Page containing the requested slice of entities and the total element count
     */
    Page<E> findAllOnPage(Pageable pageable);
}