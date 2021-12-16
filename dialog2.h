#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>

namespace Ui {
class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2(QWidget *parent = nullptr);
    ~Dialog2();
     QString cell1() const;

private:
    Ui::Dialog2 *ui;  
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

#endif // DIALOG2_H
