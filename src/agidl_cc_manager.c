#include <stdio.h>
#include "agidl_cc_manager.h"
#include "agidl_math_utils.h"
#include "agidl_img_types.h"
#include "agidl_cc_converter.h"
/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_cc_manager.c
*   Date: 9/8/2023
*   Version: 0.1b
*   Updated: 12/21/2023
*   Author: Ryandracus Chapman
*
********************************************/

u8 AGIDL_GetR(COLOR clr, AGIDL_CLR_FMT fmt){
	switch(fmt){
		case AGIDL_RGB_888:{
			return ((clr & 0xff0000) >> 16);
		}break;
		case AGIDL_BGR_888:{
			return ((clr & 0xff));
		}break;
		case AGIDL_RGBA_8888:{
			return ((clr >> 24) & 0xff);
		}break;
		case AGIDL_ARGB_8888:{
			return ((clr >> 16) & 0xff);
		}break;
		case AGIDL_RGB_555:{
			return ((clr & 0x7C00) >> 10);
		}break;
		case AGIDL_BGR_555:{
			return ((clr & 0x001F));
		}break;
		case AGIDL_RGB_565:{
			return ((clr & 0xF800) >> 11);
		}break;
		case AGIDL_BGR_565:{
			return ((clr & 0x001F));
		}break;
		default: return 0; break;
	}
}

u8 AGIDL_GetG(COLOR clr, AGIDL_CLR_FMT fmt){
	switch(fmt){
		case AGIDL_RGB_888:{
			return ((clr & 0xff00) >> 8);
		}break;
		case AGIDL_BGR_888:{
			return ((clr & 0xff00) >> 8);
		}break;
		case AGIDL_RGBA_8888:{
			return ((clr & 0xff0000) >> 16);
		}break;
		case AGIDL_ARGB_8888:{
			return ((clr & 0xff) >> 8);
		}break;
		case AGIDL_RGB_555:{
			return ((clr & 0x3E0) >> 5);
		}break;
		case AGIDL_BGR_555:{
			return((clr & 0x3E0) >> 5);
		}break;
		case AGIDL_RGB_565:{
			return ((clr & 0x7E0) >> 5);
		}break;
		case AGIDL_BGR_565:{
			return((clr & 0x7E0) >> 5);
		}break;
		default: return 0; break;
	}
}

u8 AGIDL_GetB(COLOR clr, AGIDL_CLR_FMT fmt){
	switch(fmt){
		case AGIDL_RGB_888:{
			return ((clr & 0xff));
		}break;
		case AGIDL_BGR_888:{
			return ((clr & 0xff0000) >> 16);
		}break;
		case AGIDL_RGBA_8888:{
			return ((clr & 0xff00) >> 8);
		}break;
		case AGIDL_ARGB_8888:{
			return ((clr & 0xff));
		}break;
		case AGIDL_RGB_555:{
			return ((clr & 0x001F));
		}break;
		case AGIDL_BGR_555:{
			return ((clr & 0x7C00) >> 10);
		}break;
		case AGIDL_RGB_565:{
			return ((clr & 0x001F));
		}break;
		case AGIDL_BGR_565:{
			return ((clr & 0xF800) >> 11);
		}break;
		default: return 0; break;
	}
}

u8 AGIDL_GetA(COLOR clr, AGIDL_CLR_FMT fmt){
	if(fmt == AGIDL_RGBA_8888){
		return ((clr & 0xff));
	}
	else if(fmt == AGIDL_ARGB_8888){
		return ((clr >> 24) && 0xff);
	}
	else return 0;
}

COLOR AGIDL_SetR(COLOR clr, u8 newR, AGIDL_CLR_FMT fmt){
	switch(fmt){
		case AGIDL_RGB_888:{
			u8 r = newR;
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = AGIDL_GetB(clr,fmt);
			return AGIDL_RGB(r,g,b,fmt);
		}break;
		case AGIDL_BGR_888:{
			u8 r = newR;
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = AGIDL_GetB(clr,fmt);
			return AGIDL_RGB(r,g,b,fmt);
		}break;
		case AGIDL_RGBA_8888:{
			u8 r = newR;
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = AGIDL_GetB(clr,fmt);
			u8 a = AGIDL_GetA(clr,fmt);
			return AGIDL_RGBA(r,g,b,a,fmt);
		}break;
		case AGIDL_ARGB_8888:{
			u8 r = newR;
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = AGIDL_GetB(clr,fmt);
			u8 a = AGIDL_GetA(clr,fmt);
			return AGIDL_RGBA(r,g,b,a,fmt);
		}break;
		case AGIDL_RGB_555:{
			u8 r = AGIDL_Clamp(0,newR,31);
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = AGIDL_GetB(clr,fmt);
			return AGIDL_RGB(r,g,b,fmt);
		}break;
		case AGIDL_BGR_555:{
			u8 r = AGIDL_Clamp(0,newR,31);
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = AGIDL_GetB(clr,fmt);
			return AGIDL_RGB(r,g,b,fmt); 
		}break;
		case AGIDL_RGB_565:{
			u8 r = AGIDL_Clamp(0,newR,31);
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = AGIDL_GetB(clr,fmt);
			return AGIDL_RGB(r,g,b,fmt);
		}break;
		case AGIDL_BGR_565:{
			u8 r = AGIDL_Clamp(0,newR,31);
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = AGIDL_GetB(clr,fmt);
			return AGIDL_RGB(r,g,b,fmt);
		}break;
	}
	return 0;
}

