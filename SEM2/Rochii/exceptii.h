#pragma once
#include <string>

class RepoException {
    std::string mesaj;
public:
    RepoException(const std::string& mesaj) : mesaj(mesaj) {}
    std::string get_mesaj() const { return mesaj; }
};