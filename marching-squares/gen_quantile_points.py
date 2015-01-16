#!/usr/bin/python
#
# usage: gen_quantile_points.py in_cdf
#
# Takes an input CDF+quantile file and
# emits the corresponding quantile points
#
# Input format:
# width height
# quantiles0, quantile1, quantile2, ...
# val_0_0, val_1_0, val_2_0, val_3_0, ...
# val_0_1, val_1_1, val_2_1, val_3_1, ...
# ...
#
# Output Format:
# p1.x p1.y p2.x p2.y p3.x p3.y ...
# p1.x p1.y p2.x p2.y p3.x p3.y ...
# p1.x p1.y p2.x p2.y p3.x p3.y ...
# ...
#
#

import sys
from math import sqrt
from vtk import *

# algorithm to merge line segments into polylines
def dist(p1, p2):
    dx = p2[0] - p1[0]
    dy = p2[1] - p1[1]
    return sqrt(dx * dx + dy * dy)

def merge_lines(lines, eps):
    incurves = lines
    outcurves = []
    while len(incurves) > 0:
        curve1 = incurves.pop()
        merged = True

        while merged:
            new_incurves = []
            merged = False

            for curve2 in incurves:
                if dist(curve1[0], curve2[0]) <= eps:
                    curve1 = curve2[1:] + curve1
                    merged = True

                elif dist(curve1[0], curve2[-1]) <= eps:
                    curve1 = curve2[:-1] + curve1
                    merged = True

                elif dist(curve1[-1], curve2[0]) <= eps:
                    curve1 = curve1 + curve2[1:]
                    merged = True

                elif dist(curve1[-1], curve2[-1]) <= eps:
                    curve1 = curve1 + curve2[:-1]
                    merged = True

                if merged == False:
                    new_incurves.append(curve2)

            incurves = new_incurves
        outcurves.append(curve1)
    return outcurves

# Setup Image Canvas data source
canvasSource = vtkImageCanvasSource2D()
canvasSource.SetNumberOfScalarComponents(1)

# read input CDF and write it to the canvas
width = 0
height = 0
curve_count = 1
quantiles = []
with open(sys.argv[1]) as cdf_file:
    # read dimensions
    header = cdf_file.readline().split(' ')
    width = int(header[0])
    height = int(header[1])

    # read quantiles
    quantile_line = cdf_file.readline().split(' ')
    quantiles = [float(l) for l in quantile_line]

    canvasSource.SetExtent(0, width-1, 0, height-1, 0, 0)
    canvasSource.SetDrawColor(0.0)
    canvasSource.FillBox(0, width, 0, height)

    # write cdf to canvas
    for y in range(height):
        row = cdf_file.readline().split(' ')
        for x in range(width):
            canvasSource.SetDrawColor(float(row[x]))
            canvasSource.DrawPoint(x, y)

canvasSource.Update()

# Set input to canvasSource
inputImage = canvasSource

# create marching squares algorithm
marchingSquares = vtkMarchingSquares()
marchingSquares.SetInputConnection(inputImage.GetOutputPort())
marchingSquares.SetImageRange(0, width, 0, height, 0, 0)
marchingSquares.CreateDefaultLocator()

# Run marching squares for each quantile
quantile_points = []
for quantile in quantiles:
    marchingSquares.GenerateValues(curve_count, quantile, quantile)
    marchingSquares.Update()

    # Get output from polyline generation
    polyData = marchingSquares.GetOutput()

    isolines = []
    for i in range(0, polyData.GetNumberOfCells()):
        cell = polyData.GetCell(i)

        isoline = []
        for j in range(0, cell.GetNumberOfPoints()):
            pointID = cell.GetPointId(j)
            point = polyData.GetPoint(pointID)
            isoline.append(point)
        isolines.append(isoline)

    if len(isolines) > 0:
        isocurves = merge_lines(isolines, 0.0)
        quantile_points.append(isocurves[0])
    else:
        quantile_points.append([])

for point_set in quantile_points:
    print ' '.join([str(p[0]) + " " + str(p[1]) for p in point_set])

##################################
# BELOW THIS IS JUST FOR RENDERING
##################################

# # create a rendering window and renderer
# ren = vtkRenderer()
# renWin = vtkRenderWindow()
# renWin.AddRenderer(ren)
# # create a renderwindowinteractor
# iren = vtkRenderWindowInteractor()
# iren.SetRenderWindow(renWin)
# #dataset mapper
# mapper = vtkDataSetMapper()
# mapper.SetInputData(inputImage.GetOutput())
# #polydata mapper
# polyMapper = vtkPolyDataMapper()
# polyMapper.SetInputData(marchingSquares.GetOutput())
# # actor
# guassianPlane = vtkActor()
# guassianPlane.SetMapper(polyMapper)
# # actor
# isolines = vtkActor()
# isolines.SetPosition(0, 0, 10)
# isolines.SetMapper(mapper)
# # assign actor to the renderer
# ren.AddActor(guassianPlane)
# ren.AddActor(isolines)
# # enable user interface interactor
# iren.Initialize()
# renWin.Render()
# iren.Start()