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

#include "ConfigFile.tpp"

using namespace std;

int main(int argc, char * argv[])
{
    // intitial configuration:
    Systeme s;
    Vecteur3D v1(1, 0, 0);
    Vecteur3D v2(1, 0, 0);
    Vecteur3D v3(1, 0, 0);
    v2 = v1.rotate(M_PI / 3 * 2, Vecteur3D(0, 0, 1));
    v3 = v1.rotate(M_PI / 3 * 4, Vecteur3D(0, 0, 1));
    Magnet M1(Position(0, 0, 0), v2);
    Magnet M2(Position(0 + M1.length * 1.2, 0, 0), v3);
    Magnet M3(Position(0 + M1.length * 0.6, 0 + M1.length * 1.039, 0), v1);
    Magnet M4(Position(0, 0, 0), Vecteur3D(0, 1, 0), 0);
    Magnet M5(Position(0, 0, 0 + M1.length * 2.2), Vecteur3D(0, 1, 0), 1, 1.5);

    Dodec dode(Vecteur3D(0, 0, 0), 3e-2, Vecteur3D(0, 0, 1.23607), false);
    Cylinder c1(Position(0, 10, 0), Vecteur3D(0, 7, 0), 1, 1);
    Cylinder c2(Position(10, 0, 0), Vecteur3D(7, 0, 0), 1, 1);
    Cylinder c3(Position(0, 0, 10), Vecteur3D(0, 0, 1), 1, 1);


    for (size_t i = 0; i < (dode.vertipositions()).size(); ++i) {
        size_t si = ((dode.vertipositions())[i]).size();
        for (size_t j = 0; j < si; ++j) {
            Vecteur3D p(0, 0, 0);
            p = ((dode.vertipositions())[i][j] + (dode.vertipositions())[i][(j + 1) % si]) / 2;
            // p += dode.position;
            // ++num;
            // cout << i << "," << j << num << ":  ";
            // cout << p << endl;
            // For the axe
            Vecteur3D v1(0, 1, 0);
            Vecteur3D v2(0, 1, 0);
            Vecteur3D v3(0, 1, 0);
            Vecteur3D v4(0, 1, 0);
            Vecteur3D axe(0, 1, 0);
            v1 = ((dode.vertipositions())[i][j] - (dode.vertipositions())[i][(j + 1) % si]);
            // for v2 :
            v2 = ((dode.vertipositions())[i][(j + 1) % si] - (dode.vertipositions())[i][(j + 2) % si]);
            // for v3 :
            v3 = v1 ^ v2;
            double alph = atan(2); // angle of rotation arctan(2)
            v4  = v3.rotate(alph, v1);
            axe = v4 ^ v1;

            // calculate polaraxis:
            Vecteur3D polaraxis(1, 0, 0);
            polaraxis = (dode.vertipositions())[i][j] - (dode.vertipositions())[i][(j + 1) % si];

            // add magnet here.
            Magnet M(p, axe, 1, 0, polaraxis); // position p, axis a, movable yes, angle_0 0, polaraxis polaraxis
        }
    }


    // the text stuff ::

    // input configuration file:
    string inputPath("configuration.in");
    if (argc > 1) { // Fichier d'input specifie par l'utilisateur ("./Exercice8 config_perso.in")
        inputPath = argv[1];
    }
    ConfigFile configFile(inputPath);
    for (int i(2); i < argc; ++i) { // Input complementaires ("./Exercice8 config_perso.in input_scan=[valeur]")
        configFile.process(argv[i]);
    }

    double dt      = configFile.get<double>("dt");
    double timesim = configFile.get<double>("timesim");
    double f       = configFile.get<double>("f");
    int n = configFile.get<int>("nb_repet");

    // output text file:
    string output = configFile.get<string>("output");
    unique_ptr<ofstream> tfile(new ofstream(output.c_str()));
    tfile->precision(20);
    SupportADessinTexte tsupport(*tfile);
    s.f = f;
    s.n = n;
    s.set_support(&tsupport);
    s.evolue1(dt, timesim);

    /*std::cout << "Please input dt:" << '\n';
       cin >> dt;
       cout << endl;
       std::cout << "Please input time of simulation:" << '\n';
       cin >> timesim;*/
    return 0;
} // main

// unique_ptr<ofstream> textfile0(new ofstream("Dodecedgesandvertices"));
// tfile->precision(20);
