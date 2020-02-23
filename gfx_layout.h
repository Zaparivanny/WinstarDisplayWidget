#ifndef GFX_LAYOUT_H
#define GFX_LAYOUT_H

#include "list.h"
#include "stdint.h"
#ifdef __cplusplus
 extern "C" {
#endif

typedef struct gfx_widget_t;
typedef struct gfx_layout_t;

//typedef void(*f_layout_key_t)(struct gfx_layout_t *widget, uint32_t key);

typedef struct gfx_layout_t
{
    struct list_head menu_stack;
    struct list_head widgets;
	uint8_t cursor_pos;
	uint8_t line_offset;
	uint8_t line_cnt;

}gfx_layout_t;

void gfx_layout_init(gfx_layout_t *layout);
void gfx_layout_add_widget(gfx_layout_t *layout, struct gfx_widget_t *widget);

#define GFX_LAYOUT_ADD_WIDGET(l, w) gfx_layout_add_widget(l, (gfx_widget_t *)w)

void gfx_layout_paint(gfx_layout_t *layout, char *buffer);

void gfx_layout_prev(gfx_layout_t *layout);
void gfx_layout_next(gfx_layout_t *layout);

void gfx_layout_key(gfx_layout_t *layout, uint32_t key);
void gfx_default_key(uint32_t key);

#ifdef __cplusplus
 }
#endif

#endif
