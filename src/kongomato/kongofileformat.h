/***************************************************************************
 *   Copyright (C) 2008 by Michael Boyarov				   *
 *   mi666gan@gmail.com   						   *
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
#ifndef KONGOFILEFORMAT_H
#define KONGOFILEFORMAT_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include <libgen.h>
#define dirname
#include "kongobase.h"
#include "kongomath.h"
namespace Kongomato { namespace FileFormat
{

class DLL_DECLSPEC Xfm3
{
        static void ReadElementsContainer(Base::ElementsContainer<float> & ec,std::ifstream& file);
	public:

        static void Load(const std::string & filename,Base::AbstractSubMesh* root,bool root_is_submesh=false);
        static void Save(const std::string & filename,const Base::AbstractSubMesh* root);
};
/*
class DLL_DECLSPEC Fm3
{
    template <class T1,class T2> static void SaveMeshData();
    static void SaveMeshNode(std::ofstream* to,NODE* child_node);
    template <class T1> static void SaveVertexElements(std::ofstream* to,T1* element,const char* type_name)
    {
                      //real
           for(int b=0;b<(*element).size()>0;b++)
           {
              *to<<"<vertex_element_array type="<<type_name<<
                   " element_length="<<
                   (*element)[b].GetStride()<<
                   " gl_fixed_target="<<
                   (*element)[b].GetTargetString()<<
                   " gl_attribute_index="<<
                   (*element)[b].GetGLAttributeIndex()<<
                   ">"<<std::endl;

                   for(int c=0;c<(*element)[b].GetRawArraySize();c++)
                      *to<<" "<<(*element)[b].GetRawArrayElement(c);

                  *to<<"</vertex_element_array>"<<std::endl;
          }
    }
    public:
    static void LoadNodeFromFile(const char* from,NODE& to);
    static void SaveNodeToFile(const char* to,NODE* from);

};*/

} }
#endif
