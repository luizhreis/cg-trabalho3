#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMenu>
#include <RenderPanel.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
   
public slots:
    void update(void);
    void clicou(QAction* a);
    void bondaryClick(bool value);

public:
    QMenu *mnuZoon;
    MainWindow(QWidget* parent = 0);

    void bondaryFeedBack(bool value);
    void bondaryReset();
    
private:
   CommandQueue *fila;
   RenderPanel* centralpanel;

    Ui::MainWindow *ui;

    void criarMenu();
};


#endif
