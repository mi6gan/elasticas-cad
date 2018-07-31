/**  \file elcore.h
  *  \author M. S. Boyarov
  *  \brief Elasticas core interface.
  *
  *   This class provides interface for accessing El3D System common variables and "object classes".
  */

#ifndef ELCORE_H
#define ELCORE_H
#include <QVector>
#include <QString>
#include <QVariant>
#include <QHash>
#include <QDebug>
#include <QtXml/QtXml>
#include <QFile>
#include "elexception.h"
namespace Elasticas
{
 class MainWindow; 
 class Dialog;

 class DLL_DECLSPEC CommonData: public QHash<QString,QVariant>
 {
 public:
     QVariant & operator[] ( const QString & key );
     const QVariant operator[] ( const QString & key ) const;
 };
class DLL_DECLSPEC Core
{
    friend class Elasticas::MainWindow;
    friend class Elasticas::Dialog;
    CommonData common_variables;
    CommonData & CommonVariablesSafeRW();
    void saveCommonVariablesToFile(const QString & filename);
    void loadCommonVariablesFromFile(const QString & filename);
   protected:
    static Core* self;
    void parseClassesXML();
    void predefineVariables();
   public:
    /** Provides "object class"'s information which is useful in your own implementation of Plugin::update().
     * E.g., you can know either object is enabled or changed at the moment of Plugin::update() call.
     */
    class DLL_DECLSPEC ObjectClass
    {
        friend class Elasticas::Core;
        friend class Elasticas::MainWindow;
        friend class Elasticas::Dialog;
        bool enabled,changed;
        QString name;
        QVector<ObjectClass*> parents;
        QVector<ObjectClass*> children;
        ObjectClass(const QString & name);
        void setEnabled(bool enabled);
        bool setChanged(bool changed);
     public:
        void addChild(Core::ObjectClass* child);
        const QVector<Core::ObjectClass*> & parentsList();
        const QVector<Core::ObjectClass*> & childrenList();
        /**
          \return either this "object class" is in enabled state or not.
        */
        bool isEnabled() const;
        /**
          \return either this "object class" is in changed state or not.
        */
        bool isChanged() const;
        const QString & className();
        void subTreeList(QList<Core::ObjectClass*> & list);
        const QVariant & propertyValue(const QString & property_name) const;

    };
    friend class Core::ObjectClass;
    /**

    */
    const CommonData & commonVariables() const;

    /**
      \warining this method is deprecated, use  Core::commonVariables() instead.
    */
    const CommonData & CommonVariables() const;
    //const QHash< QString,Core::ObjectClass* > & objectClasses();
    const QList<Core::ObjectClass* > & objectClasses();
    QHash<QString,Core::ObjectClass*> & objectClassesHash();
    Core::ObjectClass* classByName(const QString & name,bool creatr_if_not_exist=true);
    static Core* Instance();
   private:
    //QHash< QString,Core::ObjectClass* > classes;
    QList<Core::ObjectClass* > classes;
    QHash<QString,Core::ObjectClass*> classes_hash;
    void addClass(Core::ObjectClass* object_class);
    void sortClassesByLevel();
};
}
#endif // CORE_H
