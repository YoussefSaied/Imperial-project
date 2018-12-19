#include "SupportADessinTexte.h"
#include <iostream>
#include "GrainLJ.h"
#include "Grain.h"
#include "Plan.h"
#include "Dalle.h"
#include "Source.h"
#include "SystemeP9.h"
#include "SystemeP12.h"
#include "Brique.h"
#include "Sphere.h"
#include "Cylinder.h"
using namespace std;


void SupportADessinTexte :: dessine(GrainLJ const& G )
{
    cout<<"Grain L-J : ";
    G.Grain::display(cout);
}
void SupportADessinTexte :: dessine(GrainLJUn const& G  )
{
    cout<<"Grain L-J de type un : ";
    G.Grain::display(cout);
}
void SupportADessinTexte :: dessine(GrainLJDeux const& G  )
{
    cout<<"Grain L-J de type deux : ";
    G.Grain::display(cout);
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
void SupportADessinTexte :: dessine(Source const& s)
{
    s.display(cout);
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
void SupportADessinTexte :: dessine(Cylinder const& c)
{
    c.display(cout);
}

void SupportADessinTexte :: dessine(Mediumi const& M)
{
    M.display(cout);
}
