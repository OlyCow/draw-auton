#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QMainWindow>

namespace Ui {
class DrawWindow;
}

class DrawWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrawWindow(QWidget *parent = 0);
    ~DrawWindow();

private:
    Ui::DrawWindow *ui;
};

#endif // DRAWWINDOW_H
