#ifndef FRAMESDATAPOOL_H
#define FRAMESDATAPOOL_H

#include <QDebug>
#include <QFile>
#include <QMap>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QRegularExpression>


class FramesDataPool
{
public:
    struct AnimationData;

private:

    static QMap<QString, QPixmap> m_frames;
    static QMap<QString, AnimationData> m_animationsData;

    static void getDataFromXML(QString fileName);


    static void getDataFromJson(QString fileName/*animationData*/);




public:
    //FramesDataPool();
    struct AnimationData
    {
        int frameRate;
        QVector<QString> frameNames;
        //QVector<QString> scenarios; //TODO
        //ScenariosData defaultScenarioData; //TODO
    };


    static AnimationData& getAnimationData(QString animationName);

    static QPixmap& getFrame(QString frameName);


    static void init();


};

#endif // FRAMESDATAPOOL_H
