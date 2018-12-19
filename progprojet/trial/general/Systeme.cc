#include "Systeme.h"
#include <iostream>
using namespace std;


void Systeme:: ajouteObstacle(Obstacle const& nouveau_obstacle)
{
// faire des tests de compatibilité
    tab_ptr_obstacles.push_back(nouveau_obstacle.copie());
    (*(tab_ptr_obstacles.back())).set_support(support);
}

void Systeme:: ajouteSource(Source const& nouvelle_source)
{
    // faire des tests de compatibilité
    tab_ptr_sources.push_back(nouvelle_source.copie());
    (*(tab_ptr_sources.back())).set_support(support);
}

void Systeme:: ajouteMediumi(Mediumi const& nouveau_mediumi){
	tab_ptr_mediums.push_back(nouveau_mediumi.cloneMe());
	(*(tab_ptr_mediums.back())).set_support(support);
}


// externe
ostream& operator<<(ostream& sortie, Systeme const& systeme)
{
    systeme.display(sortie);
    return sortie;
}
