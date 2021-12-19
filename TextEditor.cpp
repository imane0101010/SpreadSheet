#include "TextEditor.h"
#include <QPixmap>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
TextEditor ::TextEditor (QWidget *parent)
    : QMainWindow(parent)
{
    //Seting the spreadsheet

    setupMainWidget();

    // Creaeting Actions
    createActions();

    // Creating Menus
    createMenus();


    //Creating the tool bar
    createToolBars();

    //making the connexions
    makeConnexions();
}

void TextEditor ::setupMainWidget()
{
    textEditor = new QPlainTextEdit;

    setCentralWidget(textEditor);

}

TextEditor ::~TextEditor()
{
    delete textEditor ;

    // --------------- Actions       --------------//
    delete  newFile;
    delete  open;
    delete  save;
    delete  exit;
    delete cut;
    delete copy;
    delete paste;
    delete about;
    delete aboutQt;

    // ---------- Menus ----------
    delete FileMenu;
    delete editMenu;
    delete helpMenu;
}

void TextEditor::createActions()
{
    // --------- New File -------------------
   QPixmap newIcon(":/newFile.png");
   newFile = new QAction(newIcon, "&New", this);
   newFile->setShortcut(tr("Ctrl+N"));


    // Open
   //QPixmap openIcon(":/newFile.png");
  // newFile = new QAction(newIcon, "&New", this);
   open = new QAction("&Open", this);
   open->setShortcut(tr("Ctrl+O"));

    // Save
   QPixmap SaveIcon(":/save_file.png");
   save = new QAction(SaveIcon,"&Save", this);
   save->setShortcut(tr("Ctrl+S"));
    //cutfile
   QPixmap cutIcon(":/cut.png");
   cut = new QAction(newIcon, "&Cut", this);
   cut->setShortcut(tr("Ctrl+X"));

   // Copy menu
   QPixmap copyIcon(":/copy.png");
   copy = new QAction( "&Copy", this);
   copy->setShortcut(tr("Ctrl+C"));

//paste
   paste = new QAction( "&Paste", this);
   paste->setShortcut(tr("Ctrl+V"));

   about =  new QAction("&About");
   aboutQt = new QAction("About &Qt");

    // --------- exit -------------------
   QPixmap exitIcon(":/quit_icon.png");
   exit = new QAction(exitIcon,"&Exit", this);
   exit->setShortcut(tr("Ctrl+Q"));
}

void TextEditor::close()
{

    auto reply = QMessageBox::question(this, "Exit",
                                       "Do you really want to quit?");
    if(reply == QMessageBox::Yes)
        qApp->exit();
}

void TextEditor ::createMenus()
{
    //  File menu
    FileMenu = menuBar()->addMenu("&File");
    FileMenu->addAction(newFile);
    FileMenu->addAction(open);
    FileMenu->addAction(save);

    FileMenu->addSeparator();
    FileMenu->addAction(exit);


    //Edit menu

    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(cut);
    editMenu->addAction(copy);
    editMenu->addAction(paste);

    //Help menu
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(about);
    helpMenu->addAction(aboutQt);
}

void TextEditor::createToolBars()
{

    //Create toolbar
    auto toolbar1 = addToolBar("File");


    //Add actions to the toolbar
    toolbar1->addAction(newFile);
    toolbar1->addAction(save);
    toolbar1->addSeparator();
    toolbar1->addAction(exit);


}

void TextEditor::showCursorPos()
{
    //store
    int line = textEditor->textCursor().blockNumber()+1;
    int pos = textEditor->textCursor().columnNumber()+1;
    statusBar()->showMessage(QString("Ln %1, Col %2").arg(line).arg(pos));
}

void TextEditor::makeConnexions()
{


   connect(copy, &QAction::triggered,
          textEditor, &QPlainTextEdit::copy);
   connect(paste, &QAction::triggered,
          textEditor, &QPlainTextEdit::paste);
   connect(cut, &QAction::triggered,
          textEditor, &QPlainTextEdit::cut);

   connect(save, &QAction::triggered,this,&TextEditor::saveSlot);

   //Connection for the exit button
   connect(exit, &QAction::triggered, this, &TextEditor::close);
   connect(textEditor, SIGNAL(cursorPositionChanged()), this, SLOT(showCursorPos()));
          connect(newFile, &QAction::triggered, this, &TextEditor::newSlot);
   //connectting the chane of any element in the spreadsheet with the update status bar
  connect(open,&QAction::triggered, this,&TextEditor::openSlot);
}
void TextEditor::newSlot()
{
    /* Dialog4 D;
     //Executing the dialog and storing the user response
     auto rep = D.exec();
     if(rep == QDialog::Accepted){

        saveSlot();
      }
      */
     //Clearing the content of spreadsheet
       textEditor->clear();
       CurrentFile ="";
        setWindowTitle("SpreadSheet");
}

void TextEditor::saveContent(QString Filename) const
{
    //Gettign a pointer on the file
       QFile file(Filename);

       //Openign the file
       if(file.open(QIODevice::WriteOnly))  //Opening the file in writing mode
       {
           //Initiating a stream using the file
           QTextStream out(&file);

             out<<textEditor->toPlainText();


               }
       file.close();

}

void TextEditor::saveSlot()
{
    //Creating a file dialog to choose a file graphically
    auto dialog = new QFileDialog(this);

    //Check if the current file has a name or not
    if(CurrentFile == "")
    {
       CurrentFile = dialog->getSaveFileName(this,"choose your file");

       //Update the window title with the file name
       setWindowTitle(CurrentFile);
    }

   //If we have a name simply save the content
   if( CurrentFile != "")
   {
           saveContent(CurrentFile);
   }
}
void TextEditor::openSlot(){
    QString name = QFileDialog::getOpenFileName(this,tr("Open File"),NULL,"TXT - Text file (*.txt)");
    QString filecontent;
    QFile file(name);
    file.open(QFile::ReadOnly | QFile::Text);
   // QTextStream ReadFile(&file);
    QTextStream in(&file);
    filecontent= in.readAll();
    textEditor->clear();
    textEditor->setPlainText(filecontent);
       file.close();

    }

