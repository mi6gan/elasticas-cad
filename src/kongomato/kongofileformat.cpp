/***************************************************************************
 *   Copyright (C) 2008 by Michael Boyarov				   *
 *   mi666gan@gmail.com							   *
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
#include "kongofileformat.h"

namespace Kongomato { namespace FileFormat {
void Xfm3::ReadElementsContainer(Base::ElementsContainer<float> & ec,std::ifstream& file)
{
    unsigned int t_uint;
    int capacity=ec.get_element_capacity();
    file.read((char*)&t_uint,sizeof(t_uint));
    ec.resize(t_uint);
    Math::CommonVector<float> v(capacity);
    for(int a=0;a<t_uint;a++)
    {
        file.read((char*) &v[0],capacity*sizeof(float));
        ec[a]=v;
    }
}

void Xfm3::Load(const std::string & filename,Base::AbstractSubMesh* root,bool root_is_submesh)
{
    unsigned int t_uint,total_nodes;
    unsigned short t_ushort;
    char t_char;
    float t_float;
    std::string t_string;
    std::ifstream file(filename.c_str(),std::ios_base::binary);
    if(file.fail())  throw Base::Exception("void Xfm3::Load(const std::string & filename,Base::AbstractSubMesh* root) exception");
    file.read((char*)&total_nodes,sizeof(total_nodes));
    Base::AbstractSubMesh* submesh;
    Base::IndicesContainer* indices;
    Base::VerticesContainer* vertices;
    if(root_is_submesh) total_nodes=1;
    for(unsigned int a=0;a<total_nodes;a++)
    {
        if(root_is_submesh) submesh=root;
        else submesh=root->NewChild();
        submesh->LockBuffers(true);
        file.read((char*)&t_uint,sizeof(t_uint));
        if(t_uint>0)
        {            
            vertices=submesh->GetVertices();
            indices=submesh->GetIndices();
            indices->set_index_type(Base::index_16);
            indices->resize(t_uint);

            for(unsigned int b=0;b<t_uint;b++)
            {
                file.read((char*)&t_ushort,sizeof(t_ushort));
                indices->set_value(b,t_ushort);
            }            
        }
        file.read((char*)&t_uint,sizeof(t_uint));

        ReadElementsContainer(vertices->enable_vertex_attribute<float>(Base::vertex_attribute_id_position,3),file);
        ReadElementsContainer(vertices->enable_vertex_attribute<float>(Base::vertex_attribute_id_texture_coordinate,2),file);
        file.read((char*)&t_uint,sizeof(t_uint));
        for(int a=0;a<t_uint*3;a++) file.read(&t_char,sizeof(t_char));
        ReadElementsContainer(vertices->enable_vertex_attribute<float>(Base::vertex_attribute_id_normal,3),file);
        //

        file.read((char*)&t_uint,sizeof(t_uint));        
        t_string.resize(t_uint);

        file.read((char*)&t_string[0],t_uint);
        char* dname=strdup(filename.c_str());
        t_string="/"+t_string;
        submesh->InitializeTexture(dirname(dname)+t_string);
        free(dname);
        submesh->LockBuffers(false);
    }

    file.close();
}


void Xfm3::Save(const std::string & filen,const Base::AbstractSubMesh* root)
{
/*	unsigned int t_uint;
	ofstream file(filen,ios_base::binary);
	t_uint=mymesh.size();
	file.write((char*)&t_uint,sizeof(t_uint));
	for(unsigned int a=0;a<mymesh.size();a++)
	{
                t_uint=mymesh[a].indices->i16.size();
		file.write((char*)&t_uint,sizeof(t_uint));
                for(unsigned int b=0;b<mymesh[a].indices->i16.size();b++)
                        file.write((char*)mymesh[a].indices->i16[b].GetCPointer(),mymesh[a].indices->i16[b].GetSizeInBytes());
                t_uint=mymesh[a].indices->i32.size();
		file.write((char*)&t_uint,sizeof(t_uint));
                for(unsigned int b=0;b<mymesh[a].indices->i32.size();b++)
                         file.write((char*)mymesh[a].indices->i32[b].GetCPointer(),mymesh[a].indices->i32[b].GetSizeInBytes());

                WriteVertexAttrToXfm3(&mymesh[a].vertices->real[0],&file);//xyz
                WriteVertexAttrToXfm3(&mymesh[a].vertices->real[3],&file);//uv
                WriteVertexAttrToXfm3(&mymesh[a].vertices->real[1],&file);//uvw
                WriteVertexAttrToXfm3(&mymesh[a].vertices->real[2],&file);//normal

		t_uint=mymesh[a].tx_n.size();
		file.write((char*)&t_uint,sizeof(t_uint));
		file.write((char*)&mymesh[a].tx_n[0],t_uint);
	}
        file.close();*/
}
/*
void Fm3::LoadNodeFromFile(const char* from,NODE& to)
{ */
 /*   xmlDocPtr doc;
    xmlNodePtr node;
    std::ofstream file(to);
    file<<"<?xml version=\"1.0\"?>"<<endl<<"<kongofm3 version=\"0.01\">"<<endl<<"</kongofm3>"<<endl;
    file.close();
    doc=xmlParseFile(to);
    node=xmlDocGetRootElement(doc);
    node=xmlNewChild(node,NULL,(const xmlChar*)"mesh_sequence",(const xmlChar*)"\n");
    for(int a=0;a<(int)from->child.size();a++)
    AddXmlChildFromMeshNode(node,from->child[a]);
    xmlSaveFormatFile(to,doc,true);*/


/*
}

void Fm3::SaveNodeToFile(const char* to,NODE* from)
{
    ofstream file(to);
    file<<"<?xml version=\"1.0\"?>"<<endl<<"<kongofm3 version=\"0.01\">"<<endl;
    file<<"<mesh_sequence>"<<std::endl;
    for(int a=0;a<from->child.size();a++)
    SaveMeshNode(&file,from->child[a]);
    file<<"</mesh_sequence>"<<std::endl;
    file<<"</kongofm3>"<<endl;
    file.close();
}

  void Fm3::SaveMeshNode(std::ofstream* to,NODE* child_node)
  {
        SUBMESH_NODE* submesh_node;
        switch(child_node->type)
        {
            case node_type_mesh:
            *to<<"<mesh name=\'"<<child_node->name<<"\'>"<<std::endl;
            for(int a=0;a<(int)child_node->child.size();a++)
            {
                *to<<"<submesh name=\'"<<child_node->child[a]->name+"\'>"<<std::endl;
                if(child_node->child[a]->type==node_type_submesh)
                {
                    submesh_node=(SUBMESH_NODE*)child_node->child[a];
               //real
                    SaveVertexElements(to,&submesh_node->vertices->real,"real");
                    SaveVertexElements(to,&submesh_node->vertices->integer,"integer");
               }
               *to<<"</submesh>"<<std::endl;
            }
            *to<<"</mesh>"<<std::endl;
            break;
            default:
            break;

        }
  }
*/
} }




