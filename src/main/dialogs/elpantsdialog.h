#include "elskirtdialogs.h"
namespace Elasticas
{
class PantsBKBasicPropertiesDialog: public PropertiesDialog //БК  брюк, пояс
{
public:
    PantsBKBasicPropertiesDialog();
};

class PantsIMKBeltPropertiesDialog: public SkirtPropertiesDialog //ИМК  брюк, пояс
{
public:
    PantsIMKBeltPropertiesDialog();
};

class PantsIMKClaspPropertiesDialog: public SkirtPropertiesDialog //ИМК брюк, застёжка
{
public:
    PantsIMKClaspPropertiesDialog();
};
}
