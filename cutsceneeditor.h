#ifndef CUTSCENEEDITOR_H
#define CUTSCENEEDITOR_H

#include <QMainWindow>
#include <QUrl>

#include "danformats.h"

namespace Ui {
class CutsceneEditor;
}

class CutsceneEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit CutsceneEditor(QWidget *parent = nullptr);
    ~CutsceneEditor();

    QString rootDirectory;

private slots:
    void on_actionNew_triggered();

    void on_actionSet_Root_Directory_triggered();

    void on_actionOpen_triggered();

private:
    Ui::CutsceneEditor *ui;
};

#endif // CUTSCENEEDITOR_H
