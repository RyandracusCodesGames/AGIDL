/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023-2024 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_imgp_filter.c
*   Date: 12/13/2023
*   Version: 0.2b
*   Updated: 1/29/2024
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdlib.h>
#include "agidl_imgp_filter.h"
#include "agidl_imgp_scale.h"
#include "agidl_img_bmp.h"
#include "agidl_cc_mixer.h"
#include "agidl_math_utils.h"

COLOR AGIDL_SamplePointNearest(void* data, float u, float v, u32 width, u32 height, AGIDL_CLR_FMT fmt){
	u = AGIDL_Clampf(0.0f,u,1.0f);
	v = AGIDL_Clampf(0.0f,v,1.0f);
	
	int x = u * width - 0.5f;
	int y = v * height - 0.5f;
	
	x = AGIDL_Clamp(0,x,width);
	y = AGIDL_Clamp(0,y,height);
	
	if(AGIDL_GetBitCount(fmt) == 16){
		COLOR16* clrdata = (COLOR16*)data;
		return AGIDL_GetClr16(clrdata,x,y,width,height);
	}
	else{
		COLOR* clrdata = (COLOR*)data;
		return AGIDL_GetClr(clrdata,x,y,width,height);
	}
}

COLOR AGIDL_SamplePointBilerp(void* data, float u, float v, u32 width, u32 height, AGIDL_CLR_FMT fmt){
	u = AGIDL_Clampf(0.0f,u,1.0f);
	v = AGIDL_Clampf(0.0f,v,1.0f);
	
	int x = u * width - 0.5f;
	int y = v * height - 0.5f;
	
	x = AGIDL_Clamp(0,x,width);
	y = AGIDL_Clamp(0,y,height);
	
	if(AGIDL_GetBitCount(fmt) == 16){
		COLOR16* clrdata = (COLOR16*)data;
		
		COLOR16 clr1 = AGIDL_GetClr16(clrdata,x,y,width,height);
		COLOR16 clr2 = AGIDL_GetClr16(clrdata,x+1,y,width,height);
		COLOR16 clr3 = AGIDL_GetClr16(clrdata,x,y+1,width,height);
		COLOR16 clr4 = AGIDL_GetClr16(clrdata,x+1,y+1,width,height);
		
		return AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5f,0.5f,fmt);
	}
	else{
		COLOR* clrdata = (COLOR*)data;
		
		COLOR clr1 = AGIDL_GetClr(clrdata,x,y,width,height);
		COLOR clr2 = AGIDL_GetClr(clrdata,x+1,y,width,height);
		COLOR clr3 = AGIDL_GetClr(clrdata,x,y+1,width,height);
		COLOR clr4 = AGIDL_GetClr(clrdata,x+1,y+1,width,height);
		
		return AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5f,0.5f,fmt);
	}
}

