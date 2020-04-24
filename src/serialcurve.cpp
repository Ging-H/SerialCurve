#include "serialcurve.h"
#include "ui_serialcurve.h"
#include "QtEndian"
#include <QTextCodec>

SerialCurve::SerialCurve(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SerialCurve)
{
    ui->setupUi(this);
    currentPort = new BaseSerialComm();
    connect(currentPort,SIGNAL(errorOccurred(QSerialPort::SerialPortError)),this,SLOT(slots_errorHandler( QSerialPort::SerialPortError)));

    this->initComboBox_Config();
    this->initPlot();
    rdbGroup = new QButtonGroup();
    rdbGroup ->setExclusive(true);
    rdbGroup ->addButton(ui->rdbSinglePlot);
    rdbGroup ->addButton(ui->rdbMultiPlot);
}

SerialCurve::~SerialCurve()
{
    delete ui;
}


/*   初始化了串口设置当中的下拉列表(ComboBox) */
void SerialCurve::initComboBox_Config()
{
    /* 更新下拉列表 */
    BaseSerialComm::listBaudRate( ui -> cbbBaud    );
    BaseSerialComm::listDataBit ( ui -> cbbDataBit );
    BaseSerialComm::listVerify  ( ui -> cbbVerify  );
    BaseSerialComm::listStopBit ( ui -> cbbStopBit );
    BaseSerialComm::listPortNum ( ui -> cbbPortNum );
}

/* 刷新按钮点击 槽函数 */
void SerialCurve::on_btnRefresh_clicked()
{
    if( !ui->btnOpenPort->isChecked()){  // 关闭串口才能刷新端口号
        ui -> cbbPortNum ->clear();
        BaseSerialComm::listPortNum ( ui -> cbbPortNum );
    }
}

/* 打开串口 槽函数*/
void SerialCurve::on_btnOpenPort_clicked(bool checked)
{
    QString tmp = ui->cbbPortNum->currentText();
    tmp = tmp.split(" ").first();//  Item的 text 由 <COM1 "描述"> 组成,使用空格作为分隔符取第一段就是端口名
    if(checked){
        // 当前串口处于关闭状态
        currentPort->setPortName( tmp );              // 设置端口号
        if( currentPort->open(QIODevice::ReadWrite)){ // 打开串口
            currentPort -> setDTRState(false);
            currentPort -> setRTSState(false);
            /* 配置端口的波特率等参数 */
            this->configPort();

            connect(currentPort ,SIGNAL(readyRead()),this,SLOT( slots_getRxBuf()));// 有数据就直接接收显示

            // 添加曲线,并且启动定时器
            if(ui->rdbSinglePlot->isChecked()){
                emit ui->rdbSinglePlot->clicked(true);
            }else{
                emit ui->rdbMultiPlot->clicked(true);
            }

            ui->btnOpenPort->setText(tr("关闭串口"));
        }else{
            ui->btnOpenPort->setChecked(false);
        }
    }
    else{
        if(timer.isActive()){
            timer.stop();
        }
        currentPort->close();
        ui->btnOpenPort->setText(tr("打开串口"));
    }
}

/* 配置端口的波特率\数据位\奇偶校验\停止位 */
void SerialCurve::configPort()
{
    QVariant tmpVariant;
    /* 设置波特率 */
    tmpVariant = ui->cbbBaud->currentData();  // 读取控件的当前项的值
    currentPort->setBaudRate(tmpVariant.value < BaseSerialComm::BaudRate > ()  );

    /* 设置数据位 */
    tmpVariant = ui->cbbDataBit->currentData();
    currentPort->setDataBits( tmpVariant.value <BaseSerialComm::DataBits > () );

    /* 设置校验位 */
    tmpVariant = ui->cbbVerify->currentData();
    currentPort->setParity (tmpVariant.value < BaseSerialComm::Parity > () );

    /* 设置停止位 */
    tmpVariant = ui->cbbStopBit->currentData();// 某些情况不支持1.5停止位
    if(currentPort->setStopBits (tmpVariant.value < BaseSerialComm::StopBits > () ) == false ){
        ui -> cbbStopBit->clear();
        BaseSerialComm::listStopBit ( ui -> cbbStopBit );
        QMessageBox::information(NULL, tr("不支持的设置"),  tr("该串口设备不支持当前停止位设置,已修改为默认的设置"), 0, 0);
    }
}

