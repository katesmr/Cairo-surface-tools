#include <cairo.h>
#include "../src/cairo_surface_tools.h"

int main(void) 
{ 
    cairo_surface_t *surface_dest; 
    cairo_surface_t *img; 
    cairo_t *cr_dest; 

    img = cairo_image_surface_create_from_png("cat.png"); 
    int width = cairo_image_surface_get_width(img); 
    int height = cairo_image_surface_get_height(img); 

    surface_dest = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height); /* create surface for result image */
    cr_dest = cairo_create(surface_dest); 

    filter_sepia(cr_dest, img);

    cairo_surface_write_to_png(surface_dest, "res.png"); /* save result */

    /* free memory */
    cairo_destroy(cr_dest); 
    cairo_surface_destroy(img); 
    cairo_surface_destroy(surface_dest); 

    return 0; 
}
