#include <iostream>
#include "Source.h"
#include <vector>

using namespace std;

int main()
{
    cout << "Bonjour! Ceci est un test de la classe Source!" << endl;
    cout << endl;

    GrainLJUn grain_modele1(Position(1.0), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    GrainLJUn grain_modele2(Position(3.,5.,-2.), Vitesse(5.), 1, .6 );

    vector<unique_ptr<Grain>> tab_ptr_grain;

    Source source(Position(0.5), grain_modele2, Vitesse(10), 5, 4.5, 30.27, true );
    cout << "Source :" << endl;
    cout << source << endl;
    cout << endl;

    cout << "Grain modele : " << endl;
    cout << grain_modele2 << endl;
    cout << endl;

    cout << "On éteint la Source! :" << endl;
    source.off();
    cout << source << endl;
    cout << endl;

    cout << "On allume la Source! :" << endl;
    source.on();
    cout << source << endl;
    cout << endl;

    cout << "On dessine la Source! (affiche) :" << endl;
    source.dessine();
    cout << endl;

    cout << "Teste le constructeur de copie et on affiche la copie :" << endl;
    Source copie(source);
    cout<<copie;

    cout << "On crée des Grains! :" << endl;
    source.creation(tab_ptr_grain, 0.1);
    cout << "Grains crées :" << endl;
    for(auto const& grain : tab_ptr_grain) grain->display(cout);

    return 0;
}
