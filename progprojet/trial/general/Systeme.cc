#define _USE_MATH_DEFINES
#include "Systeme.h"
#include <iostream>
<<<<<<< HEAD
#include <cmath>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <stdio.h>

=======
#include <fstream>
#include <sstream>
#include <iostream>
>>>>>>> 09fcf2009e5b03350e296195431b706596c4b5c8
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

int Systeme:: addMagnet(Magnet const & nouveau_Magnet)
{
    // faire des tests de compatibilité
    int index = -1;
    for (size_t i = 0; i < tab_ptr_Magnets.size(); i++) {
        if ((tab_ptr_Magnets[i]->position - nouveau_Magnet.position).norme() < 0.0001) {
            index = i;
        }
    }
    if (index == -1) {
        tab_ptr_Magnets.push_back(nouveau_Magnet.copie());
        (*(tab_ptr_Magnets.back())).set_support(support);
        (*(tab_ptr_Magnets.back())).f = f;
        // cout << 1 << endl;
    }
    return index;
}

void Systeme:: setangles(std::string filename)
{
    unique_ptr<ifstream> tfile(new ifstream(filename));
    int value;
    for (auto& ptr_Magnet : tab_ptr_Magnets) {
        *tfile >> value;
        ptr_Magnet->angle = value;
    }
}

void Systeme:: setfriction(double friction)
{
  for (auto const& ptr_Magnet : tab_ptr_Magnets) {
    ptr_Magnet->f = friction;
  }
  f = friction;
}

void Systeme:: randominitial()
{ int i = 0;
  for (auto const& ptr_Magnet : tab_ptr_Magnets) {
    ++i;
    std::chrono::time_point<std::chrono::system_clock> noww = std::chrono::system_clock::now();
    int secnow = std::chrono::duration_cast<std::chrono::seconds>(
                  noww.time_since_epoch()).count();
    srand (secnow + i);
    double randomval = M_PI*(rand() % 2);
    ptr_Magnet->angle = randomval;
  }
}


ostream& Systeme:: display(ostream& c) const
{
  bool fric = 1;
  if (fric){
  c << time<<" ";
  c << NearestCorrelation()<<" ";
  c << totalangle()<<" ";
  c << Energy()<<" ";
  c << KineticEnergy<<" ";
  c << endl;}
  else{
    c << time;
    for (auto& g: tab_ptr_Magnets) {
        c << " " << g->angle << " ";
    }
    c << Energy();
    c << endl;}
    return c;
}

ostream& Systeme:: displaypos(ostream& c) const
{
    for (auto& g: tab_ptr_Magnets) {
        c << g->position << endl;
    }
    return c;
}

unique_ptr<Systeme> Systeme :: cloneme() const
{
    unique_ptr<Systeme> P9(new Systeme(support, f, selectedmagnet));
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
        KineticEnergy   += energyunit * tab_ptr_Magnets[i]->Kinetic();
        PotentialEnergy += energyunit * tab_ptr_Magnets[i]->potB() / 2;
    }
    if (std::abs(KineticEnergy/Energy()) < 1e-15){eq=true;}
}

// Systeme::evolue2 : Nearest neighbours using position if statement
void Systeme:: evolue2(double dt)
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
                if ( (tab_ptr_Magnets[i]->position - tab_ptr_Magnets[j]->position).norme() <
                  2 * tab_ptr_Magnets[i]->length and i != j){
                    tab_ptr_Magnets[i]->addTorque(tab_ptr_Magnets[j]);}
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
          if ( (tab_ptr_Magnets[i]->position - tab_ptr_Magnets[j]->position).norme() <
            2 * tab_ptr_Magnets[i]->length and i != j) {
                tab_ptr_Magnets[i]->addnewTorque(tab_ptr_Magnets[j]);
                tab_ptr_Magnets[i]->addpotB(tab_ptr_Magnets[j]);
            }
        }
    }

    // MOVE OMEGA & ENERGY
    for (size_t i(0); i < tab_ptr_Magnets.size(); ++i) {
        tab_ptr_Magnets[i]->moveomega(dt);
        KineticEnergy   += energyunit * tab_ptr_Magnets[i]->Kinetic();
        PotentialEnergy += energyunit * tab_ptr_Magnets[i]->potB() / 2;
    }
    if (std::abs(KineticEnergy/Energy()) < 1e-15){eq=true;}
}








void Systeme:: evolue1(double dt, unsigned int nb_repet)
{
    for (unsigned int i(0); i < nb_repet; ++i) {
        evolue1(dt);
    }
}

void Systeme:: evolue1(double dt, double t, bool d)
{
<<<<<<< HEAD
    double targettime = t / n;                                                  //n=1
=======
    double targettime = t / n; // the output interval
>>>>>>> 09fcf2009e5b03350e296195431b706596c4b5c8
    while (targettime <= t) {
        while (abs(time + dt - targettime) < abs(time - targettime) ) {
            evolue1(dt);
            }
            targettime += t / n;
            if (d) { dessine(); }


    }
}


void Systeme:: evolue2(double dt, double t, bool d)
{
    double targettime = t / n;                                                  //n=1
    while (targettime <= t) {
        while (abs(time + dt - targettime) < abs(time - targettime) ) {
            evolue2(dt);
            }
            targettime += t / n;
            if (d) { dessine(); }


    }
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



double Systeme:: NearestCorrelation() const
{ // can we do it with angles?
  double correlation(0);
        for (size_t i(0); i < tab_ptr_Magnets.size(); ++i) {
            for (size_t j(0); j < tab_ptr_Magnets.size(); ++j) {
                if ( (tab_ptr_Magnets[i]->position - tab_ptr_Magnets[j]->position).norme() <
                  2 * tab_ptr_Magnets[i]->length and i != j)
                {
                    correlation += (tab_ptr_Magnets[i]->moment().normalise())
                      * (tab_ptr_Magnets[j]->moment().normalise());
                }
            }
        }
        if (!tab_ptr_Magnets.empty()) { correlation /= tab_ptr_Magnets.size(); }
      return correlation;

}






double Systeme::totalangle() const
{
    double totalangle1 = 0;
    for (size_t i(0); i < tab_ptr_Magnets.size(); ++i) {
        double angle = tab_ptr_Magnets[i]->angle;
        int numberofrotations(angle / M_PI);
        angle        = pow(-1, numberofrotations) * std::fmod(angle, M_PI);
        totalangle1 += angle;
    }
    // provisional:

    /*if (tab_ptr_Magnets.size() > 29) {
        totalangle1 += -2 * tab_ptr_Magnets[1]->angle;
        totalangle1 += -2 * tab_ptr_Magnets[2]->angle;
        totalangle1 += -2 * tab_ptr_Magnets[23]->angle;
        totalangle1 += -2 * tab_ptr_Magnets[28]->angle;
        totalangle1 += -2 * tab_ptr_Magnets[3]->angle;
       }*/
    return totalangle1;
}

std::vector<double> Systeme::vertexangles(Vecteur3D vertexposition, double thresholddistance)
{
    std::vector<double> angles;
    for (size_t i(0); i < tab_ptr_Magnets.size(); ++i) {
        if ((tab_ptr_Magnets[i]->position - vertexposition).norme() < thresholddistance) {
            angles.push_back(tab_ptr_Magnets[i]->angle);
        }
    }
    return angles;
}
