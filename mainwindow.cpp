#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QStorageInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qlog(plib::pwd());
    this->setWindowTitle("linux远程工具");
    ui->ptree->addRoot("服务器列表");
    plib::setPathConf("host.conf");
    int count=0;
    while(1)
    {
        count++;
        pstring host=plib::getConfString("basic","host"+plib::toString(count));
        if(host=="")
            break;
        pstring pwd=plib::getConfString("basic","pwd"+plib::toString(count));
        hlog(host,pwd);
        mall.add(host,pwd);
        auto jointnew=ui->ptree->newJoint(host.c_str());
        ui->ptree->root()->addChild(jointnew);
    }
    ui->ptree->expandAll();
    hlog(mall);

    pActionDelLocal=new QAction("删除",this);
    ui->ptablelocal->addAction(pActionDelLocal);
    connect(pActionDelLocal,SIGNAL(triggered(bool)),this,SLOT(slotDelLocal()));
    pActionDelRemote=new QAction("删除",this);
    ui->ptableRemote->addAction(pActionDelRemote);
    connect(pActionDelRemote,SIGNAL(triggered(bool)),this,SLOT(slotDelRemote()));
    pActionUpload=new QAction("上传",this);
    ui->ptablelocal->addAction(pActionUpload);
    connect(pActionUpload,SIGNAL(triggered(bool)),this,SLOT(slotUpload()));
    pActionDownload=new QAction("下载",this);
    ui->ptableRemote->addAction(pActionDownload);
    connect(pActionDownload,SIGNAL(triggered(bool)),this,SLOT(slotDownload()));
    pActionRenameLocal=new QAction("重命名",this);
    ui->ptablelocal->addAction(pActionRenameLocal);
    connect(pActionRenameLocal,SIGNAL(triggered(bool)),this,SLOT(slotRenameLocal()));
    pActionRenameRemote=new QAction("重命名",this);
    ui->ptableRemote->addAction(pActionRenameRemote);
    connect(pActionRenameRemote,SIGNAL(triggered(bool)),this,SLOT(slotRenameRemote()));
    connect(ui->ptree,SIGNAL(sigClick(QTreeWidgetItem*,int)),this,SLOT(slotClickTree(QTreeWidgetItem*,int)));

    connect(this,SIGNAL(sigMessageBox(QString)),this,SLOT(slotMessageBox(QString)));
    connect(this,SIGNAL(sigTextBrowser(QString)),ui->textBrowser,SLOT(append(QString)));
    connect(this,SIGNAL(sigLineText(QString)),ui->lineEditHostpwd,SLOT(setText(QString)));
    connect(this,SIGNAL(sigShowTable(plist<pmap<pstring,pstring> >,int)),ui->ptableRemote,SLOT(slotUpdateTable(plist<pmap<pstring,pstring> >,int)));
    connect(this,SIGNAL(sigClearLocal()),ui->ptablelocal,SLOT(clear()));
    connect(this,SIGNAL(sigClearRemote()),ui->ptableRemote,SLOT(clear()));

    connect(ui->ptableRemote,SIGNAL(sigDoubleClick(int,int)),this,SLOT(slotDoubleClickRemote(int,int)));
    connect(ui->ptablelocal,SIGNAL(sigDoubleClick(int,int)),this,SLOT(slotDoubleClickLocal(int,int)));
    connect(this,SIGNAL(sigShowJindu(QString)),this,SLOT(slotShowJindu(QString)));
    ui->ptableRemote->setHeaderText(QStringList()<<strname.c_str()<<strsize.c_str()<<strtype.c_str());
    ui->ptablelocal->setHeaderText(QStringList()<<strname.c_str()<<strsize.c_str()<<strtype.c_str());
    //    ui->ptablejindu->setHeaderText(QStringList()<<"名称"<<"速率"<<"传输百分比");
    ui->ptableRemote->setColWidth(0,500);
    ui->ptableRemote->setColWidth(1,100);
    ui->ptablelocal->setColWidth(0,500);
    ui->ptablelocal->setColWidth(1,100);
    //    ui->ptablejindu->setColWidth(0,600);

    //    showbyPathLocalWin();
    //    showbyPathRemoteLinux();
}
void MainWindow::threadLinux()
{
    if(!threadShowbyPathRemoteLinux())
    {
        //        ui->ptablelocal->clear();
        //        ui->ptableRemote->clear();
        sigClearLocal();
        sigClearRemote();
    }
    else
        showbyPathLocalWin();
}
void MainWindow::slotClickTree(QTreeWidgetItem *item, int column)
{
    pstring strhost=(item->text(0).toStdString());
    hlog(strhost);
    ui->textBrowser->append(QString("连接服务器")+QString(strhost.c_str())+"中......");
    //如果含有冒号,说明有端口,可能是带域名的,要分开
    if(strhost.contain(":"))
    {
        pliststring lres=strhost.split(":");
        this->host=lres[0];

        this->port=stoi(lres[1]);
    }
    else
    {
        this->host=strhost;
        this->port=22;
    }
    this->pwd=mall[strhost];
    hlog(host,pwd,port);
    ptrans=new pscp(this->host,"root",this->pwd,this->port);
    std::thread thlinux(&MainWindow::threadLinux,this);
    thlinux.detach();
}

