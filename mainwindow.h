#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTreeWidgetItem>
#include "qlib/qlib.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showstr(pstring str);
    pmap<pstring,pstring> mall;//host and pwd
private slots:

    void slotDoubleClickRemote(int row,int col);
    void slotDoubleClickLocal(int row,int col);


    void slotDelLocal();
    void slotDelRemote();
    void slotUpload();
    void slotDownload();

    void slotRenameLocal();
    void slotRenameRemote();

    void on_textBrowser_textChanged();
    void slotShowJindu(QString jindu);
    void slotClickTree(QTreeWidgetItem *item, int column);
    void slotMessageBox(QString info);
    //耗时的放这里面防止界面卡顿
    void threadLinux();
signals:
    void sigShowJindu(QString jindu);
    void sigMessageBox(QString info);
    void sigTextBrowser(QString info);
    void sigLineText(QString info);
    void sigShowTable(plist<pmap<pstring, pstring> > lmdata, int keyid);
    void sigClearLocal();
    void sigClearRemote();
private:
    bool bloop=true;

    void createConnection();
    Ui::MainWindow *ui;

    pstring strpwdremote="/root";
    pstring strpwdlocal="C:/Users/Administrator/Desktop";
    pstring host="106.12.222.93";
//    pstring host="192.168.72.156";
    pstring pwd="npants0703***";
    int port=22;
    //    pstring host="106.13.131.240";
    //    pstring pwd="sjcsfwq";
    //    pstring host="172.16.11.6";
    //    pstring pwd="scfwq_325";

    bool threadShowbyPathRemoteLinux();
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
