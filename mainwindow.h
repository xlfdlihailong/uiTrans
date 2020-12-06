#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "qlib/qlib.h"
namespace Ui {
class MainWindow;
}
class pscp
{
public:
    pscp(pstring host,pstring user,pstring pwd)
    {
        this->host=host;
        this->user=user;
        this->pwd=pwd;
    }
    //线程下载,支持文件夹
    void downloadThread(pstring strFullPathLocal,pstring strFullPathRemote,std::function<void(pstring)> fun)
    {
        std::thread pthUploadFile(
                    &pscp::download,this,strFullPathLocal,strFullPathRemote,fun);
        pthUploadFile.detach();
    }
    //普通下载,支持文件夹
    void download(pstring strFullPathLocal,pstring strFullPathRemote,std::function<void(pstring)> fun)
    {
        pstring cmd="pscp.exe -r -l "+this->user+" -pw "+this->pwd+" "+this->host+":"+strFullPathRemote+" "+strFullPathLocal;
        hlog(cmd);
        hlog(plib::toChinese(cmd));
        //hlog(plib::getCmdOutputFun("pscp.exe -l root -pw sjcsfwq 106.12.222.93:/root/VNC-Server-6.7.2-Linux-x64-ANY.tar.gz C:/Users/Administrator/Desktop",fun));
        (plib::getCmdOutputFun(cmd,fun));
    }
    //线程上传,支持文件夹
    void uploadThread(pstring strFullPathLocal,pstring strFullPathRemote,std::function<void(pstring)> fun)
    {
        std::thread pthUploadFile(
                    &pscp::upload,this,strFullPathLocal,strFullPathRemote,fun);
        pthUploadFile.detach();
    }
    //普通上传,支持文件夹
    void upload(pstring strFullPathLocal,pstring strFullPathRemote,std::function<void(pstring)> fun)
    {
        pstring cmd="pscp.exe -r -l "+this->user+" -pw "+this->pwd+" "+strFullPathLocal+" "+this->host+":"+strFullPathRemote;
        hlog(cmd);
        (plib::getCmdOutputFun(cmd,fun));
    }

private:
    pstring host;
    pstring pwd;
    pstring user;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showstr(pstring str);
private slots:

    void on_pushButton_clicked();
    void slotDoubleClickRemote(int row,int col);
    void slotDoubleClickLocal(int row,int col);
    void on_pushButtonupdatelocal_clicked();

    void on_pushButton_3_clicked();
    void slotDelLocal();
    void slotDelRemote();
    void slotUpload();
    void slotDownload();

    void slotRenameLocal();
    void slotRenameRemote();

    void on_textBrowser_textChanged();
    void slotShowJindu(QString jindu);
signals:
    void sigShowJindu(QString jindu);
private:
    bool bloop=true;

    void createConnection();
    Ui::MainWindow *ui;

    pstring strpwdremote="/root";
    pstring strpwdlocal="C:/Users/Administrator/Desktop";
    pstring host="106.12.222.93";
//    pstring host="192.168.72.156";
    pstring pwd="npants0703***";
    //    pstring host="106.13.131.240";
    //    pstring pwd="sjcsfwq";
    //    pstring host="172.16.11.6";
    //    pstring pwd="scfwq_325";
    void showbyPathRemoteLinux();
    void showbyPathLocalWin();
    pscp* ptrans;
    //统一名称,包括map,表头
    pstring strtype="类型";
    pstring strname="名称";
    pstring strsize="大小";
    QAction* pActionDelLocal;
    QAction* pActionDelRemote;
    QAction* pActionUpload;
    QAction* pActionDownload;
    QAction* pActionRenameLocal;
    QAction* pActionRenameRemote;
};

#endif // MAINWINDOW_H
