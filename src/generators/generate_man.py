# -*- coding: utf-8 -*-
# imports
from sage.all import *
from pyel3d_math import *
from pyel3d_prep_model import *
import shutil
class Man(PrepModel):
  def __init__(self):
    PrepModel.__init__(self)
    def fhv(p0_n,p1_n,i,f=1):
      return "lambda hv: (float(approx_dict['growth']*10.0*self.grid[1])/float(knots_dict['"+str(p0_n)+"'][1]-knots_dict['"+str(p1_n)+"'][1]))*"+"("+str(f)+"*(hv-knots_dict['"+str(p0_n)+"']["+str(i)+"])/(10*self.grid["+str(i)+"]))" 
      
    self.planes={
	  'front':{
		    'knots':['1','2','3','4','5','6','7'],
		    'haxis':'x','vaxis':'z','daxis':'y',
		    'fh':fhv("a0","a1",0),'fv':fhv("a0","a1",1,-1),'fd':"lambda d: d",
		    'defaultd':0.0
		  },
	  'side':{
		    'knots':['8','9','10','11','12','13','14','15','16','17','18','19','20','21','22'],
		    'haxis':'y','vaxis':'z','daxis':'x',
		    'fh':fhv("b0","b1",0),'fv':fhv("b0","b1",1,-1),'fd':"lambda d: d",
		    'defaultd':0.0
		}
    }
    self.loadApproximationData(["./photos/"+str(i)+"/data" for i in range(1,3)])
    self.segments['4-21_22f']={'xt':line_3,'yt':pseudo_ellipse_y_3,'zt':pseudo_ellipse_x_3,'knot0':'4','knot1':'21_22f','u_or_v':'v'}
    self.segments['21_22f-6']={'xt':line_3,'yt':pseudo_ellipse_x_3,'zt':pseudo_ellipse_y_3,'knot0':'21_22f','knot1':'6','u_or_v':'v'}
    self.segments['4-21_22b']={'xt':line_3,'yt':pseudo_ellipse_y_3,'zt':pseudo_ellipse_x_3,'knot0':'4','knot1':'21_22b','u_or_v':'v'}
    self.segments['21_22b-6']={'xt':line_3,'yt':pseudo_ellipse_x_3,'zt':pseudo_ellipse_y_3,'knot0':'21_22b','knot1':'6','u_or_v':'v'}
    self.segments['4-5']={'xt':line,'yt':line,'zt':line,'knot0':'4','knot1':'5','u_or_v':'v'}         
    self.segments["13"]={'xt':line,'yt': line,'zt':line,'knot0':'13','knot1':'13','u_or_v':'v'}
    self.segments["4"]={'xt':line,'yt': line,'zt':line,'knot0':'4','knot1':'4','u_or_v':'u'}
    self.segments["6"]={'xt':line,'yt': line,'zt':line,'knot0':'6','knot1':'6','u_or_v':'u'}
    self.segments["1-8"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'1','knot1':'8','u_or_v':'u'}
    self.segments["2-9"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'2','knot1':'9','u_or_v':'u'}
    self.segments["3-10"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'3','knot1':'10','u_or_v':'u'}
    self.segments["4-11"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'4','knot1':'11','u_or_v':'u'}
    self.segments["1'-14"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'1','knot1':'14','u_or_v':'u'}
    self.segments["2'-15"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'2','knot1':'15','u_or_v':'u'}
    self.segments["3'-16"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'3','knot1':'16','u_or_v':'u'}
    self.segments["4'-17"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'4','knot1':'17','u_or_v':'u'}
    self.segments["6'-19"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'6','knot1':'19','u_or_v':'u'}
    self.segments["7'-20"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'7','knot1':'20','u_or_v':'u'}
    self.segments["6-12_13"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'6','knot1':'12_13','u_or_v':'u'}
    self.segments["7-13"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'7','knot1':'13','u_or_v':'u'}
    self.segments["21_22f-12"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'21_22f','knot1':'12','u_or_v':'u'}
    self.segments["21_22b-18"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'21_22b','knot1':'18','u_or_v':'u'}
    self.segments["5-21_22f"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'5','knot1':'21_22f','u_or_v':'u'}
    self.segments["5-21_22b"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_z_3,'knot0':'5','knot1':'21_22b','u_or_v':'u'}
    
    self.divideBezier3Segment('12-13','12-12_13','12_13-13','12_13')
    self.super_knots['21_22f']=["knots['4'][0]+(knots['6'][0]-knots['4'][0])*((knots['22'][2]+knots['21'][2])/2-knots['4'][2])/(knots['6'][2]-knots['4'][2])","knots['21'][1]","(knots['22'][2]+knots['21'][2])/2",1,1,1]
    self.super_knots['21_22b']=["knots['4'][0]+(knots['6'][0]-knots['4'][0])*((knots['22'][2]+knots['21'][2])/2-knots['4'][2])/(knots['6'][2]-knots['4'][2])","knots['22'][1]","(knots['22'][2]+knots['21'][2])/2",1,1,1]
    
    self.surfaces={
      '1':{'segments':['1-8','8-9','2-9','1-2'],'ccw':False},
      '2':{'segments':['2-9','2-3','3-10','9-10'],'ccw':False},
      '3':{'segments':['3-10','3-4','4-11','10-11'],'ccw':False},
      '4':{'segments':["6-12_13","6-7","12_13-13","7-13"],'ccw':False},
      '5':{'segments':['4-11',"4-21_22f",'11-12','21_22f-12'], 'ccw':False},
      '6':{'segments':['4',"4-5","4-21_22f",'5-21_22f'], 'ccw':True},
      '7':{'segments':['21_22f-12',"21_22f-6",'12-12_13','6-12_13'], 'ccw':False},
      '8':{'segments':['6',"5-6","21_22f-6",'5-21_22f'], 'ccw':False},

      '9':{'segments':["1'-14","2'-15","1-2","14-15"],'ccw':True},
      '10':{'segments':["2'-15","3'-16","2-3","15-16"],'ccw':True},
      '11':{'segments':["3'-16","4'-17","3-4","16-17"],'ccw':True},
      '12':{'segments':["6'-19","6-7",'19-20',"7'-20"],'ccw':True},
      '13':{'segments':["4'-17","4-21_22b",'17-18','21_22b-18'], 'ccw':True},
      '14':{'segments':['4',"4-5","4-21_22b",'5-21_22b'], 'ccw':False},
      '15':{'segments':['21_22b-18',"21_22b-6",'18-19',"6'-19"], 'ccw':True},
      '16':{'segments':['6',"5-6","21_22b-6",'5-21_22b'], 'ccw':True}

    }
    self.mirror_axis_knots=self.planes['side']['knots']
    
man=Man()
man.processSegments()
man.finalizeKnots()
man.generateMirroredSide()
man.writeToFile("../../data/models/Man") #-----------------
shutil.copy("../../data/models/Man","../../debug/models/")