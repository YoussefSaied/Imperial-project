#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "ConfigFile.tpp" // Fichier .tpp car inclut un template

using namespace std;

class Exercice3{

private:
  double t, dt, tFin;
  double Omega, B0, B1, mu, nu, Ig;
  double theta, thetadot;
  int sampling;
  int last;
  ofstream *outputFile;

  void printOut(bool force)
  {
    if((!force && last>=sampling) || (force && last!=1)){
      double emec = 0.5*Ig*thetadot*thetadot-mu*(B0 + B1*sin(t*Omega))*cos(theta);
      double pnc = -thetadot*thetadot*nu;
			double edissip = thetadot*thetadot*nu + B1*mu*thetadot*sin(Omega*t)*sin(theta);
      *outputFile << t << " " << theta << " " << thetadot << " " << emec << " " << pnc << edissip <<endl;
      last = 1;
    }else{
      last++;
    }
  }

  double alpha(double x, double v, double temps)
  {
	  double B = B0 + B1*sin(Omega*temps);
	  return -(1/Ig) *(mu*B*sin(x) + nu*v);
  }

  void step()
  {
    // Schema de Stormer-Verlet
    double theta_old = theta;
    double thetadot_05 = thetadot + 0.5*dt*alpha(theta_old,thetadot,t);
    theta += thetadot*dt + 0.5*dt*dt*alpha(theta,thetadot,t);
    thetadot += 0.5*dt * ( alpha(theta_old, thetadot_05,t) + alpha(theta, thetadot_05,t+dt) );
  }


public:

  Exercice3(int argc, char* argv[]){

    string inputPath("configuration.in"); // Fichier d'input par defaut
    if(argc>1) // Fichier d'input specifie par l'utilisateur ("./Exercice3 config_perso.in")
      inputPath = argv[1];

    ConfigFile configFile(inputPath); // Les parametres sont lus et stockes dans une "map" de strings.

    for(int i(2); i<argc; ++i) // Input complementaires ("./Exercice3 config_perso.in input_scan=[valeur]")
      configFile.process(argv[i]);

    tFin     = configFile.get<double>("tFin");
    dt       = configFile.get<double>("dt");
    Omega    = configFile.get<double>("Omega");
    B0       = configFile.get<double>("B0");
    B1       = configFile.get<double>("B1");
    mu       = configFile.get<double>("mu");
    nu       = configFile.get<double>("nu");
    Ig       = configFile.get<double>("Ig");
    theta    = configFile.get<double>("theta0");
    thetadot = configFile.get<double>("thetadot0");
    sampling = configFile.get<int>("sampling");

    // Ouverture du fichier de sortie
    outputFile = new ofstream(configFile.get<string>("output").c_str());
    outputFile->precision(25);
  };

  ~Exercice3(){
    outputFile->close();
    delete outputFile;
  };

  void run(){
    last = 0;
    t = 0;
    printOut(true);
    while( t<(tFin-0.5*dt) ) {
      step();
      t += dt;
      printOut(false);
    }
    printOut(true);
  };

};


int main(int argc, char* argv[])
{
  Exercice3 engine(argc, argv);
  engine.run();
  return 0;
}
