#pragma once
#include <vector>
#include "Obstacle.h"
#include <iostream>
#include "Dessinable.h"
#include <memory>
#include "SupportADessin.h"
#include "SupportADessinTexte.h"
#include "Vecteur3D.h"
#include "Systeme.h"
#include "Magnet.h"



class SystemeP9: public Systeme
{
    friend class VueOpenGL;
public:

    // constructeur et destructeur
    SystemeP9(SupportADessin * support, int selectmagnet = 0) : Systeme(support), selectedmagnet(selectedmagnet){ }

    SystemeP9(){ }

  virtual void dessine() const override {support->dessine(*this);}


	virtual void evolue1(double dt=0.001); //evolution du système selon le 1er algo avec les ameliorations le long du projet
	virtual void evolue1(double dt, unsigned int nb_repet); // evolution du système selon le 1er algo nb_repet fois

	void evolue2(double dt=0.001); // evolution du système selon le 2ème algo
	void evolue2(double dt, unsigned int nb_repet); // evolution du système selon le 2ème algo nb_repet fois

    virtual double evolue1(double dt = 0.001);      // evolution du système selon le 1er algo avec les ameliorations le long du projet
    void evolue1(double dt, unsigned int nb_repet); // evolution du système selon le 1er algo nb_repet fois

	virtual void addMagnet(Magnet const& nouveau_Magnet);


	// copie polymorphique du système
	std::unique_ptr<Systeme> copie() const;
	std::unique_ptr<SystemeP9> cloneme() const;

    /*// conversion des systèmes durant la simulation!
     * std::unique_ptr<SystemeP12> P9toP12s() const;
     * std::unique_ptr<Systeme> P12toP9()const{ std::cout<<" deja P9, mais bon.. "<<std::endl; return copie(); }
     * std::unique_ptr<Systeme> P9toP12() const;*/

    // copie polymorphique du système
    std::unique_ptr<Systeme> copie() const;
    std::unique_ptr<SystemeP9> cloneme() const;
    int selectedmagnet;

    /*void selected(int mn)
       {
       tab_ptr_Magnets[mn]->selected(1);
       tab_ptr_Magnets[selectedmagnet]->selected(0);
       selectedmagnet = mn;
       }*/

private:


    // deletes
    SystemeP9 (SystemeP9 const&) = delete;
    void operator = (SystemeP9 modele) = delete;
};

// externe
std::ostream& operator << (std::ostream& sortie, Systeme const& s);
