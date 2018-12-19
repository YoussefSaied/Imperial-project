QMAKE_CXXFLAGS += -std=c++11 -g

TARGET = testTexte

INCLUDEPATH = ../general

SOURCES += \
	../general/main_text.cc \
	../general/SupportADessinTexte.cc \
    ../general/Systeme.cc \
    ../general/Aleatoire.cc \
    ../general/Source.cc \
    ../general/Grain.cc\
    ../general/GrainLJ.cc \
    ../general/Sphere.cc \
    ../general/Brique.cc \
    ../general/Dalle.cc \   
    ../general/Plan.cc \
    ../general/Vecteur3D.cc \
	../general/SystemeP9.cc \
    ../general/SystemeP12.cc 
    
    
HEADERS += \
    ../general/SupportADessinTexte.h \
    ../general/Dessinable.h \
    ../general/SupportADessin.h \
    ../general/Systeme.h \
    ../general/Aleatoire.h \
    ../general/Brique.h \
    ../general/Source.h \
    ../general/Obstacle.h \
    ../general/Plan.h \
    ../general/Dalle.h \
    ../general/Grain.h \
    ../general/GrainLJ.h \
    ../general/GrainLJUn.h \
    ../general/GrainLJDeux.h \
    ../general/Medium.h \
    ../general/Sphere.h \
    ../general/Vecteur3D.h \
    ../general/SystemeP9.h \
    ../general/SystemeP12.h \
    ../general/Mediumi.h 
    