COLOR AGIDL_SetG(COLOR clr, u8 newG, AGIDL_CLR_FMT fmt){
	switch(fmt){
		case AGIDL_RGB_888:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = newG;
			u8 b = AGIDL_GetB(clr,fmt);
			return AGIDL_RGB(r,g,b,fmt);
		}break;
		case AGIDL_BGR_888:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = newG;
			u8 b = AGIDL_GetB(clr,fmt);
			return AGIDL_RGB(r,g,b,fmt);
		}break;
		case AGIDL_RGBA_8888:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = newG;
			u8 b = AGIDL_GetB(clr,fmt);
			u8 a = AGIDL_GetA(clr,fmt);
			return AGIDL_RGBA(r,g,b,a,fmt);
		}break;
		case AGIDL_ARGB_8888:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = newG;
			u8 b = AGIDL_GetB(clr,fmt);
			u8 a = AGIDL_GetA(clr,fmt);
			return AGIDL_RGBA(r,g,b,a,fmt);
		}break;
		case AGIDL_RGB_555:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = AGIDL_Clamp(0,newG,31);
			u8 b = AGIDL_GetB(clr,fmt);
			return AGIDL_RGB(r,g,b,fmt);
		}break;
		case AGIDL_BGR_555:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = AGIDL_Clamp(0,newG,31);
			u8 b = AGIDL_GetB(clr,fmt);
			return AGIDL_RGB(r,g,b,fmt); 
		}break;
		case AGIDL_RGB_565:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = AGIDL_Clamp(0,newG,63);
			u8 b = AGIDL_GetB(clr,fmt);
			return AGIDL_RGB(r,g,b,fmt);
		}break;
		case AGIDL_BGR_565:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = AGIDL_Clamp(0,newG,63);
			u8 b = AGIDL_GetB(clr,fmt);
			return AGIDL_RGB(r,g,b,fmt); 
		}break;
	}
	return 0;
}

COLOR AGIDL_SetB(COLOR clr, u8 newB, AGIDL_CLR_FMT fmt){
	switch(fmt){
		case AGIDL_RGB_888:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = newB;
			return AGIDL_RGB(r,g,b,fmt);
		}break;
		case AGIDL_BGR_888:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = newB;
			return AGIDL_RGB(r,g,b,fmt);
		}break;
		case AGIDL_RGBA_8888:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = newB;
			u8 a = AGIDL_GetA(clr,fmt);
			return AGIDL_RGBA(r,g,b,a,fmt);
		}break;
		case AGIDL_ARGB_8888:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = newB;
			u8 a = AGIDL_GetA(clr,fmt);
			return AGIDL_RGBA(r,g,b,a,fmt);
		}break;
		case AGIDL_RGB_555:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = AGIDL_Clamp(0,newB,31);
			return AGIDL_RGB(r,g,b,fmt);
		}break;
		case AGIDL_BGR_555:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = AGIDL_Clamp(0,newB,31);
			return AGIDL_RGB(r,g,b,fmt); 
		}break;
		case AGIDL_RGB_565:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = AGIDL_Clamp(0,newB,31);
			return AGIDL_RGB(r,g,b,fmt); 
		}break;
		case AGIDL_BGR_565:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = AGIDL_Clamp(0,newB,31);
			return AGIDL_RGB(r,g,b,fmt); 
		}break;
	}
	return 0;
}

COLOR AGIDL_SetA(COLOR clr, u8 newA, AGIDL_CLR_FMT fmt){
	switch(fmt){
		case AGIDL_RGBA_8888:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = AGIDL_GetB(clr,fmt);
			return AGIDL_RGBA(r,g,b,newA,fmt); 
		}break;
		case AGIDL_ARGB_8888:{
			u8 r = AGIDL_GetR(clr,fmt);
			u8 g = AGIDL_GetG(clr,fmt);
			u8 b = AGIDL_GetB(clr,fmt);
			return AGIDL_RGBA(r,g,b,newA,fmt); 
		}break;
	}
	return 0;
}

COLOR AGIDL_RGB(u8 r, u8 g, u8 b, AGIDL_CLR_FMT fmt){
	switch(fmt){
		case AGIDL_RGB_888:{
			return r << 16 | g << 8 | b;
		}break;
		case AGIDL_BGR_888:{
			return b << 16 | g << 8 | r;
		}break;
		case AGIDL_RGB_555:{
			r = AGIDL_Clamp(0,r,31);
			g = AGIDL_Clamp(0,g,31);
			b = AGIDL_Clamp(0,b,31);
			return r << 10 | g << 5 | b;
		}break;
		case AGIDL_BGR_555:{
			r = AGIDL_Clamp(0,r,31);
			g = AGIDL_Clamp(0,g,31);
			b = AGIDL_Clamp(0,b,31);
			return b << 10 | g << 5 | r;
		}break;
		case AGIDL_RGB_565:{
			r = AGIDL_Clamp(0,r,31);
			g = AGIDL_Clamp(0,g,63);
			b = AGIDL_Clamp(0,b,31);
			return r << 11 | g << 5 | b;
		}break;
		case AGIDL_BGR_565:{
			r = AGIDL_Clamp(0,r,31);
			g = AGIDL_Clamp(0,g,63);
			b = AGIDL_Clamp(0,b,31);
			return b << 11 | g << 5 | r;
		}break;
		default: return 0; break;
	}
}

COLOR AGIDL_RGBA(u8 r, u8 g, u8 b, u8 a, AGIDL_CLR_FMT fmt){
	if(fmt == AGIDL_RGBA_8888){
		return r << 24 | g << 16 | b << 8 | a;
	}
	else return a << 24 | r << 16 | g << 8 | b;
}

