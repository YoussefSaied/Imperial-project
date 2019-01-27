#include "Systeme.h"
#include <iostream>
using namespace std;


void Systeme:: addObstacle(Obstacle const& nouveau_obstacle)
{
    // faire des tests de compatibilité
    tab_ptr_obstacles.push_back(nouveau_obstacle.copie());
    (*(tab_ptr_obstacles.back())).set_support(support);
}

// externe
ostream& operator << (ostream& sortie, Systeme const& systeme)
{
    systeme.display(sortie);
    return sortie;
}
