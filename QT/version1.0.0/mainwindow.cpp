#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{
    //拉曼光谱显示区域
}


void MainWindow::on_textBrowser_anchorClicked(const QUrl &arg1)
{
    //程序信息输出区域
}


void MainWindow::on_radioButton_clicked()
{
    //检测结果->正常组织
}


void MainWindow::on_radioButton_2_clicked()
{
    //检测结果->舌癌
}


void MainWindow::on_radioButton_3_clicked()
{
    //检测结果->颊癌
}


void MainWindow::on_radioButton_4_clicked()
{
    //检测结果->牙龈癌
}


void MainWindow::on_progressBar_valueChanged(int value)
{
    //检测结果->正常组织（置信度）
}


void MainWindow::on_progressBar_2_valueChanged(int value)
{
    //检测结果->舌癌(置信度)
}


void MainWindow::on_progressBar_3_valueChanged(int value)
{
    //检测结果->颊癌（置信度）
}


void MainWindow::on_progressBar_4_valueChanged(int value)
{
    //检测结果->牙龈癌（置信度）
}


void MainWindow::on_radioButton_5_clicked()
{
    //模型选择->alexnet
}


void MainWindow::on_radioButton_6_clicked()
{
    //模型选择->densenet
}


void MainWindow::on_radioButton_7_clicked()
{
    //模型选择->efficientnet
}


void MainWindow::on_radioButton_9_clicked()
{
    //模型选择->ghostnet
}


void MainWindow::on_radioButton_10_clicked()
{
    //模型选择->inception
}


void MainWindow::on_radioButton_8_clicked()
{
    //模型选择->mobilenet
}


void MainWindow::on_radioButton_12_clicked()
{
    //模型选择->resnet
}


void MainWindow::on_radioButton_13_clicked()
{
    //模型选择->shufflenet
}


void MainWindow::on_radioButton_11_clicked()
{
    //模型选择->squeezenet
}


void MainWindow::on_radioButton_15_clicked()
{
    //模型选择->transformer
}


void MainWindow::on_radioButton_16_clicked()
{
    //模型选择->vggnet
}


void MainWindow::on_radioButton_14_clicked()
{
    //模型选择->PCA+LDA
}


void MainWindow::on_radioButton_18_clicked()
{
    //模型选择->PCA+SVM
}


void MainWindow::on_radioButton_17_clicked()
{
    //模型选择->others(当且仅当本选项选中时，可以进行模型选择操作)
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    //用于显示本程序在选择others时所调用的文件路径（禁止写入，由下一个button按钮写入）
}


void MainWindow::on_pushButton_clicked()
{
    //模型选择:仅选择others时可用，将文件路径输出到lineedit中
}


void MainWindow::on_pushButton_2_clicked()
{
    //拉曼光谱仪->启动
}


void MainWindow::on_pushButton_3_clicked()
{
    //拉曼光谱仪->关闭
}


void MainWindow::on_pushButton_4_clicked()
{
    //拉曼光谱仪->导出文件
}


void MainWindow::on_pushButton_7_clicked()
{
    //拉曼光谱仪->波特率调节
}


void MainWindow::on_pushButton_5_clicked()
{
    //激光器->启动
}


void MainWindow::on_pushButton_6_clicked()
{
    //激光器->关闭
}


void MainWindow::on_pushButton_8_clicked()
{
    //激光器->设定积分时间
}


void MainWindow::on_pushButton_9_clicked()
{
    //激光器->设定激发波长
}


void MainWindow::on_pushButton_10_clicked()
{
    //激光器->设定距离
}


void MainWindow::on_pushButton_11_clicked()
{
    //离线模式->选择文件，调用所选的模型，识别，给出置信度，识别结果，并绘制出光谱图
}


void MainWindow::on_pushButton_12_clicked()
{
    //在线模式->一键检测，从拉曼光谱仪下载数据，调用选定的模型文件，识别，给出置信度，绘制出光谱图。
}


void MainWindow::on_pushButton_13_clicked()
{
    //在线模式->下载数据，从拉曼光谱一下载必要的数据，导出为csv文件
}


void MainWindow::on_pushButton_14_clicked()
{
    //在线模式->选择数据并识别，给出光谱图，置信度，识别结果
}


void MainWindow::on_radioButton_19_clicked()
{
    //模式选择->离线模式
}


void MainWindow::on_radioButton_20_clicked()
{
    //模式选择->在线模式
}


void MainWindow::on_action_save_data_normal_triggered()
{
    //菜单->导出数据
    QMessageBox::information(this,
                             tr("操作成功"),
                             tr("操作成功"),
                             QMessageBox::Ok);
    //上方代码是用于验证菜单栏是否响应的操作
}

