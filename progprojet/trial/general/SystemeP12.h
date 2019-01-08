#pragma once
#include <vector>
#include "Obstacle.h"
#include <iostream>
#include "Dessinable.h"
#include <memory>
#include "Medium.h"
#include "SupportADessin.h"
#include "SupportADessinTexte.h"
#include "Vecteur3D.h"
#include "Systeme.h"

class SystemeP12: public Systeme
{
    friend class VueOpenGL;
public:

    // constructeurs et destructeurs
    SystemeP12(SupportADessin* support);
    virtual ~SystemeP12 () {}



// operateurs

    std:: ostream& display(std:: ostream& c) const;

// methodes

    std::unique_ptr<SystemeP9> P12toP9s() const;
    std::unique_ptr<Systeme> P12toP9() const;
    std::unique_ptr<Systeme> P9toP12() const { std::cout<<"deja p12 mais.. "<<std::endl; return copie(); }
    std::unique_ptr<Systeme> copie() const;
    std::unique_ptr<SystemeP12> cloneme()const;

    virtual void dessine() const override { support->dessine(*this); }

    void vider();

	virtual double evolue1(double dt=0.001);


// manipulateurs

    void addMagnet(Magnet const& nouveau_Magnet);

private:
	// attributs
	std:: vector<std::vector<std::vector<std:: vector<std::unique_ptr<Magnet>> >>> tab_case;

	// deletes
	SystemeP12 (SystemeP12 const&) = delete;
	void operator=(SystemeP12 modele) = delete;

};
