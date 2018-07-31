#ifndef ELSTRAIGHTSKIRTDIALOGS_H
#define ELSTRAIGHTSKIRTDIALOGS_H
#include "elskirtdialogs.h"
namespace Elasticas
{
class StraightSkirtBKBasicPropertiesDialog: public SkirtPropertiesDialog  //БК прямой юбки, основные параметры
{
    public:
        StraightSkirtBKBasicPropertiesDialog(const QString & class_name);
};

class StraightSkirtBKBasicSkewsPropertiesDialog: public SkirtPropertiesDialog //БК прямой юбки, основные конструктивные швы
{
public:
    StraightSkirtBKBasicSkewsPropertiesDialog(const QString & class_name);
};

class StraightSkirtIMKBeltPropertiesDialog: public SkirtPropertiesDialog //ИМК прямой юбки, пояс
{
public:
    StraightSkirtIMKBeltPropertiesDialog(const QString & class_name);
};

class StraightSkirtIMKClaspPropertiesDialog: public SkirtPropertiesDialog //ИМК прямой юбки, застёжка
{
public:
    StraightSkirtIMKClaspPropertiesDialog(const QString & class_name);
};

class SkirtDressIMKNarrowingPropertiesDialog: public PropertiesDialog //ИМК прямой юбки и платья, заужение
{
public:
    SkirtDressIMKNarrowingPropertiesDialog(const QString & classname);
};

class StraightSkirtIMKVentPropertiesDialog: public SkirtPropertiesDialog //ИМК прямой юбки, разрезы/шлицы
{
public:
    StraightSkirtIMKVentPropertiesDialog(const QString & class_name);
};
}
#endif
