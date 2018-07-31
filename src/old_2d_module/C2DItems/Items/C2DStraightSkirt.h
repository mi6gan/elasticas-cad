//Straight Skirt

#ifndef C2DSTRAIGHTSHIRT_H
#define C2DSTRAIGHTSHIRT_H

#include <math.h>
#include <QDebug>
#include <QGroupBox>
#include <QGraphicsView>
#include <QGenericMatrix>
#include <QGraphicsScene>

#include <iostream>
//#include <C2DSync.h>
//#include <C2DSceneItems.h>
#include "../../C2DModule/Frameworks/Items/include/C2DItem.h"
//#include <C2DLayerManager.h>
#include "C2DStraightSkirtDartsDialog.h"


#include "../../C2DModule/Frameworks/Items/include/Unicus/Intersection.h"

#include "../../../elcore/elcore.h"
//#include "../../../elcore/elcommondata.h"

class C2DStraightSkirt: public C2DItem
{

public:
    C2DStraightSkirt( C2DLayerManager * LayerManager, QGraphicsScene * scene = 0 );

    void Update();

protected:
     virtual void requiredVariables();
     virtual void setVariables();
     virtual void UpdatePoints();
     virtual void DrawOnWidget();
private:

    void BeltUpdate();

    QPointF FrontDartTopPosition(double width, QPointF SideDartTop, QPointF RightPoint);
    QPointF BackDartTopPosition(double width, QPointF SideDartTop, QPointF LeftPoint);
};

#endif // C2DSTRAIGHTSHIRT_H
