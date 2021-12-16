#include "spreadsheet.h"
#include "dialog1.h"
#include "dialog2.h"
#include "dialog3.h"
#include "dialog4.h"
#include <QPixmap>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QProcess>
#include <ostream>
#include <QClipboard>



SpreadSheet::SpreadSheet(QWidget *parent)
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


    //Creating the labels for the status bar (should be in its proper function)
    cellLocation = new QLabel("(1, 1)");
    cellFormula = new QLabel("");
    statusBar()->addPermanentWidget(cellLocation);
    statusBar()->addPermanentWidget(cellFormula);
}
void SpreadSheet::setupMainWidget()
{
    spreadsheet = new QTableWidget;
    spreadsheet->setRowCount(26);
    spreadsheet->setColumnCount(10);
    spreadsheet->setVerticalHeaderLabels({"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"});
    setCentralWidget(spreadsheet);
}
SpreadSheet::~SpreadSheet()
{
    delete spreadsheet;
    // --------------- Actions       --------------//
    delete  newFile;
    delete  open;
    delete  save;
    delete  saveAs;
    delete  exit;
    delete cut;
    delete copy;
    delete paste;
    delete deleteAction;
    delete find;
    delete row;
    delete Column;
    delete all;
    delete goCell;
    delete recalculate;
    delete sort;
    delete showGrid;
    delete clearAll;

   // delete recentFiles;

    delete about;
    delete aboutQt;

    // ---------- Menus ----------
    delete FileMenu;
    delete editMenu;
    delete toolsMenu;
    delete optionsMenu;
    delete helpMenu;
}



void SpreadSheet::createActions()
{
    // --------- New File -------------------
   QPixmap newIcon(":/new_file.png");
   newFile = new QAction(newIcon, "&New", this);
   newFile->setShortcut(tr("Ctrl+N"));


    // --------- open file -------------------
   open = new QAction("&Open", this);
   open->setShortcut(tr("Ctrl+O"));

    // --------- open file -------------------
   save = new QAction("&Save", this);
   save->setShortcut(tr("Ctrl+S"));

    // --------- open file -------------------
   saveAs = new QAction("save &As", this);


    // --------- open file -------------------
   QPixmap cutIcon(":/cut_icon.png");
   cut = new QAction(newIcon, "Cu&t", this);
   cut->setShortcut(tr("Ctrl+X"));

   // --------- Cut menu -----------------
   copy = new QAction( "&Copy", this);
   copy->setShortcut(tr("Ctrl+C"));


   paste = new QAction( "&Paste", this);
   paste->setShortcut(tr("Ctrl+V"));


   deleteAction = new QAction( "&Delete", this);
   deleteAction->setShortcut(tr("Del"));

   row  = new QAction("&Row", this);
   Column = new QAction("&Column", this);
   all = new QAction("&All", this);
   all->setShortcut(tr("Ctrl+A"));
  QPixmap findIcon(":/search_icon.png"); find= new QAction(newIcon, "&Find", this);
   find->setShortcut(tr("Ctrl+F"));

   QPixmap goCellIcon(":/go_to_icon.png");
   goCell = new QAction( goCellIcon, "&Go to Cell", this);
   deleteAction->setShortcut(tr("f5"));


   recalculate = new QAction("&Recalculate",this);
   recalculate->setShortcut(tr("F9"));


   sort = new QAction("&Sort");



   showGrid = new QAction("&Show Grid");
   showGrid->setCheckable(true);
   showGrid->setChecked(spreadsheet->showGrid());

 //  recentFiles = new QAction("&Auto-recalculate");
  // auto_recalculate->setCheckable(true);
  // auto_recalculate->setChecked(true);



   about =  new QAction("&About");
   aboutQt = new QAction("About &Qt");

    // --------- exit -------------------
   QPixmap exitIcon(":/quit_icon.png");
   exit = new QAction(exitIcon,"&Exit", this);
   exit->setShortcut(tr("Ctrl+Q"));
}

void SpreadSheet::close()
{

    auto reply = QMessageBox::question(this, "Exit",
                                       "Do you really want to quit?");
    if(reply == QMessageBox::Yes)
        qApp->exit();
}

