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

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWidget = new QWidget();
    listItem = new std::vector<QListWidgetItem*>();
    fileInfoList = new std::vector<FileInfo*>();
    setWindowTitle("Wiper");
    setFixedSize(800,600);
    mainLayout = new QHBoxLayout();
    mainWidget->setLayout(mainLayout);
    createToolbar();
    addToolBar(mainToolBar);
    //createStatusBar();
    createWidgetItems();
    setCentralWidget(mainWidget);
    setSideBar();
    //Connect calls to toolbar functions.
    connect(aboutAction, SIGNAL(triggered(bool)), this , SLOT(about()));
    connect(clearAction,SIGNAL(triggered(bool)),this,SLOT(clear()));
    connect(openAction, SIGNAL(triggered(bool)),this,SLOT(open()));
    connect(delAction,SIGNAL(triggered(bool)),this,SLOT(del()));
    connect(fileListWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(updateSideBarInfo()));

}

MainWindow::~MainWindow()
{
    delete delAction;
    delete openAction;
    delete clearAction;
    delete aboutAction;
    delete mainToolBar;
    delete listItem;
    delete fileInfoList;
}

void MainWindow::about()
{
    QMessageBox::about(this,tr("Wiper"),
                       tr("The <b>Wiper</b> deletes file from the disk using disk mapped lba's\n"
                          "Developed by <b><i>Anurag Tripathi</i></b>"));
}

void MainWindow::open()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    addItemToList(fileNames[0]);

}

void MainWindow::del()
{
    QMessageBox::about(this,tr("Not implemented"),
                       tr("This feature is not implemented, will be implemented soon"));
}

void MainWindow::clear()
{
    fileListWidget->clear();
    //for(std::vector<QListWidgetItem*>::iterator it = listItem->begin(); it != listItem->end(); ++it) {
    //   delete(*it);
    //}
    listItem->clear();
    printf("size:%ld",listItem->size());

}

