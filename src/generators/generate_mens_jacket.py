# -*- coding: utf-8 -*-
from os import environ
from sage.all import *
from pyel3d_math import *
from pyel3d_prep_model import *
import shutil
exec open('../../data/models/Man','r')
class Jacket(PrepModel):
  def __init__(self):
    PrepModel.__init__(self)
    self.segments={}
    self.super_knots=super_knots
    self.knots_table=knots

    var('t,p0,p1')

    def curve_oy_x(P):
      
      f=bezier_polynome_3(function_to_P[curve_oy_x](P))
      return f

    def curve_oy_y(P):
      f=bezier_polynome_3(function_to_P[curve_oy_y](P))
      return f
  
    function_to_P[curve_oy_x]=lambda P: [P[0],P[0],P[-1],P[-1]]
    function_to_P[curve_oy_y]=lambda P: [P[0],P[0]+(P[-1]-P[0])/4.0,P[0]+(P[-1]-P[0])/2.0,P[0]+3.0*(P[-1]-P[0])/4.0,P[-1]]


    self.segments["1j-8j"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_y_3,'knot0':'1j','knot1':'8j','u_or_v':'u'}
    self.segments["3j-10j"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_y_3,'knot0':'3j','knot1':'10j','u_or_v':'u'}
    self.segments["4j-12j"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_y_3,'knot0':'4j','knot1':'12j','u_or_v':'u'}
    self.segments["21_22f-12j"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_y_3,'knot0':'21_22f','knot1':'12j','u_or_v':'u'}
    self.segments["21_22f_-21_22f"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_y_3,'knot0':'21_22f_','knot1':'21_22f','u_or_v':'u'}
    self.segments["6j-13j"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_y_3,'knot0':'6j','knot1':'13j','u_or_v':'u'}
    self.segments["7j-13j"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_y_3,'knot0':'7j','knot1':'13j','u_or_v':'u'}
    self.segments["1j-14j"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_y_3,'knot0':'1j','knot1':'14j','u_or_v':'u'}
    self.segments["3j-16j"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_y_3,'knot0':'3j','knot1':'16j','u_or_v':'u'}
    self.segments["4j-16j"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_y_3,'knot0':'4j','knot1':'16j','u_or_v':'u'}
    self.segments["4j"]={'xt':line,'yt':line,'zt':line,'knot0':'4j','knot1':'4j','u_or_v':'u'}
    self.segments["21_22b-18"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_y_3,'knot0':'21_22b','knot1':'18','u_or_v':'u'}
    self.segments["21_22b_-21_22b"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_y_3,'knot0':'21_22b_','knot1':'21_22b','u_or_v':'u'}
    self.segments["6j-19"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_y_3,'knot0':'6j','knot1':'19','u_or_v':'u'}
    self.segments["7j-20"]={'xt':pseudo_ellipse_x_3,'yt': pseudo_ellipse_y_3,'zt':pseudo_ellipse_y_3,'knot0':'7j','knot1':'20','u_or_v':'u'}

    self.segments["8j-10j"]={'xt':line,'yt':curve_oy_x,'zt':curve_oy_y,'knot0':'8j','knot1':'10j','u_or_v':'v'}
    self.segments["10j-12j"]={'xt':line,'yt':curve_oy_x,'zt':curve_oy_y,'knot0':'10j','knot1':'12j','u_or_v':'v'}
    self.segments["12j"]={'xt':line,'yt':line,'zt':line,'knot0':'12j','knot1':'12j','u_or_v':'v'}
    self.segments["12j-13j"]={'xt':line,'yt':line,'zt':line,'knot0':'12j','knot1':'13j','u_or_v':'v'}
    self.segments["13j"]={'xt':line,'yt':line,'zt':line,'knot0':'13j','knot1':'13j','u_or_v':'v'}
          
    self.segments["14j-16j"]={'xt':line,'yt':curve_oy_x,'zt':curve_oy_y,'knot0':'14j','knot1':'16j','u_or_v':'v'}
    self.segments["16j"]={'xt':line,'yt':line,'zt':line,'knot0':'16j','knot1':'16j','u_or_v':'v'}
    self.segments["16j-18"]={'xt':line,'yt':curve_oy_x,'zt':curve_oy_y,'knot0':'16j','knot1':'18','u_or_v':'v'}
          
    self.segments["1j-3j"]={'xt':line,'yt':curve_oy_x,'zt':curve_oy_y,'knot0':'1j','knot1':'3j','u_or_v':'v'}
    self.segments["3j-4j"]={'xt':line,'yt':curve_oy_x,'zt':curve_oy_y,'knot0':'3j','knot1':'4j','u_or_v':'v'}
    self.segments["4j-21_22f"]={'xt':line,'yt':pseudo_ellipse_y_3,'zt':pseudo_ellipse_x_3,'knot0':'4j','knot1':'21_22f','u_or_v':'v'}
    self.segments["4j-21_22f_"]={'xt':line,'yt':pseudo_ellipse_y_3,'zt':pseudo_ellipse_x_3,'knot0':'4j','knot1':'21_22f_','u_or_v':'v'}
    self.segments["21_22f-6j"]={'xt':line,'yt':pseudo_ellipse_x_3,'zt':pseudo_ellipse_y_3,'knot0':'21_22f','knot1':'6j','u_or_v':'v'}
    self.segments["21_22f_-5j"]={'xt':line,'yt':pseudo_ellipse_x_3,'zt':pseudo_ellipse_y_3,'knot0':'21_22f_','knot1':'5j','u_or_v':'v'}
    self.segments["4j-21_22b"]={'xt':line,'yt':pseudo_ellipse_y_3,'zt':pseudo_ellipse_x_3,'knot0':'4j','knot1':'21_22b','u_or_v':'v'}
    self.segments["4j-21_22b_"]={'xt':line,'yt':pseudo_ellipse_y_3,'zt':pseudo_ellipse_x_3,'knot0':'4j','knot1':'21_22b_','u_or_v':'v'}
    self.segments["21_22b-6j"]={'xt':line,'yt':pseudo_ellipse_x_3,'zt':pseudo_ellipse_y_3,'knot0':'21_22b','knot1':'6j','u_or_v':'v'}
    self.segments["21_22b_-5j"]={'xt':line,'yt':pseudo_ellipse_x_3,'zt':pseudo_ellipse_y_3,'knot0':'21_22b_','knot1':'5j','u_or_v':'v'}
    self.segments["5j-6j"]={'xt':line,'yt':line,'zt':line,'knot0':'5j','knot1':'6j','u_or_v':'v'}
    self.segments["6j-7j"]={'xt':line,'yt':line,'zt':line,'knot0':'6j','knot1':'7j','u_or_v':'v'}

    #changeSegmentPos(self.segments["18-19"],[0.0,-0.3,0.0],knots,change_knot0=True,change_knot1=True)
    #changeSegmentPos(self.segments["19-20"],[0.0,-0.3,0.0],knots,change_knot0=False,change_knot1=True)

    self.super_knots['21_22f']=["knots['4'][0]+(knots['6'][0]-knots['4'][0])*((knots['22'][2]+knots['21'][2])/2-knots['4'][2])/(knots['6'][2]-knots['4'][2])+0.2","knots['21'][1]","(knots['22'][2]+knots['21'][2])/2",1,1,1]
    self.super_knots['21_22b']=["knots['4'][0]+(knots['6'][0]-knots['4'][0])*((knots['22'][2]+knots['21'][2])/2-knots['4'][2])/(knots['6'][2]-knots['4'][2])+0.2","knots['22'][1]","(knots['22'][2]+knots['21'][2])/2",1,1,1]
    self.super_knots['21_22f_']=["knots['4'][0]+(knots['5'][0]-knots['4'][0])*((knots['22'][2]+knots['21'][2])/2-knots['4'][2])/(knots['5'][2]-knots['4'][2])+0.2","knots['21'][1]","(knots['22'][2]+knots['21'][2])/2",1,1,1]
    self.super_knots['21_22b_']=["knots['4'][0]+(knots['5'][0]-knots['4'][0])*((knots['22'][2]+knots['21'][2])/2-knots['4'][2])/(knots['5'][2]-knots['4'][2])+0.2","knots['22'][1]","(knots['22'][2]+knots['21'][2])/2",1,1,1]

    self.super_knots['8j']=["knots['8'][0]","knots['8'][1]+2.2","knots['8'][2]",1,1,1]
    self.super_knots['10j']=["knots['10'][0]","knots['10'][1]+1.6","knots['10'][2]",1,1,1]
    self.super_knots['12j']=["knots['12'][0]","knots['12'][1]+1.0","knots['12'][2]",1,1,1]
    self.super_knots['13j']=["knots['13'][0]","knots['13'][1]+1.3","knots['13'][2]",1,1,1]
    self.super_knots['1j']=["knots['1'][0]+2.5","knots['1'][1]","knots['1'][2]",1,1,1]
    self.super_knots['3j']=["knots['3'][0]+2.4","knots['3'][1]","knots['3'][2]",1,1,1]
    self.super_knots['4j']=["knots['4'][0]+1.6","knots['4'][1]","knots['4'][2]",1,1,1]
    self.super_knots['5j']=["knots['5'][0]+0.5","knots['5'][1]","knots['5'][2]+1.5",1,1,1]
    self.super_knots['6j']=["knots['6'][0]+0.5","knots['6'][1]","knots['6'][2]+1.0",1,1,1]
    self.super_knots['7j']=["knots['7'][0]+0.5","knots['7'][1]","knots['7'][2]+1.0",1,1,1]
    self.super_knots['14j']=["knots['14'][0]","knots['14'][1]-2.6","knots['8'][2]",1,1,1]
    self.super_knots['16j']=["knots['16'][0]","knots['16'][1]-5.0","knots['16'][2]",1,1,1]
