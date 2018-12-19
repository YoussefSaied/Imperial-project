#include "Obstacle.h"
#include "Vecteur3D.h"
#include "Cylinder.h"
#include <iostream>
#include <cmath>
using namespace std;
//internes

Cylinder:: Cylinder(Position position, Vecteur3D vector1, double h, double r, bool m): Obstacle(position, m), hauteur(h), rayon(r)
{
    vecteur_1 = vector1.normalise();
}

Vecteur3D Cylinder :: PointPlusProche(Vecteur3D const& x_i) const
{
    double d(x_i * vecteur_1);
    Vecteur3D e(x_i-position);
    Vecteur3D en(d*vecteur_1);
    Vecteur3D n(en.normalise());
    Vecteur3D eu(e-en);
    Vecteur3D u(eu.normalise());
    if(d < hauteur/2) return position + d * vecteur_1 + rayon*u;
    return position + hauteur * n/2 + min(rayon,eu.norme()) * u;
}

ostream& Cylinder:: display (ostream& sortie) const
{
    sortie<<"Je suis un cylindre! " << vecteur_1<<endl;
    return sortie;
}

void Cylinder :: distancea(Vecteur3D vector1)const
{
    cout<<"distance à "<< vector1<< " : " << PointPlusProche(vector1);
}

unique_ptr<Cylinder> Cylinder:: cloneMe() const
{
    return unique_ptr<Cylinder>(new Cylinder(*this));
}

unique_ptr<Obstacle> Cylinder:: copie() const
{
    return cloneMe();
}

//externes

ostream& operator<<(ostream& sortie, Cylinder const& cyl1)
{
    cyl1.display(sortie);
    return sortie;
}
