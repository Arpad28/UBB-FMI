#pragma once
#include "repo.h"
#include <vector>

class Service {
private:
    Repo& repo;
    std::string determineNewStatus(const std::string& board, int dim) const;
public:
    Service(Repo& repo) : repo(repo) {}
    
    std::vector<Game> get_all_sorted() const;
    Game cauta(int id) const;
    void createGame(int dim, char next_player);
    void updateGame(int id, int dim, const std::string& board, char next_player, const std::string& status);
    void playMove(int id, int row, int col);
};