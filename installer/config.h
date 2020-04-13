#ifndef CONFIG_H
#define CONFIG_H


#include <QObject>
#include <QMap>

class Config : public QObject
{
    Q_OBJECT
public:
    QString W3VERSION_LATEST;
    QString W3VERSION_126;
    QString BNET_EUROPE;
    QString BNET_ASIA;
    QString BNET_USEAST;
    QString BNET_USWEST;
    QString DATAPATH;

    QString W3PATH_LATEST;
    QString W3PATH_126;
    QString EUROPATH;
    QString LANGID;
    QString ARCHIVE;
    QString ARCHIVE_FULL;
    QString APPDATA;

    QMap<QString, QString> hashmap;

    Config();
};


#endif //CONFIG_H
