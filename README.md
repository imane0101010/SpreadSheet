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
    ``` cpp
    connect(goCell, &QAction::triggered, this, &SpreadSheet::goCellSlot);
   connect(find, &QAction::triggered, this, &SpreadSheet::goFindSlot);
   //Connexion for the saveFileMenus
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
```
###
