#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QVector>
#include "taginfo.hpp"
#include "iplaylistformatprovider.hpp"

class CPlaylist : public QVector<STagInfo>
{

public:
    CPlaylist();

    void setPlaylistFormatProvider(PtrPlaylistProvider provider);

    bool saveToFile(const QString& filePath) const;
    bool appendFromFile(const QString& filePath);


private:
    PtrPlaylistProvider provider;
};

#endif // PLAYLIST_H
