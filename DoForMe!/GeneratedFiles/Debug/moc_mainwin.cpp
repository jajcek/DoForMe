/****************************************************************************
** Meta object code from reading C++ file 'mainwin.h'
**
** Created: Thu 2. Aug 22:31:32 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mainWin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      19,    8,    8,    8, 0x0a,
      31,    8,    8,    8, 0x0a,
      44,    8,    8,    8, 0x0a,
      69,   57,    8,    8, 0x0a,
      93,    8,    8,    8, 0x0a,
     110,    8,    8,    8, 0x0a,
     122,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_mainWin[] = {
    "mainWin\0\0newFile()\0runAction()\0"
    "saveScript()\0saveAction()\0scriptTitle\0"
    "scriptSelected(QString)\0scriptModified()\0"
    "addAction()\0showAbout()\0"
};

void mainWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        mainWin *_t = static_cast<mainWin *>(_o);
        switch (_id) {
        case 0: _t->newFile(); break;
        case 1: _t->runAction(); break;
        case 2: _t->saveScript(); break;
        case 3: _t->saveAction(); break;
        case 4: _t->scriptSelected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->scriptModified(); break;
        case 6: _t->addAction(); break;
        case 7: _t->showAbout(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData mainWin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject mainWin::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_mainWin,
      qt_meta_data_mainWin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mainWin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mainWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mainWin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mainWin))
        return static_cast<void*>(const_cast< mainWin*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int mainWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
