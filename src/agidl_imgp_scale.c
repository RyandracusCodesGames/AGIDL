/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_imgp_scale.c
*   Date: 12/9/2023
*   Version: 0.2b
*   Updated: 12/10/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdlib.h>
#include <string.h>
#include "agidl_imgp_scale.h"
#include "agidl_img_bmp.h"
#include "agidl_cc_mixer.h"

void * AGIDL_ScaleImgDataNearest(void* data, u16* width, u16* height, float sx, float sy, AGIDL_CLR_FMT fmt){
	if(AGIDL_GetBitCount(fmt) == 24 || AGIDL_GetBitCount(fmt) == 32){
		u16 worg = *width;
		u16 horg = *height;
		
		COLOR* clrs = (COLOR*)data;
		
		u16 newwidth = (u16)(worg*sx), newheight = (u16)(horg*sy);
		
		COLOR* scale = (COLOR*)malloc(sizeof(COLOR)*newwidth*newheight);
		
		float xscale = ((float)(worg-1)/newwidth);
		float yscale = ((float)(horg-1)/newheight);
		
		u16 x,y;
		for(y = 0; y < newheight; y++){
			for(x = 0; x < newwidth; x++){
				u16 x2 = (x*xscale);
				u16 y2 = (y*yscale);
				
				COLOR clr = AGIDL_GetClr(clrs,x2,y2,worg,horg);
				AGIDL_SetClr(scale,clr,x,y,newwidth,newheight);
			}
		}
		
		*width = newwidth;
		*height = newheight;
		
		free(clrs);

		return scale;
	}
	else{
		u16 worg = *width;
		u16 horg = *height;
		
		COLOR16* clrs = (COLOR16*)data;
		
		u16 newwidth = (u16)(worg*sx), newheight = (u16)(horg*sy);
		
		COLOR16* scale = (COLOR16*)malloc(sizeof(COLOR16)*newwidth*newheight);
		
		float xscale = ((float)(worg-1)/newwidth);
		float yscale = ((float)(horg-1)/newheight);
		
		u16 x,y;
		for(y = 0; y < newheight; y++){
			for(x = 0; x < newwidth; x++){
				u16 x2 = (x*xscale);
				u16 y2 = (y*yscale);
				
				COLOR16 clr = AGIDL_GetClr16(clrs,x2,y2,worg,horg);
				AGIDL_SetClr16(scale,clr,x,y,newwidth,newheight);
			}
		}
		
		*width = newwidth;
		*height = newheight;
		
		free(clrs);
		
		return scale;
	}
}

