#include "stm32f10x.h"
#include "OLED.h"
#include "Menu.h"
#include "string.h"
#include "Delay.h"
#include "stdio.h"
#include "stdlib.h"



//const修饰的字符串会被编译器放在Flash区域里
struct Menu{
    const char* title; //菜单标题
    const char** items; //菜单项数组
    MenuAction* actions; //回调函数数组
    uint8_t itemCount; //菜单项数量
    struct Menu* parent; //父菜单指针
};

//静态全局变量，static修饰的全局变量只在当前文件可见
static Menu* currentMenu=NULL; //当前显示的菜单
static uint8_t selectedIndex=0; //当前选中的索引
static uint8_t scrollOffset=0; //滚动偏移量

//这里使用了双指针，mainMenuItems指向了
static const char* mainMenuItems[]={
    "Status",
    "Wind speed", 
    "Brightness",
    "Settings",
    "About"
};

static void ShowStatus(void);
static void ShowSettings(void);
static void ShowBrightness(void);
static void ShowSystem(void);
static void ShowAbout(void);

static MenuAction mainMenuActions[] = {
    ShowStatus,
    ShowSettings,
    ShowBrightness,
    ShowSystem,
    ShowAbout
};

static Menu mainMenu = {
    .title = "smart-fan-stm32",           // 标题
    .items = mainMenuItems,           // 菜单项数组
    .actions = mainMenuActions,       // 回调函数数组
    .itemCount = 5,                   // 5个菜单项
    .parent = NULL                    // 主菜单没有父菜单
};

static void ShowStatus(void) {

}

static void ShowSettings(void) {

}

static void ShowBrightness(void) {

}

static void ShowSystem(void) {

}

static void ShowAbout(void) {

}

void Menu_Init(void)
{
    currentMenu=&mainMenu;
    
    selectedIndex=0;
    scrollOffset=0;

    OLED_Clear();
    OLED_ShowString(1,1,"smart-fan-stm32");
    OLED_ShowString(2,2,"waiting...");
    Delay_s(3);
    Menu_Draw();
}

void Menu_Draw(void)
{
    /*
    清屏
    显示标题
    计算显示范围
    循环绘制可见菜单项
    绘制选中指示器
    绘制滚动提示
    */
   uint8_t i;
   uint8_t displayLine; //OLED显示行号
   uint8_t itemIndex; //实际菜单项索引
   uint8_t maxVisibleItems=3; //一屏最多显示三个菜单项

   if (currentMenu==NULL)
   {
        return ;
   }

   OLED_Clear();

   uint8_t titleLength=strlen(currentMenu->title);
   uint8_t titlePosition=(16-titleLength)/2 +1;

   if (titlePosition<1) {titlePosition=1;}
   OLED_ShowString(1,titlePosition,currentMenu->title);

   if (selectedIndex<scrollOffset)
   {
        scrollOffset=selectedIndex;
   }
   else if (selectedIndex>=scrollOffset+maxVisibleItems)
   {
        scrollOffset=selectedIndex-maxVisibleItems+1;
   }

   for (i=0;i<maxVisibleItems;i++)
   {
        itemIndex=scrollOffset+i;
        
        if (itemIndex >= currentMenu->itemCount)
        {
            OLED_ShowString(2+i,1,"                 ");
            continue;
        }

        displayLine=i+2;

        OLED_ShowString(displayLine,1,"                 ");

        if (itemIndex==selectedIndex)
        {
            OLED_ShowChar(displayLine,1,'>');
        }
        else
        {
            OLED_ShowChar(displayLine,1,' ');
        }

        OLED_ShowString(displayLine,3,currentMenu->items[itemIndex]);

   }
   if (currentMenu->itemCount>maxVisibleItems)
   {
        if (scrollOffset+maxVisibleItems<currentMenu->itemCount)
        {
            OLED_ShowChar(4,15,'v');
        }    
        if (scrollOffset>0)
        {
            OLED_ShowChar(2,15,'^');
        }

   }
   if (currentMenu->itemCount<=maxVisibleItems)
   {
        OLED_ShowString(4,11,"OK-Sure");
   }
}

void Menu_Up(void)
{
    if (currentMenu==NULL) {return;}
    if (selectedIndex>0)
    {
        selectedIndex--;
        Menu_Draw();
    }
}

void Menu_Down(void)
{
    if (currentMenu==NULL) {return;}
    if (selectedIndex<currentMenu->itemCount-1)
    {
        selectedIndex++;
        Menu_Draw();
    }
}

void Menu_DrawPartial(void)
{
    static uint8_t lastSelectedIndex = 0xFF;
    static uint8_t lastScrollOffset = 0xFF;
    
    // 如果选中项或滚动偏移变化，才重绘
    if (lastSelectedIndex != selectedIndex || lastScrollOffset != scrollOffset) {
        Menu_Draw();
        lastSelectedIndex = selectedIndex;
        lastScrollOffset = scrollOffset;
    }
}


