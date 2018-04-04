#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtConcurrent/QtConcurrent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setFiles(QStringList files);

public slots:
    void selezionaDir();
    void showImage(int num);
    void finished();
    void onProgressChanged(QString info);
    void errorString(QString info);
    void thumbFound(QString filename);

private:
    Ui::MainWindow *ui;
    QList<QLabel *> labels;
    int thumbsPerColumn = 1;
    int thumbSize;

    QPushButton *openButton;

    QTextEdit *logsTextEdit;
    QVBoxLayout *mainLayout;
    QGridLayout *imagesLayout;

    QString selectDir;
    QFutureWatcher<QImage> *imageScaling;


};

#endif // MAINWINDOW_H
