#include "dialog2.h"
#include "ui_dialog2.h"
#include "spreadsheet.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{


    ui->setupUi(this);


    createWidgets();
    placeWidgets();
    connect(ok, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);

}

Dialog2::~Dialog2()
{
    delete ui;
}
void Dialog2::createWidgets()
{
    ok = new QPushButton("ok");
    cancel = new QPushButton("Cancel");
    line = new QLineEdit();
    cell = new QLabel("Search");
    Hlay1 = new QHBoxLayout;
    Hlay2 = new QHBoxLayout;
    Layout = new QVBoxLayout;
}

void Dialog2::placeWidgets()
{
   setLayout(Layout);
      ok->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
      cancel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
      Hlay2->addSpacing(20);
     Hlay1->addWidget(cell);
     Hlay1->addWidget(line);
     Hlay2->addWidget(ok);
     Hlay2->addWidget(cancel);
     Layout->addLayout(Hlay1);
     Layout->addLayout(Hlay2);


}
QString Dialog2::cell1() const
{
    return line->text();
}
