# -*- coding: utf-8 -*-
from sage.all import *
from pyel3d_math import *
from pyel3d_prep_model import *
import shutil
import sys
exec open('../../data/models/Woman','r')

class Skirt(PrepModel):
  def __init__(self):
    PrepModel.__init__(self)
    #self.copyFrom(segments,knots,super_knots,variables,surfaces,postfix="",except_postfix="m")

    #self.knots_table=knots
    #self.extra_vars=variables
    #self.super_knots=super_knots
    #self.segments=segments
    self.knots_table=[[]]*len(knots)
    knots_d={"14t":[0.8,0,0],"15t":["-A3_+0.5",0,0],"5t":[0,-0.5,0],"6t":[0,"A5_-0.5",0],"11t":[0,0.5,0],"12t":[0,"-A6_+0.5",0],"10t":[0,0.5,0]}
    for knot_name,d in knots_d.iteritems(): self.super_knots[knot_name]=["parent.knots[\""+knot_name+"\"][0]+"+str(d[0]),"parent.knots[\""+knot_name+"\"][1]+"+str(d[1]),"parent.knots[\""+knot_name+"\"][2]+"+str(d[2]),1,1,1]
    self.super_knots["5t_"]=["0.0","knots[\"5t\"][1]","knots[\"5t\"][2]+BeltWidth",1,1,1]
    self.super_knots["14t_"]=["knots[\"14t\"][0]","0.0","knots[\"14t\"][2]+BeltWidth",1,1,1]
    self.super_knots["11t_"]=["0.0","knots[\"11t\"][1]+(knots[\"10t\"][1]-knots[\"11t\"][1])*BeltWidth/(knots[\"10t\"][2]-knots[\"11t\"][2])","knots[\"11t\"][2]+BeltWidth",1,1,1]
    self.super_knots["7t"]=["0.0","parent.knots[\"6t\"][1]+A5","knots[\"5t\"][2]-A1",1,1,1]
    self.super_knots["15t_0"]=["parent.knots[\"15t\"][0]-A3","0.0","knots[\"5t\"][2]-A1",1,1,1]
    self.super_knots["12t_0"]=["0.0","parent.knots[\"12t\"][1]-A6","knots[\"5t\"][2]-A1",1,1,1]
    
    self.super_knots["7t_"]=["0.0","parent.knots[\"6t\"][1]+A5","knots[\"5t\"][2]-A1-tmp2",1,1,1]
    self.super_knots["15t_0_"]=["parent.knots[\"15t\"][0]-A3","0.0","knots[\"5t\"][2]-A1-tmp2",1,1,1]
    self.super_knots["12t_0_"]=["0.0","parent.knots[\"12t\"][1]-A6","knots[\"5t\"][2]-A1-tmp2",1,1,1]
    
    self.super_knots["7t_1"]=["0.0","parent.knots[\"6t\"][1]+A5_-0.5","(knots[\"5t\"][2]-A1)+A4",1,1,1]
    self.super_knots["15t_1"]=["parent.knots[\"15t\"][0]-A3_+0.5","0.0","(knots[\"5t\"][2]-A1)+A4",1,1,1]    
    self.super_knots["12t_1"]=["0.0","parent.knots[\"12t\"][1]-A6_+0.5","(knots[\"5t\"][2]-A1)+A4",1,1,1]
    
    var("knot_15t_x,knot_15t_y,knot_15t_1_x,knot_15t_1_y,knot_15t_0_x,knot_15t_0_y,knot_15t_z,knot_15t_1_z,knot_15t_0_z,p0,p1")
    def xfrom_line(p0x,p0y,p1x,p1y,py): return p0x+(py-p0y)*(p1x-p0x)/(p1y-p0y)
    self.segments={   
		   "5t_-5t":{"xt":line_3,"yt":curve3_0_x,"zt":curve3_0_y,"knot0":"5t_","knot1":"5t"},
		   "5t-6t":{"xt":line_3,"yt":curve3_0_x,"zt":curve3_0_y,"knot0":"5t","knot1":"6t"},
		   "6t-7t_1":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6t","knot1":"7t_1"},
		   "7t_1-7t":{"xt":line_3_1,"yt":curve3_0_y,"zt":curve3_0_x,"knot0":"7t_1","knot1":"7t"},
		   
		   "11t_-11t":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"11t_","knot1":"11t"},
		   "11t-12t":{"xt":line_3,"yt":curve3_0_x,"zt":curve3_0_y,"knot0":"11t","knot1":"12t"},
		   "12t-12t_1":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"12t","knot1":"12t_1"},
		   "12t_1-12t_0":{"xt":line_3_1,"yt":curve3_0_y,"zt":curve3_0_x,"knot0":"12t_1","knot1":"12t_0"},
		   
		   "14t_-14t":{"xt":line_3,"yt":curve3_0_x,"zt":curve3_0_y,"knot0":"14t_","knot1":"14t"},
		   "14t-15t":{"xt":curve3_3_x,"yt":line_3,"zt":curve3_3_y,"knot0":"14t","knot1":"15t"},
		   
		   "15t-15t_1":{"xt":pseudo_ellipse_y_3,"yt":line_3,"zt":pseudo_ellipse_x_3,"knot0":"15t","knot1":"15t_1"},
		   "15t_1-15t_0":{"xt":pseudo_ellipse_x_3,"yt":line_3,"zt":pseudo_ellipse_y_3,"knot0":"15t_1","knot1":"15t_0"},
		   "15t_0-15t_0_":{"xt":pseudo_ellipse_x_3,"yt":line_3,"zt":pseudo_ellipse_y_3,"knot0":"15t_0","knot1":"15t_0_"},

		   #"15t-15t_1":{"xt":bezier_polynome_3,"yt":line_3,"zt":bezier_polynome_3,"knot0":"15t","knot1":"15t_1",
			        #"Cx":[p0,p0,xfrom_line(knot_15t_x,knot_15t_z,knot_15t_1_x,knot_15t_1_z,knot_15t_z+2.0*(knot_15t_1_z-knot_15t_z)/3.0),p1],
			        #"Cz":[p0,p0+(p1-p0)/3.0,p0+2.0*(p1-p0)/3.0,p1]},
		   #"15t_1-15t_0":{"xt":bezier_polynome_3,"yt":line_3,"zt":bezier_polynome_3,"knot0":"15t_1","knot1":"15t_0",
				  #"Cx":[p0,xfrom_line(knot_15t_1_x,knot_15t_1_z,knot_15t_0_x,knot_15t_0_z-0.01,knot_15t_1_z+(knot_15t_0_z-knot_15t_1_z)/3.0),p0+2.0*(p1-p0)/3.0,p1],
				  #"Cz":[p0,p0+(p1-p0)/3.0,p1,p1]},
		   
		   "14t_-11t_":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"14t_","knot1":"11t_"},
		   "14t-11t":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"14t","knot1":"11t"},
		   "14t_0-11t_0s":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"14t_0","knot1":"11t_0s"},
		   "15t-12t":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"15t","knot1":"12t"},
		   "15t_1-12t_1":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"15t_1","knot1":"12t_1"},
		   "15t_0-12t_0":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"15t_0","knot1":"12t_0"},
		   "12t_0-12t_0_":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"12t_0","knot1":"12t_0_"},
		   
		   "14t_-5t_":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"14t_","knot1":"5t_"},
		   "14t-5t":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"14t","knot1":"5t"},
		   "14t_0-6t":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"14t_0","knot1":"6t"},
		   "15t-6t_0":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"15t","knot1":"6t_0"},
		   "15t_1-7t_1":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"15t_1","knot1":"7t_1"},
		   "15t_0-7t":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"15t_0","knot1":"7t"},
		   "7t-7t_":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"7t","knot1":"7t_"}
		  }
    
    self.surfaces={
		   "a_":{"segments":["5t_-5t","14t_-5t_","14t_-14t","14t-5t"],"ccw":False},
		   "a":{"segments":["5t-6t","14t-5t","14t-14t_0","14t_0-6t"],"ccw":False},
		   "b":{"segments":["6t-6t_0","14t_0-6t","14t_0-15t","15t-6t_0"],"ccw":False},
		   "c":{"segments":["6t_0-7t_1","15t-6t_0","15t-15t_1","15t_1-7t_1"],"ccw":False},
		   "d":{"segments":["7t_1-7t","15t_1-7t_1","15t_1-15t_0","15t_0-7t"],"ccw":False,'cond':"Narrow==1"},

		   "ab_":{"segments":["11t_-11t","14t_-11t_","14t_-14t","14t-11t"],"ccw":True},
		   "ab":{"segments":["11t-11t_0s","14t-11t","14t-14t_0","14t_0-11t_0s"],"ccw":True},
		   "bb":{"segments":["11t_0s-12t","14t_0-11t_0s","14t_0-15t","15t-12t"],"ccw":True},
		   "cb":{"segments":["12t-12t_1","15t-12t","15t-15t_1","15t_1-12t_1"],"ccw":True},
		   "db":{"segments":["12t_1-12t_0","15t_1-12t_1","15t_1-15t_0","15t_0-12t_0"],"ccw":True,'cond':"Narrow==1"},
		  }
		  
    self.divideBezier3Segment("11t-12t","11t-11t_0s","11t_0s-12t","11t_0s")
    self.divideBezier3Segment("14t-15t","14t-14t_0","14t_0-15t","14t_0")
    self.divideBezier3Segment("6t-7t_1","6t-6t_0","6t_0-7t_1","6t_0")
    
    self.mirror_axis_knots=["5t_","5t","6t","6t_0","7t","7t_1","11t_","11t","11t_0s","12t","12t_0","12t_1"]
    self.external_vars=['A1','A3','A3_','A4','A5','A5_','A6','A6_','BeltWidth','Narrow',"tmp0","tmp1","tmp2","tmp3","tmp4","tmp5","tmp6"]

if sys.argv[0]=="generate_skirt.py":
  skirt=Skirt()
  skirt.processKnots()
  skirt.processSegments()
  skirt.finalizeKnots()
  skirt.generateMirroredSide()
  skirt.writeToFile("../../data/models/Skirt")
  shutil.copy("../../data/models/Skirt","../../debug/models/")