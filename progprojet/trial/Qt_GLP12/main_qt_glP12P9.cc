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
#include "Cylinder.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    GLWidget w;
		MagnetE M1(Position(2,2,0), Vitesse(), 1.0, 0.2, Vecteur3D(), air,1 , Vecteur3D(1,1,0));
		MagnetE M2(Position(2,-2,0), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
		MagnetE M3(Position(-2,-2,0), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
		MagnetE M4(Position(-2,2,0), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
		MagnetE M5(Position(2,2,4), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
		MagnetE M6(Position(2,-2,4), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
		MagnetE M7(Position(-2,-2,4), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
		MagnetE M8(Position(-2,2,4), Vitesse(), 1.0, 0.2, Vecteur3D(), air);
		Dalle dalle_obstacled(Position(0, 0, 0), Vecteur3D(0, 0.0, 1.0), Vecteur3D(0.0, 1.0, 0.0), 4, 4);
	  Brique b(dalle_obstacled, 4.0);
		Cylinder c1(Position(0,0,10),Vecteur3D(7,7,0),1,1);
		Cylinder c2(Position(0,0,10),Vecteur3D(7,0,0),1,1);
		Cylinder c3(Position(0,0,10),Vecteur3D(0,0,1),1,1);
		w.addMagnet(M1);
		w.addMagnet(M2);
		w.addMagnet(M3);
		w.addMagnet(M4);
		w.addMagnet(M5);
		w.addMagnet(M6);
		w.addMagnet(M7);
		w.addMagnet(M8);
		w.addObstacle(b);
		w.addObstacle(c1);
		w.addObstacle(c2);
		w.addObstacle(c3);
		//w.addObstacle(dalle_obstacled);
		//w.addObstacle((b.dalle6())[3]);
		//w.addObstacle((b.dalle6())[4]);

    w.show();


    return a.exec();
}
