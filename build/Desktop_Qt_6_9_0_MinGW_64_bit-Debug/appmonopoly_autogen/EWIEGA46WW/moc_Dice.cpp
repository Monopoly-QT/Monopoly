/****************************************************************************
** Meta object code from reading C++ file 'Dice.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Dice.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Dice.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN4DiceE_t {};
} // unnamed namespace

template <> constexpr inline auto Dice::qt_create_metaobjectdata<qt_meta_tag_ZN4DiceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Dice",
        "DiceAShowChanged",
        "",
        "DiceBShowChanged",
        "DiceCShowChanged",
        "DiceDShowChanged",
        "DiceEShowChanged",
        "DiceFShowChanged",
        "DiceGShowChanged",
        "pointColorChanged",
        "dicePointChanged",
        "rollDice",
        "seed",
        "DiceAShow",
        "DiceBShow",
        "DiceCShow",
        "DiceDShow",
        "DiceEShow",
        "DiceFShow",
        "DiceGShow",
        "pointColor",
        "dicePoint"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'DiceAShowChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'DiceBShowChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'DiceCShowChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'DiceDShowChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'DiceEShowChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'DiceFShowChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'DiceGShowChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'pointColorChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'dicePointChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'rollDice'
        QtMocHelpers::MethodData<void(int)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'DiceAShow'
        QtMocHelpers::PropertyData<bool>(13, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 0),
        // property 'DiceBShow'
        QtMocHelpers::PropertyData<bool>(14, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 1),
        // property 'DiceCShow'
        QtMocHelpers::PropertyData<bool>(15, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 2),
        // property 'DiceDShow'
        QtMocHelpers::PropertyData<bool>(16, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 3),
        // property 'DiceEShow'
        QtMocHelpers::PropertyData<bool>(17, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 4),
        // property 'DiceFShow'
        QtMocHelpers::PropertyData<bool>(18, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 5),
        // property 'DiceGShow'
        QtMocHelpers::PropertyData<bool>(19, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 6),
        // property 'pointColor'
        QtMocHelpers::PropertyData<QColor>(20, QMetaType::QColor, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 7),
        // property 'dicePoint'
        QtMocHelpers::PropertyData<int>(21, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Final, 8),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Dice, qt_meta_tag_ZN4DiceE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Dice::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4DiceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4DiceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN4DiceE_t>.metaTypes,
    nullptr
} };

void Dice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Dice *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->DiceAShowChanged(); break;
        case 1: _t->DiceBShowChanged(); break;
        case 2: _t->DiceCShowChanged(); break;
        case 3: _t->DiceDShowChanged(); break;
        case 4: _t->DiceEShowChanged(); break;
        case 5: _t->DiceFShowChanged(); break;
        case 6: _t->DiceGShowChanged(); break;
        case 7: _t->pointColorChanged(); break;
        case 8: _t->dicePointChanged(); break;
        case 9: _t->rollDice((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Dice::*)()>(_a, &Dice::DiceAShowChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Dice::*)()>(_a, &Dice::DiceBShowChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Dice::*)()>(_a, &Dice::DiceCShowChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Dice::*)()>(_a, &Dice::DiceDShowChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Dice::*)()>(_a, &Dice::DiceEShowChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Dice::*)()>(_a, &Dice::DiceFShowChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Dice::*)()>(_a, &Dice::DiceGShowChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (Dice::*)()>(_a, &Dice::pointColorChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (Dice::*)()>(_a, &Dice::dicePointChanged, 8))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->DiceAShow(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->DiceBShow(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->DiceCShow(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->DiceDShow(); break;
        case 4: *reinterpret_cast<bool*>(_v) = _t->DiceEShow(); break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->DiceFShow(); break;
        case 6: *reinterpret_cast<bool*>(_v) = _t->DiceGShow(); break;
        case 7: *reinterpret_cast<QColor*>(_v) = _t->pointColor(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->dicePoint(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 7: _t->setPointColor(*reinterpret_cast<QColor*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Dice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dice::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4DiceE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Dice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Dice::DiceAShowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Dice::DiceBShowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Dice::DiceCShowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Dice::DiceDShowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Dice::DiceEShowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Dice::DiceFShowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Dice::DiceGShowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Dice::pointColorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Dice::dicePointChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
