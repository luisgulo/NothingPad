#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionClose_triggered()
{
    currFile.clear();
    ui->textEdit->setText(QString());
    QMessageBox::warning(this,"Aviso", "Se cerró el fichero actual (sin grabar)");
    setWindowTitle("NothingPad");
}


void MainWindow::on_actionOpen_triggered()
{
    QString FileName = QFileDialog::getOpenFileName(this,"Abrir el fichero");
    QFile file(FileName);
    currFile = FileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Error", "No puedo abrir el fichero: " + file.errorString());
        return;
    }
        setWindowTitle(FileName);
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textEdit->setText(text);
        file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Guardar como");
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Error", "No puedo guardar el fichero: " + file.errorString());
        return;
    }
    currFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text ;
    file.close();

}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter Printer ;
    Printer.setPrinterName("Mi Impresora");
    QPrintDialog pDialog(&Printer,this);

    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this,"Error", "No puedo acceder a la impresora");
        return;
    }
    ui->textEdit->print(&Printer);
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
