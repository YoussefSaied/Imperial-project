QT             += opengl
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Obstacleshowcase

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH += ../general
INCLUDEPATH += ../MediumandQt
CONFIG += qt debug
SOURCES += \
    Obstacleshowcase.cc \
    ../MediumandQt/glwidget.cc \
    ../MediumandQt/glsphere.cc \
    ../MediumandQt/glcylinder.cc \
    ../MediumandQt/vue_opengl.cc


HEADERS += \
    ../MediumandQt/glwidget.h \
    ../MediumandQt/vertex_shader.h \
    ../MediumandQt/vue_opengl.h \
    ../MediumandQt/glsphere.h \
    ../MediumandQt/glcylinder.h \
    ../general/Dessinable.h \
    ../general/SupportADessin.h \
    ../general/SupportADessinTexte.h \
    ../general/Systeme.h \
    ../general/SystemeP9.h \
    ../general/SystemeP12.h \
    ../general/Aleatoire.h \
    ../general/Source.h \
    ../general/Obstacle.h \
    ../general/Plan.h \
    ../general/Dalle.h \
    ../general/Brique.h \
    ../general/Sphere.h \
    ../general/Grain.h \
    ../general/GrainLJ.h \
    ../general/GrainLJUn.h \
    ../general/GrainLJDeux.h \
    ../general/Medium.h \
    ../general/Mediumi.h \
    ../general/Vecteur3D.h

RESOURCES += \
    ../MediumandQt/resource.qrc
