#include "playlist.hpp"

CPlaylist::CPlaylist()
    : provider(nullptr)
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
