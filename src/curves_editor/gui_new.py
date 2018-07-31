# -*- coding: utf-8 -*-
import sys
import math
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from os import environ
environ["DOT_SAGE"]="./.sage"
# from sage.all import *

class GeometricObject:  
  objects={}
  top_level_items={}
  tree_item_to_object={}
  selected=None
  type_name="Geometric Object"
  @staticmethod
  def clear():
    for type_name in GeometricObject.objects:
      for obj in GeometricObject.objects[type_name]:
	GeometricObject.top_level_items[type_name].removeChild(obj.tree_item)
    GeometricObject.tree_widget.clear()    
    GeometricObject.objects.clear()
    GeometricObject.tree_item_to_object.clear()
    GeometricObject.top_level_items.clear()   
  
  @staticmethod
  def Initialize(graphics_view,grid): 
    GeometricObject.graphics_view=graphics_view
    GeometricObject.grid=grid
    GeometricObject.tree_widget=QTreeWidget()
    GeometricObject.tree_widget.setHeaderLabel("")
    GeometricObject.tree_widget.currentItemChanged.connect(GeometricObject.currentItemChanged)
    
    GeometricObject.remove_current_button=QPushButton(GeometricObject.tree_widget.trUtf8("Удалить"))
    GeometricObject.remove_current_button.released.connect(GeometricObject.removeCurrentItem)
    GeometricObject.rename_current_button=QPushButton(GeometricObject.tree_widget.trUtf8("Переименовать"))
    GeometricObject.rename_current_button.released.connect(GeometricObject.renameCurrentItem)
    GeometricObject.up_down_widget=QWidget()
    GeometricObject.up_down_widget.setLayout(QHBoxLayout())
    GeometricObject.up_button=QPushButton(GeometricObject.tree_widget.trUtf8("Вверх"))
    GeometricObject.down_button=QPushButton(GeometricObject.tree_widget.trUtf8("Вниз"))
    GeometricObject.up_button.released.connect(GeometricObject.setCurrentUp)
    GeometricObject.down_button.released.connect(GeometricObject.setCurrentDown)
    GeometricObject.up_down_widget.layout().addWidget(GeometricObject.up_button)
    GeometricObject.up_down_widget.layout().addWidget(GeometricObject.down_button)
    
    GeometricObject.widget=QWidget()
    GeometricObject.widget.setLayout(QVBoxLayout())
    GeometricObject.widget.layout().addWidget(GeometricObject.tree_widget)
    GeometricObject.widget.layout().addWidget(GeometricObject.up_down_widget)
    GeometricObject.widget.layout().addWidget(GeometricObject.rename_current_button)
    GeometricObject.widget.layout().addWidget(GeometricObject.remove_current_button)
    GeometricObject.remove_current_button.setEnabled(False)
    GeometricObject.rename_current_button.setEnabled(False)
    GeometricObject.up_down_widget.setEnabled(False)
    
    
  @staticmethod
  def addObject(obj,type_name):
    if not GeometricObject.objects.has_key(type_name): GeometricObject.objects[type_name]=[]
    if not GeometricObject.top_level_items.has_key(type_name):
      top_level_item=QTreeWidgetItem()
      top_level_item.setText(0,type_name)
      GeometricObject.top_level_items[type_name]=top_level_item
      GeometricObject.tree_widget.addTopLevelItem(top_level_item)
      GeometricObject.tree_widget.expandItem(top_level_item)
      
    GeometricObject.objects[type_name].append(obj)
    tree_item=QTreeWidgetItem()
    GeometricObject.tree_item_to_object[tree_item]=obj
    obj.tree_item=tree_item
    tree_item.setText(0,obj.name)
    GeometricObject.top_level_items[type_name].addChild(tree_item)  
    
  @staticmethod
  def xToGridCenter(x): 
    grd_w=GeometricObject.grid.width_spinbox.value()
    return grd_w*int(x/grd_w)+grd_w/2.0
  @staticmethod
  def yToGridCenter(y): 
    grd_h=GeometricObject.grid.height_spinbox.value()
    return grd_h*int(y/grd_h)+grd_h/2.0
  @staticmethod
  def updateAll():
    for key,o_lst in GeometricObject.objects.iteritems():
      for obj in o_lst: obj.update()
      
  @staticmethod
  def currentItemChanged(item,previous):
    if GeometricObject.tree_item_to_object.has_key(item):
      GeometricObject.remove_current_button.setEnabled(True)
      GeometricObject.rename_current_button.setEnabled(True)
      GeometricObject.up_down_widget.setEnabled(True)
      GeometricObject.tree_item_to_object[item].select()
    else:
      GeometricObject.remove_current_button.setEnabled(False)
      GeometricObject.rename_current_button.setEnabled(False)
      GeometricObject.up_down_widget.setEnabled(False)
      if not GeometricObject.selected is None: GeometricObject.selected.deselect()
  
  @staticmethod
  def removeCurrentItem():
    item=GeometricObject.tree_widget.currentItem()
    if GeometricObject.tree_item_to_object.has_key(item):
      obj=GeometricObject.tree_item_to_object[item]
      GeometricObject.removeObject(obj)
  
  @staticmethod
  def swapItems(item1,item2):
    if not (GeometricObject.tree_item_to_object.has_key(item1) and GeometricObject.tree_item_to_object.has_key(item2)): return
    obj1=GeometricObject.tree_item_to_object[item1]
    obj2=GeometricObject.tree_item_to_object[item2]
    objects=GeometricObject.objects[obj1.type_name]
    i1=objects.index(obj1)
    i2=objects.index(obj2)
    GeometricObject.tree_item_to_object[item1],GeometricObject.tree_item_to_object[item2]=obj2,obj1
    objects[i1],objects[i2]=objects[i2],objects[i1]
    item1.setText(0,obj2.name)
    item2.setText(0,obj1.name)
    if GeometricObject.tree_widget.currentItem() is item1: GeometricObject.tree_widget.setCurrentItem(item2)
    elif GeometricObject.tree_widget.currentItem() is item2: GeometricObject.tree_widget.setCurrentItem(item1)
    
  
  @staticmethod
  def renameCurrentItem():
    item=GeometricObject.tree_widget.currentItem()
    if GeometricObject.tree_item_to_object.has_key(item):
      GeometricObject.tree_item_to_object[item].rename()
  
  @staticmethod
  def setCurrentDown():
    item=GeometricObject.tree_widget.currentItem()
    GeometricObject.swapItems(item,GeometricObject.tree_widget.itemBelow(item))
      

  @staticmethod
  def setCurrentUp():
    item=GeometricObject.tree_widget.currentItem()
    GeometricObject.swapItems(item,GeometricObject.tree_widget.itemAbove(item))
    
  @staticmethod
  def removeObject(obj):
      obj.deselect()
      GeometricObject.top_level_items[obj.type_name].removeChild(obj.tree_item)
      GeometricObject.objects[obj.type_name].remove(obj)
      del GeometricObject.tree_item_to_object[obj.tree_item]
      
  def __init__(self):
    self.name="Unnamed"
    GeometricObject.addObject(self,self.type_name)
  
  def __del__(self): pass
    
  def rename(self,name=None):
    if name is None:
      name,ok = QInputDialog.getText(GeometricObject.graphics_view, GeometricObject.graphics_view.trUtf8("Название объекта"),GeometricObject.graphics_view.trUtf8("Название "),QLineEdit.Normal,self.name)
    else: ok=True
    if ok and not name=="": self.name=name
    self.tree_item.setText(0,self.name)
  
  def deselect(self):
    if GeometricObject.selected is self: GeometricObject.selected=None
  
  def select(self):
     if not GeometricObject.selected is None: GeometricObject.selected.deselect()
     GeometricObject.selected=self
  
  def index(self):
    return GeometricObject.objects[self.type_name].index(self)
  
  def isPointIn(self,x,y): return False
  def Serialize(self): return "[]"
  def update(self): pass
  
  