/* 串口错误信息处理 */
void SerialCurve::slots_errorHandler(QSerialPort::SerialPortError error)
{
    switch(error){
    case QSerialPort::DeviceNotFoundError:QMessageBox::information(NULL, tr("未找到设备"),  tr("检查设备是否已经连接,或者是否正常供电"), 0, 0);
        break;
    case QSerialPort::OpenError:
    case QSerialPort::PermissionError:QMessageBox::information(NULL, tr("打开失败"),  tr("检查设备是否已被其他软件占用"), 0, 0);
        break;
    default:
        break;
    }
}

/*  */
/* 初始化自定义绘图曲线 */
void SerialCurve::initPlot()
{
    // set some pens, brushes and backgrounds:
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->customPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->customPlot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui->customPlot->axisRect()->setBackground(axisRectGradient);


    ui->customPlot->xAxis->setRange(0, 10, Qt::AlignCenter);
    ui->customPlot->yAxis->setRange(0, 10, Qt::AlignCenter);

    //设定右上角图形标注和字体
    ui->customPlot->legend->setBorderPen(QPen(QColor(140, 140, 140,0)));// legend 边框颜色透明
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setTextColor(QColor(255,255,255,150)); // legend 字体颜色,白色
    ui->customPlot->legend->setBrush(QColor(74,74,74,0));   //legend背景色设为灰色但背景透明，允许图像在legend区域可见
    ui->customPlot->legend->setWrap(20); // 超过20行就换一列

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

/* 功能实现 */
/* 添加一条曲线 */
void SerialCurve::configSinglePlot()
{
    /* 清空原有曲线 */
    qint32 tmpCG;
    tmpCG = ui->customPlot->clearGraphs();
    ui->btnCurveSel->clear();
    ui->statusBar->showMessage(tr("clear %1 Graphs").arg(tmpCG));

    /* 新增一条曲线 */
    this->addNewGraph();
    graphsCount = 1;
    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);

    /* 更新坐标提示 */
    if( ui->actionCoorTips->isChecked() ){
        emit ui->actionCoorTips->triggered(false);
        emit ui->actionCoorTips->triggered(true);
    }
}
/* 添加多条曲线 */
void SerialCurve::configMultiPlot()
{
    /* 清空原有曲线 */
    qint32 tmpCG;
    tmpCG = ui->customPlot->clearGraphs();
    ui->btnCurveSel->clear();
    ui->statusBar->showMessage(tr("clear %1 Graphs").arg(tmpCG));

    /* 添加多条曲线 */
    qint32 numGraphs = ui->spbNumberG->value();
    for(qint32 i=0; i<numGraphs; i++){
        // set line style
        this->addNewGraph();
    }
    graphsCount = numGraphs;
    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);

    /* 更新坐标提示 */
    if( ui->actionCoorTips->isChecked() ){
        emit ui->actionCoorTips->triggered(false);
        emit ui->actionCoorTips->triggered(true);
    }

    ui->statusBar->showMessage(tr("添加%1条曲线").arg(numGraphs));
}

/* 添加新的曲线 */
void SerialCurve::addNewGraph()
{
    // add new graphs and set their look:
    ui->customPlot->addGraph();

    qint32 currentNum = 0;// 当前曲线的索引号
    currentNum = ui->customPlot->graphCount()-1;

    /* 使用随机颜色 */
    qint32 colorIndex = qrand()%20;// 伪随机
    QPen pen;         // 画笔,绘制曲线颜色,形状等
    pen.setWidth(1);  //线宽
    pen.setStyle(Qt::PenStyle::SolidLine);// a plain line
    pen.setColor(colorTable[colorIndex]);// 在20种颜色中随机选择一种
    ui->customPlot->graph(currentNum)->setPen(pen); // line color blue for first graph
    ui->customPlot->graph(currentNum)->setName(tr("曲线%1").arg(currentNum+1));//默认曲线名字
    ui->customPlot->graph(currentNum)->setSelectable(QCP::stNone);// 禁止鼠标选择曲线

    /* 添加对曲线的控制参数 */
    ui->btnCurveSel->addItem(ui->customPlot->graph(currentNum)->name());
}