COLOR AGIDL_SamplePointTrilerp(void* data, float u, float v, u32 width, u32 height, AGIDL_CLR_FMT fmt){
	u = AGIDL_Clampf(0.0f,u,1.0f);
	v = AGIDL_Clampf(0.0f,v,1.0f);
	
	int x = u * width - 0.5f;
	int y = v * height - 0.5f;
	
	x = AGIDL_Clamp(0,x,width);
	y = AGIDL_Clamp(0,y,height);
	
	if(AGIDL_GetBitCount(fmt) == 16){
		COLOR16* clrdata = (COLOR16*)data;
		COLOR16* clrscpy = (COLOR16*)malloc(sizeof(COLOR16)*width*height);
		AGIDL_ClrMemcpy16(clrscpy,clrdata,width*height);
		
		u16 w = width, h = height;
		
		COLOR16* clrscale = (COLOR16*)malloc(sizeof(COLOR16)*w*h);
		clrscale = (COLOR16*)AGIDL_ScaleImgDataNearest(clrscpy,&w,&h,0.5f,0.5f,fmt);
		
		AGIDL_FilterImgDataBilerp(clrscale,w,h,fmt);
		
		float x_scale = ((float)(w-1)/width);
		float y_scale = ((float)(h-1)/height);
		
		int xx = x * x_scale;
		int yy = y * y_scale;
		
		COLOR16 clr1 = AGIDL_GetClr16(clrdata,x,y,width,height);
		COLOR16 clr2 = AGIDL_GetClr16(clrdata,x+1,y,width,height);
		COLOR16 clr3 = AGIDL_GetClr16(clrdata,x,y+1,width,height);
		COLOR16 clr4 = AGIDL_GetClr16(clrdata,x+1,y+1,width,height);
		
		COLOR16 clr1s = AGIDL_GetClr16(clrscale,xx,yy,w,h);
		COLOR16 clr2s = AGIDL_GetClr16(clrscale,xx+1,yy,w,h);
		COLOR16 clr3s = AGIDL_GetClr16(clrscale,xx,yy+1,w,h);
		COLOR16 clr4s = AGIDL_GetClr16(clrscale,xx+1,yy+1,w,h);
		
		COLOR16 bilerp1 = AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5f,0.5f,fmt);
		COLOR16 bilerp2 = AGIDL_BilerpColor(clr1s,clr2s,clr3s,clr4s,0.5f,0.5f,fmt);
		
		free(clrscpy);
		
		return AGIDL_InterpColor(bilerp1,bilerp2,0.5f,fmt);
	}
	else{
		COLOR* clrdata = (COLOR*)data;
		COLOR* clrscpy = (COLOR*)malloc(sizeof(COLOR)*width*height);
		AGIDL_ClrMemcpy(clrscpy,clrdata,width*height);
		
		u16 w = width, h = height;
		
		COLOR* clrscale = (COLOR*)malloc(sizeof(COLOR)*w*h);
		clrscale = (COLOR*)AGIDL_ScaleImgDataNearest(clrscpy,&w,&h,0.5f,0.5f,fmt);
		
		AGIDL_FilterImgDataBilerp(clrscale,w,h,fmt);
		
		float x_scale = ((float)(w-1)/width);
		float y_scale = ((float)(h-1)/height);
		
		int xx = x * x_scale;
		int yy = y * y_scale;
		
		COLOR clr1 = AGIDL_GetClr(clrdata,x,y,width,height);
		COLOR clr2 = AGIDL_GetClr(clrdata,x+1,y,width,height);
		COLOR clr3 = AGIDL_GetClr(clrdata,x,y+1,width,height);
		COLOR clr4 = AGIDL_GetClr(clrdata,x+1,y+1,width,height);
		
		COLOR clr1s = AGIDL_GetClr(clrscale,xx,yy,w,h);
		COLOR clr2s = AGIDL_GetClr(clrscale,xx+1,yy,w,h);
		COLOR clr3s = AGIDL_GetClr(clrscale,xx,yy+1,w,h);
		COLOR clr4s = AGIDL_GetClr(clrscale,xx+1,yy+1,w,h);
		
		COLOR bilerp1 = AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5f,0.5f,fmt);
		COLOR bilerp2 = AGIDL_BilerpColor(clr1s,clr2s,clr3s,clr4s,0.5f,0.5f,fmt);
		
		free(clrscpy);
		
		return AGIDL_InterpColor(bilerp1,bilerp2,0.5f,fmt);
	}
}

