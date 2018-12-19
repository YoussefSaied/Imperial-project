#include <iostream>
#include "Vecteur3D.h"
#include "Grain.h"
#include "Plan.h"
#include "Dalle.h"
using namespace std;


int main(){
	Vecteur3D origin(0,0,0);
	Vecteur3D origin_(1, 2, 3);
	Vecteur3D Vp1(0, 0, 2); //vecteur normale a plan 1
	Vecteur3D Vp2(0, 1, 0); //vecteur normale a plan 2
	Vecteur3D Vp3(1, 0, 0); //vecteur normale a plan 3
	Vecteur3D Vp4(1, 1, 1); //vecteur normale a plan 4
	Vecteur3D Vp5(1.1, 3.3, 2.2); //vecteur normale a plan 5
	Vecteur3D p1(0, 7, 0); //point 1
	Vecteur3D p2(0, 0, 10); //point 2
	Vecteur3D p3(2, 0, 0); //point 3
	Vecteur3D p4(5, -4, 6); //point 4
	Plan Pl1(origin, Vp1); //plan1
	Plan Pl2(origin, Vp2); //plan2
	Plan Pl3(origin, Vp3); //plan3
	Plan Pl4(origin, Vp4); //plan4
	Plan Pl5(origin_, Vp5); // plan5
	Dalle dalle(origin, Vp1, Vp2); //Dalle1

	cout<<"Teste Plan : "<<endl;
	cout<<Pl1;
	Pl1.distancea(p1);
	cout<<endl;
	Pl1.distancea(p2);
	cout<<endl;
	Pl1.distancea(p3);
	cout<<endl;
	Pl1.distancea(p4);
	cout<<endl;

	cout<<endl;
	cout<<Pl2;
	Pl2.distancea(p1);
	cout<<endl;
	Pl2.distancea(p2);
	cout<<endl;
	Pl2.distancea(p3);
	cout<<endl;
	Pl2.distancea(p4);
	cout<<endl;


	cout<<endl;
	cout<<Pl3;
	Pl3.distancea(p1);
	cout<<endl;
	Pl3.distancea(p2);
	cout<<endl;
	Pl3.distancea(p3);
	cout<<endl;
	Pl3.distancea(p4);
	cout<<endl;


	cout<<endl;
	cout<<Pl4;
	Pl4.distancea(p1);
	cout<<endl;
	Pl4.distancea(p2);
	cout<<endl;
	Pl4.distancea(p3);
	cout<<endl;
	Pl4.distancea(p4);
	cout<<endl;

	cout<<endl;
	cout<<Pl5;
	Pl5.distancea(p1);
	cout<<endl;
	Pl5.distancea(p2);
	cout<<endl;
	Pl5.distancea(p3);
	cout<<endl;
	Pl5.distancea(p4);
	cout<<endl;

	cout<<endl;
	
	
	cout<<"Teste Dalle : "<<endl;
	cout<<dalle<<endl;
	dalle.distancea(p1);
	cout<<dalle.PointPlusProche(p1) <<endl;
	dalle.distancea(p2);
	cout<<dalle.PointPlusProche(p2) <<endl;
	dalle.distancea(p3);
	cout<<dalle.PointPlusProche(p3) <<endl;
	dalle.distancea(p4);
	cout<<dalle.PointPlusProche(p4) <<endl;

	return 0;}
