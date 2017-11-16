#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Admin");
    ui->tableWidget->setColumnCount(4);
    QStringList titles;
    titles<<"ID"<<"student"<<"Class"<<"Hour";
    ui->tableWidget->setHorizontalHeaderLabels(titles);
    ui->tableWidget->setColumnWidth(1,200);
    ui->tableWidget->setColumnWidth(2,80);
    ui->tableWidget->setColumnWidth(3,200);
    ui->txtId->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QFile file("pro.txt");
        if(!file.open(QIODevice::Append|QIODevice::Text))
            return;

        QTextStream out(&file);
        out<<ui->txtId->text()<<"-"<<ui->txtStudent->text()
          <<"-"<<ui->txtClass->text()<<"-"<<ui->txtHour->text()<<"\n";
        file.close();
}

void MainWindow::resetTable()
{
    while(ui->tableWidget->rowCount()>0){
        ui->tableWidget->removeRow(0);
    }
}





void MainWindow::on_pushButton_2_clicked()
{
    resetTable();
    QFile file("pro.txt");
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            return;

        QTextStream in(&file);
        while(!in.atEnd()){
            QString line = in.readLine();
            list(line);
        }
        file.close();
}

void MainWindow::list(QString tableList){
        QStringList A = tableList.split("-");
        QString id = A[0];
        QString student = A[1];
        QString cclass = A[2];
        QString hour = A[3];
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(id));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(student));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(cclass));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(hour));
    }






void MainWindow::on_pushButton_3_clicked()
{
    QString txt = ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text();
    QFile sr("pro.txt");
        if(!sr.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QFile sw("temp.txt");
            if(!sw.open(QIODevice::Append | QIODevice::Text))
                return;

        QTextStream in(&sr);
        QTextStream out(&sw);
            while (!in.atEnd()){
                QString line = in.readLine();
                QStringList A = line.split("-");
                QString id =A[0];
                if(id.compare(txt)!=0){
                    out<<line<<"\n";
                }
            }
      sr.close();
      sw.close();

      QFile sw2("pro.txt");
      if(!sw2.open(QIODevice::WriteOnly | QIODevice::Text))
          return;
      sw2.close();

      QFile sw3("pro.txt");
      if(!sw3.open(QIODevice::Append | QIODevice::Text))
          return;
      QFile sr3("temp.txt");
      if(!sr3.open(QIODevice::ReadOnly|QIODevice::Text))
          return;
      QTextStream in3(&sr3);
      QTextStream out3(&sw3);
      while(!in3.atEnd()){
          QString line = in3.readLine();
          out3<<line<<"\n";
      }
}

void MainWindow::on_pushButton_4_clicked()
{
    resetTable();
    QString find=ui->txtSearch->text();
    QFile sr("pro.txt");
    if(!sr.open(QIODevice::ReadOnly|QIODevice::Text))
        return;
    QTextStream in(&sr);
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList A = line.split("-");
        QString pro=A[1];
        if(pro.contains(find)==true){
            list(line);
        }
    }
}
