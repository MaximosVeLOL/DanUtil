#ifndef ERROR_H
#define ERROR_H

#include <QtMultimedia/QSoundEffect>
#include <QMessageBox>
#include <QCoreApplication>
namespace Error {
    QSoundEffect* errorSound = nullptr;


    void Init() {
        errorSound = new QSoundEffect();
        errorSound->setSource(QUrl::fromLocalFile("resources/error.wav"));
    }

    void ShowMessage(QWidget* pParent, QString pMessage) {
        QMessageBox error(pParent);
        error.setText("An error has occured.");
        error.setInformativeText(pMessage);
        error.setStandardButtons(QMessageBox::Ok | QMessageBox::Abort);
        error.setDefaultButton(QMessageBox::Ok);
        errorSound->play();
        //I'm not gonna delete errorSound now because idk whats happening to it
        int ret = error.exec();
        if(ret == QMessageBox::Abort) {
            delete errorSound;
            QCoreApplication::quit();
        }
    }
}

#endif // ERROR_H