class Knot(GeometricObject):
  type_name=QObject().trUtf8("Узел")
  def __init__(self,x=0,y=0): 
    GeometricObject.__init__(self)
    self.x=x
    self.y=y
    self.rect_item=GeometricObject.graphics_view.scene().addRect(QRectF())
    self.text_item=GeometricObject.graphics_view.scene().addText(self.name)
    self.text_item.setX(x)
    self.text_item.setY(y)
    self.setColor(QColor(0,0,0))
    self.rect_item.setZValue(0.1)
    self.text_item.setZValue(0.2)
    self.update()
  
  def __del__(self):
    GeometricObject.graphics_view.scene().removeItem(self.rect_item)
    GeometricObject.graphics_view.scene().removeItem(self.text_item)
    GeometricObject.__del__(self)
  
  def rename(self,name=None):
    GeometricObject.rename(self,name)
    self.text_item.setPlainText(self.name)
    
  def isPointIn(self,x,y):
    return self.rect_item.rect().contains(x,y)
  
  def setColor(self,color):
    self.rect_item.setBrush(color)
    self.text_item.setDefaultTextColor(color)
    
  def update(self):
    gx=self.xToGridCenter(self.x)
    gy=self.yToGridCenter(self.y)
    gw=self.grid.width_spinbox.value()
    gh=self.grid.height_spinbox.value()
    self.rect_item.setRect(QRectF(gx-gw/2.0,gy-gh/2.0,gw,gh))
  
  def deselect(self):
    GeometricObject.deselect(self)
    self.setColor(QColor(0,0,0))
    
  def select(self):
    GeometricObject.select(self)
    self.setColor(QColor(255,0,0))
  
  @staticmethod
  def knotByPoint(x,y):
    print x,y
    for knot in GeometricObject.objects[Knot.type_name]:
      if knot.isPointIn(x,y): return knot
    return None
    
class Segment(GeometricObject):
  def __init__(self,knot1,knot2):
    GeometricObject.__init__(self)
    self.knot1=knot1
    self.knot2=knot2
  
  def __del__(self):
    GeometricObject.__del__(self)
    