void MainWindow::slotMessageBox(QString info)
{
    qlib::messageBox(info);
}


MainWindow::~MainWindow()
{
    delete ui;
}


//如果太快会出现一次多个的情况,要慢慢来
//ignoring potentially dangerous server-supplied filename 'D:'

//ignoring potentially dangerous server-supplied filename 'D:'

//A: 00:00:00 | 100%


//xlib.class                | 19 kB |  19.2 kB/s | ETA: 00:00:00 | 100%


//xtcp.class                | 4 kB |   4.8 kB/s | ETA: 00:00:00 | 100%


//CallbackThread.class      | 0 kB |   0.2 kB/s | ETA: 00:00:00 | 100%


//xmysql.class              | 5 kB |   5.4 kB/s | ETA: 00:00:00 | 100%


//xtcp$threadClient.class   | 1 kB |   1.8 kB/s | ETA: 00:00:00 | 100%


//messageType.class         | 0 kB |   0.6 kB/s | ETA: 00:00:00 | 100%


//Reply.class               | 0 kB |   0.4 kB/s | ETA: 00:00:00 | 100%


//Submit.class              | 0 kB |   0.8 kB/s | ETA: 00:00:00 | 100%


//log4j-1.2.17.jar          | 32 kB |  32.0 kB/s | ETA: 00:00:13 |   6%]
void MainWindow::showstr(pstring str)
{
    //    hlog(str);


    pliststring lstrline=str.split("\r\n");
    hlog(lstrline);
    QString strNoReturn=lstrline[0].c_str();
    sigShowJindu(strNoReturn);
    //    qlog(lstrline.size());
    //    //每行按空格分,第一个和最后一个就是名称和进度
    //    for(int i=0;i<lstrline.size();i++)
    //    {
    //        pstring stri=lstrline[i];
    //        //        hlog(stri);
    //        if(!stri.contain("%"))
    //            continue;
    //        pliststring lstr=stri.split(" ");
    //        //        hlog(lstr);
    //        //    //取第一个是文件名,最后一个是百分比
    //        pstring name=lstr[0];
    //        pstring percent=lstr[lstr.size()-1];
    //        pstring speed;
    //        if(lstr.size()>6)
    //        {
    //            speed=lstr[5]+lstr[6];
    //        }
    //        hlog(name,percent,speed);

    //        QString strName=qlib::toString(name);
    //        QString strPercent=qlib::toString(percent);
    //        QString strSpeed=qlib::toString(speed);


    //        qlog(strName,strPercent);
    //        //要增加上去 ,如果有就更新,如果没有就增加
    //        //先查一遍有没有
    //        int ifind=-1;
    //        for(int i=0;i<ui->ptablejindu->getRowCount();i++)
    //        {
    //            QString namei=ui->ptablejindu->getItemText(i,"名称");
    //            if(namei==strName)
    //            {
    //                ifind=i;
    //                break;
    //            }
    //        }
    //        //    hlog(ifind);

    //        //没找到,要在目前行数加一行,同时如果是100%了要更新
    //        if(ifind==-1)
    //        {
    //            int rowdst=ui->ptablejindu->getRowCount()+1;

    //            ui->ptablejindu->setRowCount(rowdst);
    //            ui->ptablejindu->setItemText(rowdst-1,"名称",strName);
    //            ui->ptablejindu->setItemText(rowdst-1,"速率",strSpeed);
    //            ui->ptablejindu->setItemText(rowdst-1,"传输百分比",strPercent);
    //            hlog(strPercent);
    //            if(strPercent=="100%")
    //            {
    ////                this->showbyPathLocalWin();
    ////                hlog("###### trans finish #########");
    ////                this->showbyPathRemoteLinux();
    ////                qlog(rowdst);
    //                //最后要删除
    //                ui->ptablejindu->removeRow(rowdst-1);
    //            }
    //        }
    //        else//找到
    //        {
    //            ui->ptablejindu->setItemText(ifind,"名称",strName);
    //            ui->ptablejindu->setItemText(ifind,"速率",strSpeed);
    //            ui->ptablejindu->setItemText(ifind,"传输百分比",strPercent);
    //            hlog(strPercent);
    //            if(strPercent=="100%")
    //            {
    //                this->showbyPathLocalWin();
    //                this->showbyPathRemoteLinux();
    //                //最后要删除
    //                ui->ptablejindu->removeRow(ifind);
    //            }
    //        }
    //    }
}





