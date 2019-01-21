#pragma once
#include <vector>
#include "Obstacle.h"
#include <iostream>
#include "Dessinable.h"
#include <memory>
#include "SupportADessin.h"
#include "SupportADessinTexte.h"
#include "Vecteur3D.h"
#include "Systeme.h"
#include "Magnet.h"



class SystemeP9: public Systeme
{
friend class VueOpenGL;
public:

	// constructeur et destructeur
	SystemeP9(SupportADessin* support): Systeme(support) {}
	SystemeP9() {}
	virtual ~SystemeP9() {}

	// methodes
	std:: ostream& display(std:: ostream& c) const override;

  virtual void dessine() const override {support->dessine(*this);}


	virtual void evolue1(double dt=0.001); //evolution du système selon le 1er algo avec les ameliorations le long du projet
	virtual void evolue1(double dt, unsigned int nb_repet); // evolution du système selon le 1er algo nb_repet fois

	void evolue2(double dt=0.001); // evolution du système selon le 2ème algo
	void evolue2(double dt, unsigned int nb_repet); // evolution du système selon le 2ème algo nb_repet fois


	virtual void addMagnet(Magnet const& nouveau_Magnet);


	// copie polymorphique du système
	std::unique_ptr<Systeme> copie() const;
	std::unique_ptr<SystemeP9> cloneme() const;

private:
	// attributs
	std:: vector<std::unique_ptr<Magnet>> tab_ptr_Magnets;

	// deletes
	SystemeP9 (SystemeP9 const&) = delete;
	void operator=(SystemeP9 modele) = delete;
};

// externe
std::ostream& operator<<(std::ostream& sortie, Systeme const& s);
