#pragma once
#include <vector>
#include "Obstacle.h"
#include <iostream>
#include "Dessinable.h"
#include <memory>
#include "Medium.h"
#include "SupportADessin.h"
#include "SupportADessinTexte.h"
#include "Vecteur3D.h"
#include "Mediumi.h"
#include "Sphere.h"
#include "Dodec.h"
#include "Magnet.h"
#include "MagnetE.h"
#include "MagnetEO.h"
class Systeme : public Dessinable
{
    friend class VueOpenGL; // simple solution
public:

    // constructeurs et destructeurs
    Systeme(SupportADessin * support = &Texte1, Medium m = air) : Dessinable(Position(), support),
        H(0, 0, 0)
    { }

    virtual ~Systeme(){ }

    Vecteur3D H; // external magnetic field

    // methodes


    virtual double evolue1(double dt = 0.001) = 0;

    virtual std:: ostream& display(std:: ostream& c) const = 0;

    virtual void addMagnet(Magnet const& new_Magnet) = 0;

    void ajouteObstacle(Obstacle const& nouveau_obstacle);

    void ajouteMediumi(Mediumi const& nouveau_mediumi);

    virtual std::unique_ptr<Systeme> copie() const = 0;

    // virtual std::unique_ptr<Systeme> P9toP12() const =0;

    // virtual std::unique_ptr<Systeme> P12toP9() const =0;


public:

    // delete
    Systeme (Systeme const&) = delete;


    // attributs
    std:: vector<std::unique_ptr<Obstacle> > tab_ptr_obstacles;
    std:: vector<std::unique_ptr<Mediumi> > tab_ptr_mediums;
    std:: vector<std::unique_ptr<Magnet> > tab_ptr_Magnets;
    Medium * ptr_medium;
};

// externe
std::ostream& operator << (std::ostream& sortie, Systeme const& s);
