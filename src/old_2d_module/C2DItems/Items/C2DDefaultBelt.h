#ifndef C2DDEFAULTBELT_H
#define C2DDEFAULTBELT_H

#include "../../C2DModule/Frameworks/Items/include/C2DItem.h"

class C2DDefaultBelt : public C2DItem
{
public:
    C2DDefaultBelt( const QString & prefix );

    void Update();

 protected:
     void requiredVariables();
     void setVariables();
     void UpdatePoints();
     void DrawOnWidget();

};

#endif // C2DDEFAULTBELT_H
