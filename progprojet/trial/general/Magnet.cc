#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include "Vecteur3D.h"
#include <cmath>
#include "Magnet.h"

using namespace std;
Magnet :: Magnet(Position const& position, Vecteur3D axis, double charge, double mass, double radius, double length,  bool selected, double torque, double oldtorque, Vecteur3D Bfield,
   double angle, double omega, int rotations,SupportADessin* support):
    Dessinable(position,support), axis(axis), torque(torque), Bfield(Bfield), oldtorque(oldtorque),radius(radius), length(length),mass(mass), angle(angle), omega(omega), rotations(rotations) {}


ostream& Magnet:: display(std :: ostream& c) const
{
    c << "Position: " << position << endl
      << "axis: " << axis << endl
      << "Rotations: " << rotations << endl
      << "Torque: " << oldtorque << endl
      << "acc: " << alpha() << endl
      << "Hamiltonian: " << Hamiltonian() << endl;
    return c;
}

// plane vectors -- don't need normalise but ok
Vecteur3D Magnet :: planevec1() const
{
    if (axis != Vecteur3D(1, 0, 0)) return (axis ^ Vecteur3D(1, 0, 0)).normalise();
    else return (axis ^ Vecteur3D(0, 1, 0)).normalise();
}

Vecteur3D Magnet :: planevec2() const
{
    return (axis ^ planevec1()).normalise();
}

// Torque from magnet2
void Magnet :: addTorque(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D rNN = Magnet2->positionN() - positionN(); // Npole i Npole j
    torque += ((length / 2) * 10e-7) * chargeN() * Magnet2->chargeN() * (orientation() ^ rNN).norme()
      / (rNN.norme() * rNN.norme() * rNN.norme());
    Vecteur3D rNS = Magnet2->positionS() - positionN(); // Npole i Spole j
    torque += ((length / 2) * 10e-7) * chargeN() * Magnet2->chargeS() * (orientation() ^ rNS).norme()
      / (rNS.norme() * rNS.norme() * rNS.norme());
    Vecteur3D rSN = Magnet2->positionN() - positionS(); // Spole i Npole j
    torque += ((length / 2) * 10e-7) * chargeS() * Magnet2->chargeN() * (orientation() ^ rSN).norme()
      / (rSN.norme() * rSN.norme() * rSN.norme());
    Vecteur3D rSS = Magnet2->positionS() - positionS();
    torque += ((length / 2) * 10e-7) * chargeS() * Magnet2->chargeS() * (-1 * orientation() ^ rSS).norme()
      / (rSS.norme() * rSS.norme() * rSS.norme());
}

void Magnet :: addTorque(Vecteur3D extfield)
{
    torque = (moment() ^ extfield).norme();
}

void Magnet :: move(double delta_t)
{
    angle += delta_t * omega + 1 / 2 * delta_t * delta_t * alpha();
    double zeta = (delta_t * gamma()) / (2 * inertia());
    omega     = (1 / (1 + zeta)) * (omega * (1 - zeta)) + (zeta / gamma()) * (oldtorque + torque);
    oldtorque = torque;
    torque    = 0.0;
    Bfield    = Vecteur3D(0, 0, 0);
}

void Magnet :: addBfield(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D rN = Magnet2->positionN() - position;
    Vecteur3D rS = Magnet2->positionS() - position;
    Bfield += 10e-7 * Magnet2->chargeN() * rN / (rN.norme() * rN.norme());
    Bfield += 10e-7 * Magnet2->chargeS() * rS / (rS.norme() * rS.norme());
}
