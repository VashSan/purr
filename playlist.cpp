#include "playlist.hpp"
#include <QFile>

/// simplest file provider for saving playlists
class DefaultProvider : public IPlaylistFormatProvider
{
    virtual void save(const QVector<STagInfo> &playlist,
                 const QString &filePath) const override
    {
        // buffer data first for faster disc write
        QByteArray data;
        for(STagInfo info : playlist)
        {
            data.append(info.file.toUtf8());
            data.append('\n');
        }

        // TODO file errors
        QFile file;
        file.setFileName(filePath);
        file.open(QFile::WriteOnly);
        file.write(data);
        file.close();
    }

    virtual void append(QVector<STagInfo>& playlist,
                 const QString& filePath) const override
    {
        QFile file;
        file.setFileName(filePath);
        // TODO file exists and errors
        file.open(QFile::ReadOnly);
        QByteArray data = file.readAll();

        QList<QByteArray> fileList = data.split('\n');

        for (QByteArray file : fileList)
        {
            // TODO read file tag
            STagInfo info;
            info.file = QString::fromUtf8(file);
            playlist.append(info);
        }
    }
};

CPlaylist::CPlaylist()
    : provider(new DefaultProvider())
{
}


bool CPlaylist::saveToFile(const QString& filePath) const
{
    if (provider == nullptr || filePath.isEmpty())
    {
        return false;
    }

    provider->save(*this, filePath);

    return true;
}

bool CPlaylist::appendFromFile(const QString& filePath)
{
    if (provider == nullptr || filePath.isEmpty())
    {
        return false;
    }

    provider->append(*this, filePath);

    return true;
}

