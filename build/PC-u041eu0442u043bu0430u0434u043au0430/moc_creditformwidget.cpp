/****************************************************************************
** Meta object code from reading C++ file 'creditformwidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../creditformwidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'creditformwidget.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN16CreditFormWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto CreditFormWidget::qt_create_metaobjectdata<qt_meta_tag_ZN16CreditFormWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CreditFormWidget",
        "navigateToUser",
        "",
        "navigateToSuccess",
        "creditDataReady",
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
        "penaltyAmount",
        "penaltyPercent",
        "creditType",
        "calculateEndSum",
        "onCreateCreditClicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'navigateToUser'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'navigateToSuccess'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'creditDataReady'
        QtMocHelpers::SignalData<void(const QString &, const QString &, QDate, int, int, double, int, double, double, bool, double, double, int)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 }, { QMetaType::QString, 6 }, { QMetaType::QDate, 7 }, { QMetaType::Int, 8 },
            { QMetaType::Int, 9 }, { QMetaType::Double, 10 }, { QMetaType::Int, 11 }, { QMetaType::Double, 12 },
            { QMetaType::Double, 13 }, { QMetaType::Bool, 14 }, { QMetaType::Double, 15 }, { QMetaType::Double, 16 },
            { QMetaType::Int, 17 },
        }}),
        // Slot 'calculateEndSum'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCreateCreditClicked'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CreditFormWidget, qt_meta_tag_ZN16CreditFormWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CreditFormWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16CreditFormWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16CreditFormWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16CreditFormWidgetE_t>.metaTypes,
    nullptr
} };

void CreditFormWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CreditFormWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->navigateToUser(); break;
        case 1: _t->navigateToSuccess(); break;
        case 2: _t->creditDataReady((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QDate>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[6])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[7])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[8])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[9])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[10])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[11])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[12])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[13]))); break;
        case 3: _t->calculateEndSum(); break;
        case 4: _t->onCreateCreditClicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CreditFormWidget::*)()>(_a, &CreditFormWidget::navigateToUser, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (CreditFormWidget::*)()>(_a, &CreditFormWidget::navigateToSuccess, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (CreditFormWidget::*)(const QString & , const QString & , QDate , int , int , double , int , double , double , bool , double , double , int )>(_a, &CreditFormWidget::creditDataReady, 2))
            return;
    }
}

const QMetaObject *CreditFormWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreditFormWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16CreditFormWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CreditFormWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CreditFormWidget::navigateToUser()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CreditFormWidget::navigateToSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CreditFormWidget::creditDataReady(const QString & _t1, const QString & _t2, QDate _t3, int _t4, int _t5, double _t6, int _t7, double _t8, double _t9, bool _t10, double _t11, double _t12, int _t13)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9, _t10, _t11, _t12, _t13);
}
QT_WARNING_POP
