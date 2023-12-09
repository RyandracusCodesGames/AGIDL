#include "agidl_cc_manager.h"
#include "agidl_math_utils.h"

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_cc_manager.c
*   Date: 9/8/2023
*   Version: 0.1b
*   Updated: 11/22/2023
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