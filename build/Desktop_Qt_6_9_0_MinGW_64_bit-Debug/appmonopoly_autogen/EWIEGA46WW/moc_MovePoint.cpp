/****************************************************************************
** Meta object code from reading C++ file 'MovePoint.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../MovePoint.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MovePoint.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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
struct qt_meta_tag_ZN9MovePointE_t {};
} // unnamed namespace

template <> constexpr inline auto MovePoint::qt_create_metaobjectdata<qt_meta_tag_ZN9MovePointE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MovePoint",
        "isvisableChanged",
        "",
        "changeXChanged",
        "changeYChanged",
        "displayColorChanged",
        "hiddingMovePoint",
        "setIsvisable",
        "newIsvisable",
        "isvisable",
        "displayColor",
        "changeX",
        "changeY"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'isvisableChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'changeXChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'changeYChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'displayColorChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'hiddingMovePoint'
        QtMocHelpers::MethodData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setIsvisable'
        QtMocHelpers::MethodData<void(bool)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 8 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'isvisable'
        QtMocHelpers::PropertyData<bool>(9, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 0),
        // property 'displayColor'
        QtMocHelpers::PropertyData<QColor>(10, QMetaType::QColor, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 3),
        // property 'changeX'
        QtMocHelpers::PropertyData<double>(11, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 1),
        // property 'changeY'
        QtMocHelpers::PropertyData<double>(12, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 2),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MovePoint, qt_meta_tag_ZN9MovePointE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MovePoint::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9MovePointE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9MovePointE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9MovePointE_t>.metaTypes,
    nullptr
} };

void MovePoint::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MovePoint *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->isvisableChanged(); break;
        case 1: _t->changeXChanged(); break;
        case 2: _t->changeYChanged(); break;
        case 3: _t->displayColorChanged(); break;
        case 4: _t->hiddingMovePoint(); break;
        case 5: _t->setIsvisable((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MovePoint::*)()>(_a, &MovePoint::isvisableChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MovePoint::*)()>(_a, &MovePoint::changeXChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (MovePoint::*)()>(_a, &MovePoint::changeYChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (MovePoint::*)()>(_a, &MovePoint::displayColorChanged, 3))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->isvisable(); break;
        case 1: *reinterpret_cast<QColor*>(_v) = _t->displayColor(); break;
        case 2: *reinterpret_cast<double*>(_v) = _t->changeX(); break;
        case 3: *reinterpret_cast<double*>(_v) = _t->changeY(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setIsvisable(*reinterpret_cast<bool*>(_v)); break;
        case 1: _t->setDisplayColor(*reinterpret_cast<QColor*>(_v)); break;
        case 2: _t->setChangeX(*reinterpret_cast<double*>(_v)); break;
        case 3: _t->setChangeY(*reinterpret_cast<double*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *MovePoint::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MovePoint::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9MovePointE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MovePoint::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MovePoint::isvisableChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MovePoint::changeXChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MovePoint::changeYChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MovePoint::displayColorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