void AGIDL_FilterImgDataBilerp(void* data, u32 width, u32 height, AGIDL_CLR_FMT fmt){
	if(AGIDL_GetBitCount(fmt) == 24 || AGIDL_GetBitCount(fmt) == 32){
		COLOR* clrs = (COLOR*)data;

		u16 x,y;
		for(y = 0; y < height; y++){
			for(x = 0; x < width; x++){
				COLOR clr1 = AGIDL_GetClr(clrs,x,y,width,height);
				COLOR clr2 = AGIDL_GetClr(clrs,x+1,y,width,height);
				COLOR clr3 = AGIDL_GetClr(clrs,x,y+1,width,height);
				COLOR clr4 = AGIDL_GetClr(clrs,x+1,y+1,width,height);
				
				if(x == width-1){
					clr1 = AGIDL_GetClr(clrs,x,y,width,height);
					clr2 = AGIDL_GetClr(clrs,x-1,y,width,height);
					clr3 = AGIDL_GetClr(clrs,x,y+1,width,height);
					clr4 = AGIDL_GetClr(clrs,x-1,y+1,width,height);
				}
				
				if(y == height-1){
					clr1 = AGIDL_GetClr(clrs,x,y,width,height);
					clr2 = AGIDL_GetClr(clrs,x+1,y,width,height);
					clr3 = AGIDL_GetClr(clrs,x,y-1,width,height);
					clr4 = AGIDL_GetClr(clrs,x+1,y-1,width,height);
				}
				
				COLOR clr = AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5,0.5,fmt);
				
				AGIDL_SetClr(clrs,clr,x,y,width,height); 
			}
		}
	}
	else{
		COLOR16* clrs = (COLOR16*)data;

		u16 x,y;
		for(y = 0; y < height; y++){
			for(x = 0; x < width; x++){
				COLOR16 clr1 = AGIDL_GetClr16(clrs,x,y,width,height);
				COLOR16 clr2 = AGIDL_GetClr16(clrs,x+1,y,width,height);
				COLOR16 clr3 = AGIDL_GetClr16(clrs,x,y+1,width,height);
				COLOR16 clr4 = AGIDL_GetClr16(clrs,x+1,y+1,width,height);
				
				if(x == width-1){
					clr1 = AGIDL_GetClr16(clrs,x,y,width,height);
					clr2 = AGIDL_GetClr16(clrs,x-1,y,width,height);
					clr3 = AGIDL_GetClr16(clrs,x,y+1,width,height);
					clr4 = AGIDL_GetClr16(clrs,x-1,y+1,width,height);
				}
				
				if(y == height-1){
					clr1 = AGIDL_GetClr16(clrs,x,y,width,height);
					clr2 = AGIDL_GetClr16(clrs,x+1,y,width,height);
					clr3 = AGIDL_GetClr16(clrs,x,y-1,width,height);
					clr4 = AGIDL_GetClr16(clrs,x+1,y-1,width,height);
				}
				
				COLOR16 clr = AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5,0.5,fmt);
				
				AGIDL_SetClr16(clrs,clr,x,y,width,height); 
			}
		}
	}
}

void AGIDL_FastFilterImgDataBilerp(void* data, u32 width, u32 height, AGIDL_CLR_FMT fmt){
	if(AGIDL_GetBitCount(fmt) == 16){
		COLOR16* clr_data = (COLOR16*)data;
		
		int x,y;
		for(y = 0; y < height; y++){
			for(x = 0; x < width; x++){
				COLOR16 clr1 = AGIDL_GetClr16(clr_data,x,y,width,height);
				COLOR16 clr2 = AGIDL_GetClr16(clr_data,x+1,y,width,height);
				COLOR16 clr3 = AGIDL_GetClr16(clr_data,x,y+1,width,height);
				COLOR16 clr4 = AGIDL_GetClr16(clr_data,x+1,y+1,width,height);
				
				if(x == width-1){
					clr1 = AGIDL_GetClr16(clr_data,x,y,width,height);
					clr2 = AGIDL_GetClr16(clr_data,x-1,y,width,height);
					clr3 = AGIDL_GetClr16(clr_data,x,y+1,width,height);
					clr4 = AGIDL_GetClr16(clr_data,x-1,y+1,width,height);
				}
				
				if(y == height-1){
					clr1 = AGIDL_GetClr16(clr_data,x,y,width,height);
					clr2 = AGIDL_GetClr16(clr_data,x+1,y,width,height);
					clr3 = AGIDL_GetClr16(clr_data,x,y-1,width,height);
					clr4 = AGIDL_GetClr16(clr_data,x+1,y-1,width,height);
				}
				
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
				
				u8 rtop = r1 + ((r2-r1) >> 1);
				u8 gtop = g1 + ((g2-g1) >> 1);
				u8 btop = b1 + ((b2-b1) >> 1);
				
				u8 rbot = r3 + ((r4-r3) >> 1);
				u8 gbot = g3 + ((g4-g3) >> 1);
				u8 bbot = b3 + ((b4-b3) >> 1);
				
				u8 rfinal = rtop + ((rbot-rtop) >> 1);
				u8 gfinal = gtop + ((gbot-gtop) >> 1);
				u8 bfinal = btop + ((bbot-btop) >> 1);
				
				AGIDL_SetClr16(clr_data,AGIDL_RGB16(rfinal,gfinal,bfinal,fmt),x,y,width,height);
			}
		}
	}
	else{
		COLOR* clr_data = (COLOR*)data;
		
		int x,y;
		for(y = 0; y < height; y++){
			for(x = 0; x < width; x++){
				COLOR clr1 = AGIDL_GetClr(clr_data,x,y,width,height);
				COLOR clr2 = AGIDL_GetClr(clr_data,x+1,y,width,height);
				COLOR clr3 = AGIDL_GetClr(clr_data,x,y+1,width,height);
				COLOR clr4 = AGIDL_GetClr(clr_data,x+1,y+1,width,height);
				
				if(x == width-1){
					clr1 = AGIDL_GetClr(clr_data,x,y,width,height);
					clr2 = AGIDL_GetClr(clr_data,x-1,y,width,height);
					clr3 = AGIDL_GetClr(clr_data,x,y+1,width,height);
					clr4 = AGIDL_GetClr(clr_data,x-1,y+1,width,height);
				}
				
				if(y == height-1){
					clr1 = AGIDL_GetClr(clr_data,x,y,width,height);
					clr2 = AGIDL_GetClr(clr_data,x+1,y,width,height);
					clr3 = AGIDL_GetClr(clr_data,x,y-1,width,height);
					clr4 = AGIDL_GetClr(clr_data,x+1,y-1,width,height);
				}
				
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
				
				u8 rtop = r1 + ((r2-r1) >> 1);
				u8 gtop = g1 + ((g2-g1) >> 1);
				u8 btop = b1 + ((b2-b1) >> 1);
				
				u8 rbot = r3 + ((r4-r3) >> 1);
				u8 gbot = g3 + ((g4-g3) >> 1);
				u8 bbot = b3 + ((b4-b3) >> 1);
				
				u8 rfinal = rtop + ((rbot-rtop) >> 1);
				u8 gfinal = gtop + ((gbot-gtop) >> 1);
				u8 bfinal = btop + ((bbot-btop) >> 1);
				
				AGIDL_SetClr(clr_data,AGIDL_RGB(rfinal,gfinal,bfinal,fmt),x,y,width,height);
			}
		}
	}
}

