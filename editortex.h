#ifndef EDITORTEX_H
#define EDITORTEX_H

#include <QDialog>

namespace Ui {
class EditorTex;
}

class EditorTex : public QDialog
{
    Q_OBJECT

public:
    explicit EditorTex(QWidget *parent = nullptr);
    ~EditorTex();

private:
    Ui::EditorTex *ui;
};

#endif // EDITORTEX_H
