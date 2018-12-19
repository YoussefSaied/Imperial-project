QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = lib

CONFIG = staticlib

SOURCES = Systeme.cc\
SystemeP9.cc\
SystemeP12.cc\
Aleatoire.cc \
Source.cc \
Plan.cc \
Dalle.cc \
Brique.cc \
Grain.cc \
GrainLJ.cc \
Vecteur3D.cc \
Cylinder.cc \
Sphere.cc \
Mediumi.cc \
SupportADessinTexte.cc

HEADERS += \
    Systeme.h \
    SystemeP9.h\
    SystemeP12.h\
    Aleatoire.h \
    Source.h \
    Obstacle.h \
    Plan.h \
    Dalle.h \
	Brique.h \
    Grain.h \
    GrainLJ.h \
    GrainLJUn.h \
    GrainLJDeux.h \
    Medium.h \
    Mediumi.h \
    Vecteur3D.h \
    Dessinable.h \
    SupportADessin.h \
	Cylinder.h \
    Sphere.h \
    SupportADessinTexte.h
