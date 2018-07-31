#ifndef C2DFLAREDSKIRT_H
#define C2DFLAREDSKIRT_H

#include "../../C2DModule/Frameworks/Items/include/C2DItem.h"
#include "C2DFlaredSkirtKMProperties.h"

class C2DFlaredSkirt: public C2DItem
{
public:
    C2DFlaredSkirt();

    void Update();

protected:

    void setVariables();
    void UpdatePoints();
    void DrawOnWidget();

private:

    void requiredVariables();

    QPointF leftTop( double half_spread );
    QPointF rightTop( double half_spread );

};

#endif // C2DFLAREDSKIRT_H
