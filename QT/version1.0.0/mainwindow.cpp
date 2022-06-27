#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <stdlib.h>
#include <QFileDialog>
#include <Qdebug>

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

/*
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    //用于显示本程序在选择others时所调用的文件路径（禁止写入，由下一个button按钮写入）
    ui->lineEdit->setReadOnly(true);
}


void MainWindow::on_pushButton_clicked()
{
    //模型选择:仅选择others时可用，将文件路径输出到lineedit中
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("请选择文件"),
                                                    "C:",
                                                    tr("模型文件(*pt)"));
    qDebug()<<"filename="<<filename;
    if(filename=="")
    {
        QMessageBox::critical(this,
                              tr("错误"),
                              tr("未选择文件"),
                              QMessageBox::Ok);
    }
    else
    {
       //开启lineedit的写入
       ui->lineEdit->setReadOnly(false);
       ui->lineEdit->setText(filename);
       //关闭lineedit的写入
       ui->lineEdit->setReadOnly(true);
       QMessageBox::information(this,
                                tr("提示"),
                                tr("模型导入成功"),
                                QMessageBox::Ok);
    }
}
*/

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


void MainWindow::on_action_save_all_data_triggered()
{
    //菜单->导出文件全部信息
}


void MainWindow::on_action_input_file_triggered()
{
    //菜单->导入文件
}


void MainWindow::on_action_input_information_triggered()
{
    //菜单->导入病人信息
    //此处可用不隐藏当前窗口，直接在本窗口界面上方创建一个新的界面，用于后续操作
    window_input_information *main_input;
    main_input=new window_input_information();
    main_input->setWindowTitle("病人信息导入");
    main_input->show();
}


void MainWindow::on_action_show_information_triggered()
{
    //菜单->显示病人信息
}


void MainWindow::on_action_show_status_program_triggered()
{
    //菜单->显示程序目前参数以及状态
}


void MainWindow::on_action_clear_window_triggered()
{
    //菜单->程序屏幕状态清除
    ui->textBrowser->setText("程序已经完成当前状态清除");
    //清除图像显示区域
    ui->graphicsView->clearFocus();
    ui->graphicsView->clearMask();
    //清除程序状态输出
    ui->textBrowser->setText("程序已经完成当前状态清除");
    //清除检测结果
    ui->progressBar->setValue(25);
    ui->progressBar_2->setValue(25);
    ui->progressBar_3->setValue(25);
    ui->progressBar_4->setValue(25);
    ui->radioButton_21->click();
    //将4种检测结果的置信度重新设置为25%
    //模型选择部分不做出改动
    //关闭病人信息检测模块
    //主程序控制部分不做出改变
    QMessageBox::information(this,
                             tr("程序信息"),
                             tr("当前状态清除完成"),
                             QMessageBox::Ok);
    ui->textBrowser->setText("");
}


void MainWindow::on_action_exit_triggered()
{
    //菜单->安全退出本程序
    this->close();
    exit(0);
}


void MainWindow::on_action_self_check_triggered()
{
    //菜单->程序功能自检
    QFile file0("data.db");                 //存储光谱数据的数据库文件
    QFile file1("account.db");              //存储用户名和密码的数据库文件
    QFile file2("sqlite3.dll");             //操作数据库所需要的动态库连接文件
    QFile file3("D3Dcomplier_47.dll");      //动态库连接文件
    QFile file4("libgcc_s_seh-1.dll");      //动态库连接文件
    QFile file5("linstdc++-6.dll");         //动态库连接文件
    QFile file6("libwinpthread-1.dll");     //动态库连接文件
    QFile file7("opengl32sw.dll");          //动态库连接文件
    QFile file8("Qt6Core.dll");             //动态库连接文件
    QFile file9("Qt6Gui.dll");              //动态库连接文件
    QFile file10("Qt6Svg.dll");             //动态库连接文件
    QFile file11("Qt6Widgets.dll");         //动态库连接文件
    QFile file12("iconengines/qsvgicon.dll");   //动态库连接文件
    QFile file13("imageformats/qgit.dll");      //动态库连接文件
    QFile file14("imageformats/qico.dll");      //动态库连接文件
    QFile file15("imageformats/qjpeg.dll");     //动态库连接文件
    QFile file16("imageformats/qsvg.dll");      //动态库连接文件
    QFile file17("platforms/qwindows.dll");     //动态库连接文件
    QFile file18("styles/qwindowsvistastyle.dll");      //动态库连接文件
    /*********************************\
     * 下面是程序内置的模型文件
    \*********************************/

}


void MainWindow::on_action_program_information_triggered()
{
    QMessageBox::information(this,
                             tr("程序信息"),
                             tr("关于：\n应用拉曼光谱的口腔癌诊断系统\nversion1.0.0\nbuild22626\ncopyright (c) 2020~2022"),
                             QMessageBox::Ok);
    //菜单->程序信息
}


void MainWindow::on_action_visit_website_triggered()
{
    //菜单->转到程序官网

}


void MainWindow::on_textBrowser_historyChanged()
{
    //主界面->程序信息输出
}


void MainWindow::on_radioButton_21_clicked()
{
    //识别状态->保留
}

