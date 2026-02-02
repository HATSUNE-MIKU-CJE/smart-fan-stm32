#include "stm32f10x.h"
#include "OLED.h"
#include "Menu.h"
#include "string.h"
#include "Delay.h"
#include "stdio.h"
#include "stdlib.h"
#include "LightSensor.h"
#include "AD.h"
#include "Key.h"

MenuState_t g_menu_state = MENU_STATE_MAIN;


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
static uint8_t displayLine; //OLED显示行号
static uint8_t itemIndex; //实际菜单项索引
static uint8_t maxVisibleItems=3; //一屏最多显示三个菜单项

//这里使用了双指针，mainMenuItems指向了
static const char* mainMenuItems[]={
    "Status",
    "Manual Control", 
    "Auto Mode",
    "Settings",
    "About"
};

static void ShowStatus(void);
static void ShowManualControl(void);
static void ShowAutoMode(void);
static void ShowSettings(void);
static void ShowAbout(void);

static MenuAction mainMenuActions[] = {
    ShowStatus,
    ShowManualControl,
    ShowAutoMode,
    ShowSettings,
    ShowAbout
};

static Menu mainMenu = {
    .title = "smart-fan-stm32",           // 标题
    .items = mainMenuItems,           // 菜单项数组
    .actions = mainMenuActions,       // 回调函数数组
    .itemCount = 5,                   // 5个菜单项
    .parent = NULL                    // 主菜单没有父菜单
};

// 在Menu.c中添加一个全局变量记录状态页面是否需要重绘
static uint8_t status_need_redraw = 1;

// 统一的ShowStatus函数（非阻塞）
static void ShowStatus(void) {
    static uint32_t last_update = 0;
    static uint8_t first_update = 1;
    
    // 进入状态页面
    g_menu_state = MENU_STATE_STATUS;
    
    // 如果需要重绘静态框架（第一次进入或返回后）
    if (status_need_redraw) {
        OLED_Clear();
        OLED_ShowString(1, 1, "System Status");
        
        // 绘制静态标签
        OLED_ShowString(2, 1, "Light:");
        OLED_ShowString(2, 8, "/5");
        OLED_ShowString(3, 1, "AD:");
        OLED_ShowString(3, 10, "V:");
        OLED_ShowString(4, 1, "T:--C H:--%");
        
        status_need_redraw = 0;
        first_update = 1;  // 标记需要立即更新
    }
    
    // 每500ms更新一次动态数据
    if (first_update||GetTick() - last_update > 500) {
        // 获取传感器数据
        uint8_t lightLevel = LightSensor_GetLevel();
        uint16_t adValue = AD_GetValue();
        const char* lightDesc = LightSensor_GetLightDescription();
        float voltage = (float)adValue / 4095 * 3.3;
        
        // 更新光照等级
        OLED_ShowNum(2, 7, lightLevel, 1);
        
        // 更新光照描述（清除旧内容）
        OLED_ShowString(2, 11, "      ");
        for (uint8_t j = 0; j < 6 && lightDesc[j] != '\0'; j++) {
            OLED_ShowChar(2, 11 + j, lightDesc[j]);
        }
        
        // 更新AD值和电压
        OLED_ShowNum(3, 5, adValue, 4);
        OLED_ShowNum(3, 13, (uint16_t)(voltage*100)/100, 1);
        OLED_ShowString(3, 14, ".");
        OLED_ShowNum(3, 15, (uint16_t)(voltage*100)%100, 2);
        
        last_update = GetTick();
        first_update = 0;  // 重置第一次更新标志
    }
}


static void ShowManualControl(void) {
    OLED_Clear();
    Delay_s(2);
    Menu_Draw();
}

static void ShowAutoMode(void) {
    OLED_Clear();
    Delay_s(2);
    Menu_Draw();
}

static void ShowSettings(void) {
    OLED_Clear();
    Delay_s(2);
    Menu_Draw();
}

static void ShowAbout(void) {
    OLED_Clear();
    Delay_s(2);
    Menu_Draw();
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

void Menu_Select(void) {
    // 根据当前状态处理
    if (g_menu_state == MENU_STATE_MAIN) {
        // 主菜单：执行选中的动作
        switch (selectedIndex) {
            case 0: ShowStatus(); break;
            case 1: ShowManualControl(); break;
            case 2: ShowAutoMode(); break;
            case 3: ShowSettings(); break;
            case 4: ShowAbout(); break;
            default: break;
        }
    } else {
        // 子页面：按Select键返回主菜单
        Menu_ExitCurrent();
    }
}

// 新增：菜单状态处理函数（在主循环中调用）
void Menu_Process(void) {
    switch (g_menu_state)
    {
    case MENU_STATE_STATUS:
        ShowStatus();
        break;
    default:
        break;
    }
    // 目前只有状态页面需要特殊处理
    // ShowStatus函数内部会处理定时更新
    // 这里可以留空，或者处理其他页面的逻辑
    // 因为ShowStatus是非阻塞的，不需要在这里做任何事情
}

// 新增：退出当前页面回到主菜单
void Menu_ExitCurrent(void) {
    g_menu_state = MENU_STATE_MAIN;
    status_need_redraw = 1;  // 标记下次进入状态页面需要重绘
    Menu_Draw();
}
