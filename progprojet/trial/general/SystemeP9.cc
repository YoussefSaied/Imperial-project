#include "SystemeP9.h"
#include "Systeme.h"
#include <iostream>

using namespace std;


void SystemeP9:: addMagnet(Magnet const& nouveau_Magnet )
{
    // faire des tests de compatibilité
    tab_ptr_Magnets.push_back(nouveau_Magnet.copie());
    (*(tab_ptr_Magnets.back())).set_support(support);
}

ostream& SystemeP9:: display(ostream& c) const
{
    c << "System: " <<endl;
    c << tab_ptr_Magnets.size()<< " Magnets: ";

    for(auto const& ptr_Magnet : tab_ptr_Magnets) {
        (*ptr_Magnet).dessine();
    }
    c << tab_ptr_obstacles.size()<<"Obstacles: ";
    for(auto const& ptr_obstacle : tab_ptr_obstacles) {
        (*ptr_obstacle).dessine();
    }

    c<<endl;
    return c;
}

unique_ptr<SystemeP9> SystemeP9 :: cloneme() const
{
    unique_ptr<SystemeP9> P9(new SystemeP9(support));
    for(auto& g: tab_ptr_Magnets) {
        P9->addMagnet(*g);
    }
    for(auto& o : tab_ptr_obstacles) {
        P9->ajouteObstacle(*o);
    }

    return P9;
}

unique_ptr<Systeme> SystemeP9 ::copie() const
{
    return cloneme();
}

void SystemeP9:: evolue1(double dt)
{
    double newdt(dt);

    for(size_t i(0); i<tab_ptr_Magnets.size()-1; ++i) {
        //ext. field
//        tab_ptr_Magnets[i]->addTorque(H);

        for(size_t j(0); j<tab_ptr_Magnets.size(); ++j) {
        //magnet interactions
            tab_ptr_Magnets[i]->addTorque(tab_ptr_Magnets[j]);
        }
        // Magnet movement
        tab_ptr_Magnets[i]->move(dt);
    }// fin for Magnet

}

void SystemeP9:: evolue1(double dt, unsigned int nb_repet)
{
    for(unsigned int i(0); i<nb_repet; ++i) {
        evolue1(dt);
    }
}
