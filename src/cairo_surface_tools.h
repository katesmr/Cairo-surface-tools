#ifndef CAIRO_SURFACE_TOOLS
#define CAIRO_SURFACE_TOOLS

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include <cairo.h>

#define CAIRO_SURFACE_TOOLS_IS_BIG_ENDIAN 1

#define CAIRO_SURFACE_TOOLS_TO_DEG(A) (A) * (M_PI / 180)

#define CAIRO_SURFACE_TOOLS_LOG(message) printf("Error: %s in line: %d, of function: %s", message, __LINE__, __func__)

#if CAIRO_SURFACE_TOOLS_IS_BIG_ENDIAN
	typedef enum 
	{
		RED_CHANNEL_OFFSET, 
		GREEN_CHANNEL_OFFSET, 
		BLUE_CHANNEL_OFFSET, 
		ALPHA_CHANNEL_OFFSET 
	} CHANNEL_OFFSET;
#else
	typedef enum 
	{
		ALPHA_CHANNEL_OFFSET, 
		BLUE_CHANNEL_OFFSET, 
		GREEN_CHANNEL_OFFSET, 
		RED_CHANNEL_OFFSET 
	} CHANNEL_OFFSET; 
#endif /* CAIRO_SURFACE_TOOLS_IS_BIG_ENDIAN */

void set_channel(cairo_t *cr, cairo_surface_t *source, CHANNEL_OFFSET dest_channel, unsigned char channel_value)
{
	assert(cr != NULL);
	assert(source != NULL);

	int i, j;

	int width = cairo_image_surface_get_width(source); 
	int height = cairo_image_surface_get_height(source); 

	unsigned char PIXEL_SIZE;
	unsigned char *data = cairo_image_surface_get_data(source); 
	if(NULL == data)
	{
		CAIRO_SURFACE_TOOLS_LOG("Can't get surface data");
		return;
	}
	int stride = cairo_image_surface_get_stride(source); 
	
	PIXEL_SIZE = stride / width;

	for(i = 0; i < height; i++) 
	{ 
		unsigned char *row = data + i * stride; /* current row of the image! */ 
		for(j = 0; j < width; j++) 
		{ 
			/* modify the destination channel by subtract from it some value: */ 
			*(row + (j * PIXEL_SIZE) + dest_channel) += channel_value; 
		} 
	}

	cairo_set_source_surface(cr, source, 0, 0); 
	cairo_paint(cr); 
}

void filter_grayscale(cairo_t *cr, cairo_surface_t *source)
{
	assert(cr != NULL);
	assert(source != NULL);

	int i, j; 
	unsigned char gray;
	unsigned char *pixel;
	unsigned char red_channel;
	unsigned char blue_channel;
	unsigned char green_channel;

	int width = cairo_image_surface_get_width(source); 
	int height = cairo_image_surface_get_height(source); 

	CHANNEL_OFFSET red = RED_CHANNEL_OFFSET;
	CHANNEL_OFFSET green = GREEN_CHANNEL_OFFSET;
	CHANNEL_OFFSET blue = BLUE_CHANNEL_OFFSET; /* channel you'd like to change */ /*0 or 1 or 2 or 3*/
	unsigned char PIXEL_SIZE;
	unsigned char *data = cairo_image_surface_get_data(source); 
	if(NULL == data)
	{
		CAIRO_SURFACE_TOOLS_LOG("Can't get surface data");
		return;
	}
	int stride = cairo_image_surface_get_stride(source); 
	
	PIXEL_SIZE = stride / width;

	for(i = 0; i < height; i++) 
	{ 
		unsigned char *row = data + i * stride; /* current row of the image! */ 
		for(j = 0; j < width; j++) 
		{ 
			/* modify the destination channel by subtract from it some value: */ 
			pixel = (row + (j * PIXEL_SIZE));

			red_channel = *(pixel + red);
			green_channel = *(pixel + green);
			blue_channel = *(pixel + blue);

			gray = (*(pixel + red) * 0.3 + *(pixel + green) * 0.59 + *(pixel + blue) * 0.11);

			*(pixel + red) = gray;
			*(pixel + green) = gray;
			*(pixel + blue) = gray;
		} 
	}

	cairo_set_source_surface(cr, source, 0, 0); 
	cairo_paint(cr); 
}

