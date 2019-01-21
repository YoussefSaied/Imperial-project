#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QTime>            // Classe pour gérer le temps
#include "vue_opengl.h"
#include "Systeme.h"
#include "SystemeP9.h"

class GLWidget : public QGLWidget
/* La fenêtre hérite de QGLWidget ;
 * les événements (clavier, souris, temps) sont des méthodes virtuelles à redéfinir.
 */
{
public:
  GLWidget(QWidget* parent = nullptr)
    : QGLWidget(parent), sysm(&vue)
  {
		system_tab.push_back(sysm.copie());
	}
  virtual ~GLWidget() {}
	void set_systeme(Systeme const& sys){
		system_tab.push_back(sys.copie());
		system_tab.back()->set_support(&vue);}

	void addMagnet(Magnet const& nouveau_Magnet){system_tab[0]->addMagnet(nouveau_Magnet);}

	void addObstacle(Obstacle const& nouveau_obstacle){system_tab[0]->ajouteObstacle(nouveau_obstacle);}

  // objets à dessiner, faire évoluer

private:
  // Les 3 méthodes clés de la classe QGLWidget à réimplémenter
  virtual void initializeGL()                  override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL()                       override;

  // Méthodes de gestion d'évènements
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void timerEvent(QTimerEvent* event)  override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event)  override;

	// position de la souris
	QPointF lastMousePosition;
  // Méthodes de gestion interne
  void pause();

  // Vue : ce qu'il faut donner au contenu pour qu'il puisse se dessiner sur la vue
  VueOpenGL vue;

  // Timer
  int timerId;
	double dt = (5.0/10000.0);
  // pour faire évoluer les objets avec le bon "dt"
  QTime chronometre;
	std::vector<std::unique_ptr<Systeme>> system_tab;
	SystemeP9 sysm;

};

#endif // GLWIDGET_H
