#include <iostream>
#include "SystemeP9.h"
#include "Systeme.h"
#include "GrainLJ.h"
#include "GrainLJUn.h"
#include "GrainLJDeux.h"
#include "Obstacle.h"
#include "Medium.h"
#include "Vecteur3D.h"
#include "Plan.h"
#include "Grain.h"
#include <vector>
#include "SupportADessinTexte.h"

using namespace std;

typedef Vecteur3D Position, Vitesse, Force;

int main()
{
    cout << "Bonjour! Ceci est un test de la classe SystemeP9!" << endl;
    cout << endl;

    cout << "Constructeur par défaut" << endl;
    cout << endl;

	SupportADessinTexte support(cout);
    SystemeP9 systeme(&support);
    cout << systeme << endl;

    GrainLJUn grainLJUn1(Position(), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    GrainLJUn grainLJUn2(Position(1.0), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    GrainLJUn grainLJUn3(Position(0.5, 0.866025, 0.0), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    GrainLJDeux grainLJDeux1(Position(0.5, 0.288675, 0.816497), Vitesse(), 1.0, 0.4, Vecteur3D(), air);

    Plan plan_obstacle(Position(0.0, 0.0, -0.9), Vecteur3D(0.0, 0.0, 1.0));

    systeme.ajouteGrain(grainLJUn1);
    systeme.ajouteGrain(grainLJUn2);
    systeme.ajouteGrain(grainLJUn3);
    systeme.ajouteGrain(grainLJDeux1);
    cout << systeme << endl;
    cout << endl;

    systeme.ajouteObstacle(plan_obstacle);
    cout << systeme << endl;
    cout << endl;

    systeme.evolue2(0.001);
    cout << systeme << endl;
    cout << endl;
    

    return 0;
}
