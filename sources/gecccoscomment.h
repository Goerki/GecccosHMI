#ifndef GECCCOSCOMMENT_H
#define GECCCOSCOMMENT_H

#include "gecccoselement.h"


class GecccosComment : public GecccosElement
{
public:
    GecccosComment(QString line);
    QString line;
    void setValueFromStream(QTextStream* stream);
    QString toString() override;
};

#endif // GECCCOSCOMMENT_H