/* 槽函数 选择任意曲线设置颜色和名字 */
void SerialCurve::on_btnCurveSel_currentIndexChanged(int index)
{
    if(ui->btnCurveSel->currentText().isEmpty())
        return;
    QString curveName = ui->customPlot->graph(index)->name();
    ui->txtCurveRename->setText( curveName );
    QColor curveColor = ui->customPlot->graph(index)->pen().color();
    ui->btnColorSel->setPalette(QPalette( curveColor ));
    ui->btnColorSel->setAutoFillBackground(true);             // 填充
    ui->btnColorSel->setStyleSheet(tr("background-color: %1").arg(curveColor.name()));
}

/* 槽函数,选择单条曲线 */
void SerialCurve::on_rdbSinglePlot_clicked(bool checked)
{
    if(checked){
        ui->statusBar->showMessage(tr("显示单一曲线"));
        this->configSinglePlot();  // 添加一条曲线
        ui->spbNumberG->setEnabled(false); // 禁用控件
        ui->cbbDataType->setEnabled(true);
        timer.disconnect(SIGNAL(timeout()));
        switch(dataType){
        case DT_int8_t:
        case DT_uint8_t:
            connect(&timer, SIGNAL(timeout()), this, SLOT(slots_singlePlotByte()));
            break;
        case DT_int16_t:
        case DT_uint16_t:
            connect(&timer, SIGNAL(timeout()), this, SLOT(slots_singlePlotHMByte()));
            break;
        case DT_int32_t:
        case DT_uint32_t:
        case DT_float:
            connect(&timer, SIGNAL(timeout()), this, SLOT(slots_singlePlotMByte()));
            break;
        }
        this->dataBuf.clear();// 清空数据缓存
        timer.start(20); // 启动定时器 20ms
    }
}
/* 槽函数,选择多条曲线 */
void SerialCurve::on_rdbMultiPlot_clicked(bool checked)
{
    if(checked){
        /* 修改数据显示函数 */
        timer.disconnect(SIGNAL(timeout()));
        connect(&timer, SIGNAL(timeout()), this, SLOT(slots_multiPlotCurve()));
        ui->cbbDataType->setEnabled(false); // 不需要数据类型选择,因为有固定的通信协议
        ui->statusBar->showMessage(tr("显示多条曲线"));
        ui->spbNumberG->setEnabled(true);
        this->configMultiPlot(); // 添加曲线
        this->dataBuf.clear();
    }
}
/* 修改曲线数量 */
void SerialCurve::on_spbNumberG_editingFinished()
{
    emit ui->rdbMultiPlot->clicked(true); // 触发"多条曲线"点击事件,修改曲线数量
}

