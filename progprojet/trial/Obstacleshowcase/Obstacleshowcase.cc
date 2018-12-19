#include <QApplication>
#include "glwidget.h"
#include "Systeme.h"
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
#include "Mediumi.h"
#include "SystemeP9.h"
#include "SystemeP12.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    GLWidget w;
    GrainLJUn grainLJUn1(Position(5,5,5), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    GrainLJUn grainLJUn2(Position(2.0,20.0,3.0), Vitesse(0,0,10), 1.0, 0.4, Vecteur3D(), air);
    GrainLJUn grainLJUn3(Position(0.5, 0.866025, 0.0), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    GrainLJDeux grainLJDeux1(Position(3.5, 0.288675, 0.816497), Vitesse(), 1.0, 0.4, Vecteur3D(), air);
    Dalle dalle_obstacle(Position(0.0, 0.0, -0.9), Vecteur3D(0.0, 0.0, 1.0), Vecteur3D(0.0, 1.0, 0.0));
    Dalle dalle_obstacled(Position(25.0, -25.0, -4.9), Vecteur3D(0.0, 0.0, 1.0), Vecteur3D(0.0, 1.0, 0.0), 100.0, 200.0);
    Plan plan_obstacle(Position(0.0, 0.0, -10.0), Vecteur3D(0.0, 0.0, 1.0));
    Sphere sphere_obstacle(Position(17.0, 14.0, 5.0), 10.0, true);
    Sphere sphere_obstacle2(Position(2.0, 14.0, -1.0), 4.0, true);
		Cylinder cylindre_obstacle(Position(-15.0, 14.0,2.0), Vecteur3D(0,1,0), 4, 7);
    //Mediumi brique_obstacle(dalle_obstacled, 5.0);
    Brique brique_obstacle(dalle_obstacled, 5.0);
    Source source(Position(0.5,0,20), grainLJUn2, Vitesse(100,200,500), 50.2, 0.25, 30.27, true );
    Source source2(Position(5.5,14,20), grainLJDeux1, Vitesse(), 5.2, 0.25, 30.27, true );
    Source source3(Position(-5.5,14,20), grainLJDeux1, Vitesse(), 5.2, 0.25, 30.27, true );
    (w.s).ajouteGrain(grainLJUn1);
    (w.s).ajouteGrain(grainLJUn2);
    (w.s).ajouteGrain(grainLJUn3);
    (w.s).ajouteGrain(grainLJDeux1);
    (w.s).ajouteObstacle(plan_obstacle);
    //(w.s).ajouteMediumi(brique_obstacle);
    (w.s).ajouteObstacle(brique_obstacle);
    (w.s).ajouteObstacle(sphere_obstacle);
    (w.s).ajouteObstacle(sphere_obstacle2);
    (w.s).ajouteObstacle(cylindre_obstacle);
    (w.s).ajouteSource(source);
    (w.s).ajouteSource(source2);
    (w.s).ajouteSource(source3);
    w.show();


    return a.exec();
}
