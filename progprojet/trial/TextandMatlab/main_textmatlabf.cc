#include "Systeme.h"
#include "Vecteur3D.h"
#include "Plan.h"
#include "Dalle.h"
#include <vector>
#include "Sphere.h"
#include "Brique.h"
#include "Dodec.h"
#include "Cylinder.h"
#include <iostream>
#include <iomanip>
#include "ConfigFile.tpp"
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <stdio.h>
#include <time.h>

using namespace std;

int main(int argc, char * argv[])
{
    // intitial configuration:
    Systeme s;

    Dodec dode(Vecteur3D(0, 0, 0), 3e-2, Vecteur3D(0, 0, 1.0), false);
    for (size_t i = 0; i < (dode.vertipositions()).size(); ++i) {
        size_t si = ((dode.vertipositions())[i]).size();
        for (size_t j = 0; j < si; ++j) {
            Vecteur3D pos( ((dode.vertipositions())[i][j] + (dode.vertipositions())[i][(j + 1) % si]) / 2);
            Vecteur3D polaraxis = (dode.vertipositions())[i][j] - (dode.vertipositions())[i][(j + 1) % si];
            Vecteur3D v2        =
              ((dode.vertipositions())[i][(j + 1) % si] - (dode.vertipositions())[i][(j + 2) % si]);
            Vecteur3D v3 = polaraxis ^ v2;
            double alph1  = -1 * atan(2) / 2;
            Vecteur3D v4  = v3.rotate(alph1, polaraxis);
            Vecteur3D axe = (v4 ^ polaraxis).normalise();

            Magnet M(pos, axe, 1, 0, polaraxis); // position pos, axis axe, movable yes, angle_0 0, polaraxis
            s.addMagnet(M);
        }
    }
    s.setfriction(3);
    double dt = 0.001;
    double timesim = 5;

   //std::chrono::time_point<std::chrono::system_clock> currenttime = std::chrono::system_clock::now();

   //EVOLVE
   string output = "evolve" ;//+ std::put_time(std::localtime(&currenttime), "%T");
   unique_ptr<ofstream> tfile(new ofstream(output.c_str()));
   tfile->precision(20);
   SupportADessinTexte tsupport(*tfile);
   s.set_support(&tsupport);
   s.randominitial();
   s.evolue(dt, timesim,1,1);


   //EVOLVE1
   string output1 = "evolve1" ;//+ std::put_time(std::localtime(&currenttime), "%T");
   unique_ptr<ofstream> tfile1(new ofstream(output1.c_str()));
   tfile1->precision(20);
   SupportADessinTexte tsupport1 = *tfile1;
   s.set_support(&tsupport1);
   s.randominitial();
   s.evolue1(dt, timesim,1,1);

   //EVOLVE2
   string output2 = "evolve2";// + std::put_time(std::localtime(&currenttime), "%T");
   unique_ptr<ofstream> tfile2(new ofstream(output2.c_str()));
   tfile2->precision(20);
   SupportADessinTexte tsupport2 = *tfile2;
   s.set_support(&tsupport2);
   s.randominitial();
   s.evolue2(dt, timesim,1,1);

    // output text file:


    // namefile with time
    // run sim. with evolve1 and evolve2

    // s.set_support(&tsupport);
    // output 30 angles
    // output energies and correlations

    /*std::cout << "Please input dt:" << '\n';
       cin >> dt;
       cout << endl;
       std::cout << "Please input time of simulation:" << '\n';
       cin >> timesim;*/
    return 0;
} // main

// unique_ptr<ofstream> textfile0(new ofstream("Dodecedgesandvertices"));
// tfile->precision(20);
