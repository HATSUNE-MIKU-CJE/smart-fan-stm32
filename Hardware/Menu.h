#ifndef __MENU_H
#define __MENU_H

#include "stm32f10x.h"
typedef struct Menu Menu;
typedef void (*MenuAction)(void);
typedef enum {
    MENU_STATE_MAIN = 0,
    MENU_STATE_STATUS,
    MENU_STATE_MANUAL,
    MENU_STATE_AUTO,
    MENU_STATE_SETTINGS,
    MENU_STATE_ABOUT
} MenuState_t;

extern MenuState_t g_menu_state;

void Menu_Init(void);
void Menu_Draw(void);
void Menu_Up(void);
void Menu_Down(void);
void Menu_DrawPartial(void);
void Menu_Select(void);
void Menu_Process(void);
void Menu_ExitCurrent(void);

#endif
