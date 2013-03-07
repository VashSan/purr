#include "purrwindow.hpp"
#include "ui_purrwindow.h"
#include <QFileDialog>


PurrWindow::PurrWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PurrWindow),
    nextTrack(0),
    currentTrack(0),
    fullStop(true)
{
    ui->setupUi(this);
    ui->playlist->setSortingEnabled(false);

    // qmediaplayer signals
    connect(&player, &QMediaPlayer::positionChanged,
            this, &PurrWindow::on_position_changed);
    connect(&player, &QMediaPlayer::durationChanged,
            this, &PurrWindow::on_duration_changed);
    connect(&player, &QMediaPlayer::stateChanged,
            this, &PurrWindow::on_playingState_changed);

    // slider signals
    connect(ui->trackProgressSlider, &QSlider::sliderReleased,
            this, &PurrWindow::on_slider_released);
    connect(ui->trackProgressSlider, &QSlider::actionTriggered,
            this, &PurrWindow::on_slider_triggered);

    // list widget signals
    connect(ui->playlist, &QListWidget::currentRowChanged,
            this, &PurrWindow::on_listitem_changed);
}

PurrWindow::~PurrWindow()
{
    delete ui;
}

void PurrWindow::on_openButton_clicked()
{
    QFileDialog dialog;
    dialog.setNameFilter("*.mp3");
    dialog.setModal(true);
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
    {
        for(QString file : dialog.selectedFiles())
        {
            // TODO validate files
            // TODO append files from dir
            selectedFiles.append(file);
            updatePlaylist();
        }
    }
}

void PurrWindow::on_playButton_clicked()
{
    fullStop = true;
    currentTrack = nextTrack < 0 ? 0 : nextTrack;
    playMedia();
    fullStop = false;
}

void PurrWindow::playMedia()
{
    if (player.state() == QMediaPlayer::PlayingState)
    {
        player.stop();
    }

    if (!selectedFiles.isEmpty())
    {
        QString selectedFile = selectedFiles.at(currentTrack);
        updatePlaylist();

        QUrl media = QUrl::fromLocalFile(selectedFile);
        player.setMedia(media);
        player.play();
    }
}

void PurrWindow::on_pauseButton_clicked()
{
    if (player.state() == QMediaPlayer::PausedState)
    {
        player.play();
    }
    else if (player.state() == QMediaPlayer::PlayingState)
    {
        player.pause();
    }
}

void PurrWindow::on_stopButton_clicked()
{
    fullStop = true;
    player.stop();
}

void PurrWindow::on_position_changed(qint64 position)
{
    if (!ui->trackProgressSlider->isSliderDown())
    {
        double result = (double)position / (double)currentDuration;
        result = floor(result * 100);
        ui->trackProgressSlider->setValue(result);
    }
}

void PurrWindow::on_duration_changed(qint64 duration)
{
    currentDuration = duration;
}

void PurrWindow::on_slider_released()
{
    updatePosition();
}

void PurrWindow::on_slider_triggered(int value)
{
    bool doUpdatePosition;
    switch(value)
    {
    case QAbstractSlider::SliderToMinimum:
        // fall through
    case QAbstractSlider::SliderToMaximum:
        // fall through
    case QAbstractSlider::SliderPageStepAdd:
        // fall through
    case QAbstractSlider::SliderPageStepSub:
        doUpdatePosition = true;
        break;
    default:
        doUpdatePosition = false;
        break;
    }

    if (doUpdatePosition)
    {
        updatePosition();
    }
}

void PurrWindow::updatePosition()
{
    int value = ui->trackProgressSlider->sliderPosition();
    qint64 newPosition = (double) currentDuration * ((double)value / 100.0L);
    player.setPosition(newPosition);
}

void PurrWindow::updatePlaylist()
{
    ui->playlist->clear();
    ui->playlist->addItems(selectedFiles);
    ui->playlist->setCurrentRow(currentTrack);
}

void PurrWindow::on_listitem_changed(int row)
{
    nextTrack = row;
}

void PurrWindow::on_playingState_changed(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::StoppedState && !fullStop)
    {
        currentTrack++;
        if (currentTrack+1 > selectedFiles.count())
        {
            currentTrack = 0;
        }
        playMedia();
    }
}

