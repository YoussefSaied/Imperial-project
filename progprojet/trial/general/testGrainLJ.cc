#include <iostream>
#include <vector>
#include "Vecteur3D.h"
#include "Grain.h"
#include "GrainLJ.h"
#include "Medium.h"
#include "SupportADessinTexte.h"

using namespace std;

int main()
{

	Vecteur3D velocity0, position0, force0, force1;
	/** velocity0.random_vector();
	position0.random_vector();
	force0.random_vector();
	force1.random_vector(); **/
	velocity0.set_coord(1.0, 2.0 ,3.0 );
	position0.set_coord(4.0, 5.0 ,6.0 );
	force0.set_coord(7.0, 8.0, 9.0);
	
	//test1: intialize and display and copy
	cout<<endl<<"TEST1: intialize and display and copy"<<endl<<endl;

	GrainLJ grain1(position0, velocity0, 1.0, 1.0, force0);
	GrainLJ grain2(grain1);
	cout<<"grain1 :"<<endl;
	cout<<grain1;
	cout<<"grain2 :"<<endl;
	cout<<grain2;


	//test2: ajoute force
	Grain* grain6(&grain1);
	cout<<endl<<"TEST2: ajoute force"<<endl<<endl;
	(*grain6).ajouteForce();
	cout<<grain1;

	//test3: bouger
	cout<<endl<<"TEST3: boujer"<<endl<<endl;
	grain1.bouger(2.0);
	cout<<grain1;


	//test4: copie
	cout<<endl<<"TEST4: copie"<<endl<<endl;
	{GrainLJ grain3(grain1);
	cout<<"grain3: "<<endl<<grain3<<endl;
	(*(grain3.get_medium())).display();}
	cout<<"grain1: "<<endl<<grain1<<endl;
	(*(grain1.get_medium())).display();
	cout<<endl<<endl;
	GrainLJ grain4(grain1);
	grain4.set_medium(air);
	cout<<"grain4: "<<endl<<grain4<<endl;
	(*(grain4.get_medium())).display();
	cout<<"grain1: "<<endl<<grain1<<endl;
	(*(grain1.get_medium())).display();



	return 0;
	}