void AGIDL_FilterImgDataTrilerp(void* data, u32 width, u32 height, AGIDL_CLR_FMT fmt){
	if(AGIDL_GetBitCount(fmt) == 24 || AGIDL_GetBitCount(fmt) == 32){
		COLOR* clrs = (COLOR*)data;
		COLOR* clrscpy = (COLOR*)malloc(sizeof(COLOR)*width*height);
		
		AGIDL_ClrMemcpy(clrscpy,clrs,width*height);
		
		u16 w = width, h = height;
		
		COLOR* clrscale = (COLOR*)malloc(sizeof(COLOR)*w*h);
		clrscale = (COLOR*)AGIDL_ScaleImgDataNearest(clrscpy,&w,&h,0.5f,0.5f,fmt);
		
		AGIDL_FilterImgDataBilerp(clrscale,w,h,fmt);
		
		float x_scale = ((float)(w-1)/width);
		float y_scale = ((float)(h-1)/height);
		
		u32 x,y;
		for(y = 0; y < height; y++){
			for(x = 0; x < width; x++){
				
				u16 xx = (x * x_scale);
				u16 yy = (y * y_scale);
			
				COLOR clr1 = AGIDL_GetClr(clrs,x,y,width,height);
				COLOR clr2 = AGIDL_GetClr(clrs,x+1,y,width,height);
				COLOR clr3 = AGIDL_GetClr(clrs,x,y+1,width,height);
				COLOR clr4 = AGIDL_GetClr(clrs,x+1,y+1,width,height);
				
				COLOR clr1s = AGIDL_GetClr(clrscale,xx,yy,w,h);
				COLOR clr2s = AGIDL_GetClr(clrscale,xx+1,yy,w,h);
				COLOR clr3s = AGIDL_GetClr(clrscale,xx,yy+1,w,h);
				COLOR clr4s = AGIDL_GetClr(clrscale,xx+1,yy+1,w,h);
				
				if(x == width-1){
					clr1 = AGIDL_GetClr(clrs,x,y,width,height);
					clr2 = AGIDL_GetClr(clrs,x-1,y,width,height);
					clr3 = AGIDL_GetClr(clrs,x,y+1,width,height);
					clr4 = AGIDL_GetClr(clrs,x-1,y+1,width,height);
					
					clr1s = AGIDL_GetClr(clrscale,xx,yy,w,h);
					clr2s = AGIDL_GetClr(clrscale,xx-1,yy,w,h);
					clr3s = AGIDL_GetClr(clrscale,xx,yy+1,w,h);
					clr4s = AGIDL_GetClr(clrscale,xx-1,yy+1,w,h);
				}
				
				if(y == height-1){
					clr1 = AGIDL_GetClr(clrs,x,y,width,height);
					clr2 = AGIDL_GetClr(clrs,x+1,y,width,height);
					clr3 = AGIDL_GetClr(clrs,x,y-1,width,height);
					clr4 = AGIDL_GetClr(clrs,x+1,y-1,width,height);
					
					clr1s = AGIDL_GetClr(clrscale,xx,yy,w,h);
					clr2s = AGIDL_GetClr(clrscale,xx+1,yy,w,h);
					clr3s = AGIDL_GetClr(clrscale,xx,yy-1,w,h);
					clr4s = AGIDL_GetClr(clrscale,xx+1,yy-1,w,h);
				}
				
				COLOR clrbilerp1 = AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5f,0.5f,fmt);
				COLOR clrbilerp2 = AGIDL_BilerpColor(clr1s,clr2s,clr3s,clr4s,0.5f,0.5f,fmt);
				
				COLOR clr = AGIDL_InterpColor(clrbilerp1,clrbilerp2,0.5f,fmt);
				
				AGIDL_SetClr(clrs,clr,x,y,width,height);
			}
		}
		
		free(clrscale);
	}
	else{
		COLOR16* clrs = (COLOR16*)data;
		COLOR16* clrscpy = (COLOR16*)malloc(sizeof(COLOR16)*width*height);
		
		AGIDL_ClrMemcpy16(clrscpy,clrs,width*height);
		
		u16 w = width, h = height;
		
		COLOR16* clrscale = (COLOR16*)malloc(sizeof(COLOR16)*w*h);
		clrscale = (COLOR16*)AGIDL_ScaleImgDataNearest(clrscpy,&w,&h,0.5f,0.5f,fmt);
		
		AGIDL_FilterImgDataBilerp(clrscale,w,h,fmt);
		
		float x_scale = ((float)(w-1)/width);
		float y_scale = ((float)(h-1)/height);
		
		u32 x,y;
		for(y = 0; y < height; y++){
			for(x = 0; x < width; x++){
				
				u16 xx = (x * x_scale);
				u16 yy = (y * y_scale);
			
				COLOR16 clr1 = AGIDL_GetClr16(clrs,x,y,width,height);
				COLOR16 clr2 = AGIDL_GetClr16(clrs,x+1,y,width,height);
				COLOR16 clr3 = AGIDL_GetClr16(clrs,x,y+1,width,height);
				COLOR16 clr4 = AGIDL_GetClr16(clrs,x+1,y+1,width,height);
				
				COLOR16 clr1s = AGIDL_GetClr16(clrscale,xx,yy,w,h);
				COLOR16 clr2s = AGIDL_GetClr16(clrscale,xx+1,yy,w,h);
				COLOR16 clr3s = AGIDL_GetClr16(clrscale,xx,yy+1,w,h);
				COLOR16 clr4s = AGIDL_GetClr16(clrscale,xx+1,yy+1,w,h);
				
				if(x == width-1){
					clr1 = AGIDL_GetClr16(clrs,x,y,width,height);
					clr2 = AGIDL_GetClr16(clrs,x-1,y,width,height);
					clr3 = AGIDL_GetClr16(clrs,x,y+1,width,height);
					clr4 = AGIDL_GetClr16(clrs,x-1,y+1,width,height);
					
					clr1s = AGIDL_GetClr16(clrscale,xx,yy,w,h);
					clr2s = AGIDL_GetClr16(clrscale,xx-1,yy,w,h);
					clr3s = AGIDL_GetClr16(clrscale,xx,yy+1,w,h);
					clr4s = AGIDL_GetClr16(clrscale,xx-1,yy+1,w,h);
				}
				
				if(y == height-1){
					clr1 = AGIDL_GetClr16(clrs,x,y,width,height);
					clr2 = AGIDL_GetClr16(clrs,x+1,y,width,height);
					clr3 = AGIDL_GetClr16(clrs,x,y-1,width,height);
					clr4 = AGIDL_GetClr16(clrs,x+1,y-1,width,height);
					
					clr1s = AGIDL_GetClr16(clrscale,xx,yy,w,h);
					clr2s = AGIDL_GetClr16(clrscale,xx+1,yy,w,h);
					clr3s = AGIDL_GetClr16(clrscale,xx,yy-1,w,h);
					clr4s = AGIDL_GetClr16(clrscale,xx+1,yy-1,w,h);
				}
				
				COLOR16 clrbilerp1 = AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5f,0.5f,fmt);
				COLOR16 clrbilerp2 = AGIDL_BilerpColor(clr1s,clr2s,clr3s,clr4s,0.5f,0.5f,fmt);
				
				COLOR16 clr = AGIDL_InterpColor(clrbilerp1,clrbilerp2,0.5f,fmt);
				
				AGIDL_SetClr16(clrs,clr,x,y,width,height);
			}
		}
		
		free(clrscale);
	}
}