COLOR16 AGIDL_RGB16(u8 r, u8 g, u8 b, AGIDL_CLR_FMT fmt){
	switch(fmt){
		case AGIDL_RGB_555:{
			r = AGIDL_Clamp(0,r,31);
			g = AGIDL_Clamp(0,g,31);
			b = AGIDL_Clamp(0,b,31);
			return r << 10 | g << 5 | b;
		}break;
		case AGIDL_BGR_555:{
			r = AGIDL_Clamp(0,r,31);
			g = AGIDL_Clamp(0,g,31);
			b = AGIDL_Clamp(0,b,31);
			return b << 10 | g << 5 | r;
		}break;
		case AGIDL_RGB_565:{
			r = AGIDL_Clamp(0,r,31);
			g = AGIDL_Clamp(0,g,63);
			b = AGIDL_Clamp(0,b,31);
			return r << 11 | g << 5 | b;
		}break;
		case AGIDL_BGR_565:{
			r = AGIDL_Clamp(0,r,31);
			g = AGIDL_Clamp(0,g,63);
			b = AGIDL_Clamp(0,b,31);
			return b << 11 | g << 5 | r;
		}break;
		default: return 0; break;
	}
}

COLOR AGIDL_Color3f(float r, float g, float b, AGIDL_CLR_FMT fmt){
	r = AGIDL_Clampf(0.0f,r,1.0f);
	g = AGIDL_Clampf(0.0f,g,1.0f);
	b = AGIDL_Clampf(0.0f,b,1.0f);
	
	if(AGIDL_GetBitCount(fmt) == 24){
		return AGIDL_RGB(r*255.0f,g*255.0f,b*255.0f,fmt);
	}
	else if(AGIDL_GetBitCount(fmt) == 32){
		return AGIDL_RGBA(r*255.0f,g*255.0f,b*255.0f,0xff,fmt);
	}
	else{
		if(fmt == AGIDL_RGB_565 || fmt == AGIDL_BGR_565){
			return AGIDL_RGB16(r*31.0f,g*63.0f,b*31.0f,fmt);
		}
		else{
			return AGIDL_RGB16(r*31.0f,g*31.0f,b*31.0f,fmt);
		}
	}
}

COLOR AGIDL_Color4f(float r, float g, float b, float a, AGIDL_CLR_FMT fmt){
	r = AGIDL_Clampf(0.0f,r,1.0f);
	g = AGIDL_Clampf(0.0f,g,1.0f);
	b = AGIDL_Clampf(0.0f,b,1.0f);
	
	if(AGIDL_GetBitCount(fmt) == 32){
		return AGIDL_RGBA(r*255.0f,g*255.0f,b*255.0f,a*255.0f,fmt);
	}
	else{
		return AGIDL_Color3f(r,g,b,fmt);
	}
}

