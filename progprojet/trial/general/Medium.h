#pragma once
#include <iostream>
#include "Vecteur3D.h"

class Medium{
public:
	// constructeurs
	Medium(double rho, double nu): rho(rho), nu(nu){}

	//methodes
	double Rho() const{ return rho ;}
	
	double Nu() const{ return nu; }
	
	void display() const { std :: cout<<"rho: "<<rho<<" nu: "<<nu<<std :: endl; }
	
protected:
	double rho;
	double nu;
};


// constantes du projet
static const Medium water(1.0, 1.0);
static const Medium air(1.3e-3, 1.8e-2);
static const Vecteur3D g(0.0, 0.0, -9.81e3);
static const double DistanceMax(100.);
