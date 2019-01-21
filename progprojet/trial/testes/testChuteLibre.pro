QMAKE_CXXFLAGS += -std=c++11 -g

TARGET = testChuteLibre

INCLUDEPATH = ../general

SOURCES += \
	../general/testChuteLibre.cc \
	../general/Systeme.cc \
	../general/SupportADessinTexte.cc \
	../general/Vecteur3D.cc \
	../general/Source.cc \
    ../general/Aleatoire.cc \
    ../general/Grain.cc\
    ../general/GrainLJ.cc \
    ../general/Plan.cc \
    ../general/Dalle.cc \
    ../general/Sphere.cc \
	../general/SystemeP9.cc \
    ../general/Brique.cc \
    ../general/SystemeP12.cc\

HEADERS += \
    ../general/SupportADessinTexte.h \
    ../general/Dessinable.h \
    ../general/SupportADessin.h \
    ../general/Aleatoire.h \
    ../general/Systeme.h \
    ../general/Source.h \
    ../general/Obstacle.h \
    ../general/Plan.h \
    ../general/Dalle.h \
    ../general/Grain.h \
    ../general/GrainLJ.h \
    ../general/GrainLJUn.h \
    ../general/GrainLJDeux.h \
    ../general/Vecteur3D.h \
    ../general/Sphere.h \
    ../general/SystemeP9.h \
    ../general/SystemeP12.h \
    ../general/Brique.h \
