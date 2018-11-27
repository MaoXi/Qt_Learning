#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include"new.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openf();

//    QMenu* menu[10];
//    QAction* act[10];
//    QMenuBar* menuBar;
//    QStatusBar* status;

public slots:
 //   void trigerMenu(QAction* act);

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_actionnew_triggered();

    void on_actionopen_triggered();

    void removeSubTab(int index);

private:
    Ui::MainWindow *ui;
   // Dialog d;
    New n;
};

#endif // MAINWINDOW_H
