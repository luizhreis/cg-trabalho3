#include <MainWindow.h>
#include <QPainter>
#include <Qt>
#include <CommandQueue.h>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    fila = new CommandQueue();
    centralpanel = new RenderPanel(fila, this);
    setCentralWidget(centralpanel);

    ui->toolBar->setVisible(false);

    connect(ui->centralwidget, SIGNAL(actionTriggered( QAction* )), this, SLOT(novoVertice(QAction*)));

    connect(ui->toolBar, SIGNAL(actionTriggered( QAction * )), this, SLOT(clicou(QAction*)));

    connect(ui->actionBondary, SIGNAL(toggled(bool)), this, SLOT(bondaryClick(bool)));

    connect(centralpanel, SIGNAL(atualizaMain()), this, SLOT(update()));

    setFixedSize(1024, 768);

    criarMenu();
}

void MainWindow::criarMenu(){
    menuBar()->addAction( ui->actionOpen_File );
    menuBar()->addSeparator();
    menuBar()->addAction( ui->actionVertice );
    menuBar()->addAction( ui->actionAresta );
    menuBar()->addAction( ui->actionFace );
    menuBar()->addSeparator();
    menuBar()->addAction( ui->actionAddVertice );
}

void MainWindow::clicou(QAction* a){
    if(a != ui->actionBondary)
        bondaryReset();

    if(a == ui->actionOpen_File){
        QString fn = QFileDialog::getOpenFileName(this, "Abrir Malha", "../..", "*.ply" );
        if(!fn.isEmpty())
            centralpanel->recebeArquivo(fn);
    }
    else if(a == ui->actionZoom_In){
        fila->produz(INCZOOM);
    }
    else if (a == ui->actionZoom_Out){
        fila->produz(DECZOOM);
    }
    else if (a == ui->actionUp){
        fila->produz(DECY);
    }
    else if (a == ui->actionLeft){
        fila->produz(DECX);
    }
    else if (a == ui->actionDown){
        fila->produz(INCY);
    }
    else if(a == ui->actionRight){
        fila->produz(INCX);
    }
    else if(a == ui->actionAddVertice){
        if(ui->actionAddVertice->isChecked()){
            //ui->actionAddVertice->setIcon(QIcon(":/verticesel"));
            ui->actionAddVertice->setChecked(true);
            ui->actionAddVertice->setStatusTip(tr("&Ativo"));
        }
        else{
            //ui->actionAddVertice->setIcon(QIcon(":/vertice"));
            ui->actionAddVertice->setChecked(false);
            ui->actionAddVertice->setStatusTip(tr("&Inativo"));
        }

        fila->produz(ADD);
    }
    else if(a == ui->actionVertice){
        if(ui->actionVertice->isChecked()){
            ui->actionVertice->setIcon(QIcon(":/verticesel"));
            ui->actionVertice->setChecked(true);
            ui->actionVertice->setStatusTip(tr("&Ativo"));
        }
        else{
            ui->actionVertice->setIcon(QIcon(":/vertice"));
            ui->actionVertice->setChecked(false);
            ui->actionVertice->setStatusTip(tr("&Inativo"));
        }
        fila->produz(PONTOS);
    }
    else if(a == ui->actionAresta){
        if(ui->actionAresta->isChecked()){
            ui->actionAresta->setIcon(QIcon(":/arestasel"));
            ui->actionAresta->setChecked(true);
        }
        else{
            ui->actionAresta->setIcon(QIcon(":/aresta"));
            ui->actionAresta->setChecked(false);
        }
        fila->produz(ARESTAS);
    }
    else if(a == ui->actionFace){
        if(ui->actionFace->isChecked()){
            ui->actionFace->setIcon(QIcon(":/facesel"));
            ui->actionFace->setChecked(true);
        }
        else{
            ui->actionFace->setIcon(QIcon(":/face"));
            ui->actionFace->setChecked(false);
        }
        fila->produz(FACES);
    }
    else if(a == ui->actionConvex_Hull){
        fila->produz(CONVHULL);
    }
}

void MainWindow::update(void){
	repaint();
}

void MainWindow::bondaryClick(bool value){
    ui->actionBondary->setIcon(QIcon(":/bond"));
    if(value)
        fila->produz(EXTERN);
}

void MainWindow::bondaryFeedBack(bool value){
    if(value)
        ui->actionBondary->setIcon(QIcon(":/true"));
    else
        ui->actionBondary->setIcon(QIcon(":/false"));
}

void MainWindow::bondaryReset(){
    ui->actionBondary->setIcon(QIcon(":/bond"));
    ui->actionBondary->setChecked(false);
}
