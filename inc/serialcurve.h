#ifndef SIMPLEOSCILLOSCOPE_H
#define SIMPLEOSCILLOSCOPE_H

#include <QMainWindow>
#include "baseserialcomm.h"
#include "qcustomplot.h"
#include "QMessageBox"
#include "QButtonGroup"

namespace Ui {
class SerialCurve;
}

class SerialCurve : public QMainWindow
{
    Q_OBJECT

public:
    explicit SerialCurve(QWidget *parent = 0);
    ~SerialCurve();

    const QColor colorTable[20] = {
        QColor("#FB0873"), QColor("#3AFFF0"),QColor("#F8CF45"),QColor("#A553A8"),
        QColor("#87FF8D"), QColor("#F7595B"),QColor("#55C6DE"),QColor("#E8FF4C"),
        QColor("#E4008A"), QColor("#5AFFCA"),QColor("#F7A148"),QColor("#817FBC"),
        QColor("#AAFF6C"), QColor("#F62869"),QColor("#4EF1F5"),QColor("#FAE947"),
        QColor("#BE349B"), QColor("#71FFA1"),QColor("#F77550"),QColor("#62ACD2")};

    typedef struct {
        bool isActive = false;
        qint32 size = 0;// 1~3
        uint8_t data[3];
    }DataBuffer;
    enum DataType{
        DT_uint8_t = 0,
        DT_uint16_t = 1,
        DT_uint32_t = 2,
        DT_int8_t = 3,
        DT_int16_t = 4,
        DT_int32_t = 5,
        DT_float = 6,
    };
    Q_ENUM(DataType)

    DataType dataType = DT_uint8_t; // 曲线数据点 类型
    QByteArray dataBuf;
    double posX = 0;
    qint32 graphsCount = 0;

    void initComboBox_Config();
    void configPort();
    void initPlot();
    void configSinglePlot();
    void configMultiPlot();
    void addNewGraph();
    QFileDialog *initSaveFileDialog();
    void resetAxisRange(double xAxis, double yAxis);

signals:

public slots :
    void slots_MultiPlotRxCallback();
    void slots_errorHandler(QSerialPort::SerialPortError error);
    void slots_getRxBuf();

    void slots_singlePlotByte();  // a Byte
    void slots_singlePlotHMByte();  // half word
    void slots_singlePlotMByte(); // multi Byte
    void slots_mouseMove(QMouseEvent* event);
    void slots_multiPlotCurve(); // 绘制多条曲线


private slots:
    void on_btnRefresh_clicked();

    void on_btnOpenPort_clicked(bool checked);

    void on_rdbSinglePlot_clicked(bool checked);

    void on_rdbMultiPlot_clicked(bool checked);

    void on_spbNumberG_editingFinished();

    void on_cbbDataType_currentIndexChanged(int index);

    void on_actionClear_triggered();

    void on_actionSaveImages_triggered();

    void on_actionPaused_triggered(bool checked);

    void on_actionSelect_triggered(bool checked);

    void on_actionCoorTips_triggered(bool checked);

    void on_btnCurveSel_currentIndexChanged(int index);

    void on_btnColorSel_clicked();

    void on_txtCurveRename_editingFinished();

    void on_actionHelpFile_triggered();

private:
    Ui::SerialCurve *ui;
    BaseSerialComm *currentPort;   // 端口号
    QButtonGroup *rdbGroup;
    QTimer timer;
    QCPItemStraightLine *  lineV; // 垂直线
    QList<QCPItemTracer *> tracerPointArray;//跟踪的点
    QList<QCPItemText *>   lblGraph; // 显示曲线值
};

#endif // MAINWINDOW_H
