#pragma once
#include <vector>
#include "Obstacle.h"
#include <iostream>
#include "Dessinable.h"
#include <memory>
#include "SupportADessin.h"
#include "SupportADessinTexte.h"
#include "Vecteur3D.h"
#include "Sphere.h"
#include "Dodec.h"
#include "Magnet.h"

class Systeme : public Dessinable
{
    friend class VueOpenGL; // simple solution
public:

    // constructeurs et destructeurs
    Systeme(SupportADessin * support = &Texte1, int selectmagnet = 0) : Dessinable(Position(), support),
        H(0, 0, 0), selectedmagnet(selectmagnet)
    { }

    virtual ~Systeme(){ }

    Vecteur3D H; // external magnetic field
    std:: vector<std::unique_ptr<Magnet> > tab_ptr_Magnets;
    int selectedmagnet;

    // methodes


    virtual void evolue1(double dt = 0.001) = 0;

    virtual std:: ostream& display(std:: ostream& c) const = 0;

    virtual void addMagnet(Magnet const& new_Magnet) = 0;

    void ajouteObstacle(Obstacle const& nouveau_obstacle);

    virtual void selected(int nm)
    {
        tab_ptr_Magnets[(nm % tab_ptr_Magnets.size())]->selected = 1;
        tab_ptr_Magnets[selectedmagnet]->selected = 0;
        selectedmagnet = (nm % tab_ptr_Magnets.size());
    }

    virtual std::unique_ptr<Systeme> copie() const = 0;

    // virtual std::unique_ptr<Systeme> P9toP12() const =0;

    // virtual std::unique_ptr<Systeme> P12toP9() const =0;


    // delete
    Systeme (Systeme const&) = delete;


    // attributs
    std:: vector<std::unique_ptr<Obstacle> > tab_ptr_obstacles;
};

// externe
std::ostream& operator << (std::ostream& sortie, Systeme const& s);
