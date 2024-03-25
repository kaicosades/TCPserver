#include "plot.h"
#include "ui_plot.h"

Plot::Plot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Plot)
{
    ui->setupUi(this);

    //задать размеры для координат
    ui->customPlot->addGraph();
    ui->customPlot->xAxis->setRange(0, 4500);
    ui->customPlot->yAxis->setRange(-500, 4500);

    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 10002);
    connect(socket, SIGNAL(readyRead()), this, SLOT(loadDataToPlot()));

}

Plot::~Plot()
{
    delete socket;
    delete ui;
}

void Plot::resizeEvent(QResizeEvent *e) // событие для сохранения пропорций wave viewer
{
    QMainWindow::resizeEvent(e);
    ui->customPlot->resize(QSize(this->geometry().width()-10, this->geometry().height()-30)); // -10 и -30 это кол-во пикселей, которое не занимает окно
    //для того, чтобы не использовать событие нужно выбрать свойство в plot.ur; пкм plot; lay out; Horizontaly

}

void Plot::loadDataToPlot()
{
    //QMessageBox mb(QMessageBox::Icon::Information, "Loading data", "Info", QMessageBox::Ok);
    //mb.show();
    int size = socket->pendingDatagramSize();

    QNetworkDatagram datagram = socket->receiveDatagram(size);  //Для работы строчки нужно в h файл прописать #include <QNetworkDatagram>
    QByteArray buffer = datagram.data();

    QDataStream stream(buffer); //создание потока
    qint16* values = new qint16 [size/2]{};
    for(int i=0; i<size/2; i++)
    {
        stream >> values[i];
    }

    int limit = size/2;
    QVector<double> x(limit), y(limit), z(limit); //vector воспринимает только double. Z нужен только для медианы
    for(int i=0; i<limit; i++)
    {
        x[i] = i;
        y[i] = values[i];
    }
    delete [] values;

    ui->customPlot->graph(0)->data()->clear();
    ui->customPlot->graph(0)->setData(x,y);

    //Для того, чтобы график перерисовался
    ui->customPlot->replot();


    /////////////////////////////// добавление макс значения и медианы в окне WV

    //double max = *std::max_element(y.begin(), y.end());
    std::sort(y.begin(), y.end());

    //рисунок медианы
    std::fill(z.begin(), z.end(), y[limit/2]);
    ui->customPlot->graph(0)->setData(x,z);
    //ui->customPlot->replot();

    ui->statusbar->showMessage("Mediane: " + QString::number(y[size/4])+ "\t\t\t" + "Maxvalue: " + QString::number(y.last()));


}
