#ifndef TEXEDITOR_H
#define TEXEDITOR_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsScene>

typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;

constexpr ushort _DEFAULT = 65535;

struct TexColor {
    byte r = 0;
    byte g = 0;
    byte b = 0;
    byte a = 0;
};

struct TexFormat {
    char header[4] = {
        'T',
        'E',
        'X',
        '\x1',
    };
    byte reserved1[12] = {
        0x00,
        0x00,
        0x00,
        0x03,
        0x08,
        0x01,
        0x08,
        0x04,
        0x08,
        0x03,
        0x08,
        0x02
    };
    int reserved2 = 0;
    ushort shortWidth = _DEFAULT;
    ushort shortHeight = _DEFAULT;
    uint reserved3 = 0x01000100;
    uint width = _DEFAULT;
    uint height = _DEFAULT;
    byte reserved4[12] = {0x00};
    uint unknown1 = 0;
    TexColor* pixelData = nullptr;
};


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

    void SetImage(QPixmap pPix);

private:
    Ui::TexEditor *ui;
    TexFormat curTexture;
};


#endif // TEXEDITOR_H
