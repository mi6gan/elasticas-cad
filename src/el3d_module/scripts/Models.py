# -*- coding: utf-8 -*-
import ModelDataGenerator as MDG
import PyEl3d
from math import *
GetI=PyEl3d.GetCommonVariableValueI
Getf=PyEl3d.GetCommonVariableValuef
Getb=PyEl3d.GetCommonVariableValueb
GetS=PyEl3d.GetCommonVariableValueS
class Basic(MDG.Basic):
  def __init__(self,filename=None):
    MDG.Basic.__init__(self)
    if not filename is None: self.initFromFile(filename)
    self.prefix=self.__class__.__name__
    
  
  def update(self):
    self.clearPolylines()
    self.iters=5
    dm=self.descrete_models[self.__class__.__name__]=self.generateDescreteModel()
    dm.generatePyEl3dModel()
    dm.pyel3d_model.SaveTo3DS("Man.3ds")
  
  def initFromFile(self,filename):
    exec open(filename,"r")
    self.segments,self.knots_table,self.surfaces,self.super_knots,self.variables,self.external_vars=segments,knots,surfaces,super_knots,variables,external_vars
    try: self.version=version
    except NameError: self.version=0.01  
    
class Man(Basic):
  def __init__(self): 
    Basic.__init__(self,"models/Man")
    self.iters=5
    self.original_super_knots=self.super_knots
    self.alt_super_knots=dict(self.super_knots)
    self.hide_polylines=False
    for key in "14t", "15t", "4s''", "1r'", "2r'", "13t", "8r'", "6r", "7t", "12t",  "11r", "5r", "9t", "10t", "7r'", "1s", "1r", "3r'", "2r", "11t", "3s", "3r", "2''r", "2s", "4r", "4s", "9r'", "3s''", "10r'", "2g", "8t", "5t", "6t", "14t_0", "3g", "4t":
      self.alt_super_knots[key]=["PyEl3d.GetCommonVariableValuef(\"Man:"+key+"_x\")","PyEl3d.GetCommonVariableValuef(\"Man:"+key+"_y\")","PyEl3d.GetCommonVariableValuef(\"Man:"+key+"_z\")",1,1,1] 


  def update(self):
    '''
    fake1=Getf("Man:fake1")
    fake2=Getf("Man:fake2")
    fake3=Getf("Man:fake3")
    man=PyEl3d.Model("Man")
    man.Clear()
    if fake1==178.0: man.LoadFrom3DS("models/man1.3ds")
    elif fake1==186.0: man.LoadFrom3DS("models/man2.3ds")
    elif fake1==178.5: man.LoadFrom3DS("models/man3.3ds")
    return
    '''
    if Getb("Man:UseDebugRP")==1:
      self.dm_displacement=[0,0,-Getf('Man:13t_z')]
      self.knots_i=-1
      self.super_knots=self.alt_super_knots
    else:
      self.knots_i=GetI("ManId")
      self.dm_displacement=[0,0,-self.knots_table[self.knots_i]['13t'][2]]
      self.super_knots=self.original_super_knots
    
    Basic.update(self)
    #self.generateDebugObjects(generate_dirs=False)
  

class Woman(Basic):
  def __init__(self): 
    Basic.__init__(self,"models/Woman")
    self.iters=5
    self.original_super_knots=self.super_knots
    self.alt_super_knots=dict(self.super_knots)
    for key in "1g", "1r", "1r'", "1s", "2''r", "2g", "2r", "2r'", "2s", "3g", "3r", "3r'", "3s", "3s''", \
	       "4r", "4s", "4s''", "4t", "5r", "5t", "6r", "6t", "7r'", "7t", "8r'", "8t", "9r'", "9t", \
	       "10r'", "10t", "11r", "11t", "12t", "13t", "14t", "15t":
		 self.alt_super_knots[key]=["PyEl3d.GetCommonVariableValuef(\"Woman:"+key+"_x\")","PyEl3d.GetCommonVariableValuef(\"Woman:"+key+"_y\")","PyEl3d.GetCommonVariableValuef(\"Woman:"+key+"_z\")",1,1,1]
	       #print key+":"+str(self.alt_super_knots[key])
    
  def update(self):
    if Getb("Woman:UseDebugRP")==1:
      self.dm_displacement=[0,0,-Getf('Woman:13t_z')]
      self.knots_i=-1
      self.super_knots=self.alt_super_knots
    else: 
      self.knots_i=0
      self.dm_displacement=[0,0,-self.knots_table[self.knots_i]['13t'][2]]
      self.super_knots=self.original_super_knots
    Basic.update(self)
    #self.generateDebugObjects()
    #self.descrete_models[self.__class__.__name__].pyel3d_model.SaveTo3DS("Woman.3ds")
    

'''   
class StraightSkirt(Woman):
  def __init__(self):
    exec open("models/StraightSkirt","r")
    self.segments,self.knots_table,self.surfaces,self.super_knots,self.variables_=segments,knots,surfaces,super_knots,variables
    try: self.version=version
    except NameError: self.version=0.01
    self.knots_i=-1
  def update(self):
    Woman.update(self)
    self.variables['L']=PyEl3d.GetCommonVariableValuef("StraightSkirt:A1")

class Jacket(MDG.Basic):
  def __init__(self):
    exec open("models/MensJacket","r")
    self.segments,self.knots_table,self.surfaces,self.super_knots,self.variables=segments,knots,surfaces,super_knots,variables
    try: self.version=version
    except NameError: self.version=0.01
  def update(self):
    self.knots_i=PyEl3d.GetCommonVariableValueI("Dummy:ManId")
    self.dm_displacement=[0,0,-self.knots_table[self.knots_i]['1'][2]]
  def generateDescreteModel(self,closed,i_iters,j_iters): return self.generateDescreteModelNew(closed,i_iters)
'''

