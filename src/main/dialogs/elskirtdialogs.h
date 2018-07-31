#ifndef ELSKIRT_H
#define ELSKIRT_H
#include "elcore/elbasicdialogs.h"
namespace Elasticas
{
    class SkirtPropertiesDialog: public PropertiesDialog
    {        
        protected:        
           void InitSkirtBKBasicProperties();           
           void InitSkirtIMKBeltProperties();
           void InitSkirtIMKClaspProperties(bool are_sews_optional=true);
           void computeDarts();
        public:
           SkirtPropertiesDialog(const QString & name,const QString & garment_name);
           virtual void exec();
    };

    class SkirtDebugDialog: public PropertiesDialog
    {
    public:
        SkirtDebugDialog(const QString & name,const QString & class_name);
    };

    class BlouseDebugDialog: public PropertiesDialog
    {
    public:
        BlouseDebugDialog(const QString & name,const QString & class_name);
    };
}

#endif // ELSKIRT_H