#super_knots['18']=["knots['18'][0]","knots['18'][1]-0.1","knots['18'][2]",1,1,1]
#super_knots['19']=["knots['19'][0]","knots['19'][1]-0.1","knots['19'][2]",1,1,1]
#super_knots['20']=["knots['20'][0]","knots['20'][1]-0.1","knots['20'][2]",1,1,1]

    self.surfaces={
      '1':{'segments':['1j-8j','8j-10j','3j-10j','1j-3j'],'ccw':False},
      '2':{'segments':[ '3j-10j','10j-12j','4j-12j','3j-4j'],'ccw':False},
      '3':{'segments':[ '4j-12j',"12j","21_22f-12j","4j-21_22f"],'ccw':False},
      '4':{'segments':[ "4j",'4j-21_22f',"21_22f_-21_22f","4j-21_22f_"],'ccw':False},
      '5':{'segments':[ "21_22f-12j","21_22f-6j","6j-13j","12j-13j"],'ccw':False},
      '6':{'segments':["21_22f_-21_22f","21_22f-6j","5j-6j","21_22f_-5j"],'ccw':False},
      '7':{'segments':["6j-13j","13j","7j-13j","6j-7j"],'ccw':False},
  
      '8':{'segments':["1j-14j","14j-16j","3j-16j","1j-3j"],'ccw':True},
      '9':{'segments':["3j-16j","16j","4j-16j","3j-4j"],'ccw':True},
      '10':{'segments':["4j-16j","16j-18","21_22b-18","4j-21_22b"],'ccw':True},
      '11':{'segments':["4j","4j-21_22b","21_22b_-21_22b","4j-21_22b_"],'ccw':True},
      #{'segments':["21_22b-18","18-19","6j-19","21_22b-6j"],'ccw':True},
      '12':{'segments':["21_22b_-21_22b","21_22b-6j","5j-6j","21_22b_-5j"],'ccw':True},
      #{'segments':["6j-19","19-20","7j-20","6j-7j"],'ccw':True}
    }

    self.mirror_axis_knots=side_knots=['1j','3j','4j','6j','8j','10j','12j','13j','14j','16j','18','19','20']

import generate_dummy
human=generate_dummy.Human(is_woman=False)
human.processSegments()
human.finalizeKnots()
human.pythonizeExpressions()

jacket=Jacket()
jacket.processSegments()
jacket.finalizeKnots()
jacket.show_model_data(human)
jacket.writeToFile("../../data/models/MensJacket")
shutil.copy("../../data/models/MensJacket","../../debug/models/")
