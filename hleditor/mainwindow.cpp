#include "mainwindow.h"
#include "customwidgets.h"

#include <QtGui>

MainWindow::MainWindow(QWidget* parent)
        : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    menuBar = new QMenuBar;
    mainMenu = new QMenu(tr("&File"));
    optionsMenu = new QMenu(tr("&Edit"));
    helpMenu = new QMenu(tr("&Help"));
    tabWidget = new QTabWidget;
    statusBar = new QStatusBar(this);

    mainMenu->addAction(tr("&New..."), this, SLOT(slotNew()),
                        QKeySequence("CTRL+N"));
    mainMenu->addAction(tr("&Open..."), this, SLOT(slotOpen()),
                        QKeySequence("CTRL+O"));
    mainMenu->addAction(tr("&Save"), this, SLOT(slotSave()),
                        QKeySequence("CTRL+S"));
    mainMenu->addSeparator();
    mainMenu->addAction(tr("Con&vert to PDF"), this, SLOT(printPdf()));
    mainMenu->addSeparator();
    mainMenu->addAction(tr("&Close"), this, SLOT(slotCloseCurTab()),
                        QKeySequence("CTRL+W"));
    mainMenu->addAction(tr("&Exit"), this, SLOT(close()),
                        QKeySequence("CTRL+Q"));
    optionsMenu->addAction(tr("&Options..."), this, SLOT(slotOptions()));
    helpMenu->addAction(tr("About"), this, SLOT(slotAbout()),
                        Qt::Key_F1);

    menuBar->addMenu(mainMenu);
    menuBar->addMenu(optionsMenu);
    menuBar->addMenu(helpMenu);
    menuBar->addSeparator();/*?*/

    tabWidget->setTabsClosable(true);
    TextEdit* textEdit = new TextEdit;
    idTabs.insert(0, textEdit);
    tabWidget->addTab(textEdit, "NoName0");

    layout->addWidget(menuBar);
    layout->addWidget(tabWidget);
    layout->addWidget(statusBar);

    setWindowTitle(QApplication::applicationName());
    setWindowIcon(QIcon(":/ASh.png"));
    setLayout(layout);
    resize(780, 600);

    connect(tabWidget, SIGNAL(tabCloseRequested(int)),
            this, SLOT(slotCloseTab(int)));
    connect(textEdit, SIGNAL(textChanged()),
            this, SLOT(slotModified()));
}

void MainWindow::slotCloseTab(int index, int arg)
{
    if (tabWidget->tabText(index).endsWith("*"))
    {
        int resp = QMessageBox::warning(this,
                                        QApplication::applicationName(),
                                        tr("The document has been "
                                           "modified.\nDo you want "
                                           "to save your changes?"),
                                        QMessageBox::Yes |
                                        QMessageBox::No |
                                        QMessageBox::Cancel);
        if (resp == QMessageBox::Yes) slotSave();
        else if (resp == QMessageBox::Cancel) return;
    }
    tabWidget->removeTab(index);
    idTabs.erase(idTabs.begin()+index);
    if (arg == 0 && tabWidget->count() == 0) slotNew();
}

void MainWindow::slotCloseTab(int index)
{
    slotCloseTab(index, 0);
}

void MainWindow::slotCloseCurTab()
{
    slotCloseTab(tabWidget->currentIndex());
}

void MainWindow::slotModified()
{
    int index = tabWidget->currentIndex();
    if (!tabWidget->tabText(index).endsWith("*"))
        tabWidget->setTabText(index,
                              tabWidget->tabText(index)+"*");
}

void MainWindow::slotNew()
{
    QString str = "NoName";
    TextEdit* textEdit = new TextEdit;
    if (tabWidget->count() == 0)
    {
        str += "0";
        idTabs.insert(0, textEdit);
    }
    else
    {
        str += QString::number((idTabs.end()-1).key()+1);
        idTabs.insert((idTabs.end()-1).key()+1, textEdit);
    }
    tabWidget->addTab(textEdit, str);
    tabWidget->setCurrentIndex(tabWidget->count()-1);
    connect(textEdit, SIGNAL(textChanged()),
            this, SLOT(slotModified()));
}

void MainWindow::slotOpen()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Dialog"), "", "*.cpp *.h");
    if (!path.isEmpty())
    {
        QFile file(path);
        if (file.open(QFile::ReadOnly))
        {
            TextEdit* textEdit = new TextEdit;
            if (tabWidget->count() == 0) idTabs.insert(0, textEdit);
            else idTabs.insert((idTabs.end()-1).key()+1, textEdit);
            textEdit->setPlainText(file.readAll());
            tabWidget->addTab(textEdit, QFileInfo(file).fileName());
            tabWidget->setCurrentIndex(tabWidget->count()-1);
            file.close();
            statusBar->showMessage(tr("File opened"), 2000);
            connect(textEdit, SIGNAL(textChanged()),
                    this, SLOT(slotModified()));
        }
    }
}

void MainWindow::slotSave()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save Dialog"),
                                                "", "*.cpp *.h");
    if (!path.isEmpty())
    {
        QFile file(path);
        if (file.open(QFile::WriteOnly))
        {
            TextEdit* textEdit = (idTabs.begin()+tabWidget->currentIndex()).value();
            file.write(textEdit->toPlainText().toUtf8());
            tabWidget->setTabText(tabWidget->currentIndex(),
                                  QFileInfo(file).fileName());
            file.close();
            statusBar->showMessage(tr("File saved"), 2000);
        }
    }
}

void MainWindow::slotOptions()
{

}

void MainWindow::slotAbout()
{
    QMessageBox::about(this, tr("About"),
                       tr("<h2>%1</h2><br><p>Copyright &copy; 2011 %2</p>"
                       "<p>%1 is small light-weight editor for C++ language.</p>"
                       "<p>Based on Qt.</p>")
                       .arg(QApplication::applicationName())
                       .arg(QApplication::organizationName()));
}

void MainWindow::printPdf()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save Dialog"),
                                                "", "*.pdf");
    if (!path.isEmpty())
    {
        if (!path.endsWith(".pdf")) path += ".pdf";
        QPrinter printer(QPrinter::HighResolution);
        printer.setPageSize(QPrinter::A4);
        printer.setOrientation(QPrinter::Portrait);
        printer.setOutputFileName(path);
        printer.setOutputFormat(QPrinter::PdfFormat);
        (idTabs.begin()+tabWidget->currentIndex()).value()->print(&printer);
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    tabWidget->setCurrentIndex(0);
    while (tabWidget->count() != 0) slotCloseTab(0, 1);
    event->accept();
}
