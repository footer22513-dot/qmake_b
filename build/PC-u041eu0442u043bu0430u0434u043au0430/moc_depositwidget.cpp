/****************************************************************************
** Meta object code from reading C++ file 'depositwidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../depositwidget.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'depositwidget.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN18DepositTableWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto DepositTableWidget::qt_create_metaobjectdata<qt_meta_tag_ZN18DepositTableWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DepositTableWidget",
        "recordDeleted",
        "",
        "id",
        "recordUpdated",
        "DepositRecord",
        "record",
        "onSearchClicked",
        "onResetClicked",
        "onDeleteClicked",
        "onItemChanged",
        "QTableWidgetItem*",
        "item"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'recordDeleted'
        QtMocHelpers::SignalData<void(int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'recordUpdated'
        QtMocHelpers::SignalData<void(const DepositRecord &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Slot 'onSearchClicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onResetClicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDeleteClicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onItemChanged'
        QtMocHelpers::SlotData<void(QTableWidgetItem *)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DepositTableWidget, qt_meta_tag_ZN18DepositTableWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DepositTableWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18DepositTableWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18DepositTableWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN18DepositTableWidgetE_t>.metaTypes,
    nullptr
} };

void DepositTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DepositTableWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->recordDeleted((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->recordUpdated((*reinterpret_cast<std::add_pointer_t<DepositRecord>>(_a[1]))); break;
        case 2: _t->onSearchClicked(); break;
        case 3: _t->onResetClicked(); break;
        case 4: _t->onDeleteClicked(); break;
        case 5: _t->onItemChanged((*reinterpret_cast<std::add_pointer_t<QTableWidgetItem*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DepositTableWidget::*)(int )>(_a, &DepositTableWidget::recordDeleted, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (DepositTableWidget::*)(const DepositRecord & )>(_a, &DepositTableWidget::recordUpdated, 1))
            return;
    }
}

const QMetaObject *DepositTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DepositTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18DepositTableWidgetE_t>.strings))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int DepositTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWidget::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void DepositTableWidget::recordDeleted(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void DepositTableWidget::recordUpdated(const DepositRecord & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
QT_WARNING_POP
