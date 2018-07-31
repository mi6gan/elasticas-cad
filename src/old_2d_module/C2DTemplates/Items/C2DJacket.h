#ifndef C2DJACKET_H
#define C2DJACKET_H

#include "C2DJacketDialog.h"
#include "../../C2DModule/Frameworks/Items/include/C2DItem.h"

class C2DJacket : public C2DItem
{
public:
    C2DJacket();

    void Update();

protected:
    void requiredVariables();
    void setVariables();
    void UpdatePoints();
    void DrawOnWidget();
    void DrawSpline( QStringList, QVariant [] );
private:
    QStringList variables;
    double rotatebeta;
};

#endif // C2DJacket_H