/* 更换曲线数据类型 */
void SerialCurve::on_cbbDataType_currentIndexChanged(int index)
{
    this->dataType = (DataType)index;
    if( ui->rdbSinglePlot->isChecked() ){
        emit ui->rdbSinglePlot->clicked(true); // 触发点击事件,更换定时器超时槽函数
    }
}
/* 单一曲线显示处理,定时器超时槽函数 */
/* 单字节处理 */
void SerialCurve::slots_singlePlotByte()
{
    if(dataBuf.isEmpty()) return; // 数据缓存为空
    quint32 dataSize = dataBuf.size();

    QVector<double> tmpPosX(dataSize), tmpData(dataSize); // 用于绘图数据点,距离上一次绘图的数据量
    switch(dataType){
    case DT_int8_t :
        for(quint32 i=0; i<dataSize ; i++){
            tmpPosX[i] = posX++;     // x轴累加
            tmpData[i] = dataBuf.at(i);
        }
        break;
    case DT_uint8_t :
        for(quint32 i=0; i<dataSize ; i++){
            tmpPosX[i] = posX++;     // x轴累加
            tmpData[i] = (quint8)dataBuf.at(i);;
        }
        break;
    default:break;
    }
    ui->customPlot->graph(0)->addData(tmpPosX, tmpData); // 将数据添加到图上
    this->resetAxisRange(posX,tmpData.at(tmpData.count()-1)); // 调整坐标轴

    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);
    dataBuf.clear();
}
/* 超时更新曲线,半字数据曲线 */
void SerialCurve::slots_singlePlotHMByte()
{
    if(dataBuf.isEmpty()) return; // 数据缓存为空
    QByteArray tmpArray;
    if( (dataBuf.size()&0x01) != 0){ // 奇偶性判断是否2的倍数
        tmpArray = dataBuf.right(1);// 处理不足1字节的数据
        dataBuf.chop(1);
    }
    quint32 dataSize = dataBuf.size()/2;
    if(dataSize == 0){   // 数据量少于2
        dataBuf.clear();
        if(!tmpArray.isEmpty()){
            dataBuf.append(tmpArray);
        }
        return;
    }

    union ArrayToX{ // 整形数据转换成浮点数
        qint16  data_hw;     // half word 2字节
        quint16 data_uhw;    // unsigned half word
    }tmp[dataSize];

    memcpy(&tmp, dataBuf.data(), dataBuf.size());

    QVector<double> tmpPosX(dataSize), tmpData(dataSize); // 用于绘图数据点,距离上一次绘图的数据量
    switch(dataType){
    case DT_int16_t :
        for(quint32 i=0; i<dataSize; i++){
            tmpPosX[i] = posX++;     // x轴累加
            tmpData[i] = qFromLittleEndian<qint16>(&tmp[i].data_hw);
        }
        break;
    case DT_uint16_t :
        for(quint32 i=0; i<dataSize; i++){
            tmpPosX[i] = posX++;     // x轴累加
            tmpData[i] = qFromLittleEndian<quint16>(&tmp[i].data_uhw);
        }
        break;
    default:break;
    }
    ui->customPlot->graph(0)->addData(tmpPosX, tmpData); // 将数据添加到图上
    this->resetAxisRange(posX,tmpData.at(tmpData.count()-1)); // 调整坐标轴

    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);
    dataBuf.clear();
    if(!tmpArray.isEmpty()){
        dataBuf.append(tmpArray);
    }
}
/* 超时更新曲线,多字节数据曲线 */
void SerialCurve::slots_singlePlotMByte()
{
    if(dataBuf.isEmpty()) return;// 数据缓存为空
    QByteArray tmpArray;
    qint32 dataMod = dataBuf.size()%4; // 处理不足4字节的数据
    if( dataMod != 0){
        tmpArray = dataBuf.right(dataMod);
        dataBuf.chop(dataMod);
    }
    quint32 dataSize = dataBuf.size()/4;
    if(dataSize == 0){   // 数据量少于4
        dataBuf.clear();
        if(!tmpArray.isEmpty()){
            dataBuf.append(tmpArray);
        }
        return;
    }

    union ArrayToX{   // 数组数据转换其他数据类型
        qint32  data_w;     // word 4字节
        quint32 data_uw;    // unsigned word
        float data_f;       // float
    }tmp[dataSize];

    memcpy(&tmp, dataBuf.data(), dataBuf.size());

    QVector<double> tmpPosX(dataSize), tmpData(dataSize); // 用于绘图数据点,距离上一次绘图的数据量

    switch(dataType){
    case DT_int32_t :
        for(quint32 i=0; i<dataSize; i++){
            tmpPosX[i] = posX++;     // x轴累加
            tmpData[i] = qFromLittleEndian<qint32>(&tmp[i].data_w);
        }
        break;
    case DT_uint32_t :
        for(quint32 i=0; i<dataSize; i++){
            tmpPosX[i] = posX++;     // x轴累加
            tmpData[i] = qFromLittleEndian<quint32>(&tmp[i].data_uw);
        }
        break;
    case DT_float :
        for(quint32 i=0; i<dataSize; i++){
            tmpPosX[i] = posX++;     // x轴累加
            tmpData[i] = qFromLittleEndian<float>(&tmp[i].data_f);
        }
        break;
    default:break;
    }
    ui->customPlot->graph(0)->addData(tmpPosX, tmpData); // 将数据添加到图上
    this->resetAxisRange(posX,tmpData.at(tmpData.count()-1)); // 调整坐标轴

    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);
    dataBuf.clear();
}

