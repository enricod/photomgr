#ifndef THUMBSWORKER_H
#define THUMBSWORKER_H

#include <QObject>

class ThumbsWorker : public QObject {
        Q_OBJECT

    private:
        QStringList files;

    public:
        ThumbsWorker(QObject *parent = 0);
        ~ThumbsWorker();

        static char* toCharArray( QString qstring);
        void setFiles(QStringList files);
        static QString creaThumbnail(QString filename);

    public slots:
        void process();

    signals:
        void finished();

        void error(QString err);

    };

#endif // THUMBSWORKER_H
