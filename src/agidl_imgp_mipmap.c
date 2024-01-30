/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023-2024 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_imgp_mipmap.c
*   Date: 1/23/2024
*   Version: 0.2b
*   Updated: 1/29/2024
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdlib.h>
#include "agidl_imgp_mipmap.h"
#include "agidl_cc_manager.h"
#include "agidl_img_core.h"
#include "agidl_imgp_impl.h"

AGIDL_MIPMAP_NODE* AGIDL_CreateMipmapNode(void* img_data, u16 width, u16 height, AGIDL_CLR_FMT fmt, u8 mip_lvl){
	AGIDL_MIPMAP_NODE* node = (AGIDL_MIPMAP_NODE*)malloc(sizeof(AGIDL_MIPMAP_NODE));
	node->width = width;
	node->height = height;
	node->fmt = fmt;
	node->mip_lvl = mip_lvl;
	node->next = NULL;
	
	if(AGIDL_GetBitCount(fmt) == 16){
		COLOR16* clr_data = (COLOR16*)img_data;
		COLOR16* cpy = (COLOR16*)malloc(sizeof(COLOR16)*width*height);
		AGIDL_ClrMemcpy16(cpy,clr_data,width*height);
		
		node->img_data = cpy;
	}
	else{
		COLOR* clr_data = (COLOR*)img_data;
		COLOR* cpy = (COLOR*)malloc(sizeof(COLOR)*width*height);
		AGIDL_ClrMemcpy(cpy,clr_data,width*height);
		
		node->img_data = cpy;
	}
	
	return node;
}

AGIDL_MIPMAP_LINKED_LIST* AGIDL_CreateMipmapLinkedList(){
	AGIDL_MIPMAP_LINKED_LIST* list = (AGIDL_MIPMAP_LINKED_LIST*)malloc(sizeof(AGIDL_MIPMAP_LINKED_LIST));
	list->head = NULL;
	list->num_mips = 0;
	return list;
}

void AGIDL_AddMipmapNode(AGIDL_MIPMAP_LINKED_LIST* list, void* img_data, u16 width, u16 height, AGIDL_CLR_FMT fmt){
	AGIDL_MIPMAP_NODE* node = AGIDL_CreateMipmapNode(img_data,width,height,fmt,list->num_mips+1);
	
	if(list->head == NULL){
		list->head = node;
		list->num_mips++;
	}
	else{
		AGIDL_MIPMAP_NODE* current = list->head;
		
		while(current->next != NULL){
			current = current->next;
		}
		
		current->next = node;
		list->num_mips++;
	}
}


void AGIDL_RemoveMipampNode(AGIDL_MIPMAP_LINKED_LIST* list, u8 mip_lvl){
	if(list->head == NULL || list == NULL){
		return;
	}
	
	if(mip_lvl <= list->num_mips){
		AGIDL_MIPMAP_NODE* current = list->head;
		
		int i;
		for(i = 0; i < mip_lvl; i++){
			current = current->next;
		}
		
		free(current->next->img_data);
		free(current->next);
		current->next = NULL;
		list->num_mips--;
	}
}

AGIDL_MIPMAP_NODE* AGIDL_FindMipmapNode(AGIDL_MIPMAP_LINKED_LIST* list, u8 mip_lvl){
	if(list->head == NULL || list == NULL){
		return NULL;
	}
	
	if(mip_lvl <= list->num_mips){
		AGIDL_MIPMAP_NODE* current = list->head;
		
		int i;
		for(i = 0; i < mip_lvl; i++){
			current = current->next;
		}
	
		return current;
	}
	else return NULL;
}
void AGIDL_PopMipmapStart(AGIDL_MIPMAP_LINKED_LIST* list){
	AGIDL_MIPMAP_NODE* current = list->head;
	
	if(list->head == NULL){
		return;
	}
	
	list->head = list->head->next;
	list->num_mips--;
	free(current->img_data);
	free(current);
}

