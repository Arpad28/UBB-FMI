#pragma once
#include <string>

class Game {
private:
    int id;
    int dim;
    std::string board;
    char next_player;
    std::string status;
public:
    Game(int id, int dim, std::string board, char next_player, std::string status);
    
    int getId() const;
    int getDim() const;
    std::string getBoard() const;
    char getNextPlayer() const;
    std::string getStatus() const;

    void setDim(int d);
    void setBoard(const std::string& b);
    void setNextPlayer(char p);
    void setStatus(const std::string& s);
};