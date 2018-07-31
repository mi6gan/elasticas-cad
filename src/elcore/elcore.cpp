#include "elcore.h"

namespace Elasticas
{
QVariant & CommonData::operator[] ( const QString & key )
{
    if(key[0]=='T'&&key[1].isNumber()) return QHash<QString,QVariant>::operator []("Woman:"+key);
    return QHash<QString,QVariant>::operator [](key);
}

const QVariant CommonData::operator[] ( const QString & key ) const
{
    if(key[0]=='T'&&key[1].isNumber()) return QHash<QString,QVariant>::operator []("Woman:"+key);
    return QHash<QString,QVariant>::operator [](key);
}
//--------------------------------------------------------
Core::ObjectClass::ObjectClass(const QString & name)
{
    this->name=name;
    this->enabled=false;this->changed=true;
    Core::Instance()->addClass(this);
}

void Core::ObjectClass::addChild(Core::ObjectClass* child)
{
    this->children.append(child);
    child->parents.append(this);
}

const QVector<Core::ObjectClass*> & Core::ObjectClass::parentsList()
{
    return this->parents;
}

const QVector<Core::ObjectClass*> & Core::ObjectClass::childrenList()
{
    return this->children;
}

void Core::ObjectClass::setEnabled(bool enabled)
{
    QVectorIterator<ObjectClass*> it(this->parents);
    while(it.hasNext()) it.next()->setEnabled(enabled);
    this->enabled=enabled;
}

bool Core::ObjectClass::setChanged(bool changed)
{
    QVectorIterator<ObjectClass*> it(this->children);
    while(it.hasNext()) it.next()->setChanged(changed);
    this->changed=changed;
}

bool Core::ObjectClass::isEnabled() const
{
    return this->enabled;
}

bool Core::ObjectClass::isChanged() const
{
    return this->changed;
}

const QString & Core::ObjectClass::className()
{
    return this->name;
}

void Core::ObjectClass::subTreeList(QList<Core::ObjectClass*> & list)
{
    list.append(this);
    Core::ObjectClass* child;
    foreach(child, this->children) child->subTreeList(list);
}

const QVariant & Core::ObjectClass::propertyValue(const QString & property_name) const
{
    return Core::Instance()->common_variables[this->name+property_name];
}

//---------------------------------------------------------

Core* Core::self=NULL;

Core* Core::Instance()
{
    if(!self)
    {
        self=new Core;
        self->parseClassesXML();
        self->predefineVariables();
    }
    return self;
}

const CommonData & Core::commonVariables() const
{
    return this->common_variables;
}

const Elasticas::CommonData & Core::CommonVariables() const
{
    return this->commonVariables();
}

CommonData & Core::CommonVariablesSafeRW()
{
    return this->common_variables;
}

void Core::saveCommonVariablesToFile(const QString & filename)
{
    QFile file(filename);
    file.open(QFile::WriteOnly|QFile::Text);
    foreach(const QString & key,common_variables.keys())
    {
        file.write((common_variables[key].toString()+"\n").toUtf8());
        file.write((key+"\n").toUtf8());
        file.write((QString().setNum((int)common_variables[key].type())+"\n").toUtf8());
    }
    file.close();
}

void Core::loadCommonVariablesFromFile(const QString & filename)
{
    QFile file(filename);
    file.open(QFile::ReadOnly|QFile::Text);
    QByteArray value;
    while(!file.atEnd())
    {
        QVariant & v=common_variables[QObject::trUtf8(file.readLine()).remove('\n')]=QObject::trUtf8(file.readLine()).remove('\n');
        v.convert((QVariant::Type)QObject::trUtf8(file.readLine()).remove("\n").toInt());
    }
    file.close();
    foreach(const QString & key,classes_hash.keys())
    {
        classes_hash[key]->setChanged(true);
        common_variables[key+"Changed"]=true;
    }
}

/*
Elasticas::CommonData & Core::CommonVariablesRW()
{
    qDebug()<<"ElastiCas warning: writeable access to common variables";
    return this->common_variables;
}
*/

void Core::parseClassesXML()
{
    QFile oc_file("models/classes.xml");
    oc_file.open(QIODevice::ReadOnly);
    QXmlStreamReader xml_reader(&oc_file);
    QVector<QString> attr_stack;
    int level=0;
    while(!xml_reader.atEnd())
    {
        xml_reader.readNext();
        if(xml_reader.error())
        {
            qDebug()<<"Error in parsing classes.xml: "<<xml_reader.errorString()<<" ("<<xml_reader.lineNumber()<<")";
            break;
        }

        if( xml_reader.tokenType()==QXmlStreamReader::StartElement)
        {
            if(xml_reader.name().toString().toUtf8()=="class"&&xml_reader.name().toString().toUtf8()!="models")
            {
                level++;
                QXmlStreamAttributes attrs=xml_reader.attributes();
                int count=attrs.size();
                if(attrs.hasAttribute("id"))
                {
                    attr_stack.push_back(attrs.value("id").toString().toUtf8());
                    //qDebug()<<attr_stack.back();
                    const QString & id=attr_stack.back();
                    new Core::ObjectClass(id);
                    for(int a=0;a<count;a++)
                    {
                        if(attrs[a].name()=="id") continue;
                        this->common_variables[id+(attrs[a].name().toString().toUtf8())]=QObject::trUtf8(attrs[a].value().toString().toUtf8());
                    }
                    if(level==1) this->common_variables[id+"Level"]=-1;
                }

            }
        }
        else if(xml_reader.tokenType()==QXmlStreamReader::EndElement&&xml_reader.name().toString().toUtf8()!="models")
        {
            level--;
            if(attr_stack.size()>1) this->classByName(attr_stack[attr_stack.size()-2])->addChild(this->classByName(attr_stack.back()));
            attr_stack.pop_back();
        }
    }
    this->sortClassesByLevel();
}

void Core::predefineVariables()
{
#ifdef BUILD_DEBUG
    this->common_variables["Debug"]=1;
#endif
}

const QList<Core::ObjectClass* > & Core::objectClasses()
{
    return this->classes;
}

QHash<QString,Core::ObjectClass*> & Core::objectClassesHash()
{
    return this->classes_hash;
}

Core::ObjectClass* Core::classByName(const QString & name,bool create_if_not_exist)
{
    if(this->classes_hash.contains(name)) return this->classes_hash[name];
    else if(create_if_not_exist) return new Core::ObjectClass(name);
    return NULL;
}

void Core::sortClassesByLevel()
{
    Core::ObjectClass* obj;
    int size=this->classes.size();
    for(int j=1;j<size;j++)
        for(int i=0;i<size-j;i++)
        {
            if(this->classes[i]->propertyValue("Level").toInt()>this->classes[i+1]->propertyValue("Level").toInt())
            {
                obj=this->classes[i];
                this->classes[i]=this->classes[i+1];
                this->classes[i+1]=obj;
            }
        }
}

void Core::addClass(Core::ObjectClass* object_class)
{
    this->classes.append(object_class);
    if(this->classes_hash.contains(object_class->className())) qDebug()<<"Warning: duplicate class name:"<<object_class->className();
    this->classes_hash[object_class->className()]=object_class;
}

}
