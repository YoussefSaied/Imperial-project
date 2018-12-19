#include "Grain.h"
#include "Vecteur3D.h"
#include "Obstacle.h"
#include "GrainLJ.h"
#include "Dessinable.h"
#include <cmath>
#include <memory>
using namespace std;

//method to initialize
GrainLJ :: GrainLJ(Position const& position, Vitesse const& vitesse, double masse_volumique, double rayon,
                   Vecteur3D const& force,  Medium medium, SupportADessin* support):
    Grain(position, support, vitesse, masse_volumique, rayon, force, medium) {}


double GrainLJ :: forceLJ(double x)
{
    double f(0);
    if (x <= 1.0) f = -1.0;
    else if(x < 2) f = (pow(x , 6.0) - 2.0)/pow(x , 13.0);
    else if(x >= 2) f = 0.0;
    return f;
}

Vecteur3D GrainLJ :: ajouteForce(unique_ptr<Grain> const& grain2)
{
    Vecteur3D ecart(grain2->get_position() - position);
    Vecteur3D u(ecart.normalise());
    double d(radius + grain2->get_radius());
    if( ecart < d ) {
        position = grain2->get_position() - d*u;
        velocity -= (velocity*u)*u;
        return Vecteur3D(0.0,0.0,0.0);
    } else	{
        Vecteur3D x((24.0*epsilon  / pow(sigma , 2.0)) * forceLJ(1.09 + (ecart.norme()-d)/sigma ) * u );
        force+= x;
        return x;
    }
}

void GrainLJ :: ajouteForce(unique_ptr<Obstacle> const& obstacle1)
{
    Vecteur3D e(obstacle1->PointPlusProche(position) - position);
    Vecteur3D u(e.normalise());
    double d(radius);
    if( e < d ) {
        position = obstacle1->PointPlusProche(position) - d*u;
        velocity -= (velocity*u)*u;
    } else	{
        force+= 2 * (24.0*epsilon  / pow(sigma , 2.0)) * forceLJ(1.09 + (e.norme()-d)/sigma ) * u ;
    }
}

void GrainLJ :: ajouteForce(Vecteur3D const& vector1)
{
    force+=vector1;
}

unique_ptr<GrainLJ> GrainLJ:: cloneMe() const
{
    return unique_ptr<GrainLJ>(new GrainLJ(*this));
}

unique_ptr<Grain> GrainLJ:: copie() const
{
    return cloneMe();
}


//external
ostream& operator<<(ostream& c, GrainLJ grainLJ)
{
    grainLJ.display(c);
    return c;
}