COLOR AGIDL_GetColor(AGIDL_CLR clr, AGIDL_CLR_FMT fmt){
	switch(clr){
		case BLACK:{
			switch(fmt){
				case AGIDL_RGB_888:{
					return BLACK_RGB_888;
				}break;
				case AGIDL_BGR_888:{
					return BLACK_BGR_888;
				}break;
				case AGIDL_RGBA_8888:{
					return BLACK_RGBA_8888;
				}break;
				case AGIDL_ARGB_8888:{
					return BLACK_ARGB_8888;
				}break;
				case AGIDL_RGB_555:{
					return BLACK_RGB_555;
				}break;
				case AGIDL_BGR_555:{
					return BLACK_BGR_555;
				}break;
				case AGIDL_RGB_565:{
					return BLACK_RGB_565;
				}break;
				case AGIDL_BGR_565:{
					return BLACK_BGR_565;
				}break;
			}
		}break;
		case WHITE:{
			switch(fmt){
				case AGIDL_RGB_888:{
					return WHITE_RGB_888;
				}break;
				case AGIDL_BGR_888:{
					return WHITE_BGR_888;
				}break;
				case AGIDL_RGBA_8888:{
					return WHITE_RGBA_8888;
				}break;
				case AGIDL_ARGB_8888:{
					return WHITE_ARGB_8888;
				}break;
				case AGIDL_RGB_555:{
					return WHITE_RGB_555;
				}break;
				case AGIDL_BGR_555:{
					return WHITE_BGR_555;
				}break;
				case AGIDL_RGB_565:{
					return WHITE_RGB_565;
				}break;
				case AGIDL_BGR_565:{
					return WHITE_BGR_565;
				}break;
			}
		}break;
		case GRAY:{
			switch(fmt){
				case AGIDL_RGB_888:{
					return GRAY_RGB_888;
				}break;
				case AGIDL_BGR_888:{
					return GRAY_BGR_888;
				}break;
				case AGIDL_RGBA_8888:{
					return GRAY_RGBA_8888;
				}break;
				case AGIDL_ARGB_8888:{
					return GRAY_ARGB_8888;
				}break;
				case AGIDL_RGB_555:{
					return GRAY_RGB_555;
				}break;
				case AGIDL_BGR_555:{
					return GRAY_BGR_555;
				}break;
				case AGIDL_RGB_565:{
					return GRAY_RGB_565;
				}break;
				case AGIDL_BGR_565:{
					return GRAY_BGR_565;
				}break;
			}
		}break;
		case RED:{
			switch(fmt){
				case AGIDL_RGB_888:{
					return RED_RGB_888;
				}break;
				case AGIDL_BGR_888:{
					return RED_BGR_888;
				}break;
				case AGIDL_RGBA_8888:{
					return RED_RGBA_8888;
				}break;
				case AGIDL_ARGB_8888:{
					return RED_ARGB_8888;
				}break;
				case AGIDL_RGB_555:{
					return RED_RGB_555;
				}break;
				case AGIDL_BGR_555:{
					return RED_BGR_555;
				}break;
				case AGIDL_RGB_565:{
					return RED_RGB_565;
				}break;
				case AGIDL_BGR_565:{
					return RED_BGR_565;
				}break;
			}
		}break;
		case GREEN:{
			switch(fmt){
				case AGIDL_RGB_888:{
					return GREEN_RGB_888;
				}break;
				case AGIDL_BGR_888:{
					return GREEN_BGR_888;
				}break;
				case AGIDL_RGBA_8888:{
					return GREEN_RGBA_8888;
				}break;
				case AGIDL_ARGB_8888:{
					return GREEN_ARGB_8888;
				}break;
				case AGIDL_RGB_555:{
					return GREEN_RGB_555;
				}break;
				case AGIDL_BGR_555:{
					return GREEN_BGR_555;
				}break;
				case AGIDL_RGB_565:{
					return GREEN_RGB_565;
				}break;
				case AGIDL_BGR_565:{
					return GREEN_BGR_565;
				}break;
			}
		}break;
		case BLUE:{
			switch(fmt){
				case AGIDL_RGB_888:{
					return BLUE_RGB_888;
				}break;
				case AGIDL_BGR_888:{
					return BLUE_BGR_888;
				}break;
				case AGIDL_RGBA_8888:{
					return BLUE_RGBA_8888;
				}break;
				case AGIDL_ARGB_8888:{
					return BLUE_ARGB_8888;
				}break;
				case AGIDL_RGB_555:{
					return BLUE_RGB_555;
				}break;
				case AGIDL_BGR_555:{
					return BLUE_BGR_555;
				}break;
				case AGIDL_RGB_565:{
					return BLUE_RGB_565;
				}break;
				case AGIDL_BGR_565:{
					return BLUE_BGR_565;
				}break;
			}
		}break;
		case YELLOW:{
			switch(fmt){
				case AGIDL_RGB_888:{
					return YELLOW_RGB_888;
				}break;
				case AGIDL_BGR_888:{
					return YELLOW_BGR_888;
				}break;
				case AGIDL_RGBA_8888:{
					return YELLOW_RGBA_8888;
				}break;
				case AGIDL_ARGB_8888:{
					return YELLOW_ARGB_8888;
				}break;
				case AGIDL_RGB_555:{
					return YELLOW_RGB_555;
				}break;
				case AGIDL_BGR_555:{
					return YELLOW_BGR_555;
				}break;
				case AGIDL_RGB_565:{
					return YELLOW_RGB_565;
				}break;
				case AGIDL_BGR_565:{
					return YELLOW_BGR_565;
				}break;
			}
		}break;
		case ORANGE:{
			switch(fmt){
				case AGIDL_RGB_888:{
					return ORANGE_RGB_888;
				}break;
				case AGIDL_BGR_888:{
					return ORANGE_BGR_888;
				}break;
				case AGIDL_RGBA_8888:{
					return ORANGE_RGBA_8888;
				}break;
				case AGIDL_ARGB_8888:{
					return ORANGE_ARGB_8888;
				}break;
				case AGIDL_RGB_555:{
					return ORANGE_RGB_555;
				}break;
				case AGIDL_BGR_555:{
					return ORANGE_BGR_555;
				}break;
				case AGIDL_RGB_565:{
					return ORANGE_RGB_565;
				}break;
				case AGIDL_BGR_565:{
					return ORANGE_BGR_565;
				}break;
			}
		}break;
		case PURPLE:{
			switch(fmt){
				case AGIDL_RGB_888:{
					return PURPLE_RGB_888;
				}break;
				case AGIDL_BGR_888:{
					return PURPLE_BGR_888;
				}break;
				case AGIDL_RGBA_8888:{
					return PURPLE_RGBA_8888;
				}break;
				case AGIDL_ARGB_8888:{
					return PURPLE_ARGB_8888;
				}break;
				case AGIDL_RGB_555:{
					return PURPLE_RGB_555;
				}break;
				case AGIDL_BGR_555:{
					return PURPLE_BGR_555;
				}break;
				case AGIDL_RGB_565:{
					return ORANGE_RGB_565;
				}break;
				case AGIDL_BGR_565:{
					return ORANGE_BGR_565;
				}break;
			}
		}break;
		case BROWN:{
			switch(fmt){
				case AGIDL_RGB_888:{
					return BROWN_RGB_888;
				}break;
				case AGIDL_BGR_888:{
					return BROWN_BGR_888;
				}break;
				case AGIDL_RGBA_8888:{
					return BROWN_RGBA_8888;
				}break;
				case AGIDL_ARGB_8888:{
					return BROWN_ARGB_8888;
				}break;
				case AGIDL_RGB_555:{
					return BROWN_RGB_555;
				}break;
				case AGIDL_BGR_555:{
					return BROWN_BGR_555;
				}break;
				case AGIDL_RGB_565:{
					return BROWN_RGB_565;
				}break;
				case AGIDL_BGR_565:{
					return BROWN_BGR_565;
				}break;
			}
		}break;
		case PINK:{
			switch(fmt){
				case AGIDL_RGB_888:{
					return PINK_RGB_888;
				}break;
				case AGIDL_BGR_888:{
					return PINK_BGR_888;
				}break;
				case AGIDL_RGBA_8888:{
					return PINK_RGBA_8888;
				}break;
				case AGIDL_ARGB_8888:{
					return PINK_ARGB_8888;
				}break;
				case AGIDL_RGB_555:{
					return PINK_RGB_555;
				}break;
				case AGIDL_BGR_555:{
					return PINK_BGR_555;
				}break;
				case AGIDL_RGB_565:{
					return PINK_RGB_565;
				}break;
				case AGIDL_BGR_565:{
					return PINK_BGR_565;
				}break;
			}
		}break;
	}
	return 0;
}

