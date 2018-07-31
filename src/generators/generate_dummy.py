# -*- coding: utf-8 -*-
from sage.all import *
from pyel3d_math import *
from pyel3d_prep_model import *
import shutil
import sys
#exec open('../../data/models/Woman','r')
class Human(PrepModel):
  def __init__(self,is_woman=True,just_gen_table=False):
    var('p0,p1,t')
    var('knot_8t_z,knot_8t_x,knot_1r_2_z,knot_1r_2_x,knot_4s_0_x,knot_8t_y,knot_1r_2_y,knot_4s_0_y')
    PrepModel.__init__(self)
    def xfrom_line(p0x,p0y,p1x,p1y,py): return p0x+(py-p0y)*(p1x-p0x)/(p1y-p0y)
    
    def fhv_arm(p0_n,p1_n,i,f=1):
      return "lambda hv: "+str(f)+"*((hv - knots_dict['"+str(p0_n)+"']["+str(i)+"])*float(approx_dict['growth'])/float(knots_dict['"+str(p0_n)+"'][1]-knots_dict['"+str(p1_n)+"'][1]))/((approx_dict['img_size'][1]/2.0-o_knots_dict['1r'][1])/(approx_dict['img_size'][1]/2.0-o_knots_dict[\"1r'\"][1]))*(sys.stdout.write(str((approx_dict['img_size'][1]/2.0-o_knots_dict['1r'][1])/(approx_dict['img_size'][1]/2.0-o_knots_dict[\"1r'\"][1]))+\"\\n\")==None)"
      
    def fhv(p0_n,p1_n,i,f=1):
      return "lambda hv: "+str(f)+"*(hv - knots_dict['"+str(p0_n)+"']["+str(i)+"])*float(approx_dict['growth'])/float(knots_dict['"+str(p0_n)+"'][1]-knots_dict['"+str(p1_n)+"'][1])"

    self.planes={
	  'super':{
		    'knots':["a0","a1","b0","b1","1r","1r'"]
		  },
	  'front':{
		    'knots':["3s''","4s''","13t","14t","14t_0","15t"],
		    'haxis':'x','vaxis':'z','daxis':'y',
		    'fh':fhv("a0","a1",0),'fv':fhv("a0","a1",1,-1),'fd':"lambda d: d",
		    'defaultd':0.0
		  },
	  'side':{
		    'knots':['7t','6t','5t','4t','3g','2g','1g','2s','1s','12t','11t','10t','9t','8t','4s','3s'],
		    'haxis':'y','vaxis':'z','daxis':'x',
		    'fh':fhv("b0","b1",0),'fv':fhv("b0","b1",1,-1),'fd':"lambda d: d",
		    'defaultd':0.0
		},
	  'front_arm':{
		    'knots':["1r","11r","2''r","6r","5r","2r","3r","4r"],
		    'haxis':'x','vaxis':'z','daxis':'y',
		    'fh':fhv("a0","a1",0),'fv':fhv("a0","a1",1,-1),'fd':"lambda d: d",
		    'defaultd':0.0
		  },
	  'side_arm':{
		    'knots':["1r'","2r'","3r'","7r'","10r'","9r'","8r'"],
		    'haxis':'y','vaxis':'z','daxis':'x',
		    #'fh':fhv("b0","b1",0),'fv':fhv("b0","b1",1,-1),'fd':"lambda d: d",
		    'fh':fhv("b0","b1",0),'fv':fhv("b0","b1",1,-1),'fd':"lambda d: d",
		    'defaultd':0.0
		},
    }
    if is_woman: self.loadApproximationData(["./photos/women/body/data"],approximate_segments=False)
    else: 
      files=[]
      #for i in (12,17,18,19,20,21,22,23,24): files.append("./photos/"+str(i)+"/data")
      for i in (17,): files.append("./photos/"+str(i)+"/data")
      self.loadApproximationData(files,approximate_segments=True)
    if just_gen_table: return
    
    #self.approx_data[-1]['approx_segments']=[]
  
    #self.super_knots["10r''"]=["knots[\"2r_0\"][0]","knots[\"10r'\"][1]","knots[\"10r'\"][2]",1,1,1]
    #self.super_knots["3g"]=["0.0","knots[\"5t\"][1]+(knots[\"13t\"][2]-knots[\"5t\"][2])*(knots[\"2g\"][1]-knots[\"5t\"][1])/(knots[\"2g\"][2]-knots[\"5t\"][2])","knots[\"13t\"][2]",1,1,1]
    #self.super_knots["4t"]=["0.0","knots[\"5t\"][1]+(knots[\"13t_0\"][2]-knots[\"5t\"][2])*(knots[\"2g\"][1]-knots[\"5t\"][1])/(knots[\"2g\"][2]-knots[\"5t\"][2])","knots[\"13t_0\"][2]",1,1,1]
    #self.super_knots["2g_"]=["knots['2g'][0]","knots['2g'][1]","knots['1g'][2]+(knots['2g'][2]-knots['1g'][2])/3.0",1,1,1]
    self.super_knots["10t_0"]=["knots[\"9t_0\"][0]","knots[\"10t\"][1]","knots[\"10t\"][2]",1,1,1]
    #self.super_knots["10t_1"]=["0.0","knots[\"10t\"][1]+(knots[\"13t\"][2]-knots[\"10t\"][2])*(knots[\"11t\"][1]-knots[\"10t\"][1])/(knots[\"11t\"][2]-knots[\"10t\"][2])", "knots[\"13t\"][2]",1,1,1]
    self.super_knots["10t_1"]=["0.0","knots[\"10t\"][1]+((knots[\"10t\"][2]+knots[\"10t_2\"][2])/2.0-knots[\"10t\"][2])*(knots[\"11t\"][1]-knots[\"10t\"][1])/(knots[\"11t\"][2]-knots[\"10t\"][2])", "(knots[\"10t\"][2]+knots[\"10t_2\"][2])/2.0",1,1,1]
    self.super_knots["10t_2"]=["0.0","knots[\"10t\"][1]+(knots[\"13t_0\"][2]-knots[\"10t\"][2])*(knots[\"11t\"][1]-knots[\"10t\"][1])/(knots[\"11t\"][2]-knots[\"10t\"][2])", "knots[\"13t_0\"][2]",1,1,1]
    #self.super_knots["1g"]=["0.0","knots[\"2g\"][1]+(self.bearing_model.knots[\"1g\"][2]-knots[\"2g\"][2])*(knots[\"2s\"][1]-knots[\"2g\"][1])/(knots[\"2s\"][2]-knots[\"2g\"][2])","self.bearing_model.knots[\"1g\"][2]",1,1,1]
    
    self.super_knots['2r_0']=["knots['2r'][0]","knots[\"2r'\"][1]","knots[\"2r'\"][2]",1,1,1]
    self.super_knots["2r_3"]=["knots[\"3r'\"][0]","knots[\"3r'\"][1]","knots[\"2r_2\"][2]",1,1,1]
    self.super_knots["2r_8"]=["knots[\"9r'\"][0]","knots[\"9r'\"][1]+(knots[\"2r_2\"][2]-knots[\"9r'\"][2])*(knots[\"10r'\"][1]-knots[\"9r'\"][1])/(knots[\"10r'\"][2]-knots[\"9r'\"][2])","knots[\"2r_2\"][2]",1,1,1]
    self.super_knots["2r_5"]=["knots[\"6r\"][0]","knots[\"6r\"][1]","knots[\"2r_2\"][2]",1,1,1]
    self.super_knots["13t_0"]=["knots[\"13t_2\"][0]","knots[\"13t_2\"][1]","knots[\"13t_2\"][2]",1,1,1]
        
    for to,from1,from2 in ("7r'","4r","5r"),("8r'","4r","5r"),("9r'","4r","5r"),("3r'","3r","6r"),("9r'","3r","6r"),("2r'","2r","2''r"): 
      self.super_knots[to]=["(src_knots[\""+from1+"\"][0]+src_knots[\""+from2+"\"][0])/2.0","src_knots[\""+to+"\"][1]","src_knots[\""+to+"\"][2]",1,1,1]
    for to,from1,from2 in ("4r","7r'","8r'"),("5r","7r'","8r'"),("3r","3r'","9r'"),("6r","3r'","9r'"),("11r","2r'","10r'"),("2''r","2r'","10r'"): #,("3s'","4s","1s"): 
      self.super_knots[to]=["src_knots[\""+to+"\"][0]","(src_knots[\""+from1+"\"][1]+src_knots[\""+from2+"\"][1])/2.0","src_knots[\""+to+"\"][2]",1,1,1]
    self.super_knots["1r"]=["src_knots[\"1r\"][0]","src_knots[\"1r'\"][1]","src_knots[\"1r\"][2]",1,1,1]
    self.super_knots["1r'"]=["src_knots[\"1r\"][0]","src_knots[\"1r'\"][1]","src_knots[\"1r'\"][2]",1,1,1]
    self.super_knots["10r'"]=["src_knots[\"2r\"][0]","src_knots[\"10r'\"][1]","src_knots[\"10r'\"][2]",1,1,1]
    
    self.super_knots["4r"][2]="knots[\"7r'\"][2]+("+self.super_knots["4r"][1]+"-knots[\"7r'\"][1])*(knots[\"8r'\"][2]-knots[\"7r'\"][2])/(knots[\"8r'\"][1]-knots[\"7r'\"][1])"

    self.super_knots["5r"][2]="knots[\"7r'\"][2]+("+self.super_knots["5r"][1]+"-knots[\"7r'\"][1])*(knots[\"8r'\"][2]-knots[\"7r'\"][2])/(knots[\"8r'\"][1]-knots[\"7r'\"][1])"
    
    def xfrom_line(p0x,p0y,p1x,p1y,py): return p0x+(py-p0y)*(p1x-p0x)/(p1y-p0y)
    self.segments={		   
		   "2s_0-1g_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2s_0","knot1":"1g_0"},
		   "1r-2r_0":{"xt":line_3,"yt":pseudo_ellipse_y_3,"zt":pseudo_ellipse_x_3,"knot0":"1r","knot1":"2r_0"},
		   "1r_0-2s_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"1r_0","knot1":"2s_0"}, 
		   		   
		   "2r_0-2r_2":{"xt":line_3,"yt":pseudo_ellipse_x_3,"zt":pseudo_ellipse_y_3,"knot0":"2r_0","knot1":"2r_2"},
		   
		   "2r_2-13t":{"xt":curve3_5_x,"yt":line_3,"zt":curve3_2_y,"knot0":"2r_2","knot1":"13t"},
		   
		   "2g_0-3g_0":{"xt":line_3,"yt":curve3_5_x,"zt":curve3_2_y,"knot1":"2g_0","knot0":"3g_0"},
		   "2g_-3g":{"xt":line_3,"yt":curve3_5_x,"zt":curve3_2_y,"knot1":"2g_","knot0":"3g"},
		   
		   "13t-14t":{"xt":curve3_1_x,"yt":line_3_1,"zt":curve3_1_y,"knot0":"13t","knot1":"14t"},
		   
		   "3g_0-4t_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"3g_0","knot1":"4t_0"},
		   "3g-4t":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"3g","knot1":"4t"},
		   
		   "4t_0-5t_0":{"xt":line_3_1,"yt":curve3_2_x,"zt":curve3_2_y,"knot0":"4t_0","knot1":"5t_0"},
		   "4t-5t":{"xt":line_3,"yt":curve3_2_x,"zt":curve3_2_y,"knot0":"4t","knot1":"5t"},
		   
		   "2r_1-2g_0":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"2r_1","knot1":"2g_0"},
		   "2g_0-2g_":{"xt":curve3_3_y,"yt":curve3_3_x,"zt":line_3,"knot1":"2g_0","knot0":"2g_"},
		   
		   "1g_0-2g_0":{"xt":line_3,"yt":curve3_5_x,"zt":curve3_2_y,"knot0":"1g_0","knot1":"2g_0"},
		   
		   "10t-11t":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"10t","knot1":"11t"}, 
		   
		   "4s''-1r":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"4s''","knot1":"1r"},
		   
		   "8t_0-9t_0":{"xt":line_3,"yt":curve3_5_x,"zt":curve3_2_y,"knot0":"8t_0","knot1":"9t_0"},
		   
		   "4s-8t":{"xt":line_3,"yt":bezier_polynome_3,"zt":bezier_polynome_3,"knot0":"4s","knot1":"8t",
			    "Cy":[p0,p0+(p1-p0)/3.0,xfrom_line(var("knot_8t_y"),var("knot_8t_z"),var("knot_9t_y"),var("knot_9t_z"),var("knot_4s_z")+2.0*(var("knot_8t_z")-var("knot_4s_z"))/3.0),p1],
			    "Cz":[p0,p0+(p1-p0)/3.0,p0+2.0*(p1-p0)/3.0,p1]},  
			     
			    
		   "4s_0-8t_0":{"xt":line_3,"yt":bezier_polynome_3,"zt":bezier_polynome_3,"knot0":"4s_0","knot1":"8t_0",
			    "Cy":[p0,p0+(p1-p0)/3.0,xfrom_line(var("knot_8t_0_y"),var("knot_8t_0_z"),var("knot_9t_0_y"),var("knot_9t_0_z"),var("knot_4s_0_z")+2.0*(var("knot_8t_0_z")-var("knot_4s_0_z"))/3.0),p1],
			    "Cz":[p0,p0,p0+2.0*(p1-p0)/3.0,p1]},
		   
		   "8t-9t":{"xt":line_3,"yt":curve3_5_x,"zt":curve3_2_y,"knot0":"8t","knot1":"9t"},
		   "9t_0-10t_0":{"xt":line_3,"yt":bezier_polynome_3,"zt":bezier_polynome_3,"knot0":"9t_0","knot1":"10t_0",
			     "Cy":[p0,p0,xfrom_line(var("knot_10t_0_y"),var("knot_10t_0_z"),var("knot_11t_0_y"),var("knot_11t_0_z"),var('knot_10t_0_z')+(var('knot_9t_0_z')-var('knot_10t_0_z'))/4.0),p1],
			     "Cz":[p0,p0+(p1-p0)/4.0,p1+(p0-p1)/4.0,p1]},
		   "9t-10t":{"xt":line_3,"yt":bezier_polynome_3,"zt":bezier_polynome_3,"knot0":"9t","knot1":"10t",
			     "Cy":[p0,p0,xfrom_line(var("knot_10t_y"),var("knot_10t_z"),var("knot_11t_y"),var("knot_11t_z"),var('knot_10t_z')+(var('knot_9t_z')-var('knot_10t_z'))/4.0),p1],
			     "Cz":[p0,p0+(p1-p0)/4.0,p1+(p0-p1)/4.0,p1]},

		   "10t_0-10t_3":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"10t_0","knot1":"10t_3"},
		   "10t-10t_1":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"10t","knot1":"10t_1"},
		   
		   "10t_3-10t_4":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"10t_3","knot1":"10t_4"},
		   "10t_1-10t_2":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"10t_1","knot1":"10t_2"},

		   "10t_4-11t_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"10t_4","knot1":"11t_0"},
		   "10t_2-11t":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"10t_2","knot1":"11t"},

		   "1r_1-4s_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"1r_1","knot1":"4s_0"},
		   
		   "10r'_0-10t_5":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"10r'_0","knot1":"10t_5"},
		   "10t_5-10t_6":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"10t_5","knot1":"10t_6"},
		   "10t_6-10t_7":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"10t_6","knot1":"10t_7"},

		   "2r_1-3g_1":{"xt":line_3,"yt":curve3_1_x,"zt":curve3_1_y,"knot0":"2r_1","knot1":"3g_1"},
		   "3g_1-4t_1":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"3g_1","knot1":"4t_1"},
		   "4t_1-5t_1":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"4t_1","knot1":"5t_1"},
		   
		   "2r_2-3r":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2r_2","knot1":"3r"},
		   "2r_3-3r'":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2r_3","knot1":"3r'"},
		   "2r_4-6r_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2r_4","knot1":"6r_0"},
		   "2r_5-6r":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2r_5","knot1":"6r"},
		   
		   "3r-4r":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"3r","knot1":"4r"},
		   "3r'-7r'":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"3r'","knot1":"7r'"},
		   "6r_0-5r_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6r_0","knot1":"5r_0"},
		   "6r-5r":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6r","knot1":"5r"},
		   
		   "2r_7-6r_2":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2r_7","knot1":"6r_2"},
		   "2r_6-6r_1":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2r_6","knot1":"6r_1"},
		   "2r-13t":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2r","knot1":"13t"},
		   
		   "6r_2-5r_2":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6r_2","knot1":"5r_2"},
		   "6r_1-5r_1":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6r_1","knot1":"5r_1"},
		   
		   
		   "10r'-2r_8":{"xt":pseudo_ellipse_y_3,"yt":line_3_1,"zt":pseudo_ellipse_x_3,"knot0":"10r'","knot1":"2r_8"},
		   "1r_2-2r_7":{"xt":pseudo_ellipse_y_3,"yt":line_3_1,"zt":pseudo_ellipse_x_3,"knot0":"1r_2","knot1":"2r_7"},
		   "1r_1-2r_6":{"xt":pseudo_ellipse_y_3,"yt":line_3_1,"zt":pseudo_ellipse_x_3,"knot0":"1r_1","knot1":"2r_6"},
		   
		   
		   "2r_5-2r_8":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3_1,"knot0":"2r_5","knot1":"2r_8"},
		   "6r-9r'":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3_1,"knot0":"6r","knot1":"9r'"},
		   "5r-8r'":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3_1,"knot0":"5r","knot1":"8r'"},
		   
		   "2r_8-9r'":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2r_8","knot1":"9r'"},
		   
		   "9r'-8r'":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"9r'","knot1":"8r'"},
		   
		   
		   "1r-6r":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"1r","knot1":"6r"},
		   "1r_0-6r_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"1r_0","knot1":"6r_0"},
		   
		   "2r_0-2r_3":{"xt":pseudo_ellipse_y_3,"yt":line_3_1,"zt":pseudo_ellipse_x_3,"knot0":"2r_0","knot1":"2r_3"},

		   "10r'-2r_2":{"xt":line_3,"yt":pseudo_ellipse_x_3,"zt":pseudo_ellipse_y_3,"knot0":"10r'","knot1":"2r_2"},   
		   
		   "2r_0-1g_0":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"2r_0","knot1":"1g_0"},
		   "1g_0-1g":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"1g_0","knot1":"1g"},
		   
		   "1r_0-2r_4":{"xt":pseudo_ellipse_y_3,"yt":line_3_1,"zt":pseudo_ellipse_x_3,"knot0":"1r_0","knot1":"2r_4"},
		   "1r-2r_5":{"xt":pseudo_ellipse_y_3,"yt":line_3_1,"zt":pseudo_ellipse_x_3,"knot0":"1r","knot1":"2r_5"},
		   
		   "4s''-2s":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"4s''","knot1":"2s"},
		   "4s''-4s":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"4s''","knot1":"4s"},
		   
		   "1r_2-8t":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"1r_2","knot1":"8t"},
		   "3s''-1s":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"3s''","knot1":"1s"},
		   "3s''-3s":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"3s''","knot1":"3s"},
		   
		   "2r_5-2r_3":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"2r_5","knot1":"2r_3"},
		   "2r_2-2r_3":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"2r_2","knot1":"2r_3"},
		   "3r-3r'":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"3r","knot1":"3r'"},
		   "6r-3r'":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"6r","knot1":"3r'"},
		   "5r-7r'":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"5r","knot1":"7r'"},
		   "4r-7r'":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"4r","knot1":"7r'"},
		   
		   "2r_2-2r_8":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"2r_2","knot1":"2r_8"},
		   
		   "3r-9r'":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"3r","knot1":"9r'"},
		   
		   "4r-8r'":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"4r","knot1":"8r'"},
		   
		   "1s-2s":{'xt':line_3_1,'yt':line_3_1,'zt':line_3_1,'knot0':"2s","knot1":"1s"},
		   "1s_0-2s_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"1s_0","knot1":"2s_0"},
		   "3s''-4s''":{'xt':line_3_1,'yt':line_3_1,'zt':line_3_1,'knot0':"4s''","knot1":"3s''"},
		   "3s_0-4s_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"3s_0","knot1":"4s_0"},
		   "3s-4s":{'xt':line_3_1,'yt':line_3_1,'zt':line_3_1,'knot0':"4s","knot1":"3s"},
		   
		   "5t-6t":{"xt":line_3,"yt":curve3_3_x,"zt":curve3_3_y,"knot0":"5t","knot1":"6t"},
		   "5t_1-6t_2":{"xt":line_3_1,"yt":curve3_1_x,"zt":curve3_1_y,"knot0":"5t_1","knot1":"6t_2"},
		   "5t_0-6t_1":{"xt":line_3_1,"yt":curve3_1_x,"zt":curve3_1_y,"knot0":"5t_0","knot1":"6t_1"},
		   
		   "6t-7t":{"xt":line_3_1,"yt":curve3_3_x,"zt":curve3_3_y,"knot1":"6t","knot0":"7t"},
		   "6t_1-6t_3":{"xt":line_3_1,"yt":curve3_3_x,"zt":curve3_3_y,"knot1":"6t_1","knot0":"6t_3"},
		   "6t_2-6t_4":{"xt":line_3_1,"yt":curve3_3_x,"zt":curve3_3_y,"knot1":"6t_2","knot0":"6t_4"},
		   

		   
		   "11t-12t":{"xt":line_3,"yt":line_3_1,"zt":line_3_1,"knot0":"11t","knot1":"12t"},
		   "10t_7-11t_2s":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"10t_7","knot1":"11t_2s"},
		   "11t_0-11t_1s":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"11t_0","knot1":"11t_1s"},
		   "11t_2s-12t_3":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"11t_2s","knot1":"12t_3"},
		   "11t_1s-12t_2":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"11t_1s","knot1":"12t_2"},

		   
		   "14t-15t":{"xt":curve3_3_x,"yt":line_3,"zt":curve3_3_y,"knot0":"14t","knot1":"15t"},
		   



		   
		  }
      
    
    self.surfaces={
		   #"o":{"segments":["1s_0-1s","1s_0-2s_0","2s_0-2s","1s-2s"],"ccw":False},
		   #"p":{"segments":["3s''-1s_0","3s''-4s''","4s''-2s_0","1s_0-2s_0"],"ccw":False},

		   
		   "a":{"segments":["2s_0-2s","2s-1g","1g_0-1g","2s_0-1g_0"],"ccw":False},
		   "b":{"segments":["4s''-1r","4s''-2s_0","1r_0-2s_0","1r-1r_0"],"ccw":True},
		   "c":{"segments":["1r_0-2s_0","2s_0-1g_0","2r_0-1g_0","1r_0-2r_0"],"ccw":False},
		   "d":{"segments":["1g_0-1g","1g-2g_","2g_0-2g_","1g_0-2g_0"],"ccw":False},		   
		   "e":{"segments":["2r_0-1g_0","1g_0-2g_0","2r_1-2g_0","2r_0-2r_1"],"ccw":False},
		   "f":{"segments":["2g_0-2g_","2g_-3g","3g_0-3g","2g_0-3g_0"],"ccw":True},		     
		   "g":{"segments":["2r_1-2g_0","2g_0-3g_0","3g_1-3g_0","2r_1-3g_1"],"ccw":False},
		   "h":{"segments":["3g_0-3g","3g-4t","4t_0-4t","3g_0-4t_0"],"ccw":False},
		   "i":{"segments":["3g_1-3g_0","3g_0-4t_0","4t_1-4t_0","3g_1-4t_1"],"ccw":False},
		   "j":{"segments":["4t_0-4t","4t-5t","5t_0-5t","4t_0-5t_0"],"ccw":False},
		   "k":{"segments":["4t_1-4t_0","4t_0-5t_0","5t_1-5t_0","4t_1-5t_1"],"ccw":False},
		   "l":{"segments":["2r_1-2r_2","2r_1-3g_1","13t-3g_1","2r_2-13t"],"ccw":True},
		   "m":{"segments":["13t-3g_1","3g_1-4t_1","13t_0-4t_1","13t-13t_0"],"ccw":False},
		   "n":{"segments":["13t_0-4t_1","4t_1-5t_1","14t-5t_1","13t_0-14t"],"ccw":False},
		   
		   'a0_s':{'segments':['14t_0-6t_2','14t-14t_0','14t-5t_1','5t_1-6t_2'],'ccw':True},
		   'a1_s':{'segments':['6t_2-6t_1','5t_1-6t_2','5t_1-5t_0','5t_0-6t_1'],'ccw':True},
		   'a2_s':{'segments':['6t_1-6t','5t_0-6t_1','5t_0-5t','5t-6t'],'ccw':True},
		   
		   'b0_s':{'segments':['15t-6t_4','14t_0-15t','14t_0-6t_2','6t_2-6t_4'],'ccw':True},
		   'b1_s':{'segments':['6t_4-6t_3','6t_2-6t_4','6t_2-6t_1','6t_1-6t_3'],'ccw':True},
		   'b2_s':{'segments':['6t_3-7t','6t_1-6t_3','6t_1-6t','6t-7t'],'ccw':True},
		   
		   #"r":{"segments":["3s_0-3s","3s_0-4s_0","4s_0-4s","3s-4s"],"ccw":True},
		   #"s":{"segments":["3s''-3s_0","3s''-4s''","4s''-4s_0","3s_0-4s_0"],"ccw":True}, 
		   
		   "ab":{"segments":["4s_0-4s","4s-8t","8t_0-8t","4s_0-8t_0"],"ccw":True},
		   "bb":{"segments":["4s''-1r","4s''-4s_0","1r_1-4s_0","1r-1r_1"],"ccw":False},
		   "cb":{"segments":["1r_1-4s_0","4s_0-8t_0","1r_2-8t_0","1r_1-1r_2"],"ccw":True},
		   "db":{"segments":["1r_2-8t_0","8t_0-9t_0","10r'-9t_0","1r_2-10r'"],"ccw":True},
		   "eb":{"segments":["8t_0-8t","8t-9t","9t_0-9t","8t_0-9t_0"],"ccw":True},
		   "gb":{"segments":["10r'-9t_0","9t_0-10t_0","10r'_0-10t_0","10r'-10r'_0"],"ccw":True},
		   "ib":{"segments":["10r'_0-10t_0","10t_0-10t_3","10t_5-10t_3","10r'_0-10t_5"],"ccw":True},
		   "nb":{"segments":["10r'_0-2r_2","10r'_0-10t_5","13t-10t_5","2r_2-13t"],"ccw":False},
		   "kb":{"segments":["10t_5-10t_3","10t_3-10t_4","10t_6-10t_4","10t_5-10t_6"],"ccw":True},
		   "ob":{"segments":["13t-10t_5","10t_5-10t_6","13t_0-10t_6","13t-13t_0"],"ccw":True},
		   "mb":{"segments":["10t_6-10t_4","10t_4-11t_0","10t_7-11t_0","10t_6-10t_7"],"ccw":True},
		   "pb":{"segments":["13t_0-10t_6","10t_6-10t_7","14t-10t_7","13t_0-14t"],"ccw":True},
		   
		   
		   "fb":{"segments":["9t_0-9t","9t-10t","10t_0-10t","9t_0-10t_0"],"ccw":True},
		   "hb":{"segments":["10t_0-10t","10t-10t_1","10t_3-10t_1","10t_0-10t_3"],"ccw":True},
		   "jb":{"segments":["10t_3-10t_1","10t_3-10t_4","10t_4-10t_2","10t_1-10t_2"],"ccw":True},
		   "lb":{"segments":["10t_4-10t_2","10t_4-11t_0","11t_0-11t","10t_2-11t"],"ccw":True},

		   'ab0_s':{'segments':['14t_0-11t_2s','14t-14t_0','14t-10t_7','10t_7-11t_2s'],'ccw':False},
		   'ab1_s':{'segments':['11t_2s-11t_1s','10t_7-11t_2s','10t_7-11t_0','11t_0-11t_1s'],'ccw':False},
		   'ab2_s':{'segments':['11t_1s-11t_0s','11t_0-11t_1s','11t_0-11t','11t-11t_0s'],'ccw':False},
		   
		   'bb0_s':{'segments':['15t-12t_3','14t_0-15t','14t_0-11t_2s','11t_2s-12t_3'],'ccw':False},
		   'bb1_s':{'segments':['12t_3-12t_2','11t_2s-12t_3','11t_2s-11t_1s','11t_1s-12t_2'],'ccw':False},
		   'bb2_s':{'segments':['12t_2-12t','11t_1s-12t_2','11t_1s-11t_0s','11t_0s-12t'],'ccw':False}   
		 }
    

    if is_woman: 
      self.super_knots["2g_0"]=["knots[\"4s''\"][0]+(knots[\"2r\"][0]-knots[\"4s''\"][0])/4.0","knots[\"2g\"][1]","knots[\"2g\"][2]",1,1,1]
      self.segments["2s-1g"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2s","knot1":"1g"}
      self.segments["1g-2g_"]={"xt":line_3,"yt":curve3_5_x,"zt":curve3_2_y,"knot0":"1g","knot1":"2g_"}
      self.divideBezier3Segment("14t-15t","14t-14t_0","14t_0-15t","14t_0")
      self.super_knots["2g_"]=["0.0","knots[\"1g\"][1]+(knots[\"2g\"][2]-knots[\"1g\"][2])*(knots[\"3g\"][1]-knots[\"1g\"][1])/(knots[\"3g\"][2]-knots[\"1g\"][2])","knots[\"2g\"][2]",1,1,1]
      
      self.super_knots["1g_0"]=["knots[\"2g_0\"][0]+(knots[\"1g\"][2]-knots[\"2g_0\"][2])*(knots[\"2s_0\"][0]-knots[\"2g_0\"][0])/(knots[\"2s_0\"][2]-knots[\"2g_0\"][2])","knots[\"1g\"][1]","knots[\"1g\"][2]",1,1,1]
      self.surfaces["ra"]={"segments":["2r_0-2r_1","2r_1-2r_2","2r_2-2r_3","2r_0-2r_3"],"ccw":False}
      self.surfaces["rb"]={"segments":["1r_0-2r_0","1r_0-2r_4","2r_4-2r_3","2r_0-2r_3"],"ccw":False}
      self.surfaces["rc"]={"segments":["1r-1r_0","1r-2r_5","2r_5-2r_4","1r_0-2r_4"],"ccw":False}
      self.surfaces["rd"]={"segments":["2r_2-2r_3","2r_3-3r'","3r-3r'","2r_2-3r"],"ccw":True}
      self.surfaces["re"]={"segments":["2r_4-2r_3","2r_3-3r'","6r_0-3r'","2r_4-6r_0"],"ccw":False}
      self.surfaces["rf"]={"segments":["2r_5-2r_4","2r_4-6r_0","6r-6r_0","2r_5-6r"],"ccw":False}
      self.surfaces["rg"]={"segments":["3r-3r'","3r'-7r'","4r-7r'","3r-4r"],"ccw":True}
      self.surfaces["rh"]={"segments":["6r_0-3r'","3r'-7r'","5r_0-7r'","6r_0-5r_0"],"ccw":False}
      self.surfaces["ri"]={"segments":["6r-6r_0","6r_0-5r_0","5r-5r_0","6r-5r"],"ccw":False}
      self.surfaces["rk"]={"segments":["10r'-10r'_0","10r'_0-2r_2","2r_2-2r_8","10r'-2r_8"],"ccw":True}
      self.surfaces["rl"]={"segments":["1r_2-10r'","10r'-2r_8","2r_7-2r_8","1r_2-2r_7"],"ccw":True}
      self.surfaces["rm"]={"segments":["1r_1-1r_2","1r_2-2r_7","2r_6-2r_7","1r_1-2r_6"],"ccw":True}
      self.surfaces["rn"]={"segments":["1r-1r_1","1r_1-2r_6","2r_5-2r_6","1r-2r_5"],"ccw":True}
      self.surfaces["ro"]={"segments":["2r_2-2r_8","2r_2-3r","3r-9r'","2r_8-9r'"],"ccw":False}
      self.surfaces["rp"]={"segments":["2r_7-2r_8","2r_8-9r'","6r_2-9r'","2r_7-6r_2"],"ccw":True}
      self.surfaces["rq"]={"segments":["2r_6-2r_7","2r_7-6r_2","6r_1-6r_2","2r_6-6r_1"],"ccw":True}
      self.surfaces["rr"]={"segments":["2r_5-2r_6","2r_6-6r_1","6r-6r_1","2r_5-6r"],"ccw":True}
      self.surfaces["rs"]={"segments":["3r-9r'","3r-4r","4r-8r'","9r'-8r'"],"ccw":False}
      self.surfaces["rt"]={"segments":["6r_2-9r'","9r'-8r'","5r_2-8r'","6r_2-5r_2"],"ccw":True}
      self.surfaces["ru"]={"segments":["6r_1-6r_2","6r_2-5r_2","5r_1-5r_2","6r_1-5r_1"],"ccw":True}
      self.surfaces["rv"]={"segments":["6r-6r_1","6r_1-5r_1","5r-5r_1","6r-5r"],"ccw":True}		 

    else:
      self.super_knots["2g_0"]=["knots[\"4s''\"][0]-(knots[\"2r\"][0]-knots[\"4s''\"][0])/4.0","knots[\"2g\"][1]","knots[\"2g\"][2]",1,1,1]
      self.segments["2s-2g_"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2s","knot1":"2g_"}
      self.divideBezier3Segment("2s-2g_","2s-1g","1g-2g_","1g")
      self.segments["14t-14t_0"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"14t","knot1":"14t_0"}
      self.segments["14t_0-15t"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"14t_0","knot1":"15t"}
      self.super_knots["2g_"]=["0.0","knots[\"2g\"][1]+(knots[\"2g\"][2]-knots[\"2g\"][2])*(knots[\"3g\"][1]-knots[\"2g\"][1])/(knots[\"3g\"][2]-knots[\"2g\"][2])","knots[\"2g\"][2]",1,1,1]
      self.super_knots["1g_0"]=["knots[\"2g_0\"][0]+(knots[\"1g\"][2]-knots[\"2g_0\"][2])*(knots[\"2s_0\"][0]-knots[\"2g_0\"][0])/(knots[\"2s_0\"][2]-knots[\"2g_0\"][2])","knots[\"1g\"][1]","knots[\"1g\"][2]",1,1,1]
    
    self.createEllipticBezier3Spline("14t_0","6t","6t_1",var("knot_2g_0_x"),left_sname="14t_0-6t_1",right_sname="6t_1-6t")
    self.divideBezier3Segment("14t_0-6t_1","14t_0-6t_2","6t_2-6t_1","6t_2")
    self.createEllipticBezier3Spline("15t","7t","6t_3",var("knot_2g_0_x"),left_sname="15t-6t_3",right_sname="6t_3-7t")
    self.divideBezier3Segment("15t-6t_3","15t-6t_4","6t_4-6t_3","6t_4")
    
    self.createEllipticBezier3Spline("14t_0","11t_0s","11t_1s",var("knot_10t_0_x"),left_sname="14t_0-11t_1s",right_sname="11t_1s-11t_0s")
    self.divideBezier3Segment("14t_0-11t_1s","14t_0-11t_2s","11t_2s-11t_1s","11t_2s")
    
    self.createEllipticBezier3Spline("15t","12t","12t_2",var("knot_10t_0_x"),left_sname="15t-12t_2",right_sname="12t_2-12t")
    self.divideBezier3Segment("15t-12t_2","15t-12t_3","12t_3-12t_2","12t_3")
           
    self.createEllipticBezier3Spline("13t","3g","3g_0",var("knot_2g_0_x"),left_sname="13t-3g_0",right_sname="3g_0-3g")
    self.createEllipticBezier3Spline("13t_0","4t","4t_0",var("knot_2g_0_x"),left_sname="13t_0-4t_0",right_sname="4t_0-4t")
    self.createEllipticBezier3Spline("14t","5t","5t_0",var("knot_2g_0_x"),left_sname="14t-5t_0",right_sname="5t_0-5t")
    
    #self.createEllipticBezier3Spline("1r_2","8t","8t_0",var("knot_4s_0_x"),left_sname="1r_2-8t_0",right_sname="8t_0-8t")
    '''
    self.super_knots["8t_0"]=["knots[\"4s_0\"][0]",
    "knots[\"8t\"][1]+(knots[\"4s_0\"][1]-knots[\"8t\"][1])/12.0",str(xfrom_line(knot_8t_z,knot_8t_x,knot_1r_2_z,knot_1r_2_x,knot_4s_0_x)),1,1,1]
    #"knots[\"1r_2\"][1]+(knots[\"8t\"][1]-knots[\"1r\"][1])/3.0","knots[\"1r\"][2]",1,1,1]
    self.segments["1r_2-8t_0"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"1r_2","knot1":"8t_0"}
    self.segments["8t_0-8t"]={"xt":bezier_polynome_3,"yt":line_3,"zt":line_3,"Cx":[p0,p0,p1+(p0-p1)/2.0,p1],"knot0":"8t_0","knot1":"8t"}
    '''
    #self.segments["1r_2-8t"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"1r_2","knot1":"8t"}
    self.segments["1r_2-8t"]={"xt":curve3_1_y,"yt":curve3_1_x,"zt":line_3,"knot0":"1r_2","knot1":"8t"}
    self.divideBezier3Segment("1r_2-8t","1r_2-8t_0","8t_0-8t","8t_0")
    
    #self.createEllipticBezier3Spline("10r'","9t","9t_0",var("knot_4s_0_x"),left_sname="10r'-9t_0",right_sname="9t_0-9t")
    self.segments["10r'-9t"]={"xt":curve3_2_y,"yt":curve3_2_x,"zt":line_3,"knot0":"10r'","knot1":"9t"}
    self.divideBezier3Segment("10r'-9t","10r'-9t_0","9t_0-9t","9t_0")
    
    #self.createEllipticBezier3Spline("10r'_0","10t","10t_0",var("knot_4s_0_x"),left_sname="10r'_0-10t_0",right_sname="10t_0-10t")
    self.segments["10r'_0-10t"]={"xt":curve3_2_y,"yt":curve3_2_x,"zt":line_3,"knot0":"10r'_0","knot1":"10t"}
    self.divideBezier3Segment("10r'_0-10t","10r'_0-10t_0","10t_0-10t","10t_0")
    
    self.createEllipticBezier3Spline("13t","10t_1","10t_3",var("knot_10t_0_x"),left_sname="13t-10t_3",right_sname="10t_3-10t_1")
    #self.segments["13t-10t_1"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"13t","knot1":"10t_1"}
    #self.divideBezier3Segment("13t-10t_1","13t-10t_3","10t_3-10t_1","10t_3")
    
    self.createEllipticBezier3Spline("13t_0","10t_2","10t_4",var("knot_10t_0_x"),left_sname="13t_0-10t_4",right_sname="10t_4-10t_2")
    #self.segments["13t_0-10t_2"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"13t_0","knot1":"10t_2"}
    #self.divideBezier3Segment("13t_0-10t_2","13t_0-10t_4","10t_4-10t_2","10t_4")
    
    self.createEllipticBezier3Spline("14t","11t","11t_0",var("knot_10t_0_x"),left_sname="14t-11t_0",right_sname="11t_0-11t")
    #self.segments["14t-11t"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"14t","knot1":"11t"}
    #self.divideBezier3Segment("14t-11t","14t-11t_0","11t_0-11t","11t_0")
    
    self.createEllipticBezier3Spline("1r","10r'","1r_2",(var("knot_10r__z")+var("knot_1r_z"))/2.0,left_sname="1r-1r_2",right_sname="1r_2-10r'",xaxis="z",zaxis="x")
    #self.segments["1r-10r'"]={"xt":pseudo_ellipse_x_3,"zt":pseudo_ellipse_y_3,"yt":line_3,"knot0":"1r","knot1":"10r'"}
    #self.divideBezier3Segment("1r-10r'","1r-1r_2","1r_2-10r'","1r_2")
    #self.super_knots["1r_1"]=["knots[\"1r\"][0]","knots[\"1r\"][1]+(knots[\"10r'\"][1]-knots[\"1r\"][1])/3.0","knots[\"1r\"][2]",1,1,1]
    #self.super_knots["1r_2"]=["knots[\"1r\"][0]","knots[\"1r\"][1]+2.0*(knots[\"10r'\"][1]-knots[\"1r\"][1])/3.0","knots[\"1r\"][2]+(knots[\"10r'\"][2]-knots[\"1r\"][2])/2.0",1,1,1]
    #self.segments["1r-1r_1"]={"xt":line_3_1,"zt":line_3_1,"yt":line_3_1,"knot0":"1r","knot1":"1r_1"}
    #self.segments["1r_1-1r_2"]={"xt":line_3_1,"zt":line_3_1,"yt":line_3_1,"knot0":"1r_1","knot1":"1r_2"}
    #self.segments["1r_2-10r'"]={"xt":line_3_1,"zt":line_3_1,"yt":line_3_1,"knot0":"1r_2","knot1":"10r'"}
    
    self.divideBezier3Segment("11t-12t","11t-11t_0s","11t_0s-12t","11t_0s")
    self.divideBezier3Segment("4s''-2s","4s''-2s_0","2s_0-2s","2s_0")
    self.divideBezier3Segment("1r-2r_0","1r-1r_0","1r_0-2r_0","1r_0")
    self.divideBezier3Segment("4s''-4s","4s''-4s_0","4s_0-4s","4s_0")
    self.divideBezier3Segment("1r-1r_2","1r-1r_1","1r_1-1r_2","1r_1")
    self.divideBezier3Segment("3s''-1s","3s''-1s_0","1s_0-1s","1s_0")
    self.divideBezier3Segment("3s''-3s","3s''-3s_0","3s_0-3s","3s_0")
    self.divideBezier3Segment("13t-10t_3","13t-10t_5","10t_5-10t_3","10t_5")
    self.divideBezier3Segment("13t_0-10t_4","13t_0-10t_6","10t_6-10t_4","10t_6")
    self.divideBezier3Segment("14t-11t_0","14t-10t_7","10t_7-11t_0","10t_7")
    self.divideBezier3Segment("13t-3g_0","13t-3g_1","3g_1-3g_0","3g_1")
    self.divideBezier3Segment("13t_0-4t_0","13t_0-4t_1","4t_1-4t_0","4t_1")
    self.divideBezier3Segment("14t-5t_0","14t-5t_1","5t_1-5t_0","5t_1")
    self.divideBezier3Segment("10r'-2r_2","10r'-10r'_0","10r'_0-2r_2","10r'_0")
    self.divideBezier3Segment("2r_0-2r_2","2r_0-2r_1","2r_1-2r_2","2r_1")
    self.divideBezier3Segment("6r-3r'","6r-6r_0","6r_0-3r'","6r_0")
    self.divideBezier3Segment("5r-7r'","5r-5r_0","5r_0-7r'","5r_0")
    self.divideBezier3Segment("2r_5-2r_3","2r_5-2r_4","2r_4-2r_3","2r_4")
    self.divideBezier3Segment("2r_5-2r_8","2r_5-2r_6","2r_6-2r_8","2r_6")
    self.divideBezier3Segment("2r_6-2r_8","2r_6-2r_7","2r_7-2r_8","2r_7")
    self.divideBezier3Segment("6r-9r'","6r-6r_1","6r_1-9r'","6r_1")
    self.divideBezier3Segment("6r_1-9r'","6r_1-6r_2","6r_2-9r'","6r_2")
    self.divideBezier3Segment("5r-8r'","5r-5r_1","5r_1-8r'","5r_1")
    self.divideBezier3Segment("5r_1-8r'","5r_1-5r_2","5r_2-8r'","5r_2")
    self.divideBezier3Segment("13t-14t","13t-13t_2","13t_2-14t","13t_2")
    self.divideBezier3Segment("2r-13t","2r-2r_2","2r_2-13t",'2r_2')
    self.divideBezier3Segment("13t-14t","13t-13t_0","13t_0-14t","13t_0")
    
    #self.super_knots["4s_0"][1]="knots[\"4s\"][1]"
    #self.segments["4s''-4s_0"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3_1,"knot0":"4s''","knot1":"4s_0"}
    #self.segments["4s_0-4s"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"4s_0","knot1":"4s"}
    
    self.mirror_axis_knots=["2s","3s","1s","1g","2g_","3g","4t","5t","4s","6t","7t","8t","9t","10t","10t_1","10t_2","11t","11t_0s","12t"]
if sys.argv[0]=="generate_dummy.py":
  lst=[]
  if len(sys.argv)<2 or sys.argv[1]=="man": lst.append([false,"Man"])
  if len(sys.argv)<2 or sys.argv[1]=="woman": lst.append([true,"Woman"])
  for is_woman,filename in lst:
    human=Human(is_woman=is_woman,just_gen_table=False)
    #print human.computed_approx_data
    '''
    knot_names_lst=[[[["3s",None],["4s",None],["8t",None],["9t",None]],1,2,"Антропометричесие точки спины 40 мужских фигур"],
		    [[["10t",None],["11t",None],["12t",None]],1,2,"Антропометричесие точки спины 40 мужских фигур"],
		    [[["1s",None],["2s",None],["2g",None],["3g",None]],1,2,"Антропометричесие точки передних абрисов 40 мужских фигур"],
		    [[["4t",None],["5t",None],["6t",None],["7t",None]],1,2,"Антропометричесие точки передних абрисов 40 мужских фигур"],
		    [[["3s''","P_{3s}^{''}"],["4s''","P_{4s}^{''}"],["1r",None],["2r",None]],0,2,"Антропометричесие точки боковых абрисов 40 мужских фигур"],
		    [[["13t",None],["14t",None],["14t_0",None],["15t",None]],0,2,"Антропометричесие точки боковых абрисов 40 мужских фигур"],
		    [[["11r",None],["2r",None],["6r",None]],0,2,"Антропометричесие точки боковых абрисов рук 40 мужских фигур"],
		    [[["5r",None],["3r",None],["4r",None]],0,2,"Антропометричесие точки боковых абрисов рук 40 мужских фигур"],
		    [[["1r'","P_{1r}^{'}"],["3r'","P_{3r}^{'}"],["7r'","P_{7r}^{'}"]],1,2,"Антропометричесие точки переднего и заднего абрисов рук 40 мужских фигур"],
		    [[["8r'","P_{8r}^{'}"],["9r'","P_{9r}^{'}"],["10r'","P_{10r}^{'}"],["2r'","P_{2r}^{'}"]],1,2,"Антропометричесие точки переднего и заднего абрисов рук 40 мужских фигур"]]
    snames_lst=[ 
	     [[["3s''-4s''","3s^{''}","4s^{''}"],["4s''-1r","4s^{''}","1r"],["2r-13t","2r","13t"]],'x','z'],
	     [[["13t-14t","13t","14t"],["14t-14t_0","14t","14t_0"],["14t_0-15t","14t_0","15t"]],'x','z'],
	     [[["1r-11r","1r","11r"],["11r-2''r","11r","2r^{''}"],["2''r-6r","{2r}^{''}","6r"]],'x','z'],
	     [[["6r-5r","6r","5r"],["2r-3r","2r","3r"],["3r-4r","3r","4r"]],'x','z'],
	     [[["1r'-2r'","1r^{'}","2r^{'}"],["2r'-3r'","2r^{'}","3r^{'}"],["3r'-7r'","3r^{'}","7r^{''}"]],'y','z'],
	     [[["1r'-10r'","1r^{'}","10r^{'}"],["10r'-9r'","10r^{'}","9r^{'}"],["9r'-8r'","9r^{'}","8r^{'}"]],'y','z']
	   ]
    for i in range(40-len(human.knots_table)):
      j=int(random()*float(len(human.knots_table)))
      xscale=0.9+random()/5.0
      yscale=0.9+random()/5.0
      new_knots={}
      new_segments={}
      knots=human.knots_table[j]
      segments=human.computed_approx_data[j]["approx_segments"]
      human.knots_table.append(new_knots)
      human.computed_approx_data.append({"approx_segments":new_segments})
      for snames,xn,yn in snames_lst:
	for sname,tex_pname0,tex_pname1 in snames:
	  new_segments[sname]={"C_"+xn:[p*xscale for p in segments[sname]["C_"+xn]],"C_"+yn:[p*yscale for p in segments[sname]["C_"+yn]]}
      for knot_names,xi,yi,table_name in knot_names_lst:
	for knot_name,tex_name in knot_names:
	  if not knot_name in knots: continue
	  new_knots[knot_name]=[0,0,0]
	  knot=knots[knot_name]
	  new_knots[knot_name][xi]=knot[xi]*xscale
	  new_knots[knot_name][yi]=knot[yi]*yscale
    
      
    tab_no=0
    for knot_names,i0,i1,table_name in knot_names_lst:
      tab_no+=1
      table="\\begin{table}[!h]\n"
      table+="\\caption{"+table_name+"}\n"
      table+="\\label{tab:app_points_"+str(tab_no)+"}\n"
      table+="\\begin{center}"
      table+="\\begin{tabular}"
      #table+="{|cp{0.25cm}"+("|cp{"+str(float(int((10.0*(12.5/float(len(knot_names)*2)))))/10.0)+"cm}")*len(knot_names)*2+"|}\n"
      table+="{"+"|c"*(len(knot_names)+1)+"|}\n"
      table+="\\hline\n"
      table+="&\\multicolumn{"+str(len(knot_names))+"}{c}{\\small{\\textit{Координаты точек, см}}}\\\\\n\cline{2-"+str(len(knot_names)+1)+"}"
      n=0
      for knots in [None]+human.knots_table:
	if not knots is None: table+="\\small{"+str(n)+"}"
	else: table+="\\small{\\textbf{№}}"
	for knot_name,tex_name in knot_names:
	  #for i,vname in (i0,"X"),(i1,"Y"):
	  if knots is None:
	      if tex_name is None: tex_name="P_{"+knot_name+"}"
	      table+="&$\scriptstyle{\mathbf{"+tex_name+"}}$" #("+vname+")}$"
	  else:
	     if knot_name in knots: value=knots[knot_name]#[i]
	     else: value=0.0
	     table+="&\\small{"+str(float(int(100.0*value[i0]))/100.0).replace(".",",")+"; "+str(float(int(100.0*value[i1]))/100.0).replace(".",",")+"}"
	table+="\\\\\n\\hline\n"
	n+=1
      table+="\\end{tabular}\n"
      table+="\\end{center}\n"
      table+="\\end{table}\n"  
      print table

    tab_no=0
    for snames,xn,yn in snames_lst:
      tab_no+=1
      table="\\begin{table}[!h]\n"
      table+="\\caption{Направляющие фрагментов "
      comma=""
      for sname,tex_pname0,tex_pname1 in snames:
       table+=comma+" $S_{"+tex_pname0+"-"+tex_pname1+"}$"
       if not len(comma): comma=","
      table+=" абрисов 40 мужских фигур}\n"		
      table+="\\label{tab:app_curve_points_"+str(tab_no)+"}\n"
      table+="\\begin{center}"
      table+="\\begin{tabular}"
      #table+="{|cp{0.25cm}"+("|cp{"+str(float(int((10.0*(12.5/float(len(snames)*2)))))/10.0)+"cm}")*len(snames)*2+"|}"
      table+="{"+"|c"*(len(snames)*2+1)+"|}"
      table+="\n\\hline\n"
      table+="&\\multicolumn{"+str(len(snames)*2)+"}{c}{\\small{\\textit{Координаты направляющих точек, см}}}\\\\\n\cline{2-"+str(len(snames)*2+1)+"}"
      for i in range(0,len(human.computed_approx_data)+1):
	#print human.computed_approx_data[i]["approx_segments"]
	table+="\n\\hline\n"
	if i: table+=str(i)
	else: table+="№";
	for sname,tex_pname0,tex_pname1 in snames:
	  if i:
	    segments=human.computed_approx_data[i-1]["approx_segments"][sname]
	    table+="&\small{"+str(float(int(100.0*segments["C_"+xn][1]))/100.0).replace(".",",")+"}"
	    table+="; \small{"+str(float(int(100.0*segments["C_"+yn][1]))/100.0).replace(".",",")+"}"
	    table+="&\small{"+str(float(int(100.0*segments["C_"+xn][2]))/100.0).replace(".",",")+"}"
	    table+="; \small{"+str(float(int(100.0*segments["C_"+yn][2]))/100.0).replace(".",",")+"}"
	  else:
	    table+="&"+"$\mathbf{P_{"+tex_pname0+"-"+tex_pname1+"}}$"+"& "+"$\mathbf{P_{"+tex_pname1+"-"+tex_pname0+"}}$"
	table+="\\\\"
      table+="\n\\hline\n"
      table+="\n\\end{tabular}\n"
      table+="\\end{center}\n"
      table+="\\end{table}\n"  
      print table
    import re
    table="\\begin{table}[!h]\n"
    table+="\\caption{Коэффициенты уравнения вида $\mathbf{P}=\mathbf{k_0} + \mathbf{P_1} \mathbf{k_1} + \mathbf{P_2} \mathbf{k_2}$ } для направляющих фрагментов абрисов мужской фигуры, полученные методом регрессионного анализа\n"		
    table+="\\label{tab:app_curve_regression_coefs}\n"
    table+="\\begin{center}"
    table+="\\begin{tabular}{|c|c|c|c|c|c|c|}\n"
    table+="\\hline\n"
    table+="&\\multicolumn{6}{c}{Коэффициенты}\\\\\n"
    table+="&\\multicolumn{3}{c}{первой направляющей}&\\multicolumn{3}{c}{второй направляющей}\\\\\n"
    table+="\\hline\n"
    table+="Фрагменты&$\mathbf{k_0}$&$\mathbf{k_1}$&$\mathbf{k_2}$&$\mathbf{k_0}$&$\mathbf{k_1}$&$\mathbf{k_2}$\\\\\n"
    table+="\\hline\n"
    for snames,xn,yn in snames_lst:
    	for sname,tex_pname0,tex_pname1 in snames:
		px=human.segments[sname]["C"+xn+"_"]
		py=human.segments[sname]["C"+yn+"_"]
		table+="$S_{"+tex_pname0+"-"+tex_pname1+"}$ "
		for i in range(2):
		 for j in range(3):
	          delim="& "
		  for p in px,py:
    		   table+=delim+"\small{"+str(float(int(100.0*p[i][j]))/100.0).replace(".",",")+"}"
		   delim="; "
		table+="\\\\\n\\hline\n"
    table+="\n\\hline\n"
    table+="\n\\end{tabular}\n"
    table+="\\end{center}\n"
    table+="\\end{table}\n"  
    print table
    '''
    	  
    human.processSegments()
    human.finalizeKnots()
    human.generateMirroredSide()
    human.writeToFile("../../data/models/"+filename)
    #human.show_model_data(show_y=True,show_labels=True,knots_names={})
    #human.show_approx_data(show_y=True,labels_d=[2.5,0,0])
    ''' 
    human.show_approx_data(show_y=True,
    knots_names={
      "3s''":"$P_{3s}^{''}$",
      "4s''":"$P_{4s}^{''}$",
      "1r":"$P_{1r}$",
      "11r":"$P_{11r}$",
      "2''r":"$P_{2r}^{''}$",
      "6r":"$P_{6r}$",
      "5r":"$P_{5r}$",
      "4r":"$P_{4r}$",
      "3r":"$P_{3r}$",
      "2r":"$P_{2r}$",
      "13t":"$P_{13t}$",
      "14t":"$P_{14t}$",
      "14t_0":"$P_{14t_0}$",
      "15t":"$P_{15t}$"
    },
    labels_d=[2.5,0,0],pass_from=0,pass_to=1)
    human.show_approx_data(show_x=True,
    knots_names={
      "3s":"$P_{3s}$",
      "4s":"$P_{4s}$",
      "8t":"$P_{8t}$",
      "9t":"$P_{9t}$",
      "10t":"$P_{10t}$",
      "11t":"$P_{11t}$",
      "12t":"$P_{12t}$",
      "1s":"$P_{1s}$",
      "2s":"$P_{2s}$",
      "2g":"$P_{2g}$",
      "3g":"$P_{3g}$",
      "4t":"$P_{4t}$",
      "5t":"$P_{5t}$",
      "6t":"$P_{6t}$",
      "7t":"$P_{7t}$",
      "1r'":"$P_{1r}^{'}$",
      "2r'":"$P_{2r}^{'}$",
      "3r'":"$P_{3r}^{'}$",
      "7r'":"$P_{7r}^{'}$",
      "8r'":"$P_{8r}^{'}$",
      "9r'":"$P_{9r}^{'}$",
      "10r'":"$P_{10r}^{'}$",
      "3s''":"",
      "4s''":"",
      "1r":"",
      "11r":"",
      "2''r":"",
      "6r":"",
      "5r":"",
      "4r":"",
      "3r":"",
      "2r":"",
      "13t":"",
      "14t":"",
      "14t_0":"",
      "15t":""
    },
    labels_d=[2.5,0,0],pass_from=0,pass_to=1)
    '''

    #,except_segments=["1r-11r","11r-2''r","2''r-6r","6r-5r","2r-3r","3r-4r","1r'-2r'",
		#"2r'-3r'","3r'-7r'","1r'-10r'","10r'-9r'","9r'-8r'",
		#"3s-4s","4s-8t","8t-9t","9t-10t","11t-12t"])
    shutil.copy("../../data/models/"+filename,"../../debug/models/")
  
