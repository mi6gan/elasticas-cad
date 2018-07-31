#ifndef BLOUSEDIALOGS_H
#define BLOUSEDIALOGS_H
#include "elcore/elbasicdialogs.h"
namespace Elasticas
{
class BlouseBKBasicDialog : public PropertiesDialog
{
public:
    BlouseBKBasicDialog(const QString & class_name);
};

class BlouseMKFormDialog : public PropertiesDialog
{
public:
    BlouseMKFormDialog(const QString & class_name);
};

class BlouseMKNeckDialog : public PropertiesDialog
{
public:
    BlouseMKNeckDialog(const QString & class_name);
};
}

#endif // BLOUSEDIALOGS_H
