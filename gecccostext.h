#ifndef GECCCOSTEXT_H
#define GECCCOSTEXT_H
#include <gecccoselement.h>

class GecccosText : public GecccosElement
{
    QString text;
public:
    GecccosText();
    void setText(QString newText);
    QString toString() override;
    bool isSet();

};

#endif // GECCCOSTEXT_H
