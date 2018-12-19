#include "SystemeP9.h"
#include "SystemeP12.h"
#include "Systeme.h"
#include <iostream>

using namespace std;


void SystemeP9:: ajouteGrain(Grain const& nouveau_grain )
{
    // faire des tests de compatibilité
    tab_ptr_grains.push_back(nouveau_grain.copie());
    (*(tab_ptr_grains.back())).set_support(support);
    (*(tab_ptr_grains.back())).set_medium(*ptr_medium);
}

ostream& SystemeP9:: display(ostream& c) const
{
    c << "Je suis un systeme avec : " <<endl;
    c << tab_ptr_grains.size()<< " grains ";
    if(tab_ptr_grains.size()!=0) {
        c<<",les suivants : "<<endl;
    }
    for(auto const& ptr_grain : tab_ptr_grains) {
        (*ptr_grain).dessine();
    }
    c << tab_ptr_obstacles.size()<<" obstacles ";
    if(tab_ptr_obstacles.size()!=0) {
        c<<",les suivants : "<<endl;
    }
    for(auto const& ptr_obstacle : tab_ptr_obstacles) {
        (*ptr_obstacle).dessine();
    }
    c << tab_ptr_sources.size()<<" sources ";
    if(tab_ptr_sources.size()!=0) {
        c<<",les suivantes : "<<endl;
    }
    for(auto const& ptr_source : tab_ptr_sources) {
        (*ptr_source).dessine();
    }
    c<<endl;
    return c;
}


unique_ptr<SystemeP12> SystemeP9 :: P9toP12s() const
{
    unique_ptr<SystemeP12> P12(new SystemeP12(support));
    for(auto& g: tab_ptr_grains) {
        P12->ajouteGrain(*g);
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
}
unique_ptr<SystemeP9> SystemeP9 :: cloneme() const
{
    unique_ptr<SystemeP9> P9(new SystemeP9(support));
    for(auto& g: tab_ptr_grains) {
        P9->ajouteGrain(*g);
    }
    for(auto& o : tab_ptr_obstacles) {
        P9->ajouteObstacle(*o);
    }
    for(auto& s : tab_ptr_sources) {
        P9->ajouteSource(*s);
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


    for(size_t i(0); i < tab_ptr_grains.size(); ++i) {
        bool inside(true);
        for(size_t j(0); j< tab_ptr_mediums.size(); ++j) {
            if(tab_ptr_mediums[j]->is_inside(*tab_ptr_grains[i])) inside = false;
        }
        if(inside)  (*(tab_ptr_grains[i])).set_medium(*ptr_medium);
    }

    for(size_t i(0); i<tab_ptr_sources.size(); ++i) {
        tab_ptr_sources[i]->creation(tab_ptr_grains, newdt);
    }
    for(size_t i(0); i<tab_ptr_grains.size(); ++i) {
        tab_ptr_grains[i]->Grain::ajouteForce();
				for(auto const& ptr_obstacle : tab_ptr_obstacles) {
						tab_ptr_grains[i]->ajouteForce(ptr_obstacle);
				}// fin for auto obstacle
				tab_ptr_grains[i]->ajouteForce(o);
    }
    for(size_t i(0); i<tab_ptr_grains.size()-1; ++i) {


        for(size_t j(i+1); j<tab_ptr_grains.size(); ++j) {
            Vecteur3D force_oppose((tab_ptr_grains[i]->ajouteForce(tab_ptr_grains[j])).oppose());
            tab_ptr_grains[j]->ajouteForce(force_oppose);
        }// grain interne
        tab_ptr_grains[i]->bouger(dt);
        if ( (0.5 * tab_ptr_grains[i]->get_radius())/((tab_ptr_grains[i]->get_velocity()).norme())  < newdt )
            newdt = (0.5 * tab_ptr_grains[i]->get_radius())/((tab_ptr_grains[i]->get_velocity()).norme());

        if((tab_ptr_grains[i]->get_position()).norme()>DistanceMax) {
            tab_ptr_grains.erase(tab_ptr_grains.begin()+i); //est-ce que le grain cesse d'exister? pas bésoin de delete?
            i-=1;
        }
    }// fin for grain
		if(tab_ptr_grains.size() == 1) tab_ptr_grains[0]->bouger(dt);
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


    for(size_t i(0); i < tab_ptr_grains.size(); ++i) {
        bool inside(true);
        for(size_t j(0); j< tab_ptr_mediums.size(); ++j) {
            if(tab_ptr_mediums[j]->is_inside(*tab_ptr_grains[i])) inside = false;
        }
        if(inside)  (*(tab_ptr_grains[i])).set_medium(*ptr_medium);
    }

    for(size_t i(0); i<tab_ptr_sources.size(); ++i) {
        tab_ptr_sources[i]->creation(tab_ptr_grains, newdt);
    }
    for(size_t i(0); i<tab_ptr_grains.size(); ++i) {
        tab_ptr_grains[i]->Grain::ajouteForce();
				for(auto const& ptr_obstacle : tab_ptr_obstacles) {
						tab_ptr_grains[i]->ajouteForce(ptr_obstacle);
				}// fin for auto obstacle
    }
    for(size_t i(0); i<tab_ptr_grains.size()-1; ++i) {


        for(size_t j(i+1); j<tab_ptr_grains.size(); ++j) {
            Vecteur3D force_oppose((tab_ptr_grains[i]->ajouteForce(tab_ptr_grains[j])).oppose());
            tab_ptr_grains[j]->ajouteForce(force_oppose);
        }// grain interne
        tab_ptr_grains[i]->bouger(dt);
        if ( (0.5 * tab_ptr_grains[i]->get_radius())/((tab_ptr_grains[i]->get_velocity()).norme())  < newdt )
            newdt = (0.5 * tab_ptr_grains[i]->get_radius())/((tab_ptr_grains[i]->get_velocity()).norme());

        if((tab_ptr_grains[i]->get_position()).norme()>DistanceMax) {
            tab_ptr_grains.erase(tab_ptr_grains.begin()+i); //est-ce que le grain cesse d'exister? pas bésoin de delete?
            i-=1;
        }
    }// fin for grain
		if(tab_ptr_grains.size() == 1) tab_ptr_grains[0]->bouger(dt);
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
    for(size_t i(0); i<tab_ptr_grains.size(); ++i) {
        tab_ptr_grains[i]->Grain::ajouteForce();

        for(auto const& ptr_obstacle : tab_ptr_obstacles) {
            tab_ptr_grains[i]->ajouteForce(ptr_obstacle);
        }// fin for auto obstacle

        for(size_t j(i); j<tab_ptr_grains.size(); ++j) {
            Vecteur3D force_oppose(tab_ptr_grains[i]->ajouteForce(tab_ptr_grains[j]));
            tab_ptr_grains[j]->ajouteForce(force_oppose);
        }// grain interne
    }// fin for grain

    for(size_t i(0); i<tab_ptr_grains.size(); ++i) {
        tab_ptr_grains[i]->Grain::bouger(dt);
        if((tab_ptr_grains[i]->get_position()).norme()>DistanceMax) {
            tab_ptr_grains.erase(tab_ptr_grains.begin()+i); //est-ce que le grain cesse d'exister? pas bésoin de delete?
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
