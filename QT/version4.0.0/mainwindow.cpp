#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <stdlib.h>
#include <QFileDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <stdio.h>
#include <QInputDialog>
#include <Windows.h>


int Spectrograph=0;                   //值为0，光谱仪关闭，值为1，光谱仪启动
int laser=0;                          //值为0，激光器关闭，值为1，激光器启动
int Baud_rate=0;                      //储存连接的波特率，值为波特率（hz）
int Integral_time=0;                  //积分时间设定，值为积分时间(ms)
int Excitation_wavelength=0;          //激发波长设定，值为激发波长(nm)
int Distance=0;                       //激发距离设定，值为激发距离(mm)
int mode_choose=0;                    //模式选择，值为0，离线模式，值为1，在线模式，值为2，自动检测模式（连接成功后自动切换为1，否则切换为0）
int choose_model=0;                   //模型选择，值为(14~18,前13个保留<也可以调用模型>)14->mobilenet15->resnet5016->transformer17->vgg18->inception
int rec_result=0;                     //识别结果，值为(0~4)0->没有检测出结果1->正常组织，2->舌癌，3->颊癌，4->牙龈癌;(-1=程序出错，无法调用模型)

//上述变量为全局变量
//下面开始进行程序的启动初始化操作
bool __init__(void)                     //程序初始化
{
    Spectrograph=0;
    laser=0;
    Baud_rate=0;
    Integral_time=0;
    Excitation_wavelength=0;
    Distance=0;
    mode_choose=0;
    choose_model=0;
    rec_result=0;
    if(!Spectrograph&&!laser&&!Baud_rate&&!Integral_time&&!Excitation_wavelength&&!Distance&&!mode_choose&&!choose_model&&!rec_result)
    {
        return true;
    }
    return false;
}

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
    FILE* f1=fopen("account.db","rb");
    if(f1==NULL)
    {
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("光谱仪无法启动:0X01,未找到相关dll文件"),
                                 QMessageBox::Ok);
    }
    else
    {
        //break;
        //等待相关的动态库链接文件
        int flag;
        flag=1;
        if(flag==0)
        {
            //操作失败
            QMessageBox::information(this,
                                     tr("提示"),
                                     tr("光谱仪无法启动：0x02,未知原因"),
                                     QMessageBox::Ok);
        }
        else
        {
            //操作成功
            QMessageBox::information(this,
                                     tr("提示"),
                                     tr("光谱仪启动成功，可以进行下一步操作"),
                                     QMessageBox::Ok);
            ui->pushButton_3->setEnabled(true);
            ui->pushButton_4->setEnabled(true);
            ui->pushButton_7->setEnabled(true);
            ui->pushButton_5->setEnabled(true);
            ui->pushButton_2->setEnabled(false);
        }
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    //拉曼光谱仪->关闭
    FILE* f1=fopen("account.db","rb");
    if(f1==NULL)
    {
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("光谱仪无法关闭:0X01,未找到相关dll文件"),
                                 QMessageBox::Ok);
    }
    else
    {
        //break;
        //等待相关的动态库链接文件
        int flag;
        flag=1;
        if(flag==0)
        {
            //操作失败
            QMessageBox::information(this,
                                     tr("提示"),
                                     tr("光谱仪无法关闭：0x02,未知原因"),
                                     QMessageBox::Ok);
        }
        else
        {
            //操作成功
            QMessageBox::information(this,
                                     tr("提示"),
                                     tr("光谱仪关闭成功<由于安全原因，自动关闭激光器>，可以进行下一步操作"),
                                     QMessageBox::Ok);
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_4->setEnabled(false);
            ui->pushButton_7->setEnabled(false);
            ui->pushButton_5->setEnabled(false);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton_6->setEnabled(false);
            ui->pushButton_8->setEnabled(false);
            ui->pushButton_9->setEnabled(false);
            ui->pushButton_10->setEnabled(false);
            ui->pushButton_5->setEnabled(false);
        }
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    //拉曼光谱仪->导出文件
    QMessageBox::information(this,
                             tr("文件导出成功"),
                             tr("文件导出成功"),
                             QMessageBox::Ok);
}


