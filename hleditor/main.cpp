#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Light C++ Editor");
    app.setOrganizationName("Artem Shmelev");

    MainWindow* window = new MainWindow;

    window->show();
    window->move((QApplication::desktop()->width() - window->width()) / 2,
                 (QApplication::desktop()->height() - window->height()) /2);

    return app.exec();
}

