#include "texeditor.h"
#include "ui_texeditor.h"

//#include "error.h"

#include <QFileDialog>

#include <QErrorMessage>

#include <QtEndian>

//For strcmp
//#include <string.h>

TexEditor::TexEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TexEditor)
{
    ui->setupUi(this);

    ui->sTexType->addItem("RGBA (Main Game, Default)");
    ui->sTexType->addItem("RGB (Backgrounds, UI)");
    //ui->sTexType->addItem("Unsupported 0x06 type (screen_)");
}

TexEditor::~TexEditor()
{
    delete ui;
}

const char* ImageTypeToString(Tex::ImageType& pType) {
    return (pType == Tex::ImageType::RGBOnly ? "RGB" : "RGBA");
}

void TexEditor::SetImage(QImage* pImg, QString& pFileName) {
    if(pImg->format() != QImage::Format_RGBA8888) pImg->convertTo(QImage::Format_RGBA8888);
    if(!ui->iViewer->scene()) {
        QGraphicsScene *scene = new QGraphicsScene(this);
        scene->addPixmap(QPixmap::fromImage(*pImg));
        //scene->setSceneRect({20, 20, 500, 500});
        ui->iViewer->setScene(scene);
        //return;
    }
    else {
        ui->iViewer->scene()->clear();
        ui->iViewer->scene()->addPixmap(QPixmap::fromImage(*pImg));
    }
    QString info = "Imported .tex\n(" + pFileName + ")\nSize: " + info.number(pImg->width()) + "x" + info.number(pImg->height()) + "\nImage Type: " + ImageTypeToString(curTexture.type);
    int index = (curTexture.type == Tex::TexRGBA ? 0x00 : Tex::RGBOnly);
    ui->iInfo->setText(info);
    ui->sTexType->setCurrentIndex(index);
    curImage = pImg;

}

void TexEditor::on_actionNew_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage *image = new QImage(fileName);
    if(image->isNull()) return;
    if(curImage) delete curImage;
    //curTexture = new Tex::Format();
    curTexture.shortWidth = (ushort)image->width();
    curTexture.shortHeight = (ushort)image->height();
    curTexture.width = image->width();
    curTexture.height = image->height();
    //TODO - Add support for 38 width
    switch (curTexture.width) {
    case 1: //Backgrounds
        curTexture.unknown1 = 2048;
        break;

    case 128:
        curTexture.unknown1 = 65536;
        break;

    case 512:
        curTexture.unknown1 = 1048576;
        break;

    case 1024:

        //outTex.unknown2 = 2097152;
        curTexture.unknown1 = 4194304;
        break;

    default:
        QErrorMessage e(this);
        e.showMessage("The imported texture is not a standard width!\nPlease change the image's width to the following:\n(1, 128, 512, 1024)");
        //Log("(Img -> Tex) Unknown width! (%d)", curTexture.width);
        //return 1;
        break;
    }
    //image->convertToFormat(QImage::Format_RGBA8888);
    image->convertTo(QImage::Format_RGBA8888);
    SetImage(image, fileName);
}



