#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QTableWidget>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileInfo>
#include <QDateTime>
using namespace std;
QString arr[256][256];
QString QFINFO;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int rowCount=ui->lineEdit->text().toInt();
    int colCount=ui->lineEdit_2->text().toInt();
    ui->tableWidget->setColumnCount(colCount);
    ui->tableWidget->setRowCount(rowCount);

    for(int i=0; i<rowCount; i++){
        for(int j=0;j<colCount;j++){
            QTableWidgetItem *kt=new QTableWidgetItem;
            kt->setText(" ");
            ui->tableWidget->setItem(j,i,kt);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{

    int col=ui->tableWidget->columnCount();
    int row=ui->tableWidget->rowCount();

    QString fns=QFileDialog::getSaveFileName(this,"Faylni saqlash","oxcfayl1","*.oxc");
    QFile file(fns);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
             return;
    QTextStream fout(&file);
    fout<<col<<" "<<row<<"\n";
    for(int i=0; i<row; i++){
        for(int j=0;j<col;j++){
            QString f=ui->tableWidget->item(i,j)->text();
            f.replace(" ","#00&pr&00#");
            fout<<f<<" ";
        }
        fout<<"\n";
    }
}


void MainWindow::on_actionOpen_triggered()
{
    int col,row;
    QString fname=QFileDialog::getOpenFileName(this,"Faylni ochish","/","*.oxc");

    QFile oFile(fname);
    QFileInfo fInfo(fname);
    QFINFO="Name: "+fInfo.fileName()+"\n"+fInfo.created().toString()+"\n"+fInfo.lastModified().toString()+"\n"+fInfo.lastRead().toString()+"\nO'lchami: "+QString::number(fInfo.size())+"\n";

    oFile.open(QFile::ReadOnly|QFile::Text);

    QTextStream fin(&oFile);
    fin>>row>>col;
    ui->tableWidget->setColumnCount(col);
    ui->tableWidget->setRowCount(row);
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            QString str;
            fin>>str;
            str.replace("#00&pr&00#"," ");
            QTableWidgetItem *kt=new QTableWidgetItem;
            kt->setText(str);
            ui->tableWidget->setItem(j,i,kt);
        }
    }

}

void MainWindow::on_actionSave_as_triggered()
{
    int col=ui->tableWidget->columnCount();
    int row=ui->tableWidget->rowCount();

    QString fns=QFileDialog::getSaveFileName(this,"Faylni saqlash","oxcfayl1","*.oxc");
    QFile file(fns);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
             return;
    QTextStream fout(&file);
    fout<<col<<" "<<row<<"\n";
    for(int i=0; i<row; i++){
        for(int j=0;j<col;j++){
            QString f=ui->tableWidget->item(i,j)->text();
            f.replace(" ","#00&pr&00#");
            fout<<f<<" ";
        }
        fout<<"\n";
    }
}

void MainWindow::on_actionRename_triggered()
{
    bool ok;
        QString text = QInputDialog::getText(this, tr("Rename"),
                                             tr("Yangi Nomi:"), QLineEdit::Normal,
                                             "rename1", &ok);
        if (ok && !text.isEmpty()){
            QString fn=QFileDialog::getOpenFileName(this,"Faylni ochish","Oddiy fayl","*.oxc");
            QFile f(fn);
            f.rename("C:\\Users\\User\\Desktop\\"+text+".oxc") ;
            QMessageBox::information(this,"Ok","Saqlandi",QMessageBox::Ok);
        }


}

void MainWindow::on_actionO_lchami_triggered()
{
    QMessageBox::information(this,"FileInfo",QFINFO,QMessageBox::Ok);
}
