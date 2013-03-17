#ifndef IPLAYLISTFORMATPROVIDER_HPP
#define IPLAYLISTFORMATPROVIDER_HPP

#include <memory>

class IPlaylistFormatProvider;

typedef std::shared_ptr<IPlaylistFormatProvider>
        PtrPlaylistProvider;

class IPlaylistFormatProvider
{
public:
    virtual void save(const QVector<STagInfo>& playlist,
              const QString& filePath) const = 0;

    virtual void append(QVector<STagInfo>& playlist,
                const QString& filePath) const = 0;
};

#endif // IPLAYLISTFORMATPROVIDER_HPP
