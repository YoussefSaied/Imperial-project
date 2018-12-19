#pragma once
#include "Vecteur3D.h"
#include "Obstacle.h"
#include <iostream>
#include <memory>

class Cylinder : public Obstacle{
public:
	//constructeur et destructeur
	Cylinder(Position position, Vecteur3D vector1, double h, double r, bool m= false);
	virtual ~Cylinder() {}

	//methodes
	virtual void dessine() const override {if (support != nullptr) support->dessine(*this);}

	virtual Vecteur3D PointPlusProche(Vecteur3D const& x_i) const; // le point le plus proche dans le plan à x_i

	virtual std::ostream& display (std::ostream& sortie) const;

	void distancea(Vecteur3D vector1)const; //affiche la distance du point plus proche au vector1

	Vecteur3D get_vecteur_1() const { return vecteur_1; }

	double get_radius() const {	return rayon; }

	double get_hauteur() const { return hauteur; }

	std:: unique_ptr<Cylinder> cloneMe() const;

	virtual std::unique_ptr<Obstacle> copie() const override;


protected:
	Vecteur3D vecteur_1; // vecteur unitaire perpendiculaire au plan
	double hauteur;
	double rayon;
};

//externes
std :: ostream& operator<<(std :: ostream& c, Cylinder const& cyl1 );
