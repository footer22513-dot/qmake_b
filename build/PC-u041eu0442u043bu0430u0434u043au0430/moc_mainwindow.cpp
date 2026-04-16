/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "goLogin",
        "",
        "goAdmin",
        "goUser",
        "goCreditTable",
        "goDepositTable",
        "goCreditForm",
        "goDepositForm",
        "goSuccess",
        "onCreditReady",
        "fio",
        "phone",
        "issueDate",
        "days",
        "rateType",
        "rate",
        "period",
        "startSum",
        "endSum",
        "earlyRepay",
        "onDepositReady",
        "onCreditDeleted",
        "id",
        "onDepositDeleted",
        "onCreditUpdated",
        "CreditRecord",
        "rec",
        "onDepositUpdated",
        "DepositRecord",
        "onLoadDb",
        "onSaveDb"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'goLogin'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'goAdmin'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'goUser'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'goCreditTable'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'goDepositTable'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'goCreditForm'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'goDepositForm'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'goSuccess'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCreditReady'
        QtMocHelpers::SlotData<void(const QString &, const QString &, QDate, int, int, double, int, double, double, bool)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 11 }, { QMetaType::QString, 12 }, { QMetaType::QDate, 13 }, { QMetaType::Int, 14 },
            { QMetaType::Int, 15 }, { QMetaType::Double, 16 }, { QMetaType::Int, 17 }, { QMetaType::Double, 18 },
            { QMetaType::Double, 19 }, { QMetaType::Bool, 20 },
        }}),
        // Slot 'onDepositReady'
        QtMocHelpers::SlotData<void(const QString &, const QString &, QDate, int, int, double, int, double, double)>(21, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 11 }, { QMetaType::QString, 12 }, { QMetaType::QDate, 13 }, { QMetaType::Int, 14 },
            { QMetaType::Int, 15 }, { QMetaType::Double, 16 }, { QMetaType::Int, 17 }, { QMetaType::Double, 18 },
            { QMetaType::Double, 19 },
        }}),
        // Slot 'onCreditDeleted'
        QtMocHelpers::SlotData<void(int)>(22, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 23 },
        }}),
        // Slot 'onDepositDeleted'
        QtMocHelpers::SlotData<void(int)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 23 },
        }}),
        // Slot 'onCreditUpdated'
        QtMocHelpers::SlotData<void(const CreditRecord &)>(25, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 26, 27 },
        }}),
        // Slot 'onDepositUpdated'
        QtMocHelpers::SlotData<void(const DepositRecord &)>(28, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 29, 27 },
        }}),
        // Slot 'onLoadDb'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSaveDb'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->goLogin(); break;
        case 1: _t->goAdmin(); break;
        case 2: _t->goUser(); break;
        case 3: _t->goCreditTable(); break;
        case 4: _t->goDepositTable(); break;
        case 5: _t->goCreditForm(); break;
        case 6: _t->goDepositForm(); break;
        case 7: _t->goSuccess(); break;
        case 8: _t->onCreditReady((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QDate>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[6])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[7])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[8])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[9])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[10]))); break;
        case 9: _t->onDepositReady((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QDate>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[6])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[7])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[8])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[9]))); break;
        case 10: _t->onCreditDeleted((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->onDepositDeleted((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->onCreditUpdated((*reinterpret_cast<std::add_pointer_t<CreditRecord>>(_a[1]))); break;
        case 13: _t->onDepositUpdated((*reinterpret_cast<std::add_pointer_t<DepositRecord>>(_a[1]))); break;
        case 14: _t->onLoadDb(); break;
        case 15: _t->onSaveDb(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
