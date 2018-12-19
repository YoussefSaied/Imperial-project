#include <QApplication>
#include "glwidgetP12P9.h"
#include "Systeme.h"
#include "SystemeP9.h"
#include "SystemeP12.h"
#include "GrainLJ.h"
#include "GrainLJUn.h"
#include "GrainLJDeux.h"
#include "Medium.h"
#include "Vecteur3D.h"
#include "Plan.h"
#include "Dalle.h"
#include <vector>
#include "Source.h"
#include "Sphere.h"
#include "Brique.h"
#include "Cylinder.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    GLWidget w;
    GrainLJUn grainLJUn1(Position(5,5,5), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    GrainLJUn grainLJUn2(Position(2.0,20.0,3.0), Vitesse(0,0,0), 1.0, 0.4, Vecteur3D(), air);
    GrainLJUn grainLJUn3(Position(0.5, 0.866025, 0.0), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    GrainLJDeux grainLJDeux1(Position(3.5, 0.288675, 0.816497), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    Dalle dalle_obstacle(Position(0.0, 0.0, -0.9), Vecteur3D(0.0, 0.0, 1.0), Vecteur3D(0.0, 1.0, 0.0));
    Dalle dalle_G1(Position(41.0, -1.0, 43.0), Vecteur3D(1.0, 0.0, 1.0), Vecteur3D(0.0, 1.0, 0.0),2.0,10.0);
    Dalle dalle_G2(Position(43.0, 2.0, 43.0), Vecteur3D(-1.0, 0.0, 1.0), Vecteur3D(0.0, -1.0, 0.0),2.0,10.0);
    Dalle dalle_obstacled(Position(85.0, -25.0, -4.9), Vecteur3D(0.0, 0.0, 1.0), Vecteur3D(0.0, 1.0, 0.0), 100.0, 86.0);
    Plan plan_obstacle(Position(0.0, 0.0, -10.0), Vecteur3D(0.0, 0.0, 1.0));
    Sphere sphere_obstacle(Position(0.0, 0.0, 4.0), 1.0);
    Brique brique_obstacle(dalle_obstacled, 5.0);
    Source source(Position(29,0,30), grainLJUn2, Vitesse(100,200,500), 50.2, 0.25, 100.27, true );
    Source source2(Position(42,0,55), grainLJUn2, Vitesse(), 5.2, 0.25, 100.27, true );
    for(int k(1); k <=2; ++k) {
        for (int j(1) ; j <= 5 ; ++j) {
            for(int i(1); i <= 13-k; ++i ) {
                w.ajouteObstacle(Cylinder(Position(6*i+3*k,0,6*j+3*k),Vecteur3D(0,1,0),1.0,1.0));
            }
        }
    }
    for (int i=0; i<=13; ++i) {
        w.ajouteObstacle(Dalle(Position(6*i +3 , -1.5 , -5.0 ),Vecteur3D(1.0,0,0),Vecteur3D(0,1,0),3.0 ,13.0 ));
    }
    w.ajouteObstacle(Dalle(Position(0.0 , 1.5 , 55.0 ),Vecteur3D(0,1.0,0),Vecteur3D(1.0,0,0),85.0,60.0  ));
    w.ajouteObstacle(Dalle(Position(0.0 , -1.5 , 55.0 ),Vecteur3D(0,1.0,0),Vecteur3D(1.0,0,0),85.0,60.0 ));
    w.ajouteObstacle(plan_obstacle);
    w.ajouteObstacle(dalle_G1);
    w.ajouteObstacle(dalle_G2);
    w.ajouteObstacle(brique_obstacle);
    w.ajouteSource(source2);
    w.show();


    return a.exec();
}
