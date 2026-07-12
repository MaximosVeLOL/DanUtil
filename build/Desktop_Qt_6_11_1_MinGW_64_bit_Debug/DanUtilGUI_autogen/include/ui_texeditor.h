/********************************************************************************
** Form generated from reading UI file 'texeditor.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXEDITOR_H
#define UI_TEXEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TexEditor
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_png;
    QWidget *centralwidget;
    QGraphicsView *iViewer;
    QFrame *frame;
    QLabel *iInfo;
    QFrame *frame_2;
    QComboBox *sTexType;
    QLabel *sLabel1;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TexEditor)
    {
        if (TexEditor->objectName().isEmpty())
            TexEditor->setObjectName("TexEditor");
        TexEditor->resize(800, 600);
        actionNew = new QAction(TexEditor);
        actionNew->setObjectName("actionNew");
        actionOpen = new QAction(TexEditor);
        actionOpen->setObjectName("actionOpen");
        actionSave = new QAction(TexEditor);
        actionSave->setObjectName("actionSave");
        actionSave_png = new QAction(TexEditor);
        actionSave_png->setObjectName("actionSave_png");
        centralwidget = new QWidget(TexEditor);
        centralwidget->setObjectName("centralwidget");
        iViewer = new QGraphicsView(centralwidget);
        iViewer->setObjectName("iViewer");
        iViewer->setGeometry(QRect(10, 20, 512, 512));
        iViewer->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        iViewer->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(530, 10, 261, 391));
        frame->setAutoFillBackground(true);
        frame->setFrameShape(QFrame::Shape::WinPanel);
        frame->setFrameShadow(QFrame::Shadow::Sunken);
        iInfo = new QLabel(frame);
        iInfo->setObjectName("iInfo");
        iInfo->setGeometry(QRect(10, 10, 481, 501));
        iInfo->setFrameShape(QFrame::Shape::NoFrame);
        iInfo->setFrameShadow(QFrame::Shadow::Plain);
        iInfo->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(530, 410, 261, 121));
        frame_2->setFrameShape(QFrame::Shape::WinPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Sunken);
        frame_2->setLineWidth(1);
        sTexType = new QComboBox(frame_2);
        sTexType->setObjectName("sTexType");
        sTexType->setGeometry(QRect(71, 10, 181, 22));
        sTexType->setEditable(false);
        sLabel1 = new QLabel(frame_2);
        sLabel1->setObjectName("sLabel1");
        sLabel1->setGeometry(QRect(10, 10, 49, 21));
        TexEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TexEditor);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        TexEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(TexEditor);
        statusbar->setObjectName("statusbar");
        TexEditor->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionSave_png);
        menuFile->addSeparator();
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);

        retranslateUi(TexEditor);

        QMetaObject::connectSlotsByName(TexEditor);
    } // setupUi

    void retranslateUi(QMainWindow *TexEditor)
    {
        TexEditor->setWindowTitle(QCoreApplication::translate("TexEditor", "Texture Editor", nullptr));
        actionNew->setText(QCoreApplication::translate("TexEditor", "New (From Image)", nullptr));
#if QT_CONFIG(tooltip)
        actionNew->setToolTip(QCoreApplication::translate("TexEditor", "New (From Image)", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOpen->setText(QCoreApplication::translate("TexEditor", "Open (.tex)", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("TexEditor", "Open (.tex)", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSave->setText(QCoreApplication::translate("TexEditor", "Save (.tex)", nullptr));
        actionSave_png->setText(QCoreApplication::translate("TexEditor", "Save (image)", nullptr));
        iInfo->setText(QCoreApplication::translate("TexEditor", ".tex Information Goes Here", nullptr));
        sTexType->setCurrentText(QString());
        sLabel1->setText(QCoreApplication::translate("TexEditor", "Tex Type", nullptr));
        menuFile->setTitle(QCoreApplication::translate("TexEditor", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TexEditor: public Ui_TexEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXEDITOR_H