int AGIDL_IsInThreshold(COLOR clr1, COLOR clr2, AGIDL_CLR_FMT fmt, AGIDL_CLR_FMT fmt2, u8 max_diff){
	if((AGIDL_GetBitCount(fmt) == 24 || AGIDL_GetBitCount(fmt) == 32) && (AGIDL_GetBitCount(fmt2) == 24 || AGIDL_GetBitCount(fmt2) == 32)){
		u8 r = AGIDL_GetR(clr1,fmt);
		u8 g = AGIDL_GetG(clr1,fmt);
		u8 b = AGIDL_GetB(clr1,fmt);
		
		u8 r2 = AGIDL_GetR(clr2,fmt2);
		u8 g2 = AGIDL_GetG(clr2,fmt2);
		u8 b2 = AGIDL_GetB(clr2,fmt2);
		
		if(AGIDL_Abs(r-r2) <= max_diff && AGIDL_Abs(g-g2) <= max_diff && AGIDL_Abs(b-b2) <= max_diff){
			return 0;
		}
		else return 1;
	}
	else if(AGIDL_GetBitCount(fmt) == 16 && (AGIDL_GetBitCount(fmt2) == 24 || AGIDL_GetBitCount(fmt2) == 32)){
		clr2 = AGIDL_CLR_TO_CLR16(clr2,fmt2,fmt); 
		
		u8 r = AGIDL_GetR(clr1,fmt);
		u8 g = AGIDL_GetG(clr1,fmt);
		u8 b = AGIDL_GetB(clr1,fmt);
		
		u8 r2 = AGIDL_GetR(clr2,fmt);
		u8 g2 = AGIDL_GetG(clr2,fmt);
		u8 b2 = AGIDL_GetB(clr2,fmt);
		
		if(AGIDL_Abs(r-r2) <= max_diff && AGIDL_Abs(g-g2) <= max_diff && AGIDL_Abs(b-b2) <= max_diff){
			return 0;
		}
		else return 1;
	}
	else{
		clr1 = AGIDL_CLR_TO_CLR16(clr1,fmt,fmt2); 
		
		u8 r = AGIDL_GetR(clr1,fmt2);
		u8 g = AGIDL_GetG(clr1,fmt2);
		u8 b = AGIDL_GetB(clr1,fmt2);
		
		u8 r2 = AGIDL_GetR(clr2,fmt2);
		u8 g2 = AGIDL_GetG(clr2,fmt2);
		u8 b2 = AGIDL_GetB(clr2,fmt2);
		
		if(AGIDL_Abs(r-r2) <= max_diff && AGIDL_Abs(g-g2) <= max_diff && AGIDL_Abs(b-b2) <= max_diff){
			return 0;
		}
		else return 1;
	}
}

void AGIDL_SetICPMode(AGIDL_ICP* palette, int mode, AGIDL_CLR_FMT fmt){
	palette->mode = mode;
	palette->fmt = fmt;
}

void AGIDL_ClearICP(AGIDL_ICP* palette, COLOR clr){
	switch(palette->mode){
		case AGIDL_ICP_256:{
			int i;
			for(i = 0; i < 256; i++){
				palette->icp.palette_256[i] = clr;
			}
		}break;
		case AGIDL_ICP_16:{
			int i;
			for(i = 0; i < 16; i++){
				palette->icp.palette_16[i] = clr;
			}
		}break;
		case AGIDL_ICP_16b_256:{
			int i;
			for(i = 0; i < 256; i++){
				palette->icp.palette_16b_256[i] = (COLOR16)clr;
			}
		}break;
		case AGIDL_ICP_16b_16:{
			int i;
			for(i = 0; i < 16; i++){
				palette->icp.palette_16b_16[i] = (COLOR16)clr;
			}
		}break;
	}
}

void AGIDL_ClearColorICP(AGIDL_ICP* palette, float r, float g, float b){
	switch(palette->mode){
		case AGIDL_ICP_256:{
			int i;
			for(i = 0; i < 256; i++){
				palette->icp.palette_256[i] = AGIDL_Color3f(r,g,b,palette->mode);
			}
		}break;
		case AGIDL_ICP_16:{
			int i;
			for(i = 0; i < 16; i++){
				palette->icp.palette_16[i] = AGIDL_Color3f(r,g,b,palette->mode);
			}
		}break;
		case AGIDL_ICP_16b_256:{
			int i;
			for(i = 0; i < 256; i++){
				palette->icp.palette_16b_256[i] = (COLOR16)AGIDL_Color3f(r,g,b,palette->mode);
			}
		}break;
		case AGIDL_ICP_16b_16:{
			int i;
			for(i = 0; i < 16; i++){
				palette->icp.palette_16b_16[i] = (COLOR16)AGIDL_Color3f(r,g,b,palette->mode);
			}
		}break;
	}
}

void AGIDL_ClearRGBICP(AGIDL_ICP* palette, u8 r, u8 g, u8 b){
	switch(palette->mode){
		case AGIDL_ICP_256:{
			int i;
			for(i = 0; i < 256; i++){
				palette->icp.palette_256[i] = AGIDL_RGB(r,g,b,palette->mode);
			}
		}break;
		case AGIDL_ICP_16:{
			int i;
			for(i = 0; i < 16; i++){
				palette->icp.palette_16[i] = AGIDL_RGB(r,g,b,palette->mode);
			}
		}break;
		case AGIDL_ICP_16b_256:{
			int i;
			for(i = 0; i < 256; i++){
				palette->icp.palette_16b_256[i] = (COLOR16)AGIDL_RGB(r,g,b,palette->mode);
			}
		}break;
		case AGIDL_ICP_16b_16:{
			int i;
			for(i = 0; i < 16; i++){
				palette->icp.palette_16b_16[i] = (COLOR16)AGIDL_RGB(r,g,b,palette->mode);
			}
		}break;
	}
}

