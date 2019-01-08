#include <iostream>
#include "Systeme.h"
#include "SystemeP9.h"
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

    systeme.evolue1(0.001);
    cout << "Après un pas de calcul :" << endl;
    systeme.dessine();

    systeme.evolue1(0.001,10);
    cout << "Après deux pas de calcul :" << endl;
    systeme.dessine();

    return 0;
}
