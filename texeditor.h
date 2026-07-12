#ifndef TEXEDITOR_H
#define TEXEDITOR_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsScene>

#include "danformats.h"


namespace Ui {
class TexEditor;
}

class TexEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit TexEditor(QWidget *parent = nullptr);
    ~TexEditor();

private slots:

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void SetImage(QImage* pImg, QString& pFileName);

    void on_actionSave_triggered();

    void on_actionSave_png_triggered();

    void on_sTexType_activated(int index);

private:
    //Holds the image data
    QImage *curImage = nullptr;
    Ui::TexEditor *ui = nullptr;
    //Holds .tex data, and no pixel data
    Tex::Format curTexture = Tex::Format();
};


#endif // TEXEDITOR_H
