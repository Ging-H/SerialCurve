#ifndef BASESERIALCOMM_H
#define BASESERIALCOMM_H

#include <QComboBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QAbstractItemView>
#include <QMessageBox>
#include <QMetaEnum>
#include <QDebug>
//#include "crc.h"

class BaseSerialComm : public QSerialPort,public QSerialPortInfo
{
    Q_OBJECT
public:
    // QSerialPort 只有115200波特率, 为避免直接修改库文件,重写波特率枚举类型
    enum BaudRate {
        Baud1200    = 1200,
        Baud2400    = 2400,
        Baud4800    = 4800,
        Baud9600    = 9600,
        Baud19200   = 19200,
        Baud38400   = 38400,
        Baud57600   = 57600,
        Baud115200  = 115200,
        Baud128000  = 128000,
        Baud256000  = 256000,
        Baud921600  = 921600,
        Baud1000000 = 1000000,
        UnknownBaud = -1
    };
    Q_ENUM(BaudRate)

    enum  Terminator{
        NONE        = 0,
        CRLF_0x0D0A = 0x0D0A, // '\r''\n',
        CR_0x0D     = 0x0D,   // '\r',
        LF_0xOA     = 0x0A,   // '\n',
        UnknownTerminator = -1
    };
    Q_ENUM(Terminator)

    explicit BaseSerialComm(QSerialPort *parent = nullptr);

    static void listVerify      (QComboBox *cbbVerify);
    static void listStopBit     (QComboBox *cbbStopBit);
    static void listBaudRate    (QComboBox *cbbBaud);
    static void listDataBit     (QComboBox *cbbDataBit);
    static void listPortNum     (QComboBox *cbbPortNum);
    static void listTerminator  (QComboBox *cbbTerminator);
    static void searchPort      (QStringList &portList);

    quint8   verifyADD8(QByteArray  buf );
    quint8   verifyXOR8(QByteArray  buf );
    quint16  verifyCRC16_Modbus(QByteArray buf);
    quint16  verifyCRC16_CCITT(QByteArray buf);
    quint32  verifyCRC32(QByteArray buf);
    quint16  verifyLRC( QByteArray buf );
    uint8_t  verifyCRC8_DS18B20(QByteArray buf);
    uint16_t verifyCRC16_USB(QByteArray buf);
    uint16_t verifyCRC16_CCITT_FALSE(QByteArray buf);

    static bool isHexString(QString src);

    qint32 readData   (QByteArray &rxBuffer);
    qint32 writtenData(QString txBuffer);
    void insertTerminator(QByteArray &buffer,BaseSerialComm::Terminator terminator);

signals:

public slots:

};

#endif // BASESERIALCOMM_H
