#pragma once
#include <string>
#include <vector>

class RepoException {
    std::string mesaj;
public:
    RepoException(const std::string& msg) : mesaj(msg) {}
    std::string get_mesaj() const { return mesaj; }
};

class ValidationException {
    std::string mesaj;
public:
    ValidationException(const std::string& msg) : mesaj(msg) {}
    std::string get_mesaj() const { return mesaj; }};