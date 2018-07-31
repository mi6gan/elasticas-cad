# -*- coding: utf-8 -*-
import ModelDataGenerator as MDG
import Models
import PyEl3d
import math
models={}
def update(name,visible=None,bearing_models=[]):
  if not name in models: 
    if name in Models.__dict__ and type(Models.__dict__[name])==type(MDG.Basic): models[name]=Models.__dict__[name]()
    else: models[name]=MDG.Basic()
  if len(bearing_models): models[name].bearing_model=models[bearing_models[-1]]
  if not (visible is None): models[name].setVisiblity(visible)
  elif visible is None: models[name].update()
  
  
  
#models["MensJacket"]=MensJacket(models["Man"])