void MainWindow::slotDoubleClickRemote(int row, int col)
{
    hlog(row,col);
    //不管点的哪里,获取第一列
    QString strName=ui->ptableRemote->getItemText(row,0);
    //    qlib::messageBox(strName);
    hlog(strName.toStdString());
    if(plib::isIncludeChinese(strName.toStdString()))
    {
        qlib::messageBox("暂不支持下载中文文件,请改为英文名后再试,目前仅支持上传中文文件");
        return;
    }
    if(strName=="..")
    {
        hlog("点击了上一级");
        hlog(strpwdremote);
        //要到上一级去
        if(strpwdremote=="/")
        {
            qlib::messageBox("已经是根目录,无法定位到上一级");
            return;
        }
        pliststring listpath=strpwdremote.split("/");
        hlog(listpath);
        listpath.deleteEnd();
        hlog(listpath);
        pstring pathres="/"+listpath.join("/");
        hlog(pathres);
        this->strpwdremote=pathres;
        this->threadShowbyPathRemoteLinux();
        return;
    }
    //获取类型
    QString strType=ui->ptableRemote->getItemText(row,2);
    hlog(strType.toStdString());
    //如果是目录或者是目录快捷方式,排除了链接
    if(strType=="目录"||strType=="目录快捷方式")
    {
        //获取新的路径,一般都是不带/的
        hlog(strpwdremote);
        pstring pathres;
        if(strpwdremote=="/")
            pathres=strpwdremote+strName.toStdString();
        else
            pathres=strpwdremote+"/"+strName.toStdString();
        hlog(pathres);
        this->strpwdremote=pathres;
        this->threadShowbyPathRemoteLinux();
    }
    if(strType=="文件")
    {
        pstring name=strName.toStdString();
        hlog(name);
        //        name=plib::toUTF8(name.c_str());
        pstring strPathFull=this->strpwdremote+"/"+name;
        hlog(strPathFull);
        //        qlib::messageBox(strPathFull.c_str());
        hlog(this->strpwdlocal);
        //传输文件
        ptrans->downloadThread(this->strpwdlocal,strPathFull,std::bind(&MainWindow::showstr,this,placeholders::_1));
    }
}

