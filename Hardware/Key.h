#ifndef __KEY_H
#define __KEY_H

typedef enum{
    KEY_EVENT_NONE=0,
    KEY_EVENT_CONFIRM,
    KEY_EVENT_BACK,
    KEY_EVENT_RESET
}KeyEvent;

void Key_Init(void);
void Key_Scan(void);
KeyEvent Key_GetEvent(void);

#endif
