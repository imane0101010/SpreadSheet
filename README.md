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

### Connection for GoCell Action:
``` cpp
connect(goCell, &QAction::triggered, this, &SpreadSheet::goCellSlot);
 ```
### Its Slot:
 
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
### Connection for Find Action: 
``` cpp

connect(find, &QAction::triggered, this, &SpreadSheet::goFindSlot);
```
### Its Slot:
``` cpp

void SpreadSheet::goFindSlot()
{
    //Creating the dialog
    Dialog2 D;

    //Executing the dialog and storing the user response
    auto rep = D.exec();
    //Storing the content of the cell in text
    auto text = D.cell1();
    if(rep == QDialog::Accepted){
    for(int i=0;i<spreadsheet->rowCount();i++){
        for(int j=0;j<spreadsheet->columnCount();j++){
        //Iterating over cells and check if the cells contains the text stored in the variable
            if(spreadsheet->item(i,j) && spreadsheet->item(i,j)->text()==text)
                      spreadsheet->setCurrentCell(i,j):
    }
    }
    }
```
### Connection for Save Action:
``` cpp
connect(save, &QAction::triggered, this, &SpreadSheet::saveSlot);
```
### Its Slot:
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
### Connection for NewFile Action:
``` cpp
connect(newFile, &QAction::triggered, this, &SpreadSheet::newSlot);
```
### Its Slot:
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
### Connection for Sort Action:
``` cpp
connect(sort, &QAction::triggered, this, &SpreadSheet::sortSlot);
```
### Its Slot:
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
### Connection for Select Row Action:
```cpp
connect(row, &QAction::triggered,this,&SpreadSheet::SelectRowSlot);
```
### Its Slot:
``` cpp
void SpreadSheet::SelectRowSlot()
{
    spreadsheet->selectRow(spreadsheet->currentIndex().row());
}
```
### Connection for Select Column Action :
``` cpp
connect(Column,&QAction::triggered,this,&SpreadSheet::SelectColSlot);
```
### Its slot:
``` cpp
void SpreadSheet::SelectColSlot()
{
    spreadsheet->selectColumn(spreadsheet->currentIndex().column());
}
```
### Connection for Copy Action:
``` cpp
connect(copy, &QAction::triggered,this,&SpreadSheet::copySlot);
```
### Its Slot:
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
### Connection of the paste Action:
``` cpp
connect(paste, &QAction::triggered,this,&SpreadSheet::pasteSlot);
```
### Its Slot:
```cpp
void SpreadSheet::pasteSlot()
{
   // Store the content of the clipboard in a variable
   auto text = QApplication::clipboard()->text();
   // Pasting the text in the selected cell
     spreadsheet->setItem(spreadsheet->currentRow(),spreadsheet->currentColumn(),new QTableWidgetItem(text));
}
```
### Connection for Delete Action:
```cpp
connect(deleteAction,&QAction::triggered,this,&SpreadSheet::deleteSlot);
```
### Its Slot:
```cpp
void SpreadSheet::deleteSlot()
{
    auto col_ =spreadsheet->currentIndex().column();
    auto row_ =spreadsheet->currentIndex().row();
    spreadsheet->item(row_, col_)->setText("");
}
```
### Connection for Cut Action:
```cpp
connect(cut,&QAction::triggered,this,&SpreadSheet::cutSlot);
```
### Its Slot:

```cpp
void SpreadSheet::cutSlot()
{
copySlot();
deleteSlot();
}
```
### Connection for OpenFile Action that can open both textfile and csv file:
```cpp
connect(open, &QAction::triggered, this, &SpreadSheet::openSlot);
```
### Its Slot:
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
### Connection for Save As Action:
```cpp
 connect(saveAs,&QAction::triggered,this,&SpreadSheet::SaveAsSlot);
 ```
 ### Its Corresponding slot:
 ```cpp
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
             CurrentFile = dialog->getSaveFileName(this, tr("Open File"),NULL,
             "TXT - Text file (*.txt);;CSV - Csv file (*.csv)");
              saveContent(CurrentFile);
              }
}
```
### And for SaveAsContent method:
```cpp
void SpreadSheet::saveAsContent(QString filename)
{
    QFile file(filename);
     saveContent(CurrentFile);   
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
## Central Widget

 QMainWindow has to define a central Widget that represent its core functionality. Using polymorphism, we could put any class that inherit from QWidget. Hence the content for this slot varies from a simple widget to a complicated one with a deep hierarchy.

For our SpreadSheet case, we only need a simple widget which is QTableWidget.

Here the code to add in the constructor:
```cpp
spreadsheet = new QTableWidget;
 spreadsheet->setRowCount(26);
spreadsheet->setColumnCount(10);
 setCentralWidget(spreadsheet);