void MainWindow::on_pushButton_7_clicked()
{
    //拉曼光谱仪->波特率调节
    bool bOk=false;
    int rate=QInputDialog::getInt(this,
                                  "请输入波特率",
                                  "请输入波特率Hz",
                                  86400,
                                  0,
                                  100000000,
                                  1,
                                  &bOk);
    if(bOk&&rate>0)
    {
        //此处等待动态链接库文件
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    //激光器->启动
    FILE* f1=fopen("account.db","rb");
    if(f1==NULL)
    {
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("激光器无法启动:0X01,未找到相关dll文件"),
                                 QMessageBox::Ok);
    }
    else
    {
        //break;
        //等待相关的动态库链接文件
        int flag;
        flag=1;
        if(flag==0)
        {
            //操作失败
            QMessageBox::information(this,
                                     tr("提示"),
                                     tr("激光器无法启动：0x02,未知原因"),
                                     QMessageBox::Ok);
        }
        else
        {
            //操作成功
            QMessageBox::information(this,
                                     tr("提示"),
                                     tr("激光器启动成功，可以进行下一步操作"),
                                     QMessageBox::Ok);
            ui->pushButton_6->setEnabled(true);
            ui->pushButton_8->setEnabled(true);
            ui->pushButton_9->setEnabled(true);
            ui->pushButton_10->setEnabled(true);
            ui->pushButton_5->setEnabled(false);
        }
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    //激光器->关闭
    FILE* f1=fopen("account.db","rb");
    if(f1==NULL)
    {
        QMessageBox::information(this,
                                 tr("提示"),
                                 tr("激光器无法关闭:0X01,未找到相关dll文件"),
                                 QMessageBox::Ok);
    }
    else
    {
        //break;
        //等待相关的动态库链接文件
        int flag;
        flag=1;
        if(flag==0)
        {
            //操作失败
            QMessageBox::information(this,
                                     tr("提示"),
                                     tr("激光器无法关闭：0x02,未知原因"),
                                     QMessageBox::Ok);
        }
        else
        {
            //操作成功
            QMessageBox::information(this,
                                     tr("提示"),
                                     tr("激光器关闭成功，可以进行下一步操作"),
                                     QMessageBox::Ok);
            ui->pushButton_6->setEnabled(false);
            ui->pushButton_8->setEnabled(false);
            ui->pushButton_9->setEnabled(false);
            ui->pushButton_10->setEnabled(false);
            ui->pushButton_5->setEnabled(true);
        }
    }
}


void MainWindow::on_pushButton_8_clicked()
{
    //激光器->设定积分时间
    bool bOk=false;
    int rate=QInputDialog::getInt(this,
                                  "请输入积分时间",
                                  "请输入积分时间ms",
                                  2000,
                                  0,
                                  100000000,
                                  1,
                                  &bOk);
    if(bOk&&rate>0)
    {
        //此处等待动态链接库文件
    }
}


void MainWindow::on_pushButton_9_clicked()
{
    //激光器->设定激发波长
    bool bOk=false;
    int rate=QInputDialog::getInt(this,
                                  "请输入激发波长",
                                  "请输入激发波长nm",
                                  86400,
                                  0,
                                  100000000,
                                  1,
                                  &bOk);
    if(bOk&&rate>0)
    {
        //此处等待动态链接库文件
    }
}


void MainWindow::on_pushButton_10_clicked()
{
    //激光器->设定距离
    bool bOk=false;
    int rate=QInputDialog::getInt(this,
                                  "请输入距离",
                                  "请输入距离mm",
                                  2,
                                  0,
                                  100000000,
                                  1,
                                  &bOk);
    if(bOk&&rate>0)
    {
        //此处等待动态链接库文件
    }
}


void MainWindow::on_pushButton_11_clicked()
{
    int mode_python_environment=-1;         //是否有python环境
    int mode_exe_draw=-1;                   //是否有绘图专用的exe文件
    int mode_python_script=-1;              //是否识别到python脚本
    int mode_model_choose=-1;               //模型状态选择
    int draw_is_ok=-1;                      //判断绘图是否完成
    int prepare_ok=0;                       //判断是否准备就绪
    qDebug()<<"0";
    //离线模式->选择文件，调用所选的模型，识别，给出置信度，识别结果，并绘制出光谱图
    int ans;
    //ans =system("pip");
    ans=WinExec("pip",SW_HIDE);
    qDebug()<<"ans="<<ans;
    if(ans<=32)
    {
        mode_python_environment=0;          //用户没有python 环境
    }
    else
    {
        mode_python_environment=1;          //用户电脑上有python 环境
    }
    //python环境测试完成
    qDebug()<<"1";
    FILE* f1=fopen("draw_picture\\draw_picture.exe","rb");
    if(f1==NULL)
    {
        //用户电脑上draw_picture.exe文件不存在
        mode_exe_draw=0;                    //用户电脑上没有draw_picture.exe文件
    }
    else
    {
        mode_exe_draw=1;                    //用户电脑上存在draw_picture.exe文件
        fclose(f1);
    }
    qDebug()<<"2";
    FILE* f2=fopen("python_script\\draw_picture.py","rb");
    qDebug()<<"3";
    if(f2==NULL)
    {
        //用户电脑上面不存在draw_picture.py文件
        mode_python_script=0;
        qDebug()<<"3";
    }
    else
    {
        //用户电脑上面存在draw_picture.py文件
        mode_python_script=1;
        qDebug()<<"3";
        fclose(f2);
        qDebug()<<"3";
    }
    qDebug()<<"3";
    FILE* f3=fopen("main_model.dll","rb");
    if(f3==NULL)
    {
        //用户电脑上没有main+_model.dll文件
        mode_model_choose=-2;
    }
    else
    {
        //用户电脑上有main_model.dll文件
        fclose(f3);
    }
    qDebug()<<"4";
    if(mode_python_environment==0||(mode_python_environment==1&&mode_python_script==0))
    {
        //无法使用python脚本
        if(mode_exe_draw==0)
        {
            //无法绘图
            QMessageBox::critical(this,
                                  tr("错误"),
                                  tr("本程序无法进行绘图操作\n重新安装本程序可能会解决本问题"),
                                  QMessageBox::Ok);
            prepare_ok=0;
            qDebug()<<"5";
        }
        else
        {
            //让用户选择待识别的csv文件
            prepare_ok=1;
            qDebug()<<"6";
        }
    }
    else
    {
        //可以使用python脚本
        prepare_ok=2;
        qDebug()<<"7";
    }
    if(prepare_ok==0)
    {
        //无操作
        qDebug()<<"8";
    }
    else if(prepare_ok==1)
    {
        //ans=WinExec("",SW_HIDE);
        //文件对话框
        qDebug()<<"9";
        QString fileName=QFileDialog::getOpenFileName(this,
                                                      tr("选择文件"),
                                                      tr("C:"),
                                                      tr("逗号分隔符文件(*csv)"));
        qDebug()<<"filename="<<fileName;
        //开始执行
        char ch0[100]={'\0'};
        char ch1[]=".\\draw_picture\\draw_picture.exe ";
        char *ch2;
        QByteArray ba=fileName.toLatin1();
        ch2=ba.data();
        strcpy(ch0,ch1);
        strcat(ch0,ch2);
        ans=WinExec(ch0,SW_HIDE);
        if(ans<32)
        {
            QMessageBox::information(this,
                                     tr("提示"),
                                     tr("本程序出现异常，无法完成识别绘制操作"),
                                     QMessageBox::Ok);
        }
    }
    else if(prepare_ok==2)
    {
        //ans=WinExec("",SW_HIDE);
        //文件对话框
        qDebug()<<"10";
        QString fileName=QFileDialog::getOpenFileName(this,
                                                      tr("选择文件"),
                                                      tr("C:"),
                                                      tr("逗号分隔符文件(*csv)"));
        qDebug()<<"filename="<<fileName;
        char ch3[100]={'\0'};
        char ch4[]="python .\\python_script\\draw_picture.py ";
        char *ch5;
        QByteArray ba=fileName.toLatin1();
        ch5=ba.data();
        strcpy(ch3,ch4);
        strcat(ch3,ch5);
        ans=WinExec(ch3,SW_HIDE);
        qDebug()<<"ans="<<ans;
        qDebug()<<"command="<<ch3;
        if(ans<32)
        {
            QMessageBox::information(this,
                                     tr("提示"),
                                     tr("本程序出现异常，无法完成识别绘制操作"),
                                     QMessageBox::Ok);
        }
    }
    if(prepare_ok!=0)
    {
        int i=0;
        FILE* f5=fopen("data.png","rb");
        while(f5==NULL)
        {
            for(i=0;i<10000;i++)
            {
                qDebug()<<"i="<<i;
            }
            f5=fopen("data.png","rb");
        }
        fclose(f5);
        //加载图片
        QImage *img=new QImage("data.png");
        img->scaled(ui->label->size(),Qt::IgnoreAspectRatio);
        ui->label->setScaledContents(true);
        ui->label->setPixmap(QPixmap::fromImage(*img));
    }
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
    if(__init__()==false)
    {
        QMessageBox::critical(this,
                              tr("提示"),
                              tr("系统错误，程序无法完成初始化操作，请检查内存是否出现故障"),
                              QMessageBox::Ok);
    }
    ui->textBrowser->setText("程序已经完成当前状态清除");
    //清除图像显示区域
    ui->graphicsView->clearFocus();
    ui->graphicsView->clearMask();
    QImage *img=new QImage("white.png");
    img->scaled(ui->label->size(),Qt::IgnoreAspectRatio);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap::fromImage(*img));
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
    system("start https://github.com/lry-123456789/Oral-cancer-diagnosis-system-using-Raman-spectroscopy");
}


