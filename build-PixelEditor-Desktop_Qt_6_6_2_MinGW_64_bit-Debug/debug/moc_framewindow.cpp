/****************************************************************************
** Meta object code from reading C++ file 'framewindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PixelEditor/framewindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'framewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSFrameWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSFrameWindowENDCLASS = QtMocHelpers::stringData(
    "FrameWindow",
    "informViewOfPencilEnabled",
    "",
    "sendPixmapData",
    "QPixmap*",
    "p",
    "setDrawingColor",
    "newColor",
    "setBrushEnabled",
    "setEraserEnabled"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSFrameWindowENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[12];
    char stringdata1[26];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[9];
    char stringdata5[2];
    char stringdata6[16];
    char stringdata7[9];
    char stringdata8[16];
    char stringdata9[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSFrameWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSFrameWindowENDCLASS_t qt_meta_stringdata_CLASSFrameWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "FrameWindow"
        QT_MOC_LITERAL(12, 25),  // "informViewOfPencilEnabled"
        QT_MOC_LITERAL(38, 0),  // ""
        QT_MOC_LITERAL(39, 14),  // "sendPixmapData"
        QT_MOC_LITERAL(54, 8),  // "QPixmap*"
        QT_MOC_LITERAL(63, 1),  // "p"
        QT_MOC_LITERAL(65, 15),  // "setDrawingColor"
        QT_MOC_LITERAL(81, 8),  // "newColor"
        QT_MOC_LITERAL(90, 15),  // "setBrushEnabled"
        QT_MOC_LITERAL(106, 16)   // "setEraserEnabled"
    },
    "FrameWindow",
    "informViewOfPencilEnabled",
    "",
    "sendPixmapData",
    "QPixmap*",
    "p",
    "setDrawingColor",
    "newColor",
    "setBrushEnabled",
    "setEraserEnabled"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFrameWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    1 /* Public */,
       3,    1,   47,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   50,    2, 0x0a,    5 /* Public */,
       8,    0,   53,    2, 0x0a,    7 /* Public */,
       9,    0,   54,    2, 0x0a,    8 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QColor,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject FrameWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_CLASSFrameWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFrameWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFrameWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FrameWindow, std::true_type>,
        // method 'informViewOfPencilEnabled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'sendPixmapData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap *, std::false_type>,
        // method 'setDrawingColor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QColor &, std::false_type>,
        // method 'setBrushEnabled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setEraserEnabled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void FrameWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FrameWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->informViewOfPencilEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->sendPixmapData((*reinterpret_cast< std::add_pointer_t<QPixmap*>>(_a[1]))); break;
        case 2: _t->setDrawingColor((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 3: _t->setBrushEnabled(); break;
        case 4: _t->setEraserEnabled(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FrameWindow::*)(bool );
            if (_t _q_method = &FrameWindow::informViewOfPencilEnabled; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FrameWindow::*)(QPixmap * );
            if (_t _q_method = &FrameWindow::sendPixmapData; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *FrameWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FrameWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFrameWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int FrameWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void FrameWindow::informViewOfPencilEnabled(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FrameWindow::sendPixmapData(QPixmap * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
