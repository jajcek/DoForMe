/****************************************************************************
** Meta object code from reading C++ file 'calendar.h'
**
** Created: Fri 10. Aug 00:36:37 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../calendar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calendar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ActionsCalendar[] = {

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
      17,   16,   16,   16, 0x09,
      46,   35,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ActionsCalendar[] = {
    "ActionsCalendar\0\0selectDate(QDate)\0"
    "year,month\0setCurrentPage(int,int)\0"
};

void ActionsCalendar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ActionsCalendar *_t = static_cast<ActionsCalendar *>(_o);
        switch (_id) {
        case 0: _t->selectDate((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 1: _t->setCurrentPage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ActionsCalendar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ActionsCalendar::staticMetaObject = {
    { &QCalendarWidget::staticMetaObject, qt_meta_stringdata_ActionsCalendar,
      qt_meta_data_ActionsCalendar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ActionsCalendar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ActionsCalendar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ActionsCalendar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ActionsCalendar))
        return static_cast<void*>(const_cast< ActionsCalendar*>(this));
    return QCalendarWidget::qt_metacast(_clname);
}

int ActionsCalendar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCalendarWidget::qt_metacall(_c, _id, _a);
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
