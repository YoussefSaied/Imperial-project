QMAKE_CXXFLAGS += -std=c++11 -g

TARGET = testSystemeP9

INCLUDEPATH = ../general

SOURCES += \
	../general/testSystemeP9.cc \
	../general/Systeme.cc \
	../general/SystemeP9.cc \
	../general/SupportADessinTexte.cc \
	../general/Vecteur3D.cc \
	../general/Source.cc \
    ../general/Aleatoire.cc \
    ../general/Grain.cc\
    ../general/GrainLJ.cc \
    ../general/Mediumi.cc \
    ../general/Plan.cc \
    ../general/Brique.cc \
    ../general/SystemeP12.cc \
    ../general/Dalle.cc 
    
HEADERS += \
    ../general/SupportADessinTexte.h \
    ../general/Dessinable.h \
    ../general/SupportADessin.h \
    ../general/Aleatoire.h \
    ../general/Systeme.h \
    ../general/SystemeP9.h \
    ../general/Source.h \
    ../general/Obstacle.h \
    ../general/Plan.h \
    ../general/Dalle.h \
    ../general/Grain.h \
    ../general/GrainLJ.h \
    ../general/GrainLJUn.h \
    ../general/GrainLJDeux.h \
    ../general/Medium.h \
    ../general/Vecteur3D.h \
    ../general/SystemeP12.h \
    ../general/Brique.h \
    ../general/Mediumi.h 
