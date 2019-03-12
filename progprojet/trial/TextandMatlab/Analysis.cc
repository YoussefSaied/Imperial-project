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


// functions and structures and variables:
Dodec dode(Vecteur3D(0, 0, 0), 3e-2, Vecteur3D(0, 0, 1.23607), false);
// The system:
Systeme s;
// functions and structures are easily generalisable to all solids, would be better with classes

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


// tables:
vector<vertixmagnets> VM;
vector<doublevertix> DV;
vector<facemagnets> FM;

// Matlab stuff :( / functions ::

// Vertix strength (f/w):

int Oddoneout(vertixmagnets vm)
{
    double p12 = s.tab_ptr_Magnets[vm.magnet1]->orientation() * s.tab_ptr_Magnets[vm.magnet2]->orientation();
    double p13 = s.tab_ptr_Magnets[vm.magnet1]->orientation() * s.tab_ptr_Magnets[vm.magnet3]->orientation();
    double p23 = s.tab_ptr_Magnets[vm.magnet2]->orientation() * s.tab_ptr_Magnets[vm.magnet3]->orientation();
    if (p12 > 0 and p13 > 0) { return vm.magnet1; }
    if (p12 > 0 and p23 > 0) { return vm.magnet2; }
    if (p23 > 0 and p13 > 0) { return vm.magnet3; }
    return -1;
} // sends back oddmagnet index

int doublevertixstrength(doublevertix dv)
{
    if (Oddoneout(dv.v1) == dv.centralmagnet and Oddoneout(dv.v2) == dv.centralmagnet) { return 3; } // ff
    else if (Oddoneout(dv.v1) != dv.centralmagnet and Oddoneout(dv.v2) == dv.centralmagnet) {
        return 2; // fw
    } else if (Oddoneout(dv.v1) == dv.centralmagnet and Oddoneout(dv.v2) !=
      dv.centralmagnet)
    {
        return 1; // wf
    } else if (Oddoneout(dv.v1) != dv.centralmagnet and Oddoneout(dv.v2) !=
      dv.centralmagnet)
    {
        return 0; // ww
    }
    return -1;
}

bool doublevertixup(doublevertix dv, int magnetindex)
{
    Vecteur3D barycenterofdv = s.tab_ptr_Magnets[dv.centralmagnet]->position;
    Vecteur3D upwardOrientation(barycenterofdv - dode.position);
    double seperationAfterorientation1 =
      (s.tab_ptr_Magnets[magnetindex]->position
      + s.tab_ptr_Magnets[magnetindex]->orientation() * s.tab_ptr_Magnets[magnetindex]->length / 2
      - barycenterofdv ).norme();
    double seperationAfterorientation2 = // reorienting the central magnet orientation
      (-1 * s.tab_ptr_Magnets[magnetindex]->position
      + s.tab_ptr_Magnets[dv.centralmagnet]->orientation() * s.tab_ptr_Magnets[magnetindex]->length / 2
      + barycenterofdv ).norme();
    double seperationBetweencenters =
      (s.tab_ptr_Magnets[magnetindex]->position
      - barycenterofdv ).norme();
    int fixer = 1;
    if (seperationAfterorientation1 < seperationBetweencenters) { fixer *= -1; } // fixing branch magnet
    if (seperationAfterorientation2 > seperationBetweencenters) { fixer *= -1; } // fixing centralmagnet
    if (fixer
      * ((s.tab_ptr_Magnets[magnetindex]->orientation() ^ s.tab_ptr_Magnets[dv.centralmagnet]->orientation())
      * upwardOrientation) > 0) { return 1; }
    return 0;
}

int finddoublevertix(int magnetindex)
{
    for (size_t i = 0; i < DV.size(); i++) {
        if (DV[i].centralmagnet == magnetindex) { return i; }
    }
    return -1;
}

