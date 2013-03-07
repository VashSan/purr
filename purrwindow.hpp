#ifndef PURRWINDOW_HPP
#define PURRWINDOW_HPP

#include <QMainWindow>
#include <QMediaPlayer>

namespace Ui {
class PurrWindow;
}

class QListWidgetItem;

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

    void on_position_changed(qint64 position);

    void on_duration_changed(qint64 duration);

    void on_slider_released();

    void on_slider_triggered(int value);

    void on_listitem_changed(int row);

    void on_playingState_changed(QMediaPlayer::State state);

    void on_listitem_doubleClicked(QListWidgetItem* item);

private:
    Ui::PurrWindow *ui;
    QStringList selectedFiles;
    QMediaPlayer player;
    qint64 currentDuration;
    qint32 nextTrack;
    qint32 currentTrack;
    bool fullStop;

    void updatePlaylist();
};

#endif // PURRWINDOW_HPP