void MainWindow::slotDoubleClickLocal(int row, int col)
{
    hlog(row,col);
    //不管点的哪里,获取第一列
    QString strName=ui->ptablelocal->getItemText(row,0);
    hlog(strName);
    hlog(plib::isIncludeChinese(strName.toStdString()));
    if(plib::isIncludeChinese(strName.toStdString()))
    {
        qlib::messageBox("暂不支持上传中文目录,请改为英文名后再试,目前仅支持上传中文文件");
        return;
    }
    //如果点击了..
    if(strName=="..")
    {
        hlog("点击了上一级");
        hlog(strpwdlocal);
        //        //要到上一级去
        //        if(strpwdlocal=="/")
        //        {
        //            qlib::messageBox("已经是根目录,无法定位到上一级");
        //            return;
        //        }
        pliststring listpath=strpwdlocal.split("/");
        hlog(listpath);
        listpath.deleteEnd();
        hlog(listpath);
        pstring pathres=listpath.join("/");
        hlog(pathres);
        //如果到了根目录,比如C:则需要加上/不然有问题,windows
        if(pathres.size()==2)
        {
            pathres+="/";
            hlog(pathres);
        }
        //如果到了再上一级,就是我的电脑了
        if(pathres.size()==0)
        {
            pathres="我的电脑";
        }
        //如果==我的电脑长度加2,说明是我的电脑点进去的--我的电脑/C:/
        //要把前边的我的电脑去掉

        qlog(pathres,pathres.size());

        this->strpwdlocal=pathres;
        ui->lineEditLocalpwd->setText(qlib::toString(this->strpwdlocal));
        this->showbyPathLocalWin();
        return;
    }
    //获取类型
    QString strType=ui->ptablelocal->getItemText(row,2);
    //    hlog(strType.toStdString());
    //如果是目录或者是目录快捷方式,排除了链接
    if(strType=="目录"||strType=="目录快捷方式")
    {

        //获取新的路径,一般都是不带/的
        hlog(strpwdlocal);
        pstring pathres;
        if(strpwdlocal=="/")
            pathres=strpwdlocal+strName.toStdString();
        else
            pathres=strpwdlocal+"/"+strName.toStdString();
        hlog(pathres);
        //要去掉我的电脑
        if(pathres.contain("我的电脑")&&pathres.contain(":/"))
        {
            pathres=pathres.substr(13,pathres.size());
            hlog(pathres);
        }
        this->strpwdlocal=pathres;
        ui->lineEditLocalpwd->setText(qlib::toString(this->strpwdlocal));
        this->showbyPathLocalWin();
    }
    //目前只有文件支持上传中文,其他都不支持
    if(strType=="文件")
    {
        pstring name=strName.toStdString();
        hlog(name);
        pstring strPathFull=this->strpwdlocal+"/"+name;
        hlog(strPathFull);
        hlog(this->strpwdremote);
        //传输文件
        ptrans->uploadThread(strPathFull,this->strpwdremote,std::bind(&MainWindow::showstr,this,placeholders::_1));
    }
}

