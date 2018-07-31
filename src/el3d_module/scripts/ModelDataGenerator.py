# -*- coding: utf-8 -*-
from math import *
arccos=acos
import pyel3d_model as pyel3d_model_module
import PyEl3d
import inspect
from random import random
axis_name_to_int={'x': 0, 'y': 1, 'z': 2}
dev_axis_name_to_int={'x': 0, 'y': 2, 'z': 1}
is_debug=(PyEl3d.GetCommonVariableValueI("Debug")>0)

class ParametricError(BaseException):
  def __init__(self,message=""): BaseException.__init__(self,message)

class TopologyError(BaseException):
  def __init__(self,message=""): BaseException.__init__(self,message)

class ParametricUnit(object):
  
  def __init__(self,environment): 
    self.environment=environment
    self.computing=False
    self._computed_value_=None
  
  def _compute_(self): pass
  
  def update(self): self._need_to_compute_=True
  
  def compute(self):
    if self.computing: raise ParametricError(self.value)
    self.computing=True
    if not "_computed_value_" in self.__dict__ or self._need_to_compute_: self._compute_()
    self.computing=False
    self._need_to_compute_=False
    return self._computed_value_

class ParametricScalar(ParametricUnit):
 
  def _compute_(self):
    self.environment["self"]=self
    exec("computed_value="+self.value) in self.environment
    self._computed_value_=self.environment["computed_value"]
    
  def __mul__(self,a): return self.compute()*a
  
  def __rmul__(self,a): return a*self.compute()
  
  def __div__(self,a): return self.compute()/a    
  
  def __rdiv__(self,a): return a/self.compute()
  
  def __add__(self,a):return self.compute()+a    
  
  def __radd__(self,a): return a+self.compute()
  
  def __sub__(self,a): return self.compute()-a    
  
  def __rsub__(self,a): return self.compute()-a
  
  def __pow__(self,a): return self.compute()**a
  
  def __rpow__(self,a): return a**self.compute()
  
  def __str__(self): return str(self.compute())
  
  def __setattr__(self,name,value):
    if name=="value": self._need_to_compute_=True
    object.__setattr__(self,name,value)
  
  def __init__(self,value="0",environment={}):    
    self.value=value
    ParametricUnit.__init__(self,environment)
#---

class ParametricObject(ParametricUnit):
  def __init__(self,environment):
    ParametricUnit.__init__(self,environment)
    self._children_=[]
  
  def __setitem__(self,key,value): 
    if type(value) in (str,float,int): self.environment[key]=ParametricScalar(str(value),self.environment)
    else: self.environment[key]=value
    
  def __getitem__(self,key): return self.environment[key]
  
  def __setattr__(self,name,value):
    ParametricUnit.__setattr__(self,name,value)
    if "_children_" in self.__dict__ and name[0]<>"_": self.update()
  
  def update(self):
    ParametricUnit.update(self)
    for child in self._children_: child.update()
  
#---

class Vector3D(ParametricObject):
  def __init__(self,x,y,z,environment):
    self.x=ParametricScalar(str(x),environment); self.y=ParametricScalar(str(y),environment); self.z=ParametricScalar(str(z),environment)
    ParametricObject.__init__(self,environment)
    
  def __getitem__(self,key):
    if type(key) is int:
      if key==0: return self.x
      if key==1: return self.y
      if key==2: return self.z
    return ParametricObject.__getitem__(self,key)
  
  def update(self):
    self.x.update()
    self.y.update()
    self.z.update()
    ParametricObject.update(self)
#---

class Bezier3Segment(ParametricObject):
  def __init__(self,vector3d_0,vector3d_1,vector3d_2,vector3d_3,environment):
    ParametricObject.__init__(self,environment)
    self.v0=vector3d_0; self.v1=vector3d_1
    self.v2=vector3d_2; self.v3=vector3d_3
    for v in self.v0,self.v1,self.v2,self.v3: v._children_.append(self)
  
  def _compute_(self):
    if "epsilon" in self.environment: epsilon=self.environment["epsilon"]
    else: epsilon=0.1
    self._computed_value_=[self.v0]
    for i in range(1,int(1.0/epsilon)):
      t=epsilon*float(i)
      x=self.v0.x*((1-t)**3)+self.v1.x*3*t*((1-t)**2)+self.v2.x*3*(t**2)*(1-t)+self.v3.x*(t**3)
      y=self.v0.y*((1-t)**3)+self.v1.y*3*t*((1-t)**2)+self.v2.y*3*(t**2)*(1-t)+self.v3.y*(t**3)
      z=self.v0.z*((1-t)**3)+self.v1.z*3*t*((1-t)**2)+self.v2.z*3*(t**2)*(1-t)+self.v3.z*(t**3)
      self._computed_value_.append(Vector3D(x,y,z,self.environment))
    self._computed_value_.append(self.v3)
    
  
  #def update(self):
#---

class Bezier3x3Surface(ParametricObject):
  def __init__(self,segment_0,segment_1,segment_2,segment_3,environment):
    self.segments=[segment_0,segment_1,segment_2,segment_3]
    ParametricObject.__init__(self,environment)
    for segment in self.segments: segment._children_.append(self)
    sorted_segments=[]
    self._orientations_=[False,False,False,False]
    # 1 ------ determining of surface's polygon topology
    verts=[]
    while len(sorted_segments)<4:
      if not len(sorted_segments): i=0; verts+=[self.segments[i].v0,self.segments[i].v3]; rev=False
      else:
	for i in range(4):
	  if self.segments[i] in sorted_segments: continue
	  if self.segments[i].v0 is verts[-1]: verts.append(self.segments[i].v3); rev=False; break
	  elif self.segments[i].v3 is verts[-1]: verts.append(self.segments[i].v0); rev=True; break
      sorted_segments.append(self.segments[i]); self._orientations_[i]=rev
    if len(verts)<>5 or verts[0]<>verts[-1]: raise TopologyError("verts="+str([[str(v.x),str(v.y),str(v.z)] for v in verts]))
    self.segments=sorted_segments
    self._verts_=verts[:-1]
    self._orientations_[2]=not self._orientations_[2]
    self._orientations_[3]=not self._orientations_[3]
  
  def _ft_(self,M4x4,i,u,v):
    P=M4x4
    (v - 1)**3*(u - 1)**3*P[0][0][i] - 3*(v - 1)**3*(u - 1)**2*P[1][0][i]*u + \
    3*(v - 1)**3*(u- 1)*P[2][0][i]*u**2 - (v - 1)**3*P[3][0][i]*u**3 - \
    3*(v - 1)**2*(u - 1)**3*P[0][1][i]*v + 9*(v- 1)**2*(u - 1)**2*P[1][1][i]*u*v - \
    9*(v - 1)**2*(u - 1)*P[2][1][i]*u**2*v + 3*(v -1)**2*P[3][1][i]*u**3*v + \
    3*(v - 1)*(u - 1)**3*P[0][2][i]*v**2 - 9*(v - 1)*(u -1)**2*P[1][2][i]*u*v**2 + \
    9*(v - 1)*(u - 1)*P[2][2][i]*u**2*v**2 - 3*(v -1)*P[3][2][i]*u**3*v**2 - \
    (u - 1)**3*P[0][3][i]*v**3 + 3*(u - 1)**2*P[1][3][i]*u*v**3 - 3*(u -1)*P[2][3][i]*u**2*v**3 + P[3][3][i]*u**3*v**3
  
  def _compute_(self):
    if "epsilon" in self.environment: epsilon=self.environment["epsilon"]
    else: epsilon=0.1
    e=self.environment
    M4x4=[None,[None,Vector3D(0,0,0,e),Vector3D(0,0,0,e),None],[None,Vector3D(0,0,0,e),Vector3D(0,0,0,e),None],None]
    for i in (0,2):
      if self._orientations_[i]: M4x4[(i<>0)*3]=[self.segments[i].v0,self.segments[i].v1,self.segments[i].v2,self.segments[i].v3]
      else: M4x4[(i<>0)*3]=[self.segments[i].v3,self.segments[i].v2,self.segments[i].v1,self.segments[i].v0]
    for i in (1,3):
      if self._orientations_[i]: M4x4[1][(i<>1)*3]=self.segments[i].v1; M4x4[2][(i<>1)*3]=self.segments[i].v2
      else: M4x4[1][(i<>1)*3]=self.segments[i].v2; M4x4[2][(i<>1)*3]=self.segments[i].v1
      
    comp_matrix=[]
    for i in range((int(1.0/epsilon)+1)): comp_matrix.append([None]*(int(1.0/epsilon)+1))

    for i in (0,-1): 
      comp_matrix[i]=self.segments[(i<>0)*3].compute()[:]
      if not self._orientations_[(i<>0)*3]: comp_matrix[i].reverse()
    for j in (0,-1):
      if self._orientations_[(j==0)+(j<>0)*3]: i=0
      else: i=int(1.0/epsilon)
      for v in self.segments[(j==0)+(j<>0)*3].compute():
	comp_matrix[i][j]=v
	if self._orientations_[(j==0)+(j<>0)*3]: i+=1
	else: i-=1
    for i in range(1,int(1.0/epsilon)):
      for j in range(1,int(1.0/epsilon)):
	u=epsilon*float(i)
	v=epsilon*float(j)
	comp_matrix[i][j]=Vector3D(self._ft_(M4x4,0,u,v),self._ft_(M4x4,1,u,v),self._ft_(M4x4,2,u,v),e)
	
    for m in comp_matrix: print m
    return

