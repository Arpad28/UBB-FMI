package Service;

import Domain.Prietenie;
import Domain.Tuple;
import Domain.Utilizator;
import Repository.Repository;
import Repository.RepositoryException;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Queue;
import java.util.Set;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

/**
 * Service class handling business logic for the social network.
 */
public class ReteaService {
    private final Repository<Long, Utilizator> repoUtilizatori;
    private final Repository<Tuple<Long, Long>, Prietenie> repoPrietenii;

    /**
     * Constructs the ReteaService with user and friendship repositories.
     * @param repoUtilizatori the repository of users
     * @param repoPrietenii the repository of friendships
     */
    public ReteaService(Repository<Long, Utilizator> repoUtilizatori,
                        Repository<Tuple<Long, Long>, Prietenie> repoPrietenii) {
        this.repoUtilizatori = repoUtilizatori;
        this.repoPrietenii = repoPrietenii;
        curataPrieteniiOrfane();
    }

    private <T> Stream<T> toStream(Iterable<T> iterable) {
        return StreamSupport.stream(iterable.spliterator(), false);
    }

    private void curataPrieteniiOrfane() {
        try {
            List<Tuple<Long, Long>> deSters = toStream(repoPrietenii.findAll())
                    .filter(p -> repoUtilizatori.findOne(p.getId().getE1()).isEmpty()
                            || repoUtilizatori.findOne(p.getId().getE2()).isEmpty())
                    .map(Prietenie::getId)
                    .collect(Collectors.toList());

            deSters.forEach(id -> {
                System.err.println("Prietenie ignorata/stearsa (utilizator inexistent): " + id);
                repoPrietenii.delete(id);
            });
        } catch (RepositoryException e) {
            System.err.println("Atentie la initializare: " + e.getMessage());
        }
    }

    /**
     * Finds a user by ID.
     * @param id the ID of the user
     * @return an Optional containing the user if found
     * @throws RepositoryException if a persistence error occurs
     */
    public Optional<Utilizator> findUtilizator(Long id) {
        return repoUtilizatori.findOne(id);
    }

    /**
     * Adds a new user to the network; the ID is generated automatically by the storage layer.
     * @param firstName the user's first name
     * @param lastName the user's last name
     * @return the saved Utilizator with its generated ID populated
     * @throws RepositoryException if a database error occurs
     */
    public Utilizator addUtilizator(String firstName, String lastName) {
        Utilizator u = new Utilizator(firstName, lastName);
        repoUtilizatori.save(u).ifPresent(existing -> {
            throw new IllegalArgumentException("Utilizatorul nu a putut fi salvat!");
        });
        return u;
    }

    /**
     * Updates an existing user's first and last name.
     * @param id the ID of the user to update
     * @param firstName the new first name
     * @param lastName the new last name
     * @throws IllegalArgumentException if no user with the given ID exists
     * @throws RepositoryException if a database error occurs
     */
    public void updateUtilizator(Long id, String firstName, String lastName) {
        Utilizator u = new Utilizator(firstName, lastName);
        u.setId(id);
        repoUtilizatori.update(u).ifPresent(notFound -> {
            throw new IllegalArgumentException("Nu exista niciun utilizator cu ID-ul " + id + "!");
        });
    }

    /**
     * Removes a user and ensures all of their friendships are removed.
     * @param id the ID of the user to remove
     * @throws IllegalArgumentException if the user does not exist
     * @throws RepositoryException if a database error occurs
     */
    public void removeUtilizator(Long id) {
        repoUtilizatori.delete(id)
                .orElseThrow(() -> new IllegalArgumentException("Nu exista niciun utilizator cu ID-ul " + id + "!"));

        // Pentru MEMORY si FILE stergem si din repoPrietenii; in DB sunt sterse deja de ON DELETE CASCADE
        List<Tuple<Long, Long>> prieteniiDeSters = repoPrietenii
                .findAll(p -> p.getId().getE1().equals(id) || p.getId().getE2().equals(id))
                .stream()
                .map(Prietenie::getId)
                .collect(Collectors.toList());

        prieteniiDeSters.forEach(repoPrietenii::delete);
    }

    /**
     * Adds a friendship between two existing users.
     * @param id1 the first user's ID
     * @param id2 the second user's ID
     * @throws IllegalArgumentException if either user does not exist or friendship already exists
     * @throws RepositoryException if a database error occurs
     */
    public void addPrietenie(Long id1, Long id2) {
        repoUtilizatori.findOne(id1)
                .orElseThrow(() -> new IllegalArgumentException("Utilizatorul cu ID-ul " + id1 + " nu exista!"));
        repoUtilizatori.findOne(id2)
                .orElseThrow(() -> new IllegalArgumentException("Utilizatorul cu ID-ul " + id2 + " nu exista!"));

        Prietenie p = new Prietenie(id1, id2);
        repoPrietenii.save(p).ifPresent(existing -> {
            throw new IllegalArgumentException("Prietenia dintre acesti utilizatori exista deja!");
        });
    }

