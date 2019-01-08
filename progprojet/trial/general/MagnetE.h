#pragma once
#include "Magnet.h"
#include "Vecteur3D.h"
#include "Obstacle.h"
#include <cmath>
#include "Dessinable.h"
#include <memory>

class MagnetE : public Magnet
{
public:

    // constructeur et destructeur
    MagnetE(Position const& position, Vitesse const& vitesse,
            double masse_volumique, double rayon, Vecteur3D const& force = Vecteur3D(), Medium medium = water,double height = 1.0, Vecteur3D moment=Vecteur3D(1,0,0), SupportADessin* support = &Texte1);
    virtual ~MagnetE() {}

    //methodes
    virtual void dessine() const override { if (support != nullptr) support->dessine(*this); }

    static constexpr double epsilon = 25.0;

    static constexpr double sigma = 0.885;

	static double get_sigma(){return sigma;}

  	double forceLJ(double x);

    virtual Vecteur3D ajouteForce(std:: unique_ptr<Magnet> const& Magnet2) override;

    virtual void ajouteForce(std:: unique_ptr<Obstacle> const& obstacle1) override;

    virtual void ajouteForce(Vecteur3D const& vector1) override;

	std:: unique_ptr<MagnetE> cloneMe() const;

    virtual std::unique_ptr<Magnet> copie() const override;
		virtual void ajouteForce(Obstacle const& obstacle1){
			/*Vecteur3D e(obstacle1.PointPlusProche(position) - position);
			Vecteur3D u(e.normalise());
			double d(radius);
			if( e < d ) {
					position = obstacle1.PointPlusProche(position) - d*u;
					velocity -= (velocity*u)*u;
			} else	{
					force+= 2 * (24.0*epsilon  / pow(sigma , 2.0)) * forceLJ(1.09 + (e.norme()-d)/sigma ) * u ;
			}*/
		}
};

//external

std :: ostream& operator<<(std :: ostream& c, MagnetE g);
