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
AGIDL implements a very simple, easy-to-use API that is surprisingly intuitive. **Every function begins with the prefix AGIDL_** and is followed by some operation request to create, save, load, export, or manipulate an image. If you wish to load any image, you simply write **AGIDL_LoadIMG**. For an original Sony Playstation TIM image, you would write **AGIDL_LoadTIM("mytim.tim")**. In the load functions, the file extension doesn't matter as long as it contains properly formatted TIM image data. When the eventual all-encompassing LoadIMG() function is added to AGIDL, the file extension will become important. It's also important to note that **AGIDL relies heavily on pointers to its image structures**, so almost any image that you use should be a pointer type to any image supported in AGIDL.

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
![mybmp](https://github.com/RyandracusCodesGames/AGIDL/assets/108719757/ab055d6a-d978-4c14-b1db-9245dc07d355)

### Image Conversion
```c
#include <stdio.h>
#include <agidl.h>

int main(){

  AGIDL_BTI* bti = AGIDL_LoadBTI("cube.bti");
  AGIDL_BMP* bmp = AGIDL_ConvertBTI2BMP(bti);
  AGIDL_ExportBMP(bmp);
  AGIDL_FreeBMP(bmp);
  AGIDL_FreeBTI(bti);

  return 0;
}
```
### Wrap and Mirror Image
```c
#include <stdio.h>
#include <agidl.h> 

int main(){
	
	AGIDL_BMP* bmp = AGIDL_LoadBMP("mirror.bmp");
	AGIDL_SetBMPFilename(bmp,"forest.bmp");
	AGIDL_WrapAndMirrorBMP(bmp,4,MIRROR_LEFT_TO_RIGHT);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	
	return 0;
}
```
![mirror](https://github.com/RyandracusCodesGames/AGIDL/assets/108719757/cad08cb2-fd8a-4652-9b73-300f93616191)
![wrap_and_mirror_tree](https://github.com/RyandracusCodesGames/AGIDL/assets/108719757/e08c89a4-ba91-4588-bac8-cff0616d9f93)

### Image Search
```c
#include <stdio.h>
#include <agidl.h>

int main(){

  AGIDL_TIMSearchFileOnDisk("GAME.RSC",AGIDL_IMG_BMP,1);
  
  return 0;
}
```
The joys of randomly extracting image data from a PS1 game. A random angel T-Posing!
![tpose](https://github.com/RyandracusCodesGames/AGIDL/assets/108719757/73a21125-e48e-479b-a6ab-c1a0b0a3853b)

### Retro Pixel Shader
```c
#include <stdio.h>
#include <agidl.h> 

int main(){
	AGIDL_CLR_FMT fmt = AGIDL_RGB_888;
	
	COLOR blue = AGIDL_GetColor(BLUE,fmt), red = AGIDL_GetColor(RED,fmt);
	COLOR purple = AGIDL_BlendColor(blue,red,0.3f,CC_BLEND_CLR_SRCINV,fmt);
	
	AGIDL_BMP* bmp = AGIDL_CreateBMP("blendclr.bmp",100,50,fmt);
	AGIDL_ClearBMP(bmp,purple);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	
	blue = AGIDL_RGB(1,1,255,fmt); red = AGIDL_RGB(255,1,1,fmt);
	purple = AGIDL_ColorCombine(blue,red,CC_SUB_AND_INTERP_CLR2,fmt);
	
	AGIDL_BMP* bmp2 = AGIDL_CreateBMP("n64_blendclr.bmp",100,50,fmt);
	AGIDL_ClearBMP(bmp2,purple);
	AGIDL_ExportBMP(bmp2);
	AGIDL_FreeBMP(bmp2);
	
	return 0;
}
```
OpenGL Color Mixing Results
![blendclr](https://github.com/RyandracusCodesGames/AGIDL/assets/108719757/8309ae1d-6543-453d-96e5-824c81937e1f)
Ninetendo64-esque Color Mixing Results
![n64_blendclr](https://github.com/RyandracusCodesGames/AGIDL/assets/108719757/e10bd260-2427-47d5-b658-f2921aa35689)

### Image Filtering
```c
#include <stdio.h>
#include <agidl.h> 

int main(){
	
	AGIDL_BMP* bmp = AGIDL_LoadBMP("quake_tex.bmp");
	AGIDL_SetBMPFilename(bmp,"bilin_filter.bmp");
	AGIDL_FilterBilerpBMP(bmp);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	
	AGIDL_BMP* bmp2 = AGIDL_LoadBMP("quake_tex.bmp");
	AGIDL_SetBMPFilename(bmp2,"trilin_filter.bmp");
	AGIDL_FilterTrilerpBMP(bmp2);
	AGIDL_ExportBMP(bmp2);
	AGIDL_FreeBMP(bmp2);
	
	return 0;
}
```
*No-Filtering*
![quake_tex](https://github.com/RyandracusCodesGames/AGIDL/assets/108719757/67db37ed-da77-41fa-9da1-c927c04a9642)
*Bilinear Filtering*
![agidl_bi_filter](https://github.com/RyandracusCodesGames/AGIDL/assets/108719757/499a2c8d-ab48-47ed-b73d-a72aa7b27844)
*Trilinear Filtering*
![agidl_tri_filter](https://github.com/RyandracusCodesGames/AGIDL/assets/108719757/7e901d01-b028-4bca-bcd3-d51f66926cee)

## Compilation

