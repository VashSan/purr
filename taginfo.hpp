#ifndef TAGINFO_HPP
#define TAGINFO_HPP
#include <QString>

struct STagInfo
{
    QString file;
    QString artist;
    QString title;

    QString toString()
    {
        QString result;

        if (artist.isEmpty() && title.isEmpty())
        {
            result = file;
        }
        else
        {
            result.append(artist);
            result.append(" - ");
            result.append(title);
        }

        return result;
    }
};


#endif // TAGINFO_HPP
