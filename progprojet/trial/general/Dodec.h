#pragma once
#include "Vecteur3D.h"
#include "Plan.h"
#include "Dalle.h"
#include "Obstacle.h"
#include <cmath>
#include <vector>

class Dodec: public Obstacle{
	public:
	//constructeur et destructeur
	Dodec(Vecteur3D position = Vecteur3D(0,0,0), double edge = 1, Vecteur3D vecteur_1= Vecteur3D(0,0,1), bool m= false): Obstacle(position, m),edge(edge),vecteur_1(vecteur_1) {}
	virtual ~Dodec(){}

	//methodes
	virtual void dessine() const override {if (support != nullptr) support->dessine(*this);}
	Vecteur3D get_vecteur_1() const {return vecteur_1;}
	double get_edge() const {return edge;}
	bool is_inside(Vecteur3D const& x_i) const; // methode qui verifie si un point est  l'interieur de la brique
	virtual Vecteur3D PointPlusProche(Vecteur3D const& x_i) const; // returne le point sur la dalle qui est le plus proche du point x_i
	std:: unique_ptr<Dodec> cloneMe() const;
	virtual std::unique_ptr<Obstacle> copie() const override;
	virtual std::ostream& display(std::ostream& sortie) const override{ sortie<<"Dodecahedron with edge:"<<edge; return sortie;};
	std::vector<Vecteur3D> vertipositions() const ;

protected:
	Vecteur3D vecteur_1;
	double edge; // hauteur de la brique
};