class Dress(Basic):
  def __init__(self):
    Basic.__init__(self)
    self.iters=5
    self.prefix="Dress:"
  
  def generateBlouseGridElements(self):

      
      
    if Getb(self.prefix+"GoresOn"):
      p0_x=(self.knots["4s''"][0]+self.knots["1r"][0])/2.0;p0_z=(self.knots["4s''"][2]+self.knots["1r"][2])/2.0
      p1_x=self.knots["2g_0"][0]/2.0;p1_z=self.knots["2g_0"][2]/2.0
      
      plist=self.pointListFromProjectionOnGrid([0,0,0],[0.0,self.knots['2g'][1],0],['o','a','b','c','d','e'],
						       lambda t:(1.0-t)*p0_x+t*p1_x,
						       lambda t: (1.0-t)*p0_z+t*p1_z)
      self.addPolyline("left_top_gore",plist,color=[1.0,1.0,1.0],normal=[0.0,-1.0,0.0],width=3.0)
      for p in plist: p[0]=-p[0]
      self.addPolyline("right_top_gore",plist,color=[1.0,1.0,1.0],normal=[0.0,-1.0,0.0],width=3.0)
      
      plist=self.pointListFromProjectionOnGrid([0,0,0],[0.0,self.knots['2g'][1],0],['h','i','j','k'],
						       lambda t:self.knots["2g_0"][0],
						       lambda t: self.knots["2g_0"][2]*(1.0-t)+(self.knots["5t"][2]-1.0)*t,accuracy=0.01)
      self.addPolyline("left_middle_gore",plist,color=[1.0,1.0,1.0],normal=[0.0,-1.0,0.0],width=3.0)
      for p in plist: p[0]=-p[0]
      self.addPolyline("right_middle_gore",plist,color=[1.0,1.0,1.0],normal=[0.0,-1.0,0.0],width=3.0)
      plist=self.pointListFromProjectionOnGrid([0,0,0],[0.0,self.knots['2g'][1],0],['h','i','j','k'],
						       lambda t:self.knots["2g_0"][0],
						       lambda t: self.knots["2g_0"][2]*(1.0-t)+(self.knots["5t"][2]-1.0)*t)
						       
      plist=self.pointListFromProjectionOnGrid([0,0,0],[0.0,self.knots['2g'][1],0],['r','ab','bb','cb'],
						       lambda t:p0_x,
						       lambda t: (1.0-t)*p0_z+self.knots["8t"][2]*t,accuracy=0.01)      
      self.addPolyline("left_top_gore_b",plist,color=[1.0,1.0,1.0],normal=[0.0,1.0,0.0],width=3.0)
      
      plist=self.pointListFromProjectionOnGrid([0,0,0],[0.0,self.knots['2g'][1],0],['fb','db','eb','gb','hb','ib','nb','jb','kb','ob','lb','mb','pb'],
						       lambda t:p0_x*(1-t)+self.knots['10t_7'][0]*t,
						       lambda t: self.knots["2g_0"][2]*(1.0-t)+(self.knots["5t"][2]-2.0)*t,accuracy=0.01)      
      
      self.addPolyline("left_middle_gore_b",plist,color=[1.0,1.0,1.0],normal=[0.0,1.0,0.0],width=3.0)      
      
    elif "left_top_gore" in self.polylines: 
      self.polylines["left_top_gore"].Clear(); self.polylines["right_top_gore"].Clear()
      self.polylines["left_middle_gore"].Clear(); self.polylines["right_middle_gore"].Clear()
    if GetI(self.prefix+"vorot_type")==1:
      plist=self.pointListFromSegment("4s''-4s_0")+self.pointListFromSegment("4s_0-4s")
      for p in plist: p[1]+=0.1; p[2]+=0.1
      self.addPolyline("vorot_back_left",plist,color=[1.0,1.0,1.0],normal=[0.0,1.0,0.0],width=3.0)
      for p in plist: p[0]=-p[0]
      self.addPolyline("vorot_back_right",plist,color=[1.0,1.0,1.0],normal=[0.0,1.0,0.0],width=3.0)      
      plist=self.pointListFromSegment("4s''-2s_0")+self.pointListFromSegment("2s_0-2s")
      for p in plist: p[1]-=0.1; p[2]+=0.1
      self.addPolyline("vorot_front_left",plist,color=[1.0,1.0,1.0],normal=[0.0,-1.0,0.0],width=3.0)
      for p in plist: p[0]=-p[0]
      self.addPolyline("vorot_front_right",plist,color=[1.0,1.0,1.0],normal=[0.0,-1.0,0.0],width=3.0)

    elif "vorot_back_left" in self.polylines:
      self.polylines["vorot_back_left"].Clear(); self.polylines["vorot_back_right"].Clear()
      self.polylines["vorot_front_left"].Clear(); self.polylines["vorot_front_right"].Clear()
    '''  
    for key in "4r-7r'","5r-7r'","5r-8r'","4r-8r'":
      plist=self.pointListFromSegment(key)
      self.addPolyline(key,plist,color=[1.0,1.0,1.0],normal=[0.0,1.0,0.0],width=3.0)
      for p in plist: p[0]=-p[0]
      self.addPolyline(key+"_m",plist,color=[1.0,1.0,1.0],normal=[0.0,1.0,0.0],width=3.0)
    '''
    
  def update(self):
    '''
    woman=PyEl3d.Model("Dress")
    woman.Clear()
    dress_3ds=GetS("dress_3ds")
    dress_png=GetS("dress_png")
    woman.LoadFrom3DS(dress_3ds)
    woman.SetTexture(dress_png)
    return
    '''
    self.initFromFile("models/Dress"+str(GetI(self.prefix+"SilhouetteType")))
    self.knots_i=0 
    #for name in 'Sm3','d1gp','Length': self.variables[name]=str(PyEl3d.GetCommonVariableValuef(self.prefix+name))
    # Fake------------------
    '''
    for name in "A3","A3_","A5","A5_","A6","A6_","A4","Narrow": 
      self.external_vars.remove(name)
      self.variables[name]="0.0"
    self.variables["Narrow"]="True"
    if GetI(self.prefix+"Form")<>0:
      if Getf(self.prefix+"kpn")==1.25: self.variables["A3_"]=self.variables["A5_"]=self.variables["A6_"]="-2.0"
      elif Getf(self.prefix+"kpn")==1.5: self.variables["A3_"]=self.variables["A5_"]=self.variables["A6_"]="-3.0"
      elif Getf(self.prefix+"kpn")==1.75: self.variables["A3_"]=self.variables["A5_"]=self.variables["A6_"]="-5.0"
    if(Getf(self.prefix+"Length2")>40.0): self.variables["A4"]="15.0"
    else: self.variables["A4"]="6.0"
    
    if Getb(self.prefix+"is_vorot"):
      self.external_vars.remove("Rg1")
      if Getf(self.prefix+"c_0_nsp")>2.0: self.variables["Rg1"]="3.0"
      else: self.variables["Rg1"]="3.0"
      
    self.dm_displacement=self.bearing_model.dm_displacement
    
    sleeve=PyEl3d.Model("Sleeve")
    sleeve.Clear()
    if Getb(self.prefix+"Sleeve") and GetI(self.prefix+"SleeveForm")==3:
      if(Getb(self.prefix+"CuffsOn")): sleeve.LoadFrom3DS("Sleeve3.3ds")
      elif(Getf(self.prefix+"SleeveLength")>20.0): sleeve.LoadFrom3DS("Sleeve1.3ds")
      else: sleeve.LoadFrom3DS("Sleeve2.3ds")
      self.external_vars.remove("Sleeve")
      self.variables["Sleeve"]="False"
      
    Basic.update(self)
    
    sleeve.SetTexture("/home/mi6gan/tmp/clothes/fake/4.png");
    if GetI(self.prefix+"z1")==0: self.descrete_models[self.__class__.__name__].pyel3d_model.SetTexture("/home/mi6gan/tmp/clothes/fake/0.png");
    else: self.descrete_models[self.__class__.__name__].pyel3d_model.SetTexture("/home/mi6gan/tmp/clothes/fake/1.png")
    
    
    for key in "15t_0-12t_7","12t_7-12t_6","12t_6-12t_0","15t_0-7t_5","7t_5-7t_4","7t_4-7t":
      plist=self.pointListFromSegment(key)
      if GetI(self.prefix+"tmp2")>0.0:
	self.addPolyline(key,plist,color=[1.0,1.0,1.0],normal=[0.0,1.0,0.0],width=3.0)
	for p in plist: p[0]=-p[0]
	self.addPolyline(key+"_m",plist,color=[1.0,1.0,1.0],normal=[0.0,1.0,0.0],width=3.0)
      else:
	if key in self.polylines: self.polylines[key].Clear()
	if key+"_m" in self.polylines: self.polylines[key+"_m"].Clear()
    '''
    # Fake----------------
    
    self.dm_displacement=self.bearing_model.dm_displacement
    Basic.update(self)
    
    if GetI(self.prefix+"GoresOn")==1:
      plist=self.pointListFromProjectionOnGrid([0,0,0],[0.0,self.knots['2g'][1],0],['a1_s','a2_s','b1_s','b2_s','c1_s','c2_s','d1_s','d2_s'],
						       lambda t:self.knots["2g_0"][0]+2.0*t,
						       lambda t: self.knots["5t"][2]*(1.0-t)+(self.knots["6t"][2])*t,accuracy=0.01)
      self.addPolyline("left_bottom_gore",plist,color=[1.0,1.0,1.0],normal=[0.0,-1.0,0.0],width=3.0)
      for p in plist: p[0]=-p[0]
      self.addPolyline("right_bottom_gore",plist,color=[1.0,1.0,1.0],normal=[0.0,-1.0,0.0],width=3.0)
      plist=self.pointListFromProjectionOnGrid([0,0,0],[0.0,self.knots['2g'][1],0],['ab0_s','ab1_s','ab2_s','bb0_s','bb1_s','bb2_s','cb0_s','cb1_s','cb2_s','db0_s','db1_s','db2_s'],
						       lambda t:self.knots['10t_7'][0]+2.0*t,
						       lambda t: (self.knots["5t"][2]+2.0)*(1.0-t)+(self.knots["6t"][2])*t,accuracy=0.01)      
      self.addPolyline("left_bottom_gore_b",plist,color=[1.0,1.0,1.0],normal=[0.0,1.0,0.0],width=3.0)
    elif "left_bottom_gore" in self.polylines:
      self.polylines["left_bottom_gore"].Clear(); self.polylines["right_bottom_gore"].Clear()
    '''        
    if PyEl3d.GetCommonVariableValueI(self.prefix+"VP")==1: 
      plist=self.pointListFromProjectionOnGrid([0,0,0],[0.0,self.knots['2g'][1],0],['o','a','d','f','h','j','a2_s','b2_s','c2_s','d2_s'],lambda t: t,lambda t: self.knots['1s'][2]*(1.0-t)+(self.knots['7t'][2]-1.0)*t)
      self.addPolyline("front_sew",plist,color=[1.0,1.0,1.0],normal=[0.0,-1.0,0.0],width=2.0)
    elif "front_sew" in self.polylines: self.polylines["front_sew"].Clear()
    if PyEl3d.GetCommonVariableValueI(self.prefix+"VZ")==1: 
      plist=self.pointListFromProjectionOnGrid([0,0,0],[0,1,0],['r','ab','db','fb','hb','jb','lb','ab2_s','bb2_s','cb2_s','db2_s'],lambda t: -t,lambda t: self.knots['3s'][2]*(1.0-t)+(self.knots['7t'][2]-1.0)*t)
      self.addPolyline("back_sew",plist,color=[1.0,1.0,1.0],normal=[0.0,1.0,0.0],width=2.0)
    elif "back_sew" in self.polylines: self.polylines["back_sew"].Clear()
    '''
    if False: #GetI(self.prefix+"z1")==1:
      z2=GetI(self.prefix+"z2")
      z3=GetI(self.prefix+"z3")
      if z3==0:
	Sm3=Getf(self.prefix+"Sm3")
	snames=['b','a','c','d','e','f','g','h','i','j','k','a2_s','b2_s','c2_s','d2_s']
	if z2==1: ['o','p']+snames
	if Sm3>0.0: 
	  p=self.pointOnBearingSpline(snames=["2s_0-2s","4s''-2s_0"],dis=Sm3,model=self,is_inv_list=[True,True])
	  plist=[p]+self.pointListFromProjectionOnGrid([0,0,0],[0.0,p[1],0],snames,lambda t: p[0],lambda t: self.knots['1s'][2]*(1.0-t)+(self.knots['7t'][2]-1.0)*t)
	else:
	  for i in range(len(snames)): snames[i]+="_m"
	  p=self.pointOnBearingSpline(snames=["2s_0-2s_m","4s''-2s_0_m"],dis=abs(Sm3),model=self,is_inv_list=[True,True])
	  plist=[p]+self.pointListFromProjectionOnGrid([0,0,0],[0.0,p[1],0],snames,lambda t: p[0],lambda t: self.knots['1s'][2]*(1.0-t)+(self.knots['7t'][2]-1.0)*t)
	self.addPolyline("clasp",plist,color=[0.8,0.8,0.8],normal=[0.0,-1.0,0.0],width=3.0)
      elif z3==2:
	plist=self.pointListFromSegment("4s''-1r")
	if z2==1 and GetI(self.prefix+"is_vorot")==1: plist+=self.pointListFromSegment("3s''-4s''")
	for p in plist: p[2]+=0.0
	self.addPolyline("left_clasp",plist,color=[0.8,0.8,0.8],normal=[0.0,-1.0,0.0],width=3.0)
	for p in plist: p[0]=-p[0]
	self.addPolyline("right_clasp",plist,color=[0.8,0.8,0.8],normal=[0.0,-1.0,0.0],width=3.0)
      self.addPolyline("debug_polyline",[p,[p[0],p[1],p[2]-2.0]],width=2.0)
    else:
      if "clasp" in self.polylines: self.polylines["clasp"].Clear()
      if "left_clasp" in self.polylines: 
	self.polylines["left_clasp"].Clear()
	self.polylines["right_clasp"].Clear()
    self.generateBlouseGridElements()
    self.descrete_models[self.__class__.__name__].pyel3d_model.SaveTo3DS("Dress.3ds")
    

