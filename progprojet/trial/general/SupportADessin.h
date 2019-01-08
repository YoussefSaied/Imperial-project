#pragma once
class Plan;
class SystemeP9;
class SystemeP12;
class Dalle;
class Sphere;
class Brique;
class Cylinder;
class Mediumi;
class Magnet;
class MagnetE;
class MagnetEO;

class SupportADessin
{
public:
    virtual ~SupportADessin() {}


    virtual void dessine(SystemeP9 const& S ) = 0;
    virtual void dessine(SystemeP12 const& S ) = 0;
    virtual void dessine(Plan const& P ) = 0;
    virtual void dessine(Dalle const& d) = 0;
    virtual void dessine(Sphere const& s) = 0;
    virtual void dessine(Brique const& b) = 0;
    virtual void dessine(Mediumi const& M)= 0;
    virtual void dessine(Cylinder const& c) = 0;
		//virtual void dessine(Magnet const& M) = 0;
		virtual void dessine(MagnetE const& M) = 0;
		virtual void dessine(MagnetEO const& M) = 0;
};
