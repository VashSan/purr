#include "purrwindow.hpp"
#include "ui_purrwindow.h"
#include <QFileDialog>


PurrWindow::PurrWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PurrWindow)
{
    ui->setupUi(this);

    connect(&player, SIGNAL(positionChanged(qint64)), this, SLOT(on_position_changed(qint64)));
    connect(&player, SIGNAL(durationChanged(qint64)), this, SLOT(on_duration_changed(qint64)));
    connect(ui->trackProgressSlider, SIGNAL(sliderReleased()), this, SLOT(on_slider_released()));
    connect(ui->trackProgressSlider, SIGNAL(actionTriggered(int)), this, SLOT(on_slider_triggered(int)));
}

PurrWindow::~PurrWindow()
{
    delete ui;
}

void PurrWindow::on_openButton_clicked()
{
    QFileDialog dialog;
    dialog.setNameFilter("*.mp3");
    if (dialog.exec())
    {
        for(QString file : dialog.selectedFiles())
        {
            // TODO validate files
            // TODO append files from dir
            selectedFiles.append(file);
        }

        if (player.state() == QMediaPlayer::StoppedState)
        {
            playMedia();
        }
    }
}

void PurrWindow::on_playButton_clicked()
{
    playMedia();
}

void PurrWindow::playMedia()
{
    if (player.state() == QMediaPlayer::PlayingState ||
            player.state() == QMediaPlayer::PausedState)
    {
        player.stop();
    }

    if (!selectedFiles.isEmpty())
    {
        QString selectedFile = selectedFiles.takeFirst();
        QUrl media = QUrl::fromLocalFile(selectedFile);
        player.setMedia(media);
        player.play();
    }
}

void PurrWindow::on_pauseButton_clicked()
{
    player.pause();
}

void PurrWindow::on_stopButton_clicked()
{
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
