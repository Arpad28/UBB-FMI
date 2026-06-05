#pragma once
#include "../domain/activitate.h"
#include <vector>
#include <string>
#include <unordered_map>

class Repo {
public:
    virtual void adauga(const Activitate& a) = 0;
    virtual void sterge(int id) = 0;
    virtual void modifica(const Activitate& a) = 0;
    virtual const Activitate& cauta(int id) const = 0;
    virtual std::vector<Activitate> get_all() const = 0;

    virtual ~Repo() = default;
};

class MemoryRepo : public Repo {
protected:
    std::vector<Activitate> lista;

public:
    MemoryRepo() = default;
    void adauga(const Activitate& a) override;
    void sterge(int id) override;
    void modifica(const Activitate& a) override;
    const Activitate& cauta(int id) const override;
    std::vector<Activitate> get_all() const override;
};

class FileRepo : public MemoryRepo {
private:
    std::string nume_fisier;
    void loadFromFile();
    void writeToFile();

public:
    FileRepo(const std::string& nume_fisier);
    void adauga(const Activitate& a) override;
    void sterge(int id) override;
    void modifica(const Activitate& a) override;
};

class MapRepo : public Repo {
private:
    std::unordered_map<int, Activitate> dict;
    double probabilitate;
    void random_fail() const;

public:
    MapRepo(double prob);
    void adauga(const Activitate& a) override;
    void sterge(int id) override;
    void modifica(const Activitate& a) override;
    const Activitate& cauta(int id) const override;
    std::vector<Activitate> get_all() const override;
};