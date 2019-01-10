#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "Systeme.h"
#include "SystemeP9.h"
#include "SystemeP12.h"
#include "Dalle.h"
#include "Sphere.h"
#include "Brique.h"
#include "Cylinder.h"
#include "Mediumi.h"
//#include <GL/glut.h>
using namespace std;

//               = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

void VueOpenGL::dessine(MagnetE const& M )
{		//rotate
		Vecteur3D axer(M.get_moment()^Vecteur3D(0,0,1));
		double angle= acos((M.get_moment()*Vecteur3D(0,0,1))/(M.get_moment().norme()));

		std::cout << "angleMM:" << axer << angle <<-1*angle*180/M_PI<<" "<<axer.get_x()<<'\n';


				QMatrix4x4 matrice2;



			//	matrice2.rotate(-1*angle*180/M_PI,axer.get_x(),axer.get_y(),axer.get_z());
				matrice2.setToIdentity();
				matrice2.translate((M.get_position()).get_x(),(M.get_position()).get_y(),(M.get_position()).get_z());
				if(axer != 0) matrice2.rotate(-1*angle*180/M_PI,axer.get_x(),axer.get_y(),axer.get_z());
				matrice2.translate(0,0,-1*M.get_height()/2);
				prog.setUniformValue("vue_modele", matrice_vue * matrice2);
				prog.setAttributeValue(CouleurId, 0.7, 0, 0);  // met la couleur
				cylinder.set_dimension(M.get_radius(),M.get_height()/2);
				cylinder.initialize();
				cylinder.draw(prog, SommetId);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		QMatrix4x4 matrice;
		matrice.setToIdentity();
		//matrice.rotate(-1*angle*180/M_PI,axer.get_x(),axer.get_y(),axer.get_z());
    matrice.translate((M.get_position()).get_x(),(M.get_position()).get_y(),(M.get_position()).get_z());
		if(axer != 0) matrice.rotate(-1*angle*180/M_PI,axer.get_x(),axer.get_y(),axer.get_z());

		//matrice.scale(M.get_radius(),M.get_radius(),M.get_height()/2);
//matrice.rotate(-90,1,0,0);
		//prog.setUniformValue("vue_modele", matrice_vue * matrice);
	//	prog.setAttributeValue(CouleurId, 0, 0, 0.7);  // met la couleur
		//cylinder.set_dimension(M.get_radius(),M.get_height()/2);
		//cylinder.initialize();
		//cylinder.draw(prog, SommetId);
		dessineCylinder(matrice,0,0,0.7);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


}

void VueOpenGL::dessine(MagnetEO const& M )
{
		//rotate
		Vecteur3D axer(M.get_moment()^Vecteur3D(1,0,0));
		double angle= acos((M.get_moment()*Vecteur3D(1,0,0))/(M.get_moment().norme()));

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		QMatrix4x4 matrice;

    matrice.translate(0,0,M.get_height()/2);
    matrice.translate((M.get_position()).get_x(),(M.get_position()).get_y(),(M.get_position()).get_z());

		matrice.rotate(angle,axer.get_x(),axer.get_y(),axer.get_z());

		GLCylinder cylinderm;
		prog.setUniformValue("vue_modele", matrice_vue * matrice);
		prog.setAttributeValue(CouleurId, 0.7, 0, 0);  // met la couleur
		cylinderm.set_dimension(M.get_radius(),M.get_height()/2);
		cylinderm.initialize();
		cylinderm.draw(prog, SommetId);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		/*glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		QMatrix4x4 matrice2;
		matrice2.translate(0,0,-1*M.get_height()/2);
		matrice2.translate((M.get_position()).get_x(),(M.get_position()).get_y(),(M.get_position()).get_z());
		matrice2.rotate(angle,axer.get_x(),axer.get_y(),axer.get_z());

		GLCylinder cylinderm2;
		prog.setUniformValue("vue_modele", matrice_vue * matrice2);
		prog.setAttributeValue(CouleurId, 0, 0, 0.7);  // met la couleur
		cylinderm2.set_dimension(M.get_radius(),M.get_height()/2);
		cylinderm2.initialize();
		cylinderm2.draw(prog, SommetId);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);*/

}



