#include <QFileInfo>
#include <QDir>
#include "libraw/libraw.h"
#include "thumbsworker.h"
using namespace std;

ThumbsWorker::ThumbsWorker(QObject *parent) : QObject(parent)
{
    // Constructor
}

ThumbsWorker::~ThumbsWorker()
{
    // Destructor
    // free resources
}


void ThumbsWorker::process()
{
    // Process. Start processing data.
    // allocate resources using new here

    const int imageSize = 100;

    for (int i=0; i < this->files.size(); i++)
    {
        //qDebug() << this->files.at(i);
        QString thumbname = ThumbsWorker::creaThumbnail( QString( this->files.at(i) ));
        // emit error(QString(this->files.at(i) ));
        if (thumbname.length() > 0) {
            emit thumbFound( QString(thumbname) );
        }
    }

    emit finished();
}

/**
 * converte QString in char*
 *
 * @brief MainWindow::toCharArray
 * @param qstring
 * @return
 */
char* ThumbsWorker::toCharArray(QString qstring)
{
    QByteArray ba = qstring.toLatin1(); //.toLocal8Bit8Bit();
    return ba.data();
}

void ThumbsWorker::setFiles(QStringList myfiles)
{
    this-> files = myfiles;
}

QString ThumbsWorker::creaThumbnail( QString filename)
{

    // const char* filenameAsCharArray = ThumbsWorker::toCharArray(filename);

    QFileInfo fileInfo = QFileInfo(filename);
    QString thumbsDir = fileInfo.absoluteDir().absolutePath().append("/_thumbs");
    QDir().mkdir( thumbsDir );
    QString result = QString( thumbsDir.append("/").append( fileInfo.baseName()).append(".jpeg"));

    // fprintf(stdout, "creazione miniatura '%s' ->  %s \n", ThumbsWorker::toCharArray(filename),ThumbsWorker::toCharArray(result) );
    // cout << "creazione miniatura " << ThumbsWorker::toCharArray(filename) << " -> " << ThumbsWorker::toCharArray(result) << endl;
    //qDebug("creazione thumb per %s -> %s ", ThumbsWorker::toCharArray(filename), ThumbsWorker::toCharArray(result));

    if (QFile::exists(result) ) return result;

    LibRaw rawProcessor;


    // NON passare char* altrimenti rawProcessor cambia il nome del file
    int ret  = rawProcessor.open_file( ThumbsWorker::toCharArray(filename), 1 );
    if (ret != LIBRAW_SUCCESS)
    {
        fprintf(stderr, "errore apertura '%s' : %d %s \n", ThumbsWorker::toCharArray(filename), ret, libraw_strerror(ret));
        return QString("");
    }
/*
    if ((ret = RawProcessor.unpack()) != LIBRAW_SUCCESS)
    {
        fprintf(stderr, "Cannot unpack '%s' : %s \n", filenameAsCharArray, libraw_strerror(ret));
        return result;
    }
*/


/*
    if (LIBRAW_SUCCESS != (ret = RawProcessor.dcraw_process()))
    {
        fprintf(stderr, "Cannot do postpocessing on %s: %s\n", filename, libraw_strerror(ret));
        if (LIBRAW_FATAL_ERROR(ret)) {
            return result;
        }
    }
*/

/*


    cout << "done processing" << endl;

    // RawProcessor.raw2image();

    //RawProcessor.imgdata.params.output_tiff;
    ret = RawProcessor.dcraw_ppm_tiff_writer(outFilename);
    cout << "scrittura ppm, ret=" << ret << endl;

    */
    ret = rawProcessor.unpack_thumb();
    if (ret  != LIBRAW_SUCCESS) {
        qDebug( "unpack thumbnail errata %s, ret=%s", ThumbsWorker::toCharArray( result ),  libraw_strerror(ret));
        return QString("");
    } else {
        ret = rawProcessor.dcraw_thumb_writer(ThumbsWorker::toCharArray( result ));
        if (ret  != LIBRAW_SUCCESS) {
            return QString("");
        }
    }
    rawProcessor.recycle();
    return result;
}
