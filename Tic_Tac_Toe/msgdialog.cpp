#include "msgdialog.h"
#include "ui_msgdialog.h"

MsgDialog::MsgDialog(const QString& messaggio, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgDialog)
{
    ui->setupUi(this);
    this->setFixedSize(geometry().width(), geometry().height());
    ui->showWinner->setText(messaggio);
}

MsgDialog::~MsgDialog()
{
    delete ui;
}