void VueOpenGL::dessine(Sphere const& sphere )
{
    QMatrix4x4 matrice;
    matrice.translate((sphere.get_position()).get_x(),(sphere.get_position()).get_y(),(sphere.get_position()).get_z());
    matrice.scale(sphere.get_radius()); //changer scale
    dessineSphere(matrice,1,0,1); //couleur

}
void VueOpenGL::dessine(Plan const& P)
{
    QMatrix4x4 matrice;
    dessinePlan(matrice, P);
}
void VueOpenGL::dessine(Dalle const& d)
{
    QMatrix4x4 matrice;
    dessineDalle(matrice, d);
}


void VueOpenGL::dessine(Brique const& b){
		std::vector<Dalle> d6;
		d6 = (b.dalle6());
		for(auto d : d6){
			d.set_support(b.get_support());
			d.dessine();
		}
}

void VueOpenGL::dessine(Dodec const& d){
	QMatrix4x4 matrice;
	matrice.setToIdentity();
	matrice.scale(d.get_edge());
	matrice.translate((d.get_position()).get_x(),(d.get_position()).get_y(),(d.get_position()).get_z());
	//matrice
	dessineDodec(matrice);
}

void VueOpenGL::dessine(Mediumi const& M){

	/**/
	std::vector<Dalle> d5;
	d5 = (M.dalle5());
	for(auto& d : d5){
		d.set_support(M.get_support());
		QMatrix4x4 matrice;
		dessineDalle(matrice, d ,0.0,0.0,0.2);}
}

