#ifndef C2DVARIABLE_H
#define C2DVARIABLE_H

#include <QString>
#include <QVariant>

class C2DVariable
{

public:
    enum Group { General, Additional, Optional };
    enum Units { Metrics, Logical, Unitless };

    C2DVariable( const QString  & n ,
                 const QString  & cn,
                 const QString  & d ,
                 const Units    & un,
                 const Group    & gr,
                 const QVariant & dv,
                 const double   & mr );

    static C2DVariable * set( const QString  & name,
                              const QString  & common_name,
                              const QString  & description,
                              const Units    & units,
                              const Group    & group,
                              const QVariant & default_value = QVariant( 0.0f ),
                              const double   & modifier      = 1.0f );

    inline const QString  & name()           { return this->var_name;          }
    inline const Units    & units()          { return this->var_units;         }
    inline const Group    & group()          { return this->var_group;         }
    inline const double   & modifier()       { return this->var_modifier;      }
    inline const QString  & common_name()    { return this->var_common_name;   }
    inline const QString  & description()    { return this->var_description;   }
    inline const QVariant & default_value()  { return this->var_default_value; }

private:
    QString          var_name;
    Units            var_units;
    Group            var_group;
    double           var_modifier;
    QString          var_common_name;
    QString          var_description;
    QList< QString > var_dependencies;
    QVariant         var_default_value;

};

#endif //C2DVARIABLE_H