void MainWindow::createToolbar()
{
    mainToolBar = new QToolBar(this);
    delAction = new QAction("&Delete",this);
    aboutAction = new QAction("&About",this);
    openAction = new QAction("&Open",this);
    clearAction = new QAction("&Clear",this);

    mainToolBar->addAction(openAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(delAction);
    mainToolBar->addAction(clearAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(aboutAction);


}

void MainWindow::createWidgetItems()
{

    QHBoxLayout *fileListLayout = new QHBoxLayout();
    fileListWidget = new QListWidget();
    fileListLayout->addWidget(fileListWidget);
    mainLayout->addLayout(fileListLayout);
    mainLayout->setStretchFactor(fileListLayout,2);


}

void MainWindow::addItemToList(QString listName)
{

    listItem->push_back(new QListWidgetItem(listName,fileListWidget));
    fileInfoList->push_back(new FileInfo(std::string(listName.toUtf8().constData())));
}

void MainWindow::setSideBar()
{


    QHBoxLayout *sideMainLayout = new QHBoxLayout();
    QGridLayout *sideBarLayout = new QGridLayout();

    //QLabel *blkDevHLabel = new QLabel(this);
    //blkDevHLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    //blkDevHLabel->setText("<b>Block Device Info</b>");

    QLabel *fileHLabel = new QLabel(this);
    fileHLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    fileHLabel->setText("<b>File Info</b>");

    //QLabel *blksHLabel = new QLabel(this);
    //blksHLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    //blksHLabel->setText("<b>Blocks</b>");

    QLabel *devLabel = new QLabel(this);
    devLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    devLabel->setText("<b>Device</b>");

    QLabel *inodeLabel = new QLabel(this);
    inodeLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    inodeLabel->setText("<b>Inode</b>");

    QLabel *modeLabel = new QLabel(this);
    modeLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    modeLabel->setText("<b>Mode</b>");

    QLabel *nlinkLabel = new QLabel(this);
    nlinkLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    nlinkLabel->setText("<b>NLink</b>");

    QLabel *uidLabel = new QLabel(this);
    uidLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    uidLabel->setText("<b>UID</b>");

    QLabel *gidLabel = new QLabel(this);
    gidLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    gidLabel->setText("<b>GID</b>");

    QLabel *sizeLabel = new QLabel(this);
    sizeLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    sizeLabel->setText("<b>Size</b>");

    QLabel *blkSizeLabel = new QLabel(this);
    blkSizeLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    blkSizeLabel->setText("<b>Block Size</b>");

    QLabel *blksLabel = new QLabel(this);
    blksLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    blksLabel->setText("<b>Blocks</b>");


    devField = new QLabel(this);
    devField->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    devField->setText(" ");

    inodeField = new QLabel(this);
    inodeField->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    inodeField->setText(" ");


    modeField = new QLabel(this);
    modeField->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    modeField->setText(" ");

    nlinkField = new QLabel(this);
    nlinkField->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    nlinkField->setText(" ");

    uidField = new QLabel(this);
    uidField->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    uidField->setText(" ");

    gidField = new QLabel(this);
    gidField->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    gidField->setText(" ");

    sizeField = new QLabel(this);
    sizeField->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    sizeField->setText(" ");

    blkSizeField = new QLabel(this);
    blkSizeField->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    blkSizeField->setText(" ");

    blksField = new QLabel(this);
    blksField->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    blksField->setText(" ");

    //sideBarLayout->addWidget(blkDevHLabel,0,0,1,2,Qt::AlignCenter);

    sideBarLayout->addWidget(fileHLabel,0,0,1,2,Qt::AlignCenter);
    sideBarLayout->addWidget(devLabel,1,0,1,1,Qt::AlignLeft);
    sideBarLayout->addWidget(inodeLabel,2,0,1,1,Qt::AlignLeft);
    sideBarLayout->addWidget(modeLabel,3,0,1,1,Qt::AlignLeft);
    sideBarLayout->addWidget(nlinkLabel,4,0,1,1,Qt::AlignLeft);
    sideBarLayout->addWidget(uidLabel,5,0,1,1,Qt::AlignLeft);
    sideBarLayout->addWidget(gidLabel,6,0,1,1,Qt::AlignLeft);
    sideBarLayout->addWidget(sizeLabel,7,0,1,1,Qt::AlignLeft);
    sideBarLayout->addWidget(blkSizeLabel,8,0,1,1,Qt::AlignLeft);
    sideBarLayout->addWidget(blksLabel,9,0,1,1,Qt::AlignLeft);

    sideBarLayout->addWidget(devField,1,1,1,1,Qt::AlignRight);
    sideBarLayout->addWidget(inodeField,2,1,1,1,Qt::AlignRight);
    sideBarLayout->addWidget(modeField,3,1,1,1,Qt::AlignRight);
    sideBarLayout->addWidget(nlinkField,4,1,1,1,Qt::AlignRight);
    sideBarLayout->addWidget(uidField,5,1,1,1,Qt::AlignRight);
    sideBarLayout->addWidget(gidField,6,1,1,1,Qt::AlignRight);
    sideBarLayout->addWidget(sizeField,7,1,1,1,Qt::AlignRight);
    sideBarLayout->addWidget(blkSizeField,8,1,1,1,Qt::AlignRight);
    sideBarLayout->addWidget(blksField,9,1,1,1,Qt::AlignRight);

    //sideBarLayout->addWidget(blksHLabel,0,0,1,2,Qt::AlignCenter);

    sideMainLayout->addLayout(sideBarLayout);
    sideMainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(sideMainLayout);
    mainLayout->setStretchFactor(sideMainLayout,1);

}

void MainWindow::updateSideBarInfo()
{
    QMessageBox::about(this,tr("Wiper"),
                       tr("Focus Changed"));
}
