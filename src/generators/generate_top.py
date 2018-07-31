# -*- coding: utf-8 -*-
from sage.all import *
from pyel3d_math import *
from pyel3d_prep_model import *
import shutil
import sys
#exec open('../../data/models/Woman','r')

class Top(PrepModel):
  def __init__(self,silhoutte_type=0):
    var('p0,p1,pa_x,pa_y,pa_z,pb_x,pb_y,pb_z,pc_x,pc_y,pc_z')
    var('knot_2r_8_y,knot_2r_8_z,knot_8r__y,knot_8r__z,knot_9r__y,knot_9r__z,knot_9r_a_y,knot_9r_a_z,knot_2r_8_y')
    PrepModel.__init__(self)
    #self.knots_table=[[]]*len(knots)
    
    def xfrom_line_and_l(x0,x1,y0,y1,l): return (x0**3 - 2*x0**2*x1 + x0*x1**2 + x0*y0**2 - 2*x0*y0*y1 + x0*y1**2 + (l*x0 - l*x1)*sqrt(x0**2 - 2*x0*x1 + x1**2 + y0**2 - 2*y0*y1 + y1**2))/(x0**2 - 2*x0*x1 + x1**2 + y0**2 - 2*y0*y1 + y1**2)
    
    def yfrom_line_and_l(x0,x1,y0,y1,l): return (y0**3 - 2*y0**2*y1 + y0*y1**2 + (x0**2 - 2*x0*x1 + x1**2)*y0 + (l*y0 - l*y1)*sqrt(x0**2 - 2*x0*x1 + x1**2 + y0**2 - 2*y0*y1 + y1**2))/(x0**2 - 2*x0*x1 + x1**2 + y0**2 - 2*y0*y1 + y1**2)
    
    def xfrom_line(p0x,p0y,p1x,p1y,py): return p0x+(py-p0y)*(p1x-p0x)/(p1y-p0y)
    def xfrom_line_s(p0x,p0y,p1x,p1y,py): return p0x+"+"+"("+py+"-"+p0y+")*("+p1x+"-"+p0x+")/("+p1y+"-"+p0y+")"
    
    def yfrom_par_lines(x0,y0,x1,y1,x0_,y0_,x1_): return -((x0_ - x1_)*y0 - (x0_ - x1_)*y1 - (x0 - x1)*y0_)/(x0 - x1)
    '''
    self.super_knots["4s''"]=["p1gb[0]","p1gb[1]","p1gb[2]+0.1",1,1,1]
    self.super_knots["4s"]=["p1gz[0]+0.1","p1gz[1]","p1gz[2]",1,1,1]
    self.super_knots["3s''"]=["pb[0]+c_0_nsb*sin(-pi*c_0_asb/180.0)","pb[1]","pb[2]+c_0_nsb*cos(-pi*c_0_asb/180.0)",1,1,1]
    self.super_knots["3s"]=["pc[0]","pc[1]-c_0_nsz*sin(pi*c_0_asz/180.0)","pc[2]+c_0_nsz*cos(pi*c_0_asz/180.0)",1,1,1]
    self.super_knots["2s"]=["p1gp[0]-0.1","p1gp[1]","p1gp[2]",1,1,1]
    self.super_knots["1s"]=["pa[0]","pa[1]+c_0_nsp*sin(-pi*c_0_asp/180.0)","pa[2]+c_0_nsp*cos(-pi*c_0_asp/180)",1,1,1]
    '''
    knots_d={"1r":[0.1,0,0.1],
	      "2r_0":[0.1,0,0],
	     "8t":[0,0.1,0],
	     "2r_2":[0.0,0,-0.1], "10t":[0,0.1,0],"11t":[0,0.1,0],"13t":[0.1,0,0],
	     "14t":[0.1,0,0],"2g":[0,-0.1,0],"3g":[0,-0.1,0],"4s''":[0,0,0.1],
	     
	     "4s":[0.1,0,0],
	     "3s''":[0,0,0.1],
	     "3s":[0.1,0,0],
	     "2s":[-0.1,0,0],
	     "1s":[-0.1,0,0],
	     
	     "4t":[0,-0.1,0],"5t":[0,-0.1,0],"9t":[0,0.1,0],
	     "3r":[-0.1,0,0],"3r'":[0,-0.1,0],"6r":["sleeve_sd_2",0,0],
	     "4r":[-0.1,0,0],"7r'":[0,-0.1,0],"5r":["sleeve_sd_3",0,0],
	     "9r'":[0,"sleeve_bk_2",0],"8r'":[0,"sleeve_bk_3",0],"10r'":[0,"sleeve_bk_1",0],
	     "2g_0":[0,-0.1,0]}
    for knot_name,d in knots_d.iteritems(): self.super_knots[knot_name]=["parent.knots[\""+knot_name+"\"][0]+"+str(d[0]),"parent.knots[\""+knot_name+"\"][1]+"+str(d[1]),"parent.knots[\""+knot_name+"\"][2]+"+str(d[2]),1,1,1]
    #self.super_knots["10r'"]=["knots[\"10r''\"][0]","knots[\"10r''\"][1]","knots[\"10r''\"][2]",1,1,1]
    self.super_knots["3g"]=["0.0","knots[\"5t\"][1]+(knots[\"13t\"][2]-knots[\"5t\"][2])*(knots[\"2g\"][1]-knots[\"5t\"][1])/(knots[\"2g\"][2]-knots[\"5t\"][2])","parent.knots[\"3g\"][2]",1,1,1]
    self.super_knots["4t"]=["0.0","knots[\"5t\"][1]+(knots[\"13t_0\"][2]-knots[\"5t\"][2])*(knots[\"2g\"][1]-knots[\"5t\"][1])/(knots[\"2g\"][2]-knots[\"5t\"][2])","knots[\"13t_0\"][2]",1,1,1]
    self.super_knots["10t_0"]=["knots[\"9t_0\"][0]","knots[\"10t\"][1]","knots[\"10t\"][2]",1,1,1]
    self.super_knots["10t_1"]=["0.0","knots[\"10t\"][1]+((knots[\"10t\"][2]+knots[\"10t_2\"][2])/2.0-knots[\"10t\"][2])*(knots[\"11t\"][1]-knots[\"10t\"][1])/(knots[\"11t\"][2]-knots[\"10t\"][2])", "(knots[\"10t\"][2]+knots[\"10t_2\"][2])/2.0",1,1,1]
    self.super_knots["10t_2"]=["0.0","knots[\"10t\"][1]+(knots[\"13t_0\"][2]-knots[\"10t\"][2])*(knots[\"11t\"][1]-knots[\"10t\"][1])/(knots[\"11t\"][2]-knots[\"10t\"][2])", "knots[\"13t_0\"][2]",1,1,1]
    self.super_knots["1g"]=["0.0","knots[\"2g\"][1]+(parent.knots[\"1g\"][2]-knots[\"2g\"][2])*(knots[\"2s\"][1]-knots[\"2g\"][1])/(knots[\"2s\"][2]-knots[\"2g\"][2])","parent.knots[\"1g\"][2]",1,1,1]
    self.super_knots["1g_0"]=["knots[\"2g_0\"][0]+(knots[\"1g\"][2]-knots[\"2g_0\"][2])*(knots[\"2s_0\"][0]-knots[\"2g_0\"][0])/(knots[\"2s_0\"][2]-knots[\"2g_0\"][2])","knots[\"1g\"][1]","knots[\"1g\"][2]",1,1,1]
    self.super_knots["2r_3"]=["knots[\"3r'\"][0]","knots[\"3r'\"][1]","knots[\"2r_2\"][2]",1,1,1]
    self.super_knots["2r_8"]=["parent.knots[\"9r'\"][0]","parent.knots[\"9r'\"][1]+sleeve_bk_1","knots[\"2r_2\"][2]",1,1,1]
    self.super_knots["9r'a"]=["(parent.knots[\"9r'\"][0]+parent.knots[\"8r'\"][0])/2.0","(parent.knots[\"9r'\"][1]+parent.knots[\"8r'\"][1])/2.0+sleeve_bk_4","(parent.knots[\"9r'\"][2]+parent.knots[\"8r'\"][2])/2.0",1,1,1]
    self.super_knots["2r_5"]=["parent.knots[\"6r\"][0]+sleeve_sd_1","0.0","knots[\"2r_2\"][2]",1,1,1]
    #self.super_knots["2g_0"]=["parent.knots[\"2g_0\"][0]","knots[\"2g\"][1]","knots[\"2g\"][2]",1,1,1]
    
    self.super_knots["13t_0"]=["parent.knots[\"13t_2\"][0]","parent.knots[\"13t_2\"][1]","parent.knots[\"13t_2\"][2]",1,1,1]
    
    		   #'cfa0':{"segments":["4r-7r'","4r-c5","c5-c6","7r'-c6"],"ccw":True,"cond":"Sleeve==1 and p1slv[3]==\"3r'-7r'\""},
		   #'cfd1':{"segments":["6r-9r'","6r-c7","c7-c8","9r'-c8"],"ccw":True,"cond":"Sleeve==1 and p1slv[3]==\"2r_3-3r'\""},
		   #'cfd2':{"segments":["2r_5-2r_8","2r_5-c7","c7-c8","2r_8'-c8"],"ccw":True,"cond":"Sleeve==1 and p1slv[3]==\"2r_0-2r_3'\""}
    
    self.extra_vars["c6_y0"]="float(p1slv[3]==\"3r'-7r'\")*knot_7r__y+float(p1slv[3]==\"2r_3-3r'\")*knot_3r__y+float(p1slv[3]==\"2r_0-2r_3'\")*knot_2r_3_y"
    self.extra_vars["c6_z0"]="float(p1slv[3]==\"3r'-7r'\")*knot_7r__z+float(p1slv[3]==\"2r_3-3r'\")*knot_3r__z+float(p1slv[3]==\"2r_0-2r_3'\")*knot_2r_3_z"
    self.extra_vars["c6_y1"]="float(p1slv[3]==\"3r'-7r'\")*knot_3r__y+float(p1slv[3]==\"2r_3-3r'\")*knot_2r_3_y+float(p1slv[3]==\"2r_0-2r_3'\")*knot_2r_0_y"
    self.extra_vars["c6_z1"]="float(p1slv[3]==\"3r'-7r'\")*knot_3r__z+float(p1slv[3]==\"2r_3-3r'\")*knot_2r_3_z+float(p1slv[3]==\"2r_0-2r_3'\")*knot_2r_0_z"
    
    self.extra_vars["c6_y0"]="float(p1slv[3]==\"3r'-7r'\")*knot_7r__y+float(p1slv[3]==\"2r_3-3r'\")*knot_3r__y+float(p1slv[3]==\"2r_0-2r_3'\")*knot_2r_3_y"
    self.extra_vars["c6_z0"]="float(p1slv[3]==\"3r'-7r'\")*knot_7r__z+float(p1slv[3]==\"2r_3-3r'\")*knot_3r__z+float(p1slv[3]==\"2r_0-2r_3'\")*knot_2r_3_z"
    self.extra_vars["c6_y1"]="float(p1slv[3]==\"3r'-7r'\")*knot_3r__y+float(p1slv[3]==\"2r_3-3r'\")*knot_2r_3_y+float(p1slv[3]==\"2r_0-2r_3'\")*knot_2r_0_y"
    self.extra_vars["c6_z1"]="float(p1slv[3]==\"3r'-7r'\")*knot_3r__z+float(p1slv[3]==\"2r_3-3r'\")*knot_2r_3_z+float(p1slv[3]==\"2r_0-2r_3'\")*knot_2r_0_z"
    
    c6y=(xfrom_line_and_l(var("knot_7r__y"),var("knot_3r__y"),var("knot_7r__z"),var("knot_3r__z"),2.0))
    c6z=(yfrom_line_and_l(var("knot_7r__y"),var("knot_3r__y"),var("knot_7r__z"),var("knot_3r__z"),2.0))

    c8y=(xfrom_line_and_l(var("knot_8r__y"),var("knot_9r__y"),var("knot_8r__z"),var("knot_9r__z"),2.0))
    c8z=(yfrom_line_and_l(var("knot_8r__y"),var("knot_9r__y"),var("knot_8r__z"),var("knot_9r__z"),2.0))
    
    c5z=(xfrom_line(c8z,c8y,c6z,c6y,var("knot_4r_y")))
    c7z=(xfrom_line(c8z,c8y,c6z,c6y,var("knot_5r_y")))
    
    self.super_knots["c1"]=["knots[\"4r\"][0]","knots[\"4r\"][1]","knots[\"4r\"][2]",1,1,1]
    self.super_knots["c3"]=["knots[\"5r\"][0]","knots[\"5r\"][1]","knots[\"5r\"][2]",1,1,1]
    self.super_knots["c2"]=["knots[\"7r'\"][0]","knots[\"7r'\"][1]","knots[\"7r'\"][2]",1,1,1]
    self.super_knots["c4"]=["knots[\"8r'\"][0]","knots[\"8r'\"][1]","knots[\"8r'\"][2]",1,1,1]
    
    self.super_knots["c5"]=["knots[\"4r\"][0]","knots[\"4r\"][1]",str(c5z),1,1,1]
    self.super_knots["c7"]=["knots[\"5r\"][0]","knots[\"5r\"][1]",str(c7z),1,1,1]
    
    
    self.super_knots["c6"]=["knots[\"7r'\"][0]",str(c6y),str(c6z),1,1,1]
    self.super_knots["c8"]=["knots[\"8r'\"][0]",str(c8y),str(c8z),1,1,1]    
    
    self.segments={
		   "2s-1g":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2s","knot1":"1g"},
		   "2s_0-1g_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2s_0","knot1":"1g_0"},
		   "1r-2r_0":{"xt":line_3_1,"yt":pseudo_ellipse_y_3,"zt":pseudo_ellipse_x_3,"knot0":"1r","knot1":"2r_0"},
		   "1r_0-2s_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"1r_0","knot1":"2s_0"}, 
		   		   
		   "2r_0-2r_2":{"xt":line_3,"yt":pseudo_ellipse_x_3,"zt":pseudo_ellipse_y_3,"knot0":"2r_0","knot1":"2r_2"},
		   
		   "2r_2-13t":{"xt":bezier_polynome_3,"yt":line_3,"zt":curve3_2_y,"knot0":"2r_2","knot1":"13t",
			       "Cx":[p0,p0,p1,p1]},
		   
		   "2g_0-3g_0":{"xt":line_3,"yt":curve3_5_x,"zt":curve3_2_y,"knot1":"2g_0","knot0":"3g_0"},
		   "2g-3g":{"xt":line_3,"yt":curve3_5_x,"zt":curve3_2_y,"knot1":"2g","knot0":"3g"},
		   

		   "3g_0-4t_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"3g_0","knot1":"4t_0"},
		   "3g-4t":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"3g","knot1":"4t"},
		   "13t-14t":{"xt":curve3_1_x,"yt":line_3_1,"zt":curve3_1_y,"knot0":"13t","knot1":"14t"},   
		   
		   "4t_0-5t_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"4t_0","knot1":"5t_0"},
		   "4t-5t":{"xt":line_3,"yt":line_3,"zt":line_3,"knot0":"4t","knot1":"5t"},
		   
		   "2r_1-2g_0":{"xt":bezier_polynome_3,"yt":bezier_polynome_3,"zt":line_3,"knot0":"2r_1","knot1":"2g_0",
				"Cx":[p0,p0,p0+(el_k-1.0)*(p1-p0)/el_k,p1],
				"Cy":[p0,p0+1.5*(p1-p0)/el_k,p1,p1]},
		   "2g_0-2g":{"xt":line_3,"yt":line_3,"zt":line_3,"knot0":"2g_0","knot1":"2g"},
		   
		   "1g_0-2g_0":{"xt":line_3,"yt":curve3_5_x,"zt":curve3_2_y,"knot0":"1g_0","knot1":"2g_0"},
		   "1g-2g":{"xt":line_3,"yt":curve3_5_x,"zt":curve3_2_y,"knot0":"1g","knot1":"2g"},
		   
		   "10t-11t":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"10t","knot1":"11t"}, 
		   
		   "4s''-1r":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"4s''","knot1":"1r"},
		   
		   "8t_0-9t_0":{"xt":line_3,"yt":curve3_5_x,"zt":curve3_2_y,"knot0":"8t_0","knot1":"9t_0"},
		   
		   "4s-8t":{"xt":line_3,"yt":bezier_polynome_3,"zt":bezier_polynome_3,"knot0":"4s","knot1":"8t",
			    "Cy":[p0,p0+(p1-p0)/3.0,xfrom_line(var("knot_8t_y"),var("knot_8t_z"),var("knot_9t_y"),var("knot_9t_z"),var("knot_4s_z")+2.0*(var("knot_8t_z")-var("knot_4s_z"))/3.0),p1],
			    "Cz":[p0,p0,p0+2.0*(p1-p0)/3.0,p1]},   
			    
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
		   "6r_0-6r_0a":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6r_0","knot1":"6r_0a"},
		   "6r_0a-5r_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6r_0a","knot1":"5r_0"},

		   
		   "6r-5r":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6r","knot1":"5r"},
		   
		   "2r_7-6r_2":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2r_7","knot1":"6r_2"},
		   
		   "2r_6-6r_1":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2r_6","knot1":"6r_1"},
		   
		   
		   "6r_2-6r_2a":{"xt":line_3,"yt":bezier_polynome_3,"zt":bezier_polynome_3,"knot0":"6r_2","knot1":"6r_2a",
				 "Cy":[p0,p0+(p1-p0)/3.0,p0+2.0*(p1-p0)/3.0,p1],
			         "Cz":[p0, yfrom_par_lines(knot_2r_8_y,knot_2r_8_z,knot_9r_a_y,knot_9r_a_z,knot_9r__y,knot_9r__z,knot_9r__y+(knot_9r_a_y-knot_9r__y)/3.0),
				           yfrom_par_lines(knot_9r__y,knot_9r__z,knot_8r__y,knot_8r__z,knot_9r_a_y,knot_9r_a_z,knot_9r__y+2.0*(knot_9r_a_y-knot_9r__y)/3.0),p1] },
		   "6r_1-6r_1a":{"xt":line_3,"yt":bezier_polynome_3,"zt":bezier_polynome_3,"knot0":"6r_1","knot1":"6r_1a",
				 "Cy":[p0,p0+(p1-p0)/3.0,p0+2.0*(p1-p0)/3.0,p1],
			         "Cz":[p0, yfrom_par_lines(knot_2r_8_y,knot_2r_8_z,knot_9r_a_y,knot_9r_a_z,knot_9r__y,knot_9r__z,knot_9r__y+(knot_9r_a_y-knot_9r__y)/3.0),
				           yfrom_par_lines(knot_9r__y,knot_9r__z,knot_8r__y,knot_8r__z,knot_9r_a_y,knot_9r_a_z,knot_9r__y+2.0*(knot_9r_a_y-knot_9r__y)/3.0),p1] },

		   
		   
		   "10r'-2r_8":{"xt":pseudo_ellipse_y_3,"yt":line_3_1,"zt":pseudo_ellipse_x_3,"knot0":"10r'","knot1":"2r_8"},
		   "1r_2-2r_7":{"xt":pseudo_ellipse_y_3,"yt":line_3_1,"zt":pseudo_ellipse_x_3,"knot0":"1r_2","knot1":"2r_7"},
		   "1r_1-2r_6":{"xt":pseudo_ellipse_y_3,"yt":line_3_1,"zt":pseudo_ellipse_x_3,"knot0":"1r_1","knot1":"2r_6"},
		   
		   
		   "2r_5-2r_8":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3_1,"knot0":"2r_5","knot1":"2r_8"},
		   "6r-9r'":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3_1,"knot0":"6r","knot1":"9r'"},
		   "5r-8r'":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3_1,"knot0":"5r","knot1":"8r'"},
		   
		   "2r_8-9r'":{"xt":line_3,"yt":bezier_polynome_3,"zt":bezier_polynome_3,"knot0":"2r_8","knot1":"9r'",
			       "Cy":[p0,p0+(p1-p0)/3.0,p0+2.0*(p1-p0)/3.0,p1],
			       "Cz":[p0,p0+(p1-p0)/3.0, yfrom_par_lines(knot_2r_8_y,knot_2r_8_z,knot_8r__y,knot_8r__z,knot_9r__y,knot_9r__z,knot_2r_8_y+2.0*(knot_9r__y-knot_2r_8_y)/3.0),p1] },
		   
		   #"9r'-8r'":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"9r'","knot1":"8r'",
		   # "Cy":[p0,p0+(p1-p0)/3.0,p0+2.0*(p1-p0)/3.0,p1],
		   # "Cz":[p0, yfrom_par_lines(knot_2r_8_y,knot_2r_8_z,knot_8r__y,knot_8r__z,knot_9r__y,knot_9r__z,knot_9r__y+(knot_8r__y-knot_9r__y)/3.0),p0+2.0*(p1-p0)/3.0,p1] },
		   #"9r'-8r'_a":{"xt":line_3_1,"yt":curve3_1_y,"zt":curve3_1_x,"knot0":"9r'","knot1":"8r'"},
		   
		   
		   "1r-6r":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"1r","knot1":"6r"},
		   "1r_0-6r_0":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"1r_0","knot1":"6r_0"},
		   
		   "9r'-9r'a":{"xt":line_3,"yt":bezier_polynome_3,"zt":bezier_polynome_3,"knot0":"9r'","knot1":"9r'a",
			       "Cy":[p0,p0+(p1-p0)/3.0,p0+2.0*(p1-p0)/3.0,p1],
			       "Cz":[p0, yfrom_par_lines(knot_2r_8_y,knot_2r_8_z,knot_9r_a_y,knot_9r_a_z,knot_9r__y,knot_9r__z,knot_9r__y+(knot_9r_a_y-knot_9r__y)/3.0),
				         yfrom_par_lines(knot_9r__y,knot_9r__z,knot_8r__y,knot_8r__z,knot_9r_a_y,knot_9r_a_z,knot_9r__y+2.0*(knot_9r_a_y-knot_9r__y)/3.0),p1] },
		   
		   "9r'a-8r'":{"xt":line_3,"yt":bezier_polynome_3,"zt":bezier_polynome_3,"knot0":"9r'a","knot1":"8r'",
			       "Cy":[p0,p0+(p1-p0)/3.0,p0+2.0*(p1-p0)/3.0,p1],
			       "Cz":[p0, yfrom_par_lines(knot_9r__y,knot_9r__z,knot_8r__y,knot_8r__z,knot_9r_a_y,knot_9r_a_z,knot_9r_a_y+(knot_8r__y-knot_9r_a_y)/3.0),
				     p0+2.0*(p1-p0)/3.0,p1] },
		   "6r_2a-5r_2":{"xt":line_3,"yt":bezier_polynome_3,"zt":bezier_polynome_3,"knot0":"6r_2a","knot1":"5r_2",
				 "Cy":[p0,p0+(p1-p0)/3.0,p0+2.0*(p1-p0)/3.0,p1],
				 "Cz":[p0, yfrom_par_lines(knot_9r__y,knot_9r__z,knot_8r__y,knot_8r__z,knot_9r_a_y,knot_9r_a_z,knot_9r_a_y+(knot_8r__y-knot_9r_a_y)/3.0),
				       p0+2.0*(p1-p0)/3.0,p1] },
		   "6r_1a-5r_1":{"xt":line_3,"yt":bezier_polynome_3,"zt":bezier_polynome_3,"knot0":"6r_1a","knot1":"5r_1",
		   		 "Cy":[p0,p0+(p1-p0)/3.0,p0+2.0*(p1-p0)/3.0,p1],
			         "Cz":[p0, yfrom_par_lines(knot_9r__y,knot_9r__z,knot_8r__y,knot_8r__z,knot_9r_a_y,knot_9r_a_z,knot_9r_a_y+(knot_8r__y-knot_9r_a_y)/3.0),
				       p0+2.0*(p1-p0)/3.0,p1] },
		   
		   
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

		   "3ra-3r'a":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"3ra","knot1":"3r'a"},
		   "6ra-3r'a":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"6ra","knot1":"3r'a"},
		   "6ra-9r'a":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"6ra","knot1":"9r'a"},
		   "3ra-9r'a":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"3ra","knot1":"9r'a"},
		   
		   "1s-2s":{'xt':bezier_polynome_2,'yt':bezier_polynome_2,'zt':bezier_polynome_2,'knot0':"2s","knot1":"1s","Cx":[p0,pa_x,p1],"Cy":[p0,pa_y,p1],"Cz":[p0,pa_z,p1]},
		   "1s_0-2s_0":{"xt":bezier_polynome_2,"yt":bezier_polynome_2,"zt":bezier_polynome_2,"knot0":"1s_0","knot1":"2s_0","Cx":[p0,(p0+p1)/2.0,p1],"Cy":[p0,(p0+p1)/2.0,p1],"Cz":[p0,(p0+p1)/2.0,p1]},
		   "3s''-4s''":{'xt':bezier_polynome_2,'yt':bezier_polynome_2,'zt':bezier_polynome_2,'knot0':"4s''","knot1":"3s''","Cx":[p0,pb_x,p1],"Cy":[p0,pb_y,p1],"Cz":[p0,pb_z,p1]},
		   "3s_0-4s_0":{"xt":bezier_polynome_2,"yt":bezier_polynome_2,"zt":bezier_polynome_2,"knot0":"3s_0","knot1":"4s_0","Cx":[p0,(p0+p1)/2.0,p1],"Cy":[p0,(p0+p1)/2.0,p1],"Cz":[p0,(p0+p1)/2.0,p1]},
		   "3s-4s":{'xt':bezier_polynome_2,'yt':bezier_polynome_2,'zt':bezier_polynome_2,'knot0':"4s","knot1":"3s","Cx":[p0,pc_x,p1],"Cy":[p0,pc_y,p1],"Cz":[p0,pc_z,p1]},
		   
		   "c1-c2":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"c1","knot1":"c2"},
		   "c3-c2":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"c3","knot1":"c2"},
		   "c1-c4":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"c1","knot1":"c4"},
		   "c3-c4":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"c3","knot1":"c4"},
		   
		   "c5-c6":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"c5","knot1":"c6"},
		   "c7-c6":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"c7","knot1":"c6"},
		   "c5-c8":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"c5","knot1":"c8"},
		   "c7-c8":{"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"c7","knot1":"c8"},
		   
		   "4r-c5":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"4r","knot1":"c5"},
		   "7r'-c6":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"7r'","knot1":"c6"},
		   "8r'-c8":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"8r'","knot1":"c8"},
		   "5r-c7":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"5r","knot1":"c7"},

		   "3r-c5":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"3r","knot1":"c5"},
		   "3r'-c6":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"3r'","knot1":"c6"},
		   "9r'-c8":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"9r'","knot1":"c8"},
		   "6r-c7":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"6r","knot1":"c7"},

		   "2r_2-c5":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2r_2","knot1":"c5"},
		   "2r_3-c6":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2r_3","knot1":"c6"},
		   "2r_8-c8":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2r_8","knot1":"c8"},
		   "2r_5-c7":{"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"2r_5","knot1":"c7"},
		   
		  }
    
    tx_v_0="1.0-(z-knot_5t_z)/(knot_1s_z-knot_5t_z)"
    tx_u_0="(1.0+x/knot_1r_x)/4.0"
    tx_u_1="1.0-(1.0+x/knot_1r_x)/4.0"
    self.surfaces={
		   #"o":{"segments":["1s_0-1s","1s_0-2s_0","2s_0-2s","1s-2s"],"ccw":False,"cond":"is_vorot==1","tx_u":tx_u_0,"tx_v":tx_v_0},
		   #"p":{"segments":["3s''-1s_0","3s''-4s''","4s''-2s_0","1s_0-2s_0"],"ccw":False,"cond":"is_vorot==1","tx_u":tx_u_0,"tx_v":tx_v_0},
		   #"r":{"segments":["3s_0-3s","3s_0-4s_0","4s_0-4s","3s-4s"],"ccw":True,"cond":"is_vorot==1","tx_u":tx_u_1,"tx_v":tx_v_0},
		   #"s":{"segments":["3s''-3s_0","3s''-4s''","4s''-4s_0","3s_0-4s_0"],"ccw":True,"cond":"is_vorot==1","tx_u":tx_u_1,"tx_v":tx_v_0},
		   
		   "a":{"segments":["2s_0-2s","2s-1g","1g_0-1g","2s_0-1g_0"],"ccw":False,"tx_u":tx_u_0,"tx_v":tx_v_0},
		   "b":{"segments":["4s''-1r","4s''-2s_0","1r_0-2s_0","1r-1r_0"],"ccw":True,"tx_u":tx_u_0,"tx_v":tx_v_0},
		   "c":{"segments":["1r_0-2s_0","2s_0-1g_0","2r_0-1g_0","1r_0-2r_0"],"ccw":False,"tx_u":tx_u_0,"tx_v":tx_v_0},
		   "d":{"segments":["1g_0-1g","1g-2g","2g_0-2g","1g_0-2g_0"],"ccw":False,"tx_u":tx_u_0,"tx_v":tx_v_0},
		   "e":{"segments":["2r_0-1g_0","1g_0-2g_0","2r_1-2g_0","2r_0-2r_1"],"ccw":False,"tx_u":tx_u_0,"tx_v":tx_v_0},
		   "f":{"segments":["2g_0-2g","2g-3g","3g_0-3g","2g_0-3g_0"],"ccw":False,"tx_u":tx_u_0,"tx_v":tx_v_0},
		   "g":{"segments":["2r_1-2g_0","2g_0-3g_0","3g_1-3g_0","2r_1-3g_1"],"ccw":False,"tx_u":tx_u_0,"tx_v":tx_v_0},
		   "h":{"segments":["3g_0-3g","3g-4t","4t_0-4t","3g_0-4t_0"],"ccw":False,"tx_u":tx_u_0,"tx_v":tx_v_0},
		   "i":{"segments":["3g_1-3g_0","3g_0-4t_0","4t_1-4t_0","3g_1-4t_1"],"ccw":False,"tx_u":tx_u_0,"tx_v":tx_v_0},
		   "j":{"segments":["4t_0-4t","4t-5t","5t_0-5t","4t_0-5t_0"],"ccw":False,"tx_u":tx_u_0,"tx_v":tx_v_0},
		   "k":{"segments":["4t_1-4t_0","4t_0-5t_0","5t_1-5t_0","4t_1-5t_1"],"ccw":False,"tx_u":tx_u_0,"tx_v":tx_v_0},
		   "l":{"segments":["2r_1-2r_2","2r_1-3g_1","13t-3g_1","2r_2-13t"],"ccw":True,"tx_u":tx_u_0,"tx_v":tx_v_0},
		   "m":{"segments":["13t-3g_1","3g_1-4t_1","13t_0-4t_1","13t-13t_0"],"ccw":False,"tx_u":tx_u_0,"tx_v":tx_v_0},
		   "n":{"segments":["13t_0-4t_1","4t_1-5t_1","14t-5t_1","13t_0-14t"],"ccw":False,"tx_u":tx_u_0,"tx_v":tx_v_0},
		   
		   "ab":{"segments":["4s_0-4s","4s-8t","8t_0-8t","4s_0-8t_0"],"ccw":True,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   "bb":{"segments":["4s''-1r","4s''-4s_0","1r_1-4s_0","1r-1r_1"],"ccw":False,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   "cb":{"segments":["1r_1-4s_0","4s_0-8t_0","1r_2-8t_0","1r_1-1r_2"],"ccw":True,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   "db":{"segments":["8t_0-8t","8t-9t","9t_0-9t","8t_0-9t_0"],"ccw":True,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   "eb":{"segments":["1r_2-8t_0","8t_0-9t_0","10r'-9t_0","1r_2-10r'"],"ccw":True,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   "gb":{"segments":["10r'-9t_0","9t_0-10t_0","10r'_0-10t_0","10r'-10r'_0"],"ccw":True,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   "ib":{"segments":["10r'_0-10t_0","10t_0-10t_3","10t_5-10t_3","10r'_0-10t_5"],"ccw":True,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   "nb":{"segments":["10r'_0-2r_2","10r'_0-10t_5","13t-10t_5","2r_2-13t"],"ccw":False,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   "kb":{"segments":["10t_5-10t_3","10t_3-10t_4","10t_6-10t_4","10t_5-10t_6"],"ccw":True,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   "ob":{"segments":["13t-10t_5","10t_5-10t_6","13t_0-10t_6","13t-13t_0"],"ccw":True,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   "mb":{"segments":["10t_6-10t_4","10t_4-11t_0","10t_7-11t_0","10t_6-10t_7"],"ccw":True,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   "pb":{"segments":["13t_0-10t_6","10t_6-10t_7","14t-10t_7","13t_0-14t"],"ccw":True,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   
		   "fb":{"segments":["9t_0-9t","9t-10t","10t_0-10t","9t_0-10t_0"],"ccw":True,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   "hb":{"segments":["10t_0-10t","10t-10t_1","10t_3-10t_1","10t_0-10t_3"],"ccw":True,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   "jb":{"segments":["10t_3-10t_1","10t_3-10t_4","10t_4-10t_2","10t_1-10t_2"],"ccw":True,"tx_u":tx_u_1,"tx_v":tx_v_0},
		   "lb":{"segments":["10t_4-10t_2","10t_4-11t_0","11t_0-11t","10t_2-11t"],"ccw":True,"tx_u":tx_u_1,"tx_v":tx_v_0},

		   #"ra":{"segments":["2r_0-2r_1","2r_1-2r_2","2r_2-2r_3","2r_0-2r_3"],"ccw":False,"cond":"Sleeve==1"},
		   #"rb":{"segments":["1r_0-2r_0","1r_0-2r_4","2r_4-2r_3","2r_0-2r_3"],"ccw":False,"cond":"Sleeve==1"},
		   #"rc":{"segments":["1r-1r_0","1r-2r_5","2r_5-2r_4","1r_0-2r_4"],"ccw":False,"cond":"Sleeve==1"},
		   
		   #"rd":{"segments":["2r_2-2r_3","2r_3-3r'","3r-3r'","2r_2-3r"],"ccw":True,"cond":"Sleeve==1 and (p1slv[3]==\"2r_3-3r'\" or (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3])))"},
		   #"re":{"segments":["2r_4-2r_3","2r_3-3r'","6r_0-3r'","2r_4-6r_0"],"ccw":False,"cond":"Sleeve==1 and (p1slv[3]==\"2r_3-3r'\" or (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3])))"},
		   #"rf":{"segments":["2r_5-2r_4","2r_4-6r_0","6r-6r_0","2r_5-6r"],"ccw":False,"cond":"Sleeve==1 and (p1slv[3]==\"2r_3-3r'\" or (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3])))"},

		   #"rg":{"segments":["3ra-3r'a","3r'a-7r'","4r-7r'","3ra-4r"],"ccw":True,"cond":"Sleeve==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   #"rh":{"segments":["6r_0a-3r'a","3r'a-7r'","5r_0-7r'","6r_0a-5r_0"],"ccw":False,"cond":"Sleeve==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   #"ri":{"segments":["6ra-6r_0a","6r_0a-5r_0","5r-5r_0","6ra-5r"],"ccw":False,"cond":"Sleeve==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},

		   #"rg_":{"segments":["3r-3r'","3r-3ra","3ra-3r'a","3r'-3r'a"],"ccw":True,"cond":"Sleeve==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   #"rh_":{"segments":["6r_0-3r'","6r_0-6r_0a","6r_0a-3r'a","3r'-3r'a"],"ccw":False,"cond":"Sleeve==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   #"ri_":{"segments":["6r-6r_0","6r-6ra","6ra-6r_0a","6r_0-6r_0a"],"ccw":False,"cond":"Sleeve==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   
		   #"rk":{"segments":["10r'-10r'_0","10r'_0-2r_2","2r_2-2r_8","10r'-2r_8"],"ccw":True,"cond":"Sleeve==1"},
		   #"rl":{"segments":["1r_2-10r'","10r'-2r_8","2r_7-2r_8","1r_2-2r_7"],"ccw":True,"cond":"Sleeve==1"},
		   #"rm":{"segments":["1r_1-1r_2","1r_2-2r_7","2r_6-2r_7","1r_1-2r_6"],"ccw":True,"cond":"Sleeve==1"},
		   #"rn":{"segments":["1r-1r_1","1r_1-2r_6","2r_5-2r_6","1r-2r_5"],"ccw":True,"cond":"Sleeve==1"},
		   
		   #"ro":{"segments":["2r_2-2r_8","2r_2-3r","3r-9r'","2r_8-9r'"],"ccw":False,"cond":"Sleeve==1 and (p1slv[3]==\"2r_3-3r'\" or (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3])))"},
		   #"rp":{"segments":["2r_7-2r_8","2r_8-9r'","6r_2-9r'","2r_7-6r_2"],"ccw":True,"cond":"Sleeve==1 and (p1slv[3]==\"2r_3-3r'\" or (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3])))"},
		   #"rq":{"segments":["2r_6-2r_7","2r_7-6r_2","6r_1-6r_2","2r_6-6r_1"],"ccw":True,"cond":"Sleeve==1 and (p1slv[3]==\"2r_3-3r'\" or (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3])))"},
		   #"rr":{"segments":["2r_5-2r_6","2r_6-6r_1","6r-6r_1","2r_5-6r"],"ccw":True,"cond":"Sleeve==1 and (p1slv[3]==\"2r_3-3r'\" or (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3])))"},
		   
		   #"rs":{"segments":["3ra-9r'a","3ra-4r","4r-8r'","9r'a-8r'"],"ccw":False,"cond":"Sleeve==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   #"rt":{"segments":["6r_2a-9r'a","9r'a-8r'","5r_2-8r'","6r_2a-5r_2"],"ccw":True,"cond":"Sleeve==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   #"ru":{"segments":["6r_1a-6r_2a","6r_2a-5r_2","5r_1-5r_2","6r_1a-5r_1"],"ccw":True,"cond":"Sleeve==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   #"rv":{"segments":["6ra-6r_1a","6r_1a-5r_1","5r-5r_1","6ra-5r"],"ccw":True,"cond":"Sleeve==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   
		   #"rs_":{"segments":["3r-9r'","3r-3ra","3ra-9r'a","9r'-9r'a"],"ccw":False,"cond":"Sleeve==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   #"rt_":{"segments":["6r_2-9r'","6r_2-6r_2a","6r_2a-9r'a","9r'-9r'a"],"ccw":True,"cond":"Sleeve==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   #"ru_":{"segments":["6r_1-6r_2","6r_1-6r_1a","6r_1a-6r_2a","6r_2-6r_2a"],"ccw":True,"cond":"Sleeve==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   #"rv_":{"segments":["6r-6r_1","6r-6ra","6ra-6r_1a","6r_1-6r_1a"],"ccw":True,"cond":"Sleeve==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   
		   #'cfa0':{"segments":["4r-7r'","4r-c5","c5-c6","7r'-c6"],"ccw":True,"cond":"Sleeve==1 and CuffsOn==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   #'cfb0':{"segments":["5r-7r'","5r-c7","c7-c6","7r'-c6"],"ccw":False,"cond":"Sleeve==1 and CuffsOn==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   #'cfc0':{"segments":["4r-8r'","4r-c5","c5-c8","8r'-c8"],"ccw":False,"cond":"Sleeve==1 and CuffsOn==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   #'cfd0':{"segments":["5r-8r'","5r-c7","c7-c8","8r'-c8"],"ccw":True,"cond":"Sleeve==1 and CuffsOn==1 and (p1slv[3]==\"3r'-7r'\" or not len(p1slv[3]))"},
		   
		   #'cfa1':{"segments":["3r-3r'","3r-c5","c5-c6","3r'-c6"],"ccw":True,"cond":"Sleeve==1 and CuffsOn==1 and p1slv[3]==\"2r_3-3r'\""},
		   #'cfb1':{"segments":["6r-3r'","6r-c7","c7-c6","3r'-c6"],"ccw":False,"cond":"Sleeve==1 and CuffsOn==1 and p1slv[3]==\"2r_3-3r'\""},
		   #'cfc1':{"segments":["3r-9r'","3r-c5","c5-c8","9r'-c8"],"ccw":False,"cond":"Sleeve==1 and CuffsOn==1 and p1slv[3]==\"2r_3-3r'\""},
		   #'cfd1':{"segments":["6r-9r'","6r-c7","c7-c8","9r'-c8"],"ccw":True,"cond":"Sleeve==1 and CuffsOn==1 and p1slv[3]==\"2r_3-3r'\""},
		   
		   #'cfa2':{"segments":["2r_2-2r_3","2r_2-c5","c5-c6","2r_3-c6"],"ccw":True,"cond":"Sleeve==1 and CuffsOn==1 and p1slv[3]==\"2r_0-2r_3'\""},
		   #'cfb2':{"segments":["2r_5-2r_3","2r_5-c7","c7-c6","2r_3-c6"],"ccw":False,"cond":"Sleeve==1 and CuffsOn==1 and p1slv[3]==\"2r_0-2r_3'\""},
		   #'cfc2':{"segments":["2r_2-2r_8","2r_2-c5","c5-c8","2r_8-c8"],"ccw":False,"cond":"Sleeve==1 and CuffsOn==1 and p1slv[3]==\"2r_0-2r_3'\""},
		   #'cfd2':{"segments":["2r_5-2r_8","2r_5-c7","c7-c8","2r_8-c8"],"ccw":True,"cond":"Sleeve==1 and CuffsOn==1 and p1slv[3]==\"2r_0-2r_3'\""}
		  }
    '''		  
    self.super_knots["4s''"]=["p1gb[0]","p1gb[1]","p1gb[2]+0.1",1,1,1]
    self.super_knots["4s"]=["p1gz[0]+0.1","p1gz[1]","p1gz[2]",1,1,1]
    self.super_knots["3s''"]=["pb[0]+c_0_nsb*sin(-pi*c_0_asb/180.0)","pb[1]","pb[2]+c_0_nsb*cos(-pi*c_0_asb/180.0)",1,1,1]
    self.super_knots["3s"]=["pc[0]","pc[1]-c_0_nsz*sin(pi*c_0_asz/180.0)","pc[2]+c_0_nsz*cos(pi*c_0_asz/180.0)",1,1,1]
    self.super_knots["2s"]=["p1gp[0]-0.1","p1gp[1]","p1gp[2]",1,1,1]
    self.super_knots["1s"]=["pa[0]","pa[1]+c_0_nsp*sin(-pi*c_0_asp/180.0)","pa[2]+c_0_nsp*cos(-pi*c_0_asp/180)",1,1,1]
    
    self.extra_vars["p1gp"]="self.pointOnBearingSpline([\"2s-1g\"],Rg1+c_0_d)"    
    self.extra_vars["p1gb"]="self.pointOnBearingSpline([\"4s''-1r\"],Rg3+c_0_e)"
    self.extra_vars["p1gz"]="self.pointOnBearingSpline([\"4s-8t\"],Rg2+c_0_f)"
    self.extra_vars["pa"]="self.pointOnBearingSpline([\"2s-1g\"],Rg1)"
    self.extra_vars["pb"]="self.pointOnBearingSpline([\"4s''-1r\"],Rg3)"
    self.extra_vars["pc"]="self.pointOnBearingSpline([\"4s-8t\"],Rg2)"
    self.extra_vars["pa_x"]="pa[0]"; self.extra_vars["pa_y"]="pa[1]"; self.extra_vars["pa_z"]="pa[2]"
    self.extra_vars["pb_x"]="pb[0]"; self.extra_vars["pb_y"]="pb[1]"; self.extra_vars["pb_z"]="pb[2]"
    self.extra_vars["pc_x"]="pc[0]"; self.extra_vars["pc_y"]="pc[1]"; self.extra_vars["pc_z"]="pc[2]"
    self.extra_vars["p1slv"]="self.pointOnBearingSpline([\"2r_0-2r_3\",\"2r_3-3r'\",\"3r'-7r'\"],SleeveLength)"
    self.extra_vars["p1slv"]="[None,None,None,None]"
    '''
    if silhoutte_type<2:
      '''woman
      self.createEllipticBezier3Spline("13t","3g","3g_0",var("knot_2g_0_x"),left_sname="13t-3g_0",right_sname="3g_0-3g")
      self.createEllipticBezier3Spline("13t_0","4t","4t_0",var("knot_2g_0_x"),left_sname="13t_0-4t_0",right_sname="4t_0-4t")
      self.createEllipticBezier3Spline("14t","5t","5t_0",var("knot_2g_0_x"),left_sname="14t-5t_0",right_sname="5t_0-5t")
      '''
      #man
      self.segments["13t-14t"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"13t","knot1":"14t"}
      #self.createEllipticBezier3Spline("3g_1","3g","3g_0",var("knot_2g_0_x"),left_sname="3g_1-3g_0",right_sname="3g_0-3g")
      #self.createEllipticBezier3Spline("4t_1","4t","4t_0",var("knot_2g_0_x"),left_sname="4t_1-4t_0",right_sname="4t_0-4t")
      #self.createEllipticBezier3Spline("5t_1","5t","5t_0",var("knot_2g_0_x"),left_sname="5t_1-5t_0",right_sname="5t_0-5t")
      
      self.segments["3g_1-3g_0"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"3g_1","knot1":"3g_0"}
      self.segments["4t_1-4t_0"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"4t_1","knot1":"4t_0"}
      self.segments["5t_1-5t_0"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"5t_1","knot1":"5t_0"}

      self.segments["3g_0-3g"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"3g_0","knot1":"3g"}
      self.segments["4t_0-4t"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"4t_0","knot1":"4t"}
      self.segments["5t_0-5t"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"5t_0","knot1":"5t"}
      
      self.segments["13t-3g_1"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"13t","knot1":"3g_1"}
      self.segments["13t_0-4t_1"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"13t_0","knot1":"4t_1"}
      self.segments["14t-5t_1"]={"xt":line_3_1,"yt":line_3_1,"zt":line_3_1,"knot0":"14t","knot1":"5t_1"}
      self.super_knots["3g_1"]=["knots[\'13t\'][0]","knots[\'2r_1\'][1]","knots[\'13t\'][2]",1,1,1]
      self.super_knots["4t_1"]=["knots[\'13t_0\'][0]","knots[\'2r_1\'][1]","knots[\'13t_0\'][2]",1,1,1]
      self.super_knots["5t_1"]=["knots[\'14t\'][0]","knots[\'2r_1\'][1]","knots[\'14t\'][2]",1,1,1]
      self.super_knots["3g_0"]=["knots[\'2g_0\'][0]","knots[\'3g\'][1]","(knots[\'13t\'][2]+knots[\'3g\'][2])/2.0",1,1,1]
      self.super_knots["4t_0"]=["knots[\'2g_0\'][0]","knots[\'4t\'][1]","(knots[\'13t_0\'][2]+knots[\'4t\'][2])/2.0",1,1,1]
      self.super_knots["5t_0"]=["knots[\'2g_0\'][0]","knots[\'5t\'][1]","(knots[\'14t\'][2]+knots[\'5t\'][2])/2.0",1,1,1]
      self.super_knots["2r_0"]=[xfrom_line_s("knots[\'1r\'][0]","knots[\'1r\'][2]","knots[\'2r_2\'][0]","knots[\'2r_2\'][2]","parent.knots[\'2r_0\'][2]"),"parent.knots[\'2r_0\'][1]","parent.knots[\'2r_0\'][2]",1,1,1]
      self.super_knots["10r'"]=[xfrom_line_s("knots[\'1r\'][0]","knots[\'1r\'][2]","knots[\'2r_2\'][0]","knots[\'2r_2\'][2]","parent.knots[\"10r\'\"][2]"),"parent.knots[\"10r\'\"][1]","parent.knots[\"10r\'\"][2]",1,1,1]
      #
      if silhoutte_type==0:
	self.super_knots["5t"][1]="(knots[\"2g\"][1]+parent.knots[\"5t\"][1])/2.0"
	self.super_knots["14t"][0]="(knots[\"13t\"][0]+parent.knots[\"14t\"][0])/2.0"
	self.super_knots["11t"][1]="(knots[\"9t\"][1]+parent.knots[\"11t\"][1])/2.0"
	self.super_knots["10t"][1]="(knots[\"9t\"][1]+parent.knots[\"10t\"][1])/2.0"
    else:
      
      self.super_knots["3g_0"]=["parent.knots[\"2g_0\"][0]","knots[\"5t\"][1]+(knots[\"3g\"][2]-knots[\"5t\"][2])*(knots[\"2g\"][1]-knots[\"5t\"][1])/(knots[\"2g\"][2]-knots[\"5t\"][2])","knots[\"3g\"][2]",1,1,1]
      self.super_knots["4t_0"]=["parent.knots[\"2g_0\"][0]","knots[\"5t\"][1]+(knots[\"4t\"][2]-knots[\"5t\"][2])*(knots[\"2g\"][1]-knots[\"5t\"][1])/(knots[\"2g\"][2]-knots[\"5t\"][2])","knots[\"4t\"][2]",1,1,1]
      self.super_knots["5t_0"]=["parent.knots[\"2g_0\"][0]","knots[\"5t\"][1]","knots[\"5t\"][2]",1,1,1]
      self.segments["13t-3g_0"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"13t","knot1":"3g_0"}
      self.segments["3g_0-3g"]={"xt":line_3,"yt":line_3,"zt":line_3,"knot0":"3g_0","knot1":"3g"}
      self.segments["13t_0-4t_0"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"13t_0","knot1":"4t_0"}
      self.segments["4t_0-4t"]={"xt":line_3,"yt":line_3,"zt":line_3,"knot0":"4t_0","knot1":"4t"}
      self.segments["14t-5t_0"]={"xt":pseudo_ellipse_x_3,"yt":pseudo_ellipse_y_3,"zt":line_3,"knot0":"14t","knot1":"5t_0"}
      self.segments["5t_0-5t"]={"xt":line_3,"yt":line_3,"zt":line_3,"knot0":"5t_0","knot1":"5t"}
      if silhoutte_type==2:
	self.super_knots["5t"][1]="knots[\"2g\"][1]"
	self.super_knots["14t"][0]="knots[\"13t\"][0]"
	self.super_knots["11t"][1]="knots[\"9t\"][1]"
	self.super_knots["10t"][1]="knots[\"9t\"][1]"

      self.divideBezier3Segment("13t-3g_0","13t-3g_1","3g_1-3g_0","3g_1")
      self.divideBezier3Segment("13t_0-4t_0","13t_0-4t_1","4t_1-4t_0","4t_1")
      self.divideBezier3Segment("14t-5t_0","14t-5t_1","5t_1-5t_0","5t_1")

    
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
    '''
    self.createEllipticBezier3Spline("13t","10t_1","10t_3",var("knot_4s_0_x"),left_sname="13t-10t_3",right_sname="10t_3-10t_1")
    self.createEllipticBezier3Spline("13t_0","10t_2","10t_4",var("knot_4s_0_x"),left_sname="13t_0-10t_4",right_sname="10t_4-10t_2")
    self.createEllipticBezier3Spline("14t","11t","11t_0",var("knot_4s_0_x"),left_sname="14t-11t_0",right_sname="11t_0-11t")
    #self.createEllipticBezier3Spline("1r","10r'","1r_2",var("knot_8t_z"),left_sname="1r-1r_2",right_sname="1r_2-10r'",xaxis="z",zaxis="x")
    '''
    self.createEllipticBezier3Spline("1r","10r'","1r_2",(var("knot_10r__z")+var("knot_1r_z"))/2.0,left_sname="1r-1r_2",right_sname="1r_2-10r'",xaxis="z",zaxis="x")
    
    self.divideBezier3Segment("4s''-2s","4s''-2s_0","2s_0-2s","2s_0")
    self.divideBezier3Segment("1r-2r_0","1r-1r_0","1r_0-2r_0","1r_0")
    self.divideBezier3Segment("4s''-4s","4s''-4s_0","4s_0-4s","4s_0")
    self.divideBezier3Segment("1r-1r_2","1r-1r_1","1r_1-1r_2","1r_1")
    self.divideBezier3Segment("3s''-1s","3s''-1s_0","1s_0-1s","1s_0")
    self.divideBezier3Segment("3s''-3s","3s''-3s_0","3s_0-3s","3s_0")
    self.divideBezier3Segment("13t-10t_3","13t-10t_5","10t_5-10t_3","10t_5")
    self.divideBezier3Segment("13t_0-10t_4","13t_0-10t_6","10t_6-10t_4","10t_6")
    self.divideBezier3Segment("14t-11t_0","14t-10t_7","10t_7-11t_0","10t_7") 
   
    
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
    self.divideBezier3Segment("13t-14t","13t-13t_0","13t_0-14t","13t_0")
    
    self.divideBezier3Segment("6ra-3r'a","6ra-6r_0a","6r_0a-3r'a","6r_0a")
    self.divideBezier3Segment("3r-4r","3r-3ra","3ra-4r","3ra")
    self.divideBezier3Segment("3r'-7r'","3r'-3r'a","3r'a-7r'","3r'a")
    self.divideBezier3Segment("6r-5r","6r-6ra","6ra-5r","6ra")
    self.divideBezier3Segment("6ra-9r'a","6ra-6r_1a","6r_1a-9r'a","6r_1a")
    self.divideBezier3Segment("6r_1a-9r'a","6r_1a-6r_2a","6r_2a-9r'a","6r_2a")
    
    self.mirror_axis_knots=["2s","3s","1s","1g","2g","3g","4t","5t","4s","8t","9t","10t","10t_1","10t_2","11t"]

    self.external_vars=['Sm3','d1gp','TempP1','TempP2','TempP3','sleeve_bk_1','sleeve_bk_2','sleeve_bk_3','sleeve_bk_4','sleeve_sd_1','sleeve_sd_2','sleeve_sd_3',"Sleeve","CuffsOn","SleeveLength","is_vorot", 'Rg3','Rg2','Rg1','c_0_d','c_0_e','c_0_f','c_0_nsb','c_0_nsp','c_0_nsz','c_0_asp','c_0_asb','c_0_asz',"CuffsOn"]

import generate_dummy
human=generate_dummy.Human(is_woman=False)
human.processSegments()
human.finalizeKnots()
human.pythonizeExpressions()
#human.show_model_data()
    
if sys.argv[0]=="generate_top.py":
  lst=[]
  if len(sys.argv)<2 or sys.argv[1]=="blouse": lst.append("Blouse")
  if len(sys.argv)<2 or sys.argv[1]=="jacket": lst.append("MensJacket")
  for gname in lst:
    for i in range(3):
      blouse=Top(i)
      blouse.processSegments()
      blouse.finalizeKnots()
      blouse.generateMirroredSide()
      blouse.writeToFile("../../data/models/"+gname+str(i))
      if gname is "MensJacket" and i==0: blouse.show_model_data(human)      
      
      shutil.copy("../../data/models/"+gname+str(i),"../../debug/models/")
