package Service;

import Domain.Prietenie;
import Domain.Tuple;
import Domain.Utilizator;
import Repository.Repository;

import java.util.*;

/**
 * Service class handling business logic for the social network.
 */
public class ReteaService {
    private final Repository<Long, Utilizator> repoUtilizatori;
    private final Repository<Tuple<Long, Long>, Prietenie> repoPrietenii;

    public ReteaService(Repository<Long, Utilizator> repoUtilizatori, Repository<Tuple<Long, Long>, Prietenie> repoPrietenii) {
        this.repoUtilizatori = repoUtilizatori;
        this.repoPrietenii = repoPrietenii;
        curataPrieteniiOrfane();
    }

    /**
     * Ensures consistency at startup: removes any friendship from the file whose users do not exist.
     */
    private void curataPrieteniiOrfane() {
        try {
            List<Tuple<Long, Long>> deSters = new ArrayList<>();
            for (Prietenie p : repoPrietenii.findAll()) {
                Long id1 = p.getId().getE1();
                Long id2 = p.getId().getE2();
                if (repoUtilizatori.findOne(id1) == null || repoUtilizatori.findOne(id2) == null) {
                    deSters.add(p.getId());
                    System.err.println("Prietenie ignorata/stearsa (utilizator inexistent): " + p.getId());
                }
            }
            for (Tuple<Long, Long> id : deSters) {
                repoPrietenii.delete(id);
            }
        } catch (UnsupportedOperationException e) {
        }
    }

    public void addUtilizator(Long id, String firstName, String lastName) {
        Utilizator u = new Utilizator(firstName, lastName);
        u.setId(id);
        Utilizator rezultat = repoUtilizatori.save(u);
        if (rezultat != null) {
            throw new IllegalArgumentException("Exista deja un utilizator cu ID-ul " + id + "!");
        }
    }

    public void removeUtilizator(Long id) {
        Utilizator sters = repoUtilizatori.delete(id);
        if (sters == null) {
            throw new IllegalArgumentException("Nu exista niciun utilizator cu ID-ul " + id + "!");
        }
        List<Tuple<Long, Long>> prieteniiDeSters = new ArrayList<>();
        for (Prietenie p : repoPrietenii.findAll()) {
            if (p.getId().getE1().equals(id) || p.getId().getE2().equals(id)) {
                prieteniiDeSters.add(p.getId());
            }
        }
        for (Tuple<Long, Long> idPrietenie : prieteniiDeSters) {
            repoPrietenii.delete(idPrietenie);
        }
    }

    public void addPrietenie(Long id1, Long id2) {
        if (repoUtilizatori.findOne(id1) == null || repoUtilizatori.findOne(id2) == null) {
            throw new IllegalArgumentException("Unul sau ambii utilizatori nu exista!");
        }
        Prietenie p = new Prietenie(id1, id2);
        Prietenie rezultat = repoPrietenii.save(p);
        if (rezultat != null) {
            throw new IllegalArgumentException("Prietenia dintre acesti utilizatori exista deja!");
        }
    }

    public void removePrietenie(Long id1, Long id2) {
        Prietenie dummy = new Prietenie(id1, id2);
        Prietenie sters = repoPrietenii.delete(dummy.getId());
        if (sters == null) {
            throw new IllegalArgumentException("Prietenia specificata nu exista!");
        }
    }

    public Iterable<Utilizator> getAllUtilizatori() {
        return repoUtilizatori.findAll();
    }

    public Iterable<Prietenie> getAllPrietenii() {
        return repoPrietenii.findAll();
    }

    private Map<Long, List<Long>> construiesteListaAdiacenta() {
        Map<Long, List<Long>> adj = new HashMap<>();
        for (Utilizator u : repoUtilizatori.findAll()) {
            adj.put(u.getId(), new ArrayList<Long>());
        }
        for (Prietenie p : repoPrietenii.findAll()) {
            Long u1 = p.getId().getE1();
            Long u2 = p.getId().getE2();
            if (adj.containsKey(u1) && adj.containsKey(u2)) {
                adj.get(u1).add(u2);
                adj.get(u2).add(u1);
            }
        }
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

            List<Long> prieteni = adj.get(curent);
            if (prieteni != null) {
                for (Long prietenId : prieteni) {
                    if (!distante.containsKey(prietenId)) {
                        distante.put(prietenId, distantaCurenta + 1);
                        coada.add(prietenId);
                    }
                }
            }
        }
        return distante;
    }

    public int nrComunitati() {
        Map<Long, List<Long>> adj = construiesteListaAdiacenta();
        Set<Long> vizitat = new HashSet<>();
        int numar = 0;

        for (Long id : adj.keySet()) {
            if (!vizitat.contains(id)) {
                numar++;
                Map<Long, Integer> componenta = bfs(id, adj);
                vizitat.addAll(componenta.keySet());
            }
        }
        return numar;
    }

    public List<Long> ceaMaiSociabilaComunitate() {
        Map<Long, List<Long>> adj = construiesteListaAdiacenta();
        int distantaMaximaGlobala = -1;
        Set<Long> iduriCastigatoare = new HashSet<>();

        for (Long startNode : adj.keySet()) {
            Map<Long, Integer> distante = bfs(startNode, adj);
            int distantaMaximaCurenta = 0;
            for (int dist : distante.values()) {
                if (dist > distantaMaximaCurenta) {
                    distantaMaximaCurenta = dist;
                }
            }
            if (distantaMaximaCurenta > distantaMaximaGlobala) {
                distantaMaximaGlobala = distantaMaximaCurenta;
                iduriCastigatoare = distante.keySet();
            }
        }
        return new ArrayList<>(iduriCastigatoare);
    }
}