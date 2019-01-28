<<<<<<< HEAD
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include "Vecteur3D.h"
#include <cmath>
#include "Magnet.h"

using namespace std;
Magnet :: Magnet(Position const& position, Vecteur3D axis, double angle,
  double charge, double mass, double radius, double length,
  bool selected, double torque, double oldtorque, Vecteur3D Bfield,
  double omega, int rotations, SupportADessin * support, double f) :
    Dessinable(position, support), axis(axis.normalise()), torque(torque), Bfield(Bfield), oldtorque(oldtorque), radius(
        radius),
    length(length), charge(charge), mass(mass), angle(angle), omega(omega), rotations(rotations), f(f), potBN(0),potBS(0) { }


ostream& Magnet:: display(std :: ostream& c) const
{
    c << "Position: " << position << endl
      << "axis: " << axis << endl
      << "posN: " << positionN() << endl
      << "posS: " << positionS() << endl
      << "omega: " << omega << endl
      << "Torque: " << oldtorque << endl
      << "realTorque: " << displ_alpha() * inertia() << endl
      << "acc: " << displ_alpha() << endl
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
    if (axis != Vecteur3D(1, 0, 0))
    {return (axis ^ Vecteur3D(1, 0, 0)).normalise();}
    else {return (axis ^ Vecteur3D(0, 1, 0)).normalise();}
}

Vecteur3D Magnet :: planevec2() const
{
    return (axis ^ planevec1()).normalise();
}

// Torque from magnet2
void Magnet :: addTorqueN(unique_ptr<Magnet> const& Magnet2)