void MainWindow::on_textBrowser_historyChanged()
{
    //主界面->程序信息输出

}


void MainWindow::on_radioButton_21_clicked()
{
    //识别状态->保留
}


void MainWindow::on_radioButton_22_clicked()
{
    //mobilenet
}


void MainWindow::on_radioButton_23_clicked()
{
    //resnet50
}


void MainWindow::on_radioButton_24_clicked()
{
    //transformer
}


void MainWindow::on_radioButton_25_clicked()
{
    //vgg
}


void MainWindow::on_radioButton_26_clicked()
{
    //inception
}


void MainWindow::on_label_linkActivated(const QString &link)
{

}


void MainWindow::on_label_linkHovered(const QString &link)
{

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    int x,y;
    x=this->frameGeometry().width();
    y=this->frameGeometry().height();
    qDebug()<<"x="<<x<<"y="<<y;
    //ui->textBrowser->setText("resize the window to ");
    ui->textBrowser->setText("");
    ui->textBrowser->insertPlainText(QString::number(x));
    ui->textBrowser->insertPlainText(",");
    ui->textBrowser->insertPlainText(QString::number(y));
    /****\
     * 上方为获取窗口大小的操作
    \****/
    //下面开始设置控件的大小
    ui->groupBox->setGeometry(10,10,x*561/1200,y*431/631);
    ui->graphicsView->setGeometry(10,20,x*541/1200,y*401/631);
    ui->label->setGeometry(10,20,x*541/1200,y*401/631);
    //第一个GroupBox大小自适应调节完成
    //下面开始调节第二个GroupBox的大小自适应
    ui->groupBox_12->setGeometry(10,440*y/631,561*x/1200,111*y/631);
    ui->textBrowser->setGeometry(10,20,541*x/1200,81*y/631);
    //第二个GroupBox大小自适应调节完成
    //下面开始调节第三个GroupBox的大小自适应
    ui->groupBox_2->setGeometry(580*x/1200,10,601*x/1200,161*y/631);
    ui->radioButton->setGeometry(10,10,95*x/1200,20*y/631);
    ui->radioButton_2->setGeometry(180*x/1200,10,95*x/1200,20*y/631);
    ui->radioButton_3->setGeometry(340*x/1200,10,95*x/1200,20*y/631);
    ui->radioButton_4->setGeometry(490*x/1200,10,95*x/1200,20*y/631);
    ui->progressBar->setGeometry(30*x/1200,40*y/631,61*x/1200,101*y/631);
    ui->progressBar_2->setGeometry(200*x/1200,40*y/631,61*x/1200,101*y/631);
    ui->progressBar_3->setGeometry(360*x/1200,40*y/631,61*x/1200,101*y/631);
    ui->progressBar_4->setGeometry(510*x/1200,40*y/631,61*x/1200,101*y/631);
    //设置隐藏部分
    ui->radioButton_21->setGeometry(650*x/1200,40*y/631,61*x/1200,101*y/631);
    //GroupBox2隐藏部分
    ui->label_5->setGeometry(0,80*y/631,21*x/1200,16*y/631);
    ui->label_6->setGeometry(10,30*y/631,21*x/1200,16*y/631);
    ui->label_7->setGeometry(10,130*y/631,21*x/1200,16*y/631);
    ui->label_8->setGeometry(170*x/1200,80*y/631,21*x/1200,16*y/631);
    ui->label_9->setGeometry(180*x/1200,30*y/631,21*x/1200,16*y/631);
    ui->label_10->setGeometry(180*x/1200,130*y/631,21*x/1200,16*y/631);
    ui->label_11->setGeometry(330*x/1200,80*y/631,21*x/1200,16*y/631);
    ui->label_12->setGeometry(340*x/1200,30*y/631,21*x/1200,16*y/631);
    ui->label_13->setGeometry(340*x/1200,130*y/631,21*x/1200,16*y/631);
    ui->label_14->setGeometry(480*x/1200,80*y/631,21*x/1200,16*y/631);
    ui->label_15->setGeometry(490*x/1200,30*y/631,21*x/1200,16*y/631);
    ui->label_16->setGeometry(490*x/1200,130*y/631,21*x/1200,16*y/631);
    //GroupBox2部分设定完成
    //准备第四个部分的设定
    ui->groupBox_3->setGeometry(580*x/1200,160*y/631,601*x/1200,391*y/631);
    //开始准备第五个部分的设定
    ui->groupBox_4->setGeometry(10,20,581*x/1200,151*y/631);
    //开始准备功能区域
    ui->radioButton_5->setGeometry(790*x/1200,20*y/631,95*x/1200,20*y/631);
    ui->radioButton_6->setGeometry(710*x/1200,20*y/631,95*x/1200,20*y/631);
    ui->radioButton_7->setGeometry(630*x/1200,20*y/631,95*x/1200,20*y/631);
    ui->radioButton_8->setGeometry(790*x/1200,70*y/631,95*x/1200,70*y/631);
    ui->radioButton_9->setGeometry(710*x/1200,110*y/631,95*x/1200,70*y/631);
    ui->radioButton_10->setGeometry(630*x/1200,50*y/631,95*x/1200,20*y/631);
    ui->radioButton_11->setGeometry(710*x/1200,50*y/631,95*x/1200,20*y/631);
    ui->radioButton_12->setGeometry(710*x/1200,70*y/631,95*x/1200,70*y/631);
    ui->radioButton_13->setGeometry(630*x/1200,70*y/631,95*x/1200,20*y/631);
    ui->radioButton_14->setGeometry(790*x/1200,110*y/631,95*x/1200,20*y/631);
    ui->radioButton_15->setGeometry(790*x/1200,50*y/631,95*x/1200,20*y/631);
    ui->radioButton_16->setGeometry(790*x/1200,90*y/631,95*x/1200,20*y/631);
    ui->radioButton_17->setGeometry(710*x/1200,90*y/631,95*x/1200,20*y/631);
    ui->radioButton_18->setGeometry(630*x/1200,90*y/631,95*x/1200,20*y/631);
    ui->radioButton_22->setGeometry(10*x/1200,70*y/631,95*x/1200,20*y/631);
    ui->radioButton_23->setGeometry(140*x/1200,70*y/631,95*x/1200,20*y/631);
    ui->radioButton_24->setGeometry(260*x/1200,70*y/631,95*x/1200,20*y/631);
    ui->radioButton_25->setGeometry(370*x/1200,70*y/631,95*x/1200,20*y/631);
    ui->radioButton_26->setGeometry(470*x/1200,70*y/631,95*x/1200,20*y/631);
    //第五个部分设定完成
    //开始准备第六个功能区域
    ui->groupBox_5->setGeometry(10,170*y/631,591*x/1200,131*y/631);
    //准备第七个功能区域
    ui->groupBox_6->setGeometry(10,20*y/631,571*x/1200,51*y/631);
    ui->pushButton_2->setGeometry(10*x/1200,20*y/631,75*x/1200,24*y/631);
    ui->pushButton_3->setGeometry(170*x/1200,20*y/631,75*x/1200,24*y/631);
    ui->pushButton_4->setGeometry(330*x/1200,20*y/631,75*x/1200,24*y/631);
    ui->pushButton_7->setGeometry(480*x/1200,20*y/631,75*x/1200,24*y/631);
    //准备第八个功能区域
    ui->groupBox_7->setGeometry(10*x/1200,70*y/631,571*x/1200,51*y/631);
    ui->pushButton_5->setGeometry(10*x/1200,20*y/631,75*x/1200,24*y/631);
    ui->pushButton_6->setGeometry(120*x/1200,20*y/631,75*x/1200,24*y/631);
    ui->pushButton_8->setGeometry(230*x/1200,20*y/631,81*x/1200,24*y/631);
    ui->pushButton_9->setGeometry(350*x/1200,20*y/631,91*x/1200,24*y/631);
    ui->pushButton_10->setGeometry(480*x/1200,20*y/631,75*x/1200,24*y/631);
    //准备第九个功能区域
    ui->groupBox_8->setGeometry(10*x/1200,300*y/631,591*x/1200,80*y/631);
    //准备第十个功能区域
    ui->groupBox_9->setGeometry(460*x/1200,10*y/631,120*x/1200,61*y/631);
    ui->radioButton_19->setGeometry(10*x/1200,20*y/631,95*x/1200,20*y/631);
    ui->radioButton_20->setGeometry(10*x/1200,40*y/631,95*x/1200,20*y/631);
    //准备第十一个功能区域
    ui->groupBox_10->setGeometry(10*x/1200,20*y/631,120*x/1200,51*y/631);
    ui->pushButton_11->setGeometry(10*x/1200,20*y/631,101*x/1200,24*y/631);
    //准备第十二个功能区域
    ui->groupBox_11->setGeometry(170*x/1200,20*y/631,281*x/1200,51*y/631);
    ui->pushButton_12->setGeometry(40*x/1200,20*y/631,75*x/1200,24*y/631);
    ui->pushButton_13->setGeometry(170*x/1200,20*y/631,75*x/1200,24*y/631);
}