bool MainWindow::threadShowbyPathRemoteLinux()
{
    //打印大小,文件名,以及类型,第一列是为了判断类型
    //去掉total的
    pstring strcmd="ls -l " +this->strpwdremote+" |grep -v total| awk '{print $5,$9,$1}'";
    hlog(strcmd);
    pstring strll=plib::xsh(host.c_str(),strcmd.c_str(),pwd.c_str(),"root",this->port);
    hlog(strll);
    if(strll=="connect fail")
    {
        sigTextBrowser((pstring()<<"连接服务器"<<this->host<<"失败").c_str());
        return false;
    }
    qlog(this->strpwdremote);
    //显示当前路径指定路径
    sigLineText(qlib::toString(this->strpwdremote));
    hlog(host,pwd,strcmd,strll);
    pliststring listall=strll.split("\n");
    hlog(listall);


    plist<pmap<pstring,pstring> > lmall;
    pmap<pstring,pstring> mapinfo;
    //如果不是根目录,则要先加..
    if(this->strpwdremote!="/")
    {
        mapinfo.add(strtype,"目录");
        mapinfo.add(strsize,"");
        mapinfo.add(strname,"..");
        lmall.append(mapinfo);
    }
    for(int i=0;i<listall.size();i++)
    {
        pmap<pstring,pstring> mapinfo;
        //当前数据
        pstring data=listall[i];

        pliststring listi=data.split(" ");
        if(listi.size()!=3)
            continue;
        //第一列是大小,第二列是文件名或者文件夹名,第三列是类型

        pstring typei=listi[2];
//        hlog(listi);
//        hlog(typei);
        if(typei.contain("d"))
        {
            //如果是目录,且开头不是.,就是要去掉隐藏目录,才加入
            mapinfo.add(strtype,"目录");
            mapinfo.add(strsize,"");
            mapinfo.add(strname,listi[1]);
        }
        else if(typei.contain("l"))
        {
            continue;
        }
        else
        {
//            hlog("this is a file");
            mapinfo.add(strtype,"文件");
            pstring strbytes=listi[0];
//            hlog(listi[0],strbytes);
            int iMB=stoull(strbytes)*1.0/1024/1024;
//            hlog(iMB);
            pstring stres=plib::toString(iMB)+" MB";//最终MB数
//            hlog(stres);
            mapinfo.add(strsize,stres);
            mapinfo.add(strname,listi[1]);
        }

//                hlog(mapinfo);
        lmall.append(mapinfo);
    }

//        hlog(lmall);
    //显示当前路径下的所有文件以及文件夹
    sigShowTable(lmall,0);

    //    ui->ptableRemote->setRowCount(lmall.size());
    //    for(int i=0;i<lmall.size();i++)
    //    {
    //        pmap<pstring,pstring> mapi=lmall[i];
    //        ui->ptableRemote->setItemText(i,strname.c_str(),mapi[strname].c_str());
    //        ui->ptableRemote->setItemText(i,strsize.c_str(),mapi[strsize].c_str());
    //        ui->ptableRemote->setItemText(i,strtype.c_str(),mapi[strtype].c_str());
    //    }
    sigTextBrowser((pstring()<<"连接服务器"<<this->host<<"成功").c_str());
    return true;
}