void AGIDL_PopMipmap(AGIDL_MIPMAP_LINKED_LIST* list){
	AGIDL_MIPMAP_NODE* current = list->head;
	
	if(list->head == NULL){
		return;
	}
	
	while(current->next->next != NULL){
		current = current->next;
	}
	
	free(current->next->img_data);
	free(current->next);
    current->next = NULL;
    list->num_mips--;
}

void AGIDL_DestroyMipmapList(AGIDL_MIPMAP_LINKED_LIST* list){
	if(list->head != NULL){
		int count = list->num_mips;
		int i;
		for(i = 0; i < count; i++){
			AGIDL_PopMipmapStart(list);
		}
		
		free(list);
		list->head = NULL;
	}
}

AGIDL_MIPMAP* AGIDL_CreateMipmap(void* img_data, u16 width, u16 height, AGIDL_CLR_FMT fmt, AGIDL_Bool IsLinear){
	AGIDL_MIPMAP* mipmap = (AGIDL_MIPMAP*)malloc(sizeof(AGIDL_MIPMAP));
	mipmap->width = width;
	mipmap->height = height;
	mipmap->fmt = fmt;
	mipmap->IsLinear = IsLinear;
	
	if(AGIDL_GetBitCount(fmt) == 16){
		COLOR16* clr_data = (COLOR16*)img_data;
		mipmap->img_data = (COLOR16*)malloc(sizeof(COLOR16)*width*height);
		AGIDL_ClrMemcpy16(mipmap->img_data,clr_data,width*height);
	}
	else{
		COLOR* clr_data = (COLOR*)img_data;
		mipmap->img_data = (COLOR*)malloc(sizeof(COLOR)*width*height);
		AGIDL_ClrMemcpy(mipmap->img_data,clr_data,width*height);
	}
	
	mipmap->list = AGIDL_CreateMipmapLinkedList();
	AGIDL_AddMipmapNode(mipmap->list,mipmap->img_data,mipmap->width,mipmap->height,mipmap->fmt);
	
	return mipmap;
}

void AGIDL_DestroyMipmap(AGIDL_MIPMAP* mipmap){
	AGIDL_DestroyMipmapList(mipmap->list);
	free(mipmap->img_data);
	free(mipmap);
	mipmap = NULL;
}

