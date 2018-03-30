#include "thumbsextractorthread.h"
#include "mainwindow.h"
#include "libraw/libraw.h"
#include <QThread>
using namespace std;

ThumbsExtractorThread::ThumbsExtractorThread() { // Constructor
    // you could copy data from constructor arguments to internal variables here.
}







void ThumbsExtractorThread::setFiles(QStringList files) {
    this->files = files;
}
