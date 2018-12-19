#pragma once
#include <vector>
#include <memory>
#include "Grain.h"

// Classe qui répresente les Cases pour l'exercice P12
class Box
{
    friend class SystemeP12;
public:
    Box() {}
    Box(Box const& modele); //constructeur de copie
private:
    std:: vector<std::unique_ptr<Grain>> tab_ptr_grains; // grains qui sont dans la box
};
