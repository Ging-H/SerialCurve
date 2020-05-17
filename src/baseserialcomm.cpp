#include "baseserialcomm.h"


BaseSerialComm::BaseSerialComm(QSerialPort *parent) : QSerialPort(parent)
{
}

/**
 * @brief BaseSerialComm::listBaudRate 在控件中列出支持的波特率
 * @param cbbBaud BaudRate
 */
void BaseSerialComm::listBaudRate(QComboBox *cbbBaud)
{
    QMetaEnum mtaEnum = QMetaEnum::fromType<BaseSerialComm::BaudRate>();
    QString tmp;
    for (int i = 0; i < mtaEnum.keyCount(); i++) {
        tmp = QString::number(mtaEnum.value(i));
        cbbBaud->addItem(tmp, mtaEnum.value(i));
        /* 删除未知值 */
        if(mtaEnum.value(i)== BaseSerialComm::BaudRate::UnknownBaud ){
            cbbBaud->removeItem(i);
        }
    }
    cbbBaud->setCurrentText("115200"); // 设定默认值
}
/**
 * @brief BaseSerialComm::listDataBit  在控件中列出支持的数据位
 * @param cbbDataBit
 */
void BaseSerialComm::listDataBit(QComboBox *cbbDataBit)
{
    QString tmp;
    QMetaEnum mtaEnum = QMetaEnum::fromType<BaseSerialComm::DataBits>();
    for (int i = 0; i < mtaEnum.keyCount(); i++) {
        tmp = QString::number(mtaEnum.value(i));
        cbbDataBit->addItem(tmp, mtaEnum.value(i));
        /* 删除未知值 */
        if(mtaEnum.value(i) == BaseSerialComm::DataBits::UnknownDataBits )
            cbbDataBit->removeItem(i);
    }
    cbbDataBit->setCurrentText("8"); // 设定默认值
}

/**
 * @brief BaseSerialComm::listVerify  列出校验控制选项
 * @param cbbVerify
 */
void BaseSerialComm::listVerify(QComboBox *cbbVerify)
{
    /* 获取枚举元信息,并且与下拉列表 cbbVerify的item 绑定 */
    QMetaEnum mtaEnum = QMetaEnum::fromType<QSerialPort::Parity>();
    for (int i = 0; i < mtaEnum.keyCount(); i++) { // 遍历每个枚举值,获得text和data,添加到item中
        cbbVerify->addItem(mtaEnum.key(i), mtaEnum.value(i));
        /* 删除未知值 */
        if(mtaEnum.value(i) == BaseSerialComm::Parity::UnknownParity )
            cbbVerify->removeItem(i);
    }
    cbbVerify->setCurrentText("NoParity"); // 设定默认值
}

/**
 * @brief BaseSerialComm::listStopBit  列出停止位
 * @param cbbStopBit
 */
void BaseSerialComm::listStopBit(QComboBox *cbbStopBit)
{
    /* StopBits 停止位 */
    QMetaEnum mtaEnum = QMetaEnum::fromType < BaseSerialComm::StopBits >();
    QString tmp;
    for (int i = 0; i < mtaEnum.keyCount(); i++) {
        tmp = QString::number(mtaEnum.value(i));
        if(mtaEnum.value(i) == 3)
            tmp = "1.5";  // 用3表示1.5个停止位
        cbbStopBit->addItem(tmp, mtaEnum.value(i));

        /* 删除未知值 */
        if(mtaEnum.value(i) == BaseSerialComm::StopBits::UnknownStopBits )
            cbbStopBit->removeItem(i);
    }
    cbbStopBit->setCurrentText("1"); // 设定默认值
}

/**
 * @brief BaseSerialComm::listPortNum 列出端口号
 * @param cbbPortNum
 */
void BaseSerialComm::listPortNum(QComboBox *cbbPortNum)
{
    QStringList portList;
    qint32 len = 0;   // list中最大的字符宽度

    portList.clear(); // 清空列表
    searchPort(portList);                      // 搜索可用的串口和描述
    if(portList.empty() == false){
        cbbPortNum->addItems(portList);    // 添加到ComboBox
        foreach(const QString &item, portList) // 遍历list每一项
        {
            if(len < item.toLocal8Bit().length() ) // 获取字符宽度
                len = item.toLocal8Bit().length();
        }
        qint32 fontSize = cbbPortNum->font().pointSize(); // 获取所用字体大小
        cbbPortNum->view()->setFixedWidth( len * fontSize * 0.75 ); // 调整显示宽度,字符数*字符宽度*0.75

    }
    else{
        QMessageBox::information(NULL, "无串口设备",  "没有搜索到串口设备", 0, 0);
    }
}

/**
 * @brief BaseSerialComm::listTerminator 列出行结束符
 * @param cbbTerminator
 */
void BaseSerialComm::listTerminator(QComboBox *cbbTerminator)
{
    QMetaEnum mtaEnum = QMetaEnum::fromType<BaseSerialComm::Terminator>();
    for (int i = 0; i < mtaEnum.keyCount(); i++) {
        cbbTerminator->addItem(mtaEnum.key(i), mtaEnum.value(i));
        /* 删除未知值 */
        if(mtaEnum.value(i) == BaseSerialComm::Terminator::UnknownTerminator)
            cbbTerminator->removeItem(i);
    }
    cbbTerminator->setCurrentText("NONE"); // 设定默认值
}

/**
 * @brief BaseSerialComm::searchPort 搜索端口号
 * @param portList
 */
void BaseSerialComm::searchPort(QStringList &portList)
{
    portList.clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        portList << info.portName() + " " + info.description();
    }
}