class LineSegment(Segment):
  type_name=QObject().trUtf8("Прямая")
  def __init__(self,knot1,knot2): 
    Segment.__init__(self,knot1,knot2)
    self.arrow_item=GeometricObject.graphics_view.scene().addPath(QPainterPath())
    if knot1 is None or knot2 is None: self.line_item=GeometricObject.graphics_view.scene().addLine(QLineF())
    else: 
      self.line_item=GeometricObject.graphics_view.scene().addLine(knot1.x,knot1.y,knot2.x,knot2.y)
      self.updateArrow()
    self.line_item.setZValue(0.3)
    
    
  def updateArrow(self):
    path=QPainterPath()
    path.moveTo(-8,2)
    path.lineTo(0,0)
    path.lineTo(-8,-2)
    path.lineTo(-8,2)
    self.arrow_item.setBrush(QBrush(QColor()))
    self.arrow_item.setPath(path)
    #self.arrow_item.
    self.arrow_item.setRotation(360.0-self.line_item.line().angle())
    self.arrow_item.setPos(self.line_item.line().x2(),self.line_item.line().y2())
  
  def setColor(self,color):
    self.arrow_item.setBrush(color)
    self.line_item.setPen(color)
  
  def deselect(self):
    GeometricObject.deselect(self)
    self.setColor(QColor(0,0,0))
    
    
  def select(self):
    GeometricObject.select(self)
    self.setColor(QColor(255,0,0))
    
  def __del__(self):
    GeometricObject.graphics_view.scene().removeItem(self.line_item)
    GeometricObject.graphics_view.scene().removeItem(self.arrow_item)
    Segment.__del__(self)
    
class ApproximationSegment(LineSegment):
  type_name=QObject().trUtf8("Сегмент")
  def __init__(self):
    LineSegment.__init__(self,None,None)
    self.line_item.setPen(QPen(Qt.DotLine))
    self.points=[]
    self.items=[]
    
  def setKnots(self,knot1,knot2):
    self.knot1=knot1
    self.knot2=knot2
    self.line_item.setLine(QLineF(knot1.x,knot1.y,knot2.x,knot2.y))
    self.updateArrow()
  
  def setColor(self,color):
    LineSegment.setColor(self,color)
    for item in self.items: item.setBrush(color)
    pen=QPen(Qt.DotLine)
    pen.setColor(color)
    self.line_item.setPen(pen)
  
  def deselect(self):
    LineSegment.deselect(self)
    self.setColor(QColor(0,0,255))
    
  def select(self):
    LineSegment.select(self)
    self.setColor(QColor(255,0,0))
    
  def __del__(self):
    for item in self.items:
      GeometricObject.graphics_view.scene().removeItem(item)
    LineSegment.__del__(self)
  
  def addPoint(self,x,y): 
    gx=ApproximationSegment.xToGridCenter(x)
    gy=ApproximationSegment.yToGridCenter(y)
    gw=ApproximationSegment.grid.width_spinbox.value()
    gh=ApproximationSegment.grid.height_spinbox.value()
    rect=QRectF(gx-gw/2.0,gy-gh/2.0,gw,gh)
    for i in  range(len(self.items)):
      if rect==self.items[i].rect():
	if i==len(self.items)-1:
	  GeometricObject.graphics_view.scene().removeItem(self.items[i])
	  self.points.remove(self.points[i])
	  self.items.remove(self.items[i])
	return
    item=GeometricObject.graphics_view.scene().addEllipse(rect)
    item.setZValue(0.1)
    item.setBrush(QColor(0,0,255))
    self.points.append([x,y])
    self.items.append(item)
  
  def update(self):
    gw=ApproximationSegment.grid.width_spinbox.value()
    gh=ApproximationSegment.grid.height_spinbox.value()
    for i in range(len(self.items)):
      gx=ApproximationSegment.xToGridCenter(self.points[i][0])
      gy=ApproximationSegment.yToGridCenter(self.points[i][1])
      self.items[i].setRect(QRectF(gx-gw/2.0,gy-gh/2.0,gw,gh))

class PolarApproximationSegment(ApproximationSegment):
  type_name=QObject().trUtf8("Сегмент полярной аппроксимации")
  def __init__(self,knot1,knot2):
    ApproximationSegment.__init__(self)
    ApproximationSegment.setKnots(self,knot1,knot2)
    self.angle1=0.0
    self.angle2=90.0
    self.count=8
    self.horizontal=True
  
  def setAngles(self,angle1=None,angle2=None,count=None,horizontal=None):
    w=GeometricObject.graphics_view
    hstr=None
    ok=True
    if angle1 is None: angle1,ok=QInputDialog.getDouble(w, w.trUtf8("Начальный угол"),w.trUtf8("Угол"), self.angle1, 0, 100000, 2)
    if not ok: return
    ok=True
    if angle2 is None: angle2,ok=QInputDialog.getDouble(w, w.trUtf8("Конечный угол"),w.trUtf8("Угол"), self.angle2, 0, 100000, 2)
    if not ok: return
    ok=True
    if count is None: count,ok=QInputDialog.getInt(w, w.trUtf8("Количество промежуточных точек"),w.trUtf8("Количество"), self.count, 0, 100000, 1)
    if not ok: return
    if horizontal is None: hstr,ok=QInputDialog.getItem(w, w.trUtf8("Ориентация сегмента"),w.trUtf8("Ориентация"),[w.trUtf8("Вертикальный"),w.trUtf8("Горизонтальный")],self.horizontal)
    self.angle1,self.angle2,self.count=angle1,angle2,count
    if hstr is None: self.horizontal=horizontal
    else: (horizontal==w.trUtf8("Горизонтальный"))
  
  def __del__(self):
    ApproximationSegment.__del__(self)
      
