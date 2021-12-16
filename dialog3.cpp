#include "dialog3.h"
#include "ui_dialog3.h"

Dialog3::Dialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3)
{
    ui->setupUi(this);
    createWidgets();
    placeWidgets();
    connect(ok, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);

}

Dialog3::~Dialog3()
{
    delete ui;
}

void Dialog3::createWidgets()
{
    ok = new QPushButton("ok");
    cancel = new QPushButton("Cancel");
    line = new QLineEdit();
    col = new QLabel("Col:");
    Hlay1 = new QHBoxLayout;
    Hlay2 = new QHBoxLayout;
    Layout = new QVBoxLayout;
}

void Dialog3::placeWidgets()
{
       setLayout(Layout);
       ok->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
       cancel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
       Hlay2->addSpacing(20);
       Hlay1->addWidget(col);
       Hlay1->addWidget(line);
       Hlay2->addWidget(ok);
       Hlay2->addWidget(cancel);
       Layout->addLayout(Hlay1);
       Layout->addLayout(Hlay2);

}
QString Dialog3::cell3() const
{
    return line->text();
}
