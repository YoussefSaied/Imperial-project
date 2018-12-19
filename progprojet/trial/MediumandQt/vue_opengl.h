#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include <QGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "SupportADessin.h"
#include "Vecteur3D.h"
#include "glsphere.h"
#include "glcylinder.h"


class VueOpenGL : public SupportADessin
{
public:
    // méthode(s) de dessin (héritée(s) de SupportADessin)

    virtual void dessine(GrainLJ const& G ) override;
    virtual void dessine(GrainLJUn const& G   ) override;
    virtual void dessine(GrainLJDeux  const& G  ) override;
    virtual void dessine(SystemeP9 const& S ) override;
    virtual void dessine(SystemeP12 const& S ) override;
    virtual void dessine(Plan const& P) override;
    virtual void dessine(Dalle const& d) override;
    virtual void dessine(Source const& s) override;
    virtual void dessine(Sphere const& s) override;
    virtual void dessine(Brique const& b) override;
    virtual void dessine(Mediumi const& M);
    virtual void dessine(Cylinder const& c) override;
    virtual ~VueOpenGL() {}

    // méthodes de (ré-)initialisation
    void init();
    void initializePosition();

    // méthode set
    void setProjection(QMatrix4x4 const& projection)
    {
        prog.setUniformValue("projection", projection);
    }

    // Méthodes set
    void translate(double x, double y, double z);
    void rotate(double angle, double dir_x, double dir_y, double dir_z);

    // méthode utilitaire offerte pour simplifier
    void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
    void dessineDalle (QMatrix4x4 const& point_de_vue, Dalle dalle, double x=1.0, double y=1.0,double z=0.0);
    void dessinePlan (QMatrix4x4 const& point_de_vue, Plan p);
    void dessineCross (QMatrix4x4 const& point_de_vue, Vecteur3D v);
    void dessineSphere(QMatrix4x4 const& point_de_vue,
                       double rouge = 1.0, double vert = 0.0, double bleu = 0.0);
    void dessineCylinder(QMatrix4x4 const& point_de_vue,
                         double rouge = 1.0, double vert = 0.0, double bleu = 0.0);
    void dessineLine (QMatrix4x4 const& point_de_vue, Vecteur3D v1, Vecteur3D v2);

    //alpha
    bool get_alpha()
    {
        return alpha;
    }
    void set_alpha(bool a)
    {
        alpha = a;
    }
private:
    // Un shader OpenGL encapsulé dans une classe Qt
    QGLShaderProgram prog;
    GLSphere sphere;
    GLCylinder cylinder;
    bool alpha;

    // Caméra
    QMatrix4x4 matrice_vue;
};

#endif
