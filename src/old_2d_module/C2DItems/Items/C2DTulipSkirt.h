#ifndef C2DTULIPSKIRT_H
#define C2DTULIPSKIRT_H

#include "../../C2DModule/Frameworks/Items/include/C2DItem.h"
#include "C2DDefaultBelt.h"

class C2DTulipSkirt : public C2DItem
{
public:
    C2DTulipSkirt();

   void Update();

protected:
    virtual void requiredVariables();
    void setVariables();
    void UpdatePoints();
    void DrawOnWidget();

private:
   QPointF leftTop( double half_spread );
   QPointF rightTop( double half_spread );
};

#endif // C2DTULIPSKIRT_H
