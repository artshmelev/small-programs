#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMap>

class TextEdit;
class QMenu;
class QMenuBar;
class QStatusBar;
class QTabWidget;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = 0);

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void slotNew();
    void slotOpen();
    void slotSave();
    void slotCloseTab(int index, int arg);
    void slotCloseTab(int index);
    void slotCloseCurTab();
    void slotModified();
    void slotOptions();
    void slotAbout();
    void printPdf();

private:
    QMenuBar* menuBar;
    QMenu* mainMenu;
    QMenu* optionsMenu;
    QMenu* helpMenu;
    QTabWidget* tabWidget;
    QMap<int, TextEdit*> idTabs;
    QStatusBar* statusBar;

};

#endif // MAINWINDOW_H
