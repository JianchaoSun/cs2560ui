#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->t);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSave_triggered()
{

    QString filename = QFileDialog::getSaveFilename(this,"Save file");
    QFile file(filename);

    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"warning","Cannot save"+file.errorString);
    }
    currentFile = filename;
    setWindowFile(filename);
    QTextStream out(&file);

    //copy text in textedit widge
    QString text = ui->textedit->toPlainText();

    out <<text;
    file.close();

}



void MainWindow::on_actionEnd_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui ->textedit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui ->textedit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui-textedit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui-textedit->redo();
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textedit->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "open this file");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly|Qfile::Text)){
        QMessageBox::warning(this,"cant open"+file.errorString());

    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textedit->setText(text);
    file.close();
}
