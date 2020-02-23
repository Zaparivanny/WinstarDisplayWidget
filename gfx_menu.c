#include "gfx_menu.h"
#include "gfx_widget.h"
#include "gfx_layout.h"
#include "list.h"


typedef struct gfx_menu_context_t
{
    struct list_head *stack;
}gfx_menu_context_t;

static inline gfx_menu_context_t *_gfx_menu_context(void)
{
    static gfx_menu_context_t gfx_menu_context = {
        .stack = NULL,
    };
    return &gfx_menu_context;
}

void gfx_menu_push(struct gfx_layout_t *layout)
{
    gfx_menu_context_t *context = _gfx_menu_context();
    if(context->stack == NULL)
    {
        context->stack = &layout->menu_stack;
    }
    else
    {
        list_add(&layout->menu_stack, context->stack);
    }
}

void gfx_menu_pop()
{
    gfx_menu_context_t *context = _gfx_menu_context();
    if(context->stack && !list_empty(context->stack))
    {
        list_del(context->stack->next);
    }
}

gfx_layout_t *gfx_menu_layout()
{
    gfx_menu_context_t *context = _gfx_menu_context();
    if(context->stack)
    {
        return (gfx_layout_t *)context->stack->next;
    }
    return NULL;
}



void gfx_menu_key(uint32_t key)
{
    gfx_layout_t *lay = gfx_menu_layout();
    if(lay)
    {
        gfx_layout_key(lay, key);
    }
}

void gfx_menu_reset()
{
    gfx_menu_context_t *context = _gfx_menu_context();
    context->stack = NULL;
}
