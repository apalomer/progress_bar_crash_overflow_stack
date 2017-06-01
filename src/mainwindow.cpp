#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    progress = new QProgressDialog("Iterating...","Cancell", 0, ui->spinBox->value(), this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_nowhait_clicked()
{
    qDebug()<<"No whait push button clicked";
    // Run in new thread and create a progress bar
    progress->setMinimum(0);
    progress->setMaximum(ui->spinBox->value());
    progress->setWindowModality(Qt::WindowModal);
    progress->setAutoClose(true);
    progress->show();
    QThread* th = new QThread;
    ThreadedWorker* work = new ThreadedWorker(ui->spinBox->value());
    work->moveToThread(th);
    connect(th, SIGNAL(started()), work, SLOT(process()));
    connect(work,SIGNAL(status(int)),progress,SLOT(setValue(int)));
    connect(work, SIGNAL(finished()), th, SLOT(quit()));
    connect(work,SIGNAL(finished()),progress,SLOT(close()));
    connect(work, SIGNAL(finished()), work, SLOT(deleteLater()));
    connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));
    connect(progress,SIGNAL(canceled()),th,SLOT(quit()));
    connect(progress,SIGNAL(canceled()),work,SLOT(quit()));
    th->start();
    qDebug()<<"exit no whait push button callback";
}

void MainWindow::on_pushButton_whait_clicked()
{
    qDebug()<<"Whait push button clicked";
    // Run in new thread and create a progress bar
    progress->setMinimum(0);
    progress->setMaximum(ui->spinBox->value());
    progress->setWindowModality(Qt::WindowModal);
    progress->setAutoClose(true);
    progress->show();
    ThreadedWorker* work = new ThreadedWorker(ui->spinBox->value());
    connect(work,SIGNAL(status(int)),progress,SLOT(setValue(int)));
    connect(work,SIGNAL(finished()),progress,SLOT(close()));
    connect(progress,SIGNAL(canceled()),work,SLOT(quit()));
    work->process();
    qDebug()<<"exit whait push button callback";
}
