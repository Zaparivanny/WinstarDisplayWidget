#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "gfx_config.h"
#include "gfx_layout.h"
#include "gfx_menu.h"
#include "gfx_widget.h"
#include "gfx_utils.h"
#include <iostream>


#include <string>

TEST(CmdTest, Gfx_ftos)
{
    char buffer[300] = {0};
    memset(buffer, ' ', 100);
    int l = ftoc(buffer, 10, 0, 1);
    EXPECT_EQ(l, 3);
    EXPECT_EQ(buffer[7], '0');
    EXPECT_EQ(buffer[8], '.');
    EXPECT_EQ(buffer[9], '0');
    EXPECT_EQ(buffer[10], ' ');

    for(int i = 0; i < 7; i++)
    {
        EXPECT_EQ(buffer[i], ' ');
    }

    l = ftoc(buffer, 2, 0, 1);
    EXPECT_EQ(l, 2);
    EXPECT_EQ(buffer[0], '.');
    EXPECT_EQ(buffer[1], '0');


    l = ftoc(buffer, 5, 12.5, 1);
    EXPECT_EQ(l, 4);
    EXPECT_EQ(buffer[1], '1');
    EXPECT_EQ(buffer[2], '2');
    EXPECT_EQ(buffer[3], '.');
    EXPECT_EQ(buffer[4], '5');

}

TEST(CmdTest, Gfx_itos)
{
    char buffer[300] = {0};
    memset(buffer, ' ', 100);
    int l = itoc(buffer, 10, 0);
    EXPECT_EQ(l, 1);
    EXPECT_EQ(buffer[9], '0');
    EXPECT_EQ(buffer[10], ' ');

    for(int i = 0; i < 9; i++)
    {
        EXPECT_EQ(buffer[i], ' ');
    }

    memset(buffer, ' ', 100);
    l = itoc(buffer, 10, 456);
    EXPECT_EQ(l, 3);
    EXPECT_EQ(buffer[7], '4');
    EXPECT_EQ(buffer[8], '5');
    EXPECT_EQ(buffer[9], '6');
    EXPECT_EQ(buffer[10], ' ');
    for(int i = 0; i < 7; i++)
    {
        EXPECT_EQ(buffer[i], ' ');
    }


    memset(buffer, ' ', 100);
    l = itoc(buffer, 2, 123);
    EXPECT_EQ(l, 2);
    EXPECT_EQ(buffer[0], '2');
    EXPECT_EQ(buffer[1], '3');
    EXPECT_EQ(buffer[2], ' ');

}

TEST(CmdTest, Gfx_label)
{
    gfx_layout_t layout;

    static char text[] = "label";
    static gfx_label_t label = LABEL_INIT(label, 0, 0, text, (sizeof(text) - 1));

    gfx_layout_init(&layout);
    GFX_LAYOUT_ADD_WIDGET(&layout, &label);


    char buffer[200] = {0};
    memset(buffer, ' ', GFX_LINES * GFX_WIDTH);
    gfx_layout_paint(&layout, buffer);
/*
    for(int i = 0; i < GFX_LINES; i++)
    {
        std::string str(buffer + i * GFX_WIDTH, GFX_WIDTH);
        std::cout << "[out]: |" << str << "|" << std::endl;
    }*/

}

TEST(CmdTest, Gfx_link)
{
    gfx_layout_t layout1;
    gfx_layout_t layout2;

    static char text[] = "settings";
    static gfx_link_t link = LINK_INIT(link, 0, 0, text, (sizeof(text) - 1));
    gfx_menu_reset();
    gfx_layout_init(&layout1);
    gfx_layout_init(&layout2);
    GFX_LAYOUT_ADD_WIDGET(&layout1, &link);
    link.layout = &layout2;


    gfx_menu_push(&layout1);
    gfx_menu_key(KEY_PRESSED);

    EXPECT_EQ(&layout2, gfx_menu_layout());

    /*char buffer[200] = {0};
    memset(buffer, ' ', GFX_LINES * GFX_WIDTH);
    gfx_layout_paint(gfx_menu_layout(), buffer);

    for(int i = 0; i < GFX_LINES; i++)
    {
        std::string str(buffer + i * GFX_WIDTH, GFX_WIDTH);
        std::cout << "[out]: |" << str << "|" << std::endl;
    }*/

}

