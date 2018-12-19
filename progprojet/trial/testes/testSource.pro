QMAKE_CXXFLAGS += -std=c++11 -g

TARGET = testSource

INCLUDEPATH = ../general

SOURCES += \
	../general/testSource.cc \
	../general/SupportADessinTexte.cc \
	../general/Vecteur3D.cc \
	../general/Source.cc \
    ../general/Aleatoire.cc \
    ../general/Grain.cc\
    ../general/GrainLJ.cc \
    ../general/Brique.cc \
    ../general/Plan.cc \
    ../general/Dalle.cc 
    
HEADERS += \
    ../general/SupportADessinTexte.h \
    ../general/dessinable.h \
    ../general/SupportADessin.h \
    ../general/Aleatoire.h \
    ../general/Source.h \
    ../general/Obstacle.h \
    ../general/Plan.h \
    ../general/Brique.h \
    ../general/Dalle.h \
    ../general/Grain.h \
    ../general/GrainLJ.h \
    ../general/GrainLJUn.h \
    ../general/GrainLJDeux.h \
    ../general/Medium.h \
    ../general/Vecteur3D.h