void AGIDL_LoadMipmapImgData(AGIDL_MIPMAP* mipmap, u8 mipmap_count, FILE* file){
	u16 width = mipmap->width;
	u16 height = mipmap->height;
	
	int i;
	for(i = 0; i < mipmap_count; i++){
		if(AGIDL_GetBitCount(mipmap->fmt) == 16){
			width >>= 1;
			height >>= 1;
			
			u16* data = (u16*)malloc(sizeof(u16)*width*height);
			
			fread(data,2,width*height,file);
			
			if(mipmap->IsLinear == TRUE){
				
				int x,y;
				for(y = 0; y < height; y++){
					for(x = 0; x < width; x++){
						u16 clr = AGIDL_GetClr16(data,x,y,width,height);
						clr = AGIDL_GammaCorrectColor(clr,2.2f,mipmap->fmt);
						AGIDL_SetClr16(data,clr,x,y,width,height);
					}
				}
			}
			
			AGIDL_AddMipmapNode(mipmap->list,data,width,height,mipmap->fmt);
			
			free(data);
		}
		else if(AGIDL_GetBitCount(mipmap->fmt) == 24){
			width >>= 1;
			height >>= 1;
			
			u32* data = (u32*)malloc(sizeof(u32)*width*height);
			
			int x,y;
			for(y = 0; y < height; y++){
				for(x = 0; x < width; x++){
					if(mipmap->fmt == AGIDL_RGB_888){
						u8 r = 0, g = 0, b = 0;
						fread(&r,1,1,file);
						fread(&g,1,1,file);
						fread(&b,1,1,file);
						
						COLOR clr = AGIDL_RGB(r,g,b,AGIDL_RGB_888);
						
						if(mipmap->IsLinear == TRUE){
							clr = AGIDL_GammaCorrectColor(AGIDL_RGB(r,g,b,mipmap->fmt),2.2f,mipmap->fmt);
						}
						
						AGIDL_SetClr(data,clr,x,y,width,height);
					}
					else{
						u8 r = 0, g = 0, b = 0;
						fread(&b,1,1,file);
						fread(&g,1,1,file);
						fread(&r,1,1,file);
						
						COLOR clr = AGIDL_RGB(r,g,b,AGIDL_BGR_888);
						
						if(mipmap->IsLinear == TRUE){
							clr = AGIDL_GammaCorrectColor(AGIDL_RGB(r,g,b,mipmap->fmt),2.2f,mipmap->fmt);
						}
						
						AGIDL_SetClr(data,clr,x,y,width,height);
					}
				}
			}
			
			AGIDL_AddMipmapNode(mipmap->list,data,width,height,mipmap->fmt);
			
			free(data);
		}
		else{
			width >>= 1;
			height >>= 1;
			
			u32* data = (u32*)malloc(sizeof(u32)*width*height);
			
			int x,y;
			for(y = 0; y < height; y++){
				for(x = 0; x < width; x++){
					if(mipmap->fmt == AGIDL_RGBA_8888){
						u8 r = 0, g = 0, b = 0, a = 0;
						fread(&r,1,1,file);
						fread(&g,1,1,file);
						fread(&b,1,1,file);
						fread(&a,1,1,file);
						
						COLOR clr = AGIDL_RGBA(r,g,b,a,AGIDL_RGBA_8888);
						
						if(mipmap->IsLinear == TRUE){
							clr = AGIDL_GammaCorrectColor(AGIDL_RGBA(r,g,b,a,mipmap->fmt),2.2f,mipmap->fmt);
						}
						
						AGIDL_SetClr(data,clr,x,y,width,height);
					}
					else{
						u8 r = 0, g = 0, b = 0, a = 0;
						fread(&a,1,1,file);
						fread(&r,1,1,file);
						fread(&g,1,1,file);
						fread(&b,1,1,file);
						
						COLOR clr = AGIDL_RGBA(r,g,b,a,AGIDL_RGBA_8888);
						
						if(mipmap->IsLinear == TRUE){
							clr = AGIDL_GammaCorrectColor(AGIDL_RGBA(r,g,b,a,mipmap->fmt),2.2f,mipmap->fmt);
						}

						AGIDL_SetClr(data,clr,x,y,width,height);
					}
				}
			}
			
			AGIDL_AddMipmapNode(mipmap->list,data,width,height,mipmap->fmt);
			
			free(data);
		}
	}
}

