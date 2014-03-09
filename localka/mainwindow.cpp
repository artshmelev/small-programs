#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&parser, SIGNAL(dataLoaded(QStringList&)),
            this, SLOT(showData(QStringList&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent* e)
{
    QMainWindow::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    parser.clearList();
    ui->listWidget->clear();
    //qDebug() << ui->lineEdit->text().toAscii().toPercentEncoding();
    parser.loadPage(ui->lineEdit->text());
}

void MainWindow::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Export to m3u"), "/home/artem");
    QFile file(filename);
    if (!file.open(QFile::WriteOnly))
        return;
    QTextStream out(&file);
    for (int i = 0; i < ui->listWidget_2->count(); i++)
        out << ui->listWidget_2->item(i)->text() << "\n";
    file.close();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->listWidget_2->clear();
}

void MainWindow::showData(QStringList& strList)
{
    ui->listWidget->addItems(strList);
}
