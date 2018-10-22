#include "FramesDataPool.h"
#include "globalconst.h"
#include <thread>
//#include <chrono>
#include <iostream>
//FramesDataPool::FramesDataPool()
//{

//}

QHash<QString, QPixmap> FramesDataPool::m_frames;
QHash<QString, FramesDataPool::AnimationData> FramesDataPool::m_animationsData;


void FramesDataPool::init()
{
//    auto start = std::chrono::steady_clock::now();
    getDataFromXML(PATH_TO_RESOURCES + "/images/textures.xml");

//    getDataFromJson(PATH_TO_RESOURCES + "/instructionsForAssetsManager.json");
//    std::cout << std::this_thread::get_id() << "\n";
    std::thread threadJsonGetting(getDataFromJson, PATH_TO_RESOURCES + "/instructionsForAssetsManager.json");
    threadJsonGetting.join();

//    auto end = std::chrono::steady_clock::now();
//    std::cout << std::chrono::duration <double, std::milli> (end - start).count() << " ms" <<  std::endl;
}

void FramesDataPool::getDataFromXML(QString fileName){
    // В данном коде не осуществляется проверка на закрытие тега, поскольку в этом нет необходимости
    QPixmap pngFile;
    QFile xmlFile;

    //Открываем XML файл для чтения
    xmlFile.setFileName(fileName);
    if (!xmlFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(0,"Ошибка файла","Не удалось открыть файл \n"+fileName, QMessageBox::Ok);
        return;
    }

    //Создаем объект, с помощью которого осуществляется чтение из файла
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&xmlFile);
    xmlReader.readNext();   //Переходит к первому элементу в файле

    //Крутимся в цикле до тех пор, пока не достигнем конца документа
    while(!xmlReader.atEnd())
    {
        // Проверяем, является ли элемент началом тега
        if(xmlReader.isStartElement())
        {

            if(xmlReader.name() == "TextureAtlas")
            {
                QString fileName = xmlReader.attributes().at(0).value().toString();
                pngFile.load(PATH_TO_RESOURCES + "/images/" + fileName);

            }

            if(xmlReader.name() == "sprite")
            {

                //FrameData frameData;
                QString name;
                int x, y, width, height;

                // Забираем все атрибуты тега и перебираем их для проверки на соответствие нужному нам атрибуту
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes()) {
                    // Если найден нужный атрибут, то по его значению устанавливаем значения координат

                    if (attr.name().toString() == "n")
                        name = attr.value().toString();

                    else if (attr.name().toString() == "x")
                        x = attr.value().toInt();

                    else if (attr.name().toString() == "y")
                        y = attr.value().toInt();

                    else if (attr.name().toString() == "w")
                        width = attr.value().toInt();

                    else if (attr.name().toString() == "h")
                        height = attr.value().toInt();

                }

                //забираем текст из тела тега
                //QString elementText = xmlReader.readElementText();
                //m_frames[frameData.name] = frameData;
                if(m_frames.contains(name))
                {
                    QMessageBox::warning(0,"Ошибка","совпадают имена у текстур \n"+name, QMessageBox::Ok);
                    return;
                }

                QPixmap frame;
                frame = pngFile.copy( x, y, width, height);

                m_frames.insert(name, frame);

            }
        }
        xmlReader.readNext(); // Переходим к следующему элементу файла
    }
    xmlFile.close(); // Закрываем файл

}

void FramesDataPool::getDataFromJson(QString fileName)
{
//    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
//    std::cout << std::this_thread::get_id() << "\n";
    QString val;
    QFile file;
    file.setFileName(fileName);
    //file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(0,"Ошибка файла","Не удалось открыть файл \n"+fileName, QMessageBox::Ok);
        return;
    }
    val = file.readAll();
    file.close();
    //qWarning() << val;
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject root = doc.object();
    QJsonValue value = root.value("animations");
    QJsonArray animations = value.toArray();


    QList<QString> allFrameNames = m_frames.keys();

    for ( int i = 0; i < animations.count(); i++ )
    {
        QJsonObject animation = animations.at(i).toObject();
        // Забираем значения свойств
        QString name = animation.value("name").toString();

        //int frameRate = animation.value("frameRate").toInt();

        AnimationData animationData;
        animationData.frameRate = animation.value("frameRate").toInt();


        QRegularExpression re("^"+name);
        for ( auto i = allFrameNames.cbegin(); i != allFrameNames.cend(); i++ )
        {
            if ( re.match( *i ).hasMatch() )
            {
                animationData.frameNames.push_back( *i );
            }
        }

        m_animationsData.insert(name, animationData);

    }

}

FramesDataPool::AnimationData &FramesDataPool::getAnimationData(QString animationName)
{
    return m_animationsData[animationName];
}

QPixmap &FramesDataPool::getFrame(QString frameName)
{
    return m_frames[frameName];
}
