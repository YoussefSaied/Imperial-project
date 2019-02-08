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
#include "glwidget.h"
#include <string>
#include <sstream>
#include <QtCharts>

using namespace QtCharts;
class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    GLWidget * glWidget;
    QSlider * createSlider();
    QSpinBox * createSpin();
    QDoubleSpinBox * createdoubleSpin(double step = 0.01);
    QSplineSeries * createScatterSeries();
    QChart * createMyChart(QString s = "Hamiltonian");

public slots:
    void updatelabelO()
    {
        // do that at the system level
        std::string s = "Graphical Window, B=  ";
        std::stringstream ss;
        ss << (glWidget->system_tab[0])->B;
        ss << ", time: " << (glWidget->system_tab[0])->time;
        ss << ", Hamiltonian: " << (glWidget->system_tab[0])->Energy();
        ss << std::endl;
        ss << "friction: " << (glWidget->system_tab[0])->f;
        ss << ", Kinetic Energy: " << (glWidget->system_tab[0])->KineticEnergy;
        ss << std::endl << "PotentialEnergy: " << (glWidget->system_tab[0])->PotentialEnergy;
        s += ss.str();
        QString qstr = QString::fromStdString(s);
        labelO->setText(qstr);
        if ((glWidget->system_tab[0])->time >= 0.05 and std::fmod((glWidget->system_tab[0])->time, 0.1) ) {
            HamiltonianTime->append((glWidget->system_tab[0])->time, (glWidget->system_tab[0])->Energy());
        }
        // HamiltonianTime->remove(0);
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
        // HamiltonianTime->append((glWidget->system_tab[0])->time, (glWidget->system_tab[0])->Energy());
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
    QSplineSeries * HamiltonianTime;
    QChart * chart;
    QChartView * chartview;
};

// double spinbox for moment, angle (double connected)
// Qlabel for time current magnet position and mass radius, height