class StraightSkirt(Dress):
  def __init__(self):
    Basic.__init__(self,"models/Skirt")
    self.prefix="StraightSkirt:"

  def update(self):
    self.knots_i=0
    self.dm_displacement=self.bearing_model.dm_displacement
    self.descrete_models[self.__class__.__name__]=dm=self.generateDescreteModel()
    dm.generateCylindricalTextureUVs(radius=abs(self.knots["14t"][0]),bottom=self.knots["5t_"][2]-self.dm_displacement[2],top=self.knots["7t"][2]-self.dm_displacement[2],ufactor=1.0,vfactor=1.0)
    Basic.update(self)
    
    if PyEl3d.GetCommonVariableValueI(self.prefix+"VP")==1: 
      plist=self.pointListFromProjectionOnGrid([0,0,0],[0.0,self.knots['5t'][1],0],['a','b','c','d'],lambda t: 0.0,lambda t: self.knots['5t'][2]*(1.0-t)+self.knots['7t'][2]*t)
      self.addPolyline("front_sew",plist+[[plist[-1][0],plist[-1][1],self.knots['7t'][2]]])
    elif "front_sew" in self.polylines: self.polylines["front_sew"].Clear()
    
    if PyEl3d.GetCommonVariableValueI(self.prefix+"VZ")==1: 
      plist=self.pointListFromProjectionOnGrid([0,0,0],[0.0,self.knots['11t'][1],0],['ab','bb','cb','db'],lambda t: 0.0,lambda t: self.knots['5t'][2]*(1.0-t)+self.knots['7t'][2]*t)
      self.addPolyline("back_sew",plist+[[plist[-1][0],plist[-1][1],self.knots['7t'][2]]])
    elif "back_sew" in self.polylines: self.polylines["back_sew"].Clear()
    
    A2=PyEl3d.GetCommonVariableValuef(self.prefix+"A2")
    if A2>0.0: p=self.pointOnBearingSpline(["14t-11t"],A2,model=self)
    else: p=self.pointOnBearingSpline(["14t-5t"],abs(A2),model=self)    
    if PyEl3d.GetCommonVariableValueI(self.prefix+"VB")==1: 
      plist=self.pointListFromProjectionOnGrid([0,0,0],[p[0],p[1],0],['a','ab','b','bb','c','cb','d','db'],lambda t: 0.0,lambda t: self.knots['5t'][2]*(1.0-t)+(self.knots['7t'][2]-1.0)*t)
      #plist=plist+[[plist[-1][0],plist[-1][1],self.knots['7t'][2]]]
      self.addPolyline("left_sew",plist)
      for p in plist: p[0]=-p[0]
      self.addPolyline("right_sew",plist)
    elif "left_sew" in self.polylines: 
      self.polylines["left_sew"].Clear()
      self.polylines["right_sew"].Clear()
    
    '''
    if PyEl3d.GetCommonVariableValueI("StraightSkirt:VB")==1: self.polylineFromProjectionOnGrid("right_sew",[0,0,0],[self.knots['14t_m'][0],0,0],['a_m','b_m','c_m'],lambda t: 0.0,lambda t: self.knots['5t'][2]*(1.0-t)+self.knots['7t'][2]*t)
    elif "right_sew" in self.polylines: self.polylines["right_sew"].Clear()
    '''
    #self.pyel3d_model.SetTexture("images/texture0.png")
    
    
