#ifndef C2DSLEEVE_H
#define C2DSLEEVE_H

#include "C2DSleeveDialog.h"
#include "../../C2DModule/Frameworks/Items/include/C2DItem.h"

class C2DSleeve : public C2DItem
{
public:
    C2DSleeve();

   void Update();
protected:
    void requiredVariables();
    void setVariables();
    void UpdatePoints();
    void DrawOnWidget();

};

#endif // C2DSIMPLEITEM_H

