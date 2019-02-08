#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include "Vecteur3D.h"
#include <cmath>
#include "Magnet.h"

using namespace std;
Magnet :: Magnet(Position const& position, Vecteur3D axis, bool movable, double angle,
  Vecteur3D polaraxis1, double charge, double mass, double radius, double length,
  bool selected, double torque, double newtorque, Vecteur3D Bfield,
  double omega, int rotations, SupportADessin * support, double f) :
    Dessinable(position, support), axis(axis.normalise()), movable(movable), angle(angle),
    charge(charge), mass(mass), radius(radius), length(length), selected(selected),
    torque(torque), oldtorque(0), newtorque(newtorque), Bfield(Bfield),
    omega(omega), rotations(rotations), f(f), potBN(0), potBS(0)
{
    if (polaraxis1 * axis == 0) { polaraxis = polaraxis1.normalise(); } else { polaraxis = planevec1(); }
}

ostream& Magnet:: display(std :: ostream& c) const
{
    c << "Fixed Attributes" << endl
      << "Position of centre: " << position << endl
      << "axis: " << axis << endl
      << "inertia: " << inertia() << endl
      << "gamma: " << gamma() << endl
      << endl
      << "Motion" << endl
      << "angle: " << std::fmod(angle, M_PI) << endl
      << "orientation: " << orientation() << endl
      << endl
      << "omega: " << omega << endl
      << endl
      << "Torque: " << torque << endl
      << "realTorque: " << displ_accel(newtorque, omega) * inertia() << endl
      << endl
      << "acc(T): " << torqueaccel(newtorque) << endl
      << "acc(W): " << dampingaccel(omega) << endl
      << "acc(T,W): " << displ_accel(newtorque, omega) << endl
      << endl
      << "Energy (*1e7)" << endl
      << "Kinetic Energy: " << Kinetic() * 1e7 << endl
      << "Potential Energy: " << (potBN + potBS) * 1e7 << endl;

    return c;
}

void Magnet :: reset()
{
    // reinitialise
    torque    = 0.0;
    newtorque = 0.0;
    Bfield    = Vecteur3D(0, 0, 0);
    potBN     = 0;
    potBS     = 0;
}

void Magnet :: resetnew()
{
    // reinitialise
    torque    = newtorque;
    newtorque = 0.0;
    Bfield    = Vecteur3D(0, 0, 0);
    potBN     = 0;
    potBS     = 0;
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
    return (axis ^ polaraxis).normalise();
}

// TORQUE
double Magnet :: torquecalc(Vecteur3D r, double chargeM2, double chargeM1) const
{
    double pow = 1e-7;
    return ((length / 2) * pow) * (chargeM2 * chargeM1)
           * (zaxis() * (orientation() ^ r)) / (r.norme() * r.norme() * r.norme());
}

// torque and torquecalc inconsistent I think; Oh I understand now, you take S and N relative vector positions into account and
// N is positive while S is negative. Wow how did we miss that :(
void Magnet :: addTorque(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D rNN = positionN() - Magnet2->positionN(); // Npole i Npole j
    Vecteur3D rNS = positionN() - Magnet2->positionS(); // Npole i Spole j
    Vecteur3D rSN = positionS() - Magnet2->positionN(); // Spole i Npole j
    Vecteur3D rSS = positionS() - Magnet2->positionS(); // Spole i Spole j

    torque += torquecalc(rNN, Magnet2->chargeN(), chargeN());
    torque += torquecalc(rNS, Magnet2->chargeS(), chargeN());
    // -= because S
    torque -= torquecalc(rSN, Magnet2->chargeN(), chargeS());
    torque -= torquecalc(rSS, Magnet2->chargeS(), chargeS());
}

void Magnet :: addnewTorque(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D rNN = positionN() - Magnet2->positionN(); // Npole i Npole j
    Vecteur3D rNS = positionN() - Magnet2->positionS(); // Npole i Spole j
    Vecteur3D rSN = positionS() - Magnet2->positionN(); // Spole i Npole j
    Vecteur3D rSS = positionS() - Magnet2->positionS(); // Spole i Spole j

    newtorque += torquecalc(rNN, Magnet2->chargeN(), chargeN());
    newtorque += torquecalc(rNS, Magnet2->chargeS(), chargeN());
    // -= because S
    newtorque -= torquecalc(rSN, Magnet2->chargeN(), chargeS());
    newtorque -= torquecalc(rSS, Magnet2->chargeS(), chargeS());
}

void Magnet :: addTorque(Vecteur3D extfield)
{
    double pow = 1e-7;
    torque += pow * zaxis() * (moment() ^ extfield);
}

void Magnet :: addnewTorque(Vecteur3D extfield)
{
    double pow = 1e-7;
    newtorque += pow * zaxis() * (moment() ^ extfield);
}

// MAGNETIC FIELD
void Magnet :: addpotBN(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D rN = Magnet2->positionN() - positionN();
    Vecteur3D rS = Magnet2->positionS() - positionN();
    potBN += 1e-7 * chargeN() * Magnet2->chargeN() / rN.norme();
    potBN += 1e-7 * chargeN() * Magnet2->chargeS() / rS.norme();
}

void Magnet :: addpotBS(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D rN = Magnet2->positionN() - positionS();
    Vecteur3D rS = Magnet2->positionS() - positionS();
    potBS += 1e-7 * chargeS() * Magnet2->chargeN() / rN.norme();
    potBS += 1e-7 * chargeS() * Magnet2->chargeS() / rS.norme();
}

// VERLET CALCULATIONS
void Magnet :: VerletBU(double delta_t)
{
    if (movable) { angle += delta_t * omega + 1 / 2 * delta_t * delta_t * accel(torque, omega); }
    double zeta = (delta_t * gamma()) / (2 * inertia());
    omega = (1 / (1 + zeta)) * ((omega * (1 - zeta)) + (delta_t / (2 * inertia())) * (oldtorque + torque));
}

void Magnet :: move(double delta_t) // works!!
{
    if (movable) {
        double omega_half = omega + 0.5 * delta_t * accel(oldtorque, omega);
        omega += 0.5 * delta_t * (torqueaccel(torque) + torqueaccel(oldtorque) + 2 * dampingaccel(omega_half));
        angle += delta_t * omega + 0.5 * delta_t * delta_t * accel(torque, omega);
    }
}

void Magnet :: moveomega(double delta_t)
{
    if (movable) {
        double omega_half = omega + 0.5 * delta_t * accel(torque, omega);
        omega += 0.5 * delta_t * (torqueaccel(torque) + torqueaccel(newtorque) + 2 * dampingaccel(omega_half));
    }
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
