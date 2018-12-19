#pragma once
#include "Vecteur3D.h"
#include <iostream>

static const Vecteur3D g(0.0, 0.0, -9.81);


class Grains{

	public:
	// constructeurs
	Grains(Vecteur3D p, Vecteur3D v, Vecteur3D f, double d, double r);

	//set medium constants
	void set_medium(bool medium);

	//method to get the value of the volume of the grain
	double get_volume() const;

	//method to get the value of the mass of the grain
	double get_mass()const;

	//method to get the value of the coefficient lambda
	double lambda()const;

	//method to add force
	void ajouteForce();

	//method to update the coordinates and velocity of the grain after a specified period of time
	void bouger(double temps);

	//method to display the grain's data
	void display();


	private:
	Vecteur3D position;
	Vecteur3D velocity;
	Vecteur3D force;
	double massvolumique;
	double radius;
	bool medium = true; //1 for water, 0 for air
	
	//density of the medium
	static double constexpr rho1 = 1.3; //water
	static double constexpr rho0 = 1000.0; //air
	
	//viscosity of the medium
	static double constexpr nu1 = 0.000018; //water
	static double constexpr nu0 = 0.001; //air
	
	//gravitational constant as a method
	Vecteur3D get_g() const;
};
