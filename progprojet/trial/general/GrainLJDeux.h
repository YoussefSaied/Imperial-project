#pragma once
#include "GrainLJ.h"
#include "Grain.h"

class GrainLJDeux: public GrainLJ
{
public:

	// constructeur et destructeur
    GrainLJDeux(Position const& position, Vitesse const& vitesse,
                double masse_volumique, double rayon, Vecteur3D const& force = Vecteur3D(),
                Medium medium = water, SupportADessin* support = &Texte1): GrainLJ(position, vitesse, masse_volumique, rayon, force, medium, support) {}
    virtual ~GrainLJDeux() {}

    //methodes
    virtual void dessine() const override { if (support != nullptr) support->dessine(*this); }

    std:: unique_ptr<GrainLJDeux> cloneMe() const { return std::unique_ptr<GrainLJDeux>(new GrainLJDeux(*this)); }
    virtual std::unique_ptr<Grain> copie() const override{ return cloneMe(); }
};
