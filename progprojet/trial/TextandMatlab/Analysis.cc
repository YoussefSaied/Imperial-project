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

    Dodec dode(Vecteur3D(0, 0, 0), 3e-2, Vecteur3D(0, 0, 1.23607), false);


    // vertices:

    // vector<vector<double> > verticesfaceindex; // position face index face index

    struct vertixmagnets {
        Vecteur3D position;
        int       magnet1; // index
        int       magnet2; // index
        int       magnet3; // index
    };

    struct doublevertix {
        int           centralmagnet;
        vertixmagnets v1;
        vertixmagnets v2;
    };

    struct facemagnets {
        vector<doublevertix> doubleVertixVector;
        double               orientation;
    };

    vector<vertixmagnets> VM;
    vector<doublevertix> DV;
    vector<facemagnets> FM;

    // VM initialisation:

    vector<vector<Vecteur3D> > vertixpositions = dode.vertipositions();

    for (size_t i = 0; i < vertixpositions.size(); ++i) {
        size_t si = (vertixpositions[i]).size();
        for (size_t j = 0; j < si; ++j) {
            int exists = -1;
            for (size_t l = 0; l < VM.size(); ++l) {
                if (vertixpositions[i][j] == VM[l].position) { exists = l; }
            }
            if ((exists != -1)) {
                VM.push_back({ vertixpositions[i][j], -1, -1, -1 });
            }
        }
    }


    for (size_t i = 0; i < (dode.vertipositions()).size(); ++i) {
        size_t si = ((dode.vertipositions())[i]).size();
        for (size_t j = 0; j < si; ++j) {
            Vecteur3D p(0, 0, 0);
            p = ((dode.vertipositions())[i][j] + (dode.vertipositions())[i][(j + 1) % si]) / 2;

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

            int index;
            if (s.addMagnet(M); ) { index = (s.tab_ptr_Magnets.size() - 1); }

            // VM:
            for (auto VMelem: VM) {
                if ((VMelem.vfi).position == (dode.vertipositions())[i][j]) {
                    if (VMelem.magnet1 == -1) { magnet1 = index; }
                    elseif(VMelem.magnet2 == -1) magnet2 = index;
                    elseif(VMelem.magnet3 == -1) magnet3 = index;
                }
                if ((VMelem.vfi).position == (dode.vertipositions())[i][(j + 1) % si]) {
                    if (VMelem.magnet1 == -1) { magnet1 = index; }
                    elseif(VMelem.magnet2 == -1) magnet2 = index;
                    elseif(VMelem.magnet3 == -1) magnet3 = index;
                }
            }
        }
    }


    // DV:
    for (auto VMelem1: VM) {
        for (auto VMelem2: VM) {
            if (VMelem1.magnet1 == VMelem2.magnet1) {
                DV.push_back({ VMelem2.magnet1, VMelem1, VMelem2 });
            }
            if (VMelem1.magnet2 == VMelem2.magnet2) {
                DV.push_back({ VMelem2.magnet2, VMelem1, VMelem2 });
            }
            if (VMelem1.magnet3 == VMelem2.magnet3) {
                DV.push_back({ VMelem2.magnet3, VMelem1, VMelem2 });
            }
        }
    }

    // Facevector:
    for (size_t i = 0; i < vertixpositions.size(); ++i) {
        vector<doublevertix> VectorDVelem;
        size_t si = (vertixpositions[i]).size();
        for (size_t j = 0; j < si; ++j) {
            for (auto DVelem: DV) {
                if (DVelem.v1.position == vertixpositions[i][j] and DVelem.v2.position ==
                  vertixpositions [i][(j + 1) % si]) { VectorDVelem.push_back(DVelem); }
            }
        }
        FM.push_back({ VectorDVelem, -1 });
    }


    // IMPORTANT: We might need to seperate them
    // set angles:


    s.setangles("finalangles.in");


    // Matlab stuff :( ::

    // Vertix strength (f/w):

    int Oddoneout(vertixmagnets vm)
    {
        double p12 = s.tab_ptr_Magnets[vm.magnet1]->orientation() * s.tab_ptr_Magnets[vm.magnet2]->orientation();
        double p13 = s.tab_ptr_Magnets[vm.magnet1]->orientation() * s.tab_ptr_Magnets[vm.magnet3]->orientation();
        double p23 = s.tab_ptr_Magnets[vm.magnet2]->orientation() * s.tab_ptr_Magnets[vm.magnet3]->orientation();
        if (p12 > 0 and p13 > 0) { return vm.magnet1; }
        if (p12 > 0 and p23 > 0) { return vm.magnet2; }
        if (p23 > 0 and p13 > 0) { return vm.magnet3; }
    } // sends back oddmagnet index

    int doublevertixstrength(doublevertix dv)
    {
        if (Oddoneout(dv.v1) == dv.centralmagnet and Oddoneout(dv.v2) == dv.centralmagnet) { return 3; }
        elseif(Oddoneout(dv.v1) != dv.centralmagnet and Oddoneout(dv.v2) == dv.centralmagnet) return 2;

        elseif(Oddoneout(dv.v1) == dv.centralmagnet and Oddoneout(dv.v2) != dv.centralmagnet) return 1;

        elseif(Oddoneout(dv.v1) != dv.centralmagnet and Oddoneout(dv.v2) != dv.centralmagnet) return 0;
    }

    bool doublevertixup(doublevertix dv, int magnetindex)
    {
        Vecteur3D barycenterofdv = s.tab_ptr_Magnets[dv.centralmagnet]->position;
        Vecteur3D upwardorientation(barycenterofface - Dodec.position);
        double seperationafterorientation1 =
          (s.tab_ptr_Magnets[magnetindex]->position
          + s.tab_ptr_Magnets[magnetindex]->orientation() * s.tab_ptr_Magnets[magnetindex]->length
          - barycenterofdv ).norme();
        double seperationafterorientation2 =
          -1 * (s.tab_ptr_Magnets[magnetindex]->position
          + s.tab_ptr_Magnets[dv.centralmagnet]->orientation() * s.tab_ptr_Magnets[magnetindex]->length
          + barycenterofdv ).norme();
        double seperationbetweencenters =
          (s.tab_ptr_Magnets[magnetindex]->position
          - barycenterofdv ).norme();
        int fixer = 1;
        if (seperationafterorientation1 < seperationbetweencenters) { fixer *= -1 }
        if (seperationafterorientation2 > seperationbetweencenters) { fixer *= -1 }
        if (fixer
          * ((s.tab_ptr_Magnets[magnetindex]->orientation() ^ s.tab_ptr_Magnets[dv.centralmagnet]->orientation())
          * upwardorientation) > 0) { return 1; }
        return 0;
    }

    int finddoublevertix(int magnetindex)
    {
        for (int i = 0; i < DV.size(); i++) {
            if (DV[i].centralmagnet == magnetindex) { return i; }
        }
    }

    int doublevertixstrengthRelative(doublevertix dv, int magnetindex)
    {
        int detailed = 0;
        int doublevertixindexofmagnet = finddoublevertix(magnetindex);
        if (doublevertixstrength(DV[doublevertixindexofmagnet]) ==
          0 or doublevertixstrength(DV[doublevertixindexofmagnet]) == 3)
        {
            detailed += doublevertixstrength(DV[doublevertixindexofmagnet]);
        }           else {
            if (Oddoneout(dv.v1) == DV[doublevertixindexofmagnet].centralmagnet) {
                detailed += 2
            } else { detailed += 1 }
        }
        return detailed;
    }

    int doublevertixstrengthDetailed(doublevertix dv)
    {
        int detailed(doublevertixstrength(dv) * 100);
        if (doublevertixup(dv, (dv.v1).magnet1)) {
            // v1m1
            detailed += doublevertixstrengthRelative(dv, (dv.v1).magnet1);
            // v1m2
            detailed += doublevertixstrengthRelative(dv, (dv.v1).magnet2) * 10;
        } else {
            // v1m1
            detailed += doublevertixstrengthRelative(dv, (dv.v1).magnet1) * 10;
            // v1m2
            detailed += doublevertixstrengthRelative(dv, (dv.v1).magnet2);
        }

        if (doublevertixup(dv, (dv.v2).magnet1)) {
            // v2m1
            detailed += doublevertixstrengthRelative(dv, (dv.v2).magnet1) * 1000;
            // v2m2
            detailed += doublevertixstrengthRelative(dv, (dv.v2).magnet2) * 10000;
        } else {
            // v2m1
            detailed += doublevertixstrengthRelative(dv, (dv.v2).magnet1) * 10000;
            // v2m2
            detailed += doublevertixstrengthRelative(dv, (dv.v2).magnet2) * 1000;
        }
        return detailed;
    }

    // orientation of face
    int getFaceOrientaion(facemagnets fm)
    {
        // we can do it with vector product; seems elegant?
        vector<double> scalarproducts;
        Vecteur3D barycenterofface(0, 0, 0);
        size_t facesize = fm.doubleVertixVector.size();
        for (size_t i = 0; i < facesize; ++i) {
            double scalarp(s.tab_ptr_Magnets[fm.doubleVertixVector[i].centralmagnet]->orientation()
              * s.tab_ptr_Magnets[fm.doubleVertixVector[(i + 1) % facesize].centralmagnet]->orientation());
            scalarproducts.push_back(scalarp);
            barycenterofface += s.tab_ptr_Magnets[fm.doubleVertixVector[i].centralmagnet]->position;
            barycenterofface /= 5;
        }
        int streaksize     = 0;
        int maxstreaksize  = 1;
        int maxstreakindex = 0;
        for (size_t i = 0; i < 2 * scalarproducts.size(); ++i) {
            if (scalarproducts[i] > 0) { streaksize += 1; }
            if (streaksize >= maxstreaksize) {
                maxstreaksize  = streaksize;
                maxstreakindex = i;
            }
            if (scalarproducts[i] < 0) { streaksize = 0; }
        }
        // for orientation:
        Vecteur3D upwardorientation(barycenterofface - Dodec.position);
        double orientation = (s.tab_ptr_Magnets[fm.doubleVertixVector[i].centralmagnet]->orientation()
          ^ s.tab_ptr_Magnets[fm.doubleVertixVector[(i + 1) % facesize].centralmagnet]->orientation())
          * upwardorientation;
        if (orientation > 0) { return maxstreaksize; } else { return -1 * maxstreaksize; }
    }

    // energies:
    double vertixEnergy(vertixmagnets vm)
    {
        double Energy = 0;
        Energy += s.tab_ptr_Magnets[vm.magnet1]->spotB(s.tab_ptr_Magnets[vm.magnet2]);
        Energy += s.tab_ptr_Magnets[vm.magnet1]->spotB(s.tab_ptr_Magnets[vm.magnet3]);
        Energy += s.tab_ptr_Magnets[vm.magnet2]->spotB(s.tab_ptr_Magnets[vm.magnet3]);
        return Energy;
    }

    double doublevertixEnergy(doublevertix dv)
    {
        return vertixEnergy(dv.v1) + vertixEnergy(dv.v2);
    }

    double faceEnergy(facemagnets fm)
    {
        double Energy = 0;
        for (int i = 0; i < doubleVertixVector.size(); i++) {
            Energy +=
              s.tab_ptr_Magnets[doubleVertixVector[i].centralmagnet]->
              spotB(s.tab_ptr_Magnets[doubleVertixVector[(i + 1) % doubleVertixVector.size()].centralmagnet]);
        }
        return Energy;
    }

    // Correlation


    // output files:
    string outputPath;
    if (argc > 1) { // Fichier d'output specifie par l'utilisateur ("./Exercice8 config_perso.in")
        outputPath = argv[1];
    }

    string Vertex = outputPath + "Vertex"; // Energy //Oddoneout type //faces?
    unique_ptr<ofstream> tfile1(new ofstream(Vertex.c_str()));
    for (auto vm: VM) {
        *tfile1 << vertixEnergy(vm) << " " << Oddoneout(vm) << endl;
    }

    string Dvertex = outputPath + "Dvertex"; // central magnet index // Energy // type
    unique_ptr<ofstream> tfile2(new ofstream(Dvertex.c_str()));
    for (auto dv: DV) {
        *tfile2 << dv.centralmagnet << " " << doublevertixEnergy(dv) << " " << doublevertixstrengthDetailed(vm) << endl;
    }

    string Face = outputPath + "Faceparameters"; // Energy // type // 5 magnetsindex
    unique_ptr<ofstream> tfile3(new ofstream(Dvertex.c_str()));
    for (auto fm: FM) {
        *tfile3 << getFaceOrientaion(fm) << " " << faceEnergy(fm) << " ";
        for (auto dv: fm.doubleVertixVector) {
            *tfile3 << dv.centralmagnet << " ";
        }
        *tfile3 << endl;
    }

    // string MagnetsofFace = "FaceMagnetsindex";
    string Dvertexindex = "Dvertexindex";

    return 0;
} // main

// unique_ptr<ofstream> textfile0(new ofstream("Dodecedgesandvertices"));
// tfile->precision(20);
