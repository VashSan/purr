#include "tagger.hpp"
#include <QFile>
#include <QDebug>
namespace tagger
{

CTagger::CTagger(const QString& taggedFile)
    : filePath(taggedFile)
{
}

STagInfo CTagger::parse()
{
    STagInfo tagInfo;
    tagInfo.file = filePath;

    if ( parse_id3v1(tagInfo) )
    {
        return tagInfo;
    }

    return tagInfo;
}

#pragma pack(1)
struct s_tag
{
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    char genre;
};

bool CTagger::parse_id3v1(STagInfo &info)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    const short tagLength = 125;
    const short tagNameLength = 3;

    qint64 tagOffset = file.size() - (tagLength + tagNameLength);
    if ( !file.seek(tagOffset) )
    {
        return false;
    }

    char tagNameActual[tagNameLength+1];
    memset(tagNameActual, 0, tagNameLength+1);
    if ( tagNameLength != file.read(tagNameActual, tagNameLength) )
    {
        return false;
    }

    const char tagNameExpected[tagNameLength+1] = "TAG";
    if ( strcmp(tagNameExpected, tagNameActual) != 0 )
    {
        return false;
    }

    char tagData[tagLength];
    if ( tagLength != file.read(tagData, tagLength) )
    {
        return false;
    }

    s_tag* pTag = reinterpret_cast<s_tag*>(&tagData);

    // Unclear from documentation which encoding to use.
    // Google believes its Latin1 but there may be other
    // files out there.

    // WARNING: restrict to sizeof(chars)
    // ID3v1 does not terminate the strings!

    info.artist = QString::fromLatin1(pTag->artist, sizeof(pTag->artist));
    info.title = QString::fromLatin1(pTag->title, sizeof(pTag->title));

    return true;
}

}
