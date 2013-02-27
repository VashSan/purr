#include "filedialog.hpp"
#include "ui_filedialog.h"

FileDialog::FileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileDialog)
{
    ui->setupUi(this);

    QStringList filterList;
    filterList.append("*.mp3");
    filterList.append("*.ogg");
    filesModel.setNameFilters(filterList);

    filesModel.setRootPath("/");


    ui->treeView->setModel(&filesModel);

    connect(
        ui->treeView->selectionModel(),
        SIGNAL(currentChanged(QModelIndex,QModelIndex)),
        this,
        SLOT(on_folder_changed(QModelIndex,QModelIndex)));
    // ?
}

FileDialog::~FileDialog()
{
    delete ui;
}

void FileDialog::on_folder_changed(QModelIndex current, QModelIndex )
{
    ui->fileEdit->setText( filesModel.filePath(current) );
}

void FileDialog::on_buttonBox_accepted()
{

}


void FileDialog::on_buttonBox_rejected()
{

}

QString FileDialog::getSelectedPath()
{
    QModelIndex current = ui->treeView->currentIndex();
    QString path = filesModel.filePath(current);
    return path;
}
