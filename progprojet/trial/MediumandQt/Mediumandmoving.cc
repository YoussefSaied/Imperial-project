#include <QApplication>
#include "glwidget.h"
#include "Systeme.h"
#include "Vecteur3D.h"
#include "Plan.h"
#include "Dalle.h"
#include <vector>
#include "Sphere.h"
#include "Brique.h"
#include "Cylinder.h"
#include "SystemeP9.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    GLWidget w;

    //Brique brique_obstacle(dalle_obstacled, 5.0);

    //(w.s).ajouteObstacle(brique_obstacle);
    //(w.s).ajouteObstacle(sphere_obstacle);

    w.show();


    return a.exec();
}
