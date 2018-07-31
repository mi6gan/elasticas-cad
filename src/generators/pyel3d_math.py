# -*- coding: utf-8 -*-
from sage.all import *
var('t')
el_k=0.1
el_k=1.8
def line(P):
  f=symbolic_expression(P[0]+(P[-1]-P[0])*t).function(t)
  return f

def bezier_polynome_2(P):
  f=symbolic_expression(P[0]*(1-t)**2+P[1]*2*t*(1-t)+P[2]*t**2).function(t)
  return f
  
def bezier_polynome_3(P):
  f=symbolic_expression(P[0]*((1-t)**3)+P[1]*3*t*((1-t)**2)+P[2]*3*(t**2)*(1-t)+(t**3)*P[3]).function(t)
  return f
  
def bezier_polynome_4(P):  
  f=symbolic_expression( (t - 1)**4*P[0] - 4*(t - 1)**3*P[1]*t + 6*(t - 1)**2*P[2]*t**2 - 4*(t - 1)*P[3]*t**3+ P[4]*t**4 ).function(t)
  return f

def curve3_0_x(P):
     f=bezier_polynome_3(function_to_P[curve3_0_x](P))
     return f

def curve3_0_y(P):
  f=bezier_polynome_3(function_to_P[curve3_0_y](P))
  return f
  
def curve3_1_x(P):
  f=bezier_polynome_3(function_to_P[curve3_1_x](P))
  return f

def curve3_1_y(P):
  f=bezier_polynome_3(function_to_P[curve3_1_y](P))
  return f
  
def curve3_2_x(P):
  f=bezier_polynome_3(function_to_P[curve3_2_x](P))
  return f

def curve3_2_y(P):
  f=bezier_polynome_3(function_to_P[curve3_2_y](P))
  return f

def curve3_3_x(P):
  f=bezier_polynome_3(function_to_P[curve3_3_x](P))
  return f

def curve3_3_y(P):
  f=bezier_polynome_3(function_to_P[curve3_3_y](P))
  return f
  
def curve3_4_x(P):
  f=bezier_polynome_3(function_to_P[curve3_4_x](P))
  return f
  
def curve3_5_x(P):
  f=bezier_polynome_3(function_to_P[curve3_5_x](P))
  return f
  
def line_3(P): return bezier_polynome_3(function_to_P[line_3](P))

def line_3_1(P): return bezier_polynome_3(function_to_P[line_3_1](P))

def pseudo_ellipse_x_3(P): return bezier_polynome_3(function_to_P[pseudo_ellipse_x_3](P))
def pseudo_ellipse_y_3(P): return bezier_polynome_3(function_to_P[pseudo_ellipse_y_3](P))
def pseudo_ellipse_z_3(P): return bezier_polynome_3(function_to_P[pseudo_ellipse_z_3](P))

def pseudo_ellipse_y_3_1(P): return bezier_polynome_3(function_to_P[pseudo_ellipse_y_3_1](P))

function_to_Pcount={
    bezier_polynome_2: 3,
    bezier_polynome_3: 4,
    bezier_polynome_4: 5
}
function_to_P={
  pseudo_ellipse_x_3: lambda P: [P[0],P[0],P[0]+(el_k-1.0)*(P[-1]-P[0])/el_k,P[-1]],
  pseudo_ellipse_y_3: lambda P: [P[0],P[0]+(P[-1]-P[0])/el_k,P[-1],P[-1]],
  pseudo_ellipse_z_3: lambda P: [P[0],P[0],P[-1],P[-1]],
  #pseudo_ellipse_x_3_1: lambda P: [P[0],P[0],P[0]+(el_k-1.0)*(P[-1]-P[0])/el_k,P[-1]],
  pseudo_ellipse_y_3_1: lambda P: [P[0],P[0]+1.5*(P[-1]-P[0])/el_k,P[-1],P[-1]],
  #pseudo_ellipse_z_3_1: lambda P: [P[0],P[0],P[-1],P[-1]],
  line_3: lambda P: [P[0],P[0],P[-1],P[-1]],
  line_3_1: lambda P: [P[0],P[0]+(P[-1]-P[0])/3.0,P[0]+2.0*(P[-1]-P[0])/3.0,P[-1]],
  curve3_0_x:lambda P: [P[0],P[0]+(P[-1]-P[0])/3.0,P[-1],P[-1]],
  curve3_0_y:lambda P: [P[0],P[0],P[0]+2.0*(P[-1]-P[0])/3.0,P[-1]],
  curve3_1_x:lambda P: [P[0],P[0],P[-1],P[-1]],
  curve3_1_y:lambda P: [P[0],P[0]+(P[-1]-P[0])/3.0,P[0]+2.0*(P[-1]-P[0])/3.0,P[-1]],
  curve3_2_x:lambda P: [P[0],P[0],P[-1],P[-1]],
  curve3_2_y:lambda P: [P[0],P[0]+0.5*(P[-1]-P[0])/3.0,P[0]+1.5*(P[-1]-P[0])/3.0,P[-1]],
  curve3_3_x:lambda P: [P[0],P[0],P[-1],P[-1]],
  curve3_3_y:lambda P: [P[0],P[0]+0.5*(P[-1]-P[0])/3.0,P[0]+0.5*(P[-1]-P[0])/3.0,P[-1]],
  curve3_4_x:lambda P: [P[0],P[0],P[0]+1.5*(P[-1]-P[0])/3.0,P[-1]],
  curve3_5_x:lambda P: [P[0],P[0]+0.5*(P[-1]-P[0])/3.0,P[-1],P[-1]]
  
}
function_to_P[line]=lambda P: P
#function_to_P[bezier_polynome_3]=function_to_P[bezier_polynome_4]=lambda P: P

