#ifndef PURRWINDOW_HPP
#define PURRWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class PurrWindow;
}

class PurrWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PurrWindow(QWidget *parent = 0);
    ~PurrWindow();
    
private slots:
    void on_openButton_clicked();

    void on_playButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::PurrWindow *ui;
};

#endif // PURRWINDOW_HPP