void AGIDL_FastFilterImgDataTrilerp(void* data, u32 width, u32 height, AGIDL_CLR_FMT fmt){
	if(AGIDL_GetBitCount(fmt) == 24 || AGIDL_GetBitCount(fmt) == 32){
		COLOR* clrs = (COLOR*)data;
		COLOR* clrscpy = (COLOR*)malloc(sizeof(COLOR)*width*height);
		
		AGIDL_ClrMemcpy(clrscpy,clrs,width*height);
		
		u16 w = width, h = height;
		
		COLOR* clrscale = (COLOR*)malloc(sizeof(COLOR)*w*h);
		clrscale = (COLOR*)AGIDL_ScaleImgDataNearest(clrscpy,&w,&h,0.5f,0.5f,fmt);
		
		AGIDL_FastFilterImgDataBilerp(clrscale,w,h,fmt);
		
		float x_scale = ((float)(w-1)/width);
		float y_scale = ((float)(h-1)/height);
		
		u32 x,y;
		for(y = 0; y < height; y++){
			for(x = 0; x < width; x++){
				
				u16 xx = (x * x_scale);
				u16 yy = (y * y_scale);
			
				COLOR clr1 = AGIDL_GetClr(clrs,x,y,width,height);
				COLOR clr2 = AGIDL_GetClr(clrs,x+1,y,width,height);
				COLOR clr3 = AGIDL_GetClr(clrs,x,y+1,width,height);
				COLOR clr4 = AGIDL_GetClr(clrs,x+1,y+1,width,height);
				
				COLOR clr1s = AGIDL_GetClr(clrscale,xx,yy,w,h);
				COLOR clr2s = AGIDL_GetClr(clrscale,xx+1,yy,w,h);
				COLOR clr3s = AGIDL_GetClr(clrscale,xx,yy+1,w,h);
				COLOR clr4s = AGIDL_GetClr(clrscale,xx+1,yy+1,w,h);
				
				if(x == width-1){
					clr1 = AGIDL_GetClr(clrs,x,y,width,height);
					clr2 = AGIDL_GetClr(clrs,x-1,y,width,height);
					clr3 = AGIDL_GetClr(clrs,x,y+1,width,height);
					clr4 = AGIDL_GetClr(clrs,x-1,y+1,width,height);
					
					clr1s = AGIDL_GetClr(clrscale,xx,yy,w,h);
					clr2s = AGIDL_GetClr(clrscale,xx-1,yy,w,h);
					clr3s = AGIDL_GetClr(clrscale,xx,yy+1,w,h);
					clr4s = AGIDL_GetClr(clrscale,xx-1,yy+1,w,h);
				}
				
				if(y == height-1){
					clr1 = AGIDL_GetClr(clrs,x,y,width,height);
					clr2 = AGIDL_GetClr(clrs,x+1,y,width,height);
					clr3 = AGIDL_GetClr(clrs,x,y-1,width,height);
					clr4 = AGIDL_GetClr(clrs,x+1,y-1,width,height);
					
					clr1s = AGIDL_GetClr(clrscale,xx,yy,w,h);
					clr2s = AGIDL_GetClr(clrscale,xx+1,yy,w,h);
					clr3s = AGIDL_GetClr(clrscale,xx,yy-1,w,h);
					clr4s = AGIDL_GetClr(clrscale,xx+1,yy-1,w,h);
				}
				
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
				
				u8 rtop = r1 + ((r2-r1) >> 1);
				u8 gtop = g1 + ((g2-g1) >> 1);
				u8 btop = b1 + ((b2-b1) >> 1);
				
				u8 rbot = r3 + ((r4-r3) >> 1);
				u8 gbot = g3 + ((g4-g3) >> 1);
				u8 bbot = b3 + ((b4-b3) >> 1);
				
				u8 rbilerp1 = rtop + ((rbot-rtop) >> 1);
				u8 gbilerp1 = gtop + ((gbot-gtop) >> 1);
				u8 bbilerp1 = btop + ((bbot-btop) >> 1);
				
				r1 = AGIDL_GetR(clr1s,fmt);
			    g1 = AGIDL_GetG(clr1s,fmt);
				b1 = AGIDL_GetB(clr1s,fmt);
				
				r2 = AGIDL_GetR(clr2s,fmt);
				g2 = AGIDL_GetG(clr2s,fmt);
				b2 = AGIDL_GetB(clr2s,fmt);
				
				r3 = AGIDL_GetR(clr3s,fmt);
				g3 = AGIDL_GetG(clr3s,fmt);
				b3 = AGIDL_GetB(clr3s,fmt);
				
				r4 = AGIDL_GetR(clr4s,fmt);
				g4 = AGIDL_GetG(clr4s,fmt);
				b4 = AGIDL_GetB(clr4s,fmt);
				
				rtop = r1 + ((r2-r1) >> 1);
				gtop = g1 + ((g2-g1) >> 1);
				btop = b1 + ((b2-b1) >> 1);
				
				rbot = r3 + ((r4-r3) >> 1);
				gbot = g3 + ((g4-g3) >> 1);
				bbot = b3 + ((b4-b3) >> 1);
				
				u8 rbilerp2 = rtop + ((rbot-rtop) >> 1);
				u8 gbilerp2 = gtop + ((gbot-gtop) >> 1);
				u8 bbilerp2 = btop + ((bbot-btop) >> 1);
				
				u8 rfinal = rbilerp1 + ((rbilerp2-rbilerp1) >> 1);
				u8 gfinal = gbilerp1 + ((gbilerp2-gbilerp1) >> 1);
				u8 bfinal = bbilerp1 + ((bbilerp2-bbilerp1) >> 1);
				
				AGIDL_SetClr(clrs,AGIDL_RGB(rfinal,gfinal,bfinal,fmt),x,y,width,height);
			}
		}
		
		free(clrscale);
	}
	else{
		COLOR16* clrs = (COLOR16*)data;
		COLOR16* clrscpy = (COLOR16*)malloc(sizeof(COLOR16)*width*height);
		
		AGIDL_ClrMemcpy16(clrscpy,clrs,width*height);
		
		u16 w = width, h = height;
		
		COLOR16* clrscale = (COLOR16*)malloc(sizeof(COLOR16)*w*h);
		clrscale = (COLOR16*)AGIDL_ScaleImgDataNearest(clrscpy,&w,&h,0.5f,0.5f,fmt);
		
		AGIDL_FastFilterImgDataBilerp(clrscale,w,h,fmt);
		
		float x_scale = ((float)(w-1)/width);
		float y_scale = ((float)(h-1)/height);
		
		u32 x,y;
		for(y = 0; y < height; y++){
			for(x = 0; x < width; x++){
				
				u16 xx = (x * x_scale);
				u16 yy = (y * y_scale);
			
				COLOR16 clr1 = AGIDL_GetClr16(clrs,x,y,width,height);
				COLOR16 clr2 = AGIDL_GetClr16(clrs,x+1,y,width,height);
				COLOR16 clr3 = AGIDL_GetClr16(clrs,x,y+1,width,height);
				COLOR16 clr4 = AGIDL_GetClr16(clrs,x+1,y+1,width,height);
				
				COLOR16 clr1s = AGIDL_GetClr16(clrscale,xx,yy,w,h);
				COLOR16 clr2s = AGIDL_GetClr16(clrscale,xx+1,yy,w,h);
				COLOR16 clr3s = AGIDL_GetClr16(clrscale,xx,yy+1,w,h);
				COLOR16 clr4s = AGIDL_GetClr16(clrscale,xx+1,yy+1,w,h);
				
				if(x == width-1){
					clr1 = AGIDL_GetClr16(clrs,x,y,width,height);
					clr2 = AGIDL_GetClr16(clrs,x-1,y,width,height);
					clr3 = AGIDL_GetClr16(clrs,x,y+1,width,height);
					clr4 = AGIDL_GetClr16(clrs,x-1,y+1,width,height);
					
					clr1s = AGIDL_GetClr16(clrscale,xx,yy,w,h);
					clr2s = AGIDL_GetClr16(clrscale,xx-1,yy,w,h);
					clr3s = AGIDL_GetClr16(clrscale,xx,yy+1,w,h);
					clr4s = AGIDL_GetClr16(clrscale,xx-1,yy+1,w,h);
				}
				
				if(y == height-1){
					clr1 = AGIDL_GetClr16(clrs,x,y,width,height);
					clr2 = AGIDL_GetClr16(clrs,x+1,y,width,height);
					clr3 = AGIDL_GetClr16(clrs,x,y-1,width,height);
					clr4 = AGIDL_GetClr16(clrs,x+1,y-1,width,height);
					
					clr1s = AGIDL_GetClr16(clrscale,xx,yy,w,h);
					clr2s = AGIDL_GetClr16(clrscale,xx+1,yy,w,h);
					clr3s = AGIDL_GetClr16(clrscale,xx,yy-1,w,h);
					clr4s = AGIDL_GetClr16(clrscale,xx+1,yy-1,w,h);
				}
				
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
				
				u8 rtop = r1 + ((r2-r1) >> 1);
				u8 gtop = g1 + ((g2-g1) >> 1);
				u8 btop = b1 + ((b2-b1) >> 1);
				
				u8 rbot = r3 + ((r4-r3) >> 1);
				u8 gbot = g3 + ((g4-g3) >> 1);
				u8 bbot = b3 + ((b4-b3) >> 1);
				
				u8 rbilerp1 = rtop + ((rbot-rtop) >> 1);
				u8 gbilerp1 = gtop + ((gbot-gtop) >> 1);
				u8 bbilerp1 = btop + ((bbot-btop) >> 1);
				
				r1 = AGIDL_GetR(clr1s,fmt);
			    g1 = AGIDL_GetG(clr1s,fmt);
				b1 = AGIDL_GetB(clr1s,fmt);
				
				r2 = AGIDL_GetR(clr2s,fmt);
				g2 = AGIDL_GetG(clr2s,fmt);
				b2 = AGIDL_GetB(clr2s,fmt);
				
				r3 = AGIDL_GetR(clr3s,fmt);
				g3 = AGIDL_GetG(clr3s,fmt);
				b3 = AGIDL_GetB(clr3s,fmt);
				
				r4 = AGIDL_GetR(clr4s,fmt);
				g4 = AGIDL_GetG(clr4s,fmt);
				b4 = AGIDL_GetB(clr4s,fmt);
				
				rtop = r1 + ((r2-r1) >> 1);
				gtop = g1 + ((g2-g1) >> 1);
				btop = b1 + ((b2-b1) >> 1);
				
				rbot = r3 + ((r4-r3) >> 1);
				gbot = g3 + ((g4-g3) >> 1);
				bbot = b3 + ((b4-b3) >> 1);
				
				u8 rbilerp2 = rtop + ((rbot-rtop) >> 1);
				u8 gbilerp2 = gtop + ((gbot-gtop) >> 1);
				u8 bbilerp2 = btop + ((bbot-btop) >> 1);
				
				u8 rfinal = rbilerp1 + ((rbilerp2-rbilerp1) >> 1);
				u8 gfinal = gbilerp1 + ((gbilerp2-gbilerp1) >> 1);
				u8 bfinal = bbilerp1 + ((bbilerp2-bbilerp1) >> 1);
				
				AGIDL_SetClr16(clrs,AGIDL_RGB16(rfinal,gfinal,bfinal,fmt),x,y,width,height);
			}
		}
		
		free(clrscale);
	}
}