def computeCByLSM(P,C,polynome_f):
  C=C[:]
  phi=polynome_f(C)
  n=len(P)
  T=[float(i)/float(n-1) for i in range(0 ,n)]
  Q=sum([(phi(T[i])-P[i])**2 for i in range(0,n)])
  system=[]
  C_=[]
  for c in C:
    try:
      if not type(c) is float: system.append(diff(Q,c)==0); C_.append(c)
    except TypeError: print c
  if len(C_)==1: C__=C_[0]
  else: C__=C_
  solutions=solve(system,C__,solution_dict=True)
  ret=[]
  last_i=0
  for key in C_: 
      for i in range(last_i,len(C)):
          if not type(C[i]) is float: 
              C[i]=float(solutions[-1][key])
              last_i=i
              break
  E=0
  for i in range(0 ,n):E+=(P[i]-polynome_f(C)(T[i]))**2
  return C,sqrt(E)

def unproject(pnt, vp=[0,0,1024,768]): 
    '''
    | 2n/(r-l) 0 (r+l)/(r-l) 0 |
    | 0 2n/(t-b) (t+b)/(t-b) 0 |
    | 0 0 -(f+n)/(f-n) -2fn/(f-n) |
    | 0 0 -1 0 |
    '''
    max_z=max(vp[2],vp[3])
    x=pnt[0]; y=pnt[1]; z=pnt[2]
    nx=2.0*(x-vp[0])/vp[2]-1.0
    ny=2.0*(y-vp[1])/vp[3]-1.0
    nz=-z/max_z
    n=1; f=1; l=-1
    r=1; t=1; b=-1
    w=-nz+((t+b)*ny)/(2*n)+((r+l)*nx)/(2*n)-(-n-f)/(2*f*n)
    x_=(((r-l)*nx)/(2*n))/w
    y_=(((t-b)*ny)/(2*n))/w
    z_=-(f-n)/(2*f*n)
    return (x_+1)*(vp[2]/2.0)+vp[0],(y_+1)*(vp[3]/2.0)+vp[1]

def computeRegressionC(X,Y,N,M=-1):
    if M<0: M=min(len(X),len(Y))
    left=[]
    right=[]
    b=[var('b'+str(i)) for i in range(N+1)]
    left=[0]*(N+1)
    right=[0]*(N+1)
    for k in range(N+1):
        if k: xik=0
        else: xik=M
        for i in range(1,M+1):
            if k: 
                xik+=X[i-1][k-1]
                left[k]+=Y[i-1]*X[i-1][k-1]
            else: left[k]+=Y[i-1]
            for j in range(1,N+1): 
                if k: right[k]+=b[j]*X[i-1][j-1]*X[i-1][k-1]
                else: right[k]+=b[j]*X[i-1][j-1]
        right[k]+=b[0]*xik
    system=[]
    for i in range(len(left)): system.append(right[i]==left[i])
    solutions=solve(system,b,solution_dict=True)
    ret=[]
    for key in b: ret.append(solutions[-1][key])
    return ret