void SpreadSheet::createMenus()
{
    // --------  File menu -------//
    FileMenu = menuBar()->addMenu("&File");
    FileMenu->addAction(newFile);
    FileMenu->addAction(open);
    FileMenu->addAction(save);
    FileMenu->addAction(saveAs);
    FileMenu->addSeparator();
    FileMenu->addAction(exit);


    //------------- Edit menu --------/
    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(cut);
    editMenu->addAction(copy);
    editMenu->addAction(paste);
    editMenu->addAction(deleteAction);
    editMenu->addSeparator();
    auto select = editMenu->addMenu("&Select");
    select->addAction(row);
    select->addAction(Column);
    select->addAction(all);

    //auto recentFiles = editMenu->addMenu("&Recent Files");

     //recentFiles->addAction(RecentFile[0]);
    // recentFiles->addAction(RecentFile[1]);
     /*recentFiles->addAction(RecentFile[2]);
     recentFiles->addAction(RecentFile[3]);
     recentFiles->addAction(RecentFile[4]);
     recentFiles->addSeparator();
     */
    // recentFiles->addAction(clearAll);
    editMenu->addAction(find);
    editMenu->addAction(goCell);



    //-------------- Toosl menu ------------
    toolsMenu = menuBar()->addMenu("&Tools");
    toolsMenu->addAction(recalculate);
    toolsMenu->addAction(sort);



    //Optins menus
    optionsMenu = menuBar()->addMenu("&Options");
    optionsMenu->addAction(showGrid);
    optionsMenu->addAction(recalculate);


    //----------- Help menu ------------
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(about);
    helpMenu->addAction(aboutQt);
}

void SpreadSheet::createToolBars()
{

    //Crer une bare d'outils
    auto toolbar1 = addToolBar("File");


    //Ajouter des actions acette bar
    toolbar1->addAction(newFile);
    toolbar1->addAction(save);
    toolbar1->addSeparator();
    toolbar1->addAction(exit);


    //Creer une autre tool bar
    auto toolbar2  = addToolBar("ToolS");
    toolbar2->addAction(goCell);
}

void SpreadSheet::updateStatusBar(int row, int col)
{
    QString cell{"(%0, %1)"};
   cellLocation->setText(cell.arg(row+1).arg(col+1));

}

void SpreadSheet::makeConnexions()
{

   // --------- Connexion for the  select all action ----/
   connect(all, &QAction::triggered,
           spreadsheet, &QTableWidget::selectAll);

   // Connection for the  show grid
   connect(showGrid, &QAction::triggered,
           spreadsheet, &QTableWidget::setShowGrid);

   //Connection for the exit button
   connect(exit, &QAction::triggered, this, &SpreadSheet::close);


   //connectting the chane of any element in the spreadsheet with the update status bar
   connect(spreadsheet, &QTableWidget::cellClicked, this,  &SpreadSheet::updateStatusBar);
   connect(goCell, &QAction::triggered, this, &SpreadSheet::goCellSlot);
   connect(find, &QAction::triggered, this, &SpreadSheet::goFindSlot);
   //Connexion for the saveFile
   connect(save, &QAction::triggered, this, &SpreadSheet::saveSlot);
   connect(open, &QAction::triggered, this, &SpreadSheet::openSlot);
   connect(newFile, &QAction::triggered, this, &SpreadSheet::newSlot);
   connect(sort, &QAction::triggered, this, &SpreadSheet::sortSlot);
   connect(row, &QAction::triggered,this,&SpreadSheet::SelectRowSlot);
   connect(Column,&QAction::triggered,this,&SpreadSheet::SelectColSlot);
  connect(copy, &QAction::triggered,this,&SpreadSheet::copySlot);
  connect(paste, &QAction::triggered,this,&SpreadSheet::pasteSlot);
  connect(deleteAction,&QAction::triggered,this,&SpreadSheet::deleteSlot);
  connect(saveAs,&QAction::triggered,this,&SpreadSheet::SaveAsSlot);
}

void SpreadSheet::saveContent(QString filename) const
{
    //Gettign a pointer on the file
       QFile file(filename);

       //Openign the file
       if(file.open(QIODevice::WriteOnly))  //Opening the file in writing mode
       {
           //Initiating a stream using the file
           QTextStream out(&file);

           //loop to save all the content
           for(int i=0; i < spreadsheet->rowCount();i++){
               for(int j=0; j < spreadsheet->columnCount(); j++)
               {
                   auto cell = spreadsheet->item(i, j);

                   //Cecking if the cell is non empty
                   if(cell)
                       out << i << ", "<< j << ", " << cell->text()<<Qt::endl;
               }
            }
       }
       file.close();
}



void SpreadSheet::goCellSlot()
{
    //Creating the dialog
    Dialog1 D;

    //Executing the dialog and storing the user response
    auto reply = D.exec();

    //Checking if the dialog is accepted
    if(reply == Dialog1::Accepted)
    {

        //Getting the cell text
        auto cell = D.cell_();

        //letter distance
        int row = cell[0].toLatin1() - 'A';
        cell.remove(0,1);

        //second coordinate
        int col =  cell.toInt();


        //changing the current cell
        spreadsheet->setCurrentCell(row, col-1);
    }
}
void SpreadSheet::saveSlot()
{
    //Creating a file dialog to choose a file graphically
        auto dialog = new QFileDialog;

        //Check if the current file has a name or not
        if(CurrentFile == "")
        {
           CurrentFile = dialog->getSaveFileName();
           //Update the window title with the file name
           setWindowTitle(CurrentFile);
        }

       //If we have a name simply save the content
        if( CurrentFile != "")
         {
                 saveContent(CurrentFile);
         }
}
void SpreadSheet::openFile(QString filename)
{
    spreadsheet->clearContents();
    QFile file(filename);

    if(file.open(QIODevice::ReadOnly))
    {
      //  QTextStream stream(&file);
        QTextStream in(&file);
        QString line;
        while (!in.atEnd()){
         line = in.readLine();
         QStringList s1 = line.split(QChar(','));

         int r=s1[0].toInt();
         int c=s1[1].toInt();
        spreadsheet->item(r, c)->setText(s1[2]);

        }
   file.close();
    }
}

