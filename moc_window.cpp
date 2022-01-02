/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata__window_t {
    QByteArrayData data[21];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata__window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata__window_t qt_meta_stringdata__window = {
    {
QT_MOC_LITERAL(0, 0, 7), // "_window"
QT_MOC_LITERAL(1, 8, 9), // "animacion"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 7), // "Forearm"
QT_MOC_LITERAL(4, 27, 9), // "_opciones"
QT_MOC_LITERAL(5, 37, 6), // "opcion"
QT_MOC_LITERAL(6, 44, 7), // "ArmBody"
QT_MOC_LITERAL(7, 52, 3), // "Fly"
QT_MOC_LITERAL(8, 56, 6), // "Ratios"
QT_MOC_LITERAL(9, 63, 5), // "Modes"
QT_MOC_LITERAL(10, 69, 11), // "_draw_modes"
QT_MOC_LITERAL(11, 81, 2), // "dm"
QT_MOC_LITERAL(12, 84, 7), // "Objects"
QT_MOC_LITERAL(13, 92, 7), // "_object"
QT_MOC_LITERAL(14, 100, 2), // "ot"
QT_MOC_LITERAL(15, 103, 16), // "Luces_Materiales"
QT_MOC_LITERAL(16, 120, 11), // "Perspectiva"
QT_MOC_LITERAL(17, 132, 4), // "Ejes"
QT_MOC_LITERAL(18, 137, 10), // "choose_ply"
QT_MOC_LITERAL(19, 148, 2), // "op"
QT_MOC_LITERAL(20, 151, 14) // "choose_texture"

    },
    "_window\0animacion\0\0Forearm\0_opciones\0"
    "opcion\0ArmBody\0Fly\0Ratios\0Modes\0"
    "_draw_modes\0dm\0Objects\0_object\0ot\0"
    "Luces_Materiales\0Perspectiva\0Ejes\0"
    "choose_ply\0op\0choose_texture"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data__window[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    1,   75,    2, 0x0a /* Public */,
       6,    1,   78,    2, 0x0a /* Public */,
       7,    1,   81,    2, 0x0a /* Public */,
       8,    1,   84,    2, 0x0a /* Public */,
       9,    1,   87,    2, 0x0a /* Public */,
      12,    1,   90,    2, 0x0a /* Public */,
      15,    1,   93,    2, 0x0a /* Public */,
      16,    1,   96,    2, 0x0a /* Public */,
      17,    1,   99,    2, 0x0a /* Public */,
      18,    1,  102,    2, 0x0a /* Public */,
      20,    1,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,   19,
    QMetaType::Void, 0x80000000 | 4,   19,

       0        // eod
};

void _window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<_window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->animacion(); break;
        case 1: _t->Forearm((*reinterpret_cast< _opciones(*)>(_a[1]))); break;
        case 2: _t->ArmBody((*reinterpret_cast< _opciones(*)>(_a[1]))); break;
        case 3: _t->Fly((*reinterpret_cast< _opciones(*)>(_a[1]))); break;
        case 4: _t->Ratios((*reinterpret_cast< _opciones(*)>(_a[1]))); break;
        case 5: _t->Modes((*reinterpret_cast< _draw_modes(*)>(_a[1]))); break;
        case 6: _t->Objects((*reinterpret_cast< _object(*)>(_a[1]))); break;
        case 7: _t->Luces_Materiales((*reinterpret_cast< _opciones(*)>(_a[1]))); break;
        case 8: _t->Perspectiva((*reinterpret_cast< _opciones(*)>(_a[1]))); break;
        case 9: _t->Ejes((*reinterpret_cast< _opciones(*)>(_a[1]))); break;
        case 10: _t->choose_ply((*reinterpret_cast< _opciones(*)>(_a[1]))); break;
        case 11: _t->choose_texture((*reinterpret_cast< _opciones(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject _window::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata__window.data,
    qt_meta_data__window,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *_window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata__window.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int _window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