void MainWindow::showbyPathLocalWin()
{
    plist<pmap<pstring,pstring> > lmall;
    plist<pstring> listallFile;
    //    QString mFolderPath="C:/Users/Administrator/Desktop";
    QString mFolderPath=qlib::toString(this->strpwdlocal);
    qlog(mFolderPath);
    qlog(mFolderPath=="我的电脑");
    if(mFolderPath!="我的电脑")
    {
        QStringList mImgNames;
        // 获取所有文件名
        QDir dir(mFolderPath);
        mFolderPath = dir.fromNativeSeparators(mFolderPath);//  "\\"转为"/"
        hlog(dir.exists());
        if (!dir.exists())
            mImgNames = QStringList("");
        dir.setFilter(QDir::Files);
        dir.setSorting(QDir::Name);
        dir.setNameFilters(QString("*.*;*.*").split(";"));
        mImgNames = dir.entryList();
        //        qlog(mImgNames);
        for (int i = 0; i < mImgNames.size(); ++i)
        {
            //        qDebug() << "entryList: " << i << "-" << mFolderPath + "/" +mImgNames[i];
            QString name=mImgNames[i];
            pstring pname=name.toStdString();

            //去掉隐藏文件以及.lnk的目录
            if(!name.contains(".lnk")&&name[0]!='.')
            {
                //                            hlog(pname,strFullPath,plib::getFileSize(strFullPath));
                //                hlog(pname);
                listallFile.append(pname);
            }
        }

        //目录结果,先加上..上一级
        plist<pstring> listallDir;
        listallDir.append("..");
        // 获取所有文件夹名
        QDir dir2(mFolderPath);
        mFolderPath = dir2.fromNativeSeparators(mFolderPath);//  "\\"转为"/"
        if (!dir2.exists()) mImgNames = QStringList("");
        dir2.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
        //    dir2.setFilter(QDir::Dirs|QDir::NoDot );
        dir2.setSorting(QDir::Name);
        mImgNames = dir2.entryList();
        for (int i = 0; i < mImgNames.size(); ++i)
        {
            //        qDebug() << "entryList: " << i << "-" << mFolderPath + "/" +mImgNames[i];
            QString namedir=mImgNames[i];
            //        hlog(namedir.toStdString());
            //去掉隐藏目录以及.lnk的目录
            if(!namedir.contains(".lnk")&&namedir[0]!='.')
            {
                //            hlog(namedir);
                listallDir.append(namedir.toStdString());
            }
        }

        //    this->strpwdlocal=path;
        //显示当前路径指定路径
        ui->lineEditLocalpwd->setText(qlib::toString(this->strpwdlocal));

        hlog(listallFile);



        for(int i=0;i<listallDir.size();i++)
        {
            pmap<pstring,pstring> mapinfo;
            mapinfo.add(strname,listallDir[i]);
            mapinfo.add(strtype,"目录");
            //要有这一句,不然会崩,因为现在pmap都比较严格
            mapinfo.add(strsize,"");
            //        hlog(mapinfo);
            lmall.append(mapinfo);
        }
        //从第三个开始,因为第一个是pwd,第二个是.
        for(int i=0;i<listallFile.size();i++)
        {
            pstring pname=listallFile[i];

            pstring strFullPath=this->strpwdlocal+"/"+pname;
            //            hlog(strFullPath);
            longlong llsize=plib::getFileSize(strFullPath);
            pmap<pstring,pstring> mapinfo;
            mapinfo.add(strname,listallFile[i]);
            mapinfo.add(strtype,"文件");
            //整数M
            mapinfo.add(strsize,plib::toString((int)1.0*llsize/1024/1024)+" MB");
            //        hlog(mapinfo);
            lmall.append(mapinfo);
        }
    }
    else//如果是我的电脑,则把盘符加进去都
    {
        auto listdevice=qlib::getAllDeviceValid();
        for(int i=0;i<listdevice.size();i++)
        {
            QString devicei=listdevice[i];
            pmap<pstring,pstring> mapinfo;
            mapinfo.add(strname,devicei.toStdString());
            mapinfo.add(strtype,"目录");
            //要有这一句,不然会崩,因为现在pmap都比较严格
            mapinfo.add(strsize,"");
            //        hlog(mapinfo);
            lmall.append(mapinfo);
        }
    }
    //    hlog(lmall);
    //显示当前路径下的所有文件以及文件夹

    ui->ptablelocal->setRowCount(lmall.size());
    //    hlog(lmall);
    for(int i=0;i<lmall.size();i++)
    {
        pmap<pstring,pstring> mapi=lmall[i];
        //        hlog(mapi);
        ui->ptablelocal->setItemText(i,strname.c_str(),mapi[strname].c_str());
        ui->ptablelocal->setItemText(i,strsize.c_str(),mapi[strsize].c_str());
        ui->ptablelocal->setItemText(i,strtype.c_str(),mapi[strtype].c_str());
    }

}


void MainWindow::slotDelLocal()
{
    qlog(ui->ptablelocal->getRowNow());
    QString name=ui->ptablelocal->getItemText(ui->ptablelocal->getRowNow(),"名称");
    qlog(name);
    pstring pathFull=this->strpwdlocal+"/"+name.toStdString();
    qlog(pathFull);

    if(qlib::confirmbox("确定删除: "+qlib::toString(pathFull)+"吗?"))
    {

        plib::rm(pathFull);

        showbyPathLocalWin();
    }
}

