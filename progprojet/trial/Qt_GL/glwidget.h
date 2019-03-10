#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget> // Classe pour faire une fenêtre OpenGL
#include <QTime>     // Classe pour gérer le temps
#include "vue_opengl.h"
#include "Systeme.h"


class GLWidget : public QGLWidget

/* La fenêtre hérite de QGLWidget ;
 * les événements (clavier, souris, temps) sont des méthodes virtuelles à redéfinir.
 */
{
public:
<<<<<<< HEAD
    GLWidget(QWidget * parent = nullptr, double f = 2.5, double dt = 0.001)
=======
    GLWidget(QWidget * parent = nullptr, double f = 0.1, double dt = 0.001)
>>>>>>> 09fcf2009e5b03350e296195431b706596c4b5c8
        : QGLWidget(parent), sysm(&vue, f), dt(dt)
    {
        system_tab.push_back(sysm.copie());
    }

    virtual ~GLWidget(){ }

    void set_systeme(Systeme const& sys)
    {
        system_tab.push_back(sys.copie());
        system_tab.back()->set_support(&vue);
    }

    void addMagnet(Magnet const& nouveau_Magnet)
    {
        system_tab[0]->addMagnet(nouveau_Magnet);
    }

    void addObstacle(Obstacle const& nouveau_obstacle)
    {
        system_tab[0]->addObstacle(nouveau_obstacle);
    }

    // system
    std::vector<std::unique_ptr<Systeme> > system_tab;
    Systeme sysm;
    double dt;
public slots:
    void setXB(double x)
    {
        if (x * 1e-6 != (system_tab[0]->B).get_x()) {
            (system_tab[0]->B).setx(x * 1e-4);
            emit XBChanged(x);
        }
    }

    void setYB(double y)
    {
        if (y * 1e-6 != (system_tab[0]->B).get_y()) {
            (system_tab[0]->B).sety(y * 1e-4);
            emit YBChanged(y);
        }
    }

    void setZB(double z)
    {
        if (z * 1e-6 != (system_tab[0]->B).get_z()) {
            (system_tab[0]->B).setz(z * 1e-4);
            emit ZBChanged(z);
        }
    }

    void setXB(int x)
    {
        if (x * 1e-6 != (system_tab[0]->B).get_x()) {
            (system_tab[0]->B).setx(x * 1e-4);
            emit XBChanged(x);
        }
    }

    void setYB(int y)
    {
        if (y * 1e-4 != (system_tab[0]->B).get_y()) {
            (system_tab[0]->B).sety(y * 1e-4);
            emit YBChanged(y);
        }
    }

    void setZB(int z)
    {
        if (z * 1e-4 != (system_tab[0]->B).get_z()) {
            (system_tab[0]->B).setz(z * 1e-4);
            emit ZBChanged(z);
        }
    }

    void selectmagnet(int mn)
    {
        system_tab[0]->selected(mn);
        int siz(((system_tab[0])->tab_ptr_Magnets).size());
        // (system_tab[0]->selectedmagnet) = mn;
        emit magnetselected(mn % siz);
    }

    void changeangle(double angle)
    {
        int mn = (system_tab[0]->selectedmagnet);
        int siz(((system_tab[0])->tab_ptr_Magnets).size());
        ((system_tab[0])->tab_ptr_Magnets)[mn]->angle = angle;
        emit anglechanged((system_tab[0]->selectedmagnet) % siz);
    }

    void flipmagnet()
    {
        int mn = (system_tab[0]->selectedmagnet);
        int siz(((system_tab[0])->tab_ptr_Magnets).size());
        ((system_tab[0])->tab_ptr_Magnets)[mn]->angle += M_PI;
        emit anglechanged((system_tab[0]->selectedmagnet) % siz);
    }

    void omegato0()
    {
        int mn = (system_tab[0]->selectedmagnet);
        int siz(((system_tab[0])->tab_ptr_Magnets).size());
        ((system_tab[0])->tab_ptr_Magnets)[mn]->omega = 0;
        emit anglechanged((system_tab[0]->selectedmagnet) % siz);
    }

signals:
    void XBChanged(double newx);
    void YBChanged(double newy);
    void ZBChanged(double newz);
    void magnetselected(int mn);
    void evolved(double dt);
    void anglechanged(int mn);


    // objets à dessiner, faire évoluer

private:
    Q_OBJECT

    // Les 3 méthodes clés de la classe QGLWidget à réimplémenter
    virtual void initializeGL()                  override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL()                       override;
    QSize minimumSizeHint() const
    {
        return QSize(50, 50);
    }

    QSize sizeHint() const

    {
        return QSize(800, 600);
    }

    // Méthodes de gestion d'évènements
    virtual void keyPressEvent(QKeyEvent * event) override;
    virtual void timerEvent(QTimerEvent * event)  override;
    virtual void mousePressEvent(QMouseEvent * event) override;
    virtual void mouseMoveEvent(QMouseEvent * event)  override;

    // position de la souris
    QPointF lastMousePosition;
    // Méthodes de gestion interne
    void pause();
    // Vue : ce qu'il faut donner au contenu pour qu'il puisse se dessiner sur la vue
    VueOpenGL vue;

    // Timer
    int timerId;


    // pour faire évoluer les objets avec le bon "dt"
    QTime chronometre;
};

#endif // GLWIDGET_H
