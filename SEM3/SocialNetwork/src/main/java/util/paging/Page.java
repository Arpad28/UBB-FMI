package util.paging;

/**
 * Represents a single page of elements along with the total count of available elements.
 *
 * @param <E> the type of elements on the page
 */
public class Page<E> {
    private final Iterable<E> elementsOnPage;
    private final int totalNumberOfElements;

    /**
     * Constructs a new Page instance.
     *
     * @param elementsOnPage        the elements contained on the current page
     * @param totalNumberOfElements the total number of elements across all pages
     */
    public Page(Iterable<E> elementsOnPage, int totalNumberOfElements) {
        this.elementsOnPage = elementsOnPage;
        this.totalNumberOfElements = totalNumberOfElements;
    }

    /**
     * @return an Iterable of the elements on this page
     */
    public Iterable<E> getElementsOnPage() {
        return elementsOnPage;
    }

    /**
     * @return the total number of elements across all pages
     */
    public int getTotalNumberOfElements() {
        return totalNumberOfElements;
    }
}