/**
 * @brief BaseSerialComm::readData 读取串口缓存中的数据 ,返回0代表没有接收到数据
 * @param rxBuffer
 * @return
 */
qint32 BaseSerialComm::readData(QByteArray &rxBuffer)
{
    rxBuffer = this->readAll();
    if(rxBuffer.isEmpty()){
        return 0;
    }
    else {
        return rxBuffer.length();
    }
}

/**
 * @brief BaseSerialComm::writtenData  往串口写入数据,写入字符串类型数据
 * @param txBuffer
 * @return  返回-1代表写入错误
 */
qint32 BaseSerialComm::writtenData(QString txBuffer)
{
    QByteArray tmpBuffer = txBuffer.toLatin1();
    return this->write(tmpBuffer);
}

/**
 * @brief BaseSerialComm::insertTerminator  插入行结束符
 * @param buffer
 * @param terminator
 */
void BaseSerialComm::insertTerminator(QByteArray &buffer, Terminator terminator)
{
    if(buffer.isEmpty())
        return;
    if(terminator != NONE){
        switch(terminator){
        case CRLF_0x0D0A:
            buffer.append(CR_0x0D);
            buffer.append(LF_0xOA);
            break;
        case CR_0x0D:
            buffer.append(CR_0x0D);
            break;
        case LF_0xOA:
            buffer.append(LF_0xOA);
            break;
        default:break;
        }
    }
}

/**
 * @brief BaseSerialComm::isHexString 检查src中字符是否符合Hex规则表达式
 * @param src
 * @return
 */
bool BaseSerialComm::isHexString(QString src)
{
    bool isMatch = true;
    QRegExp regExp("[a-f0-9A-F ]*");
    isMatch = regExp.exactMatch(src);
    return isMatch;
}

/**
 * @brief BaseSerialComm::verifyADD8 添加校验码 ADD8
 * @param buf
 * @return
 */
quint8 BaseSerialComm::verifyADD8(QByteArray buf)
{
    quint8 retVal = 0;
    foreach(quint8 c, buf){
        retVal += c;
    }
    return retVal;
}


/**
 * @brief BaseSerialComm::verifyXOR8 添加校验码 XOR8
 * @param buf
 * @return
 */
quint8 BaseSerialComm::verifyXOR8(QByteArray buf)
{
    quint8 retVal = 0;
    foreach(quint8 c, buf){
        retVal ^= c;
    }
    return retVal;
}

/**
 * @brief BaseSerialComm::verifyCRC16 添加校验码 Modbus CRC16
 * @param buf
 * @return CRC16
 */
quint16 BaseSerialComm::verifyCRC16_Modbus(QByteArray buf)
{
    quint16 crc16 = 0;
//    crc16 = crc16_modbus_calc((uint8_t *)buf.data(),buf.size());
    return crc16;
}

/**
 * @brief BaseSerialComm::verifyCRC16_CCITT  计算校验码 CCITT
 * @param buf
 * @return CRC16
 */
quint16 BaseSerialComm::verifyCRC16_CCITT(QByteArray buf)
{
    quint16 crc16 = 0;
//    crc16 = crc16_ccitt_calc((uint8_t *)buf.data(),buf.size());
    return crc16;
}
/**
 * @brief BaseSerialComm::verifyCRC32  计算校验码 CRC32
 * @param buf
 * @return CRC32
 */
quint32 BaseSerialComm::verifyCRC32(QByteArray buf)
{
    quint32 crc32 = 0;
//    crc32 = crc32_calc((uint8_t *)buf.data(),buf.size());
    return crc32;
}
/**
 * @brief BaseSerialComm::verifyLRC 计算校验码 LRC
 * @param buf
 * @return LRC-ASCII
 */
uint16_t BaseSerialComm::verifyLRC(QByteArray buf)
{
    uint8_t uchLRC = 0;
    uint8_t tmp;
    uint16_t retVal;
    uchLRC = verifyADD8(buf);

    tmp = (uchLRC>>4);
    if( tmp <= 9 ){
        tmp += '0';
    }else{
        tmp += 'A';
    }
    retVal = tmp<<8;

    tmp = uchLRC&0x0F;
    if( tmp <= 9 )
    {
        tmp += '0';
    }
    else
    {
        tmp += 'A';
    }
    retVal |= tmp;
    return  ( retVal );
}
/**
 * @brief BaseSerialComm::verifyCrc8Ds18b20 校验码crc8 一般用于ds18b20
 * @param buf
 * @return CRC8
 */
uint8_t BaseSerialComm::verifyCRC8_DS18B20(QByteArray buf)
{
    uint8_t crc8 = 0;
//    uint8_t crc8 = crc8_maxim_calc((uint8_t *)buf.data(), buf.size());
    return  crc8;
}
/**
 * @brief BaseSerialComm::verifyCrc16Usb 校验码crc16,一般用于usb校验
 * @param buf
 * @return CRC16 USB
 */
uint16_t BaseSerialComm::verifyCRC16_USB(QByteArray buf)
{
    uint16_t  crc16 = 0;
//    uint16_t crc16 = crc16_usb_calc((uint8_t *)buf.data(), buf.size());
    return crc16;
}
/**
 * @brief BaseSerialComm::verifyCrc16Ccitt_f 校验码crc16,一般用于ccitt false
 * @param buf
 * @return CRC16 CCITT False
 */
uint16_t BaseSerialComm::verifyCRC16_CCITT_FALSE(QByteArray buf)
{
    uint16_t crc16 = 0;
//    uint16_t crc16 = crc16_ccitt_false_calc((uint8_t*)buf.data(), buf.size() );
    return crc16;
}
