#pragma once
#include "SupportADessin.h"
#include <iostream>
#include <vector>


class SupportADessinTexte : public SupportADessin
{
public:
	//constructeur et destructeur
    SupportADessinTexte(std::ostream& flot) : flot(flot) {}
    virtual ~SupportADessinTexte() {}

    //methodes
    virtual void dessine(GrainLJ const& G ) override;
    virtual void dessine(GrainLJUn const& G   ) override;
    virtual void dessine(GrainLJDeux  const& G  ) override;
  	virtual void dessine(SystemeP12 const& S ) override;
    virtual void dessine(SystemeP9 const& S ) override;
    virtual void dessine(Plan const& P) override;
    virtual void dessine(Source const& s) override;
    virtual void dessine(Dalle const& d) override;
    virtual void dessine(Sphere const& s)override;
    virtual void dessine(Brique const& b) override;
	virtual void dessine(Mediumi const& M)override;
	virtual void dessine(Cylinder const& c) override;

private:
    std::ostream& flot;
};

static SupportADessinTexte Texte1(std::cout);
