#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_chooseDirButton_clicked()
{

    QString filename = QFileDialog::getExistingDirectory(this, "Choose Folder");
    if (filename.isEmpty())
        return;
    ui->lineEdit->setText(filename);

}

void Widget::on_createDirButton_clicked()
{

    // Create a dir if it doesn't
    QString dirPath = ui->lineEdit->text();
    if (dirPath.isEmpty())
        return;
    QDir dir(dirPath);
    if (!dir.exists()) {
        // create it
        if (dir.mkdir(dirPath)) {
            QMessageBox::information(this, "Message", "Directory Created");
        }
    } else {
        QMessageBox::information(this, "Message", "Directory already exists");
    }
}

void Widget::on_DirExistsButton_clicked()
{

    QString dirPath = ui->lineEdit->text();
    if (dirPath.isEmpty())
        return;
    QDir dir(dirPath);
    if (!dir.exists()){
        QMessageBox::information(this, "Message", "Directory Doesn't exist");

    } else {
        QMessageBox::information(this, "Message", "Directory already exist");
    }

}

void Widget::on_dirOrFileButton_clicked()
{

}

void Widget::on_FolderContentButton_clicked()
{

    QString dirPath = ui->lineEdit->text();
    if (dirPath.isEmpty())
        return;
    QDir dir(dirPath);


    QList<QFileInfo> fileList = dir.entryInfoList();
    foreach(QFileInfo fileInfo, fileList ) {
        QString prefix;
        if(fileInfo.isFile()) {
            prefix = "File : ";
        }
        if (fileInfo.isDir()) {
            prefix = "Directory: ";
        }
    }

}
