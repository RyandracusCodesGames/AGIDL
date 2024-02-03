CC = gcc
INCS = -I"$(CURDIR)/include"
CFLAGS = -Wall -O2 $(INCS)
LDFLAGS =
OBJFILES = agidl_math_utils.o agidl_cc_manager.o agidl_cc_converter.o agidl_cc_mixer.o agidl_img_types.o agidl_imgp_grayscale.o agidl_imgp_rotate.o agidl_imgp_scale.o agidl_imgp_filter.o agidl_imgp_lightmap.o agidl_imgp_mirror.o agidl_imgp_blend.o agidl_imgp_wrap.o agidl_imgp_font.o agidl_imgp_mipmap.o agidl_imgp_halftone.o agidl_imgp_impl.o agidl_img_bmp.o agidl_img_tga.o agidl_img_tim.o agidl_img_pcx.o agidl_img_quake.o agidl_img_pvr.o agidl_img_gxt.o agidl_img_bti.o agidl_img_converter.o agidl_img_search.o agidl_img_compression.o agidl_img_error.o agidl_file_utils.o agidl_gd_display.o
OBJS = src/agidl_math_utils.o src/agidl_cc_manager.o src/agidl_cc_converter.o src/agidl_cc_mixer.o src/agidl_img_types.o src/agidl_imgp_grayscale.o src/agidl_imgp_rotate.o src/agidl_imgp_scale.o src/agidl_imgp_filter.o src/agidl_imgp_lightmap.o src/agidl_imgp_mirror.o src/agidl_imgp_blend.o src/agidl_imgp_wrap.o src/agidl_imgp_font.o src/agidl_imgp_mipmap.o src/agidl_imgp_halftone.o src/agidl_imgp_impl.o src/agidl_img_bmp.o src/agidl_img_tga.o src/agidl_img_tim.o src/agidl_img_pcx.o src/agidl_img_quake.o src/agidl_img_pvr.o src/agidl_img_gxt.o src/agidl_img_bti.o src/agidl_img_converter.o src/agidl_img_search.o src/agidl_img_compression.o src/agidl_img_error.o src/agidl_file_utils.o src/agidl_gd_display.o
DEPS = include/agidl_types.h include/agidl_math_utils.h include/agidl_cc_types.h include/agidl_cc_manager.h include/agidl_cc_convert.h include/agidl_cc_mixer.h include/agidl_cc_core.h include/agidl_img_types.h include/agidl_imgp_grayscale.h include/agidl_imgp_rotate.h include/agidl_imgp_scale.h include/agidl_imgp_lightmap.h include/agidl_imgp_filter.h inclue/agidl_imgp_blend.h include/agidl_imgp_mirror.h include/agidl_imgp_wrap.h include/agidl_imgp_font.h include/agidl_imgp_mipmap.h include/agidl_imgp_halftone.h include/agidl_imgp_impl.h include/agidl_imgp_core.h include/agidl_img_bmp.h include/agidl_img_tga.h include/agidl_img_tim.h include/agidl_img_pcx.h include/agidl_img_quake.h include/agidl_img_pvr.h include/agidl_img_gxt.h include/agidl_img_bti.h include/agidl_img_converter.h include/agidl_img_search.h include/agidl_img_compression.h include/agidl_img_error.h include/agidl_file_utils.h include/agidl_gd_display.h include/agidl_img_core.h include/agidl.h
TARGET = main

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
	
clean:
	rm -f $(OBJSFILES) $(TARGET) *~