void SpreadSheet::saveAsContent(QString filename) const
{
    QFile file(filename);

   file.rename(filename,CurrentFile);


}



void SpreadSheet::openSlot()
{
/*
       //Creating a file dialog to choose a file graphically
        auto dialog = new QFileDialog(this);

    //   QString file = dialog->getOpenFileName(this,"choose your file");

        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Text file"), "");

        openFile(fileName);
*/
     QFileDialog dialog;

 //   QString file = dialog->getOpenFileName(this,"choose your file");

     QString fileName = dialog.getOpenFileName();
     CurrentFile = fileName;
     openFile(fileName);

}

void SpreadSheet::goFindSlot()
{
    //Creating the dialog
    Dialog2 D;

    //Executing the dialog and storing the user response
    auto rep = D.exec();
    auto text = D.cell1();
    if(rep == QDialog::Accepted){
    for(int i=0;i<spreadsheet->rowCount();i++){
        for(int j=0;j<spreadsheet->columnCount();j++){

            if(spreadsheet->item(i,j) && spreadsheet->item(i,j)->text()==text)
            {
                       spreadsheet->setCurrentCell(i,j);
            }
                 }
    }
}

}

void SpreadSheet::newSlot()
{
    /*
    QTableWidget *spreadsheet1 = new QTableWidget;
    spreadsheet1->setRowCount(22);
    spreadsheet1->setColumnCount(10);
    spreadsheet1->setVerticalHeaderLabels({"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"});
    setCentralWidget(spreadsheet1);
    */

     //spreadsheet->clear();

     Dialog4 D;

     //Executing the dialog and storing the user response
     auto rep = D.exec();
     if(rep == QDialog::Accepted){
        saveSlot();
     }
       spreadsheet->clear();









}

void SpreadSheet::sortSlot()
{
    Dialog3 D;
   auto rep = D.exec();
     auto num = D.cell3().toInt();
   if(rep == QDialog::Accepted){
  spreadsheet->sortItems(num,Qt::AscendingOrder);
   }
}

void SpreadSheet::copySlot()
{

    QApplication::clipboard()->clear();
    if(spreadsheet->currentItem()){
   QApplication::clipboard()->setText(spreadsheet->currentIndex().data().toString());
}


}
//spreadsheet->item(1,2)->setText("abc");


/*
const QClipboard *clipboard = QApplication::clipboard();
const QMimeData *mimeData = clipboard->mimeData();

 auto i =  spreadsheet->currentIndex().row();
 auto j= spreadsheet->currentIndex().column();
 auto text = QApplication::clipboard()->text();
spreadsheet->item(i,j)->setText(text);
*/
 /*if(mimeData->hasText()){
    auto text = mimeData->text();
   spreadsheet->item(i,j)->setText("abc");

   }
   */
void SpreadSheet::pasteSlot()
{

    auto col_ =spreadsheet->currentIndex().column();
    auto row_ =spreadsheet->currentIndex().row();
   auto text = QApplication::clipboard()->text();
  spreadsheet->item(row_,col_)->setText( QApplication::clipboard()->text());
}

void SpreadSheet::SelectRowSlot()
{
    spreadsheet->selectRow(spreadsheet->currentIndex().row());


}

void SpreadSheet::SelectColSlot()
{

    spreadsheet->selectColumn(spreadsheet->currentIndex().column());

}

void SpreadSheet::deleteSlot()
{

    auto col_ =spreadsheet->currentIndex().column();
    auto row_ =spreadsheet->currentIndex().row();
    spreadsheet->item(row_, col_)->setText("");

}

void SpreadSheet::SaveAsSlot()
{
    auto dialog = new QFileDialog;

    //Check if the current file has a name or not

        if(CurrentFile != ""){
       CurrentFile = dialog->getSaveFileName();
       //Update the window title with the file name
       setWindowTitle(CurrentFile);
    saveAsContent(CurrentFile);
        }else{
             CurrentFile = dialog->getSaveFileName();
              saveContent(CurrentFile);
        }

}

void SpreadSheet::RecentFilesSlot()
{

}

