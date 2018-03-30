#ifndef THUMBSEXTRACTORTHREAD_H
#define THUMBSEXTRACTORTHREAD_H

#include <QObject>

class ThumbsExtractorThread : public QObject {
    Q_OBJECT

private:
    QStringList files;

public:
    ThumbsExtractorThread();
    ~ThumbsExtractorThread();

    static char* toCharArray( QString qstring);
    void setFiles(QStringList files);
    static QString creaThumbnail(QString filename);

public slots:
    void process();

signals:
    void finished();
    void error(QString err);
};

#endif // THUMBSEXTRACTORTHREAD_H
