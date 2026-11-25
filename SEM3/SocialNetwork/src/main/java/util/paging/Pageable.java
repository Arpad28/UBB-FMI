package util.paging;

/**
 * Represents pagination information (page number and page size).
 */
public class Pageable {
    private final int pageNumber;
    private final int pageSize;

    /**
     * Constructs a new Pageable instance.
     *
     * @param pageNumber the zero-based page index (must be >= 0)
     * @param pageSize   the number of elements per page (must be > 0)
     * @throws IllegalArgumentException if pageNumber < 0 or pageSize <= 0
     */
    public Pageable(int pageNumber, int pageSize) {
        if (pageNumber < 0) {
            throw new IllegalArgumentException("Page number must be non-negative.");
        }
        if (pageSize <= 0) {
            throw new IllegalArgumentException("Page size must be strictly positive.");
        }
        this.pageNumber = pageNumber;
        this.pageSize = pageSize;
    }

    /**
     * @return the zero-based page number
     */
    public int getPageNumber() {
        return pageNumber;
    }

    /**
     * @return the maximum number of elements on a page
     */
    public int getPageSize() {
        return pageSize;
    }
}