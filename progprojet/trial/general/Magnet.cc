#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include "Vecteur3D.h"
#include <cmath>
#include "Magnet.h"
#include "Obstacle.h"

using namespace std;


Magnet :: Magnet(Position const& position, SupportADessin * support, Vitesse const& vitesse, double masse_volumique,
  double rayon, Vecteur3D const& force, Medium medium, double height, Vecteur3D moment) :
    Dessinable(position, support), velocity(vitesse), masse_volumique(masse_volumique), radius(rayon), force(force),
    medium(&medium), height(height), moment(moment){ }


ostream& Magnet:: display(std :: ostream& c) const
{
    c << "Position: " << position << endl
      << "Velocity: " << velocity << endl
      << "Force: " << force << endl
      << "Moment: " << moment << endl
      << "Radius: " << radius << endl << "Height: " << height << endl
      << "Volume: " << get_volume() << endl
      << "Mass: " << calc_mass() << endl;
    return c;
}

void Magnet :: set_medium(Medium medium)
{
    (*this).medium = &medium;
}

Medium * Magnet :: get_medium() const
{
    return medium;
}

double Magnet :: get_lambda() const
{
    if (velocity <= 80.0 / 3.0 / radius * ((*medium).Nu()) / ((*medium).Rho())) {
        return 6.0 * M_PI * radius * ((*medium).Nu());
    } else { return ((9.0 * M_PI / 40.0 * radius * radius * (*medium).Rho()) * velocity).norme(); }
}

Position Magnet :: get_position() const
{
    return position;
}

double Magnet:: get_volume() const
{
    return (M_PI) *radius * radius * height;
}

Vecteur3D Magnet:: get_velocity() const
{
    return velocity;
}

void Magnet:: set_velocity(Vecteur3D newV)
{
    velocity = newV;
}

void Magnet:: set_velocity(double newVx, double newVy, double newVz)
{
    velocity.set_coord(newVx, newVy, newVz);
}

void Magnet :: set_radius(double newR)
{
    if (newR <= 1e-6) {
        radius = 1e-6;
    } else {
        radius = newR;
    }
}

double Magnet :: get_radius() const
{
    return radius;
}

// Your part here:


// method to add force
void Magnet :: ajouteForce()
{
    /*force+= (((calc_mass())*g - (get_lambda())*velocity) + (-1* (get_volume()*g*((*medium).Rho())))
            );*/
}

// method to update the coordinates and velocity of the Magnet after a specified period of time
bool Magnet:: bouger(double temps)
{
    velocity += (((temps / (calc_mass())) * (force)));

    position += (temps * velocity);

    force = 0.0;
    return (temps * velocity) > radius / 2;
}
