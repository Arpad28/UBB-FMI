#include "repo.h"
#include <fstream>
#include <sstream>

Repo::Repo(std::string nume_fisier) : nume_fisier(nume_fisier) {
    loadFromFile();
}

void Repo::loadFromFile() {
    std::ifstream in(nume_fisier);
    std::string linie;
    lista.clear();
    while (std::getline(in, linie)) {
        if(linie.empty()) continue;
        std::stringstream ss(linie);
        std::string s_id, s_dim, board, s_player, status;
        
        std::getline(ss, s_id, ',');
        std::getline(ss, s_dim, ',');
        std::getline(ss, board, ',');
        std::getline(ss, s_player, ',');
        std::getline(ss, status, '\n');
        
        Game g(std::stoi(s_id), std::stoi(s_dim), board, s_player[0], status);
        lista.push_back(g);
    }
    in.close();
}

void Repo::saveToFile() {
    std::ofstream out(nume_fisier);
    for (const auto& g : lista) {
        out << g.getId() << "," 
            << g.getDim() << "," 
            << g.getBoard() << "," 
            << g.getNextPlayer() << "," 
            << g.getStatus() << "\n";
    }
    out.close();
}

std::vector<Game> Repo::get_all() const {
    return lista;
}

void Repo::addGame(const Game& g) {
    lista.push_back(g);
    saveToFile();
}

void Repo::updateGame(const Game& modifiedGame) {
    for (auto& g : lista) {
        if (g.getId() == modifiedGame.getId()) {
            g.setDim(modifiedGame.getDim());
            g.setBoard(modifiedGame.getBoard());
            g.setNextPlayer(modifiedGame.getNextPlayer());
            g.setStatus(modifiedGame.getStatus());
            break;
        }
    }
    saveToFile();
}