#---

class Model(ParametricObject):
  def __init__(self,environment):
    ParametricObject.__init__(self,environment)
  

class SomeModel(Model):

  def __init__(self):
    Model.__init__(self,{})
    e=self.environment
    self["v0"]=Vector3D(0,0,0,e)
    self["v0_0"]=Vector3D(5,5,0,e)
    self["v0_1"]=Vector3D(7,6,0,e)
    
    self["v1"]=Vector3D(12,10,0,e)
    self["v1_0"]=Vector3D(13,30,0,e)
    self["v1_1"]=Vector3D(13,40,0,e)
    
    self["v2"]=Vector3D(14,54,0,e)
    self["v2_0"]=Vector3D(10,50,0,e)
    self["v2_1"]=Vector3D(5,48,0,e)
    
    self["v3"]=Vector3D(2,45,0,e)
    self["v3_0"]=Vector3D(1,20,0,e)
    self["v3_1"]=Vector3D(1,10,0,e)
    
    self["bz0"]=Bezier3Segment(self["v0"],self["v0_0"],self["v0_1"],self["v1"],e)
    self["bz1"]=Bezier3Segment(self["v1"],self["v1_0"],self["v1_1"],self["v2"],e)
    self["bz2"]=Bezier3Segment(self["v2"],self["v2_0"],self["v2_1"],self["v3"],e)
    self["bz3"]=Bezier3Segment(self["v3"],self["v3_0"],self["v3_1"],self["v0"],e)
    
    self["bz_s0"]=Bezier3x3Surface(self["bz0"],self["bz1"],self["bz2"],self["bz3"],e)
    
    self["T1"]="3000+T12+v0.x"
    self["T12"]="3000+1.0"
    self["T16"]="T12**v0.z"

#S=SomeModel()
#vs=S["bz0"].compute()
#print S["bz_s0"].compute()

#print [[str(v.x),str(v.y),str(v.z)] for v in vs]
#print S["T16"].compute()
    
