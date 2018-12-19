#include <iostream>
#include "Vecteur3D.h"

using namespace std;

int main()
{
    cout << "Bonjour! Ceci est un test de la classe Vecteur3D!" << endl;
    cout << endl;

    cout << "test du constructeur par defaut expected : (0, 0, 0)  ansi que de l'operateur << : " << endl;
    Vecteur3D vect1;
    cout << vect1;
    cout << endl;

    cout << "test du constructeur à 3 arguments expected : (2.6, 3.5,  4.1) ansi que de l'operateur  << : " << endl;
    Vecteur3D vect2(2.6, 3.5,  4.1);
    cout << vect2;
    cout << endl;

    cout << "test du constructeur à 1 argument expected : (-5.4, 0,  0) ansi que de l'operateur  << : " << endl;
    Vecteur3D vect3(-5.4);
    cout << vect3;
    cout << endl;

    cout << "test du constructeur à 2 arguments expected : (-7.4, 5.9,  0) ansi que de l'operateur  << : " << endl;
    Vecteur3D vect4(-7.4, 5.9);
    cout << vect4;
    cout << endl;

    cout << "test du constructeur à 2 arguments expected : (0, 5.9,  0) ansi que de l'operateur  << : " << endl;
    Vecteur3D vect5(0, 5.9);
    cout << vect5;
    cout << endl;

    cout << "test du constructeur par copie expected : (2.6, 3.5,  4.1) ansi que de l'operateur  << : " << endl;
    Vecteur3D vect100(vect2);
    cout << vect100;
    cout << endl;


    cout << "test du set_coord sans arguments expected : (0, 0,  0) ansi que de l'operateur  << : " << endl;
    Vecteur3D vect6(2.6, 3.5,  4.1);
    vect6.set_coord();
    cout << vect6;
    cout << endl;

    cout << "test du set_coord 3 arguments expected : (-48.5, -87.5,  358.9654) ansi que de l'operateur  << : " << endl;
    Vecteur3D vect7(58480, -45654.546465,  500.9654);
    vect7.set_coord(-48.5, -87.5,  358.9654);
    cout << vect7;
    cout << endl;

    cout << "test du constructeur de copie expected : (-48.5, -87.5,  358.9654) ansi que de l'operateur  << : " << endl;
    Vecteur3D vect8(vect7);
    cout << vect8;
    cout << endl;

    cout << "test de la méthode 'ostream& affiche( ostream& sortie) const'  expected : (-7.4, 5.9,  0) : " << endl;
    vect4.affiche(cout) << endl;
    cout << endl;

    cout << "test de la méthode prod_scal (-7.4, 5.9,  0) (0, 0, 0) expected : 0 : " << endl;
    cout << (vect4 * vect1) << endl;
    cout << endl;

    cout << "test de la méthode prod_scal (-7.4, 5.9,  0) (1, 1, 1) expected : -1.5 : " << endl;
    cout << (vect4 * Vecteur3D(1,1,1)) << endl;
    cout << endl;

    cout << "test de commutativité de la méthode prod_scal  (1, 1, 1) (-7.4, 5.9,  0) expected : -1.5 : " << endl;
    cout << ((Vecteur3D(1,1,1)) * (Vecteur3D(-7.4, 5.9,  0))) << endl;
    cout << endl;

    cout << "test de la méthode prod_scal (1, 1, 1) (1, 1, 1) expected : 3 : " << endl;
    cout << ((Vecteur3D(1,1,1)) * (Vecteur3D(1,1,1))) << endl;
    cout << endl;


    cout << "test de la méthode prod_vect (1, 1, 1) (1, 1, 1) expected : (0, 0, 0) : " << endl;
    cout << ((Vecteur3D(1,1,1)) ^ (Vecteur3D(1,1,1))) << endl;
    cout << endl;

    cout << "test de la méthode prod_vect (1, 1, 0) (1, 1, 1) expected : {1; -1; 0} : " << endl;
    cout << ((Vecteur3D(1,1,0)) ^ (Vecteur3D(1,1,1))) << endl;
    cout << endl;

    cout << "test de la méthode (NON COMMUTATIVE) prod_vect (1, 1, 1) (1, 1, 0) expected : {-1; 1; 0} : " << endl;
    cout << ((Vecteur3D(1,1,1)) ^ (Vecteur3D(1,1,0))) << endl;
    cout << endl;

    cout << "test de la méthode prod_vect (1789, -4581, 3.1415) (-871, -97.121, -5000) expected : {22905305.1056215; 8942263.7535; -4163800.469} : " << endl;
    cout << ((Vecteur3D(1789, -4581, 3.1415)) ^ (Vecteur3D(-871, -97.121, -5000))) << endl;
    cout << endl;

    cout << "test de la méthode prod_vect (-7.4, 5.9,  0) (1, 1, 1) expected : {5.9; 7.4; -13.3} : " << endl;
    cout << ((Vecteur3D(-7.4, 5.9,  0)) ^ (Vecteur3D(1, 1, 1))) << endl;
    cout << endl;

    cout << "test de la methode random vector   expected : SURPRISE : " << endl;
    Vecteur3D().random_vector();
    cout << endl;

    cout << "test de l'operateur * (-7.4, 5.9,  0) (1, 1, 1) expected : -1.5 : " << endl;
    cout << vect4*(Vecteur3D(1,1,1)) << endl;
    cout << endl;

    cout << "test de methode oppose (3, 4, -2.5) expected : (-3, -4, +2.5) " << endl;
    cout << (Vecteur3D(3, 4, -2.5)).oppose() << endl;
    cout << endl;

    cout << "test de l'operateur + avec oppose:  (3, 4, 0) + (3, 4, -2.5).oppose  expected : (0, 0, +2.5) : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) + (Vecteur3D(3, 4, -2.5)).oppose()) << endl;
    cout << endl;

    cout << "test de la commutativité de  l'operateur *  (1, 1, 1) (-7.4, 5.9,  0) expected : -1.5 : " << endl;
    cout << (Vecteur3D(1,1,1))*(Vecteur3D(-7.4, 5.9,  0)) << endl;
    cout << endl;

    cout << "test de l'operateur ^ (-7.4, 5.9,  0) (1, 1, 1) expected : {5.9; 7.4; -13.3} : ATTENTION A LA PRIORITÉ DES OP. " << endl;
    cout << ((Vecteur3D(-7.4, 5.9,  0))^(Vecteur3D(1, 1, 1))) << endl;
    cout << endl;

    cout << "test de la méthode oppose (-7.4, 5.9,  0) expected : (7.4, -5.9,  0) : " << endl;
    cout << (Vecteur3D(-7.4, 5.9,  0)).oppose() << endl;
    cout << endl;

    cout << "test de la méthode oppose (-7.4, 5.9, -98.7) expected : (7.4, -5.9, 98.7) : " << endl;
    cout << (Vecteur3D(-7.4, 5.9,  -98.7)).oppose() << endl;
    cout << endl;

    cout << "test de la méthode oppose (-7.4, -5.9, -98.7) expected : (7.4, 5.9, 98.7) : " << endl;
    cout << (Vecteur3D(-7.4, -5.9,  -98.7)).oppose() << endl;
    cout << endl;

    cout << "test de la méthode oppose (7.4, 5.9, 98.7) expected : (-7.4, -5.9, -98.7) : " << endl;
    cout << (Vecteur3D(7.4, 5.9, 98.7)).oppose() << endl;
    cout << endl;

    cout << "test de la méthode norme (7.4, 5.9, -98.7) expected : 99.15271050253745 : " << endl;
    cout << (Vecteur3D(7.4, 5.9, -98.7)).norme() << endl;
    cout << endl;

    cout << "test de la méthode norme au carré (5, 3, -9) expected : 115 : " << endl;
    cout << (Vecteur3D(5, 3, -9)).norme2() << endl;
    cout << endl;

    cout << "test de l'operateur /  (3.6, -3.9, 4.8)  3 expected : (1.2, -1.3, 1.6) : " << endl;
    cout << (Vecteur3D(3.6, -3.9, 4.8))/3 << endl;
    cout << endl;

    cout << "test de l'operateur /  (3.6, -3.9, 0)  3 expected : (1.2, -1.3, 0) : " << endl;
    cout << (Vecteur3D(3.6, -3.9, 0))/3 << endl;
    cout << endl;

    cout << "test de la méthode normalise (7.4, 5.9, -98.7) expected : norme 1 : " << endl;
    Vecteur3D vect9(7.4, 5.9, -98.7);
    Vecteur3D vect10(vect9.normalise());
    cout << vect10 << endl;
    cout << vect10.norme() << endl;
    cout << endl;

    cout << "test de la methode distance (3.6, -3.9, 4.8) (17, 6, 2) expected : 16.894082 : " << endl;
    cout << (Vecteur3D(3.6, -3.9, 4.8)).distance(Vecteur3D(17, 6, 2)) << endl;
    cout << endl;

    cout << "test de l'operateur == (3.6, -3.9, 0) (17, 6, 2) expected : 0 : " << endl;
    cout << ((Vecteur3D(3.6, -3.9, 0))==(Vecteur3D(17, 6, 2))) << endl;
    cout << endl;

    cout << "test de l'operateur == (7.4, 5.9, -98.7) (7.4, 5.9, -98.7) expected : 1 : " << endl;
    cout << (vect9==(Vecteur3D(7.4, 5.9, -98.7))) << endl;
    cout << endl;

    cout << "test de l'operateur != (3.6, -3.9, 0) (17, 6, 2) expected : 1 : " << endl;
    cout << ((Vecteur3D(3.6, -3.9, 0))!=(Vecteur3D(17, 6, 2))) << endl;
    cout << endl;

    cout << "test de l'operateur != (7.4, 5.9, -98.7) (7.4, 5.9, -98.7) expected : 0 : " << endl;
    cout << (vect9!=(Vecteur3D(7.4, 5.9, -98.7))) << endl;
    cout << endl;

    cout << "test de l'operateur == (3, 0, -4) et 5 expected : 1 : " << endl;
    cout << ((Vecteur3D(3, 0, -4))==5.0) << endl;
    cout << endl;

    cout << "test de l'operateur < (7.4, 5.9, -98.7) < 100 norme 99.1527 expected : 1 : " << endl;
    cout << vect9.norme() << endl;
    cout << (vect9 < 100) << endl;
    cout << endl;

    cout << "test de l'operateur < (7.4, 5.9, -98.7) < 99 norme 99.1527 expected : 0 : " << endl;
    cout << vect9.norme() << endl;
    cout << (vect9 < 99) << endl;
    cout << endl;

    cout << "test de l'operateur < (7.4, 5.9, -98.7) < 99.1527 norme 99.1527 expected : 0 : " << endl;
    cout << vect9.norme() << endl;
    cout << (vect9 < 99.1527) << endl;
    cout << endl;

    cout << "test de l'operateur <= (3, 4, 0) <= 5 norme 5 expected : 1 : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) <= 5) << endl;
    cout << endl;

    cout << "test de l'operateur <= (3, 4, 0) <= 4 norme 5 expected : 0 : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) <= 4) << endl;
    cout << endl;

    cout << "test de l'operateur > (7.4, 5.9, -98.7) > 100 norme 99.1527 expected : 0 : " << endl;
    cout << vect9.norme() << endl;
    cout << (vect9 > 100) << endl;
    cout << endl;

    cout << "test de l'operateur > (7.4, 5.9, -98.7) > 99 norme 99.1527 expected : 1 : " << endl;
    cout << vect9.norme() << endl;
    cout << (vect9 > 99) << endl;
    cout << endl;

    cout << "test de l'operateur > (7.4, 5.9, -98.7) > 99.1527 norme 99.1527 expected : 1 : " << endl;
    cout << vect9.norme() << endl;
    cout << (vect9 > 99.1527) << endl;
    cout << endl;

    cout << "test de l'operateur >= (3, 4, 0) >= 5 norme 5 expected : 1 : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) >= 5) << endl;
    cout << endl;

    cout << "test de l'operateur >= (3, 4, 0) >= 4 norme 5 expected : 1 : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) >= 4) << endl;
    cout << endl;

    cout << "test de l'operateur != (3, 4, 0) != 4 norme 5 expected : 1 : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) != 4) << endl;
    cout << endl;

    cout << "test de l'operateur != (3, 4, 0) != 5 norme 5 expected : 0 : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) != 5) << endl;
    cout << endl;

    cout << "test de l'operateur += (3, 4, 0) += 5.0  expected : (8, 9, 5) : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) += 5.0) << endl;
    cout << endl;

    cout << "test de l'operateur += (3, 4, 0) += (3, 4, -2.5)  expected : (6, 8, -2.5) : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) += Vecteur3D(3, 4, -2.5)) << endl;
    cout << endl;

    cout << "test de l'operateur -= (3, 4, 0) -= (3, 4, -2.5)  expected : (0, 0, +2.5) : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) -= Vecteur3D(3, 4, -2.5)) << endl;
    cout << endl;

    cout << "test de l'operateur = double (3, 4, 0) = 3.0  expected : (3, 3, 3) : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) = 3.0) << endl;
    cout << endl;

    cout << "test de l'operateur + (3, 4, 0) + (3, 4, -2.5)  expected : (6, 8, -2.5) : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) + Vecteur3D(3, 4, -2.5)) << endl;
    cout << endl;

    cout << "test de l'operateur + (3, 4, 0) + (0, 0, 0)  expected : (3, 4, 0) : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) + Vecteur3D()) << endl;
    cout << endl;

    cout << "test de l'operateur - (3, 4, 0) - (3, 4, -2.5)  expected : (0, 0, +2.5) : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) - Vecteur3D(3, 4, -2.5)) << endl;
    cout << endl;

    cout << "test de l'operateur - (3, 4, 0) - (3, 4, 0)  expected : (0, 0, 0) : " << endl;
    cout << ((Vecteur3D(3, 4, 0)) - Vecteur3D(3, 4, 0)) << endl;
    cout << endl;

    cout << "test de l'operateur * (3, 4, -2.5) * 5.0  expected : (15, 20, -12.5) : " << endl;
    cout << ((Vecteur3D(3, 4, -2.5)) * 5.0) << endl;
    cout << endl;

    cout << "test de l'operateur * 5.0 * (3, 4, -2.5) COMMUTATIVE   expected : (15, 20, -12.5) : " << endl;
    cout << (5.0 * (Vecteur3D(3, 4, -2.5)) ) << endl;
    cout << endl;

    return 0;
}
