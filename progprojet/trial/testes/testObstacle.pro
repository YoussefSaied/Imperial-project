QMAKE_CXXFLAGS += -std=c++11 -g

TARGET = testObstacle

INCLUDEPATH = ../general

SOURCES += \
    ../general/testObstacle.cc \
    ../general/GrainsAvant.cc \
    ../general/Plan.cc \
    ../general/Dalle.cc \
    ../general/Brique.cc \
    ../general/SupportADessinTexte.cc \
    ../general/Vecteur3D.cc
    
HEADERS += \
    ../general/Vecteur3D.h \
    ../general/GrainsAvant.h \
    ../general/Dessinable.h \
    ../general/Obstacle.h \
    ../general/Plan.h \
    ../general/Brique.h \
    ../general/SupportADessinTexte.h \
    ../general/dessinable.h \
    ../general/Dalle.h \
    ../general/SupportADessin.h 
    
