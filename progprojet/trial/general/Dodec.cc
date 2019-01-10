#include "Dodec.h"
#include "Vecteur3D.h"
#include "Plan.h"
#include "Dalle.h"
#include "Obstacle.h"
#include <cmath>
#include <vector>
#include <memory>
using namespace std;

unique_ptr<Dodec> Dodec:: cloneMe() const
{
    return unique_ptr<Dodec>(new Dodec(*this));
}

unique_ptr<Obstacle> Dodec:: copie() const
{
    return cloneMe();
}


bool Dodec:: is_inside(Vecteur3D const& x_i) const
{
    if(position.distance(PointPlusProche(x_i)) > position.distance(x_i)) return true;
    return false;
}

Vecteur3D Dodec:: PointPlusProche(Vecteur3D const& x_i) const
{
    return Vecteur3D();
}

vector<Vecteur3D> Dodec:: vertipositions() const
{
	vector<Vecteur3D> vp; //vertixes positions
	double a= (1+ sqrt(5))/2;
	for(int i =-1; i<2; i+=2){
		for(int j =-1; j<2; j+=2){
			for(int k =-1; k<2; k+=2){
				vp.push_back(Vecteur3D(i,j,k));
				vp.push_back(Vecteur3D(0,j*a,k/a));
				vp.push_back(Vecteur3D(i/a,0,k*a));
				vp.push_back(Vecteur3D(i*a,j/a,0));
			}
		}
	}
	for(auto i : vp){
		i*=edge;
	}
	return vp;
}
