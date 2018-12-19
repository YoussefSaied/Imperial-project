#include <iostream>
#include <vector>
#include "Vecteur3D.h"
#include "GrainsAvant.h"
#include <random>
using namespace std;

int main()
{

    Vecteur3D velocity0, position0, force0, force1;
    velocity0.random_vector();
    position0.random_vector();
    force0.random_vector();
    force1.random_vector();
    
    
    //test1: intialize and display and copy
    cout << "Bonjour! Ceci est un test de la classe Grain!" << endl;
    cout << endl;
    
    cout<<"TEST1: intialize and display and copy"<<endl<<endl;
    Grains grain1(position0, velocity0, force0, 1.0, 1.0);
    Grains grain2(grain1);
    cout<<"grain1"<<endl;
    grain1.display();
    cout << endl;
    
  
    cout<<"grain2 (copie de grain 1) "<<endl;
    grain2.display();


    //test2: ajoute force
    cout<<endl<<"TEST2: ajoute force"<<endl<<endl;
    grain1.ajouteForce();
    grain1.display();

    //test3: bouger
    cout<<endl<<"TEST3: boujer"<<endl<<endl;
    grain1.bouger(2.0);
    grain1.display();

    return 0;
}
