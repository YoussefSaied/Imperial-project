#pragma once
class Grain;
class GrainLJ;
class Plan;
class SystemeP9;
class SystemeP12;
class Source;
class GrainLJUn;
class GrainLJDeux;
class Dalle;
class Sphere;
class Brique;
class Cylinder;
class Mediumi;

class SupportADessin
{
public:
    virtual ~SupportADessin() {}

    virtual void dessine(GrainLJ const&  G ) = 0;
    virtual void dessine(GrainLJUn const& G   ) = 0;
    virtual void dessine(GrainLJDeux  const& G  ) = 0;
    virtual void dessine(SystemeP9 const& S ) = 0;
    virtual void dessine(SystemeP12 const& S ) = 0;
    virtual void dessine(Plan const& P ) = 0;
    virtual void dessine(Dalle const& d) = 0;
    virtual void dessine(Source const& s) = 0;
    virtual void dessine(Sphere const& s) = 0;
    virtual void dessine(Brique const& b) = 0;
    virtual void dessine(Mediumi const& M)= 0;
    virtual void dessine(Cylinder const& c) = 0;
};
