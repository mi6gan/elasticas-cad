# -*- coding: utf-8 -*-
def computeVariables(computed_vars):
    exec("from math import *") in computed_vars
    knots=computed_vars["knots"]
    super_knots=computed_vars["super_knots"]
    variables=computed_vars["variables"]
    super_knots_keys=super_knots.keys()
    variables_keys=variables.keys()
    computed_vars['src_knots']=dict(knots)
    count=0
    while count<10 and (len(super_knots_keys) or len(variables_keys)):
      for knot_name in super_knots_keys[:]:
	super_knot=super_knots[knot_name]
	try:
	  exec("s0="+super_knot[0]+";"+"s1="+super_knot[1]+";"+"s2="+super_knot[2]) in None,computed_vars
	  knots[knot_name]=[computed_vars['s0']*super_knot[3],computed_vars['s1']*super_knot[4],computed_vars['s2']*super_knot[5]]
	  if not knot_name in computed_vars['src_knots']: computed_vars['src_knots'][knot_name]=knots[knot_name]
	  super_knots_keys.remove(knot_name)
	except (KeyError,NameError,ZeroDivisionError) as detail: 
	  if count>=9: print detail,knot_name+"="+str(super_knot)
	except ValueError as detail: print detail,knot_name+"="+str(super_knot); continue
      for name in variables_keys[:]:
	value=variables[name]
	try: 
	  if not len(value): value='None'
	  exec(name+"="+value) in None,computed_vars
	  variables_keys.remove(name)
	except (KeyError,NameError,ValueError,ZeroDivisionError) as detail: 
	  if count>=39: print detail,"("+str(name)+"="+str(value)+")"
	except ValueError as detail: print detail,knot_name+"="+str(super_knot); continue
      count+=1
    if count>=40: print "Couldn't compute some variable values. Knots:",super_knots_keys,", extra variables:",variables_keys