#include "dialog1.h"
#include "ui_dialog1.h"
#include <QRegExp>
#include <QRegExpValidator>
Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{

    createWidgets();
    placeWidgets();

    ui->setupUi(this);
    //Validating the regular expression


     //Connection
     connect(ok, &QPushButton::clicked, this, &QDialog::accept);
     connect(cancel, &QPushButton::clicked, this, &QDialog::reject);
     QRegExp regCell{"[A-Z][1-9][0-9]{0,2}"};
     //Validating the regular expression
     line->setValidator(new QRegExpValidator(regCell));




}

Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::createWidgets()
{
    ok = new QPushButton("ok");
    cancel = new QPushButton("Cancel");
    line = new QLineEdit();
    cell = new QLabel("Cell location");
    Hlay1 = new QHBoxLayout;
    Hlay2 = new QHBoxLayout;
    Layout = new QVBoxLayout;
}

void Dialog1::placeWidgets()
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
QString Dialog1::cell_() const
{
    return line->text();
}
