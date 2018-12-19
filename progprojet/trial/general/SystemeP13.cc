#include "Systeme.h"
#include "SystemeP13.h"
#include "SystemeP9.h"
#include <iostream>

using namespace std;

// constructeurs


// manipulateurs

void SystemeP13:: ajouteGrain(Grain const& nouveau_grain )
{
    int x, y,	z;
    double s(2 * GrainLJ::get_sigma());
    x = (nouveau_grain.get_position().get_x() + DistanceMax)/s;
    y = (nouveau_grain.get_position().get_y() + DistanceMax)/s;
    z = (nouveau_grain.get_position().get_z() + DistanceMax)/s;
    triplet t(x,y,z);
    (map_case[t]).push_back(nouveau_grain.copie());
    (*((map_case[t]).back())).set_support(support);
}

// méthodes

unique_ptr<SystemeP9> SystemeP13 :: P13toP9s() const
{
    unique_ptr<SystemeP9> P9(new SystemeP9(support));
    for (map<triplet,   vector<unique_ptr<Grain>>  >::iterator i(map_case.begin());
         i != map_case.end(); ++i) {
        for(auto& g: i) {
            P9->ajouteGrain(*g);
        }
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

unique_ptr<Systeme> SystemeP13 ::P13toP9() const
{
    cout<<"changement vers P9 :D "<<endl;
    return P13toP9s();
}

unique_ptr<SystemeP13> SystemeP13 :: cloneme() const
{
    unique_ptr<SystemeP13> P13(new SystemeP13(support));
    for (map<triplet,   vector<unique_ptr<Grain>>  >::iterator i(map_case.begin());
         i != map_case.end(); ++i) {
        for(auto& g: i) {
            P13->ajouteGrain(*g);
        }
    }
    for(auto& o : tab_ptr_obstacles) {
        P13->ajouteObstacle(*o);
    }
    for(auto& s : tab_ptr_sources) {
        P13->ajouteSource(*s);
    }
    for(auto& m : tab_ptr_mediums) {
        P13->ajouteMediumi(*m);
    }
    return P13;
}

unique_ptr<Systeme> SystemeP13 ::copie() const
{
    return cloneme();
}

double SystemeP13:: evolue1(double dt)
{
    double newdt(dt);
    for(size_t i(0); i<tab_ptr_sources.size(); ++i) {
        int x, y,	z;
        double s(2 * GrainLJ::get_sigma());
        x = (tab_ptr_sources[i]->get_position().get_x() + DistanceMax)/s;
        y = (tab_ptr_sources[i]->get_position().get_y() + DistanceMax)/s;
        z = (tab_ptr_sources[i]->get_position().get_z() + DistanceMax)/s;
        tab_ptr_sources[i]->creation(map_case[triplet(x,y,z)], newdt);
    }
    for (map<triplet,   vector<unique_ptr<Grain>>  >::iterator i(map_case.begin());
         i != map_case.end(); ++i) {
        for(int x(0) ; x < (i->second).size(); ++x) {
            (i->second)[x]->Grain::ajouteForce();
        }
        for(int x(0) ; x < i->size()-1; ++x) {
            for(int y(x+1); y<i->size(); ++y) {
                Vecteur3D force_oppose((i->second)[x]->
                                       ajouteForce(((i->second)[y])).oppose());
                i->second[y]->ajouteForce(force_oppose);
            }
            for (map<triplet,   vector<unique_ptr<Grain>>  >::iterator j(map_case.begin());
                 j != map_case.end(); ++j) {
                if(i->first < j->first) {
                    for(int y(0); y<j->size(); ++y) {
                        Vecteur3D force_oppose((i->second)[x]->
                                               ajouteForce(((j->second)[y])).oppose());
                        j->second[y]->ajouteForce(force_oppose);
                    }
                }
            } // grain interne

            for(auto const& ptr_obstacle : tab_ptr_obstacles) {
                (i->second)[x]->ajouteForce(ptr_obstacle);
            }// fin for auto obstacle

            (i->second)[x]->bouger(dt);

            if ( (0.5 * (i->second)[x]->get_radius()) /
                 (((i->second)[x]->get_velocity()).norme())  < newdt )
                newdt = (0.5 * (i->second)[x]->get_radius())/((i->second)[x]->get_velocity()).norme());

                if(((i->second)[x]->get_position()).norme()>DistanceMax) {
                    (i->second).erase((i->second).begin()+l); //est-ce que le grain cesse d'exister? pas bésoin de delete?
                    x-=1;
                }

            int x, y,	z;
            double t(2 * GrainLJ::get_sigma());
            x = ((i->second)[x]->get_position().get_x() + DistanceMax)/t;
            y = ((i->second)[x]->get_position().get_y() + DistanceMax)/t;
            z = ((i->second)[x]->get_position().get_z() + DistanceMax)/t;

            if(x!=i or y!=j or z!= k) {
            ajouteGrain(*(i->second)[x]);
                (i->second).erase((i->second).begin()+l);
                l-=1;
            }


        }// fin for one grain
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

ostream& SystemeP13:: display(std:: ostream& c) const
{
	c << "Je suis un systeme avec : " << std::endl;
	int s(0);
	for(size_t i(0); i<map_case.size(); ++i){
		for(size_t j(0); j<map_case.size(); ++j){
			for(size_t k(0); i<map_case.size(); ++k) {
				s+=map_case[i][j][k].size();
			}}}
	c << s << " grains ";
	if(s!=0){ c<<",les suivants : "<<std::endl;}
	for(size_t i(0); i<map_case.size(); ++i){
		for(size_t j(0); j<map_case.size(); ++j){
			for(size_t k(0); i<map_case.size(); ++k) {
					for(size_t l(0);l< (map_case[i][j][k]).size(); ++l){
							(map_case[i][j][k][l])->dessine();}}}}
	c << tab_ptr_obstacles.size()<<" obstacles ";
	if(tab_ptr_obstacles.size()!=0){ c<<",les suivants : "<<std::endl;}
	for(auto const& ptr_obstacle : tab_ptr_obstacles){
		(*ptr_obstacle).dessine();}
	c << tab_ptr_sources.size()<<" sources ";
	if(tab_ptr_sources.size()!=0){ c<<",les suivantes : "<<std::endl;}
	for(auto const& ptr_source : tab_ptr_sources){
		(*ptr_source).dessine();}
	c<<std::endl;
		return c;
}

