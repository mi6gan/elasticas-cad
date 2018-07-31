#include "elskirtdialogs.h"
namespace Elasticas
{
class FlaredSkirtBKBasicPropertiesDialog: public SkirtPropertiesDialog  //БК расклешённой юбки, основные параметры
{
    public:
        FlaredSkirtBKBasicPropertiesDialog();
};

class FlaredSkirtBKBasicSkewsPropertiesDialog: public SkirtPropertiesDialog //БК расклешённой юбки, основные конструктивные швы
{
public:
    FlaredSkirtBKBasicSkewsPropertiesDialog();
};

class FlaredSkirtIMKBeltPropertiesDialog: public SkirtPropertiesDialog //ИМК расклешённой юбки, пояс
{
public:
    FlaredSkirtIMKBeltPropertiesDialog();
};

class FlaredSkirtIMKClaspPropertiesDialog: public SkirtPropertiesDialog //ИМК расклешённой юбки, застёжка
{
public:
    FlaredSkirtIMKClaspPropertiesDialog();
};

class FlaredSkirtMKGarmentPropsDialog: public SkirtPropertiesDialog //ИМК расклешённой юбки, параметры готового изделия
{
public:
    FlaredSkirtMKGarmentPropsDialog();
};
}
