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
    // connect evolve to H
    connect(glWidget, SIGNAL(XHChanged(double)), this, SLOT(updatelabelO(double)));
    connect(glWidget, SIGNAL(YHChanged(double)), this, SLOT(updatelabelO(double)));
    connect(glWidget, SIGNAL(ZHChanged(double)), this, SLOT(updatelabelO(double)));
    connect(glWidget, SIGNAL(evolved(double)), this, SLOT(updatelabelO(double)));
    // connect evolve with update

    QLabel * labelx = new QLabel(this);
    labelx->setText("Hx");
    QLabel * labely = new QLabel(this);
    labely->setText("Hy");
    QLabel * labelz = new QLabel(this);
    labelz->setText("Hz");
    QLabel * labela = new QLabel(this);
    labela->setText("Change Angle:");

    xSlider        = createSlider();
    ySlider        = createSlider();
    zSlider        = createSlider();
    magnetselector = createSpin();
    labels         = new QLabel(this);
    labels->setText("Change Magnet");
    angleselector = createdoubleSpin();
    flipangle     = new QPushButton("Flip", this);


    connect(xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXH(int)));
    connect(ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYH(int)));
    connect(zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZH(int)));
    connect(magnetselector, SIGNAL(valueChanged(int)), glWidget, SLOT(selectmagnet(int)));
    connect(glWidget, SIGNAL(magnetselected(int)), this, SLOT(setmagnetT(int)));
    connect(flipangle, SIGNAL(clicked()), glWidget, SLOT(flipmagnet()));
    connect(angleselector, SIGNAL(valueChanged(double)), glWidget, SLOT(changeangle(double)));
    connect(glWidget, SIGNAL(anglechanged(int)), this, SLOT(setangleT(int)));
    QGridLayout * mainLayout = new QGridLayout;
    mainLayout->addWidget(glWidget, 0, 0);
    mainLayout->addWidget(labelO, 9, 0);
    mainLayout->addWidget(xSlider, 0, 1);
    mainLayout->addWidget(labelx, 9, 1);
    mainLayout->addWidget(ySlider, 0, 2);
    mainLayout->addWidget(labely, 9, 2);
    mainLayout->addWidget(zSlider, 0, 3);
    mainLayout->addWidget(labelz, 9, 3);
    mainLayout->addWidget(labels, 0, 5);
    mainLayout->addWidget(magnetselector, 0, 6);
    mainLayout->addWidget(labela, 9, 5);
    mainLayout->addWidget(flipangle, 9, 7);
    mainLayout->addWidget(angleselector, 9, 6);

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

QDoubleSpinBox * Window::createdoubleSpin()
{
    QDoubleSpinBox * spin = new QDoubleSpinBox();
    spin->setRange(0, 100);
    spin->setSingleStep(0.01);
    return spin;
}
