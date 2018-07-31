#ifndef C2DSIMPLEITEM_H
#define C2DSIMPLEITEM_H

#include <C2DItem.h>

class C2DSimpleItem : public C2DItem
{
public:
    C2DSimpleItem( C2DLayerManager * LayerManager, QGraphicsScene * scene );

   void Update();
protected:
    void requiredVariables();
    void getVariables();
    void setVariables();
    void UpdatePoints();
    void DrawOnWidget();

};

#endif // C2DSIMPLEITEM_H

