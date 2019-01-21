QMAKE_CXXFLAGS += -std=c++11 -g

TARGET = testGrainLJ

INCLUDEPATH = ../general

SOURCES += \
	../general/testGrainLJ.cc \
	../general/SupportADessinTexte.cc \
	../general/Vecteur3D.cc \
    ../general/Grain.cc\
    ../general/GrainLJ.cc \
    ../general/Plan.cc \
    ../general/Brique.cc \
    ../general/Dalle.cc

HEADERS += \
    ../general/SupportADessinTexte.h \
    ../general/dessinable.h \
    ../general/SupportADessin.h \
    ../general/Obstacle.h \
    ../general/Plan.h \
    ../general/Brique.h \
    ../general/Dalle.h \
    ../general/Grain.h \
    ../general/GrainLJ.h \
    ../general/GrainLJUn.h \
    ../general/GrainLJDeux.h \
    ../general/Vecteur3D.h
