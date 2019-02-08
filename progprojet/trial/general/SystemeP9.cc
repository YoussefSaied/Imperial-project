#include "SystemeP9.h"
#include "Systeme.h"
#include <iostream>

using namespace std;


void SystemeP9:: addMagnet(Magnet const& nouveau_Magnet)
{
    // faire des tests de compatibilité
    bool exists = 0;
    for (auto const& ptr_Magnet : tab_ptr_Magnets) {
        if ((ptr_Magnet->position - nouveau_Magnet.position).norme() < 0.0001) {
            exists = 1;
        }
    }
    if (!exists) {
        tab_ptr_Magnets.push_back(nouveau_Magnet.copie());
        (*(tab_ptr_Magnets.back())).set_support(support);
        (*(tab_ptr_Magnets.back())).f = f;
        // cout << 1 << endl;
    }
}

ostream& SystemeP9:: display(ostream& c) const
{
    /*if (time = 0){
       c << "A System with " << tab_ptr_Magnets.size() << " Magnets" << endl;
       c << tab_ptr_obstacles.size() << "Obstacles: ";
       for (auto const& ptr_obstacle : tab_ptr_obstacles) {
            (*ptr_obstacle).dessine();
       }
       }*/

    /*for (auto const& ptr_Magnet : tab_ptr_Magnets) {
        (*ptr_Magnet).dessine();
       }*/

    int us = tab_ptr_Magnets.size();
    c << time << " " << tab_ptr_Magnets[us - 1]->angle;
    c << endl;
    return c;
}

unique_ptr<SystemeP9> SystemeP9 :: cloneme() const
{
    unique_ptr<SystemeP9> P9(new SystemeP9(support));
    for (auto& g: tab_ptr_Magnets) {
        P9->addMagnet(*g);
    }
    for (auto& o : tab_ptr_obstacles) {
        P9->addObstacle(*o);
    }

    return P9;
}

unique_ptr<Systeme> SystemeP9 ::copie() const
{
    return cloneme();
}

/*
   //move BU or simple move
   void SystemeP9:: evolue1(double dt)
   {
    time  += dt;
    Energy = 0;
    for (size_t i(0); i < tab_ptr_Magnets.size(); ++i)
    {
        tab_ptr_Magnets[i]->addTorque(H);
        for (size_t j(0); j < tab_ptr_Magnets.size(); ++j)
          {
            if (i != j) {
                tab_ptr_Magnets[i]->addTorque(tab_ptr_Magnets[j]);
                tab_ptr_Magnets[i]->addpotB(tab_ptr_Magnets[j]);}
          }
    }

    for (size_t i(0); i < tab_ptr_Magnets.size(); ++i)
    {
        //    tab_ptr_Magnets[i]->VerletBU(dt);
           tab_ptr_Magnets[i]->move(dt);
            Energy += tab_ptr_Magnets[i]->Kinetic();
            int k=i+1;
            while (k<tab_ptr_Magnets.size()){
              Energy += tab_ptr_Magnets[k]->potB();
              k++;}
    }
   }

 */


void SystemeP9:: evolue1(double dt)
{
    time += dt;
    KineticEnergy   = 0;
    PotentialEnergy = 0;

    // CALC TORQUE
    for (size_t i(0); i < tab_ptr_Magnets.size(); ++i) {
        if (time > 0.1) {
            tab_ptr_Magnets[i]->resetnew();
        } else {
            tab_ptr_Magnets[i]->reset();
            tab_ptr_Magnets[i]->addTorque(H);
            for (size_t j(0); j < tab_ptr_Magnets.size(); ++j) {
                // magnet interactions
                if (i != j) {
                    tab_ptr_Magnets[i]->addTorque(tab_ptr_Magnets[j]);
                }
            }
        }
    }

    // MOVE ANGLE
    for (size_t i(0); i < tab_ptr_Magnets.size(); ++i) {
        tab_ptr_Magnets[i]->moveangle(dt);
    }

    // CALC NEWTORQUE
    for (size_t i(0); i < tab_ptr_Magnets.size(); ++i) {
        tab_ptr_Magnets[i]->addnewTorque(H);
        for (size_t j(0); j < tab_ptr_Magnets.size(); ++j) {
            if (i != j) {
                tab_ptr_Magnets[i]->addnewTorque(tab_ptr_Magnets[j]);
                tab_ptr_Magnets[i]->addpotB(tab_ptr_Magnets[j]);
            }
        }
    }

    // MOVE OMEGA & ENERGY
    for (size_t i(0); i < tab_ptr_Magnets.size(); ++i) {
        tab_ptr_Magnets[i]->moveomega(dt);
        KineticEnergy   += tab_ptr_Magnets[i]->Kinetic();
        PotentialEnergy += tab_ptr_Magnets[i]->potB() / 2;
        // division by 2 more logical I think and it shows better stability (scatch that, WAY better stability)
        // you had a triangular sum :( we need a diagonal one

        /*size_t k = i + 1;

           while (k < tab_ptr_Magnets.size()) {
            PotentialEnergy += tab_ptr_Magnets[k]->potB();

            k++;
           }*/
    }
} // SystemeP9::evolue1

// */

void SystemeP9:: evolue1(double dt, unsigned int nb_repet)
{
    for (unsigned int i(0); i < nb_repet; ++i) {
        evolue1(dt);
    }
}

void SystemeP9:: evolue1(double dt, double t, bool d)
{
    double targettime = t / n;
    while (targettime <= t) {
        while (time < targettime - dt) {
            evolue1(dt);
        }
        targettime += t / n;
        if (d) { dessine(); }
    }

    /*int nb_repet;
       if (t > dt)
       { nb_repet = t / dt; } else
       { nb_repet = 1; }
       unsigned int nbr2(nb_repet / n);
       for (unsigned int i(0); i < n; ++i) {
        evolue1(dt, nbr2);
        if (d) { dessine(); }
       }*/
}