AGIDL_CLR_MDL AGIDL_GetClrMDL(AGIDL_CLR_FMT fmt){
	if(fmt == AGIDL_RGB_888 || fmt == AGIDL_RGB_555 || fmt == AGIDL_RGB_565){
		return AGIDL_CLR_RGB;
	}
	else if(fmt == AGIDL_BGR_888 || fmt == AGIDL_BGR_555 || fmt == AGIDL_BGR_565){
		return AGIDL_CLR_BGR;
	}
	else if(fmt == AGIDL_RGBA_8888){
		return AGIDL_CLR_RGBA;
	}
	else{
		return AGIDL_CLR_ARGB;
	}
}

AGIDL_CLR_FMT AGIDL_GetClrFmt(AGIDL_CLR_MDL mdl, AGIDL_BITS bits){
	if(mdl == AGIDL_CLR_RGB && bits == 16){
		return AGIDL_RGB_565;	
	}
	else if(mdl == AGIDL_CLR_RGB && bits == 15){
		return AGIDL_RGB_555;	
	}
	else if(mdl == AGIDL_CLR_BGR && bits == 16){
		return AGIDL_BGR_565;	
	}
	else if(mdl == AGIDL_CLR_RGB && bits == 15){
		return AGIDL_BGR_555;	
	}
	else if(mdl == AGIDL_CLR_RGB && bits == 24){
		return AGIDL_RGB_888;
	}
	else if(mdl == AGIDL_CLR_BGR && bits == 24){
		return AGIDL_BGR_888;
	}
	else if(mdl == AGIDL_CLR_RGBA && bits == 32){
		return AGIDL_RGBA_8888;
	}
	else{
		return AGIDL_ARGB_8888;
	}
}

void AGIDL_ExportICP(const char* name, AGIDL_ICP icp){
	char* filename = AGIDL_StrCpy(name,".icp");
	FILE* file = fopen(filename,"wb");
	
	u8 clrmdl = AGIDL_GetClrMDL(icp.fmt);
	u8 bits = AGIDL_GetBitCount(icp.fmt);
	
	fwrite(&clrmdl,1,1,file);
	fwrite(&bits,1,1,file);
	
	u16 num_of_clrs = 0;
		
	if(icp.mode == AGIDL_ICP_256 || icp.mode == AGIDL_ICP_16b_256){
		num_of_clrs = 256;
	}
	else{
		num_of_clrs = 16;
	}
	
	fwrite(&num_of_clrs,2,1,file);
	
	switch(icp.mode){
		case AGIDL_ICP_256:{
			int i;
			for(i = 0; i < 256; i++){
				COLOR clr = icp.icp.palette_256[i];
				u8 r = AGIDL_GetR(clr,icp.fmt);
				u8 g = AGIDL_GetR(clr,icp.fmt);
				u8 b = AGIDL_GetR(clr,icp.fmt);
				fwrite(&r,1,1,file);
				fwrite(&g,1,1,file);
				fwrite(&b,1,1,file);
			}
		}break;
		case AGIDL_ICP_16:{
			int i;
			for(i = 0; i < 16; i++){
				COLOR clr = icp.icp.palette_256[i];
				u8 r = AGIDL_GetR(clr,icp.fmt);
				u8 g = AGIDL_GetR(clr,icp.fmt);
				u8 b = AGIDL_GetR(clr,icp.fmt);
				fwrite(&r,1,1,file);
				fwrite(&g,1,1,file);
				fwrite(&b,1,1,file);
			}
		}break;
		case AGIDL_ICP_16b_256:{
			int i;
			for(i = 0; i < 256; i++){
				COLOR16 clr = icp.icp.palette_16b_256[i];
				u8 r = AGIDL_GetR(clr,icp.fmt);
				u8 g = AGIDL_GetR(clr,icp.fmt);
				u8 b = AGIDL_GetR(clr,icp.fmt);
				fwrite(&r,1,1,file);
				fwrite(&g,1,1,file);
				fwrite(&b,1,1,file);
			}
		}break;
		case AGIDL_ICP_16b_16:{
			int i;
			for(i = 0; i < 16; i++){
				COLOR16 clr = icp.icp.palette_16b_256[i];
				u8 r = AGIDL_GetR(clr,icp.fmt);
				u8 g = AGIDL_GetR(clr,icp.fmt);
				u8 b = AGIDL_GetR(clr,icp.fmt);
				fwrite(&r,1,1,file);
				fwrite(&g,1,1,file);
				fwrite(&b,1,1,file);
			}
		}break;
	}
	fclose(file);
}

