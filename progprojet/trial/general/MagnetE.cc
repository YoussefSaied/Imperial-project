#include "Magnet.h"
#include "Vecteur3D.h"
#include "Obstacle.h"
#include "MagnetE.h"
#include "Dessinable.h"
#include <cmath>
#include <memory>
using namespace std;

//method to initialize
MagnetE :: MagnetE(Position const& position, Vitesse const& vitesse, double masse_volumique, double rayon,
                   Vecteur3D const& force,  Medium medium,double height, Vecteur3D moment, SupportADessin* support):
    Magnet(position, support, vitesse, masse_volumique, rayon, force, medium, height, moment) {}


double MagnetE :: forceLJ(double x)
{
    double f(0);
    if (x <= 1.0) f = -1.0;
    else if(x < 2) f = (pow(x , 6.0) - 2.0)/pow(x , 13.0);
    else if(x >= 2) f = 0.0;
		//return f; previously :D :D :D :D :D :D
    return 0;
}

Vecteur3D MagnetE :: ajouteForce(unique_ptr<Magnet> const& Magnet2)
{
    Vecteur3D ecart(Magnet2->get_position() - position);
    Vecteur3D u(ecart.normalise());
    double d(radius + Magnet2->get_radius());
    if( ecart < d ) {
        position = Magnet2->get_position() - d*u;
        velocity -= (velocity*u)*u;
        return Vecteur3D(0.0,0.0,0.0);
    } else	{
        Vecteur3D x((24.0*epsilon  / pow(sigma , 2.0)) * forceLJ(1.09 + (ecart.norme()-d)/sigma ) * u );
        force+= x;
        return x;
    }
}

void MagnetE :: ajouteForce(unique_ptr<Obstacle> const& obstacle1)
{
    Vecteur3D e(obstacle1->PointPlusProche(position) - position);
    Vecteur3D u(e.normalise());
    double d(radius);
    /*if( e < d ) {
        position = obstacle1->PointPlusProche(position) - d*u;
        velocity -= (velocity*u)*u;
    } else	{
        force+= 2 * (24.0*epsilon  / pow(sigma , 2.0)) * forceLJ(1.09 + (e.norme()-d)/sigma ) * u ;
    }*/

}

void MagnetE :: ajouteForce(Vecteur3D const& vector1)
{
    force+=vector1;
}

unique_ptr<MagnetE> MagnetE:: cloneMe() const
{
    return unique_ptr<MagnetE>(new MagnetE(*this));
}

unique_ptr<Magnet> MagnetE:: copie() const
{
    return cloneMe();
}


//external
ostream& operator<<(ostream& c, MagnetE MagnetE)
{
    MagnetE.display(c);
    return c;
}
