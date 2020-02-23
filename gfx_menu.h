#ifndef GFX_MENU_H
#define GFX_MENU_H

typedef struct gfx_widget_t;
typedef struct gfx_layout_t;

#include "stdint.h"

#ifdef __cplusplus
 extern "C" {
#endif


void gfx_menu_push(struct gfx_layout_t *layout);
void gfx_menu_pop(void);

struct gfx_layout_t *gfx_menu_layout(void);

void gfx_menu_key(uint32_t key);
void gfx_menu_reset(void);


#ifdef __cplusplus
 }
#endif


#endif
