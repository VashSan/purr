#ifndef PURRWINDOW_HPP
#define PURRWINDOW_HPP

#include <QMainWindow>
#include <QtMultimedia/qmediaplayer.h>
#include "filedialog.hpp"

namespace Ui {
class PurrWindow;
}

class PurrWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PurrWindow(QWidget *parent = 0);
    ~PurrWindow();
    
    void playMedia();
    void updatePosition();
private slots:
    void on_openButton_clicked();

    void on_playButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

    void on_fileDialog_accepted();

    void on_position_changed(qint64 position);

    void on_duration_changed(qint64 duration);

    void on_slider_released();

    void on_slider_triggered(int value);

private:
    Ui::PurrWindow *ui;
    QString selectedFile;
    QMediaPlayer player;
    FileDialog fileDialog;
    qint64 currentDuration;
};

#endif // PURRWINDOW_HPP