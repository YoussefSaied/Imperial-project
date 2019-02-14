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
        std::string s = "B =  ";
        std::stringstream ss;
        ss << (glWidget->system_tab[0])->B << std::endl;
        ss << "Time: " << (glWidget->system_tab[0])->time << std::endl;
        ss << "Number of magnets in the system: " << (glWidget->system_tab[0])->tab_ptr_Magnets.size() << std::endl;
        ss << "Correlation: " << (glWidget->system_tab[0])->NearestCorrelation() << std::endl;
        ss << "Hamiltonian: " << (glWidget->system_tab[0])->Energy();
        ss << std::endl;
        ss << "Kinetic Energy: " << (glWidget->system_tab[0])->KineticEnergy;
        ss << ", Potential Energy: " << (glWidget->system_tab[0])->PotentialEnergy << std::endl;
        ss << "Friction: " << (glWidget->system_tab[0])->f;


        s += ss.str();
        QString qstr = QString::fromStdString(s);
        labelO->setText(qstr);
        if ((glWidget->system_tab[0])->time > 0.00) {
            HamiltonianTime->append((glWidget->system_tab[0])->time, (glWidget->system_tab[0])->Energy());
            KineticTime->append((glWidget->system_tab[0])->time, (glWidget->system_tab[0])->KineticEnergy);
            PotentialTime->append((glWidget->system_tab[0])->time, (glWidget->system_tab[0])->PotentialEnergy);
            CorrelationTime->append((glWidget->system_tab[0])->time, (glWidget->system_tab[0])->NearestCorrelation());
            myaxis1->setMax(abs((glWidget->system_tab[0])->Energy() * 2));
            myaxis1->setMin(-1 * abs((glWidget->system_tab[0])->Energy() * 2));

            // myaxis2->setMax(abs((glWidget->system_tab[0])->NearestCorrelation() * 2));
            // myaxis2->setMin(-1 * abs((glWidget->system_tab[0])->NearestCorrelation() * 2));

            // myaxis1->applyNiceNumbers();
        }
        // HamiltonianTime->remove(0);
    } // updatelabelO

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
    QSplineSeries * KineticTime;
    QSplineSeries * PotentialTime;
    QSplineSeries * CorrelationTime;
    QChart * chart1;
    QChartView * chartview1;
    QChart * chart2;
    QChartView * chartview2;
    QValueAxis * myaxis1;
    QValueAxis * myaxis2;
};

// double spinbox for moment, angle (double connected)
// Qlabel for time current magnet position and mass radius, height
