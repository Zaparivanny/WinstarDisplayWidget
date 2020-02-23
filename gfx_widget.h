#ifndef GFX_WIDGET_H
#define GFX_WIDGET_H

#include "list.h"
#include "stdint.h"

#ifdef __cplusplus
 extern "C" {
#endif

struct gfx_widget_t;

typedef void(*f_paint)(struct gfx_widget_t *widget, char* buffer, uint32_t size);
typedef void(*f_key)(struct gfx_widget_t *widget, uint32_t key);

void gfx_widget_paint(struct gfx_widget_t *widget, char *buffer, uint32_t size);
void gfx_label_paint(struct gfx_widget_t *widget, char *buffer, uint32_t size);
void gfx_link_paint(struct gfx_widget_t *widget, char *buffer, uint32_t size);
void gfx_value_paint(struct gfx_widget_t *widget, char *buffer, uint32_t size);
void gfx_menupop_paint(struct gfx_widget_t *widget, char *buffer, uint32_t size);


void gfx_value_key(struct gfx_widget_t *widget, uint32_t key);
void gfx_link_key(struct gfx_widget_t *widget, uint32_t key);
void gfx_menupop_key(struct gfx_widget_t *widget, uint32_t key);

typedef struct gfx_widget_t
{
    struct list_head list_entry;
	uint8_t x;
    uint8_t y;
	f_paint fpaint;
    f_key key;
}gfx_widget_t;

#define _WGF_INIT(name, px, py) name.list_entry = LIST_HEAD_INIT(name.list_entry),\
    name.x = px,\
    name.y = py

#define WGF_INIT(name, px, py)  {\
 _WGF_INIT(name, px, py), \
 .fpaint = gfx_widget_paint,\
 .key = NULL}

void gfx_widget_init(gfx_widget_t *widget);

typedef struct gfx_label_t
{
    gfx_widget_t base;
    uint8_t size;
    char *text;
}gfx_label_t;

#define LABEL_INIT(name, px, py, ltext, lsize)  {\
 _WGF_INIT(name.base, px, py), \
 name.base.fpaint = gfx_label_paint, \
 name.base.key = NULL,\
 name.size = lsize, \
 name.text = ltext}


typedef struct gfx_value_t
{
    gfx_widget_t base;
    uint8_t size;
    char *text;
    float value;
    char sym;
    uint32_t flags;
}gfx_value_t;

#define VALUE_INIT(name, px, py, ltext, lsize)  {\
 _WGF_INIT(name.base, px, py), \
 name.base.fpaint = gfx_value_paint, \
 name.base.key = gfx_value_key,\
 name.size = lsize, \
 name.text = ltext,\
 name.value = 0, \
 name.sym = ' ', \
 name.flags = 0}

typedef struct gfx_link_t
{
    gfx_widget_t base;
    uint8_t size;
    char *text;
    void *layout;
}gfx_link_t;

#define LINK_INIT(name, px, py, ltext, lsize)  {\
    _WGF_INIT(name.base, px, py), \
    name.base.fpaint = gfx_link_paint, \
    name.base.key = gfx_link_key,\
    name.size = lsize, \
    name.text = ltext, \
    name.layout = NULL}


typedef struct gfx_menupop_t
{
    gfx_widget_t base;
    char text[2];
}gfx_menupop_t;

#define MENUPOP_INIT(name, px, py)  {\
    _WGF_INIT(name.base, px, py), \
    name.base.fpaint = gfx_link_paint, \
    name.base.key = gfx_menupop_key,\
    name.text = "..", \
    name.layout = NULL}


#ifdef __cplusplus
 }
#endif

#endif