{
    double pow    = 1e-7;
    Vecteur3D rN = -1 * (Magnet2->positionN() - positionN()); // Npole i Npole j
    Vecteur3D rS = -1 * (Magnet2->positionS() - positionN()); // Npole i Spole j

    torque += ((length / 2) * pow) * (chargeN() * Magnet2->chargeN()) * (axis * (orientation() ^ rN))
      / (rN.norme() * rN.norme() * rN.norme());
    torque += ((length / 2) * pow) * chargeN() * Magnet2->chargeS() * (axis * (orientation() ^ rS))
      / (rS.norme() * rS.norme() * rS.norme());
}
void Magnet :: addTorqueS(unique_ptr<Magnet> const& Magnet2)
{
    double pow    = 1e-7;
    Vecteur3D rN = -1 * (Magnet2->positionN() - positionS()); // Spole i Npole j
    Vecteur3D rS = -1 * (Magnet2->positionS() - positionS()); // Spole i Spole j

    torque += ((length / 2) * pow) * chargeS() * Magnet2->chargeN() * (axis * (-1 * orientation() ^ rN))
      / (rN.norme() * rN.norme() * rN.norme());
    torque += ((length / 2) * pow) * chargeS() * Magnet2->chargeS() * (axis * (-1 * orientation() ^ rS))
      / (rS.norme() * rS.norme() * rS.norme());
}
void Magnet :: addpotBN(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D rN = Magnet2->positionN() - positionN();
    Vecteur3D rS = Magnet2->positionS() - positionN();
    potBN -= 1e-7 * Magnet2->chargeN() / rN.norme() ;
    potBN -= 1e-7 * Magnet2->chargeS() / rS.norme();
}
void Magnet :: addpotBS(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D rN = Magnet2->positionN() - positionS();
    Vecteur3D rS = Magnet2->positionS() - positionS();
    potBS -= 1e-7 * Magnet2->chargeN() / rN.norme() ;
    potBS -= 1e-7 * Magnet2->chargeS() / rS.norme();
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

void Magnet :: addTorque(Vecteur3D extfield)
{
    // again consistency
    torque += axis * (moment() ^ extfield);
}

void Magnet :: move(double delta_t)
{
    angle += delta_t * omega + 1 / 2 * delta_t * delta_t * alpha(torque,omega);
    double zeta = (delta_t * gamma()) / (2 * inertia());
    omega     = (1 / (1 + zeta)) * ((omega * (1 - zeta)) + (delta_t / (2 * inertia())) * (oldtorque + torque));
    oldtorque = torque;
    torque    = 0.0;
    Bfield    = Vecteur3D(0, 0, 0);
    potBN = 0;
    potBS = 0;
}
/*
void Magnet :: move(double delta_t)
{
    angle += delta_t * omega + 0.5 * delta_t * delta_t * alpha(torque, omega);

    double omega_half = omega + 0.5*delta_t*alpha(torque, omega);
    omega += 0.5*delta_t*(alpha1(torque) + alpha1(oldtorque) + alpha2(omega_half));

    //reinitialise
    oldtorque = torque;
    torque    = 0.0;
    Bfield    = Vecteur3D(0, 0, 0);
    potBN     = 0;
    potBS     = 0;
}
*/
=======
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include "Vecteur3D.h"
#include <cmath>
#include "Magnet.h"

using namespace std;
Magnet :: Magnet(Position const& position, Vecteur3D axis, double angle,
  double charge, double mass, double radius, double length,
  bool selected, double torque, double oldtorque, Vecteur3D Bfield,
  double omega, int rotations, SupportADessin * support, double f) :
    Dessinable(position, support), axis(axis.normalise()), torque(torque), Bfield(Bfield), newtorque(oldtorque),
    oldtorque(oldtorque), radius(radius), length(length), charge(charge), mass(mass), angle(angle),
    omega(omega), rotations(rotations), f(f), potBN(0), potBS(0), oldpotBN(0), oldpotBS(0){ }


ostream& Magnet:: display(std :: ostream& c) const
{
    c << "Position: " << position << endl
      << "axis: " << axis << endl
      << "omega: " << omega << endl
 //  << "Torque: " << oldtorque << endl
      << "realTorque: " << displ_alpha() * inertia() << endl
      << "acc: " << displ_alpha() << endl
      << "angle: " << std::fmod(angle, 2 * M_PI) << endl
      << "orientation: " << orientation() << endl
      << "inertia: " << inertia() << endl
      << "gamma: " << gamma() << endl
      << "Hamiltonian: " << Hamiltonian() << endl;

    return c;
}

// plane vectors -- don't need normalise but ok
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

// Torque from magnet2
void Magnet :: addTorque(unique_ptr<Magnet> const& Magnet2)

{
    double pow    = 1e-7;
    Vecteur3D rNN = -1 * (Magnet2->positionN() - positionN()); // Npole i Npole j
    torque += ((length / 2) * pow) * chargeN() * Magnet2->chargeN() * (axis * (orientation() ^ rNN))
      / (rNN.norme() * rNN.norme() * rNN.norme());
    Vecteur3D rNS = -1 * (Magnet2->positionS() - positionN()); // Npole i Spole j
    torque += ((length / 2) * pow) * chargeN() * Magnet2->chargeS() * (axis * (orientation() ^ rNS))
      / (rNS.norme() * rNS.norme() * rNS.norme());

    Vecteur3D rSN = -1 * (Magnet2->positionN() - positionS()); // Spole i Npole j
    torque += ((length / 2) * pow) * chargeS() * Magnet2->chargeN() * (axis * (-1 * orientation() ^ rSN))
      / (rSN.norme() * rSN.norme() * rSN.norme());

    Vecteur3D rSS = -1 * (Magnet2->positionS() - positionS()); // Spole i Spole j
    torque += ((length / 2) * pow) * chargeS() * Magnet2->chargeS() * (axis * (-1 * orientation() ^ rSS))
      / (rSS.norme() * rSS.norme() * rSS.norme());
}

void Magnet :: addnewTorque(unique_ptr<Magnet> const& Magnet2)

{
    double pow    = 1e-7;
    Vecteur3D rNN = -1 * (Magnet2->positionN() - positionN()); // Npole i Npole j
    newtorque += ((length / 2) * pow) * chargeN() * Magnet2->chargeN() * (axis * (orientation() ^ rNN))
      / (rNN.norme() * rNN.norme() * rNN.norme());
    Vecteur3D rNS = -1 * (Magnet2->positionS() - positionN()); // Npole i Spole j
    newtorque += ((length / 2) * pow) * chargeN() * Magnet2->chargeS() * (axis * (orientation() ^ rNS))
      / (rNS.norme() * rNS.norme() * rNS.norme());

    Vecteur3D rSN = -1 * (Magnet2->positionN() - positionS()); // Spole i Npole j
    newtorque += ((length / 2) * pow) * chargeS() * Magnet2->chargeN() * (axis * (-1 * orientation() ^ rSN))
      / (rSN.norme() * rSN.norme() * rSN.norme());

    Vecteur3D rSS = -1 * (Magnet2->positionS() - positionS()); // Spole i Spole j
    newtorque += ((length / 2) * pow) * chargeS() * Magnet2->chargeS() * (axis * (-1 * orientation() ^ rSS))
      / (rSS.norme() * rSS.norme() * rSS.norme());
}

void Magnet :: addpotBN(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D rN = Magnet2->positionN() - positionN();
    Vecteur3D rS = Magnet2->positionS() - positionN();
    potBN -= 1e-7 * Magnet2->chargeN() / rN.norme();
    potBN -= 1e-7 * Magnet2->chargeS() / rS.norme();
}

void Magnet :: addpotBS(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D rN = Magnet2->positionN() - positionS();
    Vecteur3D rS = Magnet2->positionS() - positionS();
    potBS -= 1e-7 * Magnet2->chargeN() / rN.norme();
    potBS -= 1e-7 * Magnet2->chargeS() / rS.norme();
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

/*
   void Magnet :: move(double delta_t)
   {
    angle += delta_t * omega + 1 / 2 * delta_t * delta_t * alpha();
    double zeta = (delta_t * gamma()) / (2 * inertia());
    omega     = (1 / (1 + zeta)) * ((omega * (1 - zeta)) + (delta_t / (2 * inertia())) * (oldtorque + torque));
    oldtorque = torque;
    torque    = 0.0;
    Bfield    = Vecteur3D(0, 0, 0);
    potBN = 0;
    potBS = 0;
   }
 */
void Magnet :: move(double delta_t)
{
    // angle += delta_t * omega + 0.5 * delta_t * delta_t * alpha(torque, omega);              // theta_(n+1)
    double omega_half = omega + 0.5 * delta_t * alpha(torque, omega);                       // omega_(n+05)
    omega += 0.5 * delta_t * (alpha1(torque) + alpha1(newtorque) + 2 * alpha2(omega_half)); // here should be "newtorque" instead of oldtorque
    // or we could use oldangle
    oldtorque = torque; // oldtorque should never be used in algo
    torque    = 0.0;
    newtorque = 0.0;
    Bfield    = Vecteur3D(0, 0, 0);
    oldpotBN  = potBN;
    oldpotBS  = potBS;
    potBN     = 0;
    potBS     = 0;
}
>>>>>>> e8d138e39a7dd0bc76db60c4fbacc569b55aaaec