void * AGIDL_ScaleImgDataBilerp(void* data, u16* width, u16* height, float sx, float sy, AGIDL_CLR_FMT fmt){
	if(AGIDL_GetBitCount(fmt) == 24 || AGIDL_GetBitCount(fmt) == 32){
		u16 worg = *width;
		u16 horg = *height;
		
		COLOR* clrs = (COLOR*)data;
		
		u16 newwidth = (u16)(worg*sx), newheight = (u16)(horg*sy);
		
		COLOR* scale = (COLOR*)malloc(sizeof(COLOR)*newwidth*newheight);
		
		float xscale = ((float)(worg-1)/newwidth);
		float yscale = ((float)(horg-1)/newheight);
		
		float x_diff, y_diff;
		
		u16 x,y;
		for(y = 0; y < newheight; y++){
			for(x = 0; x < newwidth; x++){
				u16 x2 = (x*xscale);
				u16 y2 = (y*yscale);
				
				x_diff = (x*xscale)-x2;
				y_diff = (y*yscale)-y2;
				
				COLOR clr1 = AGIDL_GetClr(clrs,x2,y2,worg,horg);
				COLOR clr2 = AGIDL_GetClr(clrs,x2+1,y2,worg,horg);
				COLOR clr3 = AGIDL_GetClr(clrs,x2,y2+1,worg,horg);
				COLOR clr4 = AGIDL_GetClr(clrs,x2+1,y2+1,worg,horg);
				
				u8 r1 = AGIDL_GetR(clr1,fmt);
				u8 g1 = AGIDL_GetG(clr1,fmt);
				u8 b1 = AGIDL_GetB(clr1,fmt);
				
				u8 r2 = AGIDL_GetR(clr2,fmt);
				u8 g2 = AGIDL_GetG(clr2,fmt);
				u8 b2 = AGIDL_GetB(clr2,fmt);
				
				u8 r3 = AGIDL_GetR(clr3,fmt);
				u8 g3 = AGIDL_GetG(clr3,fmt);
				u8 b3 = AGIDL_GetB(clr3,fmt);
				
				u8 r4 = AGIDL_GetR(clr4,fmt);
				u8 g4 = AGIDL_GetG(clr4,fmt);
				u8 b4 = AGIDL_GetB(clr4,fmt);
				
				u8 r = r1*(1-x_diff)*(1-y_diff) + r2*(x_diff)+(1-y_diff) + r3*(y_diff)*(1-x_diff) + r4*(x_diff*y_diff);
				u8 g = g1*(1-x_diff)*(1-y_diff) + g2*(x_diff)+(1-y_diff) + g3*(y_diff)*(1-x_diff) + g4*(x_diff*y_diff);
				u8 b = b1*(1-x_diff)*(1-y_diff) + b2*(x_diff)+(1-y_diff) + b3*(y_diff)*(1-x_diff) + b4*(x_diff*y_diff);
				
				COLOR clr = AGIDL_RGB(r,g,b,fmt);
				
				AGIDL_SetClr(scale,clr,x,y,newwidth,newheight);
			}
		}
		
		*width = newwidth;
		*height = newheight;
		
		free(clrs);

		return scale;
	}
	else{
		u16 worg = *width;
		u16 horg = *height;
		
		COLOR16* clrs = (COLOR16*)data;
		
		u16 newwidth = (u16)(worg*sx), newheight = (u16)(horg*sy);
		
		COLOR16* scale = (COLOR16*)malloc(sizeof(COLOR16)*newwidth*newheight);
		
		float xscale = ((float)(worg-1)/newwidth);
		float yscale = ((float)(horg-1)/newheight);
		
		float x_diff, y_diff;
		
		u16 x,y;
		for(y = 0; y < newheight; y++){
			for(x = 0; x < newwidth; x++){
				u16 x2 = (x*xscale);
				u16 y2 = (y*yscale);
				
				x_diff = (x*xscale)-x2;
				y_diff = (y*yscale)-y2;
				
				COLOR16 clr1 = AGIDL_GetClr16(clrs,x2,y2,worg,horg);
				COLOR16 clr2 = AGIDL_GetClr16(clrs,x2+1,y2,worg,horg);
				COLOR16 clr3 = AGIDL_GetClr16(clrs,x2,y2+1,worg,horg);
				COLOR16 clr4 = AGIDL_GetClr16(clrs,x2+1,y2+1,worg,horg);
				
				u8 r1 = AGIDL_GetR(clr1,fmt);
				u8 g1 = AGIDL_GetG(clr1,fmt);
				u8 b1 = AGIDL_GetB(clr1,fmt);
				
				u8 r2 = AGIDL_GetR(clr2,fmt);
				u8 g2 = AGIDL_GetG(clr2,fmt);
				u8 b2 = AGIDL_GetB(clr2,fmt);
				
				u8 r3 = AGIDL_GetR(clr3,fmt);
				u8 g3 = AGIDL_GetG(clr3,fmt);
				u8 b3 = AGIDL_GetB(clr3,fmt);
				
				u8 r4 = AGIDL_GetR(clr4,fmt);
				u8 g4 = AGIDL_GetG(clr4,fmt);
				u8 b4 = AGIDL_GetB(clr4,fmt);
				
				u8 r = r1*(1-x_diff)*(1-y_diff) + r2*(x_diff)+(1-y_diff) + r3*(y_diff)*(1-x_diff) + r4*(x_diff*y_diff);
				u8 g = g1*(1-x_diff)*(1-y_diff) + g2*(x_diff)+(1-y_diff) + g3*(y_diff)*(1-x_diff) + g4*(x_diff*y_diff);
				u8 b = b1*(1-x_diff)*(1-y_diff) + b2*(x_diff)+(1-y_diff) + b3*(y_diff)*(1-x_diff) + b4*(x_diff*y_diff);
				
				COLOR16 clr = AGIDL_RGB16(r,g,b,fmt);
				
				AGIDL_SetClr16(scale,clr,x,y,newwidth,newheight);
			}
		}
		
		*width = newwidth;
		*height = newheight;
		
		free(clrs);

		return scale;
	}
}

void * AGIDL_ScaleImgData(void* data, u16* width, u16* height, float sx, float sy, AGIDL_SCALE scale, AGIDL_CLR_FMT fmt){
	switch(scale){
		case AGIDL_SCALE_NEAREST:{
			return AGIDL_ScaleImgDataNearest(data,width,height,sx,sy,fmt);
		}break;
		case AGIDL_SCALE_BILERP:{
			return AGIDL_ScaleImgDataBilerp(data,width,height,sx,sy,fmt);
		}break;
		case AGIDL_SCALE_TRILERP:{
		
		}break;
	}
	return AGIDL_ScaleImgDataNearest(data,width,height,sx,sy,fmt);
}