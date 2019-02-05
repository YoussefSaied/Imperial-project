#pragma once
#define _USE_MATH_DEFINES
#include "Vecteur3D.h"
#include <iostream>
#include "Dessinable.h"
#include "SupportADessin.h"
#include "Obstacle.h"
#include <memory>
#include <cmath>

typedef Vecteur3D Position, Vitesse;

//Paula's magnet: charge = 2, radius = 0.75e-3, mass = 0.3e-3, length = 1.9e-2
class Magnet : public Dessinable
{
public:
    // constructeurs et destructeurs
    Magnet(Position const& position, Vecteur3D axis = Vecteur3D(0, 0, 1), double angle = 0.0001, double charge = 2,
      double mass = 0.3e-3,
      double radius = 0.75e-3, double length = 1.9e-2, bool selected = 0, double torque = 0, double oldtorque = 0,
      Vecteur3D Bfield = Vecteur3D(0, 0, 0), double omega = 0, int rotations = 0, double speed = 0,
      SupportADessin * support = &Texte1, double f = 1);
    virtual ~Magnet(){ }

    // derived attributes
    double inertia() const
    { return mass * length * length / 12; }

    double gamma() const
    { return f * inertia(); }

    // ACCELERATION
    double accel(double T, double W) const// angular acceleration
    { return (1 / inertia()) * (T - gamma() * W); }

    double torqueaccel(double T) const// angular acceleration
    { return (1 / inertia()) * T; }

    double dampingaccel(double W) const// angular acceleration
    { return (-1 / inertia()) * gamma() * W; }

    double displ_accel() const// angular acceleration
    { return (torque / inertia()) - (gamma() / inertia()) * omega; }

    // orientation attributes (unit vectors)
    Vecteur3D planevec1() const;
    Vecteur3D planevec2() const;

    Vecteur3D orientation() const
    { return planevec1() * cos(angle) + planevec2() * sin(angle); }

    Vecteur3D moment() const
    { return orientation() * chargeN() * length; }

    // ENERGY
    double Kinetic() const
    { return 0.5* inertia() * speed*speed; }

    // charge attibutes
    Vecteur3D positionN()
    { return position + orientation() * length / 2; }

    Vecteur3D positionS()
    { return position - orientation() * length / 2; }

    double chargeN() const
    { return charge; }

    double chargeS() const
    { return charge * -1; }

    // axis
    double get_axerheight() const { return radius * 6; }

    double get_axerradius() const { return length / 20; }

    void set_support(SupportADessin * s){ support = s; }

    double get_length() const { return length; }

    // CALC METHODS
    double torquecalc(Vecteur3D r, int chargeM2 = 1) const;

    virtual void addTorque(std::unique_ptr<Magnet> const& Magnet2);

    virtual void addnewTorque(std::unique_ptr<Magnet> const& Magnet2);

    virtual void addBfield(std::unique_ptr<Magnet> const& Magnet2);

    virtual void addpotBN(std::unique_ptr<Magnet> const& Magnet2);

    virtual void addpotBS(std::unique_ptr<Magnet> const& Magnet2);

    virtual void addpotB(std::unique_ptr<Magnet> const& Magnet2)
    {
      addpotBN(Magnet2);
      addpotBS(Magnet2);
    }
    double potB() const {return oldpotBN + oldpotBS;}

    virtual void addTorque(Vecteur3D extfield);

    virtual void addnewTorque(Vecteur3D extfield);

    virtual void addBfield(Vecteur3D extfield){ Bfield += extfield; }


    virtual void VerletBU(double delta_t);
    virtual void move(double delta_t);
    virtual void moveangle(double delta_t)
    {

        angle += delta_t * omega + 0.5 * delta_t * delta_t * accel(torque, omega);
        speed = omega + 0.5 * delta_t * delta_t * accel(torque, omega) * (length/2);
    }

    virtual void moveomega(double delta_t);

    virtual void dessine() const override { if (support != nullptr) { support->dessine(*this); } }


    // methodes


    // method to display the Magnet's data
    std :: ostream& display(std :: ostream& sortie) const;

    // copie polymorphique
    std:: unique_ptr<Magnet> cloneMe() const { return std::unique_ptr<Magnet>(new Magnet(*this)); }

    virtual std::unique_ptr<Magnet> copie() const { return cloneMe(); }

    double speed;
    double torque;
    double oldtorque;
    double newtorque;
    Vecteur3D Bfield;
    double radius;
    double length;
    double omega;
    double charge;
    double angle;
    double mass;
    Vecteur3D axis;
    int rotations;
    bool selected;
    double f;
    double potBN;
    double potBS;
    double oldpotBN;
    double oldpotBS;
};

/*for rotor model (separation >> length of magnets):
      solve 2nd order ODE for alpha with Verlet using a linear damping coef.
      approximate interactions to be exclusive to nearest neighbour
      determine nearest neighbour??
   for dumbbell model (separation ~ length of magnets):
      solve 2nd order ODE for alpha with Verlet using a linear damping coef.

   dumbbell model is probably easier to implement initially as it does not require
   us to find nearest neighbours, however computation might be slow
 */
