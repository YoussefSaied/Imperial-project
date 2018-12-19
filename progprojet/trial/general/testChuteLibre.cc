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

using namespace std;

typedef Vecteur3D Position, Vitesse, Force;

int main()
{
	cout << "Teste chute libre!"<<endl;
	
    SystemeP9 systeme;
    GrainLJUn grainLJUn1(Position(10,10,10), Vitesse(0.0,0.0,0.0), 1.0, 0.4 , Vecteur3D(), air);
    systeme.ajouteGrain(grainLJUn1);

	cout << "J'evolue: algo 1 modifié dt=0.001"<<endl;
    systeme.evolue1(0.001);
    cout << systeme << endl;
    cout << endl;
    
    cout << "J'evolue: algo 1 modifié dt=0.001"<<endl;
    systeme.evolue1(0.001);
    cout << systeme << endl;
    cout << endl;
    
    cout << "J'evolue: algo 1 modifié après 10 pas de 0.001"<<endl;
    systeme.evolue1(0.001,10);
    cout << systeme << endl;
    cout << endl;
    

    return 0;
}
