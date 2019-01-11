#pragma once
#include "MagnetE.h"
#include "Magnet.h"

class MagnetEO: public MagnetE
{
public:

	// constructeur et destructeur
    MagnetEO(Position const& position,
              double rayon, double height = 4.0,
							Vecteur3D moment1=Vecteur3D(1,0,0), Vecteur3D axer = Vecteur3D(0,1,0),
							//double axerheight = 4, double axerradius = 0.1,
							SupportADessin* support = &Texte1, Vecteur3D Torque=Vecteur3D(0,0,0),Vecteur3D omega=Vecteur3D(0,0,0),
							double masse_volumique=1.0, Medium medium = water,
							Vitesse const& vitesse=Vecteur3D(0,0,0),Vecteur3D const& force = Vecteur3D(0,0,0));
    virtual ~MagnetEO() {}


    //methodes
    virtual void dessine() const override { if (support != nullptr) support->dessine(*this); }

    std:: unique_ptr<MagnetEO> cloneMe() const { return std::unique_ptr<MagnetEO>(new MagnetEO(*this)); }

    virtual std::unique_ptr<Magnet> copie() const override { return cloneMe(); }

		//new getters

		Vecteur3D get_torque() const {return torque;}
		Vecteur3D get_omega() const {return omega;}
		Vecteur3D get_axer() const {return axer;}
		double get_axerheight() const {return radius*6;}
		double get_axerradius() const {return height/20;}

		//to be done:
		/*virtual bool bouger(double temps) override;

		virtual Vecteur3D addTorque(std:: unique_ptr<Magnet> const& Magnet2);

		virtual void addTorque(std:: unique_ptr<Obstacle> const& obstacle1);

		virtual void addTorque(Vecteur3D const& vector1) ;*/

		//attributs
		protected:

		Vecteur3D axer;
		Vecteur3D torque;
		Vecteur3D omega;
		/*double axerheight;
		double axerradius;*/

};