void TexEditor::on_actionOpen_triggered()
{  
    //d.setOption(QFileDialog::Option::DontUseNativeDialog);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/jana", tr("Texture Files (*.tex *.TEX)"));
    QFile file(fileName);
    //if(!file.isOpen()) //|| file.open(QFile::OpenModeFlag::ReadOnly))
    //    return;
    if(!file.open(QFile::ReadOnly) || !file.isOpen())
        return;
    if(curImage) delete curImage;

    file.read(curTexture.header, 4);
    if(curTexture.header[0] != 'T' || curTexture.header[1] != 'E' || curTexture.header[2] != 'X' || curTexture.header[3] != 0x01) {
        QString message = "(File parse error)\nHeader is invalid! (got \" ";
        message.append(curTexture.header);
        message.append("\" instead of \"TEX\")");
        QErrorMessage e(this);
        e.showMessage(message);
        //Error::ShowMessage(this, message);
        return;
    }
    file.read(reinterpret_cast<char*>(&curTexture.type), 4);
    if(curTexture.type != Tex::ImageType::RGBOnly && curTexture.type != Tex::ImageType::TexRGBA) {
        QErrorMessage e;
        QString m = "Unsupported (.tex) type! (got " + m.number((uint)curTexture.type) + ", excepted 0 or 50331648)";
        e.showMessage(m);
        curTexture = Tex::Format();
        file.close();
        return;
    }
    //curTexture.type = (ImageType)qToBigEndian<uint>((uint)curTexture.type);
    file.read((char*)curTexture.reserved1, 8);
    file.read(reinterpret_cast<char*>(&curTexture.reserved2), 4);
    file.read(reinterpret_cast<char*>(&curTexture.shortWidth), 2);
    file.read(reinterpret_cast<char*>(&curTexture.shortHeight), 2);

    file.read(reinterpret_cast<char*>(&curTexture.reserved3), 4);

    file.read(reinterpret_cast<char*>(&curTexture.width), 4);
    file.read(reinterpret_cast<char*>(&curTexture.height), 4);

    file.read((char*)curTexture.reserved4, 12);
    file.read(reinterpret_cast<char*>(&curTexture.unknown1), 4);
    unsigned int pixelAmount = curTexture.width * curTexture.height;
    if(file.pos() + pixelAmount > file.size()) {
        QErrorMessage e;
        e.showMessage("Image size is more than file size!");
        curTexture = Tex::Format();
    }

    if(curTexture.type == Tex::ImageType::TexRGBA) {
        curTexture.pixelData = new Tex::RGBA[pixelAmount];

        file.read(reinterpret_cast<char*>(curTexture.pixelData), pixelAmount * sizeof(Tex::RGBA));
        ui->sTexType->setCurrentIndex(0); // 0 - RGBA
    }
    else {
        //Convert RGB to RGBA cuz we can't support both
        //Don't use too much stack!
        Tex::RGB *data = new Tex::RGB[pixelAmount];

        file.read(reinterpret_cast<char*>(data), pixelAmount * sizeof(Tex::RGB));

        curTexture.pixelData = new Tex::RGBA[pixelAmount];
        for(unsigned int i = 0 ; i < pixelAmount;i++) {
            //Use operator of RGB -> RGBA
            curTexture.pixelData[i] = data[i];
            //TexRGB& cur = data[i];
            //curTexture.pixelData[i] = {cur.r, cur.g, cur.b, 0xFF};
        }
        ui->sTexType->setCurrentIndex(0); // 0 - RGB
        delete[] data;
    }
    file.close();

    //ui->progressBar->setValue(file.size());
    QImage* toAdd = new QImage((byte*)curTexture.pixelData, curTexture.width, curTexture.height, QImage::Format_RGBA8888);
    //QPixmap asPix = QPixmap::fromImage(toAdd);
    //QPixmap toAdd((char*)curTexture.pixelData);
    SetImage(toAdd, fileName);

    //TODO - Check if this causes errors
    //Yeah it does
    //delete[] curTexture.pixelData;
    //curTexture.pixelData = nullptr;
}


void TexEditor::on_actionSave_triggered()
{
    if(!curImage || curTexture.width == 0)
        return;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "/home/jana", tr("Texture Files (*.tex *.TEX)"));
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly) || !file.isOpen())
        return;

    QDataStream s(&file);

    s.writeRawData((const char*)&curTexture, 52); //Write the header
    //This should have a size of width * height * 4
    byte* pixelData = curImage->bits();
    switch(curTexture.type) {
    case Tex::ImageType::TexRGBA:
        s.writeRawData((const char*)pixelData, curTexture.width * curTexture.height * 4); //RGBA = 4
        break;

    case Tex::ImageType::RGBOnly: {
        //The image size is always the number of pixels
        Tex::RGBA* c = nullptr;
        for(unsigned int i = 0 ; i < curTexture.width * curTexture.height;i++) {
            c = reinterpret_cast<Tex::RGBA*>(pixelData + (i * 4));
            s.writeRawData((const char*)&c->r, 1);
            s.writeRawData((const char*)&c->g, 1);
            s.writeRawData((const char*)&c->b, 1);
        }
    }    break;
    case Tex::ImageType::Unknown:

        break;
    }
    file.close();
}


void TexEditor::on_actionSave_png_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open Image"), "/home/jana", tr("PNG Files (*.png);;BMP Files (*.bmp);;Any Format"));
    bool s = curImage->save(fileName);
    if(!s && fileName != "") {
        QErrorMessage e(this);
        e.showMessage("Failed to save image file!");
    }
}


void TexEditor::on_sTexType_activated(int index)
{
    constexpr Tex::ImageType indexToType[] = {
        Tex::ImageType::TexRGBA,
        Tex::ImageType::RGBOnly,
        //Tex::ImageType::Unknown,
    };
    curTexture.type = indexToType[index];
}

