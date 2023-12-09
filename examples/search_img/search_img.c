/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: search_img.c
*   Date: 12/8/2023
*   Version: 0.1b
*   Updated: 12/8/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h>

int main(){
	
	AGIDL_TIMSearchFileOnDisk("GAME.RSC",AGIDL_IMG_BMP);
	
	return 0;
}