#pragma once
#include "Vecteur3D.h"
#include "Plan.h"
#include "Dalle.h"
#include "Obstacle.h"
#include "Brique.h"
#include "Medium.h"
#include <iostream>
#include <memory>
#include "Magnet.h"
#include "MagnetE.h"
#include "MagnetEO.h"

class Mediumi: public Brique
{
public:
	//constructeur et destructeur
    Mediumi(Dalle d, double h, Medium m = water, bool mov = false):Brique(d, h, mov), medium(&m) {}
    virtual~Mediumi() {}

    //methodes
    virtual void dessine() const override { if (support != nullptr) support->dessine(*this); }
    void set_medium(Medium medium = water) { (*this).medium = &medium; }
    Medium* get_medium() const { return medium; }
    bool is_inside(Magnet& g) const;
    std::vector<Dalle> dalle5() const;

    virtual std::ostream& display(std::ostream& c) const override;
    std:: unique_ptr<Mediumi> cloneMe() const
    {
        return std::unique_ptr<Mediumi>(new Mediumi(*this));
    }
    virtual std::unique_ptr<Obstacle> copie() const override
    {
        return cloneMe();
    }
protected:
    Medium* medium;
};
