#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <complex> // Pour les nombres complexes
#include "ConfigFile.tpp"

using namespace std;
/*typedef vector<complex<double> > vec_complex;



//=============================================================
// Fonction resolvant le systeme d'equations A * solution = rhs
// où A est une matrice tridiagonale
template <class T> void triangular_solve(vector<T> const& diag,
                                         vector<T> const& lower,
                                         vector<T> const& upper,
                                         vector<T> const& rhs,
                                         vector<T>& solution)
{
	vector<T> new_diag = diag;
	vector<T> new_rhs = rhs;

	// forward elimination
	for(size_t i(1); i<diag.size(); ++i) {
		T pivot = lower[i-1] / new_diag[i-1];
		new_diag[i] -= pivot * upper[i-1];
		new_rhs[i] -= pivot * new_rhs[i-1];
	}

	solution.resize(diag.size());

	// solve last equation
	solution[diag.size()-1] = new_rhs[diag.size()-1] / new_diag[diag.size()-1];

	// backward substitution
	for(int i = diag.size() - 2; i >= 0; --i) {
		solution[i] = (new_rhs[i] - upper[i] * solution[i+1]) / new_diag[i];
	}
}




//=============================================================
// Potentiel V(x) :
double V(double const& x, double const& V0, double const& xL, double const& xa, double const& xb, double const& xR)
{
   if( x < xa || x > xb )
      return 0.;
   else
      return V0;
      //return 0.0005*0.5*(x-128)*(x-128);
}


//=============================================================
// Les definitions de ces fonctions sont en dessous du main.
// Declaration des diagnostiques de la particule d'apres sa fonction d'onde psi :
//  - prob calcule la probabilite de trouver la particule entre les points nL.dx et nR.dx,
//  - E calcule son energie,
//  - xmoy calcule sa position moyenne,
//  - x2moy calcule sa position au carre moyenne,
//  - pmoy calcule sa quantite de mouvement moyenne,
//  - p2moy calcule sa quantite de mouvement au carre moyenne.
double trapeze(vector<double> const& psi, int nL, int nR, double dx);
double prob(vec_complex const& psi, int nL, int nR, double dx);
double E(vec_complex const& psi, vec_complex const& diagH, vec_complex const& lowerH, vec_complex const& upperH, double const& dx);
double xmoy(vec_complex const& psi, const vector<double>& x, double const& dx);
double x2moy(vec_complex const& psi, const vector<double>& x, double const& dx);
double pmoy(vec_complex const& psi, double const& dx);
double p2moy(vec_complex const& psi, double const& dx);

// Fonction pour normaliser une fonction d'onde :
vec_complex normalize(vec_complex const& psi, double const& dx);


*/


