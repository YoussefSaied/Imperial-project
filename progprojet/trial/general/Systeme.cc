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

void Systeme:: addMagnet(Magnet const & nouveau_Magnet)
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

ostream& Systeme:: display(ostream& c) const
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
    c << time << " " << tab_ptr_Magnets[us - 1]->angle << " " << Energy();
    c << endl;
    return c;
}

unique_ptr<Systeme> Systeme :: cloneme() const
{
    unique_ptr<Systeme> P9(new Systeme(support));
    for (auto& g: tab_ptr_Magnets) {
        P9->addMagnet(*g);
    }
    for (auto& o : tab_ptr_obstacles) {
        P9->addObstacle(*o);
    }

    return P9;
}

unique_ptr<Systeme> Systeme ::copie() const
{
    return cloneme();
}

/*
   //move BU or simple move
   void Systeme:: evolue1(double dt)
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


void Systeme:: evolue1(double dt)
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
            tab_ptr_Magnets[i]->addTorque(B);
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
        tab_ptr_Magnets[i]->addnewTorque(B);
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
        KineticEnergy   += energyunit*tab_ptr_Magnets[i]->Kinetic();
        PotentialEnergy += energyunit*tab_ptr_Magnets[i]->potB() / 2;
        // division by 2 more logical I think and it shows better stability (scatch that, WAY better stability)
        // you had a triangular sum :( we need a diagonal one

        /*size_t k = i + 1;

           while (k < tab_ptr_Magnets.size()) {
            PotentialEnergy += tab_ptr_Magnets[k]->potB();

            k++;
           }*/
    }
} // Systeme::evolue1

// */

void Systeme:: evolue1(double dt, unsigned int nb_repet)
{
    for (unsigned int i(0); i < nb_repet; ++i) {
        evolue1(dt);
    }
}

void Systeme:: evolue1(double dt, double t, bool d)
{
    double targettime = t / n;
    while (targettime <= t) {
        while (abs(time + dt - targettime) < abs(time - targettime) ) {
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

double Systeme:: NearestCorrelation() const
{ // can we do it with angles?
    double correlation(0);
    for (size_t i(0); i < tab_ptr_Magnets.size(); ++i) {
        for (size_t j(0); j < tab_ptr_Magnets.size(); ++j) {
            if ( (tab_ptr_Magnets[i]->position - tab_ptr_Magnets[j]->position).norme() <
              2 * tab_ptr_Magnets[i]->length and i != j)
            {
                correlation += (tab_ptr_Magnets[i]->moment().normalise()) * (tab_ptr_Magnets[j]->moment().normalise());
            }
        }
    }
    if (!tab_ptr_Magnets.empty()) { correlation /= tab_ptr_Magnets.size(); }
    return correlation;
}
