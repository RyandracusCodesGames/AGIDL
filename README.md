# AGIDL
The ultimate open-source, feature-rich image library geared with a rich set of image codecs, image extraction, and image manipulation utility functions.

## Table Of Contents
- [About](#About)
- [Image Codecs](#Image-Codecs)
- [Features](#Features)
- [Examples](#Examples)
- [Compilation](#Compilation)

## About
Since the dawn of the age of computer graphics, there has been a desire to store graphical data inside a common format to retrieve at any point and to
manipulate said graphical data. Being simply a two-dimensional grid of color data, the computer image has formed the backbone of bringing life to a display monitor for us all to enjoy. Over the decades of this blossoming field of graphics programming and image processing, many file formats have come and gone. Some have stood
the test of time. Others have faded into obscurity, and some have found reduced roles in new homes in retro console homebrew developer communities. AGIDL, the Adaptive Graphics Image Display Library, serves to preserve and document this burgeoning field of computer graphics by offering a rich set of tools to read these long-since forgotten and obscure images that once
had a thriving home on various platforms, to manipulate and organize graphical data and write it into these image file formats, and to demonstrate modern and old-school
image processing and graphics programming techniques. AGIDL is uniquely different from the common image libraries written over the years because I myself am not an image processing/vision software engineer. I consider myself to be a graphics programmer who is fascinated by older-generation graphical topics such as software rasterization
and the adaptive tile refresh algorithm, the namesake of this library. I have always been fascinated by what hides underneath the various API calls that I use. I love figuring out the functionality behind various graphical techniques from the ground up. As such, this library took no inspiration from those aforementioned image libraries, and I charted out my own path to define what an image library needs to truly be complete. I long pondered how to bridge the gap between retro graphics programming, 5th-generation homebrew graphics, and modern image processing, and I believe that I have found a well-designed balance with a great API, interesting image file formats, and a variety of utility functions to help the end user equally chart out their own path.

## Image Codecs

|Image Name                   | EXTENSION | PLATFORM     | READ/WRITE |
|:---------------------------:|:---------:|:------------:|:----------:|
| Winodows BMP                | .BMP      | Windows/OS/2 | FULL R/W   |
| Truevision Graphcis Adapter | .TGA      | ANY          | FULL R/W   |
| TIM                         | .TIM      | Playstation 1| FULL R/W   |
| PiCture eXchange            | .PCX      | PC Paintbrush| MOST R/W   |
| LMP image                   | .LMP      | Quake        | FULL R/W   |
| Dreamcast PowerPVR          | .PVR      | Dreamcast    | MOST R/W   |
| Playstation Vita GXT        | .GXT      | PS Vita      | PARTIAL R/W|
| BTI                         | .BTI      | GameCube/Wii | FULL R/W   |


## Features
As stated previously, AGIDL is a very feature-rich image library for those who fit within its niche. Even if you don't quite fit in with its deepest use cases, the core features of AGIDL implement the most fundamental features of any image library allowing for the loading, editing, saving, conversion, and exporting of various image file formats which should serve the basic needs of anyone needing quick access to the basics of dealing with images. Here is the full list of features supported by AGIDL:

  * Loading, Saving, Editing, and Exporting Images
  * Conversion Between Various Images
  * Function That Will Search an Entire File for a Particular Type of Image
  * Convert Between Different Color Spaces and Bit Depths
  * OpenGL and Nintendo64-based Color Mixing, Color Palette Management/Creation, Color Format Conversion
  * Apply RLE Compression to Supported Images
  * Create Copies/Duplicates of an Image
  * Export Raw Colors of an Image To A C Header/Source File or Binary File
  * Bilinear and Trilinear Texture Filtering
  * Nearest Neighbor, Bilinear, and Trilinear Image Scaling
  * Nintendo64-esque Image Mirroring and Wrapping
  * Lightmap Generating and Texture Binding
  * Grayscale Image

## Examples

### Image Creation and Saving
```c
#include <stdio.h>
#include <agidl.h>

int main(){

  AGIDL_BMP* bmp = AGIDL_CreateBMP("mybmp.bmp",100,50,AGIDL_BGR_888);
  AGIDL_ClearBMP(bmp,AGIDL_GetColor(PURPLE,AGIDL_BGR_888));
  AGIDL_ExportBMP(bmp);
  AGIDL_FreeBMP(bmp);

  return 0;
}

```

## Compilation

