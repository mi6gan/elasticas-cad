# -*- coding: utf-8 -*-
from sage.all import *
from pyel3d_math import *
from pyel3d_prep_model import *
import generate_top
import generate_skirt
import shutil
def joinDicts(to_dict,from_dict,duplicate_keys,duplicate_suffix=None):
  for from_key in from_dict:
    duplicate=None
    for to_key in to_dict.keys()[:]:
      if from_key==to_key: 
	duplicate=from_key
	break
    suffix=""
    if not (duplicate is None):
      duplicate_keys.append(duplicate)
      if not (duplicate_suffix is None): suffix=duplicate_suffix
    if duplicate is None or len(suffix): to_dict[from_key+suffix]=from_dict[from_key]
  
class Dress(PrepModel):
  def __init__(self,silhoutte_type=0):
    PrepModel.__init__(self)
    top=generate_top.Top(silhoutte_type)
    skirt=generate_skirt.Skirt()
    self.external_vars=top.external_vars+skirt.external_vars
    del skirt.surfaces["a_"]; del skirt.surfaces["ab_"]
    self.knots_table=top.knots_table
    self.segments=top.segments
    self.super_knots=top.super_knots
    self.surfaces=top.surfaces
    self.extra_vars=top.extra_vars
    self.mirror_axis_knots=top.mirror_axis_knots
    '''
    duplicate_segments=[]; duplicate_super_knots=[]; duplicate_surfaces=[]; duplicate_extra_vars=[]
    for to_dict,from_dict,duplicate_keys in \
	(self.segments,skirt.segments,duplicate_segments),\
	(self.super_knots,skirt.super_knots,duplicate_super_knots),\
	(self.surfaces,skirt.surfaces,duplicate_surfaces),\
	(self.extra_vars,skirt.extra_vars,duplicate_extra_vars):
	  joinDicts(to_dict,from_dict,duplicate_keys) #,"_s")
	  #print duplicate_keys
    self.super_knots["14t"][0]="knots[\"2r_2\"][0]"
    if silhoutte_type<2:    
      self.createEllipticBezier3Spline("14t_0","6t","6t_1",var("knot_2g_0_x"),left_sname="14t_0-6t_1",right_sname="6t_1-6t")
      self.createEllipticBezier3Spline("15t","6t_0","6t_3",var("knot_2g_0_x"),left_sname="15t-6t_3",right_sname="6t_3-6t_0")
      self.createEllipticBezier3Spline("15t_1","7t_1","7t_2",var("knot_2g_0_x"),left_sname="15t_1-7t_2",right_sname="7t_2-7t_1")
      self.createEllipticBezier3Spline("15t_0","7t","7t_4",var("knot_2g_0_x"),left_sname="15t_0-7t_4",right_sname="7t_4-7t")
      self.createEllipticBezier3Spline("15t_0_","7t_","7t_4_",var("knot_2g_0_x"),left_sname="15t_0_-7t_4_",right_sname="7t_4_-7t_")
    else:
      self.super_knots["6t"][1]="knots[\"5t\"][1]"
      self.super_knots["6t_0"][1]="knots[\"5t\"][1]"
      self.super_knots["7t"][1]="knots[\"5t\"][1]"
      self.super_knots["6t_1"]=["parent.knots[\"2g_0\"][0]","knots[\"6t\"][1]","(knots[\"14t_0\"][2]+knots[\"6t\"][2])/2",1,1,1]
      self.super_knots["6t_3"]=["parent.knots[\"2g_0\"][0]","knots[\"6t_0\"][1]","(knots[\"15t\"][2]+knots[\"6t_0\"][2])/2",1,1,1]
      self.super_knots["7t_2"]=["parent.knots[\"2g_0\"][0]","knots[\"7t_1\"][1]","(knots[\"15t_1\"][2]+knots[\"7t_1\"][2])/2",1,1,1]
      self.super_knots["7t_4"]=["parent.knots[\"2g_0\"][0]","knots[\"7t\"][1]","(knots[\"15t_0\"][2]+knots[\"7t\"][2])/2",1,1,1]
      self.super_knots["7t_4_"]=["parent.knots[\"2g_0\"][0]","knots[\"7t\"][1]","(knots[\"15t_0_\"][2]+knots[\"7t_\"][2])/2",1,1,1]
      self.segments["14t_0-6t_1"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"14t_0","knot1":"6t_1"}
      self.segments["6t_1-6t"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6t_1","knot1":"6t"}
      self.segments["15t-6t_3"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"15t","knot1":"6t_3"}
      self.segments["6t_3-6t_0"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6t_3","knot1":"6t_0"}
      self.segments["15t_1-7t_2"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"15t_1","knot1":"7t_2"}
      self.segments["7t_2-7t_1"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"7t_2","knot1":"7t_1"}
      self.segments["15t_0-7t_4"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"15t_0","knot1":"7t_4"}
      self.segments["7t_4-7t"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"7t_4","knot1":"7t"}
      self.segments["15t_0_-7t_4_"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"15t_0_","knot1":"7t_4_"}
      self.segments["7t_4_-7t_"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"7t_4_","knot1":"7t_"}
    

    self.createEllipticBezier3Spline("14t_0","11t_0s","11t_1s",var("knot_4s_0_x"),left_sname="14t_0-11t_1s",right_sname="11t_1s-11t_0s")
    self.divideBezier3Segment("14t_0-11t_1s","14t_0-11t_2s","11t_2s-11t_1s","11t_2s")
    self.createEllipticBezier3Spline("15t","12t","12t_2",var("knot_4s_0_x"),left_sname="15t-12t_2",right_sname="12t_2-12t")
    self.divideBezier3Segment("15t-12t_2","15t-12t_3","12t_3-12t_2","12t_3")
    self.createEllipticBezier3Spline("15t_1","12t_1","12t_4",var("knot_4s_0_x"),left_sname="15t_1-12t_4",right_sname="12t_4-12t_1")
    self.divideBezier3Segment("15t_1-12t_4","15t_1-12t_5","12t_5-12t_4","12t_5")
    self.createEllipticBezier3Spline("15t_0","12t_0","12t_6",var("knot_4s_0_x"),left_sname="15t_0-12t_6",right_sname="12t_6-12t_0")
    self.divideBezier3Segment("15t_0-12t_6","15t_0-12t_7","12t_7-12t_6","12t_7")
    self.createEllipticBezier3Spline("15t_0_","12t_0_","12t_6_",var("knot_4s_0_x"),left_sname="15t_0_-12t_6_",right_sname="12t_6_-12t_0_")
    self.divideBezier3Segment("15t_0_-12t_6_","15t_0_-12t_7_","12t_7_-12t_6_","12t_7_")
    
    self.segments["5t_1-6t_2"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"5t_1","knot1":"6t_2"}
    self.segments["5t_0-6t_1"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"5t_0","knot1":"6t_1"}
    self.segments["6t_1-6t_3"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6t_1","knot1":"6t_3"}
    self.segments["6t_2-6t_4"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6t_2","knot1":"6t_4"}
    self.segments["6t_3-7t_2"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6t_3","knot1":"7t_2"}
    self.segments["6t_4-7t_3"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6t_4","knot1":"7t_3"}
    self.segments["7t_2-7t_4"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"7t_2","knot1":"7t_4"}
    self.segments["7t_3-7t_5"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"7t_3","knot1":"7t_5"}
    self.segments["7t_4-7t_4_"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"7t_4","knot1":"7t_4_"}
    self.segments["7t_5-7t_5_"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"7t_5","knot1":"7t_5_"}
    self.segments["10t_7-11t_2s"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"10t_7","knot1":"11t_2s"}
    self.segments["11t_0-11t_1s"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"11t_0","knot1":"11t_1s"}
    self.segments["11t_2s-12t_3"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"11t_2s","knot1":"12t_3"}
    self.segments["11t_1s-12t_2"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"11t_1s","knot1":"12t_2"}
    self.segments["12t_3-12t_5"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"12t_3","knot1":"12t_5"}
    self.segments["12t_2-12t_4"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"12t_2","knot1":"12t_4"}
    self.segments["12t_5-12t_7"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"12t_5","knot1":"12t_7"}
    self.segments["12t_4-12t_6"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"12t_4","knot1":"12t_6"}
    self.segments["12t_7-12t_7_"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"12t_7","knot1":"12t_7_"}
    self.segments["12t_6-12t_6_"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"12t_6","knot1":"12t_6_"}

    self.divideBezier3Segment("14t_0-6t_1","14t_0-6t_2","6t_2-6t_1","6t_2")
    self.divideBezier3Segment("15t-6t_3","15t-6t_4","6t_4-6t_3","6t_4")
    self.divideBezier3Segment("15t_1-7t_2","15t_1-7t_3","7t_3-7t_2","7t_3")
    self.divideBezier3Segment("15t_0-7t_4","15t_0-7t_5","7t_5-7t_4","7t_5")
    self.divideBezier3Segment("15t_0_-7t_4_","15t_0_-7t_5_","7t_5_-7t_4_","7t_5_")
    
    #tx_v_0="1.0-(z-knot_5t_z)/(knot_7t_z-knot_5t_z)"
    #tx_u_0="0.5+atan2(x,sqrt((2.0*knot_1r_x)**2-x**2))/(2.0*pi)"
    tx_v_0="0.5*float(z>knot_5t_z)*(1.0-(z-knot_5t_z)/(knot_1s_z-knot_5t_z))+float(z<=knot_5t_z)*(0.5+0.5*(1.0-(z-knot_7t__z)/(knot_5t_z-knot_7t__z)))"
    tx_u_0="(1.0+x/knot_1r_x)/4.0"
    tx_u_1="1.0-(1.0+x/knot_1r_x)/4.0"

    for sname,surface in self.surfaces.iteritems(): 
      if "tx_u" in surface: 
	if len(sname)>=2 and sname[-1]=="b" or sname=="r" or sname=="s": surface["tx_u"]=tx_u_1
	else:  surface["tx_u"]=tx_u_0
      if "tx_v" in surface: surface["tx_v"]=tx_v_0
    
    self.surfaces['a0_s']={'segments':['14t_0-6t_2','14t-14t_0','14t-5t_1','5t_1-6t_2'],'ccw':True,"tx_u":tx_u_0,"tx_v":tx_v_0}
    self.surfaces['a1_s']={'segments':['6t_2-6t_1','5t_1-6t_2','5t_1-5t_0','5t_0-6t_1'],'ccw':True,"tx_u":tx_u_0,"tx_v":tx_v_0}
    self.surfaces['a2_s']={'segments':['6t_1-6t','5t_0-6t_1','5t_0-5t','5t-6t'],'ccw':True,"tx_u":tx_u_0,"tx_v":tx_v_0}
    self.surfaces['b0_s']={'segments':['15t-6t_4','14t_0-15t','14t_0-6t_2','6t_2-6t_4'],'ccw':True,"tx_u":tx_u_0,"tx_v":tx_v_0}
    self.surfaces['b1_s']={'segments':['6t_4-6t_3','6t_2-6t_4','6t_2-6t_1','6t_1-6t_3'],'ccw':True,"tx_u":tx_u_0,"tx_v":tx_v_0}
    self.surfaces['b2_s']={'segments':['6t_3-6t_0','6t_1-6t_3','6t_1-6t','6t-6t_0'],'ccw':True,"tx_u":tx_u_0,"tx_v":tx_v_0}
    self.surfaces['c0_s']={'segments':['15t_1-7t_3','15t-15t_1','15t-6t_4','6t_4-7t_3'],'ccw':True,"tx_u":tx_u_0,"tx_v":tx_v_0}
    self.surfaces['c1_s']={'segments':['7t_3-7t_2','6t_4-7t_3','6t_4-6t_3','6t_3-7t_2'],'ccw':True,"tx_u":tx_u_0,"tx_v":tx_v_0}
    self.surfaces['c2_s']={'segments':['7t_2-7t_1','6t_3-7t_2','6t_3-6t_0','6t_0-7t_1'],'ccw':True,"tx_u":tx_u_0,"tx_v":tx_v_0}
    self.surfaces['d0_s']={'segments':['15t_0-7t_5','15t_1-15t_0','15t_1-7t_3','7t_3-7t_5'],'ccw':True,'cond':"Narrow==1","tx_u":tx_u_0,"tx_v":tx_v_0}
    self.surfaces['d1_s']={'segments':['7t_5-7t_4','7t_3-7t_5','7t_3-7t_2','7t_2-7t_4'],'ccw':True,'cond':"Narrow==1","tx_u":tx_u_0,"tx_v":tx_v_0}
    self.surfaces['d2_s']={'segments':['7t_4-7t','7t_2-7t_4','7t_2-7t_1','7t_1-7t'],'ccw':True,'cond':"Narrow==1","tx_u":tx_u_0,"tx_v":tx_v_0}
    self.surfaces['e0_s']={'segments':['15t_0_-7t_5_','15t_0-15t_0_','15t_0-7t_5','7t_5-7t_5_'],'ccw':True,'cond':"Narrow==1 and tmp2>0.0","tx_u":tx_u_0,"tx_v":tx_v_0}
    self.surfaces['e1_s']={'segments':['7t_5_-7t_4_','7t_5-7t_5_','7t_5-7t_4','7t_4-7t_4_'],'ccw':True,'cond':"Narrow==1 and tmp2>0.0","tx_u":tx_u_0,"tx_v":tx_v_0}
    self.surfaces['e2_s']={'segments':['7t_4_-7t_','7t_4-7t_4_','7t_4-7t','7t-7t_'],'ccw':True,'cond':"Narrow==1 and tmp2>0.0","tx_u":tx_u_0,"tx_v":tx_v_0}
    
    
    self.surfaces['ab0_s']={'segments':['14t_0-11t_2s','14t-14t_0','14t-10t_7','10t_7-11t_2s'],'ccw':False,"tx_u":tx_u_1,"tx_v":tx_v_0}
    self.surfaces['ab1_s']={'segments':['11t_2s-11t_1s','10t_7-11t_2s','10t_7-11t_0','11t_0-11t_1s'],'ccw':False,"tx_u":tx_u_1,"tx_v":tx_v_0}
    self.surfaces['ab2_s']={'segments':['11t_1s-11t_0s','11t_0-11t_1s','11t_0-11t','11t-11t_0s'],'ccw':False,"tx_u":tx_u_1,"tx_v":tx_v_0}
    self.surfaces['bb0_s']={'segments':['15t-12t_3','14t_0-15t','14t_0-11t_2s','11t_2s-12t_3'],'ccw':False,"tx_u":tx_u_1,"tx_v":tx_v_0}
    self.surfaces['bb1_s']={'segments':['12t_3-12t_2','11t_2s-12t_3','11t_2s-11t_1s','11t_1s-12t_2'],'ccw':False,"tx_u":tx_u_1,"tx_v":tx_v_0}
    self.surfaces['bb2_s']={'segments':['12t_2-12t','11t_1s-12t_2','11t_1s-11t_0s','11t_0s-12t'],'ccw':False,"tx_u":tx_u_1,"tx_v":tx_v_0}
    self.surfaces['cb0_s']={'segments':['15t_1-12t_5','15t-15t_1','15t-12t_3','12t_3-12t_5'],'ccw':False,"tx_u":tx_u_1,"tx_v":tx_v_0}
    self.surfaces['cb1_s']={'segments':['12t_5-12t_4','12t_3-12t_5','12t_3-12t_2','12t_2-12t_4'],'ccw':False,"tx_u":tx_u_1,"tx_v":tx_v_0}
    self.surfaces['cb2_s']={'segments':['12t_4-12t_1','12t_2-12t_4','12t_2-12t','12t-12t_1'],'ccw':False,"tx_u":tx_u_1,"tx_v":tx_v_0}
    self.surfaces['db0_s']={'segments':['15t_0-12t_7','15t_1-15t_0','15t_1-12t_5','12t_5-12t_7'],'ccw':False,'cond':"Narrow==1","tx_u":tx_u_1,"tx_v":tx_v_0}
    self.surfaces['db1_s']={'segments':['12t_7-12t_6','12t_5-12t_7','12t_5-12t_4','12t_4-12t_6'],'ccw':False,'cond':"Narrow==1","tx_u":tx_u_1,"tx_v":tx_v_0}
    self.surfaces['db2_s']={'segments':['12t_6-12t_0','12t_4-12t_6','12t_4-12t_1','12t_1-12t_0'],'ccw':False,'cond':"Narrow==1","tx_u":tx_u_1,"tx_v":tx_v_0}
    self.surfaces['eb0_s']={'segments':['15t_0_-12t_7_','15t_0-15t_0_','15t_0-12t_7','12t_7-12t_7_'],'ccw':False,'cond':"Narrow==1 and tmp2>0.0","tx_u":tx_u_1,"tx_v":tx_v_0}
    self.surfaces['eb1_s']={'segments':['12t_7_-12t_6_','12t_7-12t_7_','12t_7-12t_6','12t_6-12t_6_'],'ccw':False,'cond':"Narrow==1 and tmp2>0.0","tx_u":tx_u_1,"tx_v":tx_v_0}
    self.surfaces['eb2_s']={'segments':['12t_6_-12t_0_','12t_6-12t_6_','12t_6-12t_0','12t_0-12t_0_'],'ccw':False,'cond':"Narrow==1 and tmp2>0.0","tx_u":tx_u_1,"tx_v":tx_v_0}

    
    self.mirror_axis_knots+=["5t","6t","6t_0","7t_1","7t","7t_","11t_0s","12t","12t_1","12t_0","12t_0_"]
    '''
    
if sys.argv[0]=="generate_dress.py":
  for i in range(3):
    dress=Dress(i)
    #dress.processKnots()
    dress.processSegments()
    dress.finalizeKnots()
    dress.generateMirroredSide()
    dress.writeToFile("../../data/models/Dress"+str(i))
    shutil.copy("../../data/models/Dress"+str(i),"../../debug/models/")


    
      
    
