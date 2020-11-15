/********************************************************************************
** Form generated from reading UI file 'mapviewpage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPVIEWPAGE_H
#define UI_MAPVIEWPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapViewPage
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *MapViewPage)
    {
        if (MapViewPage->objectName().isEmpty())
            MapViewPage->setObjectName(QString::fromUtf8("MapViewPage"));
        MapViewPage->resize(622, 422);
        MapViewPage->setToolTipDuration(0);
        widget = new QWidget(MapViewPage);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 601, 401));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(widget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        horizontalLayout->addWidget(graphicsView);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        retranslateUi(MapViewPage);
        QObject::connect(buttonBox, SIGNAL(accepted()), MapViewPage, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MapViewPage, SLOT(reject()));

        QMetaObject::connectSlotsByName(MapViewPage);
    } // setupUi

    void retranslateUi(QDialog *MapViewPage)
    {
        MapViewPage->setWindowTitle(QCoreApplication::translate("MapViewPage", "Tiled Map Viewer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MapViewPage: public Ui_MapViewPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPVIEWPAGE_H
