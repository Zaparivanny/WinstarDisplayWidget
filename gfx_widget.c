#include "gfx_widget.h"
#include "gfx_layout.h"
#include "gfx_config.h"
#include "gfx_utils.h"
#include "gfx_menu.h"

#include "assert.h"
#include "string.h"
#include "stdio.h"



void gfx_widget_init(gfx_widget_t *widget)
{
	INIT_LIST_HEAD(&widget->list_entry);
	widget->x = 0;
	widget->y = 0;
	widget->fpaint = gfx_widget_paint;
}

void gfx_widget_paint(gfx_widget_t *widget, char *buffer, uint32_t size)
{
    sprintf(buffer, "test %i", widget->y);
    int n = strlen(buffer);
    buffer[n] = ' ';
}

void gfx_label_paint(struct gfx_widget_t *widget, char *buffer, uint32_t size)
{
    gfx_label_t *label = (gfx_label_t*)widget;
    uint32_t len = label->size < size ? label->size : size;
    memcpy(buffer, label->text, len);
}

void gfx_value_paint(struct gfx_widget_t *widget, char *buffer, uint32_t size)
{
    gfx_value_t *w = (gfx_value_t*)widget;
    uint32_t len = w->size < size ? w->size : size;
    memcpy(buffer, w->text, len);
    assert(size >= 8);
    ftoc(buffer, 7, w->value, 1);
    buffer[7] = w->sym;

}

void gfx_value_key(gfx_widget_t *widget, uint32_t key)
{
    gfx_value_t *w = (gfx_value_t*)widget;
    if(key == KEY_PRESSED)
    {
        w->flags ^= 1;
    }
    else
    {
        if(w->flags & 0x1)
        {
            if(key == KEY_UP)
            {
                w->value += 1;
            }
            else if(key == KEY_DOWN)
            {
                w->value -= 1;
            }
        }
        else
        {
            gfx_default_key(key);
        }
    }

}


void gfx_link_paint(gfx_widget_t *widget, char *buffer, uint32_t size)
{
    gfx_label_t *label = (gfx_label_t*)widget;
    uint32_t len = label->size < size ? label->size : size;
    memcpy(buffer, label->text, len);
    buffer[GFX_WIDTH - 1] = '>';
}

void gfx_link_key(struct gfx_widget_t *widget, uint32_t key)
{
    gfx_link_t *link = (gfx_link_t*)widget;
    if(link->layout && key == KEY_PRESSED)
    {
        gfx_menu_push(link->layout);
    }
}




void gfx_menupop_paint(gfx_widget_t *widget, char *buffer, uint32_t size)
{
    assert(size >= 2);
    buffer[0] = '.';
    buffer[1] = '.';
}


void gfx_menupop_key(gfx_widget_t *widget, uint32_t key)
{
    if(key == KEY_PRESSED)
    {
        gfx_menu_pop();
    }
}
