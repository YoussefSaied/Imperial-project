#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include "Vecteur3D.h"
#include <cmath>
#include "Grain.h"
#include "Obstacle.h"

using namespace std;


Grain :: Grain(Position const& position, SupportADessin* support, Vitesse const& vitesse, double masse_volumique, double rayon, Vecteur3D const& force,  Medium medium):
    Dessinable(position,support), velocity(vitesse), masse_volumique(masse_volumique), radius(rayon), force(force), medium(&medium) {}


ostream& Grain:: display(std :: ostream& c) const
{
    c<<"[ Position: " 	<< position
     <<", Velocity: " 	<< velocity
     <<", Force: "		<< force
     <<", Radius: "	<< radius 	<<", Volume: "<< get_volume()
     <<", Mass: "		<< calc_mass()<<" ]"<<endl;
    return c;
}

void Grain :: set_medium(Medium medium)
{
    (*this).medium = &medium;
}

Medium* Grain :: get_medium() const
{
    return medium;
}

double Grain :: get_lambda()const
{
    if(velocity <= 80.0/3.0/radius*((*medium).Nu())/((*medium).Rho())) {
        return 6.0*M_PI*radius*((*medium).Nu());
    } else return ((9.0*M_PI/40.0*radius*radius*(*medium).Rho())*velocity).norme();
}
Position Grain :: get_position() const
{
    return position;
}

double Grain:: get_volume() const
{
    return (4.0/3.0)*(M_PI)*radius*radius*radius;
}

Vecteur3D Grain:: get_velocity() const
{
    return velocity;
}

void Grain:: set_velocity(Vecteur3D newV)
{
    velocity=newV;
}

void Grain:: set_velocity(double newVx, double newVy, double newVz)
{
    velocity.set_coord(newVx, newVy, newVz);
}


void Grain :: set_radius(double newR)
{
    if(newR<=1e-6) {
        radius = 1e-6;
    } else {
        radius = newR;
    }
}

double Grain :: get_radius() const
{
    return radius;
}

//method to add force
void Grain :: ajouteForce()
{
    force+= (((calc_mass())*g - (get_lambda())*velocity) + (-1* (get_volume()*g*((*medium).Rho())))
            );
}

//method to update the coordinates and velocity of the grain after a specified period of time
bool Grain:: bouger(double temps)
{
    velocity += (((temps/(calc_mass()))*(force)));

    position += (temps*velocity);

    force = 0.0;
    return (temps*velocity) > radius/2;
}
