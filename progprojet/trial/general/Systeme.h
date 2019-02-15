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
        B(0.000, 0, 0), selectedmagnet(selectmagnet), KineticEnergy(0), PotentialEnergy(0), time(0), f(5), n(1),energyunit(1e4)
    { }

    virtual ~Systeme(){ }

    Vecteur3D B; // external magnetic field
    std:: vector<std::unique_ptr<Magnet> > tab_ptr_Magnets;
    int selectedmagnet;
    double KineticEnergy;
    double PotentialEnergy;
    double time;
    double f;
    size_t n; // number of times display is used when running a text sim.
    int energyunit;
    // methodes

    virtual double Energy() const { return KineticEnergy + PotentialEnergy; }

    virtual double NearestCorrelation() const;

    virtual void dessine() const override { support->dessine(*this); }

    virtual void evolue1(double dt = 0.01);
    virtual void evolue1(double dt, unsigned int nb_repet);
    virtual void evolue1(double dt, double t, bool d); // evolution du système selon le 1er temps t
    virtual std:: ostream& display(std:: ostream& c) const;

    virtual void addMagnet(Magnet const& new_Magnet);

    void addObstacle(Obstacle const& nouveau_obstacle);

    virtual void selected(int nm)
    {
        tab_ptr_Magnets[(nm % tab_ptr_Magnets.size())]->selected = 1;
        tab_ptr_Magnets[selectedmagnet]->selected = 0;
        selectedmagnet = (nm % tab_ptr_Magnets.size());
    }

    virtual std::unique_ptr<Systeme> copie() const;
    virtual std::unique_ptr<Systeme> cloneme() const;
    // delete
    Systeme (Systeme const&) = delete;


    // attributs
    std:: vector<std::unique_ptr<Obstacle> > tab_ptr_obstacles;
};

// externe
std::ostream& operator << (std::ostream& sortie, Systeme const& s);
