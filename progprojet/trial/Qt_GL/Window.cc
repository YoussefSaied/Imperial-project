#include "Window.h"
#include <string>
#include <sstream>


Window::Window()

{
    glWidget = new GLWidget;
    glWidget->setFocusPolicy(Qt::ClickFocus);
    labelO = new QLabel(this);
    updatelabelO();
    // H= blabla, correlation, time
    connect(glWidget, SIGNAL(XBChanged(double)), this, SLOT(updatelabelO()));
    connect(glWidget, SIGNAL(YBChanged(double)), this, SLOT(updatelabelO()));
    connect(glWidget, SIGNAL(ZBChanged(double)), this, SLOT(updatelabelO()));
    connect(glWidget, SIGNAL(evolved(double)), this, SLOT(updatelabelO()));


    // chart1
    myaxis1         = new QValueAxis();
    chart1          = createMyChart("Energy (x10^4)");
    HamiltonianTime = createScatterSeries();
    KineticTime     = createScatterSeries();
    PotentialTime   = createScatterSeries();
    HamiltonianTime->setName("Total");
    KineticTime->setName("Kinetic");
    PotentialTime->setName("Potential");
    // HamiltonianTime->setMarkerSize(10);
    chart1->addSeries(HamiltonianTime);
    chart1->addSeries(KineticTime);
    chart1->addSeries(PotentialTime);
    chartview1 = new QChartView(chart1);
    chart1->createDefaultAxes();
    chart1->axisX()->setRange(0, 30);
    myaxis1->setTickCount(8);
    myaxis1->setLabelFormat("%.1f");
    chartview1->chart()->setAxisY(myaxis1, HamiltonianTime);
    chartview1->chart()->setAxisY(myaxis1, KineticTime);
    chartview1->chart()->setAxisY(myaxis1, PotentialTime);

    // chart1->setAxisY(myaxis1);
    //  chart1->setAxis(myaxis1)//, Qt::AlignLeft);
    // chart1->addAxis(myaxis12, Qt::AlignRight);
    // HamiltonianTime->attachAxis(myaxis1);
    // KineticTime->attachAxis(myaxis1);
    // PotentialTime->attachAxis(myaxis1);
    // myaxis12->append("0", 0);
    // chart1->setAxisY(myaxis12);
    // chart->createDefaultAxes();
    // chart->
    // maybe other series


    // chart2
    myaxis2 = new QValueAxis();
    myaxis2->setTickCount(8);
    myaxis2->setMax(1);
    chart2 = createMyChart("Correlation");
    CorrelationTime = createScatterSeries();
    // HamiltonianTime->setMarkerSize(10);
    chart2->addSeries(CorrelationTime);
    chartview2 = new QChartView(chart2);
    chart2->createDefaultAxes();
    chart2->axisX()->setRange(0, 30);
    // chart->axisY()->setRange(-0.01, 0.01);
    chart2->setAxisY(myaxis2);
    CorrelationTime->attachAxis(myaxis2);
    // chart->createDefaultAxes();
    // chart->
    // maybe other series

    QLabel * labelx = new QLabel(this);
    labelx->setText("Bx (x10^-6)");
    QLabel * labely = new QLabel(this);
    labely->setText("By (x10^-6)");
    QLabel * labelz = new QLabel(this);
    labelz->setText("Bz (x10^-6)");
    QLabel * labela = new QLabel(this);
    labela->setText("Change Angle:");
    QLabel * labelom = new QLabel(this);
    labelom->setText("Change Omega:");
    QLabel * labelmagnet = new QLabel(this);
    labelmagnet->setText("Change Magnet:");

    xSlider        = createSlider();
    ySlider        = createSlider();
    zSlider        = createSlider();
    xselector      = createdoubleSpin(0.1);
    yselector      = createdoubleSpin(0.1);
    zselector      = createdoubleSpin(0.1);
    magnetselector = createSpin();
    labels         = new QLabel(this);
    labels->setText("Change Magnet");
    angleselector = createdoubleSpin();
    flipangle     = new QPushButton("Flip", this);
    omegato0      = new QPushButton("0", this);


    connect(xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXB(int)));
    connect(ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYB(int)));
    connect(zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZB(int)));
    connect(xselector, SIGNAL(valueChanged(double)), glWidget, SLOT(setXB(double)));
    connect(yselector, SIGNAL(valueChanged(double)), glWidget, SLOT(setYB(double)));
    connect(zselector, SIGNAL(valueChanged(double)), glWidget, SLOT(setZB(double)));
    // 6 connections to H value changed
    connect(magnetselector, SIGNAL(valueChanged(int)), glWidget, SLOT(selectmagnet(int)));
    connect(glWidget, SIGNAL(magnetselected(int)), this, SLOT(setmagnetT(int)));
    connect(flipangle, SIGNAL(clicked()), glWidget, SLOT(flipmagnet()));
    connect(omegato0, SIGNAL(clicked()), glWidget, SLOT(omegato0()));
    connect(angleselector, SIGNAL(valueChanged(double)), glWidget, SLOT(changeangle(double)));
    connect(glWidget, SIGNAL(anglechanged(int)), this, SLOT(setangleT(int)));
    QGridLayout * mainLayout = new QGridLayout;
    mainLayout->addWidget(glWidget, 0, 0, 2, 1);
    mainLayout->addWidget(labelO, 2, 0, -1, 1);

    mainLayout->addWidget(chartview1, 0, 1, 1, 2);
    mainLayout->addWidget(chartview2, 1, 1, 1, 2);
    // mainLayout->setColumnStretch(8, 2);
    mainLayout->setColumnMinimumWidth(1, 250);

    // mainLayout->addWidget(xSlider, 0, 1);
    mainLayout->addWidget(xselector, 4, 2);
    mainLayout->addWidget(labelx, 4, 1);
    // mainLayout->addWidget(ySlider, 0, 2);
    mainLayout->addWidget(yselector, 3, 2);
    mainLayout->addWidget(labely, 3, 1);
    // mainLayout->addWidget(zSlider, 0, 3);
    mainLayout->addWidget(zselector, 2, 2);
    mainLayout->addWidget(labelz, 2, 1);

    mainLayout->addWidget(labels, 1, 5, 1, 3);


    mainLayout->addWidget(labelmagnet, 2, 5);
    mainLayout->addWidget(magnetselector, 2, 6);
    mainLayout->addWidget(labelom, 3, 5);
    mainLayout->addWidget(omegato0, 3, 6);
    mainLayout->addWidget(labela, 4, 5);
    mainLayout->addWidget(angleselector, 4, 6);
    mainLayout->addWidget(flipangle, 4, 7);


    setLayout(mainLayout);

    xSlider->setValue(0 * 16);
    ySlider->setValue(0 * 16);
    zSlider->setValue(0 * 16);
    setWindowTitle(tr("Magnetic Frustration"));
}

QSlider * Window::createSlider()
{
    QSlider * slider = new QSlider(Qt::Vertical);

    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

QSpinBox * Window::createSpin()
{
    QSpinBox * spin = new QSpinBox();

    spin->setRange(0, 100);
    spin->setSingleStep(1);
    return spin;
}

QDoubleSpinBox * Window::createdoubleSpin(double step)
{
    QDoubleSpinBox * spin = new QDoubleSpinBox();
    spin->setRange(0, 1000000);
    spin->setSingleStep(step);
    return spin;
}

QSplineSeries * Window::createScatterSeries()
{
    QSplineSeries * ScatterSeries1 = new QSplineSeries();
    return ScatterSeries1;
}

QChart * Window::createMyChart(QString s)
{
    QChart * MyChart = new QChart();
    MyChart->setTitle(s);
    return MyChart;
}
