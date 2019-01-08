QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = lib

CONFIG = staticlib

SOURCES = Systeme.cc\
SystemeP9.cc\
SystemeP12.cc\
Aleatoire.cc \
Plan.cc \
Dalle.cc \
Brique.cc \
Magnet.cc \
MagnetE.cc \
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
    Obstacle.h \
    Plan.h \
    Dalle.h \
	Brique.h \
    Magnet.h \
    MagnetE.h \
    MagnetEO.h \
    Medium.h \
    Mediumi.h \
    Vecteur3D.h \
    Dessinable.h \
    SupportADessin.h \
	Cylinder.h \
    Sphere.h \
    SupportADessinTexte.h
