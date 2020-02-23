#include "gfx_layout.h"
#include "gfx_widget.h"
#include "gfx_menu.h"
#include "gfx_config.h"
#include "assert.h"
#include "stdio.h"

void gfx_layout_init(gfx_layout_t *layout)
{
	INIT_LIST_HEAD(&layout->widgets);
    INIT_LIST_HEAD(&layout->menu_stack);
	layout->line_cnt = 0;
	layout->line_offset = 0;
	layout->cursor_pos = 0;
}

void gfx_layout_add_widget(gfx_layout_t *layout, gfx_widget_t *widget)
{
	list_add(&widget->list_entry, &layout->widgets);
	if(layout->line_cnt < widget->y)
	{
		layout->line_cnt = widget->y;
	}
}

void gfx_layout_paint(gfx_layout_t *layout, char *buffer)
{
    struct list_head *pos;
    list_for_each(pos, &layout->widgets)
	{
		gfx_widget_t *widget = (gfx_widget_t *)pos;
		if(widget->y >= layout->line_offset && 
		   widget->y <  layout->line_offset + GFX_LINES)
        {
            uint32_t offset = widget->y - layout->line_offset;
            assert(offset >= 0);
            int offset_buff = GFX_WIDTH * offset + widget->x;
            assert(GFX_WIDTH * GFX_LINES > offset_buff);
            uint32_t size = GFX_WIDTH * GFX_LINES - offset_buff;
            widget->fpaint(widget, buffer + offset_buff, size);
		}
	}
}

void gfx_layout_prev(gfx_layout_t *layout)
{
	if(layout->cursor_pos > 0)
	{
		--layout->cursor_pos;
        if(layout->cursor_pos < layout->line_offset)
		{
            layout->line_offset = layout->cursor_pos;
		}
	}
}

void gfx_layout_next(gfx_layout_t *layout)
{
	if(layout->cursor_pos < layout->line_cnt - 1)
	{
		++layout->cursor_pos;
        if(layout->cursor_pos >= layout->line_offset + GFX_LINES)
		{
            layout->line_offset = layout->cursor_pos - GFX_LINES + 1;
		}
	}
}

void gfx_layout_key(gfx_layout_t *layout, uint32_t key)
{
    struct list_head *pos;
    list_for_each(pos, &layout->widgets)
    {
        gfx_widget_t *widget = (gfx_widget_t *)pos;
        if(widget->y == layout->cursor_pos)
        {
            if(widget->key)
            {
                widget->key(widget, key);
            }
            else
            {
                gfx_default_key(key);
            }
            break;
        }
    }
}

void gfx_default_key(uint32_t key)
{
    gfx_layout_t *lay = gfx_menu_layout();
    if(lay == NULL)
    {
        return;
    }
    if(key == KEY_UP)
    {
        gfx_layout_prev(lay);
    }
    else if(key == KEY_DOWN)
    {
        gfx_layout_next(lay);
    }
}
