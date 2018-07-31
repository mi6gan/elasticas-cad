/***************************************************************************
 *   Copyright (C) 2008 by Michael Boyarov                                 *
 *   mi666gan@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "kongomath.h"
namespace Kongomato
{




std::ostream & operator<<(std::ostream& out,Kongomato::Math::Rectangle<int> rectangle)
{
        std::stringstream res;
        res<<"rectangle( x="<<rectangle.x()<<" y="<<rectangle.y()
           <<" width="<<rectangle.width()<<" height"<<rectangle.height()<<" )";

        res<<")";
        return out<<res.str();
}
/*
float Interpolate(float x1,float x,float x2,float y1,float y2,int type)
{
	return y1+(x-x1)*(y2-y1)/(x2-x1);
}
//________________________________________________________________________________


float TriangleXAxis(Vector3D<float>* t0,Vector3D<float>* t1,Vector3D<float>* t2,float c1,float c2,unsigned char axis)
{
        Vector3D<float> N=Vector3D<float>((*t2) -(*t0)).CrossProduct(Vector3D<float>((*t1) -(*t0))).Normal();

        if(axis==0) return (N.x()*t0->x() + N.y()*t0->y() + N.z()*t0->z() - N.y()*c1 - N.z()*c2)/N.x(); //x
        if(axis==1) return (N.x()*t0->x() + N.y()*t0->y() + N.z()*t0->z() - N.x()*c1 - N.z()*c2)/N.y(); //y
        if(axis==2) return (N.x()*t0->x() + N.y()*t0->y() + N.z()*t0->z() - N.x()*c1 - N.y()*c2)/N.z(); //z
	return 0;
}
//________________________________________________________________________________
*/
};
