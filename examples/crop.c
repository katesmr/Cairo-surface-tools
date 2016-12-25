#include <cairo.h>
#include "../src/cairo_surface_tools.h"

#define scale_delta 0.7

int main()
{
	cairo_surface_t *surface_dest; 
	cairo_surface_t *img; 
	cairo_t *cr_dest; 

	int w, h; 

	img = cairo_image_surface_create_from_png("cat.png"); 
	w = cairo_image_surface_get_width(img); 
	h = cairo_image_surface_get_height(img); 

	surface_dest = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w*scale_delta, h*scale_delta); /* create surface for result image */
	cr_dest = cairo_create(surface_dest); 

	crop(cr_dest, img, 100.0, 100.0);

	cairo_surface_write_to_png(surface_dest, "res.png"); /* save result */

	/* free memory */ 
	cairo_destroy(cr_dest); 
	cairo_surface_destroy(img); 
	cairo_surface_destroy(surface_dest); 

	return 0;
}
