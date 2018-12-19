#include "Source.h"
#include "SupportADessin.h"
#include "SupportADessinTexte.h"
using namespace std;

// constructeus

Source :: Source( Position const& position
                  ,Grain const& grain_modele
                  ,Vitesse v0_moyenne
                  ,double ecart_vitesse
                  ,double ecart_rayon
                  ,double debit
                  ,bool etat
                  ,SupportADessin* support
                ):
    Dessinable(position,support)
    ,ptr_grain_modele(grain_modele.copie())
    ,v0_moyenne(v0_moyenne)
    ,ecart_vitesse(ecart_vitesse)
    ,ecart_rayon(ecart_rayon)
    ,debit(debit)
    ,etat(etat)
{} //fin du constructeur

Source::  Source(Source const& source_modele):
    Dessinable(source_modele.position,support)
    ,ptr_grain_modele(source_modele.ptr_grain_modele->copie())
    ,v0_moyenne(source_modele.v0_moyenne)
    ,ecart_vitesse(source_modele.ecart_vitesse)
    ,ecart_rayon(source_modele.ecart_rayon)
    ,debit(source_modele.debit)
    ,etat(source_modele.etat)

{} //fin du constructeur de copie


// methodes

void Source:: creation (vector<unique_ptr<Grain>> & tab_ptr_grain, double dt) //unique ou à la c?
{
    Aleatoire generateur;
    double fraction(debit*dt); // fraction = debit "vrai", mais a priori non entier
    size_t nombre(fraction);      // partie entière
    fraction -= nombre;        // partie fractionnaire
    // on ajoute 1 au hasard, proportionnellement à la partie fractionnaire :
    if ( generateur.uniforme(0.0, 1.0) < fraction ) ++nombre; //size_t ou int? nombe changé, avant int

    if(etat) {
        for(size_t i(0); i<nombre; ++i) {
            unique_ptr<Grain> nouveau_grain(ptr_grain_modele->copie()); //césse d'exister après le for!
            nouveau_grain->set_velocity(generateur.gaussienne((v0_moyenne).get_x(),ecart_vitesse)
                                        , generateur.gaussienne((v0_moyenne).get_y(),ecart_vitesse)
                                        , generateur.gaussienne((v0_moyenne).get_z(),ecart_vitesse)); //transformé en une méthode
            nouveau_grain->set_radius(generateur.gaussienne(ptr_grain_modele->get_radius(),ecart_rayon));
            nouveau_grain->set_position(position);
            tab_ptr_grain.push_back(nouveau_grain->copie());
            (*(tab_ptr_grain.back())).set_support(support);

        }
    }
}

unique_ptr<Source> Source:: cloneMe() const
{
    return unique_ptr<Source>(new Source(*this));
}

unique_ptr<Source> Source::copie() const
{
    return cloneMe();
}

ostream& Source:: display(ostream &sortie) const
{
    sortie <<"Une Source avec "<<endl;
    sortie <<"Grain modèle : ";
    ptr_grain_modele->display(sortie);
    sortie <<"Position : "<<position<<endl;
    sortie <<"Vitesse moyenne initial : "<<v0_moyenne<<endl;
    sortie <<"Ecart type pour la vitesse : "<<ecart_vitesse<<endl;
    sortie <<"Ecart type pour le rayon : "<<ecart_rayon<<endl;
    sortie <<"Debit : "<<debit<<endl;
    sortie <<"État (1 'allumé' 0 'éteint') : "<<etat<<endl;
    return sortie;
}


// operateurs externes

ostream& operator<<(ostream &sortie, Source const& source)
{
    source.display(sortie);
    return sortie;
}
