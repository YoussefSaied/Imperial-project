QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = lib

CONFIG = staticlib

SOURCES = Systeme.cc\
SystemeP9.cc\
Aleatoire.cc \
Plan.cc \
Dalle.cc \
Brique.cc \
Magnet.cc \
Vecteur3D.cc \
Cylinder.cc \
Sphere.cc \
SupportADessinTexte.cc

HEADERS += \
    Systeme.h \
    SystemeP9.h\
    Aleatoire.h \
    Obstacle.h \
    Plan.h \
    Dalle.h \
	Brique.h \
    Magnet.h \
    Vecteur3D.h \
    Dessinable.h \
    SupportADessin.h \
	Cylinder.h \
    Sphere.h \
    SupportADessinTexte.h
