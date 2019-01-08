#pragma once
#define _USE_MATH_DEFINES
#include "Vecteur3D.h"
#include <iostream>
#include "Medium.h"
#include "Dessinable.h"
#include "SupportADessin.h"
#include "Obstacle.h"
#include <memory>
#include <cmath>

typedef Vecteur3D Position, Vitesse;

class Magnet : public Dessinable
{

public:
    // constructeurs et destructeurs
    Magnet(Position const& position, SupportADessin* support, Vitesse const& vitesse, double masse_volumique, double rayon,
          Vecteur3D const& force = Vecteur3D(), Medium medium = water,double height = 1.0, Vecteur3D moment=Vecteur3D(1,0,0));
    virtual ~Magnet() {}


    // manipulateurs

    void set_medium(Medium medium = water);

    Medium* get_medium() const; // retourne le medium dans le quelle le Magnet est

    double get_volume() const;

    double get_lambda()const;

    Position get_position() const;

    Vitesse get_velocity() const;

    void set_velocity(Vitesse newV);

    void set_velocity(double newVx, double newVy, double newVz);

    void set_radius(double newR);

    double get_radius() const;

    void set_support(SupportADessin* s){ support = s; }

		Vecteur3D get_moment() const {return moment;}

		double get_height() const {return height;}


    // methodes

    virtual void dessine() const override =0;

    bool bouger(double temps); //update the coordinates and velocity of the Magnet after a period of time

    //method to display the Magnet's data
    std :: ostream& display(std :: ostream& sortie ) const;

    // method to calculate the mass of the Magnet
    double calc_mass()const
    {
        return (get_volume()*masse_volumique);
    }

	// methodes pour ajouter les force qui agissent sur le Magnet, ces forces viennes des autres Magnets, des obstacles, gravité, archimède...
    virtual void ajouteForce();

    virtual Vecteur3D ajouteForce(std:: unique_ptr<Magnet> const& Magnet2) =0;

    virtual void ajouteForce(std:: unique_ptr<Obstacle> const& obstacle1) =0;
    virtual void ajouteForce(Obstacle const& obstacle1) =0;

    virtual void ajouteForce(Vecteur3D const& vector1) = 0;

    // copie polymorphique
    virtual std::unique_ptr<Magnet> copie() const = 0;

protected:
    Vitesse velocity;
    double masse_volumique;
    double radius;
		double height;
    Vecteur3D force;
    Medium* medium;
		Vecteur3D moment;



};
