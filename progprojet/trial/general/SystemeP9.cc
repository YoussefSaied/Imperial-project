#include "SystemeP9.h"
#include "SystemeP12.h"
#include "Systeme.h"
#include <iostream>

using namespace std;


void SystemeP9:: addMagnet(Magnet const& nouveau_Magnet )
{
    // faire des tests de compatibilité
    tab_ptr_Magnets.push_back(nouveau_Magnet.copie());
    (*(tab_ptr_Magnets.back())).set_support(support);
    (*(tab_ptr_Magnets.back())).set_medium(*ptr_medium);
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


/*unique_ptr<SystemeP12> SystemeP9 :: P9toP12s() const
{
    unique_ptr<SystemeP12> P12(new SystemeP12(support));
    for(auto& g: tab_ptr_Magnets) {
        P12->addMagnet(*g);
    }
    for(auto& o : tab_ptr_obstacles) {
        P12->ajouteObstacle(*o);
    }
    for(auto& s : tab_ptr_sources) {
        P12->ajouteSource(*s);
    }
    for(auto& m : tab_ptr_mediums) {
        P12->ajouteMediumi(*m);
    }
    return P12;
}
unique_ptr<Systeme> SystemeP9 ::P9toP12() const
{
    cout<<"changement vers P12 :D "<<endl;
    return P9toP12s();
}*/
unique_ptr<SystemeP9> SystemeP9 :: cloneme() const
{
    unique_ptr<SystemeP9> P9(new SystemeP9(support));
    for(auto& g: tab_ptr_Magnets) {
        P9->addMagnet(*g);
    }
    for(auto& o : tab_ptr_obstacles) {
        P9->ajouteObstacle(*o);
    }

    for(auto& m : tab_ptr_mediums) {
        P9->ajouteMediumi(*m);
    }
    return P9;
}

unique_ptr<Systeme> SystemeP9 ::copie() const
{
    return cloneme();
}

double SystemeP9:: evolue1(Obstacle const& o, double dt)
{
    double newdt(dt);


    for(size_t i(0); i < tab_ptr_Magnets.size(); ++i) {
        bool inside(true);
        for(size_t j(0); j< tab_ptr_mediums.size(); ++j) {
            if(tab_ptr_mediums[j]->is_inside(*tab_ptr_Magnets[i])) inside = false;
        }
        if(inside)  (*(tab_ptr_Magnets[i])).set_medium(*ptr_medium);
    }


    for(size_t i(0); i<tab_ptr_Magnets.size(); ++i) {
        tab_ptr_Magnets[i]->Magnet::ajouteForce();
				for(auto const& ptr_obstacle : tab_ptr_obstacles) {
						tab_ptr_Magnets[i]->ajouteForce(ptr_obstacle);
				}// fin for auto obstacle
				tab_ptr_Magnets[i]->ajouteForce(o);
    }
    for(size_t i(0); i<tab_ptr_Magnets.size()-1; ++i) {


        for(size_t j(i+1); j<tab_ptr_Magnets.size(); ++j) {
            Vecteur3D force_oppose((tab_ptr_Magnets[i]->ajouteForce(tab_ptr_Magnets[j])).oppose());
            tab_ptr_Magnets[j]->ajouteForce(force_oppose);
        }// Magnet interne
        tab_ptr_Magnets[i]->bouger(dt);
        if ( (0.5 * tab_ptr_Magnets[i]->get_radius())/((tab_ptr_Magnets[i]->get_velocity()).norme())  < newdt )
            newdt = (0.5 * tab_ptr_Magnets[i]->get_radius())/((tab_ptr_Magnets[i]->get_velocity()).norme());

        if((tab_ptr_Magnets[i]->get_position()).norme()>DistanceMax) {
            tab_ptr_Magnets.erase(tab_ptr_Magnets.begin()+i); //est-ce que le Magnet cesse d'exister? pas bésoin de delete?
            i-=1;
        }
    }// fin for Magnet
		if(tab_ptr_Magnets.size() == 1) tab_ptr_Magnets[0]->bouger(dt);
		for(auto const& ptr_obstacle : tab_ptr_obstacles){
			ptr_obstacle->bouger(dt);
		}
    if(newdt == dt	) return newdt;
    if(newdt != dt and newdt >2.0/10000.0) {
        cout<<"### réadaptation de dt par " << newdt/dt //<<  au temps
            <<" --> dt devient "<< newdt <<endl;
    } else {
        newdt = 2.0/10000.0;
        if(newdt!= dt) cout<<"readaptation finale! "<<" --> dt devient "<< newdt <<endl;
    }
    return newdt;
}
double SystemeP9:: evolue1(double dt)
{
    double newdt(dt);


    for(size_t i(0); i < tab_ptr_Magnets.size(); ++i) {
        bool inside(true);
        for(size_t j(0); j< tab_ptr_mediums.size(); ++j) {
            if(tab_ptr_mediums[j]->is_inside(*tab_ptr_Magnets[i])) inside = false;
        }
        if(inside)  (*(tab_ptr_Magnets[i])).set_medium(*ptr_medium);
    }


    for(size_t i(0); i<tab_ptr_Magnets.size(); ++i) {
        tab_ptr_Magnets[i]->Magnet::ajouteForce();
				for(auto const& ptr_obstacle : tab_ptr_obstacles) {
						tab_ptr_Magnets[i]->ajouteForce(ptr_obstacle);
				}// fin for auto obstacle
    }
    for(size_t i(0); i<tab_ptr_Magnets.size()-1; ++i) {


        for(size_t j(i+1); j<tab_ptr_Magnets.size(); ++j) {
            Vecteur3D force_oppose((tab_ptr_Magnets[i]->ajouteForce(tab_ptr_Magnets[j])).oppose());
            tab_ptr_Magnets[j]->ajouteForce(force_oppose);
        }// Magnet interne
        tab_ptr_Magnets[i]->bouger(dt);
        if ( (0.5 * tab_ptr_Magnets[i]->get_radius())/((tab_ptr_Magnets[i]->get_velocity()).norme())  < newdt )
            newdt = (0.5 * tab_ptr_Magnets[i]->get_radius())/((tab_ptr_Magnets[i]->get_velocity()).norme());

        if((tab_ptr_Magnets[i]->get_position()).norme()>DistanceMax) {
            tab_ptr_Magnets.erase(tab_ptr_Magnets.begin()+i); //est-ce que le Magnet cesse d'exister? pas bésoin de delete?
            i-=1;
        }
    }// fin for Magnet
		if(tab_ptr_Magnets.size() == 1) tab_ptr_Magnets[0]->bouger(dt);
		for(auto const& ptr_obstacle : tab_ptr_obstacles){
			ptr_obstacle->bouger(dt);
		}
    if(newdt == dt	) return newdt;
    if(newdt != dt and newdt >2.0/10000.0) {
        cout<<"### réadaptation de dt par " << newdt/dt //<<  au temps
            <<" --> dt devient "<< newdt <<endl;
    } else {
        newdt = 2.0/10000.0;
        if(newdt!= dt) cout<<"readaptation finale! "<<" --> dt devient "<< newdt <<endl;
    }
    return newdt;
}

void SystemeP9:: evolue1(double dt, unsigned int nb_repet)
{
    for(unsigned int i(0); i<nb_repet; ++i) {
        evolue1(dt);
    }
}

void SystemeP9:: evolue2(double dt)
{
    for(size_t i(0); i<tab_ptr_Magnets.size(); ++i) {
        tab_ptr_Magnets[i]->Magnet::ajouteForce();

        for(auto const& ptr_obstacle : tab_ptr_obstacles) {
            tab_ptr_Magnets[i]->ajouteForce(ptr_obstacle);
        }// fin for auto obstacle

        for(size_t j(i); j<tab_ptr_Magnets.size(); ++j) {
            Vecteur3D force_oppose(tab_ptr_Magnets[i]->ajouteForce(tab_ptr_Magnets[j]));
            tab_ptr_Magnets[j]->ajouteForce(force_oppose);
        }// Magnet interne
    }// fin for Magnet

    for(size_t i(0); i<tab_ptr_Magnets.size(); ++i) {
        tab_ptr_Magnets[i]->Magnet::bouger(dt);
        if((tab_ptr_Magnets[i]->get_position()).norme()>DistanceMax) {
            tab_ptr_Magnets.erase(tab_ptr_Magnets.begin()+i); //est-ce que le Magnet cesse d'exister? pas bésoin de delete?
            i-=1;
        }
    }
}

void SystemeP9:: evolue2(double dt, unsigned int nb_repet)
{
    for(unsigned int i(0); i<nb_repet; ++i) {
        evolue2(dt);
    }
}
