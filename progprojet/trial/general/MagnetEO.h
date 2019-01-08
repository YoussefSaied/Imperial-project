#pragma once
#include "MagnetE.h"
#include "Magnet.h"

class MagnetEO: public MagnetE
{
public:

	// constructeur et destructeur
    MagnetEO(Position const& position, Vitesse const& vitesse,
              double masse_volumique, double rayon, Vecteur3D const& force = Vecteur3D(),
              Medium medium = water, double height = 1.0, Vecteur3D moment=Vecteur3D(1,0,0), SupportADessin* support = &Texte1): MagnetE(position, vitesse, masse_volumique, rayon, force, medium,height,moment, support) {}
    virtual ~MagnetEO() {}


    //methodes
    virtual void dessine() const override { if (support != nullptr) support->dessine(*this); }

    std:: unique_ptr<MagnetEO> cloneMe() const { return std::unique_ptr<MagnetEO>(new MagnetEO(*this)); }

    virtual std::unique_ptr<Magnet> copie() const override { return cloneMe(); }
};
