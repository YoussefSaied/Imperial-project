#include <iostream>
#include "Systeme.h"
#include "SystemeP9.h"
#include "GrainLJ.h"
#include "GrainLJUn.h"
#include "GrainLJDeux.h"
#include "Medium.h"
#include "Vecteur3D.h"
#include "Plan.h"
#include <vector>
#include "SupportADessinTexte.h"
#include "Source.h"

using namespace std;


typedef Vecteur3D Position, Vitesse, Force;

int main()
{
    SupportADessinTexte ecran(cout); //TESTER CONSTRUCT PAR DEFAUT
    SystemeP9 systeme(&ecran);

    cout << "Au départ :" << endl;
    systeme.dessine();


    GrainLJUn grain_modele1(Position(1.0), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    systeme.ajouteGrain(grain_modele1);
    Source source(Position(0.5), grain_modele1, Vitesse(), 0, 0, 3.27, true );
    systeme.ajouteSource(source);

    cout << "Ajout grain et source :" << endl;
    systeme.dessine();


    GrainLJUn grainLJUn1(Position(), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    GrainLJUn grainLJUn2(Position(1.0), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    GrainLJUn grainLJUn3(Position(0.5, 0.866025, 0.0), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    GrainLJDeux grainLJDeux1(Position(0.5, 0.288675, 0.816497), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    Plan plan_obstacle(Position(0.0, 0.0, -0.9), Vecteur3D(0.0, 0.0, 1.0));
    Source source1(Position(0.5), grainLJUn3, Vitesse(), 0, 0, 3.27, true );
    systeme.ajouteGrain(grainLJUn1);
    systeme.ajouteGrain(grainLJUn2);
    systeme.ajouteGrain(grainLJUn3);
    systeme.ajouteGrain(grainLJDeux1);
    systeme.ajouteObstacle(plan_obstacle);
    systeme.ajouteSource(source1);

    cout << "Après :" << endl;
    systeme.dessine();

    systeme.evolue1(0.001);
    cout << "Après un pas de calcul :" << endl;
    systeme.dessine();

    systeme.evolue1(0.001,10);
    cout << "Après deux pas de calcul :" << endl;
    systeme.dessine();

   


    return 0;
}
