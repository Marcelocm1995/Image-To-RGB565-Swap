#include <QCoreApplication>
#include <QImage>
#include <QFile>

int main(int argc, char *argv[])
{
    QImage imageObject;
    imageObject.load("image.png");

    QImage newImage = imageObject.convertToFormat(QImage::Format_RGB16);

    QByteArray arr = QByteArray::fromRawData((const char*)newImage.bits(), newImage.sizeInBytes());

    QFile data("output.txt");
    data.open(QFile::WriteOnly | QFile::Truncate);
    QTextStream out(&data);

    for(long unsigned int j=0; j<newImage.sizeInBytes(); j+=2)
    {
        if( (((j+2) % 480) == 0) && (j >= 478))
        {
            uint8_t mybyte1 = arr[j];
            uint8_t mybyte2 = arr[j+1];
            char bff[16];
            memset(bff, 0x00, sizeof(bff));
            sprintf(bff, "0x%02x,0x%02x,\n", mybyte2, mybyte1);
            out << bff;
        }

        else
        {
            uint8_t mybyte1 = arr[j];
            uint8_t mybyte2 = arr[j+1];
            char bff[14];
            memset(bff, 0x00, sizeof(bff));
            sprintf(bff, "0x%02x,0x%02x,", mybyte2, mybyte1);
            out << bff;
        }
    }

    QCoreApplication a(argc, argv);

    return a.exec();
}