```
![image](https://github.com/imane0101010/SpreadSheet/blob/fbf62f506d5efb91def4ae87f12fd96efe1dcbe2/File.png)
![image](https://github.com/imane0101010/SpreadSheet/blob/fbf62f506d5efb91def4ae87f12fd96efe1dcbe2/Edit.png)

## Recent Files:
In order to add to the menu the 5 recent opened files,I proceded as follows:

*  **First,let´s create 5 actions and their connection :**
```cpp
        //Create recentFiles QAction
        QAction *recentFiles[5];
      //Add recent Files to the editMenu
     auto  recentFile = editMenu->addMenu("&Recent Files");
     for(auto i =0 ;i<5;i++){
         recentFiles[i] =new QAction(this);
         //Set Visibility of 
         recentFiles[i]->setVisible(true);
         //Add each action to recentFiles
         recentFile->addAction(recentFiles[i]);
         // Make Connections
         QObject::connect(recentFiles[i],SIGNAL(triggered()),this,SLOT(RecentFilesSlot()));
       //Updating RecentFiles Action 
         updateRecentAction();
}
```
*  **Then,let´s implement the updateRecentAction method:**
```cpp
void SpreadSheet::updateRecentAction()
{
  // we construct the QSettings object. The settings will be stored in a file which we 
  //named qsettingsexample.ini in the format QSettings::IniFormat.
   QSettings settings("SpreadSheet", QSettings::IniFormat);
   //
    QStringList recentFileList = settings.value("recentFileList").toStringList();
    //Returns min of 5 and size of recentFilelist
    int numRecentFiles = qMin(recentFileList.size(),5);
    for(int i=0;i<numRecentFiles;i++){
        QString text=tr("&%1 %2").arg(i+1).arg(QFileInfo(recentFileList[i]).fileName());
         recentFiles[i]->setText(text);
         recentFiles[i]->setData(recentFileList[i]);
         recentFiles[i]->setVisible(true);
    }
    for(int j =numRecentFiles;j>5;j--){
        recentFiles[j]->setVisible(false);
    }
}
```
*  **Now, we will implement the RecentFiles Slot:**
```cpp
void SpreadSheet::RecentFilesSlot()
{
//sender() will get the value of the sender of the signal an return a pointer to the object that called it.
//qobject_cast will then use it's argument (sender()) to cast it to the specified type(QAction).
QAction *a = qobject_cast<QAction *>(sender());
//Make sure that a isn´t a nullpointer
 if(a){
 // Open the file
    openFile(a->data().toString());
}
}
```
![image](https://github.com/imane0101010/SpreadSheet/blob/fbf62f506d5efb91def4ae87f12fd96efe1dcbe2/TRecentFiles.png)
### NB:
For the dialogs used in the previous parts , we might use qt designer to create widgets,layout and slots.Personaly,I prefer creating dialogs using code.Here is a sample:
* **Dialog 3:**
```cpp
    void createWidgets();
    void placeWidgets();
    QString cell3() const;
    QPushButton* ok ;
    QPushButton* cancel;
    QLabel * col ;
    QHBoxLayout * Hlay1 ;
    QHBoxLayout * Hlay2 ;
    QVBoxLayout *Layout ;
```
```cpp
Implemetation of createWidget method:
void Dialog3::createWidgets()
{
   ok = new QPushButton("ok");
   cancel = new QPushButton("Cancel");
    line = new QLineEdit();
   col = new QLabel("Col:");
    Hlay1 = new QHBoxLayout;
    Hlay2 = new QHBoxLayout;
    Layout = new QVBoxLayout;
    HLayr = new QVBoxLayout;
    R1 = new QRadioButton;
    R2 =new QRadioButton;
}
Implementation of place Widgets method
void Dialog3::placeWidgets()
{
       setLayout(Layout);
       ok->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
       cancel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
       Hlay2->addSpacing(20);
       Hlay1->addWidget(col);
       Hlay1->addWidget(line);
       R1->setText("Ascending");
       R2->setText("Descending");
       HLayr->addWidget(R1);
       HLayr->addWidget(R2);
       Hlay2->addWidget(ok);
       Hlay2->addWidget(cancel);
       Layout->addLayout(Hlay1);
       Layout->addLayout(HLayr);
       Layout->addLayout(Hlay2);

}
Creating a getter so as to have access to the private content :
QString Dialog3::cell3() const
{
    return line->text();
}
```
Making connections:
```cpp
 connect(ok, &QPushButton::clicked, this, &QDialog::accept);
 connect(cancel, &QPushButton::clicked, this, &QDialog::reject);
```
![image](https://github.com/imane0101010/SpreadSheet/blob/fbf62f506d5efb91def4ae87f12fd96efe1dcbe2/Search.png)




 