    /**
     * Removes a friendship between two users.
     * @param id1 the first user's ID
     * @param id2 the second user's ID
     * @throws IllegalArgumentException if the friendship does not exist
     * @throws RepositoryException if a database error occurs
     */
    public void removePrietenie(Long id1, Long id2) {
        Prietenie dummy = new Prietenie(id1, id2);
        repoPrietenii.delete(dummy.getId())
                .orElseThrow(() -> new IllegalArgumentException("Prietenia specificata nu exista!"));
    }

    public List<Utilizator> getAllUtilizatori() {
        return toStream(repoUtilizatori.findAll())
                .sorted(Comparator.comparing(Utilizator::getLastName)
                        .thenComparing(Utilizator::getFirstName))
                .collect(Collectors.toList());
    }

    public List<Prietenie> getAllPrietenii() {
        return toStream(repoPrietenii.findAll())
                .collect(Collectors.toList());
    }

    public List<Utilizator> getPrieteniUtilizator(Long userId) {
        repoUtilizatori.findOne(userId)
                .orElseThrow(() -> new IllegalArgumentException("Utilizatorul cu ID-ul " + userId + " nu exista!"));

        return toStream(repoPrietenii.findAll())
                .filter(p -> p.getId().getE1().equals(userId) || p.getId().getE2().equals(userId))
                .map(p -> p.getId().getE1().equals(userId) ? p.getId().getE2() : p.getId().getE1())
                .map(repoUtilizatori::findOne)
                .flatMap(Optional::stream)
                .sorted(Comparator.comparing(Utilizator::getLastName)
                        .thenComparing(Utilizator::getFirstName))
                .collect(Collectors.toList());
    }

    public List<Utilizator> filtreazaUtilizatori(Predicate<Utilizator> criteriu) {
        return repoUtilizatori.findAll(criteriu)
                .stream()
                .sorted(Comparator.comparing(Utilizator::getLastName)
                        .thenComparing(Utilizator::getFirstName))
                .collect(Collectors.toList());
    }

    private Map<Long, List<Long>> construiesteListaAdiacenta() {
        Map<Long, List<Long>> adj = toStream(repoUtilizatori.findAll())
                .collect(Collectors.toMap(
                        Utilizator::getId,
                        u -> new ArrayList<>()
                ));

        toStream(repoPrietenii.findAll()).forEach(p -> {
            Long u1 = p.getId().getE1();
            Long u2 = p.getId().getE2();
            if (adj.containsKey(u1) && adj.containsKey(u2)) {
                adj.get(u1).add(u2);
                adj.get(u2).add(u1);
            }
        });
        return adj;
    }

    private Map<Long, Integer> bfs(Long startId, Map<Long, List<Long>> adj) {
        Queue<Long> coada = new LinkedList<>();
        Map<Long, Integer> distante = new HashMap<>();

        coada.add(startId);
        distante.put(startId, 0);

        while (!coada.isEmpty()) {
            Long curent = coada.poll();
            int distantaCurenta = distante.get(curent);

            Optional.ofNullable(adj.get(curent))
                    .orElseGet(ArrayList::new)
                    .stream()
                    .filter(prietenId -> !distante.containsKey(prietenId))
                    .forEach(prietenId -> {
                        distante.put(prietenId, distantaCurenta + 1);
                        coada.add(prietenId);
                    });
        }
        return distante;
    }

    public int nrComunitati() {
        Map<Long, List<Long>> adj = construiesteListaAdiacenta();
        Set<Long> vizitat = new HashSet<>();

        return (int) adj.keySet().stream()
                .filter(id -> !vizitat.contains(id))
                .peek(id -> vizitat.addAll(bfs(id, adj).keySet()))
                .count();
    }

    public List<Long> ceaMaiSociabilaComunitate() {
        Map<Long, List<Long>> adj = construiesteListaAdiacenta();

        return adj.keySet().stream()
                .map(startNode -> bfs(startNode, adj))
                .max(Comparator.comparingInt(distante ->
                        distante.values().stream().mapToInt(Integer::intValue).max().orElse(0)))
                .map(Map::keySet)
                .map(ArrayList::new)
                .orElseGet(ArrayList::new);
    }
}