int doublevertixstrengthRelative(doublevertix dv, int magnetindex)
{
    int strength = 0;
    int doublevertixindexofmagnet = finddoublevertix(magnetindex);
    if (doublevertixstrength(DV[doublevertixindexofmagnet]) ==
      0 or doublevertixstrength(DV[doublevertixindexofmagnet]) == 3)
    {
        strength = doublevertixstrength(DV[doublevertixindexofmagnet]);
    } else {
        if (Oddoneout(dv.v1) == DV[doublevertixindexofmagnet].centralmagnet) {
            strength = 2;
        } else { strength = 1; }
    }
    return strength;
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
    }
    barycenterofface = barycenterofface / facesize;
    int streaksize     = 0;
    int maxstreaksize  = 1;
    int maxstreakindex = 0;
    for (size_t i = 0; i < 2 * scalarproducts.size(); ++i) {
        if (scalarproducts[i % scalarproducts.size()] > 0) { streaksize += 1; }
        if (streaksize >= maxstreaksize) {
            maxstreaksize  = streaksize;
            maxstreakindex = i;
        }
        if (scalarproducts[i] < 0) { streaksize = 0; }
    }
    // for orientation:
    Vecteur3D upwardorientation(barycenterofface - dode.position);
    double orientation =
      (s.tab_ptr_Magnets[fm.doubleVertixVector[maxstreakindex % facesize].centralmagnet]->orientation()
      ^ s.tab_ptr_Magnets[fm.doubleVertixVector[(maxstreakindex + 1) % facesize].centralmagnet]->orientation())
      * upwardorientation;
    if (orientation > 0) { return maxstreaksize % (facesize + 1); } else {
        return -1 * maxstreaksize % (facesize + 1);
    }
} // getFaceOrientaion

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
    for (size_t i = 0; i < fm.doubleVertixVector.size(); i++) {
        Energy +=
          s.tab_ptr_Magnets[fm.doubleVertixVector[i].centralmagnet]->
          spotB(s.tab_ptr_Magnets[fm.doubleVertixVector[(i + 1) % fm.doubleVertixVector.size()].centralmagnet]);
    }
    return Energy;
}

