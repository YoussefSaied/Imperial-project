/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../glwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GLWidget_t {
    QByteArrayData data[24];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GLWidget_t qt_meta_stringdata_GLWidget = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GLWidget"
QT_MOC_LITERAL(1, 9, 9), // "XBChanged"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 4), // "newx"
QT_MOC_LITERAL(4, 25, 9), // "YBChanged"
QT_MOC_LITERAL(5, 35, 4), // "newy"
QT_MOC_LITERAL(6, 40, 9), // "ZBChanged"
QT_MOC_LITERAL(7, 50, 4), // "newz"
QT_MOC_LITERAL(8, 55, 14), // "magnetselected"
QT_MOC_LITERAL(9, 70, 2), // "mn"
QT_MOC_LITERAL(10, 73, 7), // "evolved"
QT_MOC_LITERAL(11, 81, 2), // "dt"
QT_MOC_LITERAL(12, 84, 12), // "anglechanged"
QT_MOC_LITERAL(13, 97, 5), // "setXB"
QT_MOC_LITERAL(14, 103, 1), // "x"
QT_MOC_LITERAL(15, 105, 5), // "setYB"
QT_MOC_LITERAL(16, 111, 1), // "y"
QT_MOC_LITERAL(17, 113, 5), // "setZB"
QT_MOC_LITERAL(18, 119, 1), // "z"
QT_MOC_LITERAL(19, 121, 12), // "selectmagnet"
QT_MOC_LITERAL(20, 134, 11), // "changeangle"
QT_MOC_LITERAL(21, 146, 5), // "angle"
QT_MOC_LITERAL(22, 152, 10), // "flipmagnet"
QT_MOC_LITERAL(23, 163, 8) // "omegato0"

    },
    "GLWidget\0XBChanged\0\0newx\0YBChanged\0"
    "newy\0ZBChanged\0newz\0magnetselected\0"
    "mn\0evolved\0dt\0anglechanged\0setXB\0x\0"
    "setYB\0y\0setZB\0z\0selectmagnet\0changeangle\0"
    "angle\0flipmagnet\0omegato0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GLWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       6,    1,  100,    2, 0x06 /* Public */,
       8,    1,  103,    2, 0x06 /* Public */,
      10,    1,  106,    2, 0x06 /* Public */,
      12,    1,  109,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,  112,    2, 0x0a /* Public */,
      15,    1,  115,    2, 0x0a /* Public */,
      17,    1,  118,    2, 0x0a /* Public */,
      13,    1,  121,    2, 0x0a /* Public */,
      15,    1,  124,    2, 0x0a /* Public */,
      17,    1,  127,    2, 0x0a /* Public */,
      19,    1,  130,    2, 0x0a /* Public */,
      20,    1,  133,    2, 0x0a /* Public */,
      22,    0,  136,    2, 0x0a /* Public */,
      23,    0,  137,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Int,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,   14,
    QMetaType::Void, QMetaType::Double,   16,
    QMetaType::Void, QMetaType::Double,   18,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Double,   21,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GLWidget *_t = static_cast<GLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->XBChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->YBChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->ZBChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->magnetselected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->evolved((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->anglechanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setXB((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->setYB((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->setZB((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->setXB((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->setYB((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->setZB((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->selectmagnet((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->changeangle((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->flipmagnet(); break;
        case 15: _t->omegato0(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GLWidget::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLWidget::XBChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GLWidget::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLWidget::YBChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (GLWidget::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLWidget::ZBChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (GLWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLWidget::magnetselected)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (GLWidget::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLWidget::evolved)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (GLWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLWidget::anglechanged)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject GLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLWidget.data,
      qt_meta_data_GLWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget.stringdata0))
        return static_cast<void*>(const_cast< GLWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void GLWidget::XBChanged(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GLWidget::YBChanged(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GLWidget::ZBChanged(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GLWidget::magnetselected(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GLWidget::evolved(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GLWidget::anglechanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
