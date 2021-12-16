#include "qdialog.h"

Qdialog::Qdialog()
{
  createWidgets();
  placeWidgets();

}

void Qdialog::createWidgets()
{
    ok = new QPushButton("ok");
    cancel = new QPushButton("Cancel");
    line = new QLineEdit();
    cell = new QLabel("Cell location");
    Hlay1 = new QHBoxLayout;
    Hlay2 = new QHBoxLayout;
    Layout = new QVBoxLayout;
}

void Qdialog::placeWidgets()
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