class Blouse(Dress):
  def __init__(self): 
    Dress.__init__(self)
    self.iters=5
    self.prefix="Blouse:"

      
  def update(self):
    self.initFromFile("models/Blouse"+str(GetI(self.prefix+"SilhouetteType")))
    self.knots_i=0
    self.dm_displacement=self.bearing_model.dm_displacement
    #self.iters=30
    Basic.update(self)
    #self.generateBlouseGridElements()
    #self.generateBlouseGridElements()
    #self.pyel3d_model.SetTexture("images/texture0.png")
    #self.generateDebugObjects()
    '''
    fxyz="p0*((1-t)**3)+p0*3*t*((1-t)**2)+p1*3*(t**2)*(1-t)+(t**3)*p1"
    ft=[fxyz]*3
    l=10.0
    C=["p0","p0","p1","p1"]
    knot_4s___z=self.computed_vars["knot_4s___z"]
    knot_2g_0_y=self.computed_vars["knot_2g_0_y"]
    self.prism=MDG.Prism([ft,ft,ft,ft],[[-10,0,knot_4s___z],[0,0,knot_4s___z],[10,0,knot_4s___z],[0,0,knot_4s___z-10]],[C,C,C,C],[0,knot_2g_0_y,0],False)
    self.prism.dm_displacement=self.dm_displacement
    #self.prism_=MDG.Prism(ft,ft,ft,ft,[0,0,-l],[10,0,-l],[10,10,-l],[0,10,-l],[0,0,2.0*l],True)
    self.prism.generateDescreteModel()
    #self.prism_.generateDescreteModel()
    #self.dm=self.dm.difference(self.prism.dm)
    
    #self.generateDescreteModel()
    #self.dm=self.prism.dm
    self.dm._vertices,self.dm._indices=PyEl3d.CSGIntersection(self.dm._vertices,self.dm._indices,self.prism.dm._vertices,self.prism.dm._indices)
    self.dm._generateNormals()
    self.generate_dm=False
    Basic.update(self)    
    
    
    self.dm=self.dm.intersection(self.prism.dm)
    self.dm._generateNormals()
    self.generate_dm=False
    Basic.update(self)
    
    
    
    self.dm.generateGTSSurface()
    self.dm=MDG.Basic.DescreteModel(self.dm.gts_surface)
    self.dm._generateNormals()
    self.generate_dm=False
    Basic.update(self)
    '''
    #print "Blouse ---------------",self.knots["4s\'\'"],self.knots["4s"]
