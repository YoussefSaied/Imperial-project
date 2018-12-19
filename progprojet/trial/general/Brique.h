#pragma once
#include "Vecteur3D.h"
#include "Plan.h"
#include "Dalle.h"
#include "Obstacle.h"
#include <cmath>
#include <vector>

class Brique: public Obstacle{
	public:
	//constructeur et destructeur
	Brique(Dalle dalle, double hauteur, bool m= false): Obstacle(dalle.get_position(), m), dalle(dalle), hauteur(hauteur) {}
	virtual ~Brique(){}

	//methodes
	virtual void dessine() const override {if (support != nullptr) support->dessine(*this);}
	Vecteur3D get_vecteur_1() const {return dalle.get_vecteur_1();}
	Vecteur3D get_vecteur_2() const {return dalle.get_vecteur_2();}
	Vecteur3D get_vecteur_3() const {return dalle.vecteur_3();}
	Vecteur3D get_position() const {return dalle.get_position();}
	double get_longueur() const {return dalle.get_longueur();}
	double get_largeur() const {return dalle.get_largeur();}
	bool is_inside(Vecteur3D const& x_i) const; // methode qui verifie si un point est  l'interieur de la brique
	virtual Vecteur3D PointPlusProche(Vecteur3D const& x_i) const; // returne le point sur la dalle qui est le plus proche du point x_i
	std::vector<Dalle> dalle6() const; // methode qui retourne un vecteur de 6 dalles qui forment la brique
	std:: unique_ptr<Brique> cloneMe() const;
	virtual std::unique_ptr<Obstacle> copie() const override;
	virtual std::ostream& display(std::ostream& sortie) const override{ sortie<<"Je suis une brique!"; return sortie;};


protected:
	Dalle dalle;
	double hauteur; // hauteur de la brique
};
