/****************************************************************************
** Meta object code from reading C++ file 'new_file.h'
**
** Created: Tue 31. Jul 22:23:59 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../new_file.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'new_file.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewFile[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      42,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NewFile[] = {
    "NewFile\0\0createFileNameFromTitle(QString)\0"
    "clickedOk()\0"
};

void NewFile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NewFile *_t = static_cast<NewFile *>(_o);
        switch (_id) {
        case 0: _t->createFileNameFromTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->clickedOk(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NewFile::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NewFile::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewFile,
      qt_meta_data_NewFile, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewFile::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewFile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewFile))
        return static_cast<void*>(const_cast< NewFile*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE