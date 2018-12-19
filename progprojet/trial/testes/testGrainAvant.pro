QMAKE_CXXFLAGS += -std=c++11 -g

TARGET = testGrainAvant

INCLUDEPATH = ../general

SOURCES += \
    ../general/testGrainsAvant.cc \
    ../general/GrainsAvant.cc \
    ../general/Vecteur3D.cc
    
HEADERS += \
    ../general/Vecteur3D.h \
    ../general/GrainsAvant.h
    
