#pragma once
#include "Vecteur3D.h"
#include "Obstacle.h"
#include <cmath>
#include <memory>
#include <iostream>
class Sphere: public Obstacle
{
public:
	//constructeur et destructeur
	Sphere(Position position, double radius, bool m = false): Obstacle(position, m), radius(radius) {}
    virtual ~Sphere() {}


    //methodes
    virtual void dessine() const override { if (support != nullptr) support->dessine(*this); }

    virtual Vecteur3D PointPlusProche(Vecteur3D const& v) const override;

    virtual std::ostream& display (std::ostream& sortie) const;

	double get_radius() const { return radius; }

    std:: unique_ptr<Sphere> cloneMe() const;

    virtual std::unique_ptr<Obstacle> copie() const override;


protected:
    double radius;

};
