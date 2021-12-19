#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QMainWindow>
#include <QTableWidget>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>
#include <QPlainTextEdit>
class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
   TextEditor (QWidget *parent = nullptr);
    ~TextEditor ();

protected:
    void setupMainWidget();
    void createActions();
    void createMenus();
    void createToolBars();
    void makeConnexions();
    void saveContent(QString Filename)const;
    void openFile(QString & Filename);
private slots:
    void close();
    void showCursorPos(); //Respond for the call changed
    void saveSlot();
    void newSlot();
    void openSlot();


 //Pointers
private:
    // --------------- Central Widget -------------//
    QPlainTextEdit *textEditor;
    // --------------- Actions       --------------//
    QAction * newFile;
    QAction * open;
    QAction * save;
    QAction * exit;
    QAction *cut;
    QAction *copy;
    QAction *paste;
    QAction *about;
    QAction *aboutQt;


    // ---------- Menus ----------
    QMenu *FileMenu;
    QMenu *editMenu;
     QMenu *helpMenu;
    QString CurrentFile ="";
};

#endif // SPREADSHEET_H
