#pragma once
#include <vector>
#include "Obstacle.h"
#include "GrainLJ.h"
#include "Source.h"
#include "Grain.h"
#include "GrainLJUn.h"
#include "GrainLJDeux.h"
#include <iostream>
#include "Dessinable.h"
#include <memory>
#include "Medium.h"
#include "SupportADessin.h"
#include "SupportADessinTexte.h"
#include "Vecteur3D.h"
#include "triplet.h"
#include "Systeme.h"

class Systemep13: public Systeme
{
friend class VueOpenGL; //simple solution
public:

	// constructeurs et destructeur
	Systemep13(SupportADessin* support):Systeme(support) {}
	virtual ~Systemep13 () {}


// operateurs

std:: ostream& display(std:: ostream& c) const;


// methodes changement de système
std::unique_ptr<SystemeP9> p13toP9s() const;
std::unique_ptr<Systeme> p13toP9() const;
std::unique_ptr<Systeme> P9top13() const { std::cout<<"deja p13 mais.. "<<std::endl; return copie(); }


// copie polymorphique pour changer le système
std::unique_ptr<Systeme> copie() const;
std::unique_ptr<Systemep13> cloneme()const;


//autres méthodes
virtual void dessine() override {support->dessine(*this);}

double evolue1(double dt=0.001);


// manipulateurs

void ajouteGrain(Grain const& nouveau_grain);


private:
	// attributs
	map<triplet,std::vector<std::unique_ptr<Grain>>> map_case;

	// deletes
	SystemeP13 (SystemeP13 const&) = delete;
	void operator=(SystemeP13 modele) = delete;

};
