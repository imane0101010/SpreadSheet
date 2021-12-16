#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QDialog>

namespace Ui {
class example;
}

class example : public QDialog
{
    Q_OBJECT

public:
    explicit example(QWidget *parent = nullptr);
    ~example();

private:
    Ui::example *ui;
};

#endif // EXAMPLE_H
