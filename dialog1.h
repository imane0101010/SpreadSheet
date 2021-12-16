#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
#include <QWidget>
#include <QLabel>

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>

namespace Ui {
class Dialog1;
}

class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = nullptr);
    ~Dialog1();
    QString cell_() const;

private:
    Ui::Dialog1 *ui;

protected:
    void createWidgets();
    void placeWidgets();
    QPushButton* ok ;
    QPushButton* cancel;
    QLineEdit * line ;
    QLabel * cell ;
    QHBoxLayout * Hlay1 ;
    QHBoxLayout * Hlay2 ;
    QVBoxLayout *Layout ;

};

#endif // DIALOG1_H