void VueOpenGL::dessine(Cylinder const& c){

	Vecteur3D axer(Vecteur3D(0,0,1)^(c.get_vecteur_1()).normalise());
	double angle= acos((c.get_vecteur_1()*Vecteur3D(0,0,1))/((c.get_vecteur_1()).norme()));

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	QMatrix4x4 matrice;
	std::cout << "angle:" << axer << angle <<(c.get_vecteur_1()).norme()<< "produ"<< c.get_vecteur_1()*Vecteur3D(0,0,1)<<'\n';
	std::cout << "2 vectors:" << c.get_vecteur_1()<< Vecteur3D(0,0,1)<<'\n';


	matrice.translate((c.get_position()).get_x(),(c.get_position()).get_y(),(c.get_position()).get_z());

	//matrice.rotate(-90,0,0,1);
	//matrice.rotate(-90,1,0,0);
	if(axer != 0) matrice.rotate(1*angle*180/M_PI,axer.get_x(),axer.get_y(),axer.get_z());
	//matrice.rotate(-90,1,0,0);
	//matrice.rotate(-90,1,0,0);

	//matrice.scale(c.get_radius()); //changer scale
	GLCylinder cylinderm;
	prog.setUniformValue("vue_modele", matrice_vue * matrice);
	prog.setAttributeValue(CouleurId, 0.5, 0.5, 0.5);  // met la couleur
	cylinderm.set_dimension(c.get_radius(),c.get_hauteur());
	cylinderm.initialize();
	cylinderm.draw(prog, SommetId);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void VueOpenGL::dessine(SystemeP9 const& S)
{
		(S.notre_Dalle).dessine();
		if(!(S.tab_ptr_mediums).empty()) {
			for(auto const& ptr_medium : (S.tab_ptr_mediums)) {
					(*ptr_medium).dessine();}}


    if(!(S.tab_ptr_Magnets).empty()) {
        for(auto const& ptr_Magnet : (S.tab_ptr_Magnets)) {
            (*ptr_Magnet).dessine();
        }
    }
    if((S.tab_ptr_obstacles).size() != 0) {
        for(auto const& ptr_obstacle : (S.tab_ptr_obstacles)) {
            (*ptr_obstacle).dessine();
        }
    }

}

void VueOpenGL::dessine(SystemeP12 const& S)
{
	if(!(S.tab_ptr_mediums).empty()) {
		for(auto const& ptr_medium : (S.tab_ptr_mediums)) {
				(*ptr_medium).dessine();}}

    if(!(S.tab_case).empty()) {
			for(auto& i : S.tab_case){
				for(auto& j: i){
					for(auto& k: j ) {
		        	for(auto& g : k){
								g->dessine();}}}}
    }
    if((S.tab_ptr_obstacles).size() != 0) {
        for(auto const& ptr_obstacle : (S.tab_ptr_obstacles)) {
            (*ptr_obstacle).dessine();
        }
    }

}
//               = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
void VueOpenGL::init()
{
    /* Initialise notre vue OpenGL.
     * Dans cet exemple, nous créons et activons notre shader.
     *
     * En raison du contenu des fichiers *.glsl, le shader de cet exemple
     * NE permet QUE de dessiner des primitives colorées
     * (pas de textures, brouillard, reflets de la lumière ou autres).
     *
     * Il est séparé en deux parties VERTEX et FRAGMENT.
     * Le VERTEX :
     * - récupère pour chaque sommet des primitives de couleur (dans
     * l'attribut couleur) et de position (dans l'attribut sommet)
     * - multiplie l'attribut sommet par les matrices 'vue_modele' et
     * 'projection' et donne le résultat à OpenGL
     * - passe la couleur au shader FRAGMENT.
     *
     * Le FRAGMENT :
     * - applique la couleur qu'on lui donne
     */

    prog.addShaderFromSourceFile(QGLShader::Vertex, ":/vertex_shader.glsl");
    prog.addShaderFromSourceFile(QGLShader::Fragment, ":/fragment_shader.glsl");

    /* Identifie les deux attributs du shader de cet exemple
     * (voir vertex_shader.glsl).
     *
     * L'attribut identifié par 0 est particulier, il permet d'envoyer un
     * nouveau "point" à OpenGL
     *
     * C'est pourquoi il devra obligatoirement être spécifié et en dernier
     * (après la couleur dans cet exemple, voir plus bas).
     */

    prog.bindAttributeLocation("sommet", SommetId);
    prog.bindAttributeLocation("couleur", CouleurId);

    // Compilation du shader OpenGL
    prog.link();

    // Activation du shader
    prog.bind();

    /* Activation du "Test de profondeur" et du "Back-face culling"
     * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
     * partielement caché par d'autres objets.
     *
     * Le Back-face culling consiste à ne dessiner que les face avec ordre
     * de déclaration dans le sens trigonométrique.
     */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
		/*if (alpha){
					glDisable(GL_DEPTH_TEST);
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				} */

    sphere.initialize();                                      // initialise la sphère
    cylinder.initialize();                                      // initialise cylinder

		initializePosition();
}

//               = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
void VueOpenGL::initializePosition()
{
    // position initiale
    matrice_vue.setToIdentity();
    //matrice_vue.translate(0.0, 0.0, -15.0);
    matrice_vue.rotate(-90.0, 1.0, 0.0, 0.0);
}

//               = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
void VueOpenGL::translate(double x, double y, double z)
{
    /* Multiplie la matrice de vue par LA GAUCHE.
     * Cela fait en sorte que la dernière modification apportée
     * à la matrice soit appliquée en dernier (composition de fonctions).
     */
    QMatrix4x4 translation_supplementaire;
    translation_supplementaire.translate(x, y, z);
    matrice_vue    = translation_supplementaire * matrice_vue;
}

//               = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z)
{
    // Multiplie la matrice de vue par LA GAUCHE
    QMatrix4x4 rotation_supplementaire;
    rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
    matrice_vue    = rotation_supplementaire * matrice_vue;
}

//               = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
void VueOpenGL::dessineCube (QMatrix4x4 const& point_de_vue)
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_QUADS);
    // face coté X = +1
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
    prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
    prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
    prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

    // face coté X = -1
    prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
    prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
    prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
    prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

    // face coté Y = +1
    prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
    prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
    prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
    prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
    prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

    // face coté Y = -1
    prog.setAttributeValue(CouleurId, 0.0, 1.0, 1.0); // cyan
    prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
    prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

    // face coté Z = +1
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0); // jaune
    prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
    prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
    prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
    prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

    // face coté Z = -1
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 1.0); // magenta
    prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
    prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
    prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

    glEnd();
}
void VueOpenGL::dessinePenta (QMatrix4x4 const& point_de_vue,Vecteur3D x1,Vecteur3D x2,Vecteur3D x3,Vecteur3D x4,Vecteur3D x5)
{		Vecteur3D c(0,0,0);
		c= (x1 +x2 +x3+x4 +x5)/5;
		prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
		glBegin(GL_TRIANGLE_FAN);
		prog.setAttributeValue(CouleurId, 1.0, 0.0, 1.0); // magenta
		//prog.setAttributeValue(SommetId,c.get_x(), c.get_y(), c.get_z());
		prog.setAttributeValue(SommetId,x1.get_x(), x1.get_y(), x1.get_z());
		prog.setAttributeValue(SommetId,x2.get_x(), x2.get_y(), x2.get_z());
		prog.setAttributeValue(SommetId,x3.get_x(), x3.get_y(), x3.get_z());
		prog.setAttributeValue(SommetId,x4.get_x(), x4.get_y(), x4.get_z());
		prog.setAttributeValue(SommetId,x5.get_x(), x5.get_y(), x5.get_z());
		glEnd();
		//draw lines glBegin(GL_LINES);
		dessineLine(point_de_vue, x1,x2);
		dessineLine(point_de_vue, x2,x3);
		dessineLine(point_de_vue, x3,x4);
		dessineLine(point_de_vue, x4,x5);
		dessineLine(point_de_vue, x5,x1);
}
void VueOpenGL::dessineDodec (QMatrix4x4 const& point_de_vue)
{
		double a= (1+ sqrt(5))/2;
		QMatrix4x4 m;
		m.setToIdentity();
		dessinePenta(point_de_vue,Vecteur3D(1/a,0,a),Vecteur3D(-1/a,0,a),Vecteur3D(-1,-1,1),Vecteur3D(0,-a,1/a),Vecteur3D(1,-1,1)); //1
		dessinePenta(point_de_vue,Vecteur3D(-1,-1,1),Vecteur3D(-a,-1/a,0),Vecteur3D(-1,-1,-1),Vecteur3D(0,-a,-1/a),Vecteur3D(0,-a,1/a)); //2
		dessinePenta(point_de_vue,Vecteur3D(0,-a,1/a),Vecteur3D(0,-a,-1/a),Vecteur3D(1,-1,-1),Vecteur3D(a,-1/a,0),Vecteur3D(1,-1,1)); //3
		dessinePenta(point_de_vue,Vecteur3D(1/a,0,a),Vecteur3D(1,1,1),Vecteur3D(a,1/a,0),Vecteur3D(a,-1/a,0),Vecteur3D(1,-1,1)); //4 needs to be flipped
		dessinePenta(point_de_vue,Vecteur3D(1/a,0,-a),Vecteur3D(1,1,-1),Vecteur3D(a,1/a,0),Vecteur3D(a,-1/a,0),Vecteur3D(1,-1,-1));  //5
		dessinePenta(point_de_vue,Vecteur3D(1/a,0,-a),Vecteur3D(1,-1,-1),Vecteur3D(0,-a,-1/a),Vecteur3D(-1,-1,-1),Vecteur3D(-1/a,0,-a)); //6
		dessinePenta(point_de_vue,Vecteur3D(1/a,0,-a),Vecteur3D(1,1,-1),Vecteur3D(0,a,-1/a),Vecteur3D(-1,1,-1),Vecteur3D(-1/a,0,-a)); //7
		dessinePenta(point_de_vue,Vecteur3D(-1,-1,-1),Vecteur3D(-a,-1/a,0),Vecteur3D(-a,1/a,0),Vecteur3D(-1,1,-1),Vecteur3D(-1/a,0,-a)); //8
		dessinePenta(point_de_vue,Vecteur3D(-1,1,1),Vecteur3D(-a,1/a,0),Vecteur3D(-a,-1/a,0),Vecteur3D(-1,-1,1),Vecteur3D(-1/a,0,a)); //9
		dessinePenta(point_de_vue,Vecteur3D(-1,1,1),Vecteur3D(-1/a,0,a), Vecteur3D(1/a,0,a),Vecteur3D(1,1,1),Vecteur3D(0,a,1/a));  //10 needs to be flipped
		dessinePenta(point_de_vue,Vecteur3D(-1,1,1),Vecteur3D(-a,1/a,0),Vecteur3D(-1,1,-1),Vecteur3D(0,a,-1/a),Vecteur3D(0,a,1/a)); //11
		dessinePenta(point_de_vue,Vecteur3D(1,1,-1),Vecteur3D(0,a,-1/a),Vecteur3D(0,a,1/a),Vecteur3D(1,1,1),Vecteur3D(a,1/a,0)); //12 needs to be flipped
}
void VueOpenGL::dessineDalle (QMatrix4x4 const& point_de_vue, Dalle dalle,double x, double y, double z)
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_QUADS);
    prog.setAttributeValue(CouleurId, x, y, z); // jaune
    prog.setAttributeValue(SommetId, (dalle.Sommet1()).get_x(), (dalle.Sommet1()).get_y(), (dalle.Sommet1()).get_z());
    prog.setAttributeValue(SommetId, (dalle.Sommet2()).get_x(), (dalle.Sommet2()).get_y(), (dalle.Sommet2()).get_z());
    prog.setAttributeValue(SommetId, (dalle.Sommet3()).get_x(), (dalle.Sommet3()).get_y(), (dalle.Sommet3()).get_z());
    prog.setAttributeValue(SommetId, (dalle.Sommet4()).get_x(), (dalle.Sommet4()).get_y(), (dalle.Sommet4()).get_z());
    glEnd();
		glBegin(GL_LINES);
		prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
		prog.setAttributeValue(SommetId, (dalle.Sommet1()).get_x(), (dalle.Sommet1()).get_y(), (dalle.Sommet1()).get_z());
		prog.setAttributeValue(SommetId, (dalle.Sommet2()).get_x(), (dalle.Sommet2()).get_y(), (dalle.Sommet2()).get_z());
		glEnd();
		glBegin(GL_LINES);
		prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
		prog.setAttributeValue(SommetId, (dalle.Sommet1()).get_x(), (dalle.Sommet1()).get_y(), (dalle.Sommet1()).get_z());
    prog.setAttributeValue(SommetId, (dalle.Sommet4()).get_x(), (dalle.Sommet4()).get_y(), (dalle.Sommet4()).get_z());
		glEnd();
		glBegin(GL_LINES);
		prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
		prog.setAttributeValue(SommetId, (dalle.Sommet3()).get_x(), (dalle.Sommet3()).get_y(), (dalle.Sommet3()).get_z());
    prog.setAttributeValue(SommetId, (dalle.Sommet2()).get_x(), (dalle.Sommet2()).get_y(), (dalle.Sommet2()).get_z());
		glEnd();
		glBegin(GL_LINES);
		prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
		prog.setAttributeValue(SommetId, (dalle.Sommet3()).get_x(), (dalle.Sommet3()).get_y(), (dalle.Sommet3()).get_z());
		prog.setAttributeValue(SommetId, (dalle.Sommet4()).get_x(), (dalle.Sommet4()).get_y(), (dalle.Sommet4()).get_z());
		glEnd();
}
void VueOpenGL::dessinePlan (QMatrix4x4 const& point_de_vue, Plan p)
{
    Dalle d(p.get_position() - 2 * DistanceMax * ((p.get_vecteur_1()).GS1() + ((p.get_vecteur_1()).GS1()).GS1() ), p.get_vecteur_1(), ((p.get_vecteur_1()).GS1()), 4*DistanceMax, 4*DistanceMax);
    //std :: cout << d.get_vecteur_2() << std :: endl;
    //std :: cout << d.vecteur_3() << std :: endl;
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    dessineDalle(point_de_vue, d ,0.5 ,0.3,0.6);
    glBegin(GL_LINES);
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
    prog.setAttributeValue(SommetId, (p.get_position()).get_x(), (p.get_position()).get_y(), (p.get_position()).get_z());
    prog.setAttributeValue(SommetId,(p.get_position()).get_x() + (p.get_vecteur_1()).get_x()*20,
                           (p.get_position()).get_y() + (p.get_vecteur_1()).get_y()*20,
                           (p.get_position()).get_z() + (p.get_vecteur_1()).get_z()*20);

    glEnd();
}
void VueOpenGL::dessineLine (QMatrix4x4 const& point_de_vue, Vecteur3D v1, Vecteur3D v2)
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_LINES);
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
    prog.setAttributeValue(SommetId, v1.get_x(), v1.get_y(), v1.get_z());
    prog.setAttributeValue(SommetId, v2.get_x(), v2.get_y(), v2.get_z());
    glEnd();
}
void VueOpenGL::dessineCross (QMatrix4x4 const& point_de_vue, Vecteur3D v)
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_TRIANGLES);
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
    prog.setAttributeValue(SommetId, v.get_x(), v.get_y(), v.get_z());
    prog.setAttributeValue(SommetId, 1.25*(v.get_x()), 1.25*(v.get_y()), 1.25*(v.get_z()));
    prog.setAttributeValue(SommetId, 0.75*(v.get_x()), 0.75*(v.get_y()), 0.75*(v.get_z()));

    glEnd();
}

void VueOpenGL::dessineSphere (QMatrix4x4 const& point_de_vue,
                               double rouge, double vert, double bleu)
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    prog.setAttributeValue(CouleurId, rouge, vert, bleu);  // met la couleur
    sphere.draw(prog, SommetId);                           // dessine la sphère
}

void VueOpenGL::dessineCylinder (QMatrix4x4 const& point_de_vue,
                               double rouge, double vert, double bleu)
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    prog.setAttributeValue(CouleurId, rouge, vert, bleu);  // met la couleur
		cylinder.draw(prog, SommetId);                           // dessine la cylinder
}
