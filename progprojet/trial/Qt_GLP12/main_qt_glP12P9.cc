#include <QApplication>
#include "glwidgetP12P9.h"
#include "Systeme.h"
#include "SystemeP9.h"
#include "SystemeP12.h"
#include "Medium.h"
#include "Vecteur3D.h"
#include "Plan.h"
#include "Dalle.h"
#include <vector>
#include "Sphere.h"
#include "Brique.h"
#include "Dodec.h"
#include "Cylinder.h"
#include "Window.h"
#include <iostream>
using namespace std;

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    Window w;
    MagnetEO M1(Position(2, 2, 0), 0.2, 1);

    /*MagnetE M2(Position(2,-2,0), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
     * MagnetE M3(Position(-2,-2,0), Vitesse(), 1.0, 0.2, Vecteur3D(), air,1 , Vecteur3D(1,1,1));
     * MagnetE M4(Position(-2,2,0), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
     * MagnetE M5(Position(2,2,4), Vitesse(), 1.0, 0.2, Vecteur3D(), air,1,Vecteur3D(1,1,0));
     * MagnetE M6(Position(2,-2,4), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
     * MagnetE M7(Position(-2,-2,4), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
     * MagnetE M8(Position(-2,2,4), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
     * Dalle dalle_obstacled(Position(0, 0, 0), Vecteur3D(0, 0.0, 1.0), Vecteur3D(0.0, 1.0, 0.0), 4, 4);
     * Brique b(dalle_obstacled, 4.0);*/
    Dodec dode(Vecteur3D(0, 0, 0), 4, Vecteur3D(0, 0, 1), false);
    Cylinder c1(Position(0, 10, 0), Vecteur3D(0, 7, 0), 1, 1);
    Cylinder c2(Position(10, 0, 0), Vecteur3D(7, 0, 0), 1, 1);
    Cylinder c3(Position(0, 0, 10), Vecteur3D(0, 0, 1), 1, 1);

    (w.glWidget)->addMagnet(M1);
    // All the magnets :D

    /*for (int i = 0; i < (dode.vertipositions()).size(); ++i) {
        int si = ((dode.vertipositions())[i]).size()
          for (int j = 0; j < si; ++j) {
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
            double alph; // angle of rotation arctan(2)
            v4 = v3.rotate(alph, v1);
            axe = v4^v1;
            // add magnet here.
        }
       }*/

    /*w.addMagnet(M2);
       w.addMagnet(M3);
       w.addMagnet(M4);
       w.addMagnet(M5);
       w.addMagnet(M6);
       w.addMagnet(M7);
       w.addMagnet(M8);*/
    // w.addObstacle(b);
    (w.glWidget)->addObstacle(c1);
    (w.glWidget)->addObstacle(c2);
    (w.glWidget)->addObstacle(c3);
    // w.addObstacle(dode);
    // w.addObstacle(dalle_obstacled);
    // w.addObstacle((b.dalle6())[3]);
    // w.addObstacle((b.dalle6())[4]);

    w.show();


    return a.exec();
} // main
