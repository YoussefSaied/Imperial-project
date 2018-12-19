#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include "Vecteur3D.h"
#include <cmath>
#include "GrainsAvant.h"
using namespace std;


//initialize
Grains :: Grains(Vecteur3D p, Vecteur3D v, Vecteur3D f, double d, double r):
    position(p), velocity(v), force(f), massvolumique(d), radius(r) {}

//set medium constants
void Grains :: set_medium(bool medium)
{
    (*this).medium = medium;
}

//method to get the value of the volume of the grain
double Grains :: get_volume() const
{
    return (4/3)*(M_PI)*radius*radius*radius;
}

//method to get the value of the mass of the grain
double Grains :: get_mass()const
{
    return (get_volume()*massvolumique);
}

//method to get the value of the coefficient lambda
double Grains :: lambda()const
{
    double nu,rho;
    if(medium) {
        nu=nu1;		   //water
        rho=rho1;
    } else {
        nu=nu0;		   //air
        rho=rho0;
    }
    if(velocity <= 80/3/radius*nu/rho) {
        return 6*M_PI*radius*nu;
    } else return ((9*M_PI/40*radius*radius*rho)*velocity).norme();
}

//method to add force
void Grains :: ajouteForce()
{
    force+= (((get_mass())*g + (lambda())*velocity));
}

//method to update the coordinates and velocity of the grain after a specified period of time
void Grains:: bouger(double temps)
{
    velocity += (((temps/(get_mass()))*(force + (get_mass())*g))-(lambda())*velocity);

    position += (temps*velocity);

    force= 0.0;
}

//method to display the grain's data
void Grains :: display()
{
    cout<<"Position: " 	<< position <<endl;
    cout<<"Velocity: " 	<< velocity <<endl;
    cout<<"Force: "		<< force 	<<endl;
    cout<<"Radius: "	<< radius 	<<", Volume: "<< get_volume()<<endl;
    cout<<"Mass: "		<< get_mass()<<endl;
}


//gravitational constant
Vecteur3D Grains :: get_g() const
{
    return Vecteur3D(0.0, 0.0, -9.81);
}
