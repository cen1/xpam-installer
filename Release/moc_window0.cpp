/****************************************************************************
** Meta object code from reading C++ file 'window0.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../installer/window0.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window0.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Window0_t {
    QByteArrayData data[17];
    char stringdata[313];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Window0_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Window0_t qt_meta_stringdata_Window0 = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 12),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 12),
QT_MOC_LITERAL(4, 35, 21),
QT_MOC_LITERAL(5, 57, 23),
QT_MOC_LITERAL(6, 81, 23),
QT_MOC_LITERAL(7, 105, 23),
QT_MOC_LITERAL(8, 129, 23),
QT_MOC_LITERAL(9, 153, 23),
QT_MOC_LITERAL(10, 177, 23),
QT_MOC_LITERAL(11, 201, 23),
QT_MOC_LITERAL(12, 225, 23),
QT_MOC_LITERAL(13, 249, 23),
QT_MOC_LITERAL(14, 273, 23),
QT_MOC_LITERAL(15, 297, 12),
QT_MOC_LITERAL(16, 310, 1)
    },
    "Window0\0startInstall\0\0abortInstall\0"
    "on_pushButton_clicked\0on_backButton_1_clicked\0"
    "on_backButton_2_clicked\0on_nextButton_1_clicked\0"
    "on_nextButton_2_clicked\0on_pushButton_2_clicked\0"
    "on_pushButton_3_clicked\0on_nextButton_3_clicked\0"
    "on_nextButton_4_clicked\0on_pushButton_4_clicked\0"
    "on_pushButton_5_clicked\0disableAbort\0"
    "b\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window0[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06,
       3,    0,   85,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       4,    0,   86,    2, 0x08,
       5,    0,   87,    2, 0x08,
       6,    0,   88,    2, 0x08,
       7,    0,   89,    2, 0x08,
       8,    0,   90,    2, 0x08,
       9,    0,   91,    2, 0x08,
      10,    0,   92,    2, 0x08,
      11,    0,   93,    2, 0x08,
      12,    0,   94,    2, 0x08,
      13,    0,   95,    2, 0x08,
      14,    0,   96,    2, 0x08,
      15,    1,   97,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,

       0        // eod
};

void Window0::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Window0 *_t = static_cast<Window0 *>(_o);
        switch (_id) {
        case 0: _t->startInstall(); break;
        case 1: _t->abortInstall(); break;
        case 2: _t->on_pushButton_clicked(); break;
        case 3: _t->on_backButton_1_clicked(); break;
        case 4: _t->on_backButton_2_clicked(); break;
        case 5: _t->on_nextButton_1_clicked(); break;
        case 6: _t->on_nextButton_2_clicked(); break;
        case 7: _t->on_pushButton_2_clicked(); break;
        case 8: _t->on_pushButton_3_clicked(); break;
        case 9: _t->on_nextButton_3_clicked(); break;
        case 10: _t->on_nextButton_4_clicked(); break;
        case 11: _t->on_pushButton_4_clicked(); break;
        case 12: _t->on_pushButton_5_clicked(); break;
        case 13: _t->disableAbort((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Window0::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Window0::startInstall)) {
                *result = 0;
            }
        }
        {
            typedef void (Window0::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Window0::abortInstall)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject Window0::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Window0.data,
      qt_meta_data_Window0,  qt_static_metacall, 0, 0}
};


const QMetaObject *Window0::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window0::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Window0.stringdata))
        return static_cast<void*>(const_cast< Window0*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Window0::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Window0::startInstall()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Window0::abortInstall()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
