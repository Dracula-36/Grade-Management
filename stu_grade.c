/*************************************************************************
	> File Name: menu.c
	> Author: Guanyu Li
	> Mail: guanyuli@hustunique.com
	> Created Time: 2015年03月15日 星期日 17时48分19秒
 ************************************************************************/

#include"grade.h"
#include"method.h"

int main(int argc, char **argv)
{

    gtk_init(&argc, &argv);        //gtk初始化
    
    loadmenu();                    //生成主界面
    
    gtk_main();                    //等待用户触发事件

    return 0;

}