class Grid:
  def __init__(self,graphics_view):
    self.graphics_view=graphics_view

    self.item=graphics_view.scene().addPath(QPainterPath())
    self.item.setZValue(0.2)
    
    self.set_visible_checkbox=QCheckBox(graphics_view.trUtf8("Показать"))
    self.set_visible_checkbox.stateChanged.connect(self.item.setVisible)
    self.set_visible_checkbox.setChecked(True)
    
    self.width_widget=QWidget()
    self.width_widget.setLayout(QHBoxLayout())
    self.set_width_button=QPushButton(self.width_widget.trUtf8("Шаг по ширине"))
    self.set_width_button.setCheckable(True)
    self.width_spinbox=QSpinBox()
    self.width_spinbox.setValue(10)
    self.width_spinbox.setSuffix(self.width_spinbox.trUtf8(" тчк."))
    self.width_widget.layout().addWidget(self.set_width_button)
    self.width_widget.layout().addWidget(self.width_spinbox)
    
    self.height_widget=QWidget()
    self.height_widget.setLayout(QHBoxLayout())
    self.set_height_button=QPushButton(self.height_widget.trUtf8("Шаг по высоте"))
    self.set_height_button.setCheckable(True)
    self.height_spinbox=QSpinBox()
    self.height_spinbox.setValue(10)
    self.height_spinbox.setSuffix(self.height_spinbox.trUtf8(" тчк."))
    self.height_widget.layout().addWidget(self.set_height_button)
    self.height_widget.layout().addWidget(self.height_spinbox)
    
    self.widget=QWidget()
    self.widget.setLayout(QVBoxLayout())
    self.widget.layout().addWidget(self.set_visible_checkbox)
    self.widget.layout().addWidget(self.width_widget)
    self.widget.layout().addWidget(self.height_widget)
    self.widget.setMaximumHeight(150)
    

    self.Update()
    
  def Update(self):
    hstep=self.width_spinbox.value()
    vstep=self.height_spinbox.value()
    width=self.graphics_view.scene().width()
    height=self.graphics_view.scene().height()
    path=QPainterPath()
    i_count=int(width)/hstep+1
    j_count=int(height)/vstep+1
    for i in range(i_count):
     path.moveTo(i*hstep,0)
     path.lineTo(i*hstep,height)
    for j in range(j_count):
     path.moveTo(0,j*vstep)
     path.lineTo(width,j*vstep)
    self.item.setPath(path)

class ImageLibrary(QObject):
  ImageChanged= pyqtSignal(name='ImageChanged')
  def __init__(self,graphics_view):
    QObject.__init__(self)
    self.current=None
    self.graphics_view=graphics_view
    self.pixmap_item=graphics_view.scene().addPixmap(QPixmap())
    self.pixmaps=[]
    self.widget=QWidget()
    self.widget.setLayout(QVBoxLayout())
    self.list_widget=QListWidget()
    self.list_widget.itemDoubleClicked.connect(self.SetCurrent)
    self.add_image_button=QPushButton(self.widget.trUtf8("Добавить"))
    self.file_dialog=QFileDialog()
    self.add_image_button.released.connect(self.file_dialog.exec_)
    self.file_dialog.accepted.connect(self.AddImage)
    self.delete_image_button=QPushButton(self.widget.trUtf8("Удалить"))
    self.delete_image_button.released.connect(self.RemoveCurrentImage)
    self.scale_image_button=QPushButton(self.widget.trUtf8("Масштабировать"))
    self.scale_image_button.released.connect(self.ScaleImage)
    
    self.delete_image_button.setEnabled(False)
    self.scale_image_button.setEnabled(False)
    self.widget.layout().addWidget(self.list_widget)
    self.widget.layout().addWidget(self.add_image_button)
    self.widget.layout().addWidget(self.scale_image_button)
    self.widget.layout().addWidget(self.delete_image_button)
    
  
  def AddImage(self,image_path=None,factor=1.0):
    if image_path is None: image_path=self.file_dialog.selectedFiles()[0]
    list_item=QListWidgetItem(QFileInfo(image_path).baseName())
    list_item.setToolTip(image_path)
    self.list_widget.addItem(list_item)
    self.delete_image_button.setEnabled(True)
    self.scale_image_button.setEnabled(True)
    self.pixmaps.append([image_path,factor])
    #self.SetCurrent()
  
  def ScaleImage(self,factor=None):
    row=self.list_widget.currentRow()
    if row<0: return
    if factor is None:
      factor,ok=QInputDialog.getDouble(self.list_widget, self.trUtf8("Масштабировать"),self.trUtf8("Коэффициент"), 1.0, 0, 100000, 2)
      if not ok: return
    self.pixmaps[row][1]*=factor
    if self.pixmaps[row]==self.current: self.SetCurrent()
    # src_pixmap=self.pixmap_item.pixmap()
    #pixmap=src_pixmap.scaled(src_pixmap.width()*factor,src_pixmap.height()*factor)
    
  
  def RemoveCurrentImage(self):
    row=self.list_widget.currentRow()
    self.list_widget.takeItem(row)
    if not self.list_widget.count(): 
      self.delete_image_button.setEnabled(False)
      self.scale_image_button.setEnabled(False)
    else: self.list_widget.setCurrentItem(self.list_widget.item(self.list_widget.count()-1))
    if self.pixmaps[row]==self.current: 
      self.current=None
      self.pixmap_item.setPixmap(QPixmap())
    self.pixmaps.remove(self.pixmaps[row])
  
  def clear(self):
    self.list_widget.clear()
    self.pixmaps=[]
    self.pixmap_item.setPixmap(QPixmap())
    self.delete_image_button.setEnabled(False)
    self.scale_image_button.setEnabled(False)
  
  def SetCurrent(self):
    row=self.list_widget.currentRow()
    if row>-1: 
      self.current=self.pixmaps[row]
      pixmap=QPixmap(self.current[0])
      if self.current[1]<>1.0: self.pixmap_item.setPixmap(pixmap.scaled(pixmap.width()*self.current[1],pixmap.height()*self.current[1]))
      else: self.pixmap_item.setPixmap(pixmap)
    else: 
      self.current=None
      self.pixmap_item.setPixmap(QPixmap())
    self.ImageChanged.emit()
    