void filter_sepia(cairo_t *cr, cairo_surface_t *source)
{
	assert(cr != NULL);
	assert(source != NULL);

	int i, j; 
	unsigned char *pixel;
	unsigned char red_channel;
	unsigned char blue_channel;
	unsigned char green_channel;

	int width = cairo_image_surface_get_width(source); 
	int height = cairo_image_surface_get_height(source);

	CHANNEL_OFFSET red = RED_CHANNEL_OFFSET;
	CHANNEL_OFFSET green = GREEN_CHANNEL_OFFSET;
	CHANNEL_OFFSET blue = BLUE_CHANNEL_OFFSET; /* channel you'd like to change 0 or 1 or 2 or 3 */
	unsigned char PIXEL_SIZE;
	unsigned char *data = cairo_image_surface_get_data(source); 
	if(NULL == data)
	{
		CAIRO_SURFACE_TOOLS_LOG("Can't get surface data");
		return;
	}
	int stride = cairo_image_surface_get_stride(source); 
	
	PIXEL_SIZE = stride / width;

	for(i = 0; i < height; i++) 
	{ 
		unsigned char *row = data + i * stride; /* current row of the image! */ 
		for(j = 0; j < width; j++) 
		{ 
			/* modify the destination channel by subtract from it some value: */ 
			pixel = (row + (j * PIXEL_SIZE));

			red_channel = *(pixel + red);
			green_channel = *(pixel + green);
			blue_channel = *(pixel + blue);

			unsigned short red_tmp = (unsigned short)(red_channel * 0.393 + green_channel * 0.769 + blue_channel * 0.189);
			unsigned short green_tmp = (unsigned short)(red_channel * 0.349 + green_channel * 0.686 + blue_channel * 0.168);
			unsigned short blue_tmp = (unsigned short)(red_channel * 0.272 + green_channel * 0.534 + blue_channel * 0.131);

			if(255 < red_tmp)
			{
				red_tmp = 255;
			}
			if(255 < green_tmp)
			{
				green_tmp = 255;
			}
			if(255 < blue_tmp)
			{
				blue_tmp = 255;
			}

			*(pixel + red) = (unsigned char)red_tmp;
			*(pixel + green) = (unsigned char)green_tmp;
			*(pixel + blue) = (unsigned char)blue_tmp;
		} 
	}

	cairo_set_source_surface(cr, source, 0, 0); 
	cairo_paint(cr); 
}

void rescale_at(cairo_t *cr, cairo_surface_t *source, double delta_w, double delta_h, double x, double y)
{
	assert(cr != NULL);
	assert(source != NULL);

	cairo_scale(cr, delta_w, delta_h); 
	cairo_set_source_surface(cr, source, x, y); 
	cairo_paint(cr);
}

void rescale(cairo_t *cr, cairo_surface_t *source, double delta_w, double delta_h)
{
	rescale_at(cr, source, delta_w, delta_h, 0.0, 0.0);
}

void rotate_at(cairo_t *cr, cairo_surface_t *source, double degree, double x, double y)
{
	assert(cr != NULL);
	assert(source != NULL);

	int w;
	int h;
	double pos_x;
	double pos_y;

	w = cairo_image_surface_get_width(source);
	h = cairo_image_surface_get_height(source);

	pos_x = ((double) w) / 2.0;
	pos_y = ((double) h) / 2.0;

	cairo_translate(cr, pos_x, pos_y); /* move "imagepoint" to the center of the screen*/
	cairo_rotate(cr, CAIRO_SURFACE_TOOLS_TO_DEG(degree));
	cairo_translate(cr, -pos_x, -pos_y); /* move "imagepoint" to the center of the screen*/
	cairo_set_source_surface(cr, source, x, y);
	cairo_paint(cr);
}

void rotate(cairo_t *cr, cairo_surface_t *source, double degree)
{
	rotate_at(cr, source, degree, 0.0, 0.0);
}

void crop_at(cairo_t *cr, cairo_surface_t *source, double w, double h, double x, double y)
{
	assert(cr != NULL);
	assert(source != NULL);

	cairo_set_source_surface(cr, source, x, y);
	cairo_rectangle(cr, 0, 0, w, h);
    cairo_fill(cr);
	cairo_paint(cr);
}

void crop(cairo_t *cr, cairo_surface_t *source, double w, double h)
{
	crop_at(cr, source, w, h, 0.0, 0.0);
}

void merge_at(cairo_t *cr, cairo_surface_t *background, cairo_surface_t *foreground, cairo_operator_t op, double x, double y) 
{
	assert(cr != NULL);
	assert(background != NULL);
	assert(foreground != NULL);

	cairo_set_source_surface(cr, background, x, y);
	cairo_paint(cr);
	cairo_set_operator(cr, op);
	cairo_set_source_surface(cr, foreground, x, y);
	cairo_paint(cr);
}

void merge(cairo_t *cr, cairo_surface_t *background, cairo_surface_t *foreground, cairo_operator_t op)
{
	merge_at(cr, background, foreground, op, 0.0, 0.0);
}

void draw_gradient(cairo_t *cr, double alpha)
{
	assert(cr != NULL);

	cairo_pattern_t *pat = cairo_pattern_create_linear(0.0, 0.0,  350.0, 0.0);
	if(NULL == pat)
	{
		CAIRO_SURFACE_TOOLS_LOG("Can't get pattern for gradient");
		return;
	}

	cairo_surface_t *surface = cairo_get_target(cr);
	int width = cairo_image_surface_get_width(surface); 
	int height = cairo_image_surface_get_height(surface);

	double j;
	int count = 1;
	for(j = 0.0; j < 1; j += 0.1) 
	{
		count = (count + 1) & 1;
		cairo_pattern_add_color_stop_rgb(pat, j, count, 0, 0);
	}

	cairo_rectangle(cr, 0, 0, width, height);
	cairo_set_source(cr, pat);
	cairo_paint_with_alpha(cr, alpha);

	cairo_pattern_destroy(pat);
}

#endif /* CAIRO_SURFACE_TOOLS */
