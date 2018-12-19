QT             += opengl
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = excerciceP12

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH += ../general
INCLUDEPATH += ../MediumandQt
CONFIG += qt debug
SOURCES += \
    main_qt_glP12P9.cc \
    glwidgetP12P9.cc \
    ../MediumandQt/glsphere.cc \
    ../MediumandQt/glcylinder.cc \
    ../MediumandQt/vue_opengl.cc \
    ../general/SupportADessinTexte.cc \
    ../general/Systeme.cc \
    ../general/SystemeP9.cc \
    ../general/SystemeP12.cc \
    ../general/Aleatoire.cc \
    ../general/Source.cc \
    ../general/Plan.cc \
    ../general/Dalle.cc \
    ../general/Mediumi.cc \
    ../general/Brique.cc \
    ../general/Sphere.cc \
    ../general/Grain.cc \
    ../general/GrainLJ.cc \
    ../general/Vecteur3D.cc


HEADERS += \
    glwidgetP12P9.h \
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
