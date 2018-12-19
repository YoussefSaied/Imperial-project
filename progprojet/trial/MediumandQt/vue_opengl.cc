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
using namespace std;

//               = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
void VueOpenGL::dessine(GrainLJ const& G )
{
    QMatrix4x4 matrice;
    matrice.translate((G.get_position()).get_x(),(G.get_position()).get_y(),(G.get_position()).get_z());
    matrice.scale(1.0* G.get_radius());
    dessineSphere(matrice,1/(G.get_velocity()).norme(),(G.get_velocity()).norme(),0); // VERIF
    //dessineSphere(matrice,78,100,0); // vert

}
void VueOpenGL::dessine(GrainLJUn const& G )
{
    QMatrix4x4 matrice;
    matrice.translate((G.get_position()).get_x(),(G.get_position()).get_y(),(G.get_position()).get_z());
    matrice.scale(1.0* G.get_radius());

    //dessineLine(matrice, 0.8 * G.get_position(), 0.01*(G.get_position() + G.get_velocity()) );
    //QMatrix4x4 matrice1;
    //dessineSphere(matrice,250,100,0); // vert
	dessineSphere(matrice,(G.get_velocity()).norme()/300,(G.get_position()).get_z()/60,.5); // VERIF
}
void VueOpenGL::dessine(GrainLJDeux const& G )
{
    QMatrix4x4 matrice;
    matrice.translate((G.get_position()).get_x(),(G.get_position()).get_y(),(G.get_position()).get_z());
    matrice.scale(1.0* G.get_radius());
    //dessineLine(matrice,  0.8 * G.get_position(), 0.01*(G.get_position() + G.get_velocity()) );
    //QMatrix4x4 matrice1;
    dessineSphere(matrice,(G.get_velocity()).norme()/300,(G.get_position()).get_z()/60,0);  // bleu
    //dessineSphere(matrice,1/(G.get_velocity()).norme(),(G.get_velocity()).norme(),0); // VERIF
    //dessineSphere(matrice,170,100,0); // vert

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
void VueOpenGL::dessine(Source const& source)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // passe en mode "fil de fer"
    QMatrix4x4 matrice;
    matrice.translate((source.get_position()).get_x(),(source.get_position()).get_y(),(source.get_position()).get_z());
    matrice.scale(0.25);
    dessineCylinder(matrice,0,1,1); //couleur
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // repasse en mode "plein"
}

void VueOpenGL::dessine(Brique const& b){
		std::vector<Dalle> d6;
		d6 = (b.dalle6());
		for(auto d : d6){
			d.set_support(b.get_support());
			d.dessine();
		}

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
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	QMatrix4x4 matrice;

	matrice.translate((c.get_position()).get_x(),(c.get_position()).get_y(),(c.get_position()).get_z());
	matrice.rotate(90,1,0,0);
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


    if(!(S.tab_ptr_grains).empty()) {
        for(auto const& ptr_grain : (S.tab_ptr_grains)) {
            (*ptr_grain).dessine();
        }
    }
    if((S.tab_ptr_obstacles).size() != 0) {
        for(auto const& ptr_obstacle : (S.tab_ptr_obstacles)) {
            (*ptr_obstacle).dessine();
        }
    }
    if((S.tab_ptr_sources).size() != 0) {
        for(auto const& ptr_source : (S.tab_ptr_sources)) {
            (*ptr_source).dessine();
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
    if((S.tab_ptr_sources).size() != 0) {
        for(auto const& ptr_source : (S.tab_ptr_sources)) {
            (*ptr_source).dessine();
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
    matrice_vue.translate(0.0, 0.0, -15.0);
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