GeometricObjectClasses=(Knot,LineSegment,ApproximationSegment)
#,PolarApproximationSegment)

class GraphicsView(QGraphicsView): 
  mousePressed = pyqtSignal(QMouseEvent, name='mousePressed')
  mouseMoved = pyqtSignal(QMouseEvent, name='mouseMoved')
  
  def __init__(self): 
    QGraphicsView.__init__(self)
    self.setMouseTracking(True)
    
  def mousePressEvent (self, event):
    self.mousePressed.emit(event)
    
  def mouseMoveEvent (self, event):
    self.mouseMoved.emit(event)
    
class MainWindow(QMainWindow):
    def __init__(self):
      QMainWindow.__init__(self)
      self.selected_knots=[]
      self.selected_points=[]
      self.selected_items=[]
      self.start_point=[0.0,0.0]
      self.current_tool=None
      self.current_segment=None
      self.sage_imported=True
      self.cropped_rect=[0,0,0,0]
      
      self.graphics_scene=QGraphicsScene()
      self.graphics_view=GraphicsView()
      self.graphics_view.mouseMoved.connect(self.GraphicsViewMouseMoved)
      self.graphics_view.mousePressed.connect(self.GraphicsViewMousePressed)
      self.graphics_view.setScene(self.graphics_scene)
      
      self.helper_line=self.graphics_scene.addLine(QLineF())
      self.helper_line.setZValue(0.1)
      
      self.menu_bar=QMenuBar()
      self.setMenuBar(self.menu_bar)
      file_menu=self.menu_bar.addMenu(self.trUtf8("Файл"))
      self.file_load_dialog=QFileDialog()
      self.file_save_dialog=QFileDialog()
      self.file_save_dialog.setAcceptMode(QFileDialog.AcceptSave)
      file_menu.addAction(self.trUtf8("Новый")).triggered.connect(self.resetAll)
      file_menu.addAction(self.trUtf8("Открыть...")).triggered.connect(self.file_load_dialog.exec_)
      file_menu.addAction(self.trUtf8("Сохранить как...")).triggered.connect(self.file_save_dialog.exec_)
      file_menu.addAction(self.trUtf8("Сохранить")).triggered.connect(self.saveToFile)
      self.file_save_dialog.accepted.connect(self.saveToFile)
      self.file_load_dialog.accepted.connect(self.loadFromFile)
      
      
      self.dock_widget1=QDockWidget(self.trUtf8("Создать"))
      self.tools_widget=QWidget()
      self.dock_widget1.setWidget(self.tools_widget)
      self.tools_widget.setLayout(QVBoxLayout())
      max_height=0
      for TheClass in GeometricObjectClasses:
	max_height+=50
	TheClass.creationButton=QPushButton(TheClass.type_name)
	TheClass.creationButton.setCheckable(True)
	TheClass.creationButton.toggled.connect(self.setCurrentTool)
	self.tools_widget.layout().addWidget(TheClass.creationButton)
	GeometricObject.objects[TheClass.type_name]=[]
      self.tools_widget.setMaximumHeight(max_height)
      
      self.dock_widget2=QDockWidget(self.trUtf8("Изображения"))
      self.image_library=ImageLibrary(self.graphics_view)
      self.dock_widget2.setWidget(self.image_library.widget)
      
      self.dock_widget3=QDockWidget(self.trUtf8("Сетка"))
      self.grid=Grid(self.graphics_view)
      self.grid.set_width_button.toggled.connect(self.setCurrentTool)
      self.grid.set_height_button.toggled.connect(self.setCurrentTool)
      self.grid.width_spinbox.valueChanged.connect(self.updateAll)
      self.grid.height_spinbox.valueChanged.connect(self.updateAll)
      self.dock_widget3.setWidget(self.grid.widget)
      self.image_library.ImageChanged.connect(self.updateAll)
      
      GeometricObject.Initialize(self.graphics_view,self.grid)
      
      self.dock_widget5=QDockWidget(self.trUtf8("Навигация"))
      self.navigation_widget=QWidget()
      self.navigation_widget.setLayout(QVBoxLayout())
      self.dock_widget5.setWidget(self.navigation_widget)
      self.zoom_in_button=QPushButton("+")
      self.zoom_out_button=QPushButton("-")
      self.zoom_in_button.released.connect(self.zoomIn)
      self.zoom_out_button.released.connect(self.zoomOut)
      self.navigation_widget.layout().addWidget(self.zoom_in_button)
      self.navigation_widget.layout().addWidget(self.zoom_out_button)
      
      self.dock_widget4=QDockWidget(self.trUtf8("Объекты"))
      self.dock_widget4.setWidget(GeometricObject.widget)
      
      self.dock_widget6=QDockWidget(self.trUtf8("Параметры"))
      params_widget=QFrame()
      params_widget.setLayout(QHBoxLayout())
      params_widget.layout().addWidget(QLabel(self.trUtf8("Рост (см)")))
      self.growth_dspinbox=QDoubleSpinBox()
      self.growth_dspinbox.setMaximum(300.0)
      params_widget.layout().addWidget(self.growth_dspinbox)
      self.dock_widget6.setWidget(params_widget)
      
      self.status_bar=QStatusBar()
      self.status_bar_message1=QLabel()
      self.status_bar_button1=QPushButton(self.trUtf8("Определить точку отсчёта"))
      self.status_bar_button1.setCheckable(True)
      self.status_bar_button1.toggled.connect(self.setCurrentTool)
      # self.status_bar_message2=QLabel()
      self.status_bar.addWidget(self.status_bar_message1)
      self.status_bar.addWidget(self.status_bar_button1)
      # self.status_bar.addWidget(self.status_bar_message2)
      self.setStatusBar(self.status_bar)

      self.setCentralWidget(self.graphics_view)
      self.addDockWidget(Qt.RightDockWidgetArea, self.dock_widget4)
      self.addDockWidget(Qt.RightDockWidgetArea, self.dock_widget1)
      self.addDockWidget(Qt.LeftDockWidgetArea, self.dock_widget2)
      self.addDockWidget(Qt.LeftDockWidgetArea, self.dock_widget6)
      self.addDockWidget(Qt.LeftDockWidgetArea, self.dock_widget5)
      self.addDockWidget(Qt.LeftDockWidgetArea, self.dock_widget3)
    
    def resetAll(self):
      if "last_saved_file" in self.__dict__: del self.__dict__["last_saved_file"]
      self.image_library.clear()
      GeometricObject.clear()
    
    def saveToFile(self):
      if self.sender() is self.file_save_dialog: file_path=self.file_save_dialog.selectedFiles()[0]
      else:
	if "last_saved_file" in self.__dict__: file_path=self.last_saved_file
	else:
	  self.file_save_dialog.exec_()
	  return
      if "file_dict" in self.__dict__: file_dict=self.file_dict
      else: file_dict={}
      
      f=open(str(file_path.toLocal8Bit()),"w")
      f.write("# -*- coding: utf-8 -*-\n")
      prefixes=[]
      for type_name,obj_lst in GeometricObject.objects.iteritems():
        prefix=""
	if type_name==self.trUtf8("Узел"): prefix="knots="
	elif type_name==self.trUtf8("Прямая"): prefix="line_segments="
	elif type_name==self.trUtf8("Сегмент"): prefix="approx_segments="
	elif type_name==self.trUtf8("Сегмент полярной аппроксимации"): prefix="polar_approx_segments="
	if len(prefix): prefixes.append(prefix)
	else: continue
	lst=[]
	for obj in obj_lst:
	  if type_name==self.trUtf8("Узел"): lst.append([str(obj.name),[obj.x,obj.y]])
	  elif type_name==self.trUtf8("Прямая"):
	    lst.append([str(obj.name),[obj.knot1.index(),obj.knot2.index()]])  
	  elif type_name==self.trUtf8("Сегмент") or type_name==self.trUtf8("Сегмент полярной аппроксимации"):
	    lst.append([])
	    lst[-1].append(str(obj.name))
	    lst[-1].append([obj.knot1.index(),obj.knot2.index()])
	    lst[-1].append(obj.points)
	    if type_name==self.trUtf8("Сегмент полярной аппроксимации"): lst[-1].append([obj.angle1,obj.angle2,obj.horizontal]) 
	f.write(prefix+str(lst)+"\n")
      for prefix in "knots=","line_segments=","approx_segments=","polar_approx_segments=":
        if not prefix in prefixes: f.write(prefix+"[]\n")	
      lst=[]
      for pixmap in self.image_library.pixmaps: lst.append([pixmap[1],str(QFileInfo(file_path).dir().relativeFilePath(pixmap[0]).toUtf8()) ])
      f.write("img_size=["+str(self.image_library.pixmap_item.pixmap().width())+","+str(self.image_library.pixmap_item.pixmap().height())+"]\n")
      
      f.write("pixmaps="+str(lst)+"\n")
      f.write("grid="+str([self.grid.width_spinbox.value(),self.grid.height_spinbox.value(),self.grid.set_visible_checkbox.isChecked()])+"\n")
      f.write("start_point="+str(self.start_point)+"\n")
      f.write("cropped_rect="+str(self.cropped_rect)+"\n")
      f.write("growth="+str(self.growth_dspinbox.value())+"\n")
      for name, value in file_dict.iteritems(): f.write(name+"="+str(value)+"\n")
      f.close()
      self.last_saved_file=file_path
	
	
    def loadFromFile(self):
      knots=[]
      line_segments=[]
      approx_segments=[]
      polar_approx_segments=[]
      GeometricObject.clear()
      file_path=self.file_load_dialog.selectedFiles()[0]
      self.file_dict=file_dict={}
      exec open(str(file_path.toLocal8Bit()),"r") in None,file_dict
      grid,start_point,cropped_rect,pixmaps,knots,approx_segments,line_segments= \
	file_dict['grid'],file_dict['start_point'],file_dict['cropped_rect'],file_dict['pixmaps'],file_dict['knots'],file_dict['approx_segments'],file_dict['line_segments']
      del file_dict['grid']; del file_dict['start_point']; del file_dict['cropped_rect']
      del file_dict['pixmaps']; del file_dict['knots']; del file_dict['approx_segments']
      del file_dict['line_segments']
      if 'growth' in file_dict: self.growth_dspinbox.setValue(file_dict['growth'])
      self.grid.width_spinbox.setValue(grid[0])
      self.grid.height_spinbox.setValue(grid[1])
      self.grid.set_visible_checkbox.setChecked(grid[2])
      self.start_point=start_point
      try: self.cropped_rect=cropped_rect
      except NameError: pass
      self.image_library.clear()
      for pixmap in pixmaps:
	self.image_library.AddImage(QFileInfo(QFileInfo(file_path).dir().path()+"/"+self.trUtf8(pixmap[1])).absoluteFilePath(),pixmap[0])
      for knot in knots: Knot(knot[1][0],knot[1][1]).rename(knot[0])
      if len(knots)>0:
	gknots=GeometricObject.objects[self.trUtf8("Узел")]
	for line_segment in line_segments: LineSegment(gknots[line_segment[1][0]],gknots[line_segment[1][1]]).rename(line_segment[0])
	for approx_segment_lst,segment_class in (approx_segments,ApproximationSegment),(polar_approx_segments,PolarApproximationSegment):
	  for approx_segment in approx_segment_lst:
	    l=[]
	    
	    if segment_class is PolarApproximationSegment:
	      s=segment_class(gknots[approx_segment[1][0]],gknots[approx_segment[1][1]])
	      s.setAngles(approx_segment[3][0],approx_segment[3][1],len(approx_segment[2]),approx_segment[3][2])
	    else: 
	      s=segment_class()
	      s.setKnots(gknots[approx_segment[1][0]],gknots[approx_segment[1][1]])
	    for p in approx_segment[2]: s.addPoint(p[0],p[1])
	    s.rename(approx_segment[0])
      self.last_saved_file=file_path
    
    def updateAll(self):
      self.grid.Update()
      GeometricObject.updateAll()
    
    def zoomIn(self):
      self.graphics_view.scale(1.1,1.1)
    
    def zoomOut(self):
      self.graphics_view.scale(0.9,0.9)
    
    def setCurrentTool(self,checked):
      if checked: 
	if not self.current_tool is None: self.current_tool.setChecked(False)
	self.current_tool=self.sender()
      else:
	if not self.current_segment is None: 
	  GeometricObject.removeObject(self.current_segment)
	  self.current_segment=None
	for knot in self.selected_knots: knot.setColor(QColor(0,0,0))
	self.selected_knots=[]
	self.current_tool=None
	self.helper_line.setLine(QLineF())
	  
    def GraphicsViewMousePressed(self,event):
      obj=None
      pressed_point=self.graphics_view.mapToScene(event.pos())
      current_grid_tool=None
      current_segment_class=None
      if self.current_tool is Knot.creationButton:
	obj=Knot(pressed_point.x(),pressed_point.y())
	self.current_tool.setChecked(False)
      elif self.current_tool is self.status_bar_button1: 
	self.start_point=[pressed_point.x(),pressed_point.y()]
	self.current_tool.setChecked(False)
      elif self.current_tool is LineSegment.creationButton: current_segment_class=LineSegment
      elif self.current_tool is ApproximationSegment.creationButton: current_segment_class=ApproximationSegment
      elif self.current_tool is self.grid.set_width_button or self.current_tool is self.grid.set_height_button: current_grid_tool=self.current_tool
      elif self.current_tool is PolarApproximationSegment.creationButton: 
	if len(self.selected_knots)<2:
	  knot=Knot.knotByPoint(pressed_point.x(),pressed_point.y())
	  if not knot is None: 
	    self.selected_knots.append(knot)
	    knot.setColor(QColor(255,0,0))
	if len(self.selected_knots)==2:
	  if self.current_segment is None: 
	    self.current_segment=PolarApproximationSegment(self.selected_knots[0],self.selected_knots[1])
	    self.current_segment.setAngles()
	  elif len(self.current_segment.points)<self.current_segment.count:
	    if self.current_segment.horizontal is True:
	      cur_x=pressed_point.x()
	      cur_y=self.current_segment.knot1.y+float(len(self.current_segment.points)+1)*(self.current_segment.knot2.y-self.current_segment.knot1.y)/float(self.current_segment.count+1)
	    else:
	      cur_x=self.current_segment.knot1.x+float(len(self.current_segment.points)+1)*(self.current_segment.knot2.x-self.current_segment.knot1.x)/float(self.current_segment.count+1)
	      cur_y=pressed_point.y()
	    self.current_segment.addPoint(cur_x,cur_y)
	  if self.current_segment.horizontal is True:
	    cur_y=self.current_segment.knot1.y+float(len(self.current_segment.points)+1)*(self.current_segment.knot2.y-self.current_segment.knot1.y)/float(self.current_segment.count+1)
	    self.helper_line.setLine(QLineF(self.current_segment.knot1.x,cur_y,self.current_segment.knot2.x,cur_y))
	  else:
	    cur_x=self.current_segment.knot1.x+float(len(self.current_segment.points)+1)*(self.current_segment.knot2.x-self.current_segment.knot1.x)/float(self.current_segment.count+1)
	    self.helper_line.setLine(QLineF(cur_x,self.current_segment.knot1.y,cur_x,self.current_segment.knot2.y))
	  if len(self.current_segment.points)==self.current_segment.count: 
	    obj=self.current_segment
	    self.current_segment=None
	    self.current_tool.setChecked(False)
	    
      elif (not GeometricObject.selected is None) and (GeometricObject.selected.type_name==self.trUtf8("Сегмент")):
	knot=Knot.knotByPoint(pressed_point.x(),pressed_point.y())
	if knot is None: GeometricObject.selected.addPoint(pressed_point.x(),pressed_point.y())
      
      if not current_segment_class is None:
	if current_segment_class is ApproximationSegment and self.current_segment is None: self.current_segment=ApproximationSegment()
	if len(self.selected_knots)<2:
	  knot=Knot.knotByPoint(pressed_point.x(),pressed_point.y())
	  if not knot is None: 
	    self.selected_knots.append(knot)
	    knot.setColor(QColor(255,0,0))
	  elif current_segment_class is ApproximationSegment:
	    self.current_segment.addPoint(pressed_point.x(),pressed_point.y())
	if len(self.selected_knots)==2: 
	  if current_segment_class is LineSegment: 
	    obj=segment=current_segment_class(self.selected_knots[0],self.selected_knots[1])
	  elif current_segment_class is ApproximationSegment:
	    self.current_segment.setKnots(self.selected_knots[0],self.selected_knots[1])
	    obj=self.current_segment
	    self.current_segment=None
	  self.current_tool.setChecked(False)
	  
      elif not current_grid_tool is None:
	self.selected_points.append(pressed_point)
	if len(self.selected_points)==2:
	  noc,ok=QInputDialog.getInt(self, self.trUtf8("Размерность сетки"),self.trUtf8("Количество клеток"), 1, 0, 100000, 1)
	  if ok: 
	    if current_grid_tool==self.grid.set_width_button: self.grid.width_spinbox.setValue(round(abs(self.selected_points[1].x()-self.selected_points[0].x())/noc))
	    else: self.grid.height_spinbox.setValue(round(abs(self.selected_points[1].y()-self.selected_points[0].y())/noc))
	  self.selected_points=[]
	  self.current_tool.setChecked(False)
      if not obj is None: obj.rename()
	  
	
    def GraphicsViewMouseMoved(self,event):
      point=self.graphics_view.mapToScene(event.pos())
      p=point
      x=p.x()
      y=p.y()    
      self.status_bar_message1.setText( self.trUtf8("Курсор: ")+
					str(int((x-self.start_point[0])/self.grid.width_spinbox.value()))+
					self.trUtf8(" кл., ")+
					str(int((y-self.start_point[1])/self.grid.height_spinbox.value()))+self.trUtf8(" кл.")
				      )
     
a = QApplication(sys.argv)
 
w = MainWindow()
 
w.resize(320, 240)  # изменить размеры виджета
w.setWindowState(Qt.WindowMaximized)
w.setWindowTitle("")  # установить заголовок
w.show()  # отобразить окно на экране
sys.exit(a.exec_())
