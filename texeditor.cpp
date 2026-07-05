#include "texeditor.h"
#include "ui_texeditor.h"

//#include "error.h"

#include <QFileDialog>

#include <QtMultimedia/QSoundEffect>

//For strcmp
#include <string.h>

TexEditor::TexEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TexEditor)
{
    ui->setupUi(this);
}

TexEditor::~TexEditor()
{
    delete ui;
}

void TexEditor::SetImage(QPixmap pPix) {
    if(!ui->iViewer->scene()) {
        QGraphicsScene *scene = new QGraphicsScene(this);
        scene->addPixmap(pPix);
        //scene->setSceneRect({20, 20, 500, 500});
        ui->iViewer->setScene(scene);
        return;
    }
    ui->iViewer->scene()->clear();
    ui->iViewer->scene()->addPixmap(pPix);


}

void TexEditor::on_actionNew_triggered()
{
    QString filename;
    QFileDialog d;
    d.setOption(QFileDialog::DontUseNativeDialog);
    d.setFileMode(QFileDialog::FileMode::ExistingFile);
    d.setNameFilter("Image Files (*.png *.bmp)");
    if(!d.exec()) return;
    d.selectFile(filename);

    QPixmap image(filename);

    //curTexture = new TexFormat();
    curTexture.shortWidth = (ushort)image.width();
    curTexture.shortHeight = (ushort)image.height();
    curTexture.width = image.width();
    curTexture.height = image.height();
    SetImage(image);
}


void TexEditor::on_actionOpen_triggered()
{
    //d.setOption(QFileDialog::Option::DontUseNativeDialog);

    QFile file(QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)")));
    //if(!file.isOpen()) //|| file.open(QFile::OpenModeFlag::ReadOnly))
    //    return;

    ui->progressBar->setValue(0);


    file.read(curTexture.header, 4);
    if(strcmp(curTexture.header, "TEX") != 0) {
        QString message = "(File parse error)\nHeader is invalid! (got \" ";
        message.append(curTexture.header);
        message.append("\" instead of \"TEX\")");
        //Error::ShowMessage(this, message);
        return;
    }
    ui->progressBar->setMaximum(file.size());

    file.read((char*)curTexture.reserved1, 12);
    file.read(reinterpret_cast<char*>(&curTexture.reserved2), 4);

    file.read(reinterpret_cast<char*>(&curTexture.shortWidth), 2);
    file.read(reinterpret_cast<char*>(&curTexture.shortHeight), 2);

    file.read(reinterpret_cast<char*>(&curTexture.reserved3), 4);

    file.read(reinterpret_cast<char*>(&curTexture.width), 4);
    file.read(reinterpret_cast<char*>(&curTexture.height), 4);

    file.read((char*)curTexture.reserved4, 12);
    file.read(reinterpret_cast<char*>(&curTexture.unknown1), 4);
    unsigned int pixelAmount = curTexture.width * curTexture.height;

    curTexture.pixelData = new TexColor[pixelAmount];

    file.read(reinterpret_cast<char*>(curTexture.pixelData), pixelAmount * sizeof(TexColor));

    file.close();

    ui->progressBar->setValue(file.size());
    QPixmap toAdd((char*)curTexture.pixelData);
    SetImage(toAdd);
}