/* 超时更新曲线,多条曲线显示处理 */
void SerialCurve::slots_multiPlotCurve()
{
    if(dataBuf.isEmpty()) return;// 数据缓存为空
    /* 删除所有空格 */
    QString tmp = dataBuf;
    tmp.remove(QRegExp("\\s"));
    dataBuf = tmp.toLatin1();
    /* 验证最后的数据为';',表示至少接收到一帧完整的数据 */
    if(dataBuf.endsWith(';')){ // 接收到完整的数据
        QRegExp reg("(\\d+=-?\\d+\\.?\\d*;)", Qt::CaseInsensitive);
        qint32 count = 0;
        qint32 pos = 0;
        // 遍历所有匹配的字符串
        while ((pos = reg.indexIn(dataBuf, pos)) != -1) {
            ++count;
            pos += reg.matchedLength();
            if(count>graphsCount) // 曲线数量与数据不匹配
                break;

            /* 解析字符串,以'='划分两部分 */
            QStringList valueData = reg.capturedTexts().at(0).split('='); // 划分为两部分有效数据
            qint32 graphNum = valueData.at(0).toInt();  // 第一部分是曲线编号
            QString strData = valueData.at(1);          // 第二部分是曲线数据

            strData.remove(';');  // 移除';'号
            float curveData = strData.toFloat();
            ui->customPlot->graph(graphNum)->addData(posX, curveData);
        }
        ui->customPlot->xAxis->setRange(posX+200, 1000, Qt::AlignRight);// 调整坐标轴 // Y轴不调整
        ui->customPlot->replot(QCustomPlot::rpQueuedReplot);
        posX++;
        dataBuf.clear();
    }
}
/* 串口接收数据,存储在dataBuf当中 */
void SerialCurve::slots_getRxBuf()
{
    QByteArray tmp = currentPort->readAll();
    dataBuf.append(tmp);
}

/* 多条曲线接收处理 */
void SerialCurve::slots_MultiPlotRxCallback()
{
    ui->statusBar->showMessage(tr("multi Rx"));
}

/* 重绘坐标轴的范围 */
void SerialCurve::resetAxisRange(double xAxis, double yAxis)
{
    ui->customPlot->xAxis->setRange(xAxis+200, 1000, Qt::AlignRight);
    QCPRange yRange = ui->customPlot->yAxis->range();
    if(yAxis > (yRange.upper)){
        yRange.upper = yAxis + 20;
        yRange.lower = yRange.upper - 100;
    }
    else if( yAxis < (yRange.lower)){
        yRange.lower = yAxis - 20;
        yRange.upper = yRange.lower + 100;
    }
    ui->customPlot->yAxis->setRange(yRange);
}
/* 暂停和继续绘图, 实际是停止定时器 */
void SerialCurve::on_actionPaused_triggered(bool checked)
{
    if(checked){
        if(timer.isActive()){
            timer.stop();
        }
    }else{
        if(!timer.isActive()){
            timer.start();
        }
    }
}
/* 清空曲线 */
void SerialCurve::on_actionClear_triggered()
{
    qint32 graphCounts = ui->customPlot->graphCount();
    qint32 i = 0;
    while( i < graphCounts){
        ui->customPlot->graph(i++)->data()->clear();
    }
    posX = 0;
    ui->customPlot->xAxis->setRange(0, 10, Qt::AlignCenter);
    ui->customPlot->yAxis->setRange(0, 10, Qt::AlignCenter);
    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);
}
/* 选择放大 */
void SerialCurve::on_actionSelect_triggered(bool checked)
{
    if(checked){
        ui->customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
    }else{
        ui->customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmNone);
    }
}

/* 保存图像 */
void SerialCurve::on_actionSaveImages_triggered()
{
    QFileDialog *fileDialog = this->initSaveFileDialog();

    QString fileName = nullptr;
    QString fileType = nullptr;

    if(fileDialog->exec() == QDialog::Accepted) {
        fileName = fileDialog->selectedFiles()[0]; // 文件名不包含文件类型(.png)
        fileType = fileDialog->selectedNameFilter();

        QRegExp reg("(\\.).*(\\))", Qt::CaseInsensitive);// 匹配 .png)
        reg.indexIn(fileType);
        fileType = reg.cap(0);
        fileType.chop(1);
        fileName += fileType;// 拼接文件名和文件类型
    }
    QFileInfo file(fileName);
    if(file.path() != "/")
    {
        qint32 count = fileDialog->layout()->count();
        QWidget *pWidget = fileDialog->layout()->itemAt(count-1)->widget();// 获取layout最后一个Widget的指针
        count = pWidget->children().count();
        QDoubleSpinBox *pScale = (QDoubleSpinBox *)pWidget->children().at(count-1);// 获取pWidget的子widget
        QSpinBox *pHeight = (QSpinBox *)pWidget->children().at(count-3);
        QSpinBox *pWidth  = (QSpinBox *)pWidget->children().at(count-5);
        qint32 width      = pWidth->value();
        qint32 height     = pHeight->value();
        double scale      = pScale->value();

        bool success = false;

        if(fileName.endsWith(".png")){
            success = ui->customPlot->savePng(fileName, width, height, scale, 100, 100);
        }else if(fileName.endsWith(".jpg")){
            success = ui->customPlot->saveJpg(fileName,width, height, scale,100,100);
        }else if(fileName.endsWith(".bmp")){
            success = ui->customPlot->saveBmp(fileName,width, height, scale,100);
        }else if(fileName.endsWith(".pdf")){
            success = ui->customPlot->savePdf(fileName,width, height, QCP::epAllowCosmetic,"ing10 SerialData","Curve");
        }

        if(success){
            QDesktopServices::openUrl(QUrl::fromLocalFile(file.path()));
        }else{
            QMessageBox::information(NULL, tr("SaveFiles"), tr("保存失败"));
        }

    }else{
        QMessageBox::information(NULL, tr("SaveFiles"), tr("请选择正确的路径"));
    }
    delete fileDialog;
}

