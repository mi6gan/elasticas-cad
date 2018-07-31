#ifndef C2DMENSJACKET_H
#define C2DMENSJACKET_H

#include "../../C2DModule/Frameworks/Items/include/C2DItem.h"
//#include "myclasses/cGeometry.h"
#include "C2DMensjacketDialog.h"
//#include "C2DSleeve.h"
class C2DMensjacket : public C2DItem
{
public:
    C2DMensjacket();

    void Update();

protected:
    void requiredVariables();
    void setVariables();
    void UpdatePoints();
    void DrawOnWidget();
    void DrawSpline( QStringList, QVariant [] );

    void MSleeveUpdatePoints( QString , QPointF);
    void MSleeveDrawOnWidget( QString );
private:
    QStringList variables;
    double rotatebeta;
};

#endif // C2DMensjacket_H

