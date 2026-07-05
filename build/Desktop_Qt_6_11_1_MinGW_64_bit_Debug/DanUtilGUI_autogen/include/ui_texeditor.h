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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TexEditor
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QWidget *centralwidget;
    QGraphicsView *iViewer;
    QFrame *frame;
    QLabel *iInfo;
    QProgressBar *progressBar;
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
        centralwidget = new QWidget(TexEditor);
        centralwidget->setObjectName("centralwidget");
        iViewer = new QGraphicsView(centralwidget);
        iViewer->setObjectName("iViewer");
        iViewer->setGeometry(QRect(445, 10, 341, 341));
        iViewer->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        iViewer->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(449, 360, 331, 131));
        frame->setAutoFillBackground(true);
        frame->setFrameShape(QFrame::Shape::WinPanel);
        frame->setFrameShadow(QFrame::Shadow::Sunken);
        iInfo = new QLabel(frame);
        iInfo->setObjectName("iInfo");
        iInfo->setGeometry(QRect(10, 10, 311, 111));
        iInfo->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setEnabled(true);
        progressBar->setGeometry(QRect(457, 530, 321, 23));
        progressBar->setValue(0);
        progressBar->setTextVisible(true);
        progressBar->setInvertedAppearance(false);
        progressBar->setTextDirection(QProgressBar::Direction::TopToBottom);
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
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);

        retranslateUi(TexEditor);

        QMetaObject::connectSlotsByName(TexEditor);
    } // setupUi

    void retranslateUi(QMainWindow *TexEditor)
    {
        TexEditor->setWindowTitle(QCoreApplication::translate("TexEditor", "MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("TexEditor", "New", nullptr));
#if QT_CONFIG(tooltip)
        actionNew->setToolTip(QCoreApplication::translate("TexEditor", "New (From Image)", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOpen->setText(QCoreApplication::translate("TexEditor", "Open", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("TexEditor", "Open (.tex)", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSave->setText(QCoreApplication::translate("TexEditor", "Save", nullptr));
        iInfo->setText(QCoreApplication::translate("TexEditor", ".tex information here", nullptr));
        menuFile->setTitle(QCoreApplication::translate("TexEditor", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TexEditor: public Ui_TexEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXEDITOR_H
