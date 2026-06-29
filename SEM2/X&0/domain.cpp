#include "domain.h"

Game::Game(int id, int dim, std::string board, char next_player, std::string status) 
    : id(id), dim(dim), board(board), next_player(next_player), status(status) {}

int Game::getId() const {
    return id;
}
int Game::getDim() const {
    return dim;
}
std::string Game::getBoard() const {
    return board;
}
char Game::getNextPlayer() const {
    return next_player;
}
std::string Game::getStatus() const {
    return status;
}

void Game::setDim(int d) {
    dim = d;
}
void Game::setBoard(const std::string& b) {
    board = b;
}
void Game::setNextPlayer(char p) {
    next_player = p;
}
void Game::setStatus(const std::string& s) {
    status = s;
}