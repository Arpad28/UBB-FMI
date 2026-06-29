#include "service.h"
#include <algorithm>
#include <stdexcept>

std::vector<Game> Service::get_all_sorted() const {
    std::vector<Game> all = repo.get_all();
    std::sort(all.begin(), all.end(), [](const Game& a, const Game& b) {
        return a.getStatus() < b.getStatus();
    });
    return all;
}

Game Service::cauta(int id) const {
    auto all = repo.get_all();
    auto it = std::find_if(all.begin(), all.end(), [id](const Game& g) {
        return g.getId() == id;
    });
    if (it != all.end()) return *it;
    throw std::runtime_error("Jocul nu a fost gasit!");
}

void Service::createGame(int dim, char next_player) {
    if (dim < 3 || dim > 5) throw std::invalid_argument("Dimensiunea trebuie sa fie 3, 4 sau 5!");
    if (next_player != 'X' && next_player != 'O') throw std::invalid_argument("Jucatorul trebuie sa fie X sau O!");
    
    int new_id = 1;
    auto all = repo.get_all();
    for (const auto& g : all) {
        if (g.getId() >= new_id) new_id = g.getId() + 1;
    }
    
    std::string board(dim * dim, '-');
    Game g(new_id, dim, board, next_player, "Neinceput");
    repo.addGame(g);
}

void Service::updateGame(int id, int dim, const std::string& board, char next_player, const std::string& status) {
    if (dim != 3 && dim != 4 && dim != 5) throw std::invalid_argument("Dim 3, 4 sau 5.");
    if (board.size() != dim * dim) throw std::invalid_argument("Tabla incorecta (dim*dim caractere).");
    for (char c : board) {
        if (c != 'X' && c != 'O' && c != '-') throw std::invalid_argument("Doar X, O sau - pe tabla.");
    }
    if (next_player != 'X' && next_player != 'O') throw std::invalid_argument("Jucator X sau O.");
    if (status != "Neinceput" && status != "In derulare" && status != "Terminat") 
        throw std::invalid_argument("Stare invalida.");

    Game g(id, dim, board, next_player, status);
    repo.updateGame(g);
}

void Service::playMove(int id, int row, int col) {
    Game g = cauta(id);
    if (g.getStatus() == "Terminat") return;
    
    std::string board = g.getBoard();
    int pos = row * g.getDim() + col;
    
    if (board[pos] != '-') return; // Celula e ocupata
    
    board[pos] = g.getNextPlayer();
    g.setBoard(board);
    
    g.setNextPlayer(g.getNextPlayer() == 'X' ? 'O' : 'X');
    
    std::string next_status = determineNewStatus(board, g.getDim());
    g.setStatus(next_status);
    
    repo.updateGame(g);
}

std::string Service::determineNewStatus(const std::string& board, int dim) const {
    bool has_empty = (board.find('-') != std::string::npos);
    if (!has_empty) return "Terminat";
    return "In derulare";
}