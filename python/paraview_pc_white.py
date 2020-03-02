#!/usr/bin/pvpython

from paraview.simple import *

#position camera
view = GetActiveView()
if not view:
    view = CreateRenderView()

#draw the object
Show()


dp = GetDisplayProperties()

#set point color
dp.AmbientColor = [1, 1, 1] #red

#set surface color
dp.DiffuseColor = [0, 1, 0] #blue

#set point size
dp.PointSize = 2

#set representation
dp.Representation = "Points"

Render()