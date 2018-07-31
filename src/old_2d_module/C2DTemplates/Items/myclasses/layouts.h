#include "../../../C2DModule/Frameworks/Items/include/C2DItem.h"
class vboxlayout: public QVBoxLayout
{
public:
    void addrow( const char * str, double d1, double d2, double d3, double d4 );
    void addrow( const char * str );
};
