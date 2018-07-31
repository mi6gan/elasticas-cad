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

#ifndef KONGOMATH_H
#define KONGOMATH_H
#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include <vector>
#include <iostream>
#include <sstream>


namespace Kongomato { namespace Math
{
const int matrix_row_major=0x0;
const int matrix_column_major=0x1;
template <class T>  class CommonMatrix;
template <class T=float> class CommonVector:public std::vector<T>
{

    public:

    CommonVector<T>(int sz=0,T value=0):std::vector<T>(sz)
    {
        for(int a=0;a<this->size();a++) this->operator[](a)=value;
    }

    void operator =(const CommonVector<T> & v)
    {
        int sz=this->size();
        if(sz>v.size()) sz=v.size();
        // if(this->size()!=v.size()) throw "void operator =(const CommonVector<T> & v) exception";
        for(int a=0;a<sz;a++) this->operator[](a)=v[a];
    }

    void operator +=(const CommonVector<T> & v)
    {
        if(this->size()!=v.size()) return;
        for(int a=0;a<v.size();a++) this->operator[](a)=this->operator[](a)+v[a];
    }

    void operator -=(const CommonVector<T> &  v)
    {
        if(this->size()!=v.size()) return;
        for(int a=0;a<v.size();a++) this->operator[](a)=this->operator[](a)-v[a];
    }


    CommonVector<T> operator -(const CommonVector<T> & v) const
    {
        CommonVector<T> res(v.size());
        if(this->size()!=v.size()) return res;
        for(int a=0;a<v.size();a++) res[a]=this->operator[](a)-v[a];
        return res;
    }

    CommonVector<T> operator +(const CommonVector<T> & v) const
    {
        CommonVector<T> res(v.size());
        if(this->size()!=v.size()) return res;
        for(int a=0;a<v.size();a++) res[a]=this->operator[](a)+v[a];
        return res;
    }

    CommonVector<T> operator *(T v) const
    {
        CommonVector<T> res(this->size());
        for(int a=0;a<this->size();a++) res[a]=this->operator[](a)*v;
        return res;
    }

    CommonVector<T> operator *(const CommonMatrix<T> & matrix) const
    {        
        int sz1=this->size();
        if(matrix.GetTotalRows()!=sz1) throw "CommonVector<T> operator *(const CommonMatrix<T> & matrix) const exception";
        CommonVector<T> res(sz1);        
        for(int a=0;a<sz1;a++)
        {
            res[a]=0;
            for(int b=0;b<sz1;b++)  res[a]+=(*this)[b]*matrix[b][a];
        }
        return res;
    }

    CommonVector<T> operator /(T v) const
    {
        CommonVector<T> res(this->size());
        for(int a=0;a<this->size();a++) res[a]=this->operator[](a)/v;
        return res;
    }

    CommonVector<T> Normal() const
    {
        CommonVector<T> res(this->size());
        T sr=0;
        for(int a=0;a<this->size();a++) sr+=(*this)[a]*(*this)[a];
        sr=sqrt(sr);
        if(sr==0.0f) return res;
        for(int a=0;a<this->size();a++) res[a]=(*this)[a]/sr;
        return res;
    }

    T& operator ()(int a)
    {
        return (*this)[a];
    }

    const T& operator ()(int a) const
    {
        return (*this)[a];
    }


    T DotProduct( CommonVector<T>& v)
    {
        try
        {
         T res=0;
         if(v.size()!=this->size()) throw 0;
         for(int a=0;a<this->size();a++) res+=this->operator[](a)*v[a];
         return res;
        }
        catch(...)
        {
            std::cout<<"CommonVector<T>::DotProduct excepiton"<<std::endl;
        }

    }

    T Length() const
    {
        T res=0;
        for(int a=0;a<this->size();a++) res+=(*this)[a]*(*this)[a];
        return sqrt(res);
    }

    bool operator == (const CommonVector<T>& v) const
    {
        for(int a=0;a<this->size();a++) if(this->operator[](a)!=v[a]) return false;
        return true;
    }

};

template<class T=float> class Vector2D:public CommonVector<T>
{
    public:

    T & x()
    {
        return this->operator [](0);
    }

    T & y()
    {
        return this->operator [](1);
    }

    const T & x() const
    {
        return this->operator [](0);
    }

    const T & y() const
    {
        return this->operator [](1);
    }

    Vector2D<T>():CommonVector<T>(2)
    {
    }

    Vector2D<T>(T x,T y):CommonVector<T>(2)
    {
        this->x()=x;
        this->y()=y;
    }

    static bool IntersectionPoint(const Vector2D<T>& a1,const Vector2D<T>& a2,const Vector2D<T>& b1,const Vector2D<T>& b2,Vector2D<T> &out)
    {
        out.x() = (a1.x()*(b1.x()*b2.y()-b1.y()*b2.x())+a2.x()*(-b1.x()*b2.y()+b1.y()*b2.x()+a1.y()*(b1.x()-b2.x()))+
        a1.x()*a2.y()*(b2.x()-b1.x()))/(a1.x()*(b2.y()-b1.y())+a2.x()*(b1.y()-b2.y())+a2.y()*(b2.x()-b1.x())+
                            a1.y()*(b1.x()-b2.x()));
        out.y() = (a2.y()*(a1.x()*(b2.y()-b1.y())-b1.x()*b2.y()+b1.y()*b2.x())+a1.y()*(b1.x()
        *b2.y()-b1.y()*b2.x())+a1.y()*a2.x()*(b1.y()-b2.y()))/(a1.x()*(b2.y()-b1.y())+a2.x()*(b1.y()-b2.y())+
                                          a2.y()*(b2.x()-b1.x())+a1.y()*(b1.x()-b2.x()));
        T alen=(a1-a2).Length(),blen=(b1-b2).Length();
        return ((out-a1).Length()<=alen)&&((out-a2).Length()<=alen)&&
                ((out-b1).Length()<=blen)&&((out-b2).Length()<=blen);
    }

};

template<class T=float> class Vector3D:public CommonVector<T>
{
    public:

    T & x()
    {
        return this->operator [](0);
    }

    T & y()
    {
        return this->operator [](1);
    }

    T & z()
    {
        return this->operator [](2);
    }

    const T & x() const
    {
        return this->operator [](0);
    }

    const T & y() const
    {
        return this->operator [](1);
    }

    const T & z() const
    {
        return this->operator [](2);
    }

    Vector3D<T>():CommonVector<T>(3)
    {
    }

    Vector3D<T>(const CommonVector<T> & v):CommonVector<T>(v)
    {
    }

    void operator =(const CommonVector<T> & v)
    {
      //  if(this->size()!=v.size()) throw "void operator =(const CommonVector<T> & v) exception";
        CommonVector<T>::operator =(v);
    }

    Vector3D<T>(T x,T y,T z):CommonVector<T>(3)
    {
        this->x()=x;
        this->y()=y;
        this->z()=z;
    }

    Vector3D<T> CrossProduct(const Vector3D<T> & v) const
    {
        Vector3D<T> res;
        res.x()=this->y()*v.z()-this->z()*v.y();
        res.y()=this->z()*v.x()-this->x()*v.z();
        res.z()=this->x()*v.y()-this->y()*v.x();
        return res;
    }
};

template<class T=float > class Vector4D:public CommonVector<T>
{
    public:

    T & x()
    {
        return this->operator [](0);
    }

    T & y()
    {
        return this->operator [](1);
    }

    T & z()
    {
        return this->operator [](2);
    }

    T & w()
    {
        return this->operator [](3);
    }

    const T & x() const
    {
        return this->operator [](0);
    }

    const T & y() const
    {
        return this->operator [](1);
    }

    const T & z() const
    {
        return this->operator [](2);
    }

    const T & w() const
    {
        return this->operator [](3);
    }

    void operator =(const CommonVector<T> & v)
    {
        // if(this->size()!=v.size()) throw "void operator =(const CommonVector<T> & v) exception";
        CommonVector<T>::operator =(v);
    }

    Vector4D<T>():CommonVector<T>(4)
    {
    }

    Vector4D<T>(T x,T y,T z,T w):CommonVector<T>(4)
    {
        this->x()=x;
        this->y()=y;
        this->z()=z;
        this->w()=w;
    }

};


template<class T=float> class CommonMatrix
{
    std::vector<T> data;
    int crows,ccolumns;
    int majority;

   public:
    static void LUP(const CommonMatrix<T> &A, CommonMatrix<T> &C, CommonMatrix<T> &P)
    {
     const char * exception="CommonMatrix<T>::LUP()";
    if(A.crows!=A.ccolumns||C.crows!=C.ccolumns||P.crows!=P.ccolumns) throw exception;
    if(A.crows!=C.crows||C.crows!=P.crows||P.crows!=A.crows) throw exception;
    //n - размерность исходной матрицы
    const int n = A.crows;
    C = A;
    //загружаем в матрицу P единичную матрицу
    P.SetIdentity();

    for( int i = 0; i < n; i++ ) {
        //поиск опорного элемента
        double pivotValue = 0;
        int pivot = -1;
        for( int row = i; row < n; row++ ) {
            if( fabs(C[ row ][ i ]) > pivotValue ) {
                pivotValue = fabs(C[ row ][ i ]);
                pivot = row;
            }
        }
        if( pivotValue == 0 ) {
            throw exception;
            return;
        }

        //меняем местами i-ю строку и строку с опорным элементом
        P.SwapRows(pivot, i);
        C.SwapRows(pivot, i);
        for( int j = i+1; j < n; j++ ) {
            C[ j ][ i ] /= C[ i ][ i ];
            for( int k = i+1; k < n; k++ )
                C[ j ][ k ] -= C[ j ][ i ] * C[ i ][ k ];
        }
     }

    }

    void SwapRows(int a,int b)
    {
        const char * exception="CommonMatrix<T>::SwapRows()";
            if(a<0||a>=crows||b<0||b>=crows) throw exception;
            if(a==b) return;
            T tv;
            for(int i=0;i<ccolumns;i++)
            {
                tv=(*this)[a][i];(*this)[a][i]=(*this)[b][i];(*this)[b][i]=tv;
            }
    }
    int GetTotalRows() const
    {
        return crows;
    }

    int GetTotalColumns() const
    {
        return ccolumns;
    }

    void SetIdentity(T base=1)
    {
        for(int i=0;i<crows;i++)
            for(int j=0;j<ccolumns;j++)
                if(i==j) (*this)[i][j]=base;
                else    (*this)[i][j]=0;
    }

    CommonMatrix<T>(int rows=0,int columns=0,T value=1,int majority=matrix_row_major)
    {

        crows=rows;ccolumns=columns;
        data.resize(rows*columns);
        SetIdentity(value);

    }



    T* operator [](int i)
    {
            const char * exception="CommonMatrix<T>::operator [](int i)";
            if(data.size()&&i<ccolumns) return &data[i*ccolumns];
            else throw exception;

    }

    const T* operator [](int i) const
    {
            const char * exception="CommonMatrix<T>::operator [](int i)";
            if(data.size()&&i<ccolumns) return &data[i*ccolumns];
            else throw exception;

    }

    const T& operator ()(int i,int j) const
    {
        return this->data[i*ccolumns+j];
    }

    T& operator ()(int i,int j)
    {
        return this->data[i*ccolumns+j];
    }

    CommonMatrix<T> operator*(const CommonMatrix<T> & m) const
    {
        const char * exception="CommonMatrix<T>::operator *(CommonMatrix<T> m)";
        CommonMatrix<T> res(this->crows,m.ccolumns,0);
        if(m.crows==0||this->ccolumns!=m.crows) throw exception;
        for(int a=0;a<this->crows;a++)
            for(int b=0;b<m.ccolumns;b++)
                for(int c=0;c<m.ccolumns;c++)
                    res[a][b]+=(*this)[a][c]*m(c,b);
        return res;
    }

    CommonVector<T> operator*(const CommonVector<T> & v) const
    {
        if(crows<=0) return v;
        int sz1=this->ccolumns;
        if(sz1!=v.size()) throw "CommonVector<T> operator*(const CommonVector<T> & m) const";
        CommonVector<T> res(sz1);
        for(int a=0;a<sz1;a++)
        {
            res[a]=0;
            for(int b=0;b<sz1;b++)  res[a]+=(*this)(a,b)*v[a];
        }
        return res;
    }

    void operator =(const CommonMatrix<T>& m)
    {
        data=m.data;
        this->crows=m.crows;
        this->ccolumns=m.ccolumns;
    }

    CommonMatrix<T> Transpose() const
    {
        CommonMatrix<T> X(this->ccolumns,this->crows);
        for(int a=0;a<this->crows;a++)
            for(int b=0;b<this->ccolumns;b++)
                X(b,a)=(*this)(a,b);
        return X;
    }

    CommonMatrix<T> Inversion() const
    {
      const char* exception="CommonMatrix<T> CommonMatrix<T>::Inverse()";
         if(crows!=ccolumns) throw exception;
        CommonMatrix<T> A=(*this);
        int n=A.crows;
        CommonMatrix<T> X(n,n);
        CommonMatrix<T> P(n, n);
        CommonMatrix<T> C(n, n);
        CommonMatrix<T>::LUP(A, C, P);
        for(int k = n-1; k >= 0; k--) {
            X[ k ][ k ] = 1;
            for( int j = n-1; j > k; j--) X[ k ][ k ] -= C[ k ][ j ]*X[ j ][ k ];
            X[ k ][ k ] /= C[ k ][ k ];
            for( int i = k-1; i >= 0; i-- ) {
                for( int j = n-1; j > i; j-- ) {
                    X[ i ][ k ] -= C[ i ][ j ]*X[ j ][ k ];
                    X[ k ][ i ] -= C[ j ][ i ]*X[ k ][ j ];
                }
                X[ i ][ k ] /= C[ i ][ i ];
            }
        }
        X = X*P;
        return X;

      }

    static CommonMatrix<T> CommonVectorToRowMatrix(const CommonVector<T>& v)
    {
        CommonMatrix<T> m(1,v.size());
        for(int a=0;a<v.size();a++) m[0][a]=v[a];
        return m;
    }

    static CommonMatrix<T> CommonVectorToColumnMatrix(const CommonVector<T>& v)
    {
        CommonMatrix<T> m(v.size(),1);
        for(int a=0;a<v.size();a++) m[a][0]=v[a];
        return m;
    }

};

template<class T=float> class Matrix4x4:public CommonMatrix<T>
{
    public:

    Matrix4x4<T>():CommonMatrix<T>(4,4)
    {
    }

    Matrix4x4<T>(const CommonMatrix<T> & m)
    {
      //   if(m.GetTotalRows()!=this->GetTotalRows()||m.GetTotalColumns()!=this->GetTotalColumns()) throw "Matrix4x4<T>(const CommonMatrix<T> & m) exception";
         (*this)=m;
    }

    Matrix4x4<T>( CommonMatrix<T>& m):CommonMatrix<T>(m)
    {
    }

    static Matrix4x4<T> PerspectiveView(float fovY,float Aspect,float zn, float zf)
    {
        Matrix4x4<T> res;
        res[1][1]=cos(fovY/2.0f)/sin(fovY/2.0f);
        res[0][0]=res(1,1)/Aspect;
        res[2][2]=zf/(zf-zn);
        res[2][3]=-zn*zf/(zf-zn);
        res[3][2]=1;
        res[3][3]=0;
        return res;
    }

    static Matrix4x4<T> PerspectiveViewOffC(float r,float l,float t,float b,float zn, float zf)
    {
        Matrix4x4<T> res;
        res[0][0]=2/(r-l);
        res[1][1]=2/(t-b);
        res[2][2]=1/(zf-zn);
        res[3][1]=(l+r)/(l-r);
        res[3][2]=(t+b)/(b-t);
        res[3][3]=zn/(zn-zf);
        return res;
    }


    static Matrix4x4<T> Translation(T x,T y,T z)
    {
        Matrix4x4<T> res;
        res[3][0]=x;
        res[3][1]=y;
        res[3][2]=z;
        return res;
    }

    static Matrix4x4<T> Translation(const Vector3D<T>& v)
    {
        return Matrix4x4<T>::Translation(v[0],v[1],v[2]);
    }

    static Matrix4x4<T> RotationX(float angle)
    {
        Matrix4x4<T> res;
        res[1][1]=res[2][2]=cos(angle);
        res[1][2]=sin(angle);
        res[2][1]=-res(1,2);
        return res;
    }

    static Matrix4x4<T> RotationY(float angle)
    {
        Matrix4x4<T> res;
        res[0][0]=res[2][2]=cos(angle);
        res[0][2]=sin(angle);
        res[2][0]=-res(0,2);
        return res;
    }

    static Matrix4x4<T> RotationZ(float angle)
    {
        Matrix4x4<T> res;
        res[0][0]=res[1][1]=cos(angle);
        res[0][1]=sin(angle);
        res[1][0]=-res(0,1);
        return res;
    }

    static Matrix4x4<T> YawPitchRoll(float yaw,float pitch,float roll)
    {
        Matrix4x4<T> res;
        res=res*RotationZ(roll)*RotationX(pitch)*RotationY(yaw);
        return res;
    }

    static Matrix4x4<T> Scale(T x,T y,T z)
    {
        Matrix4x4<T> res;
        res[0][0]=x;
        res[1][1]=y;
        res[2][2]=z;
        return res;
    }

    static Matrix4x4<T> Scale(const Vector3D<T>& size)
    {
        Matrix4x4<T> res;
        res.SetIdentity();
        res[0][0]=size[0];
        res[1][1]=size[1];
        res[2][2]=size[2];
        return res;
    }

    static Matrix4x4<T> LookAtView(const Vector3D<T>& Eye,const Vector3D<T>& At,const Vector3D<T>& Up)
    {

        Vector3D<T> zaxis=(At-Eye).Normal();
        Vector3D<T> xaxis=(zaxis.CrossProduct(Up.Normal())).Normal();
        Vector3D<T> yaxis=(xaxis.CrossProduct(zaxis));
        Vector3D<T> nEye=(Vector3D<T>(0,0,0)-(Eye));
        Matrix4x4<T>  res;
        res[0][0]=xaxis(0);res[0][1]=yaxis(0);res[0][2]=-zaxis(0);res[0][3]=0;
        res[1][0]=xaxis(1);res[1][1]=yaxis(1);res[1][2]=-zaxis(1);res[1][3]=0;
        res[2][0]=xaxis(2);res[2][1]=yaxis(2);res[2][2]=-zaxis(2);res[2][3]=0;
        res[3][0]=0;res[3][1]=0;res[3][2]=0;res[3][3]=1;
        res=Matrix4x4<T>::Translation(nEye)*res;
        return res;
    }

    static Matrix4x4<T> OrthoView(float r,float l,float t,float b,float zn, float zf)
    {
        Matrix4x4<T> res;
        res[0][0]=2.0f/(r-l);
        res[1][1]=2.0f/(t-b);
        res[2][2]=1.0f/(zf-zn);
        res[3][0]=(l+r)/(l-r);
        res[3][1]=(t+b)/(b-t);
        res[3][2]=zn/(zn-zf);
        return res;
    }

    void operator=(const CommonMatrix<T>& m)
    {
        CommonMatrix<T>::operator =(m);
    }

    Matrix4x4<T> operator*(const CommonMatrix<T>& m) const
    {
        return CommonMatrix<T>::operator *(m);
    }
};

template<class T1=float> class CommonPlane
{
    protected:
    std::vector< CommonVector<T1> > p;
    public:
    CommonPlane<T1>(int dimension)
    {
        p.resize(dimension);
        for(int a=0;a<p.size();a++) p[a].resize(dimension);
    }

    int GetSize()
    {
        return p.size();
    }

    const CommonVector<T1> & GetP(int i) const
    {
        const char* exception="CommonVector<T1> CommonVector<T1>::GetP(int i)";
        if(i>=p.size()) throw exception;
        return p[i];
    }

    void SetP(int i,const CommonVector<T1>& value)
    {
        const char* exception="void CommonPlane<T1>::SetP() exception";
        if(i>=p.size()||value.size()!=p.size()) throw exception;
        p[i]=value;
    }

    CommonMatrix<T1> ToOrthonormalAxis() const
    {
        const char* exception="CommonMatrix<T1> CommonMatrix<T1>::ToOrthonormalAxis() exception";
        if(p.size()!=3) throw exception;
        CommonMatrix<T1> result(p.size(),p.size());
        std::vector< Vector3D<T1> > o(p.size());
        o[0]=p[1]-p[0];
        o[1]=p[2]-p[0];
        o[2]=o[1].CrossProduct(o[0]);
        o[1]=o[0].CrossProduct(o[2]);
        for(int a=0;a<p.size();a++)
        {
          CommonVector<T1> tv=o[a].Normal();
          for(int b=0;b<p.size();b++)  result[b][a]=tv[b];
        }
        return result;
    }
};

template <class T1=float> class Plane3D:public CommonPlane<T1>
{
    public:
    Plane3D<T1>(T1 x1=0,T1 y1=0,T1 z1=0,T1 x2=0,T1 y2=0,T1 z2=0,T1 x3=0,T1 y3=0,T1 z3=0):CommonPlane<T1>(3)
    {
        this->SetPlane(x1,y1,z1,x2,y2,z2,x3,y3,z3);
    }

    Plane3D<T1>(const Vector3D<T1>& v1,const Vector3D<T1>& v2,const Vector3D<T1>& v3):CommonPlane<T1>(3)
    {
        this->SetPlane(v1,v2,v3);
    }


    void SetPlane(T1 x1,T1 y1,T1 z1,T1 x2,T1 y2,T1 z2,T1 x3,T1 y3,T1 z3)
    {
        CommonPlane<T1>::p[0][0]=x1;CommonPlane<T1>::p[0][1]=y1;CommonPlane<T1>::p[0][2]=z1;
        CommonPlane<T1>::p[1][0]=x2;CommonPlane<T1>::p[1][1]=y2;CommonPlane<T1>::p[1][2]=z2;
        CommonPlane<T1>::p[2][0]=x3;CommonPlane<T1>::p[2][1]=y3;CommonPlane<T1>::p[2][2]=z3;
    }

    void SetPlane(const Vector3D<T1>& v1,const Vector3D<T1>& v2,const Vector3D<T1>& v3)
    {
        this->SetP(0,v1);
        this->SetP(1,v2);
        this->SetP(2,v3);
    }

    Vector3D<T1> IntersectionPoint(const Vector3D<T1>& p1,const  Vector3D<T1>& p2) const
    {
        const char* exception="Vector3D<T1> Vector3D<T1>::IntersectionPoint(Vector3D<T1> p1, Vector3D<T1> p2)";
        Vector3D<T1> result;
        std::vector< Vector3D<T1> > & p=(std::vector< Vector3D<T1> > &)CommonPlane<T1>::p;
        Vector3D<T1> N=Vector3D<T1>(p[2]-p[0]).CrossProduct(Vector3D<T1>(p[1]-p[0]));
        T1 k=(N.z()*(p2.z()-p1.z())+N.y()*(p2.y()-p1.y())+N.x()*(p2.x()-p1.x()));
        if(k==0.0f) throw exception;
        result.x() =
        (N.z()*(p1.x()*p2.z()-p1.z()*p2.x())+N.y()*(p1.x()*p2.y()-p1.y()*p2.x())+
         N.z()*p[0].z()*(p2.x()-p1.x())+
         N.y()*p[0].y()*(p2.x()-p1.x())+
         N.x()*p[0].x()*(p2.x()-p1.x()))
         /k;
         result.y() =
         (N.z()*(p1.y()*p2.z()-p1.z()*p2.y())+N.x()*(p1.y()*p2.x()-p1.x()*p2.y())+
          N.z()*p[0].z()*(p2.y()-p1.y())+
          N.y()*p[0].y()*(p2.y()-p1.y())+
          N.x()*p[0].x()*(p2.y()-p1.y()))
         /k;
         result.z() =
         (N.y()*(p1.z()*p2.y()-p1.y()*p2.z())+N.x()*(p1.z()*p2.x()-p1.x()*p2.z())+
         N.z()*p[0].z()*(p2.z()-p1.z())+
         N.y()*p[0].y()*(p2.z()-p1.z())+
         N.x()*p[0].x()*(p2.z()-p1.z()))
         /k;
        return result;
    }
};

template<class T1> class Size
{
    T1 _width,_height;
    public:
    Size()
    {
        this->_width=this->_height=0;
    }

    Size(T1 width,T1 height)
    {
        this->_width=width;this->_height=height;
    }

    T1 & width()
    {
        return this->_width;
    }

    T1 & height()
    {
        return this->_height;
    }

    const T1 & width() const
    {
        return this->_width;
    }

    const T1 & height() const
    {
        return this->_height;
    }
};

template<class T1> class Rectangle //This class template implements  rectangle
{
        T1 _x,_y;
        T1 _width,_height;
        public:
        Rectangle(T1 x,T1 y,T1 width,T1 height)
        {
            this->_x=x;this->_y=y;this->_width=width;this->_height=height;
        }
        Rectangle()
        {
            _x=_y=_width=_height=0;
        }

        bool operator ==(const Rectangle& r) const
        {
            return (r._x==_x&&r._y==_y&&r._width==_width&&r._height==_height);
        }

        static Rectangle<T1> Intersection(const Rectangle& r1,const Rectangle& r2)
        {
            Rectangle<T1> res;
            if(r1._x>r2._x+r2._width) return Rectangle<T1>(0,0,0,0);
            if(r2._x>r1._x+r1._width) return Rectangle<T1>(0,0,0,0);
            if(r1._y>r2._y+r2._height) return Rectangle<T1>(0,0,0,0);
            if(r2._y>r1._y+r1._height) return Rectangle<T1>(0,0,0,0);
            if(r1._width==0||r2._width==0||r1._height==0||r2._height==0)  return Rectangle<T1>(0,0,0,0);
            if(r1._x>r2._x) res._x=r1._x;
            else res._x=r2._x;
            if(r1._y>r2._y) res._y=r1._y;
            else res._y=r2._y;
            if(r1._x+r1._width<r2._x+r2._width) res._width=abs((r1._x+r1._width)-res._x);
            else res._width=abs((r2._x+r2._width)-res._x);
            if(r1._y+r1._height<r2._y+r2._height) res._height=abs((r1._y+r1._height)-res._y);
            else res._height=abs((r2._y+r2._height)-res._y);
            return res;
        }

        T1 & x()
        {
            return _x;
        }

        T1 & y()
        {
            return _y;
        }

        T1 & width()
        {
            return _width;
        }

        T1 & height()
        {
            return _height;
        }

        const T1 & x() const
        {
            return _x;
        }

        const T1 & y() const
        {
            return _y;
        }

        const T1 & width() const
        {
            return _width;
        }

        const T1 & height() const
        {
            return _height;
        }
};

template <class T> class Range
{
        T not_less,not_greater;
        bool not_less_or_equal,not_greater_or_equal;
    public:
        Range<T>(T not_less,T not_greater,bool not_less_or_equal=true,bool not_greater_or_equal=true)
        {
            define(not_less,not_greater,not_less_or_equal,not_greater_or_equal);
        }

        Range<T>(T element)
        {
            define(element,element);
        }

        void define(T not_less,T not_greater,bool not_less_or_equal=true,bool not_greater_or_equal=true)
        {
            if(not_less>not_greater) throw "Range<T>::define(): invalid range limit values, a>b";
            this->not_less=not_less;this->not_greater=not_greater;
            this->not_less_or_equal=not_less_or_equal;this->not_greater_or_equal=not_greater_or_equal;
        }

        void define(T v)
        {
            not_less=v;
        }

        bool contains(T v) const
        {
             return  (v>not_less&&v<not_greater)||
                     (not_less_or_equal&&v==not_less)||
                     (not_greater_or_equal&&v==not_greater);
        }

        bool contains(const Range<T>& range) const
        {
            return this->contains(range.not_less)&&this->contains(range.not_greater);
        }

        T left()
        {
            return not_less;
        }

        T right()
        {
            return not_greater;
        }

        template <class T1> friend std::ostream& operator <<(std::ostream& out, Range<T1> r);
};

template <class T> bool operator>(T v,const Range<T> & r)
         //friend Range<T>
{
    return (v>r.not_greater)||(v==r.not_greater&&!r.not_greater_or_equal);
};

template <class T> bool operator<(T v,const Range<T> & r)
{
    return (v<r.not_less)||(v==r.not_less&&!r.not_less_or_equal);
};// friend Range<T>;

template <class T>  std::ostream& operator <<(std::ostream& out,const Range<T> & r)
{
  char a='(',b=')';
  if(r.not_less_or_equal) a='[';
  if(r.not_greater_or_equal) b=']';
  return out<<"range "<<a<<r.not_less<<","<<r.not_greater<<b;
} //friend Range<T>;


// float TriangleXAxis(Vector3D<float>* t0,Vector3D<float>* t1,Vector3D<float>* t2,float c1,float c2,unsigned char axis);

}}

