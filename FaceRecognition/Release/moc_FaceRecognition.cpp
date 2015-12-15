/****************************************************************************
** Meta object code from reading C++ file 'FaceRecognition.h'
**
** Created: Tue 6. Jul 22:34:12 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FaceRecognition.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FaceRecognition.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FaceRecognition[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,   16,   16,   16, 0x0a,
      41,   16,   16,   16, 0x0a,
      55,   16,   16,   16, 0x0a,
      69,   16,   16,   16, 0x0a,
      79,   16,   16,   16, 0x0a,
      92,   16,   16,   16, 0x0a,
     100,   16,   16,   16, 0x0a,
     109,   16,   16,   16, 0x0a,
     129,   16,   16,   16, 0x0a,
     139,   16,   16,   16, 0x0a,
     150,   16,   16,   16, 0x0a,
     169,   16,   16,   16, 0x0a,
     182,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FaceRecognition[] = {
    "FaceRecognition\0\0doubleclick()\0Capture()\0"
    "InitCapture()\0StopCapture()\0AddUser()\0"
    "DeleteUser()\0LogOn()\0LogOut()\0"
    "Recognition_Ok(int)\0User_On()\0User_Out()\0"
    "Authentification()\0UpdateUser()\0Start()\0"
};

const QMetaObject FaceRecognition::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FaceRecognition,
      qt_meta_data_FaceRecognition, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FaceRecognition::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FaceRecognition::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FaceRecognition::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FaceRecognition))
        return static_cast<void*>(const_cast< FaceRecognition*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FaceRecognition::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: doubleclick(); break;
        case 1: Capture(); break;
        case 2: InitCapture(); break;
        case 3: StopCapture(); break;
        case 4: AddUser(); break;
        case 5: DeleteUser(); break;
        case 6: LogOn(); break;
        case 7: LogOut(); break;
        case 8: Recognition_Ok((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: User_On(); break;
        case 10: User_Out(); break;
        case 11: Authentification(); break;
        case 12: UpdateUser(); break;
        case 13: Start(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void FaceRecognition::doubleclick()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
