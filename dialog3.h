#ifndef DIALOG3_H
#define DIALOG3_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

namespace Ui {
class Dialog3;
}

class Dialog3 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3(QWidget *parent = nullptr);
    ~Dialog3();
    QString cell3() const;
private:
    Ui::Dialog3 *ui;
private:
    void createWidgets();
    void placeWidgets();
    QPushButton* ok ;
    QPushButton* cancel;
    QLineEdit * line ;
    QLabel * col ;
    QHBoxLayout * Hlay1 ;
    QHBoxLayout * Hlay2 ;
    QVBoxLayout *Layout ;

};

#endif // DIALOG3_H
