#pragma once
#include "Vecteur3D.h"
#include "Grain.h"
#include <vector>
#include "Aleatoire.h"
#include "GrainLJ.h"
#include "GrainLJUn.h"
#include "GrainLJDeux.h"
#include "Dessinable.h"
#include "SupportADessin.h"
#include "SupportADessinTexte.h"
#include <memory>
typedef Vecteur3D Position, Vitesse;

class Source : public Dessinable
{
public:
    // constructeurs et destructeurs
    Source( Position const& position
            ,Grain const& grain_modele
            ,Vitesse v0_moyenne
            ,double ecart_vitesse
            ,double ecart_rayon
            ,double debit
            ,bool etat=true
            ,SupportADessin* support = &Texte1
          );

    Source(const Source& source_modele);

    virtual ~Source() {}


    // méthodes pour modifier l'état de la source.
    void on()
    {
        (*this).etat=true;
    }
    void off()
    {
        (*this).etat=false;
    }


    //autres méthodes

    void creation (std::vector<std::unique_ptr<Grain>> & tab_ptr_grain, double dt); // methodes qui crér les grains

    virtual std:: ostream& display(std:: ostream &sortie) const;

    virtual void dessine() const override { if (support != nullptr) support->dessine(*this); }

    void set_support(SupportADessin* s) { support = s; }

	std::unique_ptr<Source> cloneMe() const;

	std::unique_ptr<Source> copie() const;


private:
    std::unique_ptr<Grain> ptr_grain_modele;
    Vitesse v0_moyenne;
    double ecart_vitesse;
    double ecart_rayon;
    double debit;
    bool etat; // true "allumé" false "éteint"

};

// operateurs externes
std::ostream& operator<<(std::ostream& sortie, Source const& source);