template<class T>std::ostream & operator<<(std::ostream& out,const Kongomato::Math::CommonVector<T>& vec)
{
    std::stringstream str;
    int size=vec.size();
    for(int a=0;a<size;a++) str<<vec(a)<<" ";
    return out<<"vector( "<<str.str()<<")";
}

template<class T>std::ostream & operator<<(std::ostream& out,const Kongomato::Math::CommonMatrix<T>& mat)
{
    std::stringstream str;
    int rows=mat.GetTotalRows();
    int columns=mat.GetTotalColumns();
    for(int a=0;a<rows;a++)
    {
        str<<"( ";
        for(int b=0;b<columns;b++)
            str<<mat[a][b]<<" ";
        str<<")";
        if(a<rows-1) str<<",";
    }
    return out<<"matrix( "<<str.str()<<" )";
}

template<class T>std::ostream & operator<<(std::ostream& out,const Kongomato::Math::CommonPlane<T>& plane)
{
        std::stringstream res;
        res<<"plane( ";
        int size=plane.GetSize();
        for(int a=0;a<size;a++)
            res<<plane.GetP(a)<<" ";
        res<<")";
        return out<<res.str();
}

template<class T>std::ostream & operator<<(std::ostream& out,const Kongomato::Math::Rectangle<T>& rectangle)
{
        std::stringstream res;
        res<<"rectangle( x="<<rectangle.x()<<" y="<<rectangle.y()
           <<" width="<<rectangle.width()<<" height="<<rectangle.height()<<" )";
        return out<<res.str();
}

template<class T>std::ostream & operator<<(std::ostream& out,const Kongomato::Math::Size<T>& size)
{
        std::stringstream res;
        res<<"rectangle("<<" width="<<size.width()<<" height="<<size.height()<<" )";
        return out<<res.str();
}

#endif
