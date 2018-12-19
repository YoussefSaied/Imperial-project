#include "Mediumi.h"
#include <vector>
#include <cmath>

bool Mediumi:: is_inside(Grain& g) const
    {
        if(Brique::is_inside(g.get_position())) g.set_medium(*medium);
        return Brique::is_inside(g.get_position());
    }

    std::vector<Dalle> Mediumi:: dalle5() const
    {
        std::vector<Dalle> d5;
        //1

        //2
        d5.push_back(Dalle((get_position()-hauteur*get_vecteur_1()) , get_vecteur_1()
                           , get_vecteur_2(),get_longueur(), get_largeur()));
        //3
        d5.push_back(Dalle((get_position()) , -1*get_vecteur_2()
                           , get_vecteur_3(),get_largeur(), hauteur));

        //4
        d5.push_back(Dalle((get_position()) , -1*get_vecteur_3()
                           , -1* get_vecteur_1(),hauteur, get_longueur()));

        //5
        d5.push_back(Dalle((get_position() + get_longueur()*get_vecteur_2()) , get_vecteur_2()
                           , -1*get_vecteur_1(),hauteur, get_largeur()));

        //6
        d5.push_back(Dalle((get_position() + get_largeur()*get_vecteur_3()) , get_vecteur_3()
                           , get_vecteur_2(),get_longueur(), hauteur));

        return d5;
    }
    
std::ostream& Mediumi:: display(std::ostream& c) const
    {
        c<<"Je suis un millieu INTERNE!";
        return c;
    }