void AGIDL_ExportMipmapImgData(AGIDL_MIPMAP* mipmap, AGIDL_IMG_TYPE img, int flip){
	switch(img){
		case AGIDL_IMG_BMP:{
			AGIDL_BMP* bmp = AGIDL_CreateBMP("mip_1.bmp",mipmap->width,mipmap->height,mipmap->fmt);
				
			if(AGIDL_GetBitCount(mipmap->fmt) == 16){
				AGIDL_BMPSyncPix16(bmp,mipmap->img_data);
			}
			else{
				AGIDL_BMPSyncPix(bmp,mipmap->img_data);
			}
			
			if(flip){
				AGIDL_FlipHorzBMP(bmp);
			}
			
			AGIDL_ExportBMP(bmp);
			AGIDL_FreeBMP(bmp);
		}break;
		case AGIDL_IMG_TGA:{
			AGIDL_TGA* tga = AGIDL_CreateTGA("mip_1.tga",mipmap->width,mipmap->height,mipmap->fmt);
				
			if(AGIDL_GetBitCount(mipmap->fmt) == 16){
				AGIDL_TGASyncPix16(tga,mipmap->img_data);
			}
			else{
				AGIDL_TGASyncPix(tga,mipmap->img_data);
			}
			
			if(flip){
				AGIDL_FlipHorzTGA(tga);
			}
			
			AGIDL_ExportTGA(tga);
			AGIDL_FreeTGA(tga);
		}break;
		case AGIDL_IMG_TIM:{
			AGIDL_TIM* tim = AGIDL_CreateTIM("mip_1.tim",mipmap->width,mipmap->height,mipmap->fmt);
				
			if(AGIDL_GetBitCount(mipmap->fmt) == 16){
				AGIDL_TIMSyncPix16(tim,mipmap->img_data);
			}
			else{
				AGIDL_TIMSyncPix(tim,mipmap->img_data);
			}
			
			if(flip){
				AGIDL_FlipHorzTIM(tim);
			}
			
			AGIDL_ExportTIM(tim);
			AGIDL_FreeTIM(tim);
		}break;
		case AGIDL_IMG_PCX:{
			AGIDL_PCX* pcx = AGIDL_CreatePCX("mip_1.pcx",mipmap->width,mipmap->height,mipmap->fmt);
				
			if(AGIDL_GetBitCount(mipmap->fmt) == 16){
				AGIDL_PCXSyncPix16(pcx,mipmap->img_data);
			}
			else{
				AGIDL_PCXSyncPix(pcx,mipmap->img_data);
			}
			
			if(flip){
				AGIDL_FlipHorzPCX(pcx);
			}
			
			AGIDL_ExportPCX(pcx);
			AGIDL_FreePCX(pcx);
		}break;
		case AGIDL_IMG_LMP:{
			AGIDL_LMP* lmp = AGIDL_CreateLMP("mip_1.lmp",mipmap->width,mipmap->height,mipmap->fmt);
				
			if(AGIDL_GetBitCount(mipmap->fmt) == 16){
				AGIDL_LMPSyncPix16(lmp,mipmap->img_data);
			}
			else{
				AGIDL_LMPSyncPix(lmp,mipmap->img_data);
			}
			
			if(flip){
				AGIDL_FlipHorzLMP(lmp);
			}
			
			AGIDL_ExportLMP(lmp);
			AGIDL_FreeLMP(lmp);
		}break;
		case AGIDL_IMG_PVR:{
			AGIDL_PVR* pvr = AGIDL_CreatePVR("mip_1.pvr",mipmap->width,mipmap->height,mipmap->fmt);
				
			if(AGIDL_GetBitCount(mipmap->fmt) == 16){
				AGIDL_PVRSyncPix16(pvr,mipmap->img_data);
			}
			else{
				AGIDL_PVRSyncPix(pvr,mipmap->img_data);
			}
			
			if(flip){
				AGIDL_FlipHorzPVR(pvr);
			}
			
			AGIDL_ExportPVR(pvr);
			AGIDL_FreePVR(pvr);
		}break;
		case AGIDL_IMG_GXT:{
			AGIDL_GXT* gxt = AGIDL_CreateGXT("mip_1.gxt",mipmap->width,mipmap->height,mipmap->fmt);
				
			if(AGIDL_GetBitCount(mipmap->fmt) == 16){
				AGIDL_GXTSyncPix16(gxt,mipmap->img_data);
			}
			else{
				AGIDL_GXTSyncPix(gxt,mipmap->img_data);
			}
			
			if(flip){
				AGIDL_FlipHorzGXT(gxt);
			}
			
			AGIDL_ExportGXT(gxt);
			AGIDL_FreeGXT(gxt);
		}break;
		case AGIDL_IMG_BTI:{
			AGIDL_BTI* bti = AGIDL_CreateBTI("mip_1.bti",mipmap->width,mipmap->height,mipmap->fmt);
				
			if(AGIDL_GetBitCount(mipmap->fmt) == 16){
				AGIDL_BTISyncPix16(bti,mipmap->img_data);
			}
			else{
				AGIDL_BTISyncPix(bti,mipmap->img_data);
			}
			
			if(flip){
				AGIDL_FlipHorzBTI(bti);
			}
			
			AGIDL_ExportBTI(bti);
			AGIDL_FreeBTI(bti);
		}break;
	}
	
	int i;
	for(i = 1; i < mipmap->list->num_mips-1; i++){
		AGIDL_MIPMAP_NODE* node = AGIDL_FindMipmapNode(mipmap->list,i);
		
		if(node != NULL){
			switch(img){
				case AGIDL_IMG_BMP:{
					char filename[20];
					sprintf(filename,"mip_%d.bmp",i+1);
					
					AGIDL_BMP* bmp = AGIDL_CreateBMP(filename,node->width,node->height,node->fmt);
					
					if(AGIDL_GetBitCount(node->fmt) == 16){
						AGIDL_BMPSyncPix16(bmp,node->img_data);
					}
					else{
						AGIDL_BMPSyncPix(bmp,node->img_data);
					}
					
					if(flip){
						AGIDL_FlipHorzBMP(bmp);
					}
					
					AGIDL_ExportBMP(bmp);
					AGIDL_FreeBMP(bmp);
					
				}break;
				case AGIDL_IMG_TGA:{
					char filename[20];
					sprintf(filename,"mip_%d.tga",i+1);
					
					AGIDL_TGA* tga = AGIDL_CreateTGA(filename,node->width,node->height,node->fmt);
					
					if(AGIDL_GetBitCount(node->fmt) == 16){
						AGIDL_TGASyncPix16(tga,node->img_data);
					}
					else{
						AGIDL_TGASyncPix(tga,node->img_data);
					}
					
					if(flip){
						AGIDL_FlipHorzTGA(tga);
					}
					
					AGIDL_ExportTGA(tga);
					AGIDL_FreeTGA(tga);
					
				}break;
				case AGIDL_IMG_TIM:{
					char filename[20];
					sprintf(filename,"mip_%d.tim",i+1);
					
					AGIDL_TIM* tim = AGIDL_CreateTIM(filename,node->width,node->height,node->fmt);
					
					if(AGIDL_GetBitCount(node->fmt) == 16){
						AGIDL_TIMSyncPix16(tim,node->img_data);
					}
					else{
						AGIDL_TIMSyncPix(tim,node->img_data);
					}
					
					if(flip){
						AGIDL_FlipHorzTIM(tim);
					}
					
					AGIDL_ExportTIM(tim);
					AGIDL_FreeTIM(tim);
					
				}break;
				case AGIDL_IMG_PCX:{
					char filename[20];
					sprintf(filename,"mip_%d.pcx",i+1);
					
					AGIDL_PCX* pcx = AGIDL_CreatePCX(filename,node->width,node->height,node->fmt);
					
					if(AGIDL_GetBitCount(node->fmt) == 16){
						AGIDL_PCXSyncPix16(pcx,node->img_data);
					}
					else{
						AGIDL_PCXSyncPix(pcx,node->img_data);
					}
					
					if(flip){
						AGIDL_FlipHorzPCX(pcx);
					}
					
					AGIDL_ExportPCX(pcx);
					AGIDL_FreePCX(pcx);
					
				}break;
				case AGIDL_IMG_LMP:{
					char filename[20];
					sprintf(filename,"mip_%d.lmp",i+1);
					
					AGIDL_LMP* lmp = AGIDL_CreateLMP(filename,node->width,node->height,node->fmt);
					
					if(AGIDL_GetBitCount(node->fmt) == 16){
						AGIDL_LMPSyncPix16(lmp,node->img_data);
					}
					else{
						AGIDL_LMPSyncPix(lmp,node->img_data);
					}
					
					if(flip){
						AGIDL_FlipHorzLMP(lmp);
					}
					
					AGIDL_ExportLMP(lmp);
					AGIDL_FreeLMP(lmp);
					
				}break;
				case AGIDL_IMG_PVR:{
					char filename[20];
					sprintf(filename,"mip_%d.pvr",i+1);
					
					AGIDL_PVR* pvr = AGIDL_CreatePVR(filename,node->width,node->height,node->fmt);
					
					if(AGIDL_GetBitCount(node->fmt) == 16){
						AGIDL_PVRSyncPix16(pvr,node->img_data);
					}
					else{
						AGIDL_PVRSyncPix(pvr,node->img_data);
					}
					
					if(flip){
						AGIDL_FlipHorzPVR(pvr);
					}
					
					AGIDL_ExportPVR(pvr);
					AGIDL_FreePVR(pvr);
					
				}break;
				case AGIDL_IMG_GXT:{
					char filename[20];
					sprintf(filename,"mip_%d.gxt",i+1);
					
					AGIDL_GXT* gxt = AGIDL_CreateGXT(filename,node->width,node->height,node->fmt);
					
					if(AGIDL_GetBitCount(node->fmt) == 16){
						AGIDL_GXTSyncPix16(gxt,node->img_data);
					}
					else{
						AGIDL_GXTSyncPix(gxt,node->img_data);
					}
					
					if(flip){
						AGIDL_FlipHorzGXT(gxt);
					}
					
					AGIDL_ExportGXT(gxt);
					AGIDL_FreeGXT(gxt);
					
				}break;
				case AGIDL_IMG_BTI:{
					char filename[20];
					sprintf(filename,"mip_%d.bti",i+1);
					
					AGIDL_BTI* bti = AGIDL_CreateBTI(filename,node->width,node->height,node->fmt);
					
					if(AGIDL_GetBitCount(node->fmt) == 16){
						AGIDL_BTISyncPix16(bti,node->img_data);
					}
					else{
						AGIDL_BTISyncPix(bti,node->img_data);
					}
					
					if(flip){
						AGIDL_FlipHorzBTI(bti);
					}
					
					AGIDL_ExportBTI(bti);
					AGIDL_FreeBTI(bti);
					
				}break;
			}
		}
	}
}

