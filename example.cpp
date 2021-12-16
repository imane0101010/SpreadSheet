#include "example.h"
#include "ui_example.h"

example::example(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::example)
{
    ui->setupUi(this);
}

example::~example()
{
    delete ui;
}
