# SpreadSheet
## Introduction
A main window provides a framework for building an application's user interface. Qt has QMainWindow and its related classes for main window management. QMainWindow has its own layout to which you can add QToolBars, QDockWidgets, a QMenuBar, and a QStatusBar. The layout has a center area that can be occupied by any kind of widget.
In this lab ,the main component of an application is the QMainWindow. Many techniques of creating dialogs and widgets are relevant for creating main windows, since both QDialog and QMainWindow inherit from QWidget.
## The Qt resource Management system 
The Qt resource Management system is a platform independent mechanism for storing binary files in the application’s executable. The is useful if you’re application always needs a certain set of files such as:

* [x] **Icons**
* [x] **translations files**
* [x] **Local Database**

The Qt mechanism system is based on tight cooperation between qmake and rcc (Qt resource compiler).In this lab,we will be using icons.

## Creating menus and toolbars
Before creating any application, we need to carefully think about it’s features and Functionality. This will give us a list of actions that the application could perform .
* [x] **It should be able to create files**
* [x] **It can load or open new files**
* [x] **It has to save spreadsheets.**
* [x] **An application should be able to close itself**
* [x] **Our application need to Go to any cell.**
* [x] **also Find a text.**

### Actions
In applications many common commands can be invoked via menus, toolbar buttons, and keyboard shortcuts. Since the user expects each command to be performed in the same way, regardless of the user interface used, it is useful to represent each command as an action.

This mechanism is implemented in the QAction which offer a way to perform an action trough different ways.

For our case we will add the following actions to our application:

In the spreadsheet.h we will add the following declaration:
 ``` cpp
private:  //private method
   void createActions();   //Function to create all the actions
private:
     QAction * newFile;
    QAction * open;
    QAction * save;
    QAction * saveAs;
    QAction * exit;
    QAction *cut;
    QAction *copy;
    QAction *paste;
    QAction *deleteAction;
    QAction *find;
    QAction *row;
    QAction *Column;
    QAction *all;
    QAction *goCell;
    QAction *recalculate;
    QAction *sort;
    QAction *showGrid;
    QAction *about;
    QAction *aboutQt;
    QAction *clearAll;
```
Now for the implementation on spreadsheet.cpp, we will create each action with its associated icons:
1.Creating the icons:
``` cpp
 QPixmap newIcon(":/new_file.png");
 QPixmap cutIcon(":/cut.png");
 QPixmap copyIcon(":/copy.png");
 QPixmap saveIcon(":/save.png");
 QPixmap pasteIcon(":/paste.png");
```
2.Create the action with its given icon:

``` cpp
cut = new QAction(cutIcon, "&Cut", this);
copy = new QAction(copyIcon, "&Copy", this);
paste = new QAction(pasteIcon, "&Paste", this);
save = new QAction(saveIcon, "&Save", this);
new = new QAction(newIcon, "&NewFile", this);
```
3.Connect the action to it’s associated slot. 
Connection for GoCell Action:
``` cpp

 connect(goCell, &QAction::triggered, this, &SpreadSheet::goCellSlot);
 ```
 It´s Slot:
 
 ```cpp
 
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
        int col =  cell.toInt():
        //changing the current cell
        spreadsheet->setCurrentCell(row, col-1);
    }
}
```
Connection for Find Action: 
``` cpp

connect(find, &QAction::triggered, this, &SpreadSheet::goFindSlot);
```
It´s Slot:
``` cpp

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
```
Connection for Save Action:
``` cpp

connect(save, &QAction::triggered, this, &SpreadSheet::saveSlot);
```
It´s Slot:
```cpp

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
```
Connection for NewFile Action:
``` cpp

connect(newFile, &QAction::triggered, this, &SpreadSheet::newSlot);
```
It´s SLot:

``` cpp
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
```
Connection for Sort Action:
``` cpp
connect(sort, &QAction::triggered, this, &SpreadSheet::sortSlot);
```
It´s Slot:
``` cpp
void SpreadSheet::sortSlot()
{
    Dialog3 D;
   auto rep = D.exec();
     auto num = D.cell3().toInt();
   if(rep == QDialog::Accepted){
  spreadsheet->sortItems(num,Qt::AscendingOrder);
   }
}
```
Connection for Select Row Action:
```cpp

connect(row, &QAction::triggered,this,&SpreadSheet::SelectRowSlot);
```
It´s Slot:
``` cpp

void SpreadSheet::SelectRowSlot()
{
    spreadsheet->selectRow(spreadsheet->currentIndex().row());
}
```
Connection for Select Column Action :
``` cpp

connect(Column,&QAction::triggered,this,&SpreadSheet::SelectColSlot);
```
It´s slot:

``` cpp

void SpreadSheet::SelectColSlot()
{

    spreadsheet->selectColumn(spreadsheet->currentIndex().column());

}
```
Connection for Copy Action:

``` cpp
connect(copy, &QAction::triggered,this,&SpreadSheet::copySlot);
```
It´s Slot:
```cpp
void SpreadSheet::copySlot()
{
   //Clear the content of the clipboard
    QApplication::clipboard()->clear();
    //Check if the cell is not empty
    if(spreadsheet->currentItem()){
    //Copy the content of the cell to the clipboard
   QApplication::clipboard()->setText(spreadsheet->currentIndex().data().toString());
}
}
```
Connection of the paste Action:
``` cpp
connect(paste, &QAction::triggered,this,&SpreadSheet::pasteSlot);
```
It´s Slot:
```cpp
void SpreadSheet::pasteSlot()
{

  // Store the content of the clipboard in a variable
   auto text = QApplication::clipboard()->text();
   // Pasting the text in the selected cell
     spreadsheet->setItem(spreadsheet->currentRow(),spreadsheet->currentColumn(),new QTableWidgetItem(text));
}
```
Connection for Delete Action:
```cpp
connect(deleteAction,&QAction::triggered,this,&SpreadSheet::deleteSlot);
```
It´s Slot:

```cpp
void SpreadSheet::deleteSlot()
{
      
    auto col_ =spreadsheet->currentIndex().column();
    auto row_ =spreadsheet->currentIndex().row();
    spreadsheet->item(row_, col_)->setText("");

}
```
//connect(saveAs,&QAction::triggered,this,&SpreadSheet::SaveAsSlot);`
Connection for Cut Action:
```cpp
connect(cut,&QAction::triggered,this,&SpreadSheet::cutSlot);
```
It´s Slot:

```cpp
void SpreadSheet::cutSlot()
{
copySlot();
deleteSlot();
}
```
Connection for OpenFile Action that can open both textfile and csv file:
```cpp
connect(open, &QAction::triggered, this, &SpreadSheet::openSlot);
```
It´s Slot:
```cpp
void SpreadSheet::openFile(QString filename)
{

    setCurrentFile(filename);

    QString Alldata; 
    QFile importedFile(filename);
    QStringList rowOfData;
    QStringList rowData;
    Alldata.clear(); 
    rowOfData.clear();
    rowData.clear();
if (importedFile.open(QFile::ReadOnly))
{
     //Reads all data from the importedFile, and stores it as a byte array in AllData.
    Alldata = importedFile.readAll();
    //Split data so as to store it in the list row by row
    rowOfData = Alldata.split("\n");   
    //
    importedFile.close();
}

for (int x = 0; x < rowOfData.size(); x++)  
{
     //Spliting the data so as to store it in the list column by column
    rowData = rowOfData.at(x).split(",");  

    for (int y = 0; y < rowData.size(); y++)
    {
        //Assign each cell its correspondign value
        spreadsheet->setItem(x,y,new QTableWidgetItem(rowData[y]));
    }
}

    }

```
## Menus
 Menus are a way to group actions. They could be as pull down menu in the menu bar or as a standalone context menu.
In Qt, a menu regroup a set of predefined actions. The general approach for creating these menus in Qt is to::

* [x] **Declare the menus in the header file:**
```cpp
    QMenu *FileMenu;
    FileMenu = menuBar()->addMenu("&File");
    QMenu *editMenu;
    editMenu = menuBar()->addMenu("&Edit");
    QMenu *toolsMenu;
    toolsMenu = menuBar()->addMenu("&Tools");
    QMenu *optionsMenu;
    optionsMenu = menuBar()->addMenu("&Options");
    QMenu *helpMenu;
    helpMenu = menuBar()->addMenu("&Help");
```
* [x] **Once they’re declared, we could add actions to them via the:**
   ```cpp
    FileMenu->addAction(newFile);
    FileMenu->addAction(open);
    FileMenu->addAction(save);
    FileMenu->addAction(saveAs);
    FileMenu->addAction(exit);
    editMenu->addAction(cut);
    editMenu->addAction(copy);
    editMenu->addAction(paste);
    editMenu->addAction(deleteAction);
    select->addAction(row);
    select->addAction(Column);
    select->addAction(all);
    ```
* [x] **Sometimes, it is useful to separate actions, we use the simple functional:**
```cpp
FileMenu->addSeparator();
editMenu->addSeparator();
```
* [x] **Also in several situations a menu could have a sub menu.In order to achieve that, we use the method addMenu("name") as following:**
```cpp
 auto select = editMenu->addMenu("&Select");
 ```
 ## ToolBar
 A toolbar provides a movable panel that contains a set of controls. Those controls are generally shortcut for the most used actions.
 
* [x] **Adding a toolbar by a given name:**
```cpp
 auto toolbar1 = addToolBar("File");
auto toolbar2  = addToolBar("Tools");
```
* [x] **Adding a set of actions to the toolbar**
```cpp
toolbar1->addAction(newFile);
toolbar1->addAction(save);
toolbar1->addAction(exit);
toolbar2->addAction(goCell);
```
* [x] **We can add a separator:**
```cpp
toolbar1->addSeparator();
```
## The Status Bar
The QStatusBar provides a horizontal bar suitable for presenting status information. A status message could be one of the following categories:
* [x] ****
* [x] **Temporary: briefly occupies most of the status bar. This is used to explain tooltip text and entires.**
* [x] **Normal: occupies part of the status bar and may be hidden by temporary messages. For example, the information of page number in word.**
* [x] **Permanant: is never hidden. Used for imporetant mode indications.**

In Qt each QMainWindow has a function statusBar() that return a pointer to the current status bar. We can use the status to either:

*  **Add permanent widget using:**
```cpp
    statusBar()->addPermanentWidget(cellLocation);
    statusBar()->addPermanentWidget(cellFormula);
```
*  **Show temporary messages using:**
```cpp
statusBar()->showMessage("Opening a new file", 2000);
  ```
  




 
