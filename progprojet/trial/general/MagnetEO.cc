#include "Magnet.h"
#include "Vecteur3D.h"
#include "Obstacle.h"
#include "MagnetE.h"
#include "MagnetEO.h"
#include "Dessinable.h"
#include <cmath>
#include <memory>
using namespace std;

//method to initialize
MagnetEO ::   MagnetEO(Position const& position,
              double rayon, double height,
							Vecteur3D moment1, Vecteur3D axer,
							//double axerheight, double axerradius,
							SupportADessin* support , Vecteur3D Torque,Vecteur3D omega,
							double masse_volumique, Medium medium,
							Vitesse const& vitesse,Vecteur3D const& force):
							MagnetE(position, vitesse, masse_volumique, rayon, force, medium,height,moment1, support),
							omega(omega),torque(Torque)
							//axer(axer), axerheight(axerheight), axerradius(axerradius)
							{
								//make moment orthogonal to axe:
								moment= moment1.norme()*(moment1.GS1(axer)).normalise();
							}
