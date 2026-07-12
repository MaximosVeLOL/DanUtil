#include "cutsceneeditor.h"
#include "ui_cutsceneeditor.h"

#include <QFileDialog>
#include <QXmlStreamReader>

CutsceneEditor::CutsceneEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CutsceneEditor)
{
    ui->setupUi(this);
}

CutsceneEditor::~CutsceneEditor()
{
    delete ui;
}

void CutsceneEditor::on_actionNew_triggered()
{

}


void CutsceneEditor::on_actionSet_Root_Directory_triggered()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(dir == "") return;
    rootDirectory = dir;
}


void CutsceneEditor::on_actionOpen_triggered() {
    QString fileDir = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/jana", tr("XML Files (*.xml *.XML)"));
    QFile f(fileDir);
    if(!f.open(QFile::ReadOnly | QFile::Text)) return;
    QXmlStreamReader r(&f);


}