void AGIDL_GenerateMipmapFromImgData(AGIDL_MIPMAP* mipmap, void* img_data, u16 width, u16 height, AGIDL_CLR_FMT fmt, u8 mip_lvl, AGIDL_SCALE scale){
	
	u16 w = width;
	u16 h = height;
	
	if(AGIDL_GetBitCount(fmt) == 16){
		COLOR16* cpy = (COLOR16*)malloc(sizeof(COLOR16)*w*h);
		COLOR16* clr_data = (COLOR16*)img_data;
		AGIDL_ClrMemcpy16(cpy,clr_data,w*h);
		
		int i;
		for(i = 0; i < mip_lvl; i++){
			if(scale == AGIDL_SCALE_NEAREST){
				cpy = (COLOR16*)AGIDL_HalfImgDataNearest(cpy,&w,&h,fmt);
			}
			else{
				cpy = (COLOR16*)AGIDL_HalfImgDataBilerp(cpy,&w,&h,fmt);
			}

			AGIDL_AddMipmapNode(mipmap->list,cpy,w,h,fmt);
		}
		
		free(cpy);
	}
	else{
		COLOR* cpy = (COLOR*)malloc(sizeof(COLOR)*w*h);
		COLOR* clr_data = (COLOR*)img_data;
		AGIDL_ClrMemcpy(cpy,clr_data,w*h);
		
		int i;
		for(i = 0; i < mip_lvl; i++){
			
			if(scale == AGIDL_SCALE_NEAREST){
				cpy = (COLOR*)AGIDL_HalfImgDataNearest(cpy,&w,&h,fmt);
			}
			else{
				cpy = (COLOR*)AGIDL_HalfImgDataBilerp(cpy,&w,&h,fmt);
			}

			AGIDL_AddMipmapNode(mipmap->list,cpy,w,h,fmt);
		}
		
		free(cpy);
	}
}

void AGIDL_FilterMipmapImgDataBilerp(AGIDL_MIPMAP* mipmap){
	AGIDL_FastFilterImgDataBilerp(mipmap->img_data,mipmap->width,mipmap->height,mipmap->fmt);
	
	int i;
	for(i = 1; i < mipmap->list->num_mips-1; i++){
		AGIDL_MIPMAP_NODE* node = AGIDL_FindMipmapNode(mipmap->list,i);
		
		AGIDL_FastFilterImgDataBilerp(node->img_data,node->width,node->height,node->fmt);
	}
}

void AGIDL_FilterMipmapImgDataTrilerp(AGIDL_MIPMAP* mipmap){
	AGIDL_FastFilterImgDataTrilerp(mipmap->img_data,mipmap->width,mipmap->height,mipmap->fmt);
	
	int i;
	for(i = 1; i < mipmap->list->num_mips-1; i++){
		AGIDL_MIPMAP_NODE* node = AGIDL_FindMipmapNode(mipmap->list,i);
		
		AGIDL_FastFilterImgDataTrilerp(node->img_data,node->width,node->height,node->fmt);
	}
}