void MainWindow::slotDelRemote()
{
    qlog(ui->ptableRemote->getRowNow());
    QString name=ui->ptableRemote->getItemText(ui->ptableRemote->getRowNow(),"名称");
    qlog(name);
    pstring pathFull=this->strpwdremote+"/"+name.toStdString();
    qlog(pathFull);

    if(qlib::confirmbox("确定删除: "+qlib::toString(pathFull)+"吗?"))
    {

        pstring cmd="rm -rf "+pathFull;
        qlog(cmd);
        plib::xsh(this->host.c_str(),cmd,this->pwd.c_str(),"root",this->port);
//        plib::xshplink(this->host,cmd,this->pwd);
        //        if(this->getShellRes(cmd.c_str())=="")
        //        {
        //            qlib::messageBox("删除失败");
        //        }
        threadShowbyPathRemoteLinux();
    }
}

void MainWindow::slotUpload()
{
    qlog(ui->ptablelocal->getRowNow());
    QString name=ui->ptablelocal->getItemText(ui->ptablelocal->getRowNow(),"名称");
    qlog(name);
    if(plib::isIncludeChinese(name.toStdString()))
    {
        qlib::messageBox("暂不支持上传中文目录,请改为英文名后再试,目前仅支持上传中文文件");
        return;
    }
    pstring pathFull=this->strpwdlocal+"/"+name.toStdString();
    qlog(pathFull);

    ptrans->uploadThread(pathFull,this->strpwdremote,std::bind(&MainWindow::showstr,this,placeholders::_1));
}

void MainWindow::slotDownload()
{
    qlog(ui->ptableRemote->getRowNow());
    QString name=ui->ptableRemote->getItemText(ui->ptableRemote->getRowNow(),"名称");
    qlog(name);
    if(plib::isIncludeChinese(name.toStdString()))
    {
        qlib::messageBox("暂不支持上传中文目录,请改为英文名后再试,目前仅支持上传中文文件");
        return;
    }
    pstring pathFull=this->strpwdremote+"/"+name.toStdString();
    qlog(pathFull);

    ptrans->downloadThread(this->strpwdlocal,pathFull,std::bind(&MainWindow::showstr,this,placeholders::_1));
}

void MainWindow::slotRenameLocal()
{
    hlog("rename local");

    QString name=ui->ptablelocal->getItemText(ui->ptablelocal->getRowNow(),"名称");
    hlog(name,this->strpwdlocal);
    QString strinput;
    if(!qlib::inputbox(strinput))
    {
        qlib::messageBox("操作取消");
        return;
    }
    pstring strFullPath=this->strpwdlocal+"/"+name.toStdString();
    pstring strFullPathDes=this->strpwdlocal+"/"+strinput.toStdString();
    hlog(strFullPath,strFullPathDes);
    if(plib::mv(plib::toChinese(strFullPath),plib::toChinese(strFullPathDes)))
    {
        qlib::messageBox("重命名成功");
        showbyPathLocalWin();
    }
    else
    {
        qlib::messageBox("重命名失败");
    }
}

void MainWindow::slotRenameRemote()
{
    hlog("rename remote");
    qlog(ui->ptableRemote->getRowNow());
    QString name=ui->ptableRemote->getItemText(ui->ptableRemote->getRowNow(),"名称");
    qlog(name);
    if(plib::isIncludeChinese(name.toStdString()))
    {
        qlib::messageBox("远程linux中文件名包含中文,无法重命名");
        return;
    }
    pstring pathFull=this->strpwdremote+"/"+name.toStdString();
    qlog(pathFull);
    hlog(plib::toChinese(pathFull));
    QString strinput;
    if(!qlib::inputbox(strinput))
    {
        qlib::messageBox("操作取消");
        return;
    }
    pstring pathFullRemote=this->strpwdremote+"/"+strinput.toStdString();
    pstring cmd="mv "+pathFull+" "+pathFullRemote;
    hlog(cmd);
    //    cmd=plib::toChinese(cmd);
    hlog(plib::xsh(host.c_str(),cmd,this->pwd.c_str(),"root",(port)));
}


void MainWindow::on_textBrowser_textChanged()
{
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void MainWindow::slotShowJindu(QString jindu)
{
    ui->textBrowser->append(jindu);
    if(jindu=="end")
    {
        this->threadShowbyPathRemoteLinux();
        this->showbyPathLocalWin();
    }
}



