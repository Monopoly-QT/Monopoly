/****************************************************************************
** Meta object code from reading C++ file 'map.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../map.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'map.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3MapE_t {};
} // unnamed namespace

template <> constexpr inline auto Map::qt_create_metaobjectdata<qt_meta_tag_ZN3MapE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Map",
        "isDisplayChanged",
        "",
        "orderChanged",
        "nameChanged",
        "displayColorChanged",
        "playerStayChanged",
        "isDisplayBuildingChanged",
        "isDisplay",
        "order",
        "name",
        "displayColor",
        "playerStay",
        "QList<int>",
        "isDisplayBuilding"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'isDisplayChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'orderChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'nameChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'displayColorChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'playerStayChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'isDisplayBuildingChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'isDisplay'
        QtMocHelpers::PropertyData<bool>(8, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 0),
        // property 'order'
        QtMocHelpers::PropertyData<QString>(9, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 1),
        // property 'name'
        QtMocHelpers::PropertyData<QString>(10, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 2),
        // property 'displayColor'
        QtMocHelpers::PropertyData<QColor>(11, QMetaType::QColor, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 3),
        // property 'playerStay'
        QtMocHelpers::PropertyData<QList<int>>(12, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 4),
        // property 'isDisplayBuilding'
        QtMocHelpers::PropertyData<QList<int>>(14, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 5),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Map, qt_meta_tag_ZN3MapE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Map::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3MapE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3MapE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3MapE_t>.metaTypes,
    nullptr
} };

void Map::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Map *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->isDisplayChanged(); break;
        case 1: _t->orderChanged(); break;
        case 2: _t->nameChanged(); break;
        case 3: _t->displayColorChanged(); break;
        case 4: _t->playerStayChanged(); break;
        case 5: _t->isDisplayBuildingChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Map::*)()>(_a, &Map::isDisplayChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Map::*)()>(_a, &Map::orderChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Map::*)()>(_a, &Map::nameChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Map::*)()>(_a, &Map::displayColorChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Map::*)()>(_a, &Map::playerStayChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Map::*)()>(_a, &Map::isDisplayBuildingChanged, 5))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->isDisplay(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->order(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->name(); break;
        case 3: *reinterpret_cast<QColor*>(_v) = _t->displayColor(); break;
        case 4: *reinterpret_cast<QList<int>*>(_v) = _t->playerStay(); break;
        case 5: *reinterpret_cast<QList<int>*>(_v) = _t->isDisplayBuilding(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setIsDisplay(*reinterpret_cast<bool*>(_v)); break;
        case 1: _t->setOrder(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setName(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setDisplayColor(*reinterpret_cast<QColor*>(_v)); break;
        case 4: _t->setPlayerStay(*reinterpret_cast<QList<int>*>(_v)); break;
        case 5: _t->setIsDisplayBuilding(*reinterpret_cast<QList<int>*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Map::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Map::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3MapE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Map::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Map::isDisplayChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Map::orderChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Map::nameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Map::displayColorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Map::playerStayChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Map::isDisplayBuildingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