AGIDL_ICP AGIDL_LoadICP(const char* filename){
	FILE* file = fopen(filename,"rb");
	
	if(file == NULL){
		printf("Cannot find/located AGIDL Indexed Color Palette(ICP) - %s!\n",filename);
	}
	
	AGIDL_ICP icp;
	
	u8 clrmdl = 0, bits = 0;
	u16 num_of_colors = 0;
	
	fread(&clrmdl,1,1,file);
	fread(&bits,1,1,file);
	fread(&num_of_colors,2,1,file);
	
	icp.fmt = AGIDL_GetClrFmt(clrmdl,bits);
	
	if(num_of_colors == 256 && bits != 16){
		icp.mode = AGIDL_ICP_256;
		
		int i;
		for(i = 0; i < num_of_colors; i++){
			u8 r = 0, g = 0, b = 0;
			fread(&r,1,1,file);
			fread(&g,1,1,file);
			fread(&b,1,1,file);
			icp.icp.palette_256[i] = AGIDL_RGB(r,g,b,icp.fmt);
		}
	}
	else if(num_of_colors == 16 && bits != 16){
		icp.mode = AGIDL_ICP_16;
		
		int i;
		for(i = 0; i < num_of_colors; i++){
			u8 r = 0, g = 0, b = 0;
			fread(&r,1,1,file);
			fread(&g,1,1,file);
			fread(&b,1,1,file);
			icp.icp.palette_16[i] = AGIDL_RGB(r,g,b,icp.fmt);
		}
	}
	else if(num_of_colors == 16 && bits != 256){
		icp.mode = AGIDL_ICP_16b_256;
		
		int i;
		for(i = 0; i < num_of_colors; i++){
			u8 r = 0, g = 0, b = 0;
			fread(&r,1,1,file);
			fread(&g,1,1,file);
			fread(&b,1,1,file);
			icp.icp.palette_16b_256[i] = AGIDL_RGB16(r,g,b,icp.fmt);
		}
	}
	else{
		icp.mode = AGIDL_ICP_16b_16;
		
		int i;
		for(i = 0; i < num_of_colors; i++){
			u8 r = 0, g = 0, b = 0;
			fread(&r,1,1,file);
			fread(&g,1,1,file);
			fread(&b,1,1,file);
			icp.icp.palette_16b_16[i] = AGIDL_RGB16(r,g,b,icp.fmt);
		}
	}
	
	fclose(file);
	
	return icp;
}

void AGIDL_InitICP(AGIDL_ICP *palette, int mode){
	palette->mode = mode;
	
	if(mode == AGIDL_ICP_16){
		int i;
		for(i = 0; i < 16; i++){
			palette->icp.palette_16[i] = 0;
		}
	}
	else if(mode == AGIDL_ICP_256){
		int i;
		for(i = 0; i < 256; i++){
			palette->icp.palette_256[i] = 0;
		}
	}
	else if(mode == AGIDL_ICP_16b_16){
		int i;
		for(i = 0; i < 16; i++){
			palette->icp.palette_16b_16[i] = 0;
		}
	}
	else{
		int i;
		for(i = 0; i < 256; i++){
			palette->icp.palette_16b_256[i] = 0;
		}
	}
}

void AGIDL_AddColorICP(AGIDL_ICP *palette, u8 index, COLOR clr, AGIDL_CLR_FMT fmt, int max_diff, int *pass){
	/*Extract Individual RGB components of clr*/
	u8 r = AGIDL_GetR(clr,fmt);
	u8 g = AGIDL_GetG(clr,fmt);
	u8 b = AGIDL_GetB(clr,fmt);
	
	switch(palette->mode){
		case AGIDL_ICP_16:{
			int i;
			for(i = 0; i < 16; i++){
				COLOR palclr = palette->icp.palette_16[i];
				u8 palr = AGIDL_GetR(palclr,fmt);
				u8 palg = AGIDL_GetG(palclr,fmt);
				u8 palb = AGIDL_GetB(palclr,fmt);
				if(AGIDL_Abs(r-palr) <= max_diff && AGIDL_Abs(g-palg) <= max_diff && AGIDL_Abs(b-palb) <= max_diff){
					*pass = 0;
					return;
				}
			}
			
			palette->icp.palette_16[index] = clr;
			
			*pass = 1;
		}break;
		case AGIDL_ICP_256:{
			int i;
			for(i = 0; i < 256; i++){
				COLOR palclr = palette->icp.palette_256[i];
				u8 palr = AGIDL_GetR(palclr,fmt);
				u8 palg = AGIDL_GetG(palclr,fmt);
				u8 palb = AGIDL_GetB(palclr,fmt);
				if(AGIDL_Abs(r-palr) <= max_diff && AGIDL_Abs(g-palg) <= max_diff && AGIDL_Abs(b-palb) <= max_diff){
					*pass = 0;
					return;
				}
			}
			
			palette->icp.palette_256[index] = clr;
			
			*pass = 1;
		}break;
		case AGIDL_ICP_16b_16:{
			int i;
			for(i = 0; i < 16; i++){
				COLOR16 palclr = palette->icp.palette_16b_16[i];
				u8 palr = AGIDL_GetR(palclr,fmt);
				u8 palg = AGIDL_GetG(palclr,fmt);
				u8 palb = AGIDL_GetB(palclr,fmt);
				if(AGIDL_Abs(r-palr) <= max_diff && AGIDL_Abs(g-palg) <= max_diff && AGIDL_Abs(b-palb) <= max_diff){
					*pass = 0;
					return;
				}
			}
			
			palette->icp.palette_16b_16[index] = (COLOR16)clr;
			
			*pass = 1;
		}break;
		case AGIDL_ICP_16b_256:{
			int i;
			for(i = 0; i < 256; i++){
				COLOR16 palclr = palette->icp.palette_16b_256[i];
				u8 palr = AGIDL_GetR(palclr,fmt);
				u8 palg = AGIDL_GetG(palclr,fmt);
				u8 palb = AGIDL_GetB(palclr,fmt);
				if(AGIDL_Abs(r-palr) <= max_diff && AGIDL_Abs(g-palg) <= max_diff && AGIDL_Abs(b-palb) <= max_diff){
					*pass = 0;
					return;
				}
			}
			
			palette->icp.palette_16b_256[index] = (COLOR16)clr;
			
			*pass = 1;
		}break;
	}
}