TEST(CmdTest, Gfx_app)
{
    gfx_layout_t layout;

    static char text1[] = "f1";
    static char text2[] = "f2";
    static char text3[] = "f3";
    static char text4[] = "p1";

    static char text5[] = "t1";
    static char text6[] = "t2";

    static gfx_value_t labelf1 = VALUE_INIT(labelf1, 0, 0, text1, (sizeof(text1) - 1));
    static gfx_value_t labelf2 = VALUE_INIT(labelf2, 0, 1, text2, (sizeof(text2) - 1));
    static gfx_value_t labelf3 = VALUE_INIT(labelf3, 0, 2, text3, (sizeof(text3) - 1));
    static gfx_value_t labelp1 = VALUE_INIT(labelp1, 0, 3, text4, (sizeof(text4) - 1));
    static gfx_value_t labelt1 = VALUE_INIT(labelt1, 8, 0, text5, (sizeof(text5) - 1));
    static gfx_value_t labelt2 = VALUE_INIT(labelt2, 8, 1, text6, (sizeof(text6) - 1));

    labelf1.value = 10.0;
    labelf2.value = 12.0;
    labelf3.value = 10.0;

    labelp1.value = 12.0;
    labelp1.sym = 'P';

    labelt1.value = 10.0;
    labelt1.sym = 'C';

    labelt2.value = 12.0;
    labelt2.sym = 'C';

    gfx_layout_init(&layout);
    GFX_LAYOUT_ADD_WIDGET(&layout, &labelf1);
    GFX_LAYOUT_ADD_WIDGET(&layout, &labelf2);
    GFX_LAYOUT_ADD_WIDGET(&layout, &labelf3);
    GFX_LAYOUT_ADD_WIDGET(&layout, &labelp1);
    GFX_LAYOUT_ADD_WIDGET(&layout, &labelt1);
    GFX_LAYOUT_ADD_WIDGET(&layout, &labelt2);


    char buffer[200] = {0};
    memset(buffer, ' ', GFX_LINES * GFX_WIDTH);
    gfx_layout_paint(&layout, buffer);

    for(int i = 0; i < GFX_LINES; i++)
    {
        std::string str(buffer + i * GFX_WIDTH, GFX_WIDTH);
        std::cout << "[out]: |" << str << "|" << std::endl;
    }

}

TEST(CmdTest, Gfx_simple)
{
    gfx_layout_t layout;
    gfx_widget_t widget[10];
    gfx_widget_t widgetr = WGF_INIT(widgetr, 0, 7);

    gfx_layout_init(&layout);
    for(int i = 0; i < sizeof(widget) / sizeof(widget[0]); i++)
    {
        gfx_widget_init(&widget[i]);
        widget[i].y = i;
        widget[i].x = 0;
        gfx_layout_add_widget(&layout, &widget[i]);
    }


    gfx_layout_add_widget(&layout, &widgetr);

    for(int i = 0; i < 6; i++)
    {
        gfx_layout_next(&layout);
    }

    for(int i = 0; i < 4; i++)
    {
        gfx_layout_prev(&layout);
    }
    char buffer[200] = {0};
    memset(buffer, ' ', GFX_LINES * GFX_WIDTH);
    gfx_layout_paint(&layout, buffer);

    /*for(int i = 0; i < GFX_LINES; i++)
    {
        std::string str(buffer + i * GFX_WIDTH, GFX_WIDTH);
        std::cout << "[out]: |" << str << "|" << std::endl;
    }
    std::cout << "[pos]: " << (int)layout.cursor_pos << " " << (int)layout.line_offset << std::endl;*/



}


TEST(CmdTest, Gfx_menu)
{
    gfx_layout_t layout1;
    gfx_layout_t layout2;
    gfx_menu_reset();

    gfx_layout_init(&layout1);
    gfx_layout_init(&layout2);


    gfx_menu_push(&layout1);
    gfx_menu_push(&layout2);

    EXPECT_EQ(&layout2, gfx_menu_layout());

    gfx_menu_pop();
    gfx_menu_pop();
    gfx_menu_pop();
    gfx_menu_pop();
    EXPECT_EQ(&layout1, gfx_menu_layout());
}
