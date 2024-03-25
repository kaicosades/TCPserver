#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionWave_viewer, &QAction::triggered, this, &MainWindow::showGraph);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about()
{
    AboutDialog* aboutDlg = new AboutDialog(this);
    aboutDlg->setModal(true);
    aboutDlg->show();
}

void MainWindow::showGraph()
{
    Plot* plot = new Plot(this); //this здесь это родительское окно
    plot->setWindowModality(Qt::WindowModality::ApplicationModal); // модальность
    plot->show();
}