int main(int argc, char * argv[])
{
    // VM initialisation:
    vector<vector<Vecteur3D> > vertixpositions = dode.vertipositions();

    for (size_t i = 0; i < vertixpositions.size(); ++i) {
        size_t si = (vertixpositions[i]).size();
        for (size_t j = 0; j < si; ++j) {
            int exists = -1;
            for (size_t l = 0; l < VM.size(); ++l) {
                if (vertixpositions[i][j] == VM[l].position) { exists = l; }
            }
            if ((exists == -1)) {
                VM.push_back({ vertixpositions[i][j], -1, -1, -1 });
            }
        }
    }

    for (size_t i = 0; i < (dode.vertipositions()).size(); ++i) {
        size_t si = ((dode.vertipositions())[i]).size();
        for (size_t j = 0; j < si; ++j) {
            Vecteur3D pos( ((dode.vertipositions())[i][j] + (dode.vertipositions())[i][(j + 1) % si]) / 2);
            Vecteur3D polaraxis = (dode.vertipositions())[i][j] - (dode.vertipositions())[i][(j + 1) % si];
            Vecteur3D v2        =
              ((dode.vertipositions())[i][(j + 1) % si] - (dode.vertipositions())[i][(j + 2) % si]);
            Vecteur3D v3  = polaraxis ^ v2;
            double alph1  = -1 * atan(2) / 2;
            Vecteur3D v4  = v3.rotate(alph1, polaraxis);
            Vecteur3D axe = (v4 ^ polaraxis).normalise();

            Magnet M(pos, axe, 1, 0, polaraxis); // position pos, axis axe, movable yes, angle_0 0, polaraxis

            int index;
            // if (s.addMagnet(M)  { index = (s.tab_ptr_Magnets.size() - 1); }
            index = s.addMagnet(M);

            // VM:
            for (auto vm: VM) {
                if ((vm).position == (dode.vertipositions())[i][j]) {
                    if (vm.magnet1 == -1) {  vm.magnet1 = index; } else if (vm.magnet2 == -1) {
                        vm.magnet2 = index;
                    } else if (vm.magnet3 == -1) { vm.magnet3 = index; }
                }
                if ((vm).position == (dode.vertipositions())[i][(j + 1) % si]) {
                    if (vm.magnet1 == -1) { vm.magnet1 = index; } else if (vm.magnet2 == -1) {
                        vm.magnet2 = index;
                    } else if (vm.magnet3 == -1) { vm.magnet3 = index; }
                }
            }
        }
    }


    // DV:
    for (size_t i = 0; i < VM.size(); ++i) {
        for (size_t j = i + 1; j < VM.size(); ++j) {
            if (VM[i].magnet1 == VM[j].magnet1) {
                DV.push_back({ VM[j].magnet1, VM[i], VM[j] });
            }
            if (VM[i].magnet2 == VM[j].magnet2) {
                DV.push_back({ VM[j].magnet2, VM[i], VM[j] });
            }
            if (VM[i].magnet3 == VM[j].magnet3) {
                DV.push_back({ VM[j].magnet3, VM[i], VM[j]  });
            }
        }
    }

    // Facevector (FM):
    for (size_t i = 0; i < vertixpositions.size(); ++i) {
        vector<doublevertix> VectorDVelem;
        size_t si = (vertixpositions[i]).size();
        for (size_t j = 0; j < si; ++j) {
            for (auto DVelem: DV) {
                if (DVelem.v1.position == vertixpositions[i][j] and DVelem.v2.position ==
                  vertixpositions [i][(j + 1) % si]) { VectorDVelem.push_back(DVelem); }
                if (DVelem.v2.position == vertixpositions[i][j] and DVelem.v1.position ==
                  vertixpositions [i][(j + 1) % si]) { VectorDVelem.push_back(DVelem); }
            }
        }
        FM.push_back({ VectorDVelem, -10 });
    }

    // set angles:
    s.setangles("finalangles.in");


    /*
       I think this is the most logical way to do it:
       Rather than working out the angles from the indices in Matlab, we
       do it here so that we have 4 files:

       Magnet: [angle, moment, Vtype (ff,fw,ww)] (x30)
       Vertex: [anglex3, Energy] (x20)
       DVertex: [anglex5, Energy, Dtype] (x30)
       Face: [anglex5, Vtypex5, Ftype, Energy] (x12)

       Vtype = ff,fw,ww
       Dtype = intx5 eg ww-ww-ff-ww-ww
       Ftype = 5,4,3,2
     */

    // output files:
    string outputPath;
    if (argc > 1) { // Fichier d'output specifie par l'utilisateur ("./Exercice8 config_perso.in")
        outputPath = argv[1];
    }

    // create:
    //////Magnet: // Angle // Moment // Type
    string Magnet = outputPath + "Magnet";
    unique_ptr<ofstream> tfile0(new ofstream(Magnet.c_str()));

    ///////VERTEX: // Angles (x3) // Energy
    // comments:  Oddoneout gives index of forced magnet
    string Vertex = outputPath + "Vertex";
    unique_ptr<ofstream> tfile1(new ofstream(Vertex.c_str()));
    for (auto vm: VM) {
        *tfile1 << vertixEnergy(vm) << " " << Oddoneout(vm) << endl;
    }

    ////DOUBLE VERTEX: // Angles (x5) // Energy // type
    // comments: type = int with 5 digits, each digit has value 3,2,1,0
    // digits correspond to magnets in double vertex (3rd digit is central mag)
    // values correspond to ff=3,fw=2,wf=1,ww=0
    string Dvertex = outputPath + "Dvertex";
    unique_ptr<ofstream> tfile2(new ofstream(Dvertex.c_str()));
    for (auto dv: DV) {
        *tfile2 << dv.centralmagnet << " " << doublevertixEnergy(dv) << " " << doublevertixstrengthDetailed(dv) << endl;
    }

    ////FACE: // Angles (x5) // orientation // Energy // types
    // comments: orientation gives max streak size = 5,4,3,2 (-1,1 for CW,ACW)
    // Y: We can use the index to get all the information we might need
    string Face = outputPath + "Faceparameters";
    unique_ptr<ofstream> tfile3(new ofstream(Dvertex.c_str()));
    for (auto fm: FM) {
        for (auto dv: fm.doubleVertixVector) {
            *tfile3 << doublevertixstrengthDetailed(dv) << " ";
        }
        *tfile3 << getFaceOrientaion(fm) << " " << faceEnergy(fm) << " ";
        *tfile3 << endl;
    }

    // string MagnetsofFace = "FaceMagnetsindex";
    string Dvertexindex = "Dvertexindex";

    return 0;
} // main
