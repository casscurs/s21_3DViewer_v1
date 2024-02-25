# 3DViewer v1.0

This is a team project developed in collaboration with hunturek also student of School 21 in Moscow.

Implementation of 3DViewer v1.0.

![interface image](/materials/pumpkin.png)

## Chapter I

## Introduction

This project aims to develop a 3D wireframe model viewer (3D Viewer) using the C programming language. The viewer will load models from .obj files, enabling users to rotate, scale, and translate the models for viewing on the screen.

## Chapter II

## Information

A wireframe model represents an object in 3D graphics as a set of vertices and edges, defining the shape of the object in three-dimensional space.

### .Obj File Format for 3D Object Representation

The .obj file format, developed by Wavefront Technologies, is widely accepted for defining 3D geometry. It primarily represents vertex positions, texture coordinates, vertex normals, and polygonal faces.

In this project, only support for vertices and surface lists is necessary.

### Affine Transformations

Affine transformations, including translation, rotation, and scaling, are fundamental operations in 3D graphics. Translation moves objects in space, rotation changes their orientation, and scaling adjusts their size.

#### Translation

Translation shifts objects along the X, Y, or Z axes.

#### Rotation

Rotation changes the orientation of objects around the X, Y, or Z axes.

#### Scaling

Scaling alters the size of objects along the X, Y, or Z axes.

## Chapter III

## Part 1. 3DViewer

### Program Requirements

- Developed in C language (C11 standard) using gcc compiler
- Located in the src folder
- Built with a Makefile containing standard GNU targets
- Developed according to structured programming principles and Google style guide
- Includes full test coverage for model loading and affine transformations
- Supports loading a wireframe model from an obj file (vertices and surfaces only)
- Enables translation, rotation, and scaling of the model
- Utilizes a GUI library for C89/C99/C11 compatibility
- GUI should include model selection, visualization area, translation/rotation/scaling controls, and model information
- Handles models with up to 1,000,000 vertices without freezing

## Part 2. Bonus. Settings

### Additional Features

- Customizable projection type (parallel and central)
- Adjustable edge type (solid, dashed), color, and thickness
- Configurable display method for vertices (none, circle, square), color, and size
- Option to choose the background color
- Settings persistence between program restarts


## Part 3. Bonus. Record

- The program must allow saving the captured (rendered) images as bmp and jpeg files.
- The program must allow recording small screencasts by a special button - the current custom affine transformation of the loaded object into gif-animation (640x480, 10fps, 5s)