class Cloud(Basic):
  def __init__(self): 
    Basic.__init__(self)
    self.prefix="Cloud:"
    self.pyel3d_models=[]

  def setVisiblity(self,visible): 
    for pyel3d_model in self.pyel3d_models: pyel3d_model.SetVisiblity(visible)
  
  def update(self):
    self.pyel3d_models=[]
    lines=open("pic.3d","r")
    points=[]
    min_point=None
    max_point=None
    for line in lines:
      points.append([])
      word=""
      for symbol in line:
	if symbol==" " or symbol==line[-1]:
	  points[-1].append(float(word))
	  word=""
	else: word+=symbol
      points[-1][1],points[-1][0],points[-1][2]=-points[-1][0],points[-1][1],-points[-1][2]
      if min_point is None: min_point=points[-1][:]
      else:
	for i in range(3):
	  if min_point[i]>points[-1][i]: min_point[i]=points[-1][i]
      if max_point is None: max_point=points[-1][:]
      else:
	for i in range(3):
	  if max_point[i]<points[-1][i]: max_point[i]=points[-1][i]
    for point in points:
      for i in range(3):
	point[i]-=min_point[i]+(max_point[i]-min_point[i])/2.0
	point[i]/=10
      point[1]-=38
      point[2]-=3.5
    
    part=5000
    out=open("cloud.txt","w")
    out.write(str(points))
    out.close()
    for i in range(len(points)/part+1):
      if part*(i+1)<len(points): to=part*(i+1)
      else: to=len(points)
      self.pyel3d_models.append(PyEl3d.Model("Cloud"+str(i)))
      self.pyel3d_models[-1].Clear()
      self.pyel3d_models[-1].SetViewMode(0,1)
      self.pyel3d_models[-1].SetViewMode(1,0)
      self.pyel3d_models[-1].SetViewMode(2,0)
      self.pyel3d_models[-1].SetSurface(points[part*i:to],[[3*j,3*j+1,3*j+2] for j in range((to-part*i)/3)],points,points)
    
	
    
class Jacket(Dress):
  def __init__(self): 
    Dress.__init__(self)
    self.iters=5
    self.prefix="Jacket:"
  
  def update(self):
    '''
    fake1=Getf("Man:fake1")
    fake2=Getf("Man:fake2")
    fake3=Getf("Man:fake3")
    fake1_=Getf("Jacket:fake1")
    fake2_=Getf("Jacket:fake2")
    jacket=PyEl3d.Model("Jacket")
    jacket.Clear()
    if fake1==178.0: jacket.LoadFrom3DS("models/jacket1.3ds")
    elif fake1==186.0:
      jacket.LoadFrom3DS("models/jacket2.3ds")
      jacket.SetTexture("images/jacket2.png")
    elif fake1==178.5: 
      if fake1_: 
	jacket.LoadFrom3DS("models/jacket3_1.3ds")
	if fake2_: jacket.SetTexture("images/jacket3_2.png")
	else: jacket.SetTexture("images/jacket3_1.png")
      else:
	jacket.LoadFrom3DS("models/jacket3.3ds")
	jacket.SetTexture("images/jacket3.png")
      
    return
    '''
    
    self.initFromFile("models/MensJacket"+str(GetI(self.prefix+"SilhouetteType")))
    self.knots_i=0
    self.dm_displacement=self.bearing_model.dm_displacement
    self.clearPolylines()
    dm=self.generateDescreteModel()
    #self.generateDebugObjects()

    
    '''
    dm._generateNormals()
    dm.generatePyEl3dModel()
    Jd=1.5
    Jf=[-3,18]
    Jg=[self.knots["4s''"][0]+1.0,Jf[1]/2.0]
    p0x=Jf[0]; p1x=self.knots["4s''"][0]
    p0y=self.knots["4s''"][2]-Jf[1]; p1y=self.knots["4s''"][2]
    Jo=[0, (p0x*p1y - p0y*p1x)/(p0x - p1x)]
    Ji=[Jf[0]+(self.knots["4s''"][0]-Jf[0])/2.0, 
        self.knots["2g"][1]+(self.knots["4s''"][1]-self.knots["2g"][1])/2.0,
        (self.knots["4s''"][2]-Jf[1])+((self.knots["4s''"][2]+Jd)-(self.knots["4s''"][2]-Jf[1]))/2.0]
    
    for sname in "4s''-4s_0","4s_0-4s":
      pls=self.pointListFromSegment(sname)
      self.addPolyline(sname,pls)
      pls=[[pl[0],pl[1],pl[2]+Jd] for pl in pls]
      self.addPolyline(sname+"_up",pls)
    self.addPolyline("je-jf",[self.knots["4s''"],[Jf[0],self.knots["2g"][1],self.knots["4s''"][2]-Jf[1]]])
    self.addPolyline("je-jf_up",[[self.knots["4s''"][0],self.knots["4s''"][1],self.knots["4s''"][2]+Jd],[Jf[0],self.knots["2g"][1],self.knots["4s''"][2]-Jf[1]]])
    self.addPolyline("jg-jf",[[Jg[0],self.knots["2g"][1]/2.0,self.knots["4s''"][2]-Jg[1]],[Jf[0],self.knots["2g"][1],self.knots["4s''"][2]-Jf[1]]])
    self.addPolyline("ji-jg",[Ji,[Jg[0],self.knots["2g"][1]/2.0,self.knots["4s''"][2]-Jg[1]]])
    return
    '''
    fxyz=bezier3_string0=self.Bezier3String("p0","p0","p1","p1")
    el_cx=["p0","p0","p0+(1.8-1.0)*(p1-p0)/1.8","p1"]
    el_cy=["p0","p0+(p1-p0)/1.8","p1","p1"]
    bezier3_string_el_x=self.Bezier3String("p0","p0","p0+(1.8-1.0)*(p1-p0)/1.8","p1")
    bezier3_string_el_y=self.Bezier3String("p0","p0+(p1-p0)/1.8","p1","p1")
    knot_4s_y=self.computed_vars["knot_4s_y"]
    knot_4s_z=self.computed_vars["knot_4s_z"]
    knot_8t_y=self.computed_vars["knot_8t_y"]
    knot_4s___z=self.computed_vars["knot_4s___z"]
    knot_4s___x=self.computed_vars["knot_4s___x"]
    knot_2g_0_y=self.computed_vars["knot_2g_0_y"]
    knot_1r_x=self.computed_vars["knot_1r_x"]
    C=[["p0","p0","p1","p1"]]*3
    ft=[fxyz]*3
    for vname,dvalue in ("l0",knot_4s___x),("l1",1.0),("l2",1.0),("l3",18.0),("l4",5.0),("l5",1.0),("m0",0.8):
      globals()[vname]=Getf("Jacket:"+vname)
      if globals()[vname]==0: globals()[vname]=dvalue

    
    p5=[0.0-l5,0,(knot_4s___z-l3)+(l5)*(-l4-l3)/(l0+l1)]
    
    plane=MDG.Prism([ft,ft,ft,ft],[[l0+l1,0,knot_4s___z-l4],[p5[0],0,p5[2]],[p5[0]+0.1,0,p5[2]],[l0+l1+0.1,0,knot_4s___z-l4]],[C,C,C,C],[0,1.5*knot_2g_0_y,0],True,"Plane")
    plane.dm_displacement=self.dm_displacement
    plane_dm=plane.generateDescreteModel()
    #self.descrete_models["plane_dm"]=plane_dm
    #plane_dm.generatePyEl3dModel()
    temp_dm=dm.intersection(plane_dm,"temp_dm")
    temp_dm.orderCSGSharedEdges()

    def genList0(lim_count=2,rev=False):
      i0=i1=-1
      a_=[]
      count=0
      if rev: it=reversed(temp_dm.csg_shared_edges)
      else: it=temp_dm.csg_shared_edges
      for i2 in it:
	p2=temp_dm._vertices[i2]
	if i0>=0 and i1>=0:
	  p0=temp_dm._vertices[i0]
	  p1=temp_dm._vertices[i1]
	  x0,x1,x2=(p0[0]-p1[0],p0[1]-p1[1],p0[2]-p1[2])
	  y0,y1,y2=(p2[0]-p1[0],p2[1]-p1[1],p2[2]-p1[2])
	  #/sqrt((x0*x0+x1*x1+x2*x2)*((y0*y0+y1*y1+y2*y2)))
	  if (x0*y0+x1*y1+x2*y2)>=0: count+=1
	  print (x0*y0+x1*y1+x2*y2)
	if count==lim_count-1: a_.append([p2[0]-self.dm_displacement[0],p2[2]-self.dm_displacement[1],p2[1]-self.dm_displacement[2]])
	elif count==lim_count: break
	i0=i1; i1=i2
      return a_
    a0=genList0()
    
    
    self.prism=MDG.Prism([ft,ft,ft,ft],[[-l0,0,knot_4s___z],[0,0,knot_4s___z],[l0,0,knot_4s___z],[0.0,0,knot_4s___z-l3]],[C,C,C,C],[0,1.5*knot_2g_0_y,0],False,"Prism")
    self.prism.dm_displacement=self.dm_displacement
    self.descrete_models["prism"]=prism_dm=self.prism.generateDescreteModel()
    
    debug0=PyEl3d.GetCommonVariableValueI("debug0")
    if debug0==3:
      self.descrete_models[self.name]=dm=dm.intersection(prism_dm,dm.name)
    elif debug0==1:
      prism_dm.generatePyEl3dModel()
      self.descrete_models[self.name]=dm
    elif debug0==2:
      prism_dm.generatePyEl3dModel()
      self.descrete_models[self.name]=dm=prism_dm
    elif debug0==0:
      self.descrete_models[self.name]=dm
      #del self.prism
    
      
    
    '''
    dm.orderCSGSharedEdges()
    a1=[]
    for i in dm.csg_shared_edges:
      if dm._vertices[i][0]>=0:
	a1.append([dm._vertices[i][0]-self.dm_displacement[0],dm._vertices[i][2]-0.01-self.dm_displacement[1],dm._vertices[i][1]-self.dm_displacement[2]])    
     
    self.addPolyline("a0_poly",a0)
    self.addPolyline("a1_poly",a1)
    if a0[0][2]>a0[-1][2]: a0.reverse()
    if a1[0][2]>a1[-1][2]: a1.reverse()
    for i in range(len(a0)): a0[i][2]+=m0*i/len(a0)
    for i in range(len(a1)): a1[i][2]+=m0*i/len(a1) 
    
    
    
    p0=[(a1[-1][0]+a0[-1][0])/2.0,0.0,(a1[-1][2]+a0[-1][2])/2.0]
    p1=self.pointOnBearingSpline(snames=["4s-8t"],dis=m0)[:3]
    p2=a1[-1]
    p2[1]=0.0
    p3=self.pointOnBearingSpline(snames=["3s-4s"],dis=m0)[:3]
    #p0[1]=-p0[1];p1[1]=-p1[1];p2[1]=-p2[1];p3[1]=-p3[1]
    
    collar_back=MDG.Basic(knots_table=[{
				  "k0":p0,
				  "k1":p1,
				  "k2":p2,
				  "k3":p3,
				  "k0_":[-p0[0],p0[1],p0[2]],
				  "k2_":[-p2[0],p2[1],p2[2]]
				   }],
		     segments={
				"k0-k2":{"xt":bezier3_string0,"yt":bezier3_string0,"zt":bezier3_string0,"knot0":"k0","knot1":"k2",
					  "Cx":["p0","p0","p1","p1"],"Cy":["p0","p0","p1","p1"],"Cz":["p0","p0","p1","p1"]},
				"k1-k3":{"xt":bezier3_string0,"yt":bezier3_string0,"zt":bezier3_string0,"knot0":"k1","knot1":"k3",
					  "Cx":["p0","p0","p1","p1"],"Cy":["p0","p0","p1","p1"],"Cz":["p0","p0","p1","p1"]},
				"k0_-k2_":{"xt":bezier3_string0,"yt":bezier3_string0,"zt":bezier3_string0,"knot0":"k0_","knot1":"k2_",
					  "Cx":["p0","p0","p1","p1"],"Cy":["p0","p0","p1","p1"],"Cz":["p0","p0","p1","p1"]},
				"k0-k1":{"xt":bezier3_string_el_x,"yt":bezier3_string_el_y,"zt":bezier3_string0,"knot0":"k0","knot1":"k1",
					 "Cx":el_cx, "Cy":el_cy,
					 "Cz":["p0","p0","p1","p1"]},
				"k2-k3":{"xt":bezier3_string_el_x,"yt":bezier3_string_el_y,"zt":bezier3_string0,"knot0":"k2","knot1":"k3",
					 "Cx":el_cx, "Cy":el_cy,
					 "Cz":["p0","p0","p1","p1"]},
				"k0_-k1":{"xt":bezier3_string_el_x,"yt":bezier3_string_el_y,"zt":bezier3_string0,"knot0":"k0_","knot1":"k1",
					 "Cx":el_cx, "Cy":el_cy,
					 "Cz":["p0","p0","p1","p1"]},
				"k2_-k3":{"xt":bezier3_string_el_x,"yt":bezier3_string_el_y,"zt":bezier3_string0,"knot0":"k2_","knot1":"k3",
					 "Cx":el_cx, "Cy":el_cy,
					 "Cz":["p0","p0","p1","p1"]}
			      },
		     surfaces={
			       "A":{"segments":["k0-k2","k0-k1","k1-k3","k2-k3"],"ccw":True},
			       "B":{"segments":["k0_-k2_","k0_-k1","k1-k3","k2_-k3"],"ccw":False}},
		     name="collar_back",
		     dm_displacement=self.dm_displacement)   
    self.descrete_models["collar_back"]=collar_back.generateDescreteModel()
    self.descrete_models["collar_back"].generatePyEl3dModel()


    cs={}; fs={}
    for a,name in (a0,"a0"),(a1,"a1"):#,(a2,"a2"):
      cx,cy,cz=cs[name]=[self.approximateByBezier3([p[0] for p in a]),
			 self.approximateByBezier3([p[1] for p in a]),
			 self.approximateByBezier3([p[2] for p in a])]
      fs[name]=[self.Bezier3String(str(cx[0]),str(cx[1]),str(cx[2]),str(cx[3])),
		self.Bezier3String(str(cy[0]),str(cy[1]),str(cy[2]),str(cy[3])),
		self.Bezier3String(str(cz[0]),str(cz[1]),str(cz[2]),str(cz[3]))]
      l=[]
      for i in range(100):
	t=float(i)/99.0
	l.append([eval(fs[name][0]),eval(fs[name][1]),eval(fs[name][2])])
      # self.addPolyline(name,l,color=[1,0.2,0.2])
    for collar_name,s in ("collar_right",1.0),("collar_left",-1.0):
      collar=MDG.Basic(knots_table=[{
				  "k0":[s*cs["a0"][0][0],cs["a0"][1][0],cs["a0"][2][0]],
				  "k0_":[s*cs["a1"][0][0],cs["a1"][1][0],cs["a1"][2][0]],
				  "k1":[s*cs["a0"][0][-1],cs["a0"][1][-1],cs["a0"][2][-1]],
				  "k1_":[s*cs["a1"][0][-1],cs["a1"][1][-1],cs["a1"][2][-1]]
				   }],
		       segments={
				"k0-k0_":{"xt":bezier3_string0,"yt":bezier3_string0,"zt":bezier3_string0,"knot0":"k0","knot1":"k0_",
					  "Cx":["p0","p0","p1","p1"],"Cy":["p0","p0","p1","p1"],"Cz":["p0","p0","p1","p1"]},
				"k1-k1_":{"xt":bezier3_string0,"yt":bezier3_string0,"zt":bezier3_string0,"knot0":"k1","knot1":"k1_",
					  "Cx":["p0","p0","p1","p1"],"Cy":["p0","p0","p1","p1"],"Cz":["p0","p0","p1","p1"]},
				"k0_-k1_":{"xt":str(s)+"*("+fs["a1"][0]+")","yt":fs["a1"][1],"zt":fs["a1"][2],"knot0":"k0_","knot1":"k1_",
					 "Cx":["p0",str(s*cs["a1"][0][1]),str(s*cs["a1"][0][2]),"p1"],
					 "Cy":["p0",str(cs["a1"][1][1]),str(cs["a1"][1][2]),"p1"],
					 "Cz":["p0",str(cs["a1"][2][1]),str(cs["a1"][2][2]),"p1"]},
				"k0-k1":{"xt":str(s)+"*("+fs["a0"][0]+")","yt":fs["a0"][1],"zt":fs["a0"][2],"knot0":"k0","knot1":"k1",
					 "Cx":["p0",str(s*cs["a0"][0][1]),str(s*cs["a0"][0][2]),"p1"],
					 "Cy":["p0",str(cs["a0"][1][1]),str(cs["a0"][1][2]),"p1"],
					 "Cz":["p0",str(cs["a0"][2][1]),str(cs["a0"][2][2]),"p1"]},
			      },
		     surfaces={"A":{"segments":["k0-k0_","k0_-k1_","k0-k1","k1-k1_"],"ccw":s==1}},
		     name=collar_name,
		     dm_displacement=self.dm_displacement)
      self.descrete_models[collar_name]=collar.generateDescreteModel()
      self.descrete_models[collar_name].generatePyEl3dModel()

    plane=MDG.Prism([ft,ft,ft,ft],[[p5[0],p5[1],p5[2]],[p5[0]-0.1,p5[1],p5[2]],[p5[0]-0.1,p5[1],p5[2]],[l0+l1+0.1,0,knot_4s___z-l4]],[C,C,C,C],[0,1.5*knot_2g_0_y,0],True,"Plane")
    plane.dm_displacement=self.dm_displacement
    plane_dm=plane.generateDescreteModel()
      
    '''
    dm._generateNormals()
    dm.generatePyEl3dModel()
    


class ComplexSkirt(StraightSkirt):
  def __init__(self): 
    StraightSkirt.__init__(self)
    self.prefix="ComplexSkirt:"
    
class ComplexDress(Dress):
  def __init__(self): 
    Dress.__init__(self)
    self.prefix="ComplexDress:"
    
class ComplexBlouse(Blouse):
  def __init__(self): 
    Blouse.__init__(self)
    self.prefix="ComplexBlouse:"