//=============================================================
int main(int argc,char **argv)
{
	complex<double> complex_i = complex<double> (0,1); // Nombre imaginaire i

	string inputPath("configuration4.in"); // Fichier d'input par defaut
	if(argc>1) // Fichier d'input specifie par l'utilisateur ("./Exercice8 config_perso.in")
	inputPath = argv[1];

	ConfigFile configFile(inputPath); // Les parametres sont lus et stockes dans une "map" de strings.

	for(int i(2); i<argc; ++i) // Input complementaires ("./Exercice8 config_perso.in input_scan=[valeur]")
	configFile.process(argv[i]);

	/*// Parametres physiques :
	double hbar    = 1.;
	double m       = 1.;
	double tfin    = configFile.get<double>("tfin");
	double tdetect = configFile.get<double>("tdetect");
	double xL      = configFile.get<double>("xL");
	double xR      = configFile.get<double>("xR");
	double xa      = configFile.get<double>("xa");
	double xb      = configFile.get<double>("xb");
	double V0      = configFile.get<double>("V0");
	double x0      = configFile.get<double>("x0");
	double k0      = 2. * M_PI * configFile.get<int>("n") / (xR-xL);
	double sigma0  = configFile.get<double>("sigma_norm") * (xR-xL);

	// Parametres numeriques :
	double dt      = configFile.get<double>("dt");
	int Ninters    = configFile.get<int>("Ninters");
	int Npoints    = Ninters + 1;
	double dx      = (xR-xL) / Ninters;

	// Maillage :
	vector<double> x(Npoints);
	for(int i(0); i < Npoints; ++i)
		x[i] = xL + i*dx;

	// Fonction d'onde :
	vec_complex psi(Npoints);
	// TODO: initialiser le paquet d'onde initial de forme gausienne equation (4.109) du cours
	for(int i(0); i < Npoints; ++i)
	psi[i] = exp(complex_i *k0 *x[i]) * exp(-pow((x[i]-x0),2) / (2*sigma0*sigma0) );

	// Modifications des valeurs aux bords (psi = 0 à gauche et à droite) :
	psi[0] = complex<double> (0.,0.);
	psi[Npoints-1] = complex<double> (0.,0.);

	// Normalisation :
	psi = normalize(psi, dx);*/

	// Matrices (d: diagonale, a: sous-diagonale, c: sur-diagonale) :
	/*vec_complex dH(Npoints), aH(Ninters), cH(Ninters); // matrice Hamiltonienne
	vec_complex dA(Npoints), aA(Ninters), cA(Ninters); // matrice du membre de gauche de l'equation (4.90)
	vec_complex dB(Npoints), aB(Ninters), cB(Ninters); // matrice du membre de droite de l'equation (4.90)

	complex<double> a, b, c;
	a = complex_i * hbar * dt / (4.0*m*dx*dx);
	b = complex_i * dt / (hbar * 2.0);
	c = -hbar*hbar / (2.0*m*dx*dx);*/



	/*// TODO: calculer les éléments des matrices A, B et H.
	// Ces matrices sont stockées sous forme tridiagonale, d:diagonale, c et a: diagonales supérieures et inférieures
	for (int i(0) ; i < Npoints; i++) {
		dH[i] = -2.0*c + V(x[i],V0,xL,xa,xb,xR);
		dA[i] = 1.0 + 2.0*a + b*V(x[i],V0,xL,xa,xb,xR);
		dB[i] = 1.0 - 2.0*a - b*V(x[i],V0,xL,xa,xb,xR);
	};

	for (int i(0) ; i < Ninters; i++) {
		aH[i] = c;
		cH[i] = c;

		aA[i] = -a;
		cA[i] = -a;

		aB[i] = a;
		cB[i] = a;
	}


	// Conditions aux limites: psi nulle aux deux bords
	// TODO: Modifier les matrices A et B pour satisfaire les conditions aux limites
	dA[0] = 1.0 ; dA[Npoints-1] = 1.0 ;
	cA[0] = 0.0 ; aA[Npoints-2] = 0.0;

	dB[0] = 0.0 ; dB[Npoints-1] = 0.0;
	cB[0] = 0.0 ; aB[Npoints-2] = 0.0;*/




	// Fichiers de sortie :
	string output = configFile.get<string>("output");

	ofstream fichier_potentiel((output + "_pot.out").c_str());
	fichier_potentiel.precision(15);
	for(int i(0); i < Npoints; ++i) {
		fichier_potentiel << x[i] << " " << V(x[i], V0, xL, xa, xb, xR) << endl;
	}
	fichier_potentiel.close();

	ofstream fichier_psi((output + "_psi2.out").c_str());
	fichier_psi.precision(15);

	ofstream fichier_observables((output + "_obs.out").c_str());
	fichier_observables.precision(15);

	// Boucle temporelle :
	/*double t;
	for(t = 0.0 ; t+ dt/2.0 < tfin ; t += dt) {

		if(t > tdetect-0.01 && t < tdetect+0.01 && 1) {
			for(int i(0); i < Npoints; ++i) {
				if(x[i] < xb) {
					psi[i] = 0.0;
				}
			}

			psi = normalize(psi, dx);
		}

		// Ecriture de |psi|^2 :
		for(int i(0); i<Npoints; ++i)  fichier_psi << abs(psi[i]) * abs(psi[i]) << " ";
		fichier_psi << endl;

		// Ecriture des observables :
		fichier_observables << t << " "
							<< prob(psi,0,Ninters*(xa-xL)/(xR-xL),dx) << " "                       // probabilite que la particule soit en x < xa
							<< prob(psi,Ninters*(xa-xL)/(xR-xL),Ninters*(xb-xL)/(xR-xL),dx) << " " // probabilite que la particule soit en xa <= x <= xb
							<< prob(psi,Ninters*(xb-xL)/(xR-xL),Ninters,dx) << " "                 // probabilite que la particule soit en x > xb
							<< E(psi,dH,aH,cH,dx) << " "  // Energie
							<< xmoy(psi,x,dx) << " "      // Position moyenne
							<< x2moy(psi,x,dx) << " "     // Position^2 moyenne
							<< pmoy(psi,dx) << " "      // Quantite de mouvement moyenne
							<< p2moy(psi,dx) <<  " " // (Quantite de mouvement)^2 moyenne
							<< sqrt(x2moy(psi,x,dx) - pow(xmoy(psi,x,dx),2) ) << " "   // Incertitude sur la position
							<< sqrt(p2moy(psi,dx) - pow(pmoy(psi,dx),2) ) << endl;

		// Calcul du membre de droite :
		vec_complex psi_tmp(Npoints,0.);

		// Multiplication psi_tmp = B * psi :
		for(int i(0); i<Npoints; ++i)
		{
			psi_tmp[i] = dB[i] * psi[i];
		}

		for(int i(0); i<Ninters; ++i)
		{
			psi_tmp[i] += cB[i] * psi[i+1];
			psi_tmp[i+1] += aB[i] * psi[i];
		}

		// Resolution de A * psi = psi_tmp :
		triangular_solve(dA, aA, cA, psi_tmp, psi);

	} // Fin de la boucle temporelle*/



	/*for(int i(0); i<Npoints; ++i)	fichier_psi << abs(psi[i]) * abs(psi[i]) << " ";

	fichier_observables << t << " "
					  << prob(psi,0,Ninters*(xa-xL)/(xR-xL),dx) << " "
					  << prob(psi,Ninters*(xa-xL)/(xR-xL),Ninters*(xb-xL)/(xR-xL),dx) << " "
					  << prob(psi,Ninters*(xb-xL)/(xR-xL),Ninters,dx) << " "
					  << E(psi,dH,aH,cH,dx) << " "
					  << xmoy(psi,x,dx) << " "
					  << x2moy(psi,x,dx) << " "
					  << pmoy(psi,dx) << " "
					  << p2moy(psi,dx) << " "
					  << sqrt(x2moy(psi,x,dx) - pow(xmoy(psi,x,dx),2) ) << " "   // Incertitude sur la position
					  << sqrt(p2moy(psi,dx) - pow(pmoy(psi,dx),2) ) << endl;

	fichier_observables.close();
	fichier_psi.close();
}*/



/*double trapeze(vector<double> const& f, int nL, int nR, double dx)
{
	double sum = 0.0;
	for( int i(nL) ; i < nR ; i++) {
		sum += ( f[i] + f[i+1] ) / 2.0 * dx;
	}

	return sum;
}


double prob(vec_complex const& psi, int nL, int nR, double dx)
{
	// TODO: calculer la probabilite de trouver la particule entre les points nL.dx et nR.dx
	// Intégration numérique par la méthode des trapèzes

	double sum = 0.0;
	for( int i(nL) ; i < nR ; i++) {
		sum += dx * ( pow(abs(psi[i]),2) + pow(abs(psi[i+1]),2) ) / 2.0;
	}

	return sum;
}*/


/*double E(vec_complex const& psi, vec_complex const& diagH, vec_complex const& lowerH, vec_complex const& upperH, double const& dx)
{

	// TODO: calculer la moyenne de l'Hamiltonien


	vec_complex H_psi(psi.size());
	for (size_t i(1) ; i < psi.size()-1 ; ++i) {
		H_psi[i] = lowerH[i-1]*psi[i-1] + diagH[i]*psi[i] + upperH[i]*psi[i+1];
	}

	H_psi[0]=diagH[0]*psi[0]+upperH[0]*psi[1];
	H_psi[psi.size()-1]=diagH[psi.size()-1]*psi[psi.size()-1]+lowerH[psi.size()-2]*psi[psi.size()-2];


	double sum = 0.0;

	for( size_t i(0) ; i < psi.size()-1 ; i++) {
		sum += dx * real ( conj(psi[i]) * H_psi[i] + conj(psi[i+1]) * H_psi[i+1] ) / 2.0;
	}

	return sum;
}*/

/*
double xmoy(vec_complex const& psi, const vector<double>& x, double const& dx)
{
	//TODO: calculer la moyenne de la position
	double sum = 0.0;

	for( size_t i(0) ; i < psi.size()-1 ; i++) {
		sum += dx * real ( conj(psi[i]) * x[i] * psi[i] + conj(psi[i+1]) * x[i+1] * psi[i+1] ) / 2.0;
	}

	return sum;
}


double x2moy(vec_complex const& psi, const vector<double>& x, double const& dx)
{
	//TODO: calculer la moyenne du x^2
	double sum = 0.0;

	for( size_t i(0) ; i < psi.size()-1 ; i++) {
		sum += dx * real( conj(psi[i]) * x[i] *x[i] * psi[i] + conj(psi[i+1]) * x[i+1] * x[i+1] * psi[i+1] ) / 2.0;
	}

	return sum;
}


double pmoy(vec_complex const& psi, double const& dx)
{
	//TODO: calculer la moyenne de p
	complex<double> complex_i = complex<double> (0,1);
	double sum = 0.0;

	vec_complex dpsi_dx(psi.size());
		for( size_t i(1) ; i < psi.size()-1 ; i++) {
		dpsi_dx[i] = (psi[i+1] - psi[i-1]) / (2*dx);
	}
	dpsi_dx[0] = psi[1]-psi[0] / dx;
	dpsi_dx[psi.size()-1] = psi[psi.size()]-psi[psi.size()-1] / dx;

	//conj(psi[0])*(-complex_i*1.*(psi[1]-psi[0])/dx) + conj(psi[1])*(-complex_i*1.*(psi[2]-psi[0])/(2.*dx))
	//+ conj(psi[N-2])*(-complex_i*1.*(psi[N-1]-psi[N-3])/(2.*dx)) + conj(psi[N-1])*(-complex_i*1.*(psi[N-1]-psi[N-2])/dx) );


	for( size_t i(0) ; i < psi.size()-1 ; i++) {
		sum += real ( conj(psi[i]) * (-1.0) * complex_i * dpsi_dx[i]
					+ conj(psi[i+1]) * (-1.0) * complex_i * dpsi_dx[i+1] ) / 2.0 * dx;
	}

	return sum;
}


double p2moy(vec_complex const& psi, double const& dx)
{
	// TODO: calculer la moyenne du p^2
	double sum = 0.0;

	vec_complex dpsi2_dx2(psi.size());
		for( size_t i(1) ; i < psi.size()-2 ; i++) {
		dpsi2_dx2[i] = (psi[i+1] - 2.0*psi[i] + psi[i-1] )/ (dx*dx);
	}
	dpsi2_dx2[0] = 0.0;
	dpsi2_dx2[psi.size()-1] = 0.0;

	for( size_t i(0) ; i < psi.size()-1 ; i++) {
		sum += real ( conj(psi[i]) * (-1.0) * dpsi2_dx2[i]
					+ conj(psi[i+1]) * (-1.0) * dpsi2_dx2[i+1] ) / 2.0 * dx;
	}

	return sum;
}


vec_complex normalize(vec_complex const& psi, double const& dx)
{
	vec_complex psi_norm(psi.size());
	double norm = sqrt(prob(psi,0,psi.size()-1,dx));

	for(size_t i(0); i<psi.size(); ++i) {
		psi_norm[i] = psi[i]/norm;
	}

	return psi_norm;
}*/
