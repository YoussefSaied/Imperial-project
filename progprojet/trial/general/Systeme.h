#pragma once
#include <vector>
#include "Obstacle.h"
#include "GrainLJ.h"
#include "Source.h"
#include "Grain.h"
#include "GrainLJUn.h"
#include "GrainLJDeux.h"
#include <iostream>
#include "Dessinable.h"
#include <memory>
#include "Medium.h"
#include "SupportADessin.h"
#include "SupportADessinTexte.h"
#include "Vecteur3D.h"
#include "Mediumi.h"
#include "Sphere.h"
class Systeme: public Dessinable
{
    friend class VueOpenGL; //simple solution
public:

    // constructeurs et destructeurs
    Systeme(SupportADessin* support=&Texte1, Medium m = air):Dessinable(Position(),support),
												notre_Dalle(Vecteur3D(3,2.5,1),Vecteur3D(0,0,1),Vecteur3D(0,-1,0),10,10, true),ptr_medium(&m)
												{notre_Dalle.set_support(support);}

    virtual ~Systeme() {}


	// methodes


	virtual double evolue1(double dt=0.001)=0;

    virtual std:: ostream& display(std:: ostream& c) const = 0;

    virtual void ajouteGrain(Grain const& nouveau_grain) = 0 ;

    void ajouteObstacle(Obstacle const& nouveau_obstacle);

    void ajouteSource(Source const& nouvelle_source);

    void ajouteMediumi(Mediumi const& nouveau_mediumi);

    virtual std::unique_ptr<Systeme> copie() const =0;

    virtual std::unique_ptr<Systeme> P9toP12() const =0;

    virtual std::unique_ptr<Systeme> P12toP9() const =0;


		Dalle notre_Dalle;


protected:

    // delete
    Systeme (Systeme const&) = delete;


	// attributs
    std:: vector<std::unique_ptr<Obstacle>> tab_ptr_obstacles;
    std:: vector<std::unique_ptr<Source>> tab_ptr_sources;
    std:: vector<std::unique_ptr<Mediumi>> tab_ptr_mediums;
    Medium* ptr_medium;

};

//externe
std::ostream& operator<<(std::ostream& sortie, Systeme const& s);
