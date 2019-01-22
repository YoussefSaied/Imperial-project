QT             += opengl
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simulation1
LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH += ../general
INCLUDEPATH += ../MediumandQt
CONFIG += qt debug
SOURCES += \
    main_qt_glP12P9.cc \
    glwidgetP12P9.cc \
    Window.cc \
    ../MediumandQt/glsphere.cc \
    ../MediumandQt/glcylinder.cc \
    ../MediumandQt/vue_opengl.cc \
    ../general/SupportADessinTexte.cc \
    ../general/Systeme.cc \
    ../general/SystemeP9.cc \
    ../general/Aleatoire.cc \
    ../general/Magnet.cc \
    ../general/Plan.cc \
    ../general/Dalle.cc \
    ../general/Brique.cc \
    ../general/Dodec.cc \
    ../general/Sphere.cc \
    ../general/Vecteur3D.cc


HEADERS += \
    glwidgetP12P9.h \
    Window.h \
    ../MediumandQt/vertex_shader.h \
    ../MediumandQt/vue_opengl.h \
    ../MediumandQt/glsphere.h \
    ../MediumandQt/glcylinder.h \
    ../general/Dessinable.h \
    ../general/SupportADessin.h \
    ../general/SupportADessinTexte.h \
    ../general/Systeme.h \
    ../general/SystemeP9.h \
    ../general/Aleatoire.h \
    ../general/Magnet.h \
    ../general/Obstacle.h \
    ../general/Plan.h \
    ../general/Dalle.h \
    ../general/Brique.h \
    ../general/Dodec.h \
    ../general/Sphere.h \
    ../general/Vecteur3D.h

RESOURCES += \
    ../MediumandQt/resource.qrc