class Basic(object): 
  
  class DescreteModel:
    csg_shared_edges=[]    
    _min_point=[None,None,None]
    _max_point=[None,None,None]
    _vertices=[]
    _indices=[]
    _i2vi=[]
    _normals=[]
    _colors=[]
    _texture_uvs=[]
    
    def __init__(self,name): self.name=name
    def __del__(self): 
      if "pyel3d_model" in self.__dict__: self.pyel3d_model.Clear()
    def generatePyEl3dModel(self):
      self.pyel3d_model=PyEl3d.Model(self.name)
      self.pyel3d_model.Clear()
      self.pyel3d_model.SetSurface(self._vertices,self._indices,self._texture_uvs,self._normals)
      self.pyel3d_model.SetVisiblity(False)
      
    def _generateNormals(self):
      self._normals=[[0.0,0.0,0.0]]*len(self._vertices)
      for i in self._indices:      
	v0=list(self._vertices[i[0]])
	v1=list(self._vertices[i[2]])
	v2=list(self._vertices[i[1]])
	v0[0]-=v1[0]; v0[1]-=v1[1]; v0[2]-=v1[2]
	v1[0]-=v2[0]; v1[1]-=v2[1]; v1[2]-=v2[2]
	tn=[v0[1]*v1[2]-v0[2]*v1[1],
	    v0[2]*v1[0]-v0[0]*v1[2],
	    v0[0]*v1[1]-v0[1]*v1[0]]
	length=sqrt(tn[0]*tn[0]+tn[1]*tn[1]+tn[2]*tn[2])
	if length==0.0: continue
	tn=[tn[0]/length,tn[1]/length,tn[2]/length]
	for j in range(3):
	  length=0.0
	  for k in range(3):
	    self._normals[i[j]][k]+=tn[k]
	    length+=self._normals[i[j]][k]*self._normals[i[j]][k]
	  length=sqrt(length)
	  try:
	   self._normals[i[j]]=[self._normals[i[j]][0]/length,self._normals[i[j]][1]/length,self._normals[i[j]][2]/length]
	  except ZeroDivisionError: self._normals[i[j]]=[0,0,0]
	  
    def generateCylindricalTextureUVs(self,radius=100.0,top=100.0,bottom=0.0,ufactor=1.0,vfactor=1.0):
       ix=0; iz=1; iy=2
       self._texture_uvs=[]
       for p in self._vertices:
	 u=ufactor*((p[iz]-bottom)/(top-bottom))
	 if p[ix]<>0: angle=atan(p[iy]/p[ix])
	 else: angle=pi/2.0
	 if angle<0: angle=pi+angle
	 if p[iy]<0:  angle=pi+angle
	 v=vfactor*(angle/(2*pi))
	 self._texture_uvs.append([u,v])
    
    def intersection(self,dm,new_name):
      out_dm=Basic.DescreteModel(new_name)
      out_dm._vertices,out_dm._indices,out_dm.csg_shared_edges=PyEl3d.CSGIntersection(self._vertices,self._indices,dm._vertices,dm._indices)
      return out_dm
      
    def difference(self,dm,new_name):
      out_dm=Basic.DescreteModel(new_name)
      out_dm._vertices,out_dm._indices,out_dm.csg_shared_edges=PyEl3d.CSGDifference(self._vertices,self._indices,dm._vertices,dm._indices)
      return out_dm

    def union(self,dm,new_name):
      out_dm=Basic.DescreteModel(new_name)
      out_dm._vertices,out_dm._indices,out_dm.csg_shared_edges=PyEl3d.CSGUnion(self._vertices,self._indices,dm._vertices,dm._indices)
      return out_dm
    
    def sliced(self,dm):
      return PyEl3d.CSGSlice(self._vertices,self._indices,dm._vertices,dm._indices)
      
    
    def orderCSGSharedEdges(self,check_cycles=True):
      import networkx as nx
      g=nx.Graph()
      a=self.csg_shared_edges
      for i in range(len(a)/2):
	g.add_edge(a[i*2],a[i*2+1])
      self.csg_shared_edges=[]
      if check_cycles:
	cycles=nx.cycle_basis(g)
	for cycle in cycles:
	  if len(self.csg_shared_edges)<len(cycle): self.csg_shared_edges=cycle
	if len(self.csg_shared_edges): return
	else: self.csg_shared_edges=None
      all_sp=nx.all_pairs_shortest_path(g)
      for k_key in all_sp:
	for key in all_sp[k_key]:
	 if self.csg_shared_edges is None or len(self.csg_shared_edges)<len(all_sp[k_key][key]): self.csg_shared_edges=all_sp[k_key][key]

  def __init__(self,knots_table=[],segments={},surfaces={},variables={},super_knots={},dm_displacement=[0,0,0],name=None,version=0.1):
    self.hide_polylines=True
    self.descrete_models={}
    self.polylines=[]
    self.dm_clockwise_triangles=True
    self.dm_displacement=dm_displacement
    self.bearing_model=None
    self.iters=10
    self.segments=segments
    self.knots_table=knots_table
    self.surfaces=surfaces
    self.super_knots=super_knots
    self.variables=variables
    self.polylines={}
    self.external_vars=[]
    self.version=version
    if name is None: self.name=self.__class__.__name__
    else: self.name=name
    if len(knots_table)>0: self.knots_i=0
    else: self.knots_i=-1
    
  def update(self): pass  
      
  def pointOnBearingSpline(self,snames,dis,model=None,is_inv_list=[]):
    if model is None: model=self.bearing_model
    dis_=dis; lp1=None
    iters=20
    for a in range(len(snames)):
      sname=snames[a]
      if len(is_inv_list)>a: is_inv=is_inv_list[a]
      else: is_inv=False
      for i in range(iters):
        lp0=lp1
        segment=model.segments[sname]
        lp1=[None,None,None]
        t=float(i)/float(iters-1)
        if is_inv: t=1.0-t
        for c,ci in ('x',0),('y',1),('z',2):
          p0=model.knots[segment['knot0']][ci]; p1=model.knots[segment['knot1']][ci]
          exec("lp1[ci]="+segment[c+'t']) in model.computed_vars,locals()
        if lp0 is None: continue
        l=sqrt((lp0[0]-lp1[0])**2+(lp0[1]-lp1[1])**2+(lp0[2]-lp1[2])**2)
        if dis_<l: 
	  if is_inv: t=t-(dis_/(l*float(iters)))
          else: t=t+(dis_/(l*float(iters)))
          for c,ci in ('x',0),('y',1),('z',2):
            p0=model.knots[segment['knot0']][ci]; p1=model.knots[segment['knot1']][ci]
            exec("lp1[ci]="+segment[c+'t']) in model.computed_vars,locals()
          return lp1+[sname,t]
        else: dis_-=l
    return lp1+["",0]

    
  
  def approximateOnBearingSurface(self,curve_fs,knot0,knot1,surfaces_names,dz=-0.5,Cs={'x':[None,None],'y':[None,None],'z':[None,None]},dz_at_first=True,dz_at_last=True):
    if is_debug:
      polyline=self.addPolyline(knot0+"-"+knot1)
      polyline.Clear()
      last_x=last_y=last_z=None    
    bsurf=self.bearing_model.surfaces
    approx_points=[[],[],[]]
    seg_points_0=[]; seg_points_1=[]
    verts=self.bearing_model.dm._vertices
    cn1=curve_fs.keys()[0]
    cn2=curve_fs.keys()[1]
    if not 'x' in (cn1,cn2): cn0='x'
    elif not 'y' in (cn1,cn2): cn0='y'
    elif not 'z' in (cn1,cn2): cn0='z'
    ci0=axis_name_to_int[cn0]; ci1=axis_name_to_int[cn1]; ci2=axis_name_to_int[cn2]
    ci0_=dev_axis_name_to_int[cn0]; ci1_=dev_axis_name_to_int[cn1]; ci2_=dev_axis_name_to_int[cn2]
    #dz=-0.5 #abs(self.knots[knot0][ci0]-self.knots[knot1][ci0])/10.0
    #self.knots[knot0][ci0]+=dz
    #self.knots[knot1][ci0]+=dz
    for i in range(self.iters):
      t=float(i)/float(self.iters-1)
      for ci,cn,seg_points in (ci1,cn1,seg_points_0),(ci2,cn2,seg_points_1):
	p0=self.knots[knot0][ci]
	p1=self.knots[knot1][ci]
	seg_points.append(eval(curve_fs[cn]))
      if len(seg_points_0)==2:
	done=False
	for sname in surfaces_names:
	  for triangle in bsurf[sname]['grid_triangles']:
	    for i0,i1 in (0,1),(1,2),(2,0):
	      grid_points_0=[]; grid_points_1=[]; grid_points_2=[]
	      for ci_,ci,grid_points in (ci1_,ci1,grid_points_0),(ci2_,ci2,grid_points_1),(ci0_,ci0,grid_points_2): grid_points+=[verts[triangle[i0]][ci_]-self.dm_displacement[ci],verts[triangle[i1]][ci_]-self.dm_displacement[ci]]
	      x0_0=grid_points_0[0]; y0_0=grid_points_1[0]; z0_0=grid_points_2[0]
	      x0_1=grid_points_0[1]; y0_1=grid_points_1[1]; z0_1=grid_points_2[1]
	      x1_0=seg_points_0[0]; y1_0=seg_points_1[0]
	      x1_1=seg_points_0[1]; y1_1=seg_points_1[1]
	      try:
		z=-(((x1_0 - x1_1)*y0_1 - \
		(x0_1 - x1_1)*y1_0 + (x0_1 - x1_0)*y1_1)*z0_0 - ((x1_0 - x1_1)*y0_0 - \
		(x0_0 - x1_1)*y1_0 + (x0_0 - x1_0)*y1_1)*z0_1)/((x1_0 - x1_1)*y0_0 - \
		(x1_0 - x1_1)*y0_1 - (x0_0 - x0_1)*y1_0 + (x0_0 - x0_1)*y1_1)
		y=-(((y1_0 - y1_1)*x0_1 + x1_0*y1_1 - x1_1*y1_0)*y0_0 - \
		((y1_0 -y1_1)*x0_0 + x1_0*y1_1 - x1_1*y1_0)*y0_1)/((y1_0 - y1_1)*x0_0 - \
		(y1_0 -y1_1)*x0_1 - (x1_0 - x1_1)*y0_0 + (x1_0 - x1_1)*y0_1)
		x=((x1_0 -x1_1)*x0_0*y0_1 - (x1_0 - x1_1)*x0_1*y0_0 - \
		(x1_0*y1_1 - x1_1*y1_0)*x0_0 + \
		(x1_0*y1_1 - x1_1*y1_0)*x0_1)/((y1_0 - y1_1)*x0_0 - (y1_0 - y1_1)*x0_1 \
		- (x1_0 - x1_1)*y0_0 + (x1_0 - x1_1)*y0_1)
	      except ZeroDivisionError: continue
	      if ((x>=x0_0 and x<=x0_1) or (x>=x0_1 and x<=x0_0)) and \
	         ((x>=x1_0 and x<=x1_1) or (x>=x1_1 and x<=x1_0)) and \
	         ((y>=y0_0 and y<=y0_1) or (y>=y0_1 and y<=y0_0)) and \
	         ((y>=y1_0 and y<=y1_1) or (y>=y1_1 and y<=y1_0)):
		  z+=dz
		  if is_debug: 
		    if not (last_z is None):
		      poly0=[0,0,0]; poly1=[0,0,0]
		      poly0[ci0_]=last_z+self.dm_displacement[ci0]; poly0[ci1_]=last_x+self.dm_displacement[ci1]; poly0[ci2_]=last_y+self.dm_displacement[ci2]
		      poly1[ci0_]=z+self.dm_displacement[ci0]; poly1[ci1_]=x+self.dm_displacement[ci1]; poly1[ci2_]=y+self.dm_displacement[ci2]
		      polyline.AddLine(poly0,poly1,[0,0,0])
		    last_x=x; last_y=y; last_z=z
		  approx_points[ci1].append(x)
		  approx_points[ci2].append(y)
		  approx_points[ci0].append(z)
		  done=True; break
	    if done: break
	  if done: break
	seg_points_0=[seg_points_0[1]]
	seg_points_1=[seg_points_1[1]]
    out=[]
    for cn in 'x','y','z':
      ci=axis_name_to_int[cn]
      T=len(approx_points[ci])+2
      t1=t2=t3=t4=t5=t6=0.0
      Xt=Xt2=Xt3=0.0
      P0=float(self.knots[knot0][ci])
      P3=float(self.knots[knot1][ci])
      #if cn==cn0:
	#if  not dz_at_first: P0+=dz 
	#if not dz_at_last: P3+=dz
      t=0.0
      for approx_point in [P0]+approx_points[ci]+[P3]:
	t1=t1+t
	Xt=Xt+approx_point*t
	t_=t*t; t2=t2+t_
	Xt2=Xt2+approx_point*t_
	t_=t_*t; t3=t3+t_
	Xt3=Xt3+approx_point*t_
	t_=t_*t; t4=t4+t_
	t_=t_*t; t5=t5+t_
	t_=t_*t; t6=t6+t_
	t=t+1.0/float(T-1)
      t=t1
      if len(Cs[cn])+1 is 3: 
	if not Cs[cn][0] is None:
	  P1=Cs[cn][0]
	  out.append([-1/3*((t5 - t6)*P3 + 3*(t3 - 3*t4 + 3*t5 - t6)*P1 + (t2 - 4*t3 +6*t4 - 4*t5 + t6)*P0 - Xt2 + Xt3)/(t4 - 2*t5 + t6),P1])
	elif not Cs[cn][1] is None:
	  P2=Cs[cn][1]
	  out.append([-1/3*((t4 - 2*t5 + t6)*P3 + 3*(t3 - 3*t4 + 3*t5 - t6)*P2 + (t - 5*t2 + 10*t3 - 10*t4 + 5*t5 - t6)*P0 - Xt + 2*Xt2 - Xt3)/(t2 - 4*t3 + 6*t4 - 4*t5 + t6),P2])
	else:
	  out.append([  float(1.0/3.0)*float((t4 - 2.0*t5 + t6)*Xt + (t3 - 2.0*t4 + t5)*Xt3 - \
					    (t3 - t4 - t5 + t6)*Xt2 - ((t3 - t4)*t6 - (t3 + t4)*t5 + \
					    t4**2.0 + t5**2.0)*P3 - ((t - 2.0*t2 - 8.0*t3)*t4 + (t - 4.0*t2 + 5.0*t3 - 2.0*t4)*t6 - \
					    (2.0*t - 7.0*t2 + 4.0*t3 + 5.0*t4)*t5 - t2*t3 + 4.0*t3**2.0 + 8.0*t4**2.0 + 2.0*t5**2.0)*P0)/float((t2 + 2.0*t3)*t4 + \
					    (t2 - 2.0*t3 + t4)*t6 - 2.0*(t2 - t3 - t4)*t5 - t3**2.0 - 3.0*t4**2.0 - t5**2.0),
					    -1.0/3.0*((t3 - 3.0*t4 + 3.0*t5 - t6)*Xt + (t2 - 3.0*t3 + 3.0*t4 - t5)*Xt3 - \
					    (t2 - 2.0*t3 + 2.0*t5 - t6)*Xt2 - ((t2 - 3.0*t3 + 2.0*t4)*t6 - \
					    (t2 - 2.0*t3 - 3.0*t4)*t5 + t3*t4 - 3.0*t4**2.0 - 2.0*t5**2.0)*P3 - \
					    ((t + 3.0*t2)*t3 - (3.0*t - 3.0*t2 - 8.0*t3)*t4 - (t - 3.0*t2 + 3.0*t3 - t4)*t6 + \
					    (3.0*t - 7.0*t2 + 3.0*t3 + 3.0*t4)*t5 - t2**2.0 - 6.0*t3**2.0 - 6.0*t4**2.0 - t5**2.0)*P0)/((t2 + 2.0*t3)*t4 + \
					    (t2 - 2.0*t3 + t4)*t6 - 2.0*(t2 - t3 - t4)*t5 - t3**2.0 - 3.0*t4**2.0 - t5**2.0) ])
					    
    return out
  
  def Bezier3String(self,p0,p1,p2,p3):
    return "(p0)*((1-t)**3)+(p1)*3*t*((1-t)**2)+(p2)*3*(t**2)*(1-t)+(t**3)*(p3)".replace("p0",p0).replace("p1",p1).replace("p2",p2).replace("p3",p3)
  
  def approximateByBezier3(self,x):
      T=len(x)+2
      t1=t2=t3=t4=t5=t6=0.0
      Xt=Xt2=Xt3=0.0
      P0=x[0]; P3=x[-1]
      t=0.0
      for approx_point in x:
	t1=t1+t
	Xt=Xt+approx_point*t
	t_=t*t; t2=t2+t_
	Xt2=Xt2+approx_point*t_
	t_=t_*t; t3=t3+t_
	Xt3=Xt3+approx_point*t_
	t_=t_*t; t4=t4+t_
	t_=t_*t; t5=t5+t_
	t_=t_*t; t6=t6+t_
	t=t+1.0/float(T-1)
      t=t1
      return [x[0], float(1.0/3.0)*float((t4 - 2.0*t5 + t6)*Xt + (t3 - 2.0*t4 + t5)*Xt3 - \
					    (t3 - t4 - t5 + t6)*Xt2 - ((t3 - t4)*t6 - (t3 + t4)*t5 + \
					    t4**2.0 + t5**2.0)*P3 - ((t - 2.0*t2 - 8.0*t3)*t4 + (t - 4.0*t2 + 5.0*t3 - 2.0*t4)*t6 - \
					    (2.0*t - 7.0*t2 + 4.0*t3 + 5.0*t4)*t5 - t2*t3 + 4.0*t3**2.0 + 8.0*t4**2.0 + 2.0*t5**2.0)*P0)/float((t2 + 2.0*t3)*t4 + \
					    (t2 - 2.0*t3 + t4)*t6 - 2.0*(t2 - t3 - t4)*t5 - t3**2.0 - 3.0*t4**2.0 - t5**2.0),
					    -1.0/3.0*((t3 - 3.0*t4 + 3.0*t5 - t6)*Xt + (t2 - 3.0*t3 + 3.0*t4 - t5)*Xt3 - \
					    (t2 - 2.0*t3 + 2.0*t5 - t6)*Xt2 - ((t2 - 3.0*t3 + 2.0*t4)*t6 - \
					    (t2 - 2.0*t3 - 3.0*t4)*t5 + t3*t4 - 3.0*t4**2.0 - 2.0*t5**2.0)*P3 - \
					    ((t + 3.0*t2)*t3 - (3.0*t - 3.0*t2 - 8.0*t3)*t4 - (t - 3.0*t2 + 3.0*t3 - t4)*t6 + \
					    (3.0*t - 7.0*t2 + 3.0*t3 + 3.0*t4)*t5 - t2**2.0 - 6.0*t3**2.0 - 6.0*t4**2.0 - t5**2.0)*P0)/((t2 + 2.0*t3)*t4 + \
					    (t2 - 2.0*t3 + t4)*t6 - 2.0*(t2 - t3 - t4)*t5 - t3**2.0 - 3.0*t4**2.0 - t5**2.0),x[-1] ] 
  
  
  def addPolyline(self,name,points=[],width=2.0,color=[1,1,1],normal=[0,1,0]):
    polyline=self.polylines[name]=PyEl3d.ColoredPolyline(self.name+"_"+name)
    polyline.Clear()
    polyline.SetNormal([normal[0],normal[2],normal[1]])
    last_point=None
    d=self.dm_displacement
    #if rev: points_=reversed(points)
    #else: points_=points
    for point in points:
      if not (last_point is None): polyline.AddLine([point[0]+d[0],point[2]+d[2],point[1]+d[1]],[last_point[0]+d[0],last_point[2]+d[2],last_point[1]+d[1]],color)
      last_point=point
    polyline.SetWidth(width)
    return self.polylines[name]
  
  def clearPolylines(self):
      if "polylines" in self.__dict__:
	for key,polyline in self.polylines.iteritems(): polyline.Clear()
      self.polylines={}
  
  def pointListFromSegment(self,sname):
    out=[]
    segment=self.segments[sname]
    iters=self.iters
    for i in range(iters):
      t=float(i)/float(iters-1)
      for ci,cn in (0,'x'),(1,'y'),(2,'z'):
	p0=self.knots[segment['knot0']][ci]; p1=self.knots[segment['knot1']][ci]
	exec(cn+"="+segment[cn+"t"]) in self.computed_vars,locals()
      out.append([x,y,z])
    return out
      
  
  def pointListFromProjectionOnGrid(self,center,direction,surfaces,line_xt,line_yt,accuracy=0.0):
    points=[]
    g_points=[]
    g_grid=[[[line_xt(0),line_yt(0)],[line_xt(1.0),line_yt(1.0)]]]
    intersected=False
    ci0=axis_name_to_int['x']; ci1=axis_name_to_int['y']; ci2=axis_name_to_int['z']
    ci0_=dev_axis_name_to_int['x']; ci1_=dev_axis_name_to_int['y']; ci2_=dev_axis_name_to_int['z']
    d_x=direction[ci0]-center[ci0]; d_y=direction[ci1]-center[ci1]; d_z=direction[ci2]-center[ci2]
    if d_x==0 and d_z==0: cos_oy=1.0; sin_oy=0.0
    else: cos_oy=(d_x)/sqrt(d_x**2+d_z**2); sin_oy=(d_z)/sqrt(d_x**2+d_z**2)
    if d_x==0 and d_y==0: cos_oz=1.0; sin_oz=0.0
    else: cos_oz=(d_x)/sqrt(d_x**2+d_y**2); sin_oz=(d_y)/sqrt(d_x**2+d_y**2)
    sin_oy_2=sin_oy**2; sin_oz_2=sin_oz**2
    cos_oy_2=cos_oy**2; cos_oz_2=cos_oz**2
    def to_local(p_x,p_y,p_z):
      p_x-=center[ci0]; p_y-=center[ci1]; p_z-=center[ci2]
      return [(cos_oy*p_x - p_z*sin_oy)*cos_oz + p_y*sin_oz, -(cos_oy*p_x -p_z*sin_oy)*sin_oz + cos_oz*p_y, cos_oy*p_z + p_x*sin_oy]      
    def to_global(p_x,p_y,p_z):
      sin_oz_=-sin_oz; cos_oz_=cos_oz
      sin_oy_=-sin_oy; cos_oy_=cos_oy
      return [(cos_oy_*p_x - p_z*sin_oy_)*cos_oz_ + p_y*sin_oz_+center[ci0], -(cos_oy_*p_x -p_z*sin_oy_)*sin_oz_ + cos_oz_*p_y+center[ci1], cos_oy_*p_z + p_x*sin_oy_+center[ci2]]
    last_x=last_z=None
    seg_points_0=[]; seg_points_1=[]
    d=self.dm_displacement
    verts=self.descrete_models[self.name]._vertices   
    iters=self.iters
    for i in range(iters):
      t=float(i)/float(iters-1)
      x1_1,y1_1=line_xt(t),line_yt(t)
      if t>0:
	for sname in surfaces:
	  if sname in self.surfaces:
	   if not 'grid_triangles' in self.surfaces[sname]: continue
	   for triangle in self.surfaces[sname]['grid_triangles']:
	    for i0,i1 in (0,1),(1,2),(2,0):
	      grid_points_0=[]; grid_points_1=[]; grid_points_2=[]
	      for ci_,ci,grid_points in (ci0_,ci0,grid_points_0),(ci1_,ci1,grid_points_1),(ci2_,ci2,grid_points_2): grid_points+=[verts[triangle[i0]][ci_]-d[ci],verts[triangle[i1]][ci_]-d[ci]]
	      z0_0,x0_0,y0_0=to_local(grid_points_0[0],grid_points_1[0],grid_points_2[0])
	      z0_1,x0_1,y0_1=to_local(grid_points_0[1],grid_points_1[1],grid_points_2[1])
	      if sname=="b" or sname=="bb": g_grid.append([[x0_0,y0_0],[x0_1,y0_1]])
	      try:
		y = ((y1_0 - y1_1)*(y0_0*x0_1-y0_1*x0_0) + (y1_0*x1_1 - y1_1*x1_0)*(y0_1-y0_0))/\
		    ((x1_0 - x1_1)*(y0_0 -y0_1) + (y1_0 - y1_1)*(x0_1 - x0_0))
	      except ZeroDivisionError: continue 
	      try:
		x = ((x1_0 - x1_1)*(x0_0*y0_1-x0_1*y0_0) + (x1_0*y1_1 - x1_1*y1_0)*(x0_1-x0_0))/\
		    ((y1_0 - y1_1)*(x0_0 -x0_1) + (x1_0 - x1_1)*(y0_1 - y0_0))
	      except ZeroDivisionError: continue 
	      try: z = ((x - x0_1)*z0_0 - (x - x0_0)*z0_1)/(x0_0 - x0_1)
	      except ZeroDivisionError:
		try: z == ((y - y0_1)*z0_0 - (y - y0_0)*z0_1)/(y0_0 - y0_1)
		except ZeroDivisionError: continue
	      d_=accuracy
	      if ((x+d_>=x0_0 and x-d_<=x0_1) or (x+d_>=x0_1 and x-d_<=x0_0)) and \
	         ((x+d_>=x1_0 and x-d_<=x1_1) or (x+d_>=x1_1 and x-d_<=x1_0)) and \
	         ((y+d_>=y0_0 and y-d_<=y0_1) or (y+d_>=y0_1 and y-d_<=y0_0)) and \
	         ((y+d_>=y1_0 and y-d_<=y1_1) or (y+d_>=y1_1 and y-d_<=y1_0)):
		      intersected=True
		      g_points.append([x,y])
		      points.append(to_global(z,x,y))

      x1_0=x1_1; y1_0=y1_1
    if len(g_grid)>1: pass 
      #print "g_grid=",g_grid
      #print "g_points=",g_points
      #print "intersected=",intersected
    return points
    
  
  def generateDebugObjects(self,generate_dirs=True):
    polyline=self.addPolyline(self.name+"_debug")
    polyline.Clear()
    for name,segment in self.segments.iteritems():
      point0=[self.knots[segment["knot0"]][0],self.knots[segment["knot0"]][1],self.knots[segment["knot0"]][2]]
      point1=[self.knots[segment["knot1"]][0],self.knots[segment["knot1"]][1],self.knots[segment["knot1"]][2]]
      for i in range(self.iters*3):
	point=[]
	for cn,ci in ("x",0),("z",2),("y",1):
	  t=float(i)/float(self.iters*3-1)
	  p0=point0[ci]; p1=point1[ci]
	  exec("point.append("+segment[cn+"t"]+"+self.dm_displacement[ci])") in self.computed_vars,locals()
	  #point.append(eval(segment[cn+"t"])+self.dm_displacement[ci])
	if i: polyline.AddLine(last_point,point)
	last_point=point
      color=[random(),random(),random()]
      if generate_dirs:
	for point0_1,i in (point0,1),(point1,-2):
	  if segment.has_key("Cx_"): polyline.AddLine([point0_1[0]+self.dm_displacement[0],point0_1[2]+self.dm_displacement[2],point0_1[1]+self.dm_displacement[1]],[segment["Cx_"][i]+self.dm_displacement[0],segment["Cz_"][i]+self.dm_displacement[2],segment["Cy_"][i]+self.dm_displacement[1]],color)
	
    
  def setVisiblity(self,visible):
    for key,polyline in self.polylines.iteritems(): 
      if self.hide_polylines: polyline.SetVisiblity(visible)
    for dm_name in self.descrete_models:
      if "pyel3d_model" in self.descrete_models[dm_name].__dict__: self.descrete_models[dm_name].pyel3d_model.SetVisiblity(visible)

  
  def generateDescreteModel(self, closed=1):
    def BezierSurface(P,N,M):
      #return lambda u,v,i: (v - 1.0)*(u - 1)*P[0][0] - (v - 1.0)*P[-1][0]*u - (u - 1.0)*P[0][-1]*v + P[-1][-1]*u*v
      if N==3 and M==4:
	return lambda u,v,i: \
			  -(v - 1)**4*(u - 1)**3*P[0][0] + 3*(v - 1)**4*(u - 1)**2*P[1][0]*u - \
			  3*(v -1)**4*(u - 1)*P[2][0]*u**2 + (v - 1)**4*P[3][0]*u**3 + \
			  4*(v - 1)**3*(u -1)**3*P[0][1]*v - 12*(v - 1)**3*(u - 1)**2*P[1][1]*u*v + \
			  12*(v - 1)**3*(u -1)*P[2][1]*u**2*v - 4*(v - 1)**3*P[3][1]*u**3*v - \
			  6*(v - 1)**2*(u - 1)**3*P[0][2]*v**2 + 18*(v - 1)**2*(u - 1)**2*P[1][2]*u*v**2 - \
			  18*(v - 1)**2*(u - 1)*P[2][2]*u**2*v**2 + 6*(v - 1)**2*P[3][2]*u**3*v**2 + \
			  4*(v - 1)*(u - 1)**3*P[0][3]*v**3 - 12*(v -1)*(u - 1)**2*P[1][3]*u*v**3 + \
			  12*(v - 1)*(u - 1)*P[2][3]*u**2*v**3 - 4*(v -1)*P[3][3]*u**3*v**3 - \
			  (u - 1)**3*P[0][4]*v**4 + 3*(u - 1)**2*P[1][4]*u*v**4 -\
			  3*(u -1)*P[2][4]*u**2*v**4 + P[3][4]*u**3*v**4
      elif N==3 and M==3:
	return lambda u,v,i: \
			  (v - 1)**3*(u - 1)**3*P[0][0] - 3*(v - 1)**3*(u - 1)**2*P[1][0]*u + \
			  3*(v - 1)**3*(u- 1)*P[2][0]*u**2 - (v - 1)**3*P[3][0]*u**3 - \
			  3*(v - 1)**2*(u - 1)**3*P[0][1]*v + 9*(v- 1)**2*(u - 1)**2*P[1][1]*u*v - \
			  9*(v - 1)**2*(u - 1)*P[2][1]*u**2*v + 3*(v -1)**2*P[3][1]*u**3*v + \
			  3*(v - 1)*(u - 1)**3*P[0][2]*v**2 - 9*(v - 1)*(u -1)**2*P[1][2]*u*v**2 + \
			  9*(v - 1)*(u - 1)*P[2][2]*u**2*v**2 - 3*(v -1)*P[3][2]*u**3*v**2 - \
			  (u - 1)**3*P[0][3]*v**3 + 3*(u - 1)**2*P[1][3]*u*v**3 - 3*(u -1)*P[2][3]*u**2*v**3 + P[3][3]*u**3*v**3
      elif N==3 and M==2:
	return lambda u,v,i: \
			  -(v - 1)**2*(u - 1)**3*P[0][0] + 3*(v - 1)**2*(u - 1)**2*P[1][0]*u - \
			  3*(v -1)**2*(u - 1)*P[2][0]*u**2 + (v - 1)**2*P[3][0]*u**3 + \
			  2*(v - 1)*(u - 1)**3*P[0][1]*v - 6*(v - 1)*(u - 1)**2*P[1][1]*u*v + \
			  6*(v - 1)*(u - 1)*P[2][1]*u**2*v - 2*(v -1)*P[3][1]*u**3*v - \
			  (u - 1)**3*P[0][2]*v**2 + 3*(u - 1)**2*P[1][2]*u*v**2 - \
			  3*(u - 1)*P[2][2]*u**2*v**2 + P[3][2]*u**3*v**2
      return lambda u,v,i: 0.0
    for name in self.external_vars: self.variables[name]=str(PyEl3d.GetCommonVariableValuef(self.name+":"+name))
    dm=self.DescreteModel(self.name)
    dm._vertices=[]; dm._indices=[]; dm._texture_uvs=[]; dm._min_point=[None,None,None]; dm._max_point=[None,None,None]; dm._colors=[]
    segments,surfaces,super_knots=self.segments,self.surfaces,self.super_knots
    self.edges_info={}
    if len(self.knots_table)>self.knots_i>=0: self.knots=knots=dict(self.knots_table[self.knots_i])
    else: self.knots=knots={};
    self.computed_vars=computed_vars={'variables':self.variables,'super_knots':self.super_knots,'knots':knots,'parent':self.bearing_model,'self':self,'PyEl3d':PyEl3d}
    pyel3d_model_module.computeVariables(computed_vars)
    knots_indices={}
    segments_indices={}      
    for surface_name,surface_desc in surfaces.iteritems():      
      if "cond" in surface_desc:
	exec("cond="+surface_desc["cond"]) in computed_vars,locals()
	if not cond: continue
      surface_desc['grid_triangles']=[]
      surface=surface_desc['segments']
      if len(surface)<>4: print "Warning: skipping polygon. Only 4-gons support is implemented now"; continue
      surface_desc['verts']=verts=[]; surface_desc['edges']=edges=[]; surface_desc['funcs']=funcs=[]
      surface_=[]
      for s in surface:
	segments[s]["name"]=s
	surface_.append(segments[s])
      surface=surface_
      # 1 ------ determination of surface's polygon topology
      while len(edges)<4:
	if not len(verts): i=0; verts+=[surface[i]['knot0'],surface[i]['knot1']]; rev=False
	else:
	  for i in range(4):
	    if surface[i] in edges: continue
	    if surface[i]['knot0']==verts[-1]: verts.append(surface[i]['knot1']); rev=False; break
	    elif surface[i]['knot1']==verts[-1]: verts.append(surface[i]['knot0']); rev=True; break
	edges.append(surface[i]); surface[i]['rev']=rev
      if len(verts)<>5 or verts[0]<>verts[-1]: print "Warning: skipping polygon "+surface_name+" because of its unexpected topology"; continue 
      verts=verts[:-1]
      edges[2]['rev']=not edges[2]['rev']
      edges[3]['rev']=not edges[3]['rev']
      # 2----- evaluation of points and edges
      def exprToFunc(expr,rev):
	if rev: exec("ret=lambda p0,p1,t: (lambda p0,p1,t:"+ expr+")(p1,p0,1-t)") in computed_vars,locals()
	else: exec("ret=lambda p0,p1,t: "+expr) in computed_vars,locals()
	return ret
      for vert in verts:
	if not knots_indices.has_key(vert):
	  knot=knots[vert]
	  dm._vertices.append([knot[0]+self.dm_displacement[0],knot[2]+self.dm_displacement[2],knot[1]+self.dm_displacement[1]])
	  dm._texture_uvs.append([0,0])
	  knots_indices[vert]=len(dm._vertices)-1
      for edge in edges:
	funcs.append([exprToFunc(edge['xt'],edge['rev']),exprToFunc(edge['yt'],edge['rev']),exprToFunc(edge['zt'],edge['rev'])])
	edge_name=edge['name']
	if not segments_indices.has_key(edge_name):
	  segments_indices[edge_name]=[knots_indices[edge['knot0']]]
	  for i in range(1,self.iters):
	    t=float(i)/float(self.iters)
	    p0=knots[edge['knot0']][0]; p1=knots[edge['knot1']][0]; exec("x_="+edge['xt']) in computed_vars,locals()
	    p0=knots[edge['knot0']][1]; p1=knots[edge['knot1']][1]; exec("y_="+edge['yt']) in computed_vars,locals()
	    p0=knots[edge['knot0']][2]; p1=knots[edge['knot1']][2]; exec("z_="+edge['zt']) in computed_vars,locals()
	    dm._vertices.append([x_+self.dm_displacement[0],z_+self.dm_displacement[2],y_+self.dm_displacement[1]])
	    dm._texture_uvs.append([0,0])
	    segments_indices[edge_name].append(len(dm._vertices)-1)
	  segments_indices[edge_name].append(knots_indices[edge['knot1']])
      
      #4----- evaluation of beizer surface's matrices
	 
      #5----- defining of surface functions
      surf_funcs=[None]*3
      
      #for edge in edges: print edge['name']; print edge
      for xyz_i,xyz in (0,"x"),(1,"y"),(2,"z"):
	if True and self.version>=0.1 and len(edges[0]["C"+xyz])==len(edges[2]["C"+xyz]) and len(edges[1]["C"+xyz])==len(edges[3]["C"+xyz]):
	  N=len(edges[0]["C"+xyz])-1; M=len(edges[1]["C"+xyz])-1
	  P=[None]*(N+1)
	  for i in range(0,N+1): P[i]=[None]*(M+1)
	  for j,edge,is_ij in (0,edges[0],True),(M,edges[2],True),(N,edges[1],False),(0,edges[3],False):
	    p0=knots[edge['knot0']][xyz_i]; p1=knots[edge['knot1']][xyz_i]
	    if edge['rev']: i=len(edge["C"+xyz])-1
	    else: i=0
	    segment=self.segments[edge['name']]
	    segment["C"+xyz+"_"]=[]
	    for c in edge["C"+xyz]:
	      exec("out="+c) in computed_vars,locals()
	      segment["C"+xyz+"_"].append(out)
	      if is_ij: P[i][j]=out
	      else: P[j][i]=out
	      if edge["rev"]: i-=1
	      else: i+=1
	  
	  for i in range(1,N):
	    for j in range(1,M):
	      #if not xyz is 'z': 
	      P[i][j]=P[i][0]*(1.0-float(j)/float(M))+P[i][M]*(float(j)/float(M))
	      #else: 
	      #P[i][j]=P[0][j]*(1.0-float(i)/float(N))+P[N][j]*(float(i)/float(N))
	      u=float(i)/float(N)
	      v=float(j)/float(M)
	      #P[i][j]=(v - 1.0)*(u - 1.0)*P[0][0] - (v - 1.0)*P[-1][0]*u - (u - 1.0)*P[0][-1]*v + P[-1][-1]*u*v
	      #P[i][j]/=2.0
	  
	  P[1][1]=P[0][1]+(P[1][0]-P[0][0]); P[N-1][1]=P[N][1]+(P[N-1][0]-P[N][0])
	  P[1][M-1]=P[0][M-1]+(P[1][M]-P[0][M]); P[N-1][M-1]=P[N][M-1]+(P[N-1][M]-P[N][M])

	  for i,i_ in (1,0),(N-1,N):
	    for j in range(2,M-1):
	      v0=P[i][M-1]-P[i_][M-1]; v1=P[i][1]-P[i_][1]
	      P[i][j]=P[i_][j]+v0+(v1-v0)*(j-1)/(M-2)
	      
	  for j,j_ in (1,0),(M-1,M):
	    for i in range(2,N-1):
	      v0=P[N-1][j]-P[N-1][j_]; v1=P[1][j]-P[1][j_]
	      P[i][j]=P[i][j_]+v0+(v1-v0)*(i-1)/(N-2)
	      
	  for i in range(2,N-1):
	    for j in range(2,M-1):
	      P[i][j]=P[i][0]*(1.0-float(j)/float(M))+P[i][M]*(float(j)/float(M))
	  
	  '''
	  print xyz
	  for i in range(0,N+1): print P[i]
	  
	  print knots[edges[1]['knot0']][xyz_i],knots[edges[1]['knot1']][xyz_i],edges[1]['rev']
	  print knots[edges[3]['knot0']][xyz_i],knots[edges[3]['knot1']][xyz_i],edges[3]['rev']
	  print edges[0]['rev'],edges[2]['rev']
	  
	  print knots[verts[0]][xyz_i],knots[verts[3]][xyz_i]
	  print knots[verts[1]][xyz_i],knots[verts[2]][xyz_i]
	  '''
	  surf_funcs[xyz_i]=BezierSurface(P[:],N,M)
	  
	else: surf_funcs[xyz_i]=lambda u,v,i: funcs[0][i](
					    p0=funcs[3][i](p0=knots[verts[0]][i],p1=knots[verts[3]][i],t=v),
					    p1=funcs[1][i](p0=knots[verts[1]][i],p1=knots[verts[2]][i],t=v),
					    t=u)*v+funcs[2][i](
					    p0=funcs[3][i](p0=knots[verts[0]][i],p1=knots[verts[3]][i],t=v),
					    p1=funcs[1][i](p0=knots[verts[1]][i],p1=knots[verts[2]][i],t=v), 
					    t=u)*(1-v)
      surf_func=lambda u,v,i: surf_funcs[i](u,v,i)
      if "tx_u" in surface_desc: tx_u=surface_desc["tx_u"]
      else: tx_u="0.0"
      if "tx_v" in surface_desc: tx_v=surface_desc["tx_v"]
      else: tx_v="0.0"

      # 6-----
      def compute_tx_c(i):
	x=dm._vertices[i][0]-self.dm_displacement[0]
	y=dm._vertices[i][2]-self.dm_displacement[1]
	z=dm._vertices[i][1]-self.dm_displacement[2]
	exec("u_="+tx_u) in computed_vars,locals()
	exec("v_="+tx_v) in computed_vars,locals()
	dm._texture_uvs[i]=[u_,v_]
      
      start_n=len(dm._vertices)
      for i in range(1,self.iters+1):
	u=float(i)/float(self.iters)
	for j in range(1,self.iters+1):
	  v=float(j)/float(self.iters)
	  if i<self.iters and j<self.iters: 
	    dm._vertices.append([surf_func(u,v,0)+self.dm_displacement[0],surf_func(u,v,2)+self.dm_displacement[2],surf_func(u,v,1)+self.dm_displacement[1]])
	    dm._texture_uvs.append([0,0])
	    compute_tx_c(len(dm._vertices)-1)
	  ltopi=rtopi=lbottomi=rbottomi=None
	  if i>=self.iters:
	    if edges[1]['rev']: j0=(self.iters)-j; j1=(self.iters)-(j-1)
	    else: j0=j; j1=j-1
	    ltopi=segments_indices[edges[1]['name']][j0]
	    rtopi=segments_indices[edges[1]['name']][j1]
	    compute_tx_c(ltopi); compute_tx_c(rtopi)
	  if j>=self.iters:
	    if edges[2]['rev']: i0=(self.iters)-i; i1=(self.iters)-(i-1)
	    else: i0=i; i1=i-1
	    ltopi=segments_indices[edges[2]['name']][i0]
	    lbottomi=segments_indices[edges[2]['name']][i1]
	    compute_tx_c(ltopi); compute_tx_c(lbottomi)
	  if i<=1:
	    if edges[3]['rev']: j0=(self.iters)-j; j1=(self.iters)-(j-1)
	    else: j0=j; j1=j-1
	    lbottomi=segments_indices[edges[3]['name']][j0]
	    rbottomi=segments_indices[edges[3]['name']][j1]
	    compute_tx_c(lbottomi); compute_tx_c(rbottomi)
	  if j<=1:
	    if edges[0]['rev']: i0=(self.iters)-i; i1=(self.iters)-(i-1)
	    else: i0=i; i1=i-1
	    rtopi=segments_indices[edges[0]['name']][i0]
	    rbottomi=segments_indices[edges[0]['name']][i1]
	    compute_tx_c(rtopi); compute_tx_c(rbottomi)
	  if ltopi is None: ltopi=start_n+(i-1)*(self.iters-1)+(j-1)
	  if rtopi is None: rtopi=start_n+(i-1)*(self.iters-1)+(j-2)
	  if lbottomi is None: lbottomi=start_n+(i-2)*(self.iters-1)+(j-1)
	  if rbottomi is None: rbottomi=start_n+(i-2)*(self.iters-1)+(j-2)
	  if surface_desc['ccw']:
	    #dm._indices.append([ltopi,rtopi,rbottomi,lbottomi])
	    dm._indices.append([ltopi,rtopi,lbottomi])
	    dm._indices.append([lbottomi,rtopi,rbottomi])

	  else:
	    #dm._indices.append([lbottomi,rbottomi,rtopi,ltopi])
	    dm._indices.append([lbottomi,rtopi,ltopi])
	    dm._indices.append([rbottomi,rtopi,lbottomi])
	  
	  surface_desc['grid_triangles'].append(dm._indices[-2])
	  surface_desc['grid_triangles'].append(dm._indices[-1])
    dm._generateNormals()
    #for super_knot in super_knots: del locals()[super_knot]
    #for variables_key in variables_keys: del locals()[variables_key]
    return dm

