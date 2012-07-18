/****************************************************************************
** Meta object code from reading C++ file 'calendar.h'
**
** Created: Wed 18. Jul 07:49:37 2012
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
static const uint qt_meta_data_DetailedCalendar[] = {

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
      18,   17,   17,   17, 0x09,
      43,   32,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DetailedCalendar[] = {
    "DetailedCalendar\0\0select(QDate)\0"
    "year,month\0setCurrentPage(int,int)\0"
};

void DetailedCalendar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DetailedCalendar *_t = static_cast<DetailedCalendar *>(_o);
        switch (_id) {
        case 0: _t->select((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 1: _t->setCurrentPage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DetailedCalendar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DetailedCalendar::staticMetaObject = {
    { &QCalendarWidget::staticMetaObject, qt_meta_stringdata_DetailedCalendar,
      qt_meta_data_DetailedCalendar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DetailedCalendar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DetailedCalendar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DetailedCalendar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DetailedCalendar))
        return static_cast<void*>(const_cast< DetailedCalendar*>(this));
    return QCalendarWidget::qt_metacast(_clname);
}

int DetailedCalendar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
