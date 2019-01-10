#include "SupportADessinTexte.h"
#include <iostream>

#include "Plan.h"
#include "Dalle.h"

#include "SystemeP9.h"
#include "SystemeP12.h"
#include "Brique.h"
#include "Dodec.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Magnet.h"
#include "MagnetE.h"
#include "MagnetEO.h"
using namespace std;




void SupportADessinTexte :: dessine(MagnetE const& M )
{
    M.Magnet::display(cout);
}
void SupportADessinTexte :: dessine(MagnetEO const& M  )
{
		M.Magnet::display(cout);
}


void SupportADessinTexte :: dessine(Plan const& P  )
{
    P.display(cout);
}
void SupportADessinTexte :: dessine(Dalle const& d  )
{
    d.display(cout);
}

void SupportADessinTexte :: dessine(SystemeP9 const& S )
{
    S.display(cout);
}

void SupportADessinTexte :: dessine(SystemeP12 const& S )
{
    S.display(cout);
}

void SupportADessinTexte :: dessine(Sphere const& s)
{
    s.display(cout);
}
void SupportADessinTexte :: dessine(Brique const& b)
{
    vector<Dalle> d6;
    d6 = (b.dalle6());
    for(auto d : d6) {
        d.dessine();
    }
}
void SupportADessinTexte :: dessine(Dodec const& d)
{
d.display(cout);
}

void SupportADessinTexte :: dessine(Cylinder const& c)
{
    c.display(cout);
}

void SupportADessinTexte :: dessine(Mediumi const& M)
{
    M.display(cout);
}
