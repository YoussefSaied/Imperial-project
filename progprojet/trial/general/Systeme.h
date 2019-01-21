#pragma once
#include <vector>
#include "Obstacle.h"
#include <iostream>
#include "Dessinable.h"
#include <memory>
#include "SupportADessin.h"
#include "SupportADessinTexte.h"
#include "Vecteur3D.h"
#include "Sphere.h"
#include "Dodec.h"
#include "Magnet.h"

class Systeme: public Dessinable
{
    friend class VueOpenGL; //simple solution
public:

    // constructeurs et destructeurs
    Systeme(SupportADessin* support=&Texte1):Dessinable(Position(),support),
												notre_Dalle(Vecteur3D(3,2.5,1),Vecteur3D(0,0,1),Vecteur3D(0,-1,0),0.1,0.1, true)
												{notre_Dalle.set_support(support);}

    virtual ~Systeme() {}


	// methodes


		virtual void evolue1(double dt=0.001) = 0;

    virtual std:: ostream& display(std:: ostream& c) const = 0;

    virtual void addMagnet(Magnet const& new_Magnet) = 0 ;

    void ajouteObstacle(Obstacle const& nouveau_obstacle);


    virtual std::unique_ptr<Systeme> copie() const =0;

    //virtual std::unique_ptr<Systeme> P9toP12() const =0;

    //virtual std::unique_ptr<Systeme> P12toP9() const =0;

		Dalle notre_Dalle;


protected:

    // delete
    Systeme (Systeme const&) = delete;


	// attributs
    std:: vector<std::unique_ptr<Obstacle>> tab_ptr_obstacles;

};

//externe
std::ostream& operator<<(std::ostream& sortie, Systeme const& s);
