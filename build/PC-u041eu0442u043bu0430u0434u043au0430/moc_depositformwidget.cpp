/****************************************************************************
** Meta object code from reading C++ file 'depositformwidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../depositformwidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'depositformwidget.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN17DepositFormWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto DepositFormWidget::qt_create_metaobjectdata<qt_meta_tag_ZN17DepositFormWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DepositFormWidget",
        "exportAnalyticsRequested",
        "",
        "navigateToUser",
        "navigateToSuccess",
        "depositDataReady",
        "fio",
        "phone",
        "issueDate",
        "days",
        "rateType",
        "rate",
        "period",
        "startSum",
        "endSum",
        "calculateEndSum",
        "onCreateDepositClicked",
        "onExportAnalyticsClicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'exportAnalyticsRequested'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'navigateToUser'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'navigateToSuccess'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'depositDataReady'
        QtMocHelpers::SignalData<void(const QString &, const QString &, QDate, int, int, double, int, double, double)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 }, { QMetaType::QString, 7 }, { QMetaType::QDate, 8 }, { QMetaType::Int, 9 },
            { QMetaType::Int, 10 }, { QMetaType::Double, 11 }, { QMetaType::Int, 12 }, { QMetaType::Double, 13 },
            { QMetaType::Double, 14 },
        }}),
        // Slot 'calculateEndSum'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCreateDepositClicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onExportAnalyticsClicked'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DepositFormWidget, qt_meta_tag_ZN17DepositFormWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DepositFormWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17DepositFormWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17DepositFormWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17DepositFormWidgetE_t>.metaTypes,
    nullptr
} };

void DepositFormWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DepositFormWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->exportAnalyticsRequested(); break;
        case 1: _t->navigateToUser(); break;
        case 2: _t->navigateToSuccess(); break;
        case 3: _t->depositDataReady((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QDate>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[6])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[7])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[8])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[9]))); break;
        case 4: _t->calculateEndSum(); break;
        case 5: _t->onCreateDepositClicked(); break;
        case 6: _t->onExportAnalyticsClicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DepositFormWidget::*)()>(_a, &DepositFormWidget::exportAnalyticsRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (DepositFormWidget::*)()>(_a, &DepositFormWidget::navigateToUser, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (DepositFormWidget::*)()>(_a, &DepositFormWidget::navigateToSuccess, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (DepositFormWidget::*)(const QString & , const QString & , QDate , int , int , double , int , double , double )>(_a, &DepositFormWidget::depositDataReady, 3))
            return;
    }
}

const QMetaObject *DepositFormWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DepositFormWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17DepositFormWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DepositFormWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void DepositFormWidget::exportAnalyticsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DepositFormWidget::navigateToUser()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DepositFormWidget::navigateToSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DepositFormWidget::depositDataReady(const QString & _t1, const QString & _t2, QDate _t3, int _t4, int _t5, double _t6, int _t7, double _t8, double _t9)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9);
}
QT_WARNING_POP
