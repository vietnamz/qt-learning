#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
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

void Widget::on_writeButton_clicked()
{
    // save the file to disk
    QString filename = QFileDialog::getSaveFileName(this, "Save As");
    if (filename.isEmpty()) {
        return;
    }
    QFile file (filename);
    // open the file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append )) {
        return;
    }
    QTextStream out(&file);
    out << ui->textEdit->toPlainText() << "\n";
    file.close();

}

void Widget::on_readButton_clicked()
{
    QString filecontext;

    QString filename = QFileDialog::getOpenFileName(this, "Open file");
    if (filename.isEmpty()) {
        return;
    }

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();
    while(!line.isNull()) {
        filecontext.append(line);
        line = in.readLine();
    }

    file.close();
    ui->textEdit->clear();
    ui->textEdit->setPlainText(filecontext);

}

void Widget::on_selectFileButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose File");
    if (filename.isEmpty()) {
        return;
    }
    ui->sourceLineEdit->setText(filename);

}

void Widget::on_copyButton_clicked()
{

    QString srcFileName = ui->sourceLineEdit->text();
    QString destFileName = ui->lineEdit_2->text();

    if (srcFileName.isEmpty() || destFileName.isEmpty())
        return;

    QFile file(srcFileName);
    if(file.copy(destFileName)) {
        QMessageBox::information(this, "Success", "Copy Successful");
    } else {
        QMessageBox::information(this, "Failure", "Copy failed");
    }
}
