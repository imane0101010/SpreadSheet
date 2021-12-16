#ifndef QDIALOG_H
#define QDIALOG_H
#include <QWidget>
#include <QLabel>
#include <QStatusBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>


class Qdialog: public QWidget
{
public:
    Qdialog();
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

#endif // QDIALOG_H
