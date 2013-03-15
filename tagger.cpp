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
    if ( parse_id3v1(tagInfo) )
    {
        return tagInfo;
    }

    tagInfo.title = filePath;
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
    file.seek(tagOffset);

    char tagNameActual[tagNameLength+1];
    memset(tagNameActual, 0, tagNameLength+1);
    file.read(tagNameActual, tagNameLength);

    const char tagNameExpected[tagNameLength+1] = "TAG";
    if ( strcmp(tagNameExpected, tagNameActual) != 0 )
    {
        return false;
    }

    char tagData[tagLength];
    file.read(tagData, tagLength);


    s_tag* pTag = reinterpret_cast<s_tag*>(&tagData);

    info.artist.append(pTag->artist);
    info.title.append(pTag->title);

    return true;
}

}