/* 初始化配置保存文件对话框 */
QFileDialog * SerialCurve::initSaveFileDialog()
{
    QFileDialog *fileDialog = new QFileDialog();
    fileDialog->setOption(QFileDialog::DontUseNativeDialog,true); // 不使用本地的文件对话框

    QLabel *lblWidth = new QLabel("Width",fileDialog);  // 宽度
    QSpinBox *spbWidth = new QSpinBox(fileDialog);
    spbWidth->setMinimum(10);
    spbWidth->setMaximum(16777215);
    spbWidth->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spbWidth->setValue(ui->customPlot->width());

    QLabel *lblHeight = new QLabel("Height",fileDialog);// 高度
    QSpinBox *spbHeight  = new QSpinBox(fileDialog);
    spbHeight->setMinimum(10);
    spbHeight->setMaximum(16777215);
    spbHeight->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spbHeight->setValue(ui->customPlot->height());

    QLabel *lblScale = new QLabel("Scale",fileDialog);  // 缩放比例
    QDoubleSpinBox *spbScale  = new QDoubleSpinBox(fileDialog);
    spbScale->setMinimum(0);
    spbScale->setMaximum(16777215);
    spbScale->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spbScale->setValue(1);

    QHBoxLayout *hlayout = new QHBoxLayout(); // 新建布局图层
    hlayout->addWidget(lblWidth);             // 添加Widget
    hlayout->addWidget(spbWidth);
    hlayout->addWidget(lblHeight);
    hlayout->addWidget(spbHeight);
    hlayout->addWidget(lblScale);
    hlayout->addWidget(spbScale);
    hlayout->setSpacing(3);// 间隔为0

    QWidget *pWidget = new QWidget(fileDialog);
    QLabel *lblImagesSize = new QLabel("ImagesSize:",fileDialog); // 图像大小
    fileDialog->layout()->addWidget(lblImagesSize);// 添加Widget,整体添加两个Widget, pWidget另外包含4个Widget
    fileDialog->layout()->addWidget(pWidget);      //
    pWidget->setLayout(hlayout);

    fileDialog->setWindowTitle(tr("保存图像"));           // 对话框标题
    fileDialog->setAcceptMode(QFileDialog::AcceptSave); // 保存模式
    fileDialog->setViewMode(QFileDialog::List);         // 列表显示
    fileDialog->setLabelText(QFileDialog::Accept,"保存");// 按钮文本
    fileDialog->setLabelText(QFileDialog::Reject,"取消");

    fileDialog->setDirectory(".");
    QString filters="png(*.png);;jpg(*.jpg);;bmp(*.bmp);;pdf(*.pdf)";// 过滤类型
    fileDialog->setNameFilter(filters);
    fileDialog->setDirectory(qApp->applicationDirPath());// 默认路径
    return fileDialog;
}
void SerialCurve::on_actionCoorTips_triggered(bool checked)
{
    if(graphsCount == 0) return;
    if(checked){
        QPen linesPen(Qt::yellow, 1, Qt::DashLine);
        lineV = new QCPItemStraightLine(ui->customPlot);//垂直线
        lineV->setLayer("overlay");
        lineV->setPen(linesPen);
        lineV->setClipToAxisRect(true);
        lineV->setVisible(true);

        for(qint32 i=0; i<graphsCount;i++){
            QCPItemTracer *tracer = new QCPItemTracer(ui->customPlot);
            tracer->setStyle(QCPItemTracer::tsCircle);
            tracer->setPen(QColor(Qt::red));
            tracer->setBrush(Qt::NoBrush);
            tracer->position->setTypeX(QCPItemPosition::ptPlotCoords);
            tracer->position->setTypeY(QCPItemPosition::ptPlotCoords);
            tracer->setSize(6);
            tracer->setVisible(true);
            tracerPointArray<<tracer;

            QCPItemText *label = new QCPItemText(ui->customPlot);
//            label->setLayer("overlay");
            label->setClipToAxisRect(false);
            label->setPadding(QMargins(6, 6, 6, 6));
            label->setBrush(QColor(20,20,20,200));         //  颜色填充,半透明
//            label->setPen();       // 边框颜色
            label->position->setParentAnchor(tracer->position);
            label->setColor(ui->customPlot->graph(i)->pen().color());  // 字体颜色与曲线颜色一致
            label->setText("test");
            label->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);
            label->setVisible(true);
            lblGraph<<label;
        }
        connect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(slots_mouseMove(QMouseEvent*)));
    }else{
        ui->customPlot->disconnect(SIGNAL(mouseMove(QMouseEvent*)));

        lineV->setVisible(false);
        ui->customPlot->removeItem(lineV);

        foreach( QCPItemText *label, lblGraph ){
            label->setVisible(false);
            ui->customPlot->removeItem(label);
        }
        foreach( QCPItemTracer *tracer, tracerPointArray ){
            tracer->setVisible(false);
            ui->customPlot->removeItem(tracer);
        }

        lblGraph.clear();
        tracerPointArray.clear();
        ui->customPlot->replot(QCustomPlot::rpQueuedReplot);
    }
}
void SerialCurve::slots_mouseMove(QMouseEvent* event)
{
 //获取鼠标坐标点
    qint32 x_pos = event->pos().x();

// 把鼠标坐标点 转换为 QCustomPlot 内部坐标值 （pixelToCoord 函数）
// coordToPixel 函数与之相反 是把内部坐标值 转换为外部坐标点
    qint32 x_val = qRound(ui->customPlot->xAxis->pixelToCoord(x_pos));

// 然后打印在界面上
    lineV->point1->setCoords(x_val, 0);
    lineV->point2->setCoords(x_val, 2);

    double posAtGraph=0;
    qint32 i=0;
    foreach( auto tracer, tracerPointArray ){
        /* 跟随点 */
        auto iter = ui->customPlot->graph(i)->data()->findBegin(x_val+1);
        posAtGraph = iter->mainValue();
        tracer->position->setCoords( x_val, posAtGraph);

        /* 坐标说明 */
        auto label = lblGraph.at(i);
        label->position->setCoords( 5, 0);
        label->setText(tr("X:%1\nY:%2").arg(x_val).arg(posAtGraph));
        i++;
    }
    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);
