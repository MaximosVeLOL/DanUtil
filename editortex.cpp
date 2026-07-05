#include "editortex.h"
#include "ui_editortex.h"

EditorTex::EditorTex(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditorTex)
{
    ui->setupUi(this);
}

EditorTex::~EditorTex()
{
    delete ui;
}
