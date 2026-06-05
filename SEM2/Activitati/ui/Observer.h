#pragma once
#include <vector>
#include <algorithm>

// Interfata pentru observatori (ferestrele care afiseaza cosul)
class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

// Clasa care va fi observata (Service-ul sau Cosul curent)
class Observable {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }
    
    void removeObserver(Observer* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }
    
protected:
    void notifyObservers() {
        for (auto obs : observers) {
            obs->update();
        }
    }
};