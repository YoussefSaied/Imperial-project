#include "Systeme.h"
#include "SystemeP12.h"
#include "SystemeP9.h"
#include <iostream>

using namespace std;

// constructeurs
SystemeP12:: SystemeP12(SupportADessin* support):Systeme(support)
{
    int t(DistanceMax/MagnetE::get_sigma());
    tab_case.resize(t);
    for(auto& t1: tab_case) {
        t1.resize(t);
        for(auto& t2: t1) {
            t2.resize(t);
        }
    }
}

// manipulateurs

void SystemeP12:: addMagnet(Magnet const& nouveau_Magnet )
{
    int x, y,	z;
    double t(2 * MagnetE::get_sigma());
    x = (nouveau_Magnet.get_position().get_x() + DistanceMax)/t;
    y = (nouveau_Magnet.get_position().get_y() + DistanceMax)/t;
    z = (nouveau_Magnet.get_position().get_z() + DistanceMax)/t;
    (tab_case[x][y][z]).push_back(nouveau_Magnet.copie());
    (*((tab_case[x][y][z]).back())).set_support(support);
}

// méthodes


ostream& SystemeP12:: display(std:: ostream& c) const
{
    c << "Je suis un systeme avec : " << std::endl;
    int s(0);
    for(size_t i(0); i<tab_case.size(); ++i) {
        for(size_t j(0); j<tab_case.size(); ++j) {
            for(size_t k(0); i<tab_case.size(); ++k) {
                s+=tab_case[i][j][k].size();
            }
        }
    }
    c << s << " Magnets ";
    if(s!=0) {
        c<<",les suivants : "<<std::endl;
    }
    for(size_t i(0); i<tab_case.size(); ++i) {
        for(size_t j(0); j<tab_case.size(); ++j) {
            for(size_t k(0); i<tab_case.size(); ++k) {
                for(size_t l(0); l< (tab_case[i][j][k]).size(); ++l) {
                    (tab_case[i][j][k][l])->dessine();
                }
            }
        }
    }
    c << tab_ptr_obstacles.size()<<" obstacles ";

    for(auto const& ptr_obstacle : tab_ptr_obstacles) {
        (*ptr_obstacle).dessine();
    }

    c<<std::endl;
    return c;
}

unique_ptr<SystemeP9> SystemeP12 :: P12toP9s() const
{
    unique_ptr<SystemeP9> P9(new SystemeP9(support));
    for(auto& i: tab_case) {
        for(auto& j: i) {
            for(auto& k: j) {
                for(auto& g: k) {
                    P9->addMagnet(*g);
                }
            }
        }
    }
    for(auto& o : tab_ptr_obstacles) {
        P9->ajouteObstacle(*o);
    }

    for(auto& m : tab_ptr_mediums) {
        P9->ajouteMediumi(*m);
    }
    return P9;
}
unique_ptr<Systeme> SystemeP12 ::P12toP9() const
{
    cout<<"changement vers P9 :D "<<endl;
    return P12toP9s();
}
unique_ptr<SystemeP12> SystemeP12 :: cloneme() const
{
    unique_ptr<SystemeP12> P12(new SystemeP12(support));
    for(auto& i: tab_case) {
        for(auto& j: i) {
            for(auto& k: j) {
                for(auto& g: k) {
                    P12->addMagnet(*g);
                }
            }
        }
    }
    for(auto& o : tab_ptr_obstacles) {
        P12->ajouteObstacle(*o);
    }

    for(auto& m : tab_ptr_mediums) {
        P12->ajouteMediumi(*m);
    }
    return P12;
}

unique_ptr<Systeme> SystemeP12 ::copie() const
{
    return cloneme();
}

double SystemeP12:: evolue1(double dt)
{
    double newdt(dt);

    for(size_t i(0); i<tab_case.size()-1; ++i) {
        for(size_t j(0); j<tab_case.size()-1; ++j) {
            for(size_t k(0); k<tab_case.size()-1; ++k) {
                for(size_t l(0); l< (tab_case[i][j][k]).size(); ++l) {
                    (tab_case[i][j][k][l])->Magnet::ajouteForce();
                }
                for(size_t l(0); l< (tab_case[i][j][k]).size(); ++l) {
                    (tab_case[i][j][k][l])->Magnet::ajouteForce();
                    for(size_t m(l+1); m < (tab_case[i][j][k]).size(); ++m) {
                        Vecteur3D force_oppose(((tab_case[i][j][k])[l]->
                                                ajouteForce((tab_case[i][j][k])[m])).oppose());
                        (tab_case[i][j][k])[m]->ajouteForce(force_oppose);
                    }

                    for(size_t m(0); m < (tab_case[i+1][j][k]).size(); ++m) {
                        Vecteur3D force_oppose(((tab_case[i][j][k])[l]->
                                                ajouteForce((tab_case[i+1][j][k])[m])).oppose());
                        (tab_case[i+1][j][k])[m]->ajouteForce(force_oppose);
                    }

                    for(size_t m(0); m < (tab_case[i+1][j+1][k]).size(); ++m) {
                        Vecteur3D force_oppose(((tab_case[i][j][k])[l]->
                                                ajouteForce((tab_case[i+1][j+1][k])[m])).oppose());
                        (tab_case[i+1][j+1][k])[m]->ajouteForce(force_oppose);
                    }

                    for(size_t m(0); m < (tab_case[i+1][j+1][k+1]).size(); ++m) {
                        Vecteur3D force_oppose(((tab_case[i][j][k])[l]->
                                                ajouteForce((tab_case[i+1][j+1][k+1])[m])).oppose());
                        (tab_case[i+1][j+1][k+1])[m]->ajouteForce(force_oppose);
                    }

                    for(size_t m(0); m < (tab_case[i+1][j][k+1]).size(); ++m) {
                        Vecteur3D force_oppose(((tab_case[i][j][k])[l]->
                                                ajouteForce((tab_case[i+1][j][k+1])[m])).oppose());
                        (tab_case[i+1][j][k+1])[m]->ajouteForce(force_oppose);
                    }

                    for(size_t m(0); m < (tab_case[i][j+1][k]).size(); ++m) {
                        Vecteur3D force_oppose(((tab_case[i][j][k])[l]->
                                                ajouteForce((tab_case[i][j+1][k])[m])).oppose());
                        (tab_case[i][j+1][k])[m]->ajouteForce(force_oppose);
                    }

                    for(size_t m(0); m < (tab_case[i][j+1][k+1]).size(); ++m) {
                        Vecteur3D force_oppose(((tab_case[i][j][k])[l]->
                                                ajouteForce((tab_case[i][j+1][k+1])[m])).oppose());
                        (tab_case[i][j+1][k+1])[m]->ajouteForce(force_oppose);
                    }

                    for(size_t m(0); m < (tab_case[i][j][k+1]).size(); ++m) {
                        Vecteur3D force_oppose(((tab_case[i][j][k])[l]->
                                                ajouteForce((tab_case[i][j][k+1])[m])).oppose());
                        (tab_case[i][j][k+1])[m]->ajouteForce(force_oppose);
                    }

                    // Magnet interne

                    for(auto const& ptr_obstacle : tab_ptr_obstacles) {
                        (tab_case[i][j][k][l])->ajouteForce(ptr_obstacle);
                    }// fin for auto obstacle

                    tab_case[i][j][k][l]->bouger(dt);

                    if ( (0.5 * (tab_case[i][j][k])[l]->get_radius()) /
                         (((tab_case[i][j][k])[l]->get_velocity()).norme())  < newdt )
                        newdt = (0.5 * (tab_case[i][j][k])[l]->get_radius())/(((tab_case[i][j][k])[l]->get_velocity()).norme());

                    if(((tab_case[i][j][k])[l]->get_position()).norme()>DistanceMax) {
                        tab_case[i][j][k].erase(tab_case[i][j][k].begin()+l); //est-ce que le Magnet cesse d'exister? pas bésoin de delete?
                        l-=1;
                    }

                    unsigned int x, y,	z;
                    double t(2 * MagnetE::get_sigma());
                    x = (tab_case[i][j][k][l] ->get_position().get_x() + DistanceMax)/t;
                    y = (tab_case[i][j][k][l] ->get_position().get_y() + DistanceMax)/t;
                    z = (tab_case[i][j][k][l] ->get_position().get_z() + DistanceMax)/t;

                    if(x!=i or y!=j or z!= k) {
                        addMagnet(*tab_case[i][j][k][l]);
                        tab_case[i][j][k].erase(tab_case[i][j][k].begin()+l);
                        l-=1;
                    }

                }// fin for one Magnet
            }
        }
    }
    for(auto const& ptr_obstacle : tab_ptr_obstacles) {
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
