#ifndef FILEDIALOG_HPP
#define FILEDIALOG_HPP

#include <QDialog>

namespace Ui {
class FileDialog;
}

class FileDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit FileDialog(QWidget *parent = 0);
    ~FileDialog();
    
private:
    Ui::FileDialog *ui;
};

#endif // FILEDIALOG_HPP
