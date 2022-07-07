#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "main_1_0_0_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    /*
    MainWindow w;
    w.show();
    return a.exec();
    */
    //弃用原主界面
    //使用登录界面
    window_login login_program;
    login_program.show();
    login_program.setWindowTitle("登录到应用拉曼光谱的口腔癌诊断系统");
    return a.exec();
}
