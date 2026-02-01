#ifndef __MENU_H
#define __MENU_H

#include "stm32f10x.h"
typedef struct Menu Menu;
typedef void (*MenuAction)(void);

void Menu_Init(void);
void Menu_Draw(void);
void Menu_Up(void);
void Menu_Down(void);
void Menu_DrawPartial(void);
void Menu_Select(void);

#endif
