#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>

bool MouseClicked_Cancel;
bool MouseClicked;
bool savePicDataToClip;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    uploader = new Uploader("");

    myMenu = new QMenu;
    myMenu->addAction("Stop");
    myMenu->addAction("Exit");
    connect(myMenu, SIGNAL(triggered(QAction*)), this, SLOT(trayAction(QAction *)));

    sTray = new QSystemTrayIcon(QIcon(":/images/icon.png"));
    sTray->setToolTip("Teknik Shortener");
    sTray->setContextMenu(myMenu);

    this->hide();
    sTray->show();

    monitorTimer = new QTimer(this);
    connect(monitorTimer, &QTimer::timeout, this, &MainWindow::monitorClipboard);
    monitorTimer->start(300);

//    QTimer::singleShot(10, this, MainWindow::hide());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::monitorClipboard()
{
    QString clipText = QApplication::clipboard()->text();
    QRegExp valid("(http(s)?://)?([\\w-]+\\.)+[\\w-]+[.com]+(/[/?%&=]*)?");
    if(valid.indexIn(clipText) != -1 &&
            clipText.size() > TEKNIK_SHORT_SIZE &&
            !clipText.contains("teknik") &&
            !clipText.contains("png") &&
            !uploader->gettingURL)

        uploader->getShortenURL(clipText);
}

void MainWindow::trayAction(QAction *tAction)
{

    if(tAction->text() == "Exit")
    exit(0);
    else if(tAction->text() == "Stop")
    {
        monitorTimer->stop();
        myMenu->actions().first()->setText("Start");
    }
    else
    {
        monitorTimer->start(300);
        myMenu->actions().first()->setText("Stop");
    }
}

