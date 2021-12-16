#ifndef DIALOG4_H
#define DIALOG4_H

#include <QDialog>
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
namespace Ui {
class Dialog4;
}

class Dialog4 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog4(QWidget *parent = nullptr);
    ~Dialog4();

private:
    Ui::Dialog4 *ui;
protected:
    void createWidgets();
    void placeWidgets();
    QPushButton* ok ;
    QPushButton* cancel;
    QLabel * col ;
    QHBoxLayout * Hlay1 ;
    QHBoxLayout * Hlay2 ;
    QVBoxLayout *Layout ;

};

#endif // DIALOG4_H
