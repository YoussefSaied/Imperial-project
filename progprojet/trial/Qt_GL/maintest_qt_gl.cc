#include <QApplication>
#include "glwidget.h"
#include "Systeme.h"
#include "SystemeP9.h"
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
    Magnet M1(Position(0, 0, 0), Vecteur3D(0, 1, 0));
    Magnet M2(Position(0, 0, 0 + M1.length * 2.2), Vecteur3D(0, 1, 0));
    Magnet M3(Position(0 + M1.length * 1.039, 0, 0 + M1.length * 0.6), Vecteur3D(0, 1, 0));

    /*MagnetE M2(Position(2,-2,0), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
     * MagnetE M3(Position(-2,-2,0), Vitesse(), 1.0, 0.2, Vecteur3D(), air,1 , Vecteur3D(1,1,1));
     * MagnetE M4(Position(-2,2,0), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
     * MagnetE M5(Position(2,2,4), Vitesse(), 1.0, 0.2, Vecteur3D(), air,1,Vecteur3D(1,1,0));
     * MagnetE M6(Position(2,-2,4), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
     * MagnetE M7(Position(-2,-2,4), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
     * MagnetE M8(Position(-2,2,4), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
     * Dalle dalle_obstacled(Position(0, 0, 0), Vecteur3D(0, 0.0, 1.0), Vecteur3D(0.0, 1.0, 0.0), 4, 4);
     * Brique b(dalle_obstacled, 4.0);*/
    // Dodec dode(Vecteur3D(0, 0, 3), 4, Vecteur3D(0, -0.763932, 1.23607), false);
    Dodec dode(Vecteur3D(0, 0, 0), 3e-2, Vecteur3D(0, 0, 1.23607), false);
    Cylinder c1(Position(0, 10, 0), Vecteur3D(0, 7, 0), 1, 1);
    Cylinder c2(Position(10, 0, 0), Vecteur3D(7, 0, 0), 1, 1);
    Cylinder c3(Position(0, 0, 10), Vecteur3D(0, 0, 1), 1, 1);


    // All the magnets :D
    // int num = 0;


    (w.glWidget)->addMagnet(M1);
    (w.glWidget)->addMagnet(M2);
    //    (w.glWidget)->addMagnet(M3);
    //    (w.glWidget)->addMagnet(M4);
    //    (w.glWidget)->addMagnet(M5);
    //    (w.glWidget)->addMagnet(M6);
    //    (w.glWidget)->addMagnet(M7);
    //    (w.glWidget)->addMagnet(M8);
    //    (w.glWidget)->addMagnet(M9);
    (w.glWidget)->addObstacle(c1);
    (w.glWidget)->addObstacle(c2);
    (w.glWidget)->addObstacle(c3);
    //    (w.glWidget)->addObstacle(dode);
    // w.addObstacle(dode);
    // w.addObstacle(dalle_obstacled);
    // w.addObstacle((b.dalle6())[3]);
    // w.addObstacle((b.dalle6())[4]);
    // cout << endl << "number of magnets" << (((w.glWidget)->system_tab[0])->tab_ptr_Magnets).size() << endl;
    w.show();

    /*double b = (1 + sqrt(5)) / 2;
       Vecteur3D v1(1 / b, 0, b);
       Vecteur3D v2(-1 / b, 0, b);
       Vecteur3D v3(-1, -1, 1);
       Vecteur3D o1(v1 - v2);
       Vecteur3D o2(v2 - v3);
       Vecteur3D axer0(o1 ^ o2);
       cout << axer0;*/


    return a.exec();
} // main
