#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(const QString text, QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->label->setText(text);
}

Dialog::~Dialog()
{
    delete ui;
}
