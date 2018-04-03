#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "libraw/libraw.h"
#include <iostream>
#include <QFileDialog>
#include <QDirIterator>
#include <QDebug>
#include "thumbsworker.h"
using namespace std;


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{

    setWindowTitle(tr("Raw Images Conversion"));
    resize(800, 600);

    openButton = new QPushButton(tr("Select dir"));
    connect(openButton, &QPushButton::clicked, this, &MainWindow::selezionaDir);

    imageScaling = new QFutureWatcher<QImage>(this);

    connect(imageScaling, &QFutureWatcher<QImage>::resultReadyAt, this, &MainWindow::showImage);
    connect(imageScaling, &QFutureWatcher<QImage>::finished, this, &MainWindow::finished);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(openButton);
    buttonLayout->addStretch();

    imagesLayout = new QGridLayout();

    QHBoxLayout *logsLayout =  new QHBoxLayout();
    logsTextEdit = new QTextEdit();
    logsLayout->addWidget(logsTextEdit);

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(imagesLayout);
    mainLayout->addLayout(logsLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);

    //ui->setupUi(this);
}

/**
 * @brief MainWindow::selezionaDir scelta della directory
 */
void MainWindow::selezionaDir()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home/enrico/Pictures/fujifilm",
                                                    /* "/data/Pictures/2018/2018-03-18", */
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    QStringList files;
    QDirIterator fileItr(dir, QStringList() << "*.RAF", QDir::Files); //, QDirIterator::Subdirectories);
    while (fileItr.hasNext())
    {
        QString f = fileItr.next();
        cout <<  f.toStdString() << endl;
        files.append(f);
    }

    QThread* thread = new QThread;
    ThumbsWorker* worker = new ThumbsWorker();
    worker->moveToThread(thread);
    worker->setFiles(files);
    connect(worker, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
    connect(thread, SIGNAL (started()), worker, SLOT (process()));
    connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
    connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}

void MainWindow::onProgressChanged(QString info)
{
    // aggiornamento dal thread di creazione delle miniature
    logsTextEdit->setText("Latest info: " + info);
}

void MainWindow::showImage(int num)
{
    //labels[num]->setPixmap(QPixmap::fromImage(imageScaling->resultAt(num)));
}

void MainWindow::finished()
{
    qDebug("terminato");
    //openButton->setEnabled(true);
    //cancelButton->setEnabled(false);
    //pauseButton->setEnabled(false);
}

void MainWindow::errorString(QString msg)
{
    qDebug("errore %s", ThumbsWorker::toCharArray(msg));
    logsTextEdit->append(  msg);
    //openButton->setEnabled(true);
    //cancelButton->setEnabled(false);
    //pauseButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    imageScaling->cancel();
    imageScaling->waitForFinished();
    //delete ui;
}
