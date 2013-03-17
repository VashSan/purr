#include "purrwindow.hpp"
#include "ui_purrwindow.h"
#include <QTime>
#include <QFileDialog>
#include "tagger.hpp"
#include <QMessageBox>

/// formats an amount of milliseconds to be displayed on the ui
static QString formatLabelTime(qint64 milliseconds)
{
    const qint64 one_hour = 1000 * 60 * 60;

    QString format;
    if (milliseconds >= one_hour)
    {
        format = "H:mm:ss";
    }
    else
    {
        format = "m:ss";
    }

    QTime timeValue(0, 0);
    QTime resultTime = timeValue.addMSecs(milliseconds);
    QString result = resultTime.toString(format);
    return result;
}



PurrWindow::PurrWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PurrWindow),
    nextTrack(0),
    currentTrack(0),
    fullStop(false)
{
    ui->setupUi(this);
    ui->playlist->setSortingEnabled(false);
    ui->durationLabel->setText("0:00");
    ui->positionLabel->setText("0:00");

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
    connect(ui->playlist, &QListWidget::itemDoubleClicked,
            this, &PurrWindow::on_listitem_doubleClicked);

    // actions
    connect(ui->actionAbout, &QAction::triggered,
            this, &PurrWindow::on_about_triggered);
}

PurrWindow::~PurrWindow()
{
    delete ui;
}

void PurrWindow::on_openButton_clicked()
{
    // TODO remove hardcoded mp3 stuff

    QFileDialog dialog;
    dialog.setParent(this);
    dialog.setNameFilter("*.mp3");
    dialog.setModal(true);
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
    {
        for(QString filePath : dialog.selectedFiles())
        {
            // I assume the file exists since it comes
            // from the file selection dialog. I will check
            // before playing it though.

            if (filePath.endsWith("mp3", Qt::CaseInsensitive))
            {
                // TODO append files from dir
                using namespace tagger;
                CTagger tagger(filePath);
                STagInfo info = tagger.parse();

                selectedMedia.append(info);
            }
            else
            {
                QString message("skipped adding non mp3 file: ");
                message.append(filePath);
                ui->statusBar->showMessage(message, 2000);
                qDebug() << message;
            }
        }

        updatePlaylist();
    }
}

void PurrWindow::on_playButton_clicked()
{
    currentTrack = nextTrack < 0 ? 0 : nextTrack;
    playMedia();
}

void PurrWindow::playMedia()
{
    if (player.state() == QMediaPlayer::PlayingState)
    {
        fullStop = true;
        player.stop();
        fullStop = false;
    }

    if (!selectedMedia.isEmpty())
    {
        if (currentTrack+1 > selectedMedia.count())
        {
            currentTrack = 0;
        }

        STagInfo info = selectedMedia.at(currentTrack);
        updatePlaylist();

        QFile file(info.file);
        if (file.exists())
        {
            QUrl media = QUrl::fromLocalFile(info.file);
            player.setMedia(media);
            player.play();
        }
        else
        {
            qDebug() << "Invalid file detected: " << info.file;
            ui->statusBar->showMessage("The current file does not exist. Stopped Playback.");
            // TODO proceed to next file?
        }
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

    QString labelText = formatLabelTime(position);
    ui->positionLabel->setText(labelText);
}

void PurrWindow::on_duration_changed(qint64 duration)
{
    currentDuration = duration;

    QString labelText = formatLabelTime(duration);
    ui->durationLabel->setText(labelText);
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
    QStringList listItems;
    for(STagInfo info : selectedMedia)
    {
        listItems.append(info.toString());
    }

    ui->playlist->clear();
    ui->playlist->addItems(listItems);
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
        playMedia();
    }
}

void PurrWindow::on_listitem_doubleClicked(QListWidgetItem * item)
{
    currentTrack = ui->playlist->row(item);
    playMedia();
}

void PurrWindow::on_dial_valueChanged(int value)
{
    player.setVolume(value);
}

void PurrWindow::on_clearListButton_clicked()
{
    selectedMedia.clear();
    updatePlaylist();
}

void PurrWindow::on_removeListButton_clicked()
{
    qint64 track = ui->playlist->currentRow();
    selectedMedia.remove(track);
    updatePlaylist();
    if (track == currentTrack)
    {
        playMedia();
    }
}

void PurrWindow::on_savePlaylistButton_clicked()
{
    saveSelectedMedia();
}

void PurrWindow::saveSelectedMedia()
{
    QFileDialog dialog;
    dialog.setParent(this);
    dialog.setNameFilter("*.xspf");
    dialog.setModal(true);
    // TODO set select exactly one file to open

    if (dialog.exec())
    {
        QString file = dialog.selectedFiles().at(0);
        selectedMedia.saveToFile(file);
    }

}


void PurrWindow::on_loadPlaylistButton_clicked()
{
    appendMediaFromFile();
}

void PurrWindow::on_about_triggered()
{
    QMessageBox::information(this, "Purr", "The Purr music player was brought to you by Vash.\n\nSee https://github.com/VashSan/purr for more information.");
}

void PurrWindow::appendMediaFromFile()
{
    QFileDialog dialog;
    dialog.setParent(this);
    dialog.setNameFilter("*.xspf");
    dialog.setModal(true);
    // TODO set select exactly one file to save

    if (dialog.exec())
    {
        QString file = dialog.selectedFiles().at(0);
        if (!file.isEmpty())
        {
            selectedMedia.appendFromFile(file);
            updatePlaylist();
        }
    }

}
