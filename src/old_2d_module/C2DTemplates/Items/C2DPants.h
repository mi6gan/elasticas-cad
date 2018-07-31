#ifndef C2DPANTS_H
#define C2DPANTS_H

#include "C2DPantsDialog.h"
#include "../../C2DModule/Frameworks/Items/include/C2DItem.h"

class C2DPants : public C2DItem
{
public:
    C2DPants();

   void Update();
protected:
    void requiredVariables();
    void setVariables();
    void UpdatePoints();
    void DrawOnWidget();

};

#endif // C2DPants_H

