#ifndef FILEDIALOG_HPP
#define FILEDIALOG_HPP

#include <QDialog>
#include <qfilesystemmodel.h>

namespace Ui {
class FileDialog;
}

class FileDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit FileDialog(QWidget *parent = 0);
    ~FileDialog();
    
private slots:
    void on_folder_changed(QModelIndex indexA, QModelIndex);

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

public:
    QString getSelectedPath();

private:
    Ui::FileDialog *ui;
    QFileSystemModel filesModel;

};

#endif // FILEDIALOG_HPP
