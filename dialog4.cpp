#include "dialog4.h"
#include "ui_dialog4.h"

Dialog4::Dialog4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog4)
{
    ui->setupUi(this);
    createWidgets();
    placeWidgets();
    connect(ok, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);

}

Dialog4::~Dialog4()
{
    delete ui;
}

void Dialog4::createWidgets()
{
    ok = new QPushButton("Save");
    cancel = new QPushButton("Don´t save");
    col = new QLabel("Do you want to save the current file?");
    Hlay1 = new QHBoxLayout;
    Hlay2 = new QHBoxLayout;
    Layout = new QVBoxLayout;
}

void Dialog4::placeWidgets()
{
    setLayout(Layout);
    ok->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    cancel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    Hlay2->addSpacing(20);
    Hlay1->addWidget(col);
    Hlay2->addWidget(ok);
    Hlay2->addWidget(cancel);
    Layout->addLayout(Hlay1);
    Layout->addLayout(Hlay2);

}
