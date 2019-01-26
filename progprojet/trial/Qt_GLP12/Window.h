#include <QGLWidget> // Classe pour faire une fenêtre OpenGL
#include <QTime>
#include <QSlider>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include "vue_opengl.h"
#include "Systeme.h"
#include "SystemeP9.h"
#include "glwidgetP12P9.h"
#include <string>
#include <sstream>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    GLWidget * glWidget;
    QSlider * createSlider();
    QSpinBox * createSpin();
    QDoubleSpinBox * createdoubleSpin(double step = 0.01);

public slots:
    void updatelabelO()
    {
        // do that at the system level
        std::string s = "Graphical Window, H=  ";
        std::stringstream ss;
        ss << (glWidget->system_tab[0])->H;
        ss << ", time: " << (glWidget->system_tab[0])->time;
        ss << ", Hamiltonian: " << (glWidget->system_tab[0])->Energy;
        s += ss.str();
        QString qstr = QString::fromStdString(s);
        labelO->setText(qstr);
    }

    void setmagnetT(int mn)
    {
        std::string s = "";
        std::stringstream ss;
        int siz(((glWidget->system_tab[0])->tab_ptr_Magnets).size());
        ((glWidget->system_tab[0])->tab_ptr_Magnets[mn % siz])->display(ss);
        s += ss.str();
        QString qstr = QString::fromStdString(s);
        labels->setText(qstr);
    }

    void setangleT(int mn){ setmagnetT(mn); }

public:
    QSlider * xSlider;
    QSlider * ySlider;
    QSlider * zSlider;
    QLabel * labels;
    QLabel * labelO;
    QSpinBox * magnetselector;
    QDoubleSpinBox * angleselector;
    QDoubleSpinBox * xselector;
    QDoubleSpinBox * yselector;
    QDoubleSpinBox * zselector;
    QPushButton * flipangle;
    QPushButton * omegato0;
};

// double spinbox for moment, angle (double connected)
// Qlabel for time current magnet position and mass radius, height
