#include "textfinder.h"
#include "ui_textfinder.h"
#include<QFile>
#include<QTextStream>
#include<QString>
#include<QFileDialog>
#include<QDir>
#include<QTextCharFormat>
#include<QTextCursor>
#include<QTextDocument>

TextFinder::TextFinder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextFinder)
{
    ui->setupUi(this);
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(search()));

}

TextFinder::~TextFinder()
{
    delete ui;
}

void TextFinder::on_pushButton_clicked()
{

    QString path = QFileDialog::getOpenFileName(this,tr("Open Document"),QDir::homePath(),tr("Document files(*.txt)"),0,0);
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
   ui->textBrowser->setText(in.readAll());


}
void TextFinder::search(){

    ui->textBrowser->setUndoRedoEnabled(false);
       ui->textBrowser->setUndoRedoEnabled(true);

    QString searchString = ui->lineEdit->text();
       QTextDocument *document = ui->textBrowser->document();
       QTextCursor highlightcursor(document);
       QTextCursor cursor(document);
       cursor.beginEditBlock();
       QTextCharFormat plainFormat(highlightcursor.charFormat());
       QTextCharFormat colorFormat = plainFormat;
       colorFormat.setForeground(Qt::red);
       while (!highlightcursor.isNull() && !highlightcursor.atEnd()) {
           highlightcursor = document->find(searchString,highlightcursor,QTextDocument::FindWholeWords);
           if (!highlightcursor.isNull()) {
               highlightcursor.movePosition(QTextCursor::WordRight,QTextCursor::KeepAnchor);
               highlightcursor.mergeCharFormat(colorFormat);

           }

       }
    cursor.endEditBlock();
}
