/****************************************************************************
** Meta object code from reading C++ file 'basewidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../basewidget.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.0. It"
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
struct qt_meta_tag_ZN10BaseWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto BaseWidget::qt_create_metaobjectdata<qt_meta_tag_ZN10BaseWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "BaseWidget",
        "navigateToLogin",
        "",
        "navigateToAdmin",
        "navigateToUser",
        "navigateToCreditTable",
        "navigateToDepositTable",
        "navigateToCreditForm",
        "navigateToDepositForm",
        "navigateToSuccess"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'navigateToLogin'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'navigateToAdmin'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'navigateToUser'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'navigateToCreditTable'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'navigateToDepositTable'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'navigateToCreditForm'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'navigateToDepositForm'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'navigateToSuccess'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<BaseWidget, qt_meta_tag_ZN10BaseWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject BaseWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10BaseWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10BaseWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10BaseWidgetE_t>.metaTypes,
    nullptr
} };

void BaseWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BaseWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->navigateToLogin(); break;
        case 1: _t->navigateToAdmin(); break;
        case 2: _t->navigateToUser(); break;
        case 3: _t->navigateToCreditTable(); break;
        case 4: _t->navigateToDepositTable(); break;
        case 5: _t->navigateToCreditForm(); break;
        case 6: _t->navigateToDepositForm(); break;
        case 7: _t->navigateToSuccess(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (BaseWidget::*)()>(_a, &BaseWidget::navigateToLogin, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseWidget::*)()>(_a, &BaseWidget::navigateToAdmin, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseWidget::*)()>(_a, &BaseWidget::navigateToUser, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseWidget::*)()>(_a, &BaseWidget::navigateToCreditTable, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseWidget::*)()>(_a, &BaseWidget::navigateToDepositTable, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseWidget::*)()>(_a, &BaseWidget::navigateToCreditForm, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseWidget::*)()>(_a, &BaseWidget::navigateToDepositForm, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseWidget::*)()>(_a, &BaseWidget::navigateToSuccess, 7))
            return;
    }
}

const QMetaObject *BaseWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BaseWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10BaseWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int BaseWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void BaseWidget::navigateToLogin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BaseWidget::navigateToAdmin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void BaseWidget::navigateToUser()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void BaseWidget::navigateToCreditTable()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void BaseWidget::navigateToDepositTable()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void BaseWidget::navigateToCreditForm()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void BaseWidget::navigateToDepositForm()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void BaseWidget::navigateToSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