void AGIDL_AddColorICP16(AGIDL_ICP *palette, u8 index, COLOR16 clr, AGIDL_CLR_FMT fmt, int max_diff, int *pass){
	/*Extract Individual RGB components of clr*/
	u8 r = AGIDL_GetR(clr,fmt);
	u8 g = AGIDL_GetG(clr,fmt);
	u8 b = AGIDL_GetB(clr,fmt);
	switch(palette->mode){
		case AGIDL_ICP_16b_16:{
			int i;
			for(i = 0; i < 16; i++){
				COLOR16 palclr = palette->icp.palette_16b_16[i];
				u8 palr = AGIDL_GetR(palclr,fmt);
				u8 palg = AGIDL_GetG(palclr,fmt);
				u8 palb = AGIDL_GetB(palclr,fmt);
				if(AGIDL_Abs(r-palr) <= max_diff && AGIDL_Abs(g-palg) <= max_diff && AGIDL_Abs(b-palb) <= max_diff){
					*pass = 0;
					return;
				}
			}
			
			palette->icp.palette_16b_16[index] = clr;
			
			*pass = 1;
		}break;
		case AGIDL_ICP_16b_256:{
			int i;
			for(i = 0; i < 256; i++){
				COLOR palclr = palette->icp.palette_16b_256[i];
				u8 palr = AGIDL_GetR(palclr,fmt);
				u8 palg = AGIDL_GetG(palclr,fmt);
				u8 palb = AGIDL_GetB(palclr,fmt);
				if(AGIDL_Abs(r-palr) <= max_diff && AGIDL_Abs(g-palg) <= max_diff && AGIDL_Abs(b-palb) <= max_diff){
					*pass = 0;
					return;
				}
			}
			
			palette->icp.palette_16b_256[index] = clr;
			
			*pass = 1;
		}break;
	}
}

void AGIDL_ForceAddColor(AGIDL_ICP* palette, COLOR clr, u8 index){
	if(palette->mode == AGIDL_ICP_16 || palette->mode == AGIDL_ICP_16b_16){
		index = AGIDL_Max(index,16);
		
		if(palette->mode == AGIDL_ICP_16){
			palette->icp.palette_16[index] = (COLOR16)clr;
		}
		else{
			palette->icp.palette_16b_16[index] = (COLOR16)clr;
		}
	}
	else{
		if(palette->mode == AGIDL_ICP_256){
			palette->icp.palette_256[index] = clr;
		}
		else{
			palette->icp.palette_16b_256[index] = clr;
		}
	}
}

u8 AGIDL_FindClosestColor(AGIDL_ICP palette, COLOR clr, AGIDL_CLR_FMT fmt, int max_difference){
	/*Extract Individual RGB Components of Color*/
	u8 r = AGIDL_GetR(clr,fmt);
	u8 g = AGIDL_GetG(clr,fmt);
	u8 b = AGIDL_GetB(clr,fmt);
	
	switch(palette.mode){
		case AGIDL_ICP_256:{
			int i;
			for(i = 0; i < 256; i++){
				COLOR palclr = palette.icp.palette_256[i];
			
				u8 palr = AGIDL_GetR(palclr,fmt);
				u8 palg = AGIDL_GetG(palclr,fmt);
				u8 palb = AGIDL_GetB(palclr,fmt);
				
				if(AGIDL_Abs(r-palr) <= max_difference && AGIDL_Abs(g-palg) <= max_difference && AGIDL_Abs(b-palb) <= max_difference){
					return i;
				}
				
				if(i == 255){
					return i;
				}
			}
		}break;
		case AGIDL_ICP_16:{
			int i;
			for(i = 0; i < 16; i++){
				COLOR palclr = palette.icp.palette_16[i];
			
				u8 palr = AGIDL_GetR(palclr,fmt);
				u8 palg = AGIDL_GetG(palclr,fmt);
				u8 palb = AGIDL_GetB(palclr,fmt);
				
				if(AGIDL_Abs(r-palr) <= max_difference && AGIDL_Abs(g-palg) <= max_difference && AGIDL_Abs(b-palb) <= max_difference){
					return i;
				}
			}
		}break;
		case AGIDL_ICP_16b_256:{
			int i;
			for(i = 0; i < 256; i++){
				COLOR16 palclr = palette.icp.palette_16b_256[i];
			
				u8 palr = AGIDL_GetR(palclr,fmt);
				u8 palg = AGIDL_GetG(palclr,fmt);
				u8 palb = AGIDL_GetB(palclr,fmt);
				
				if(AGIDL_Abs(r-palr) <= max_difference && AGIDL_Abs(g-palg) <= max_difference && AGIDL_Abs(b-palb) <= max_difference){
					return i;
				}
			}
		}break;
		case AGIDL_ICP_16b_16:{
			int i;
			for(i = 0; i < 16; i++){
				COLOR16 palclr = palette.icp.palette_16b_16[i];
			
				u8 palr = AGIDL_GetR(palclr,fmt);
				u8 palg = AGIDL_GetG(palclr,fmt);
				u8 palb = AGIDL_GetB(palclr,fmt);
				
				if(AGIDL_Abs(r-palr) <= max_difference && AGIDL_Abs(g-palg) <= max_difference && AGIDL_Abs(b-palb) <= max_difference){
					return i;
				}
			}
		}break;
		default: return 0; break;
	}
}

void AGIDL_SetY(AGIDL_YCbCr *ycbcr, u8 y){
	ycbcr->y = y;
}

void AGIDL_SetCb(AGIDL_YCbCr *ycbcr, u8 cb){
	ycbcr->cb = cb;
}

void AGIDL_SetCr(AGIDL_YCbCr *ycbcr, u8 cr){
	ycbcr->cr = cr;
}

void AGIDL_SetYCbCr(AGIDL_YCbCr *ycbcr, u8 y, u8 cb, u8 cr){
	AGIDL_SetY(ycbcr,y);
	AGIDL_SetCb(ycbcr,cb);
	AGIDL_SetCr(ycbcr,cr);
}