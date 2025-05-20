/****************************************************************************
** Meta object code from reading C++ file 'UseCardSetting.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../UseCardSetting.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UseCardSetting.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14UseCardSettingE_t {};
} // unnamed namespace

template <> constexpr inline auto UseCardSetting::qt_create_metaobjectdata<qt_meta_tag_ZN14UseCardSettingE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "UseCardSetting",
        "displayTargetPlayerChanged",
        "",
        "displayTargetLandChanged",
        "cardUseAvailableChanged",
        "ownCardCountChanged",
        "displayTargetPlayer",
        "QList<int>",
        "displayTargetLand",
        "cardUseAvailable",
        "ownCardCount"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'displayTargetPlayerChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'displayTargetLandChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'cardUseAvailableChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'ownCardCountChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'displayTargetPlayer'
        QtMocHelpers::PropertyData<QList<int>>(6, 0x80000000 | 7, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 0),
        // property 'displayTargetLand'
        QtMocHelpers::PropertyData<QList<QString>>(8, QMetaType::QStringList, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 1),
        // property 'cardUseAvailable'
        QtMocHelpers::PropertyData<QList<int>>(9, 0x80000000 | 7, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 2),
        // property 'ownCardCount'
        QtMocHelpers::PropertyData<QList<int>>(10, 0x80000000 | 7, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 3),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<UseCardSetting, qt_meta_tag_ZN14UseCardSettingE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject UseCardSetting::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14UseCardSettingE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14UseCardSettingE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14UseCardSettingE_t>.metaTypes,
    nullptr
} };

void UseCardSetting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<UseCardSetting *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->displayTargetPlayerChanged(); break;
        case 1: _t->displayTargetLandChanged(); break;
        case 2: _t->cardUseAvailableChanged(); break;
        case 3: _t->ownCardCountChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (UseCardSetting::*)()>(_a, &UseCardSetting::displayTargetPlayerChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (UseCardSetting::*)()>(_a, &UseCardSetting::displayTargetLandChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (UseCardSetting::*)()>(_a, &UseCardSetting::cardUseAvailableChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (UseCardSetting::*)()>(_a, &UseCardSetting::ownCardCountChanged, 3))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
        case 2:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<int>*>(_v) = _t->displayTargetPlayer(); break;
        case 1: *reinterpret_cast<QList<QString>*>(_v) = _t->displayTargetLand(); break;
        case 2: *reinterpret_cast<QList<int>*>(_v) = _t->cardUseAvailable(); break;
        case 3: *reinterpret_cast<QList<int>*>(_v) = _t->ownCardCount(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDisplayTargetPlayer(*reinterpret_cast<QList<int>*>(_v)); break;
        case 1: _t->setDisplayTargetLand(*reinterpret_cast<QList<QString>*>(_v)); break;
        case 2: _t->setCardUseAvailable(*reinterpret_cast<QList<int>*>(_v)); break;
        case 3: _t->setOwnCardCount(*reinterpret_cast<QList<int>*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *UseCardSetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UseCardSetting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14UseCardSettingE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UseCardSetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
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
void UseCardSetting::displayTargetPlayerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void UseCardSetting::displayTargetLandChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void UseCardSetting::cardUseAvailableChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void UseCardSetting::ownCardCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
