#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include <QDebug>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>

#include "uploader.h"

#define TEKNIK_SHORT_SIZE 22

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void monitorClipboard();

    void trayAction(QAction * tAction);
private slots:

private:
    Ui::MainWindow *ui;
    Uploader * uploader;
    QList <QString> * iLinks;
    QMenu * myMenu;
    QSystemTrayIcon * sTray;
    QTimer * monitorTimer;
};

#endif // MAINWINDOW_H