//    ui->statusBar->showMessage(tr("(%1 ||  %2  %3  )").arg(x_pos).arg(x_val).arg(posAtGraph));
}
/* 修改曲线颜色 */
void SerialCurve::on_btnColorSel_clicked()
{
    qint32 index = ui->btnCurveSel->currentIndex();
    QColorDialog *colorDialog = new QColorDialog();
    colorDialog->setWindowTitle("选择颜色");
    QColor color = ui->btnColorSel->palette().background().color();
    color = colorDialog->getColor(color);
    if(color.isValid() ){
        ui->btnColorSel->setPalette(QPalette( color ));
        ui->btnColorSel->setStyleSheet(tr("background-color: %1").arg(color.name()));
        ui->customPlot->graph(index)->setPen(QPen(color));
        ui->customPlot->replot(QCustomPlot::rpQueuedReplot);
        /* 更新坐标点的颜色 */
        if( ui->actionCoorTips->isChecked() ){
            emit ui->actionCoorTips->triggered(false);
            emit ui->actionCoorTips->triggered(true);
        }
    }
}
/* 修改曲线名字 */
void SerialCurve::on_txtCurveRename_editingFinished()
{
    if(ui->customPlot->graphCount() == 0) return ;
    qint32 index = ui->btnCurveSel->currentIndex();
    QString newName = ui->txtCurveRename->text();
    ui->customPlot->graph(index)->setName(newName);
    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);
}

/* 显示使用说明文件 */
void SerialCurve::on_actionHelpFile_triggered()
{
    QString path = QDir::currentPath();
    path += "/helpFile.pdf";
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

