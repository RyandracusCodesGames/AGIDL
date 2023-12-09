#include <stdio.h>
#include <stdlib.h>
#include "agidl_img_search.h"

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_img_search.c
*   Date: 11/11/2023
*   Version: 0.1b
*   Updated: 11/25/2023
*   Author: Ryandracus Chapman
*
********************************************/

void AGIDL_TIMSearchFileOnDisk(const char* filename, AGIDL_IMG_TYPE type){
	FILE* file = fopen(filename,"rb");
	
	if(file == NULL){
		printf("Could not locate/open file - %s!\n");
		return;
	}
	
	u32 img_count = 0;
	
	while(!feof(file)){
	
		AGIDL_TIM *tim = (AGIDL_TIM*)malloc(sizeof(AGIDL_TIM));
		
		AGIDL_TIMDecodeHeader(tim,file);
		
		while(!feof(file) && (tim->header.magic != 0x10 || !AGIDL_IsTIM(tim->header.version))){
			u32 curr_coord = ftell(file);
			fseek(file,curr_coord-7,SEEK_SET);
			AGIDL_TIMDecodeHeader(tim,file);
		}
		
		AGIDL_TIMDecodeIMG(tim,file); img_count++;
		
		if(AGIDL_TIMGetWidth(tim) > 0 && AGIDL_TIMGetHeight(tim) > 0 && AGIDL_TIMGetWidth(tim) < 2024 && AGIDL_TIMGetHeight(tim) < 2024){
			switch(type){
				case AGIDL_IMG_TIM:{
					char file_name[25];
					sprintf(file_name,"tim_%d.tim",img_count);
					tim->filename = file_name;
					AGIDL_ExportTIM(tim);
				}break;
				case AGIDL_IMG_BMP:{
					char file_name[25];
					sprintf(file_name,"tim_%d.tim",img_count);
					tim->filename = file_name;
					AGIDL_BMP* bmp = AGIDL_ConvertTIM2BMP(tim);
					AGIDL_ExportBMP(bmp);
					AGIDL_FreeBMP(bmp);
				}break;
				case AGIDL_IMG_TGA:{
					char file_name[25];
					sprintf(file_name,"tim_%d.tim",img_count);
					tim->filename = file_name;
					AGIDL_TGA* tga = AGIDL_ConvertTIM2TGA(tim);
					AGIDL_ExportTGA(tga);
					AGIDL_FreeTGA(tga);
				}break;
				case AGIDL_IMG_PCX:{
					char file_name[25];
					sprintf(file_name,"tim_%d.tim",img_count);
					tim->filename = file_name;
					AGIDL_PCX* pcx = AGIDL_ConvertTIM2PCX(tim);
					AGIDL_ExportPCX(pcx);
					AGIDL_FreePCX(pcx);
				}break;
				case AGIDL_IMG_LMP:{
					char file_name[25];
					sprintf(file_name,"tim_%d.tim",img_count);
					tim->filename = file_name;
					AGIDL_LMP* lmp = AGIDL_ConvertTIM2LMP(tim);
					AGIDL_LMPSetMaxDiff(lmp,32);
					AGIDL_ExportLMP(lmp);
					AGIDL_FreeLMP(lmp);
				}break;
				case AGIDL_IMG_PVR:{
					char file_name[25];
					sprintf(file_name,"tim_%d.tim",img_count);
					tim->filename = file_name;
					AGIDL_PVR* pvr = AGIDL_ConvertTIM2PVR(tim);
					AGIDL_ExportPVR(pvr);
					AGIDL_FreePVR(pvr);
				}break;
				case AGIDL_IMG_GXT:{
					char file_name[25];
					sprintf(file_name,"tim_%d.tim",img_count);
					tim->filename = file_name;
					AGIDL_GXT* gxt = AGIDL_ConvertTIM2GXT(tim);
					AGIDL_ExportGXT(gxt);
					AGIDL_FreeGXT(gxt);
				}break;
				
			}
		}
		
		AGIDL_FreeTIM(tim);
	}
	
	fclose(file);
}