#include "C2DVariable.h"

C2DVariable::C2DVariable( const QString & n,
                          const QString & cn,
                          const QString & d,
                          const Units & un,
                          const Group & gr,
                          const QVariant & dv,
                          const double & mr )
{
    this->var_name = n;
    this->var_common_name = cn;
    this->var_description = d;
    this->var_units = un;
    this->var_group = gr;
    this->var_default_value = dv;
    this->var_modifier = mr;
}

C2DVariable * C2DVariable::set( const QString  & name,
                                const QString  & common_name,
                                const QString  & description,
                                const Units    & units,
                                const Group    & group,
                                const QVariant & default_value,
                                const double   & modifier )
{
    return new C2DVariable( name, common_name, description, units, group, default_value, modifier );
}

