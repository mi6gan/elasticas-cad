#ifndef ELJACKETDIALOGS_H
#define ELJACKETDIALOGS_H
#include "elcore/elbasicdialogs.h"
namespace Elasticas
{
class JacketBKBasicDialog : public PropertiesDialog
{
public:
    JacketBKBasicDialog();
    virtual void apply();
};

class JacketVentDialog: public PropertiesDialog
{
public:
    JacketVentDialog();
};

class JacketPocketsDialog: public PropertiesDialog
{
public:
    JacketPocketsDialog();
};

class JacketCollarDialog: public PropertiesDialog
{
public:
    JacketCollarDialog();
};

class JacketMKFormDialog : public PropertiesDialog
{
public:
    JacketMKFormDialog();
};



class JacketMKNeckDialog : public PropertiesDialog
{
public:
    JacketMKNeckDialog();
};
}

#endif // ELJACKETDIALOGS_H