class Prism(Basic):
  def __init__(self,fts,ps,Cs,d,orient,name,dm_displacement=[0,0,0]):#ft0,ft1,ft2,ft3,p0,p1,p2,p3,d,orient):
    #self.version,self.super_knots,self.variables,self.external_vars=0.1,{},{},{}
    segments={}
    knots_table=[{}]
    surfaces={}
    l_last=None
    for i0 in range(len(fts)):
      if i0<len(fts)-1: i1=i0+1
      else: i1=0
      ft=fts[i0]
      Cx=Cs[i0][0]; Cy=Cs[i0][1]; Cz=Cs[i0][2]
      segment_name="l"+str(i0)
      knot0="p"+str(i0); knot1="p"+str(i1)
      p=ps[i0]
      segments[segment_name]={"name":segment_name,"xt":ft[0],"yt":ft[1],"zt":ft[2],"knot0":knot0,"knot1":knot1,"Cx":Cx,"Cy":Cy,"Cz":Cz}
      segments[segment_name+"_"]={"name":segment_name+"_","xt":ft[0],"yt":ft[1],"zt":ft[2],"knot0":knot0+"_","knot1":knot1+"_","Cx":Cx,"Cy":Cy,"Cz":Cz}
      segments[knot0+"-"+knot0+"_"]={"name":knot0+"-"+knot0+"_","xt":"p0+t*(p1-p0)","yt":"p0+t*(p1-p0)","zt":"p0+t*(p1-p0)","knot0":knot0,"knot1":knot0+"_","Cx":["p0","p0","p1","p1"],"Cy":["p0","p0","p1","p1"],"Cz":["p0","p0","p1","p1"]}
      knots_table[-1][knot0]=p
      knots_table[-1][knot0+"_"]=[p[0]+d[0],p[1]+d[1],p[2]+d[2]]
      surfaces['side'+str(i0)]={"segments":[knot0+"-"+knot0+"_",segment_name,knot1+"-"+knot1+"_",segment_name+"_"],"ccw":orient}
      if i0==3 or i0>3 and (i0-2)%3==0:
	orient_=orient
	if not l_last is None: l_first=l_last; orient_=not orient
	else: l_first="l"+str(i0-3)
	if i0==len(fts)-1: l_last="l"+str(i0)
	else: 
	  l_last="l_"+str(i0)
	  segments[l_last]={"name":l_last,"xt":"p0+t*(p1-p0)","yt":"p0+t*(p1-p0)","zt":"p0+t*(p1-p0)","knot0":knot0,"knot1":"p0","Cx":["p0","p0","p1","p1"],"Cy":["p0","p0","p1","p1"],"Cz":["p0","p0","p1","p1"]}
	  segments[l_last+"_"]={"name":l_last,"xt":"p0+t*(p1-p0)","yt":"p0+t*(p1-p0)","zt":"p0+t*(p1-p0)","knot0":knot0+"_","knot1":"p0_","Cx":["p0","p0","p1","p1"],"Cy":["p0","p0","p1","p1"],"Cz":["p0","p0","p1","p1"]}
	  
	surfaces['top'+str(i0-3)]={"segments":[l_first,"l"+str(i0-2),"l"+str(i0-1),l_last],"ccw":orient_}
	surfaces['bottom'+str(i0-3)]={"segments":[l_first+"_","l"+str(i0-2)+"_","l"+str(i0-1)+"_",l_last+"_"],"ccw":not orient_}
    knots_i=0
    Basic.__init__(self,segments=segments,surfaces=surfaces,knots_table=knots_table,name=name,dm_displacement=dm_displacement)
      
    
    
    