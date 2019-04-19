/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QWidget>
#include <QFileDialog>
#include <QGridLayout>
#include <fileinfo.h>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createToolbar();
    void createWidgetItems();
    void addItemToList(QString listName);
    void setSideBar();
    void addFileInfo();
    void addBlockInfo();
private:
    QToolBar *mainToolBar;
    QAction *delAction;
    QAction *aboutAction;
    QAction *openAction;
    QAction *clearAction;
    QListWidget *fileListWidget;\
    QHBoxLayout *mainLayout;
    std::vector<QListWidgetItem*> *listItem;
    std::vector<FileInfo*> *fileInfoList;
    QWidget *mainWidget;


    //FileInfo Fields
    QLabel *devField;
    QLabel *inodeField;
    QLabel *modeField;
    QLabel *nlinkField;
    QLabel *uidField;
    QLabel *gidField;
    QLabel *sizeField;
    QLabel *blkSizeField;
    QLabel *blksField;

private slots:
    void about();
    void open();
    void del();
    void clear();
    void updateSideBarInfo();
};

#endif // MAINWINDOW_H
