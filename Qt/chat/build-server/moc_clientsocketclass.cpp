/****************************************************************************
** Meta object code from reading C++ file 'clientsocketclass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../server/clientsocketclass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientsocketclass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_clientSocketClass_t {
    QByteArrayData data[9];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_clientSocketClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_clientSocketClass_t qt_meta_stringdata_clientSocketClass = {
    {
QT_MOC_LITERAL(0, 0, 17), // "clientSocketClass"
QT_MOC_LITERAL(1, 18, 8), // "iGotData"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "char[99]"
QT_MOC_LITERAL(4, 37, 5), // "Array"
QT_MOC_LITERAL(5, 43, 15), // "iAmDisconnected"
QT_MOC_LITERAL(6, 59, 11), // "QTcpSocket*"
QT_MOC_LITERAL(7, 71, 15), // "receiveDataSlot"
QT_MOC_LITERAL(8, 87, 16) // "disconnectedSlot"

    },
    "clientSocketClass\0iGotData\0\0char[99]\0"
    "Array\0iAmDisconnected\0QTcpSocket*\0"
    "receiveDataSlot\0disconnectedSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_clientSocketClass[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   40,    2, 0x08 /* Private */,
       8,    0,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void clientSocketClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        clientSocketClass *_t = static_cast<clientSocketClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->iGotData((*reinterpret_cast< char(*)[99]>(_a[1]))); break;
        case 1: _t->iAmDisconnected((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 2: _t->receiveDataSlot(); break;
        case 3: _t->disconnectedSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (clientSocketClass::*_t)(char [99]);
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientSocketClass::iGotData)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (clientSocketClass::*_t)(QTcpSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientSocketClass::iAmDisconnected)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject clientSocketClass::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_clientSocketClass.data,
      qt_meta_data_clientSocketClass,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *clientSocketClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *clientSocketClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_clientSocketClass.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int clientSocketClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void clientSocketClass::iGotData(char _t1[99])
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void clientSocketClass::iAmDisconnected(QTcpSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
