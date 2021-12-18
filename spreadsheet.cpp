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
#include <QSettings>


SpreadSheet::SpreadSheet(QWidget *parent)
    : QMainWindow(parent)
{
    //Seting the spreadsheet

    setupMainWidget();

    // Creaeting Actions
    createActions();

    // Creating Menus
    createMenus();



  updateRecentAction();



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

    // --------- Save file -------------------
   QPixmap saveIcon(":/save_file.png");
   save = new QAction(saveIcon,"&Save", this);
   save->setShortcut(tr("Ctrl+S"));

    // --------- Save As file -------------------
   saveAs = new QAction("save &As", this);
    saveAs->setShortcut(tr("F12"));

    // --------- Cut file -------------------
   QPixmap cutIcon(":/cut.png");
   cut = new QAction(cutIcon, "&Cut", this);
   cut->setShortcut(tr("Ctrl+X"));

   // --------- Copy menu -----------------
   QPixmap copyIcon(":/copy.png");
   copy = new QAction(copyIcon,"&Copy", this);
   copy->setShortcut(tr("Ctrl+C"));

    QPixmap pasteIcon(":/paste.png");
   paste = new QAction(pasteIcon,"&Paste", this);
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


     auto  recentFile = editMenu->addMenu("&Recent Files");
     for(auto i =0 ;i<5;i++){
         recentFiles[i] =new QAction(this);
         recentFiles[i]->setVisible(true);
         recentFile->addAction(recentFiles[i]);
         QObject::connect(recentFiles[i],SIGNAL(triggered()),this,SLOT(RecentFilesSlot()));

         updateRecentAction();

     }

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
   connect(all, &QAction::triggered,spreadsheet, &QTableWidget::selectAll);
   // Connection for the  show grid
   connect(showGrid, &QAction::triggered,spreadsheet, &QTableWidget::setShowGrid);
    //Connection for the exit button
   connect(exit, &QAction::triggered, this, &SpreadSheet::close);
   //connectting the chane of any element in the spreadsheet with the update status bar
   connect(spreadsheet, &QTableWidget::cellClicked, this,&SpreadSheet::updateStatusBar);
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
   connect(cut,&QAction::triggered,this,&SpreadSheet::cutSlot);
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
           CurrentFile = dialog->getSaveFileName(this, tr("Save File"),NULL, "TXT - Text file (*.txt);;CSV - Csv file (*.csv)");
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
    setCurrentFile(filename);
    QString Alldata;
    QFile importedCSV(filename);
    QStringList rowOfData;
    QStringList rowData;
    Alldata.clear();
    rowOfData.clear();
    rowData.clear();

if (importedCSV.open(QFile::ReadOnly))
{
    //Reads all data from the , and returns it as a byte array.
    Alldata = importedCSV.readAll();
    rowOfData = Alldata.split("\n");           //Value on each row
    importedCSV.close();
}

for (int x = 0; x < rowOfData.size(); x++)  //rowOfData.size() gives the number of row
{
    rowData = rowOfData.at(x).split(",");   //Number of collumn

    for (int y = 0; y < rowData.size(); y++)
    {
        spreadsheet->setItem(x,y,new QTableWidgetItem(rowData[y]));
    }
}

    }

void SpreadSheet::saveAsContent(QString filename)
{
    QFile file(filename);
     saveContent(CurrentFile);

}

void SpreadSheet::updateRecentAction()
{

   QSettings settings("SpreadSheet");
 //settings.clear();
    //settings.setDefaultFormat(QSettings::IniFormat);
    QStringList recentFileList = settings.value("recentFileList").toStringList();
    int numRecentFiles = qMin(recentFileList.size(),5);
    for(int i=0;i<numRecentFiles;i++){
        QString text=tr("&%1 %2").arg(i+1).arg(QFileInfo(recentFileList[i]).fileName());

         recentFiles[i]->setText(text);
         recentFiles[i]->setData(recentFileList[i]);
         recentFiles[i]->setVisible(true);
    }
    for(int j =numRecentFiles;j>5;j++){
        recentFiles[j]->setVisible(false);
    }
}


void SpreadSheet::setCurrentFile(const QString &filename)
{

    CurrentFile =filename;
    setWindowTitle(tr("SpreadSheet -%1[*]").arg(QFileInfo(CurrentFile).fileName()));
    QSettings setting("SpreadSheet");
    setting.setDefaultFormat(QSettings::IniFormat);
    QStringList recentfileslist =setting.value("recentFileList").toStringList();
    recentfileslist.removeAll(filename);
    recentfileslist.prepend(filename);
    while(recentfileslist.size()>5){
      recentfileslist.removeLast();
    }
      setting.setValue("recentFileList",recentfileslist);
      updateRecentAction();

      }
void SpreadSheet::openSlot()
{

       //Creating a file dialog to choose a file graphically
     QFileDialog dialog;
     QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),NULL, "TXT - Text file (*.txt);;CSV - Csv file (*.csv)");

        CurrentFile =fileName;
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

     Dialog4 D;

     //Executing the dialog and storing the user response
     auto rep = D.exec();
     if(rep == QDialog::Accepted){
        saveSlot();
     }
     //Clearing the content of spreadsheet
       spreadsheet->clear();
       CurrentFile ="";
        setWindowTitle("SpreadSheet");

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

void SpreadSheet::pasteSlot()
{


   auto text = QApplication::clipboard()->text();

     spreadsheet->setItem(spreadsheet->currentRow(),spreadsheet->currentColumn(),new QTableWidgetItem(text));
}


void SpreadSheet::cutSlot()
{
copySlot();
deleteSlot();


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
             CurrentFile = dialog->getSaveFileName(this, tr("Open File"),NULL, "TXT - Text file (*.txt);;CSV - Csv file (*.csv)");
              saveContent(CurrentFile);
        }

}

void SpreadSheet::RecentFilesSlot()
{
    //Storing  the given object cast to type QAction if the object is of type QAction or a nullpointer otherwise
QAction *a = qobject_cast<QAction *>(sender());
 if(a){
    openFile(a->data().toString());
}

}



