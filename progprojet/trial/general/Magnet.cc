#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include "Vecteur3D.h"
#include <cmath>
#include "Magnet.h"

using namespace std;
Magnet :: Magnet(Position const& position, Vecteur3D axis, bool movable, double angle,
  double charge, double mass, double radius, double length,
  bool selected, double torque, double oldtorque, Vecteur3D Bfield,
  double omega, int rotations, SupportADessin * support, double f) :
    Dessinable(position, support), angle(angle), movable(movable), axis(axis.normalise()),
    charge(charge), mass(mass), radius(radius), length(length), selected(selected),
    torque(torque), oldtorque(oldtorque), newtorque(oldtorque), Bfield(Bfield),
    omega(omega), rotations(rotations), f(f), potBN(0), potBS(0), oldpotBN(0), oldpotBS(0){ }


ostream& Magnet:: display(std :: ostream& c) const
{
    c << "Position: " << position << endl
      << "axis: " << axis << endl
      << "omega: " << omega << endl
 //  << "Torque: " << oldtorque << endl
      << "realTorque: " << displ_accel() * inertia() << endl
      << "acc: " << displ_accel() << endl
      << "angle: " << std::fmod(angle, 2 * M_PI) << endl
      << "orientation: " << orientation() << endl
      << "inertia: " << inertia() << endl
      << "gamma: " << gamma() << endl
      << "Hamiltonian: " << Hamiltonian() << endl;

    return c;
}

// plane vectors
Vecteur3D Magnet :: planevec1() const
{
    if (axis != Vecteur3D(1, 0, 0)) { return (axis ^ Vecteur3D(1, 0, 0)).normalise(); } else {
        return (axis ^ Vecteur3D(0, 1, 0)).normalise();
    }
}

Vecteur3D Magnet :: planevec2() const
{
    return (axis ^ planevec1()).normalise();
}

// TORQUE
double Magnet :: torquecalc(Vecteur3D r, double chargeM2) const
{
    double pow = 1e-7;
    return ((length / 2) * pow) * -1 * chargeM2 * charge * (axis * (orientation() ^ r))
           / (r.norme() * r.norme() * r.norme());
}

void Magnet :: addTorque(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D rNN = (Magnet2->positionN() - positionN()); // Npole i Npole j
    Vecteur3D rNS = (Magnet2->positionS() - positionN()); // Npole i Spole j
    Vecteur3D rSN = (Magnet2->positionN() - positionS()); // Spole i Npole j
    Vecteur3D rSS = (Magnet2->positionS() - positionS()); // Spole i Spole j

    torque += torquecalc(rNN, Magnet2->chargeN());
    torque += torquecalc(rNS, Magnet2->chargeS());
    torque += torquecalc(rSN, Magnet2->chargeN());
    torque += torquecalc(rSS, Magnet2->chargeS());
}

void Magnet :: addnewTorque(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D rNN = (Magnet2->positionN() - positionN()); // Npole i Npole j
    Vecteur3D rNS = (Magnet2->positionS() - positionN()); // Npole i Spole j
    Vecteur3D rSN = (Magnet2->positionN() - positionS()); // Spole i Npole j
    Vecteur3D rSS = (Magnet2->positionS() - positionS()); // Spole i Spole j

    newtorque += torquecalc(rNN, 1);
    newtorque += torquecalc(rNS, -1);
    newtorque += torquecalc(rSN, 1);
    newtorque += torquecalc(rSS, -1);
}

void Magnet :: addTorque(Vecteur3D extfield)
{
    // again consistency
    torque += axis * (moment() ^ extfield);
}

void Magnet :: addnewTorque(Vecteur3D extfield)
{
    // again consistency
    newtorque += axis * (moment() ^ extfield);
}

// MAGNETIC FIELD
void Magnet :: addpotBN(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D rN = Magnet2->positionN() - positionN();
    Vecteur3D rS = Magnet2->positionS() - positionN();
    potBN -= 1e-7 * chargeN() * Magnet2->chargeN() / rN.norme();
    potBN -= 1e-7 * chargeN() * Magnet2->chargeS() / rS.norme();
}

void Magnet :: addpotBS(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D rN = Magnet2->positionN() - positionS();
    Vecteur3D rS = Magnet2->positionS() - positionS();
    potBS -= 1e-7 * chargeS() * Magnet2->chargeN() / rN.norme();
    potBS -= 1e-7 * chargeS() * Magnet2->chargeS() / rS.norme();
}

// VERLET CALCULATIONS

void Magnet :: VerletBU(double delta_t)
{
    if (movable) { angle += delta_t * omega + 1 / 2 * delta_t * delta_t * accel(torque, omega); }
    double zeta = (delta_t * gamma()) / (2 * inertia());
    omega     = (1 / (1 + zeta)) * ((omega * (1 - zeta)) + (delta_t / (2 * inertia())) * (oldtorque + torque));
    oldtorque = torque;
    torque    = 0.0;
    Bfield    = Vecteur3D(0, 0, 0);
    potBN     = 0;
    potBS     = 0;
}

void Magnet :: move(double delta_t) // works!!
{
    double omega_half = omega + 0.5 * delta_t * accel(oldtorque, omega);
    omega += 0.5 * delta_t * (torqueaccel(torque) + torqueaccel(oldtorque) + 2 * dampingaccel(omega_half));
    angle += delta_t * omega + 0.5 * delta_t * delta_t * accel(torque, omega);

    // reinitialise
    oldtorque = torque;
    torque    = 0.0;
    Bfield    = Vecteur3D(0, 0, 0);
    potBN     = 0;
    potBS     = 0;
}

void Magnet :: moveomega(double delta_t)
{
    double omega_half = omega + 0.5 * delta_t * accel(torque, omega);
    omega += 0.5 * delta_t * (torqueaccel(torque) + torqueaccel(newtorque) + 2 * dampingaccel(omega_half));

    // reinitialise
    torque    = 0.0;
    newtorque = 0.0;
    Bfield    = Vecteur3D(0, 0, 0);
    oldpotBN  = potBN;
    oldpotBS  = potBS;
    potBN     = 0;
    potBS     = 0;
}

void Magnet :: addBfield(unique_ptr<Magnet> const& Magnet2)
{
    // for consistency maybe use the same model as addforce even beter would be
    // having addBfieldN and addBfieldS and use these in addforce
    Vecteur3D rN = Magnet2->positionN() - position;
    Vecteur3D rS = Magnet2->positionS() - position;
    Bfield += 1e-7 * Magnet2->chargeN() * rN / (rN.norme() * rN.norme() * rN.norme());
    Bfield += 1e-7 * Magnet2->chargeS() * rS / (rS.norme() * rS.norme() * rS.norme());
}
