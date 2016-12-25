#include <cairo.h>
#include "../src/cairo_surface_tools.h"

int main(void) 
{ 
	cairo_surface_t *surface; 
	cairo_surface_t *img_background; 
	cairo_surface_t *img_foreground; 
	cairo_t *cr;  

	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 300, 300); /* create surface for result image */ 
	cr = cairo_create(surface); 

	img_background = cairo_image_surface_create_from_png("cat.png"); 
	img_foreground = cairo_image_surface_create_from_png("gr.png"); 

	merge(cr, img_background, img_foreground, CAIRO_OPERATOR_HSL_HUE);

	cairo_surface_write_to_png(surface, "res.png"); /* save result */

	/* free memory */
	cairo_destroy(cr); 
	cairo_surface_destroy(surface); 
	cairo_surface_destroy(img_background); 
	cairo_surface_destroy(img_foreground); 

	return 0; 
}
