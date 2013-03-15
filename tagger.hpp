#ifndef TAGGER_HPP
#define TAGGER_HPP

#include <QString>

namespace tagger
{

struct STagInfo
{
    QString artist;
    QString title;
};

class CTagger
{
public:
    CTagger(const QString& taggedFile);

    STagInfo parse();

private:
    QString filePath;

    /// Tries to parse an id3 v1 tag. Returns true if successful.
    bool parse_id3v1(STagInfo& info);
};

}
#endif // TAGGER_HPP
