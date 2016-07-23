/*************************************************************************
	> File Name: method.h
	> Author: Guanyu Li
	> Mail: guanyuli@hustunique.com
	> Created Time: 2015年03月30日 星期一 11时26分31秒
 ************************************************************************/

#include"grade.h"

result cla_find(char *clanum, CLASS *head)
{

    result re = {0, NULL};
    CLASS *p = head;

    while (p != NULL)               //遍历链表查找满足条件的结点
    {   
        if (strcmp(clanum, p->cla_num) == 0) 
        {
            re.flag = 1;
            re.ptr = (void *)p;
            break;
        }
        
        p = p->cla_p;
    }

    return re;

}

result stu_find(char *stunum, CLASS *head)
{

    result re = {0, NULL};
    CLASS *ptr = head;
    STUDENT *p = NULL;

    while (ptr != NULL)     //二级嵌套循环遍历链表查找满足条件的结点
    {
        p = ptr->stu_hp;
        
        while (p != NULL)
        {
            
            if (strcmp(stunum, p->stu_num) == 0) 
            {
                re.flag = 1;
                re.ptr = (void *)p;
                break;
            }
            
            p = p->stu_p;
        }
        
        ptr = ptr->cla_p;
    }

    return re;
}

result sub_find(char *subname, CLASS *head)
{
    
    result re = {0, NULL};
    CLASS *ptr = head;
    STUDENT *p = NULL;
    GRADE *q = NULL;

    while (ptr != NULL)     //三级嵌套循环遍历链表查找满足条件的结点
    {
        p = ptr->stu_hp;
        
        while (p != NULL)
        {
            q = p->sub_hp;
            
            while (q != NULL)
            {
                if (strcmp(subname, q->sub_name) == 0) 
                {
                    re.flag = 1;
                    re.ptr = (void *)q;
                    break;
                }
                
                q = q->sub_p;
            }
            
            p = p->stu_p;
        }
        
        ptr = ptr->cla_p;
    }
    
    return re;

}

void sub_change(int i, char *subchg, char *subname, CLASS *head)
{

    CLASS *ptr = head; 
    STUDENT *p = NULL;
    GRADE *q = NULL;
    
    while (ptr != NULL)      //遍历链表   
    {
        p = ptr->stu_hp;
        
        while (p != NULL)
        {
            q = p->sub_hp;
            
            while (q != NULL)
            {
                if (strcmp(subname, q->sub_name) == 0) 
                {/*根据i判断修改选项*/
                    switch (i) {                        
                        case 1:
                            strcpy(q->sub_name, subchg);
                            break;
                        case 2:
                            q->sub_sem = atoi(subchg);
                            break;
                        case 3:
                            q->sub_hour = atoi(subchg);
                            break;
                        case 4:
                            q->sub_score = atof(subchg);
                            break;
                    }
                }
                
                q = q->sub_p;
            }
            
            p = p->stu_p;
        }
        
        ptr = ptr->cla_p;
    }

}

GtkWidget *CreatMenuItem(GtkWidget *MenuBar, char *itemname)
{

    GtkWidget *MenuItem;

    MenuItem = gtk_menu_item_new_with_label(itemname);
    gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), MenuItem); //创建子菜单
    gtk_widget_show(MenuItem);
    
    return MenuItem;

}

void loadmenu(void)
{
    
    GtkWidget *window;
    GtkWidget *MenuBar;
    GtkWidget *Menu;
    GtkWidget *Menu_Next;
    GtkWidget *Menu_NNext;
    GtkWidget *box;
    GtkWidget *MenuItem_NNext;
    GtkWidget *MenuItem_Next;
    GtkWidget *MenuItem;
    GtkWidget *Item;

    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);   //创建窗口
    gtk_window_set_title(GTK_WINDOW(window), "学生成绩管理系统");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);  
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);  
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);
    MenuBar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(box), MenuBar, FALSE, TRUE, 0);

    MenuItem = CreatMenuItem(MenuBar, "文    件");   //创建多级菜单
    Menu = gtk_menu_new();
    Item = CreatMenuItem(Menu, "数据加载");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(load_event), window);
    Item = CreatMenuItem(Menu, "数据保存");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(save_event), window);
    Item = CreatMenuItem(Menu,"数据备份");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(backup_event), window);
    Item = CreatMenuItem(Menu,"数据恢复");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(restore_event), window);
    Item = CreatMenuItem(Menu, "退出系统");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(exit_event), NULL);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem), Menu);
    gtk_widget_show(Menu);

    MenuItem = CreatMenuItem(MenuBar, "数据维护");
    Menu = gtk_menu_new();
    MenuItem_Next = CreatMenuItem(Menu, "班级信息维护");
    Menu_Next = gtk_menu_new();
    Item = CreatMenuItem(Menu_Next, "录入");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(cla_fill_event), NULL);
    Item = CreatMenuItem(Menu_Next, "修改");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(cla_amend_event), NULL);
    Item = CreatMenuItem(Menu_Next, "删除");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(cla_del_event), NULL);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem_Next), Menu_Next);
    gtk_widget_show(Menu_Next);
    MenuItem_Next = CreatMenuItem(Menu, "学生基本信息维护");
    Menu_Next = gtk_menu_new();
    Item = CreatMenuItem(Menu_Next, "录入");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(stu_fill_event), NULL);
    Item = CreatMenuItem(Menu_Next, "修改");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(stu_amend_event), NULL);
    Item = CreatMenuItem(Menu_Next, "删除");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(stu_del_event), NULL);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem_Next), Menu_Next);
    gtk_widget_show(Menu_Next);
    MenuItem_Next = CreatMenuItem(Menu, "学生课程成绩基本信息维护");
    Menu_Next = gtk_menu_new();
    Item = CreatMenuItem(Menu_Next, "录入");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(grade_fill_event), NULL);
    MenuItem_NNext = CreatMenuItem(Menu_Next, "修改");
    Menu_NNext = gtk_menu_new();
    Item = CreatMenuItem(Menu_NNext, "课程基本信息修改");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(sub_amend_event), NULL);
    Item = CreatMenuItem(Menu_NNext, "学生成绩信息修改");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(grade_amend_event), NULL);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem_NNext), Menu_NNext);
    gtk_widget_show(Menu_NNext);
    Item = CreatMenuItem(Menu_Next, "删除");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(grade_del_event), NULL);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem_Next), Menu_Next);
    gtk_widget_show(Menu_Next);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem), Menu);
    gtk_widget_show(Menu);

    MenuItem = CreatMenuItem(MenuBar, "数据查询");
    Menu = gtk_menu_new();
    Item = CreatMenuItem(Menu, "班级信息查询");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(cla_refer_event), NULL);
    MenuItem_NNext = CreatMenuItem(Menu, "学生基本信息查询");
    Menu_NNext = gtk_menu_new();
    Item = CreatMenuItem(Menu_NNext, "以学号为条件查找");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(stu_refer1_event), NULL);
    Item = CreatMenuItem(Menu_NNext, "以已修课程学分、已获学分和加权平均分为条件查找");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(stu_refer2_event), NULL);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem_NNext), Menu_NNext);
    gtk_widget_show(Menu_NNext);
    MenuItem_NNext = CreatMenuItem(Menu, "学生课程成绩基本信息查询");
    Menu_NNext = gtk_menu_new();
    Item = CreatMenuItem(Menu_NNext, "以学号和课程名为条件查找");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(sub_refer1_event), NULL);
    Item = CreatMenuItem(Menu_NNext, "以开课学期和考试成绩为条件查找");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(sub_refer2_event), NULL);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem_NNext), Menu_NNext);
    gtk_widget_show(Menu_NNext);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem), Menu);
    gtk_widget_show(Menu);

    MenuItem = CreatMenuItem(MenuBar, "数据统计");
    Menu = gtk_menu_new();
    Item = CreatMenuItem(Menu, "按班级统计");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(count_total), NULL);
    Item = CreatMenuItem(Menu, "按学生统计");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(count_semester_event), NULL);
    Item = CreatMenuItem(Menu, "按课程统计");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(count_grade), NULL);
    Item = CreatMenuItem(Menu, "按学期统计");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(count_subject), NULL);
    Item = CreatMenuItem(Menu, "按班级和学期统计");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(count_class_event), NULL);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem), Menu);
    gtk_widget_show(Menu);

    MenuItem = CreatMenuItem(MenuBar,"帮    助");
    Menu = gtk_menu_new();
    Item = CreatMenuItem(Menu, "帮助主题");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(message_event), "暂无帮助");
    Item = CreatMenuItem(Menu, "系统版本权说明");
    g_signal_connect(G_OBJECT(Item), "activate", G_CALLBACK(about_event), NULL);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem), Menu);
    gtk_widget_show(Menu);

    gtk_widget_show(box);
    gtk_widget_show(MenuBar);      
    gtk_widget_show(window);           //显示各构件

}

void exit_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *button;
    GtkWidget *hbox;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *dia_window;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);   //创建窗口
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 150, 120);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "退出系统?");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    label = gtk_label_new("\n请先确认保存数据,\n    然后后再退出!");
    gtk_widget_show(label);
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    button = gtk_button_new_with_label("退出系统");  //设置按钮及回调函数
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show(vbox);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(dia_window);

}


void destroy(GtkWidget *widget,gpointer *data)
{

    gtk_widget_destroy(GTK_WIDGET(data));       //退出data所指构件

}

void about_event(GtkWidget *widget, gpointer *data)
{
    
    GtkWidget *about;

    const char *author[] = {"Guanyu Li", NULL};

    about = gtk_about_dialog_new();         //设置版权信息
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about), "学生成绩信息管理系统");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about), "版本号 1.0");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about), "一个管理学生成绩信息的简单程序");
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about), "https://github.com/Dracula-36");
    gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about), "程序主页");
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about), author);
    gtk_about_dialog_set_artists(GTK_ABOUT_DIALOG(about), author);
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about), "© Dracula");
    gtk_dialog_run(GTK_DIALOG(about));

    gtk_widget_destroy(about);

}

void message_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dialog;

    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_message_dialog_new(NULL,flags,GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE, NULL);
    gtk_message_dialog_set_markup(GTK_MESSAGE_DIALOG(dialog), (char *)(data));                  //弹出含有data所指信息的对话框
    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(dialog);

}

void cla_fill_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *label;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);       //创建窗口
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "班级信息录入");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);  //组织窗口中的构件
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 班级编号:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry1 = gtk_entry_new();
    gtk_widget_show(entry1);
    gtk_box_pack_start(GTK_BOX(hbox), entry1, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    label = gtk_label_new(" 班  导  师:");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry2 = gtk_entry_new();
    gtk_widget_show(entry2);
    gtk_box_pack_start(GTK_BOX(hbox), entry2, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    label = gtk_label_new(" 联系电话:");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry3 = gtk_entry_new();
    gtk_widget_show(entry3);
    gtk_box_pack_start(GTK_BOX(hbox), entry3, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 100);
    button = gtk_button_new_with_label("录    入");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(cla_fill), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);  //封装构件
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void cla_fill(GtkWidget *widget, gpointer *data)
{
 
    CLASS *p = *hp;
    char buf[20];

    if (*hp == NULL)
    {
        *hp = (CLASS *)malloc(sizeof(CLASS));
        p = *hp;
    }
    else 
    {      
        while (p->cla_p != NULL) 
            p = p->cla_p;
        p->cla_p = (CLASS *)malloc(sizeof(CLASS));
        p = p->cla_p;
    }

    strcpy(buf, gtk_entry_get_text(GTK_ENTRY(entry1)));
    
    if (cla_find(buf, *hp).flag == 1) 
    {
        message_event(NULL, (void **)"此班级信息已存在，请选择修改或删除该班级信息,或者录入其他班级信息！\n");
        return;
    }

    strcpy(p->cla_num, buf);
    strcpy(p->cla_teacher, gtk_entry_get_text(GTK_ENTRY(entry2)));
    strcpy(p->cla_tel, gtk_entry_get_text(GTK_ENTRY(entry3)));
    p->cla_p = NULL;
    p->stu_hp = NULL;
    message_event(NULL, (void **)"录入成功");

    gtk_widget_destroy(GTK_WIDGET(data));   //关闭该窗口及其调用它的窗口

}

void cla_amend_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *vbox0;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *label;

    CLASS *p = head;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "班级信息修改");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 班级编号:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "请选择");
    
    while ( p!= NULL)
    {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), p->cla_num);
        p = p->cla_p;
    }                           //在combo中显示已经录入的班级编号

    gtk_widget_show(combo);
    gtk_box_pack_start(GTK_BOX(hbox),combo,FALSE,FALSE,0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,0);

    label = gtk_label_new("请选择修改选项:");
    vbox0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(vbox0), label, FALSE, FALSE, 0);
    button1 = gtk_radio_button_new_with_label(NULL, "班级编号");
    gtk_widget_show(button1);g_signal_connect(G_OBJECT(button1), "pressed", G_CALLBACK(button_event), (gpointer *)1);
    g_signal_connect(G_OBJECT(button1), "pressed", G_CALLBACK(button_event), (gpointer *)1);
    gtk_box_pack_start(GTK_BOX(vbox0), button1, FALSE, FALSE, 0);
    button2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(button1)), "班导师");
    gtk_widget_show(button2);
    g_signal_connect(G_OBJECT(button2), "pressed", G_CALLBACK(button_event), (gpointer *)2);
    gtk_box_pack_start(GTK_BOX(vbox0), button2, FALSE, FALSE, 0);
    button3 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(button2)), "联系电话");
    gtk_widget_show(button3);
    g_signal_connect(G_OBJECT(button3), "pressed", G_CALLBACK(button_event), (gpointer *)3);
    gtk_box_pack_start(GTK_BOX(vbox0), button3, FALSE, FALSE, 0);
    gtk_widget_show(vbox0);
    gtk_box_pack_start(GTK_BOX(vbox), vbox0, FALSE, FALSE, 0);

    label = gtk_label_new(" 请输入新的信息:");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry3 = gtk_entry_new();
    gtk_widget_show(entry3);
    gtk_box_pack_start(GTK_BOX(hbox), entry3, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 140);
    button = gtk_button_new_with_label("修    改");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(cla_amend), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void cla_amend(GtkWidget *widget, gpointer *data)
{

    CLASS *p = NULL;
    char buf[20];

    strcpy(buf, gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo)));

    if (cla_find(buf, head).flag != 1) 
    {
        message_event(NULL, (void **)"无此班级信息，请先录入该班级信息！");
        return;
    }
    else 
        p = (CLASS *)cla_find(buf, head).ptr;

    switch (choose) {                //根据choose判断修改选项
        case 1:
            strcpy(buf, gtk_entry_get_text(GTK_ENTRY(entry3)));
            if (cla_find(buf, head).flag == 1) 
            {
                message_event(NULL,(void **)"此班级信息已存在，请选择修改或删除该班级信息！\n");
                return;
            }
            strcpy(p->cla_num, buf);
            break;
        case 2:
            strcpy(p->cla_teacher, gtk_entry_get_text(GTK_ENTRY(entry3)));
            break;
        case 3:
            strcpy(p->cla_tel, gtk_entry_get_text(GTK_ENTRY(entry3)));
            break;
    }

    message_event(NULL, (void **)"修改成功");
    gtk_widget_destroy(GTK_WIDGET(data));

}

void cla_del_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *label;

    CLASS *p = head;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 150, 80);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "班级信息删除");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 班级编号:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),"请选择");

    while (p  != NULL)
    {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), p->cla_num);
        p = p->cla_p;
    }

    gtk_widget_show(combo);

    gtk_box_pack_start(GTK_BOX(hbox), combo, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 50);
    button = gtk_button_new_with_label("删    除");   
    gtk_widget_show(button);             //先弹出警告
    g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(cla_del_warning_event),dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void cla_del_warning_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *button;
    GtkWidget *hbox;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *dia_window;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 100);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "警告!");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);
    gtk_window_set_transient_for(GTK_WINDOW(dia_window), GTK_WINDOW(data));
    gtk_window_set_destroy_with_parent(GTK_WINDOW(dia_window), TRUE);

    label = gtk_label_new("    警告：删除该班级信息后，该\n班级内的学生及其成绩信息也均\n被删除，确认继续删除？");
    gtk_widget_show(label);           //显示警告信息
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 70);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("确    定");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(cla_del), data);
    gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show(vbox);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(dia_window);

}

void cla_del(GtkWidget *widget, gpointer *data)
{
    CLASS *prior = *hp;
    CLASS *current = *hp;

    char clanum[20];

    strcpy(clanum, gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo)));
    
    while ((strcmp(clanum, current->cla_num) != 0) && current != NULL)
    {
        prior = current;
        current = current->cla_p;
    }

    if (current == *hp)
        *hp = current->cla_p;
    else
        prior->cla_p = current->cla_p;
    free(current);                               //链表结点删除

    message_event(NULL, (void **)"删除成功");
    gtk_widget_destroy(GTK_WIDGET(data));

}

void stu_fill_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *label;
    
    CLASS *p = head;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  //设置窗口
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "学生基本信息录入");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 所在班级:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE,FALSE, 0);
    combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "请选择");
    
    while (p != NULL)
    {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), p->cla_num);
        p = p->cla_p;
    }

    gtk_widget_show(combo);
    gtk_box_pack_start(GTK_BOX(hbox), combo, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    label = gtk_label_new(" 学    号:");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry1 = gtk_entry_new();
    gtk_widget_show(entry1);
    gtk_box_pack_start(GTK_BOX(hbox), entry1, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    label = gtk_label_new(" 姓    名:");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry2 = gtk_entry_new();
    gtk_widget_show(entry2);
    gtk_box_pack_start(GTK_BOX(hbox), entry2, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox,  FALSE, FALSE, 0);

    label = gtk_label_new(" 性    别:");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    button1 = gtk_radio_button_new_with_label(NULL, "男");
    gtk_widget_show(button1);
    g_signal_connect(G_OBJECT(button1), "pressed", G_CALLBACK(button_event), (gpointer *)1);
    gtk_box_pack_start(GTK_BOX(hbox), button1, FALSE, FALSE, 0);
    button2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(button1)), "女");
    gtk_widget_show(button2);
    g_signal_connect(G_OBJECT(button2), "pressed", G_CALLBACK(button_event), (gpointer *)2);
    gtk_box_pack_start(GTK_BOX(hbox), button2, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0); //组建窗口

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 100);    //设置按钮
    button = gtk_button_new_with_label("录    入");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(stu_fill), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void stu_fill(GtkWidget *widget, gpointer *data)
{

    char buf[20] ;

    strcpy(buf,
           gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo)));
    CLASS *find_class = (CLASS *)cla_find(buf, head).ptr;

    strcpy(buf, gtk_entry_get_text(GTK_ENTRY(entry1)));

    if (stu_find(buf, head).flag == 1) 
    {
        message_event(NULL, (void **)"此学生信息已存在，请选择修改或删除该学生信息！\n");
        return;
    }

    STUDENT *stuhp = find_class->stu_hp;
    STUDENT *p = stuhp;

    if (stuhp == NULL)           //判断所插入位置是否为该链第一个结点
    {
        find_class->stu_hp = (STUDENT *)malloc(sizeof(STUDENT));
        p = find_class->stu_hp;
    }
    else 
    {      
        while (p->stu_p != NULL) 
            p = p->stu_p;
        p->stu_p = (STUDENT *)malloc(sizeof(STUDENT));
        p = p->stu_p;
    }

    strcpy(p->stu_num, buf);
    strcpy(p->cla_num,
           gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo)));
    strcpy(p->stu_name, gtk_entry_get_text(GTK_ENTRY(entry2)));

    if (choose == 1)
        p->stu_sex = 'm';
    else 
        p->stu_sex = 'w';

    p->learn_score = 0;
    p->get_score = 0;
    p->average = 0;
    p->stu_p = NULL;
    p->sub_hp = NULL;

    message_event(NULL, (void **)"录入成功");
    gtk_widget_destroy(GTK_WIDGET(data));

}

void stu_amend_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *vbox0;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *label;

    CLASS *p = head;
    STUDENT *q = NULL;
    choose = 1;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "学生信息修改");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 学号:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "请选择");
    
    while (p!=NULL)
    {
        q = p->stu_hp;
        
        while (q != NULL)
        {
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), q->stu_num);
            q = q->stu_p;
        }
        
        p = p->cla_p;
    }

    gtk_widget_show(combo);
    gtk_box_pack_start(GTK_BOX(hbox), combo, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    label = gtk_label_new("请选择修改选项:");
    vbox0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(vbox0), label, FALSE, FALSE, 0);
    button1 = gtk_radio_button_new_with_label(NULL, "所在班级");
    //gtk_widget_show(button1);
    g_signal_connect(G_OBJECT(button1), "pressed", G_CALLBACK(button_event), (gpointer *)1);
    //gtk_box_pack_start(GTK_BOX(vbox0), button1, FALSE, FALSE, 0);
    button2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(button1)), "学    号");
    gtk_widget_show(button2);
    g_signal_connect(G_OBJECT(button2), "pressed", G_CALLBACK(button_event), (gpointer *)2);
    gtk_box_pack_start(GTK_BOX(vbox0), button2, FALSE, FALSE, 0);
    button3 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(button2)), "姓    名");
    gtk_widget_show(button3);
    g_signal_connect(G_OBJECT(button3), "pressed", G_CALLBACK(button_event), (gpointer *)3);
    gtk_box_pack_start(GTK_BOX(vbox0), button3, FALSE, FALSE, 0);
    button4 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(button2)), "性    别");
    gtk_widget_show(button4);
    g_signal_connect(G_OBJECT(button4), "pressed", G_CALLBACK(button_event), (gpointer *)4);
    gtk_box_pack_start(GTK_BOX(vbox0), button4, FALSE, FALSE, 0);
    gtk_widget_show(vbox0);
    gtk_box_pack_start(GTK_BOX(vbox), vbox0, FALSE, FALSE, 0);

    label = gtk_label_new(" 请输入新的信息:");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry3 = gtk_entry_new();
    gtk_widget_show(entry3);
    gtk_box_pack_start(GTK_BOX(hbox), entry3, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 140);
    button = gtk_button_new_with_label("修    改");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(stu_amend), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void stu_amend(GtkWidget *widget,gpointer *data)
{

    STUDENT *p = NULL;
    STUDENT *q = NULL;

    char buf[20];

    strcpy(buf,gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo)));
    p = (STUDENT *)stu_find(buf, head).ptr;

    switch (choose) {
        /*case 1:
            strcpy(buf,gtk_entry_get_text(GTK_ENTRY(entry3)));
            if (cla_find(buf, head).flag != 1) 
            {
                message_event(NULL, (void **)"无此班级信息，请先录入该班级信息！");
                return;
            }
            else 
            {
                strcpy(p->cla_num, buf);
                q = ((CLASS *)cla_find(buf,head).ptr)->stu_hp;
                
                if (q == NULL)
                    ((CLASS *)cla_find(buf,head).ptr)->stu_hp = p;
                else 
                {
                    while (q->stu_p != NULL)
                        q = q->stu_p;
                    q->stu_p = p;
                }
                
                STUDENT *prior, *current, *headp;
                char stunum[20];
                
                strcpy(stunum,new.stu_num);
                headp = ((CLASS *)cla_find(buf, head).ptr)->stu_hp;
                prior = headp;
                current = headp;
                
                while ((strcmp(stunum,current->stu_num)!= 0) && current != NULL)
                {
                    prior = current;
                    current = current->stu_p;
                }
                
                if (current == headp)
                    ((CLASS *)(cla_find(((STUDENT *)(stu_find(stunum, head).ptr))->cla_num, head).ptr))->stu_hp = current->stu_p;
                else
                    prior->stu_p = current->stu_p;
                
                p->stu_p = NULL;
            }
            
            break;*/
        case 2:
            strcpy(buf, gtk_entry_get_text(GTK_ENTRY(entry3)));
            
            if (stu_find(buf, head).flag == 1)
            {  
                message_event(NULL, (void **)"此学生信息已存在，请选择修改或删除该学生信息！\n");
                return;
            }
            
            strcpy(p->stu_num, buf);
            break;
        case 3:
            strcpy(p->stu_name, gtk_entry_get_text(GTK_ENTRY(entry3)));
            break;
        case 4:
            if (strcmp(gtk_entry_get_text(GTK_ENTRY(entry3)), "男") != 0
               &&strcmp(gtk_entry_get_text(GTK_ENTRY(entry3)), "女") != 0)
            {
                message_event(NULL, (void **)"性别输入有误,请输入'男'或'女'!\n");
                return;
            }
            
            if (strcmp(gtk_entry_get_text(GTK_ENTRY(entry3)), "男") == 0)
                p->stu_sex = 'm';
            if (strcmp(gtk_entry_get_text(GTK_ENTRY(entry3)), "女") == 0)
                p->stu_sex = 'w';
            break;
    }

    message_event(NULL, (void **)"修改成功");
    gtk_widget_destroy(GTK_WIDGET(data));

}

void stu_del_event(GtkWidget *widget, gpointer *data)
{
 
    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *label;

    CLASS *p = head;
    STUDENT *q = NULL;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);    //设置窗口
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 150, 80);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "学生信息删除");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 学    号:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "请选择");

    while (p != NULL)
    {
        q = p->stu_hp;
        
        while (q != NULL)
        {
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),q->stu_num);
            q = q->stu_p;
        }
        
        p = p->cla_p;
    }                    //将所有录入的学生学号加入combo中

    gtk_widget_show(combo);
    gtk_box_pack_start(GTK_BOX(hbox), combo, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 50);
    button = gtk_button_new_with_label("删    除");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(stu_del_warning_event), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void stu_del_warning_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *button;
    GtkWidget *hbox;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *dia_window;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 100);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "警告!");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);
    gtk_window_set_transient_for(GTK_WINDOW(dia_window), GTK_WINDOW(data));
    gtk_window_set_destroy_with_parent(GTK_WINDOW(dia_window), TRUE);

    label = gtk_label_new("    警告：删除该学生基本信息后，\n该学生成绩信息也均被删除，确认\n继续删除？");
    gtk_widget_show(label);
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 70);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("确    定");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(stu_del), data);
    gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show(vbox);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(dia_window);

}

void stu_del(GtkWidget *widget, gpointer *data)
{
 
    STUDENT *prior, *current, *headp;
    char stunum[20];
    
    strcpy(stunum, gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo)));
    headp = ((CLASS *)(cla_find(((STUDENT *)(stu_find(stunum, head).ptr))->cla_num, head).ptr))->stu_hp;
    prior = headp;
    current = headp;
    
    while ((strcmp(stunum, current->stu_num)!= 0) && current != NULL)
    {
        prior = current;
        current = current->stu_p;
    }

    if (current == headp)
        ((CLASS *)(cla_find(((STUDENT *)(stu_find(stunum, head).ptr))->cla_num, head).ptr))->stu_hp = current->stu_p;
    else
        prior->stu_p = current->stu_p;
    free(current);               //链表结点的删除
    
    message_event(NULL, (void **)"删除成功");
    gtk_widget_destroy(GTK_WIDGET(data));

}

void grade_fill_event(GtkWidget *widget, gpointer *data)
{
 
    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *label;
    CLASS *p = head;
    
    STUDENT *q = NULL;
    CLASS *clap;
    STUDENT *stup;
    GRADE *subp;
    COUNT_GRA *temp, *grap, *grahd = NULL;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);   //设置窗口
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "学生课程成绩基本信息录入");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 学        号:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "请选择");
    
    while (p != NULL)               //遍历链表,将录入学生学号加入combo中
    {
        q = p->stu_hp;
        
        while (q != NULL)
        {
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), q->stu_num);
            q = q->stu_p;
        }
        
        p = p->cla_p;
    }
    
    gtk_widget_show(combo);
    gtk_box_pack_start(GTK_BOX(hbox), combo, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 课  程  名:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    combo2 = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo2), "请选择");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo2), "录入新课程");

    for (clap = head; clap != NULL; clap = clap->cla_p)
    {
        stup = clap->stu_hp;
       
        while (stup != NULL)
        {
            subp = stup->sub_hp;
            
            while (subp != NULL)
            {
                temp = grahd;
                
                while (temp != NULL)
                {
                    if (strcmp(temp->sub_name, subp->sub_name) == 0)
                        break;
                    temp = temp->gra_p;
                }
                
                if (temp == NULL)
                {
                    grap = (COUNT_GRA *)malloc(sizeof(COUNT_GRA));
                    strcpy(grap->sub_name, subp->sub_name);
                    grap->gra_p = grahd;
                    grahd = grap;
                }
                
                subp = subp->sub_p;
            }
            
            stup = stup->stu_p;
        }
    }                             //将已录入过的课程加入combo中
    
    grap = grahd;
    
    while (grap != NULL)
    {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo2), grap->sub_name);
        grap = grap->gra_p;
    }
    
    gtk_widget_show(combo2);
    gtk_box_pack_start(GTK_BOX(hbox), combo2, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    label = gtk_label_new(" 考试成绩:");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry1 = gtk_entry_new();
    gtk_widget_show(entry1);
    gtk_box_pack_start(GTK_BOX(hbox), entry1, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    label = gtk_label_new(" 补考成绩:");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry2 = gtk_entry_new();
    gtk_widget_show(entry2);
    gtk_box_pack_start(GTK_BOX(hbox), entry2, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 100); //设置按钮
    button = gtk_button_new_with_label("录    入");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(grade_fill), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void grade_fill(GtkWidget *widget, gpointer *data)
{
 
    char buf[30];              //缓冲区

    strcpy(buf, gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo)));
    STUDENT *find_student = (STUDENT *)(stu_find(buf, head).ptr);
    GRADE *subhp = find_student->sub_hp;
    GRADE *p = subhp;

    if (subhp == NULL)
    {
        find_student->sub_hp = (GRADE *)malloc(sizeof(GRADE));
        p = find_student->sub_hp;
    }
    else 
    {      
        while (p->sub_p != NULL) 
            p = p->sub_p;
        
        p->sub_p = (GRADE *)malloc(sizeof(GRADE));
        p = p->sub_p;
    }
    p->sub_p = NULL;                

    strcpy(p->stu_num, buf);
    strcpy(buf, gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo2)));
    
    if (strcmp(buf, "录入新课程") == 0) 
    {
        button0 = gtk_button_new();
        g_signal_connect(G_OBJECT(button0), "clicked", G_CALLBACK(sub_fill_event), p);
        gtk_button_clicked(GTK_BUTTON(button0));
        return;
    }  

    GRADE *subp = (GRADE *)(sub_find(buf, head).ptr);
    strcpy(p->sub_name, subp->sub_name);
    p->sub_sem = subp->sub_sem;
    p->sub_hour = subp->sub_hour;
    p->sub_score = subp->sub_score;
    find_student->learn_score += p->sub_score;    //链表信息初始化

    p->stu_grade = atoi(gtk_entry_get_text(GTK_ENTRY(entry1)));

    if (p->stu_grade < 60)
    {
        p->stu_grade_sec = atoi(gtk_entry_get_text(GTK_ENTRY(entry2)));
        
        if (p->stu_grade_sec < 0 || p->stu_grade_sec > 100)
            message_event(NULL, (void **)"请录入正确的补考成绩!");
        
        if (p->stu_grade_sec >= 60)
            find_student->get_score += p->sub_score;
    }
    else 
    {
        p->stu_grade_sec = -1;
        find_student->get_score += p->sub_score;
    }

    p->sub_p = NULL;
    subhp = find_student->sub_hp;
    p = subhp;
    
    while (p != NULL)
    {
        find_student->average += p->stu_grade * p->sub_score / find_student->learn_score;
        p = p->sub_p;
    }
    
    message_event(NULL, (void **)"录入成功");
    gtk_widget_destroy(GTK_WIDGET(data));

}

void sub_fill_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *label;

    diawindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);   
    gtk_window_set_default_size(GTK_WINDOW(diawindow), 200, 200);  
    gtk_window_set_title(GTK_WINDOW(diawindow), "请先录入新课程信息");
    gtk_window_set_position(GTK_WINDOW(diawindow), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);   
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 课程名    :");      //向窗口中加入所需构件
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry4 = gtk_entry_new();
    gtk_widget_show(entry4);
    gtk_box_pack_start(GTK_BOX(hbox), entry4, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 开课学期:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry1 = gtk_entry_new();
    gtk_widget_show(entry1);
    gtk_box_pack_start(GTK_BOX(hbox), entry1, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    label = gtk_label_new(" 学时数    :");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry2 = gtk_entry_new();
    gtk_widget_show(entry2);
    gtk_box_pack_start(GTK_BOX(hbox), entry2, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    label = gtk_label_new(" 学分数    :");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label,FALSE,FALSE, 0);
    entry3 = gtk_entry_new();
    gtk_widget_show(entry3);
    gtk_box_pack_start(GTK_BOX(hbox), entry3, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 100);
    button = gtk_button_new_with_label("录    入");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(sub_fill), data);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), diawindow);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(diawindow), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(diawindow);

}

void sub_fill(GtkWidget *widget, gpointer *data)
{
 
    GRADE *p = (GRADE *)data;            //从录入对话框中读取信息
    strcpy(p->sub_name, gtk_entry_get_text(GTK_ENTRY(entry4)));
    p->sub_sem = atoi(gtk_entry_get_text(GTK_ENTRY(entry1)));
    p->sub_hour = atoi(gtk_entry_get_text(GTK_ENTRY(entry2)));
    p->sub_score = atof(gtk_entry_get_text(GTK_ENTRY(entry3)));
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo2), p->sub_name);

    message_event(NULL, (void **)"录入新课程信息成功");
    gtk_widget_destroy(GTK_WIDGET(diawindow));

}

void sub_amend_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *vbox0;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *label;

    CLASS *p = head;                  //链表变量声明
    STUDENT *q = NULL;
    CLASS *clap;
    STUDENT *stup;
    GRADE *subp;
    COUNT_GRA *temp, *grap, *grahd = NULL;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "课程基本信息修改");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 课程名    :");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "请选择");

    for (clap = head; clap != NULL; clap = clap->cla_p)
    {
        stup = clap->stu_hp;
      
        while (stup != NULL)
        {
            subp = stup->sub_hp;
            
            while (subp != NULL)
            {
                temp = grahd;
                
                while (temp != NULL)
                {
                    if (strcmp(temp->sub_name, subp->sub_name) == 0)
                        break;
                    temp = temp->gra_p;
                }
                
                if (temp == NULL)
                {
                    grap = (COUNT_GRA *)malloc(sizeof(COUNT_GRA));
                    strcpy(grap->sub_name, subp->sub_name);
                    grap->gra_p = grahd;
                    grahd = grap;
                }
                
                subp = subp->sub_p;
            }
            
            stup = stup->stu_p;
        }
    }
    
    grap = grahd;
    
    while (grap != NULL)
    {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), grap->sub_name);
        grap = grap->gra_p;
    }

    gtk_widget_show(combo);
    gtk_box_pack_start(GTK_BOX(hbox), combo, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    label = gtk_label_new("请选择修改选项:");     //单项选择按钮
    vbox0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(vbox0), label, FALSE, FALSE, 0);
    button1 = gtk_radio_button_new_with_label(NULL, "课 程 名");
    gtk_widget_show(button1);
    g_signal_connect(G_OBJECT(button1), "pressed", G_CALLBACK(button_event), (gpointer *)1);
    gtk_box_pack_start(GTK_BOX(vbox0), button1, FALSE, FALSE, 0);
    button2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(button1)), "开课学期");
    gtk_widget_show(button2);
    g_signal_connect(G_OBJECT(button2), "pressed", G_CALLBACK(button_event), (gpointer *)2);
    gtk_box_pack_start(GTK_BOX(vbox0), button2, FALSE, FALSE, 0);
    button3 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(button2)), "学 时 数");
    gtk_widget_show(button3);
    g_signal_connect(G_OBJECT(button3), "pressed", G_CALLBACK(button_event), (gpointer *)3);
    gtk_box_pack_start(GTK_BOX(vbox0), button3, FALSE, FALSE, 0);
    button4 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(button2)), "学    分");
    gtk_widget_show(button4);
    g_signal_connect(G_OBJECT(button4), "pressed", G_CALLBACK(button_event), (gpointer *)4);
    gtk_box_pack_start(GTK_BOX(vbox0), button4, FALSE, FALSE, 0);
    gtk_widget_show(vbox0);
    gtk_box_pack_start(GTK_BOX(vbox), vbox0, FALSE, FALSE, 0);

    label = gtk_label_new(" 请输入新的信息:");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry3 = gtk_entry_new();
    gtk_widget_show(entry3);
    gtk_box_pack_start(GTK_BOX(hbox), entry3, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 140);
    button = gtk_button_new_with_label("修    改");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(sub_amend), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void sub_amend(GtkWidget *widget, gpointer *data)
{

    char buf[30];
    char subname[30];

    strcpy(subname, gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo))); //读取
    
    switch (choose) {
        case 1:
            strcpy(buf, gtk_entry_get_text(GTK_ENTRY(entry3)));
            
            if (sub_find(buf, head).flag == 1) 
            {
                message_event(NULL, (void **)"此课程信息已存在，请选择修改或删除该课程信息！\n");
                return;
            }
            
            sub_change(1, buf, subname, head);
            break;
        case 2:
            strcpy(buf, gtk_entry_get_text(GTK_ENTRY(entry3)));
            
            if (atoi(buf) > SEMMAX || atoi(buf) < 1) 
            {
                message_event(NULL, (void **)"输入的开课学期不正确,请输入符合要求的开课学期！\n");
                return;
            }
            
            sub_change(2, buf, subname, head);
            break;
        case 3:
            strcpy(buf, gtk_entry_get_text(GTK_ENTRY(entry3)));
            sub_change(3, buf, subname, head);
            break;
        case 4:
            strcpy(buf, gtk_entry_get_text(GTK_ENTRY(entry3)));
            sub_change(3, buf, subname, head);
            break;
    }
    
    message_event(NULL, (void **)"修改成功");
    gtk_widget_destroy(GTK_WIDGET(data));

}

void grade_amend_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;          //gtk变量声明
    GtkWidget *vbox;
    GtkWidget *vbox0;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *label;
    
    CLASS *p = head;
    STUDENT *q = NULL;
    CLASS *clap;
    STUDENT *stup;
    GRADE *subp;
    COUNT_GRA *temp, *grap, *grahd = NULL;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "学生成绩信息修改");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 学        号:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "请选择");

    while (p!=NULL)
    {
        q = p->stu_hp;
        
        while (q != NULL)
        {
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), q->stu_num);
            q = q->stu_p;
        }
        
        p = p->cla_p;
    }
    
    gtk_widget_show(combo);
    gtk_box_pack_start(GTK_BOX(hbox), combo, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 课  程  名:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    combo2 = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo2), "请选择");

    for (clap = head; clap != NULL; clap = clap->cla_p)
    {
        stup = clap->stu_hp;
        
        while (stup != NULL)
        {
            subp = stup->sub_hp;
            
            while (subp != NULL)
            {
                temp = grahd;
                
                while (temp != NULL)
                {
                    if (strcmp(temp->sub_name, subp->sub_name) == 0)
                        break;
                    temp = temp->gra_p;
                }
                
                if (temp == NULL)
                {
                    grap = (COUNT_GRA *)malloc(sizeof(COUNT_GRA));
                    strcpy(grap->sub_name, subp->sub_name);
                    grap->gra_p = grahd;
                    grahd = grap;
                }
                
                subp = subp->sub_p;
            }
            
            stup = stup->stu_p;
        }
    }                     //将所有已录入过的课程添加到combo中
    
    grap = grahd;
    
    while (grap != NULL)
    {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo2), grap->sub_name);
        grap = grap->gra_p;
    }
    
    gtk_widget_show(combo2);
    gtk_box_pack_start(GTK_BOX(hbox), combo2, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    label = gtk_label_new("请选择修改选项:");
    vbox0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(vbox0), label, FALSE, FALSE, 0);
    button1 = gtk_radio_button_new_with_label(NULL, "考试成绩");
    gtk_widget_show(button1);
    g_signal_connect(G_OBJECT(button1), "pressed", G_CALLBACK(button_event), (gpointer *)1);
    gtk_box_pack_start(GTK_BOX(vbox0),button1,FALSE,FALSE,0);
    button2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(button1)), "补考成绩");
    gtk_widget_show(button2);
    g_signal_connect(G_OBJECT(button2), "pressed", G_CALLBACK(button_event), (gpointer *)2);
    gtk_box_pack_start(GTK_BOX(vbox0), button2, FALSE, FALSE, 0);
    gtk_widget_show(vbox0);
    gtk_box_pack_start(GTK_BOX(vbox), vbox0, FALSE, FALSE, 0);

    label = gtk_label_new(" 请输入新的信息:");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry3 = gtk_entry_new();
    gtk_widget_show(entry3);
    gtk_box_pack_start(GTK_BOX(hbox), entry3, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 140);  //设置按钮
    button = gtk_button_new_with_label("修    改");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(grade_amend), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void grade_amend(GtkWidget *widget,gpointer *data)
{
 
    char buf[30];
    char subname[30];
    
    GRADE *p;
    
    strcpy(buf,gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo)));
    strcpy(subname,gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo2)));
    p = ((STUDENT *)stu_find(buf,head).ptr)->sub_hp;
    
    while (p != NULL)
    {
        if (strcmp(subname, p->sub_name) == 0) 
            break;
        p = p->sub_p;
    }

    if (p == NULL) 
    {
        message_event(NULL, (void **)"该学生无此课程成绩信息，请先为该生录入该课程成绩\n");
        return;
    }

    switch (choose) {
        case 1:
            p->stu_grade = atoi(gtk_entry_get_text(GTK_ENTRY(entry3)));
        case 2:
            if (p->stu_grade_sec == -1)
            {
                message_event(NULL, (void **)"该学生该科目不用补考!\n");
                return;          //判断是否有必要修改补考成绩
            }
            
            p->stu_grade_sec = atoi(gtk_entry_get_text(GTK_ENTRY(entry3)));
    }

    message_event(NULL, (void **)"修改成功");
    gtk_widget_destroy(GTK_WIDGET(data));

}

void grade_del_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;               //gtk变量声明
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *label;

    CLASS *p = head;                     //链表相关变量声明
    STUDENT *q = NULL;
    CLASS *clap;
    STUDENT *stup;
    GRADE *subp;
    COUNT_GRA *temp, *grap, *grahd = NULL;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 260, 120);
    gtk_window_set_title(GTK_WINDOW(dia_window), "学生课程成绩基本信息删除");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 50);
    label = gtk_label_new(" \t学      号:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "请选择");
    
    while (p != NULL)
    {
        q = p->stu_hp;
        
        while (q != NULL)
        {
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), q->stu_num);
            q = q->stu_p;
        }
        
        p = p->cla_p;
    }
    
    gtk_widget_show(combo);
    gtk_box_pack_start(GTK_BOX(hbox), combo, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 50);
    label = gtk_label_new(" \t课 程 名:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    combo2 = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo2), "请选择");

    for (clap = head; clap != NULL; clap = clap->cla_p)
    {
        stup = clap->stu_hp;
        
        while (stup != NULL)
        {
            subp = stup->sub_hp;
            
            while (subp != NULL)
            {
                temp = grahd;
                
                while (temp != NULL)
                {
                    if (strcmp(temp->sub_name, subp->sub_name)==0)
                        break;
                    temp = temp->gra_p;
                }
                
                if (temp == NULL)
                {
                    grap = (COUNT_GRA *)malloc(sizeof(COUNT_GRA));
                    strcpy(grap->sub_name, subp->sub_name);
                    grap->gra_p = grahd;
                    grahd = grap;
                }
                
                subp = subp->sub_p;
            }
            
            stup = stup->stu_p;
        }
    }
    
    grap = grahd;
    
    while (grap != NULL)
    {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo2), grap->sub_name);
        grap = grap->gra_p;
    }
    
    gtk_widget_show(combo2);
    gtk_box_pack_start(GTK_BOX(hbox), combo2, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 100);
    button = gtk_button_new_with_label("删    除");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(grade_del_warning_event), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void grade_del_warning_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *button;
    GtkWidget *hbox;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *dia_window;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 150, 80);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "警告!");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);
    gtk_window_set_transient_for(GTK_WINDOW(dia_window), GTK_WINDOW(data));
    gtk_window_set_destroy_with_parent(GTK_WINDOW(dia_window), TRUE);

    label = gtk_label_new("    警告：确认删除该学生该课程基本信息？");
    gtk_widget_show(label);          //警告提示
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 130);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("确    定");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button),  "clicked", G_CALLBACK(grade_del), data);
    gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show(vbox);
    
    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(dia_window);

}

void grade_del(GtkWidget *widget, gpointer *data)
{

    char stunum[20];
    char subname[30];

    GRADE *prior, *current, *headp;

    strcpy(stunum,gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo)));
    strcpy(subname,gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo2)));
    current = ((STUDENT *)(stu_find(stunum, head).ptr))->sub_hp;
    
    while (current != NULL)
    {
        if (strcmp(subname, current->sub_name) == 0) 
            break;
        current = current->sub_p;
    }
    
    if (current == NULL)
    {
        message_event(NULL, (void **)"该学生无此课程成绩信息，请先为该生录入该课程成绩\n");
        return;
    }
    else 
    {
        headp = ((STUDENT *)stu_find(stunum, head).ptr)->sub_hp;
        prior = headp;
        current = headp;
        
        while ((strcmp(subname,current->sub_name)!= 0) && current != NULL)
        {
            prior = current;
            current = current->sub_p;
        }
        
        if (current == headp)
        ((STUDENT *)stu_find(stunum, head).ptr)->sub_hp = current->sub_p;
        else
            prior->sub_p = current->sub_p;
        free(current);                  //链表结点删除
    }
    
    message_event(NULL, (void **)"删除成功");       
    gtk_widget_destroy(GTK_WIDGET(data));
}

void cla_refer_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *vbox0;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *label;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 180);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "班级信息查询");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);  //用单项选择按钮
    label = gtk_label_new("请选择查询方式:");          //选择查询方式
    vbox0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(vbox0), label, FALSE, FALSE, 0);
    button1 = gtk_radio_button_new_with_label(NULL, "以班级编号为条件查找");
    gtk_widget_show(button1);
    g_signal_connect(G_OBJECT(button1), "pressed", G_CALLBACK(label_button_event), (gpointer *)11);
    gtk_box_pack_start(GTK_BOX(vbox0), button1, FALSE, FALSE, 0);
    button2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(button1)), "以班导师为条件查找");
    gtk_widget_show(button2);
    g_signal_connect(G_OBJECT(button2), "pressed", G_CALLBACK(label_button_event), (gpointer *)12);
    gtk_box_pack_start(GTK_BOX(vbox0), button2, FALSE, FALSE, 0);
    gtk_widget_show(vbox0);
    gtk_box_pack_start(GTK_BOX(vbox), vbox0, FALSE, FALSE, 0);

    label0 = gtk_label_new("请输入班级编号");
    gtk_widget_show(label0);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label0, FALSE, FALSE, 0);
    entry3 = gtk_entry_new();
    gtk_widget_show(entry3);
    gtk_box_pack_start(GTK_BOX(hbox), entry3, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 160);
    button = gtk_button_new_with_label("查    询");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(cla_refer), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void cla_refer(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;      //对话框和treeview的初始化
    GtkWidget *scrolled;
    GtkWidget *tree_view;
    GtkListStore *store;
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;
    GtkTreeIter iter;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 300, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "查询结果");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(dia_window), "destroy", G_CALLBACK(destroy), dia_window);

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(dia_window), scrolled);
    gtk_widget_show(scrolled);
    store = gtk_list_store_new(4, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_widget_show(tree_view);
    gtk_container_add(GTK_CONTAINER(scrolled), tree_view);
    renderer = gtk_cell_renderer_text_new();
    g_object_set(G_OBJECT(renderer), "foreground", "black", NULL);
    column = gtk_tree_view_column_new_with_attributes("序    号", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("班级编号", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("班 导 师", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("联系电话", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    gtk_widget_show(dia_window);

    CLASS *clap;               //通过遍历链表查询满足条件的结点,并将其内容
    char option[20];           //加入treeview存储结构中
    int num = 0;

    strcpy(option, gtk_entry_get_text(GTK_ENTRY(entry3)));
    
    if (choose == 1)
    {
        if (cla_find(option, head).flag == 1)
        {
            num += 1;
            clap = (CLASS *)(cla_find(option, head).ptr);
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, 0, num, 1, clap->cla_num, 
                               2, clap->cla_teacher, 3, clap->cla_tel, -1);
        }
        else
            message_event(NULL, (void **)"对不起，未找到相关班级信息\n");
    }
    else
    {  
        clap = head;
        
        while (clap != NULL)
        {
            if (strcmp(option,clap->cla_teacher) == 0) 
            {
                num += 1;
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter, 0, num, 1, clap->cla_num, 
                                   2, clap->cla_teacher, 3, clap->cla_tel, -1);
            }
            clap = clap->cla_p;
        }
        
        if (num == 0)
            message_event(NULL, (void **)"对不起，未找到相关班级信息\n");
    }

}

void stu_refer1_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *label;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 80);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "学生信息查询");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    label = gtk_label_new("请输入学号");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry3 = gtk_entry_new();
    gtk_widget_show(entry3);
    gtk_box_pack_start(GTK_BOX(hbox), entry3, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 140);
    button = gtk_button_new_with_label("查    询");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(stu_refer1), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void stu_refer1(GtkWidget *widget, gpointer *data)
{
    
    GtkWidget *dia_window;
    GtkWidget *scrolled;
    GtkWidget *tree_view;
    GtkListStore *store;
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;
    GtkTreeIter iter;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 600, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "查询结果");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(dia_window), "destroy", G_CALLBACK(destroy), dia_window);

    scrolled = gtk_scrolled_window_new(NULL, NULL);  //带滚动条的对话框
    gtk_container_add(GTK_CONTAINER(dia_window), scrolled);
    gtk_widget_show(scrolled);
    store = gtk_list_store_new(8, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 
                               G_TYPE_STRING, G_TYPE_FLOAT, G_TYPE_FLOAT, G_TYPE_FLOAT);
    tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_widget_show(tree_view);
    gtk_container_add(GTK_CONTAINER(scrolled), tree_view);
    renderer = gtk_cell_renderer_text_new();
    g_object_set(G_OBJECT(renderer), "foreground", "black", NULL);
    column = gtk_tree_view_column_new_with_attributes("序号", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("所在班级", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("学    号", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("姓    名", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("性    别", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("已修课程学分", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("已获学分", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("加权平均分", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    gtk_widget_show(dia_window);

    CLASS *clap;
    STUDENT *stup;
    char option[20];
    char choose;
    int num = 0;

    strcpy(option, gtk_entry_get_text(GTK_ENTRY(entry3)));   //读取
    
    if (stu_find(option, head).flag == 1)
    {
        num += 1;
        stup = (STUDENT *)(stu_find(option, head).ptr);
        
        if (stup->stu_sex == 'm')
        {  
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, 0, num, 1, stup->cla_num, 2, stup->stu_num, 
                               3, stup->stu_name, 4, "男", 5, stup->learn_score, 6, stup->get_score, 7, stup->average, -1);
        }
        else
        {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, 0, num, 1, stup->cla_num, 2, stup->stu_num, 
                               3, stup->stu_name, 4, "女", 5, stup->learn_score, 6, stup->get_score, 7, stup->average, -1);
        }
    }
    else
        message_event(NULL, (void **)"对不起，未找到相关学生信息\n");

}

void stu_refer2_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *label;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 80);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "学生信息查询");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 已修课程学分:");     //两个entry输入范围
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry1 = gtk_entry_new();
    gtk_widget_show(entry1);
    gtk_box_pack_start(GTK_BOX(hbox), entry1, FALSE, FALSE, 0);
    label = gtk_label_new("-");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry2 = gtk_entry_new();
    gtk_widget_show(entry2);
    gtk_box_pack_start(GTK_BOX(hbox), entry2, FALSE, FALSE, 5);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 所 获 学 分    :");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry3 = gtk_entry_new();
    gtk_widget_show(entry3);
    gtk_box_pack_start(GTK_BOX(hbox), entry3, FALSE, FALSE, 0);
    label = gtk_label_new("-");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry4 = gtk_entry_new();
    gtk_widget_show(entry4);
    gtk_box_pack_start(GTK_BOX(hbox), entry4, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 加权平均分   :");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry5 = gtk_entry_new();
    gtk_widget_show(entry5);
    gtk_box_pack_start(GTK_BOX(hbox), entry5, FALSE, FALSE, 0);
    label = gtk_label_new("-");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry6 = gtk_entry_new();
    gtk_widget_show(entry6);
    gtk_box_pack_start(GTK_BOX(hbox), entry6, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 350);
    button = gtk_button_new_with_label("查    询");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(stu_refer2), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void stu_refer2(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *scrolled;
    GtkWidget *tree_view;
    GtkListStore *store;
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;
    GtkTreeIter iter;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 600, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "查询结果");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(dia_window), "destroy", G_CALLBACK(destroy), dia_window);

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(dia_window), scrolled);
    gtk_widget_show(scrolled);
    store = gtk_list_store_new(8, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, 
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_FLOAT, G_TYPE_FLOAT, G_TYPE_FLOAT);
    tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_widget_show(tree_view);
    gtk_container_add(GTK_CONTAINER(scrolled), tree_view);
    renderer = gtk_cell_renderer_text_new();
    g_object_set(G_OBJECT(renderer), "foreground", "black", NULL);
    column = gtk_tree_view_column_new_with_attributes("序号", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("所在班级", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("学    号", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("姓    名", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),column);
    column = gtk_tree_view_column_new_with_attributes("性    别", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("已修课程学分", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("已获学分", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("加权平均分", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    gtk_widget_show(dia_window);

    CLASS *clap;
    STUDENT *stup;
    char choose;
    int num = 0;
    float ler_max = STUDYSCOREMAX, ler_min = 0;
    float get_max = STUDYSCOREMAX, get_min = 0;
    float avr_max = 100, avr_min = 0;

    ler_min = atof(gtk_entry_get_text(GTK_ENTRY(entry1))); //从所有的entry
    ler_max = atof(gtk_entry_get_text(GTK_ENTRY(entry2))); //中读取所要查询
    get_min = atof(gtk_entry_get_text(GTK_ENTRY(entry3))); //的范围信息.并
    get_max = atof(gtk_entry_get_text(GTK_ENTRY(entry4))); //将string转换为
    avr_min = atof(gtk_entry_get_text(GTK_ENTRY(entry5))); //float进行存储
    avr_max = atof(gtk_entry_get_text(GTK_ENTRY(entry6))); //与比较.
    clap = head;

    while (clap != NULL)
    {
        stup = clap->stu_hp;
        
        while (stup != NULL)
        {
            if (((stup->learn_score <= ler_max)&&(stup->learn_score >= ler_min)
                &&(stup->get_score <= get_max)&&(stup->get_score >= ler_min)&&
                (stup->average <= avr_max)&&(stup->average >= avr_min)) == 1)
            {
                num += 1;
                
                if (stup->stu_sex == 'm')
                {  
                    gtk_list_store_append(store, &iter);
                    gtk_list_store_set(store, &iter, 0, num, 1, stup->cla_num, 2, stup->stu_num, 3,
                                       stup->stu_name, 4, "男", 5, stup->learn_score, 6, stup->get_score, 7, stup->average, -1);
                }
                else
                {
                    gtk_list_store_append(store, &iter);
                    gtk_list_store_set(store, &iter, 0, num, 1, stup->cla_num, 2, stup->stu_num, 3,
                                       stup->stu_name, 4, "女", 5, stup->learn_score, 6, stup->get_score, 7, stup->average, -1);
                }
            }
            
            stup = stup->stu_p;
        }
        
        clap = clap->cla_p;
    }
    
    if (num == 0)
        message_event(NULL, (void **)"对不起，未找到相关学生信息\n");

}

void sub_refer1_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *label;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 80);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "学生课程成绩信息查询");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    label = gtk_label_new("请输入学号    ");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 5);
    entry1 = gtk_entry_new();
    gtk_widget_show(entry1);
    gtk_box_pack_start(GTK_BOX(hbox), entry1, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    label = gtk_label_new("请输入课程名");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 5);
    entry2 = gtk_entry_new();
    gtk_widget_show(entry2);
    gtk_box_pack_start(GTK_BOX(hbox), entry2, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 140);
    button = gtk_button_new_with_label("查    询");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(sub_refer1), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void sub_refer1(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *scrolled;
    GtkWidget *tree_view;
    GtkListStore *store;
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;
    GtkTreeIter iter;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 600, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "查询结果");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(dia_window), "destroy", G_CALLBACK(destroy), dia_window);

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(dia_window), scrolled);
    gtk_widget_show(scrolled);
    store = gtk_list_store_new(8, G_TYPE_UINT, G_TYPE_STRING, 
                               G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_FLOAT, G_TYPE_UINT, G_TYPE_UINT);
    tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_widget_show(tree_view);
    gtk_container_add(GTK_CONTAINER(scrolled), tree_view);
    renderer = gtk_cell_renderer_text_new();
    g_object_set(G_OBJECT(renderer), "foreground", "black", NULL);
    column = gtk_tree_view_column_new_with_attributes("序    号", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("学    号", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("课 程 名", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("开课学期", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("学 时 数", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("学    分", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("考试成绩", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("补考成绩", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    gtk_widget_show(dia_window);

    CLASS *clap;
    STUDENT *stup;
    GRADE *subp;
    char option[20];
    int num = 0;

    strcpy(option,gtk_entry_get_text(GTK_ENTRY(entry1)));
    
    if (stu_find(option, head).flag == 1)
    {
        subp = ((STUDENT *)(stu_find(option, head).ptr))->sub_hp;
        strcpy(option, gtk_entry_get_text(GTK_ENTRY(entry2)));
        
        while (subp != NULL)
        {
            if (strcmp(option, subp->sub_name) == 0)
            {
                num += 1;
                if (subp->stu_grade_sec == -1)
                {
                    gtk_list_store_append(store, &iter);
                    gtk_list_store_set(store, &iter, 0, num, 1, subp->stu_num, 2, subp->sub_name,
                                       3, subp->sub_sem, 4, subp->sub_hour, 5, subp->sub_score, 6, subp->stu_grade, 7, 0, -1);
                }
                else
                {
                    gtk_list_store_append(store, &iter);
                    gtk_list_store_set(store, &iter, 0, num, 1, subp->stu_num, 2, subp->sub_name,
                                       3, subp->sub_sem, 4, subp->sub_hour, 5, subp->sub_score, 6, subp->stu_grade, 7, subp->stu_grade_sec, -1);
                }
            }
            
            subp = subp->sub_p;
        }
        
        if (num == 0)
            message_event(NULL, (void **)"对不起，未找到相关学生课程基本信息\n");
    }
    else
        message_event(NULL, (void **)"对不起，未找到相关学生信息\n");

}

void sub_refer2_event(GtkWidget *widget, gpointer *data)
{
 
    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *label;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 80);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "学生课程成绩信息查询");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new("开课学期:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 5);
    entry0 = gtk_entry_new();
    gtk_widget_show(entry0);
    gtk_box_pack_start(GTK_BOX(hbox), entry0, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    label = gtk_label_new("考试成绩:");           //录入范围
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 5);
    entry1 = gtk_entry_new();
    gtk_widget_show(entry1);
    gtk_box_pack_start(GTK_BOX(hbox), entry1, FALSE, FALSE, 0);
    label = gtk_label_new("-");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry2 = gtk_entry_new();
    gtk_widget_show(entry2);
    gtk_box_pack_start(GTK_BOX(hbox), entry2, FALSE, FALSE, 5);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 350);
    button = gtk_button_new_with_label("查    询");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(sub_refer2), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    
    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void sub_refer2(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *scrolled;
    GtkWidget *tree_view;
    GtkListStore *store;
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;
    GtkTreeIter iter;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 600, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "查询结果");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(dia_window), "destroy", G_CALLBACK(destroy), dia_window);

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(dia_window), scrolled);
    gtk_widget_show(scrolled);
    store = gtk_list_store_new(8, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, 
                               G_TYPE_UINT, G_TYPE_UINT, G_TYPE_FLOAT, G_TYPE_UINT, G_TYPE_UINT);
    tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_widget_show(tree_view);
    gtk_container_add(GTK_CONTAINER(scrolled), tree_view);
    renderer = gtk_cell_renderer_text_new();
    g_object_set(G_OBJECT(renderer), "foreground", "black", NULL);
    column = gtk_tree_view_column_new_with_attributes("序    号", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("学    号", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("课 程 名", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("开课学期", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("学 时 数", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("学    分", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("考试成绩", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("补考成绩", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    gtk_widget_show(dia_window);

    CLASS *clap;
    STUDENT *stup;
    GRADE *subp;
    int num = 0;
    int sem = 1;
    int grade_max = 100, grade_min = 0;

    sem = atoi(gtk_entry_get_text(GTK_ENTRY(entry0)));
    grade_min = atoi(gtk_entry_get_text(GTK_ENTRY(entry1)));
    grade_max = atoi(gtk_entry_get_text(GTK_ENTRY(entry2)));
    clap = head;

    while (clap != NULL)
    {
        stup = clap->stu_hp;
        
        while (stup != NULL)
        {
            subp = stup->sub_hp;
            
            while (subp != NULL)
            {
                if (((subp->sub_sem == sem) && (subp->stu_grade <= grade_max) 
                     && (subp->stu_grade >= grade_min)) == 1)
                {
                    num += 1;
                    
                    if (subp->stu_grade_sec == -1)
                    {
                        gtk_list_store_append(store, &iter);
                        gtk_list_store_set(store, &iter, 0, num, 1, subp->stu_num, 2, subp->sub_name,
                                           3, subp->sub_sem, 4, subp->sub_hour, 5, subp->sub_score, 6, subp->stu_grade, 7, 0, -1);
                    }
                    else
                    {
                        gtk_list_store_append(store, &iter);
                        gtk_list_store_set(store, &iter, 0, num, 1, subp->stu_num, 2, subp->sub_name, 3, subp->sub_sem, 
                                           4, subp->sub_hour, 5, subp->sub_score, 6, subp->stu_grade, 7, subp->stu_grade_sec, -1);
                    }            //多级嵌套循环
                }
                
                subp = subp->sub_p;
            }
            
            stup = stup->stu_p;
        }
        
        clap = clap->cla_p;
    }
    
    if (num == 0)
        message_event(NULL, (void **)"对不起，未找到相关学生课程信息");

}

void count_total(GtkWidget *widget, gpointer *data)
{
    
    GtkWidget *dia_window;
    GtkWidget *scrolled;
    GtkWidget *tree_view;
    GtkListStore *store;
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;
    GtkTreeIter iter;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 600, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "统计结果");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(dia_window), "destroy", G_CALLBACK(destroy), dia_window);

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(dia_window), scrolled);
    gtk_widget_show(scrolled);
    store = gtk_list_store_new(6, G_TYPE_STRING, G_TYPE_UINT, 
                               G_TYPE_UINT, G_TYPE_UINT, G_TYPE_FLOAT, G_TYPE_FLOAT);
    tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_widget_show(tree_view);
    gtk_container_add(GTK_CONTAINER(scrolled), tree_view);
    renderer = gtk_cell_renderer_text_new();
    g_object_set(G_OBJECT(renderer), "foreground", "black", NULL);
    column = gtk_tree_view_column_new_with_attributes("班级", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("男生人数", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("女生人数", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("不及格人数", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("不及格比例", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("平均加权平均分", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    
    gtk_widget_show(dia_window);     //统计结果显示页面的搭建

    CLASS *clap;
    STUDENT *stup;
    GRADE *subp;
    COUNT_TOT *totp, *tothd = NULL;
    COUNT_TOT *prior, *after, *cur, *temp;

    int stunum;
    float avr_tot;

    for (clap = head; clap != NULL; clap = clap->cla_p)
    {
        totp = (COUNT_TOT *)malloc(sizeof(COUNT_TOT));
        strcpy(totp->cla_num, clap->cla_num);
        totp->boy_num = 0;
        totp->girl_num = 0;
        totp->fail_num = 0;
        totp->tot_p = NULL;
        stunum = 0;             //遍历链表将所需信息转存到另一结构链表中
        avr_tot = 0;
        stup = clap->stu_hp;
        
        while (stup != NULL)
        {
            subp = stup->sub_hp;
            
            while (subp != NULL)
            {
                if (subp->stu_grade_sec != -1)
                {
                    totp->fail_num += 1;
                    break;
                }
                
                subp = subp->sub_p;
            }
            
            stunum += 1;
            
            if (stup->stu_sex == 'm')
                totp->boy_num += 1;
            else 
                totp->girl_num += 1;
            
            avr_tot += stup->average;
            stup = stup->stu_p;
        }
        
        totp->fail_rate = 1.0 * totp->fail_num / stunum;
        totp->avr_average = avr_tot / (stunum + 1);
        totp->tot_p = tothd;
        tothd = totp;
    }                               
    
    prior = tothd;
    temp = (COUNT_TOT *)malloc(sizeof(COUNT_TOT));
    
    while (prior->tot_p != NULL)          //链表的排序
    {
        cur = prior;
        after = prior->tot_p;
        
        while (after != NULL)
        {
            if (cur->avr_average < after->avr_average)
                cur = after;
            after = after->tot_p;
        }
        
        if (cur != prior)
        {
            *temp = *prior;
            *prior = *cur;
            prior->tot_p = temp->tot_p;
            temp->tot_p = cur->tot_p;
            *cur = *temp;
        }
        
        prior = prior->tot_p;
    }
    
    free(temp);
    
    for (totp = tothd; totp != NULL; totp = totp->tot_p)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, totp->cla_num, 1, totp->boy_num, 
                           2, totp->girl_num, 3, totp->fail_num, 4, totp->fail_rate*100, 5, totp->avr_average,-1);
    }                            //显示结果

}

void count_semester_event(GtkWidget *widget, gpointer *data)
{
    
    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *label;
    
    CLASS *p = head;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 100);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "按学生统计");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 班级编号:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "请选择");
    
    while (p != NULL)
    {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), p->cla_num);
        p = p->cla_p;
    }
    
    gtk_widget_show(combo);
    gtk_box_pack_start(GTK_BOX(hbox), combo, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    label = gtk_label_new(" 开课学期:");
    gtk_widget_show(label);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    entry0 = gtk_entry_new();
    gtk_widget_show(entry0);
    gtk_box_pack_start(GTK_BOX(hbox), entry0, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 100);
    button = gtk_button_new_with_label("查看结果");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(count_semester), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);

}

void count_semester(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *scrolled;
    GtkWidget *tree_view;
    GtkListStore *store;
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;
    GtkTreeIter iter;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 600, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "统计结果");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(dia_window), "destroy", G_CALLBACK(destroy), dia_window);

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(dia_window), scrolled);
    gtk_widget_show(scrolled);
    store = gtk_list_store_new(8, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, 
                               G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_FLOAT);
    tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_widget_show(tree_view);
    gtk_container_add(GTK_CONTAINER(scrolled), tree_view);
    renderer = gtk_cell_renderer_text_new();
    g_object_set(G_OBJECT(renderer), "foreground", "black", NULL);
    column = gtk_tree_view_column_new_with_attributes("名次", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("姓名", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("课程1", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("课程2", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("课程3", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("课程4", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("课程5", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("平均分", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    gtk_widget_show(dia_window);

    STUDENT *stup,*stuhp;
    GRADE *subp;
    COUNT_SEM *semp,*semhd = NULL;
    COUNT_SEM *prior, *after, *cur, *temp;
    COUNT_LES *lesp;

    char clanum[10];
    int sem;
    int rank = 0;
    int grade[5];
    int i;
    
    for (i = 1; i < 5; i++)
        grade[i]=0;
    strcpy(clanum, gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo)));
    stuhp = ((CLASS *)(cla_find(clanum, head).ptr))->stu_hp;
    sem = atoi(gtk_entry_get_text(GTK_ENTRY(entry0)));
    
    for (stup = stuhp; stup != NULL; stup = stup->stu_p)   //构建新链表
    {
        semp = (COUNT_SEM *)malloc(sizeof(COUNT_SEM));
        strcpy(semp->stu_name, stup->stu_name);
        semp->sem_score = 0;
        semp->sem_average = 0;
        semp->les_hp = NULL;
        semp->sem_p = NULL;
        subp = stup->sub_hp;
        
        while (subp != NULL)
        {
            if (subp->sub_sem == sem)
            {
                lesp = (COUNT_LES *)malloc(sizeof(COUNT_LES));
                strcpy(lesp->les_name, subp->sub_name);
                lesp->les_grade = subp->stu_grade;
                lesp->les_score = subp->sub_score;
                lesp->les_p = NULL;
                semp->sem_score += subp->sub_score;
                lesp->les_p = semp->les_hp;
                semp->les_hp = lesp;
            }
            
            subp = subp->sub_p;
        }
        
        semp->sem_p = semhd;
        semhd = semp;
    }
    
    for (semp = semhd; semp != NULL; semp = semp->sem_p) 
    {
        lesp = semp->les_hp;
        
        while (lesp != NULL)
        {
            semp->sem_average += lesp->les_grade * lesp->les_score / semp->sem_score;
            lesp = lesp->les_p;
        }
    }
    
    prior = semhd;
    temp = (COUNT_SEM *)malloc(sizeof(COUNT_SEM));
    
    while (prior->sem_p != NULL)             //链表排序
    {
        cur = prior;
        after = prior->sem_p;
        while (after != NULL)
        {
            if (cur->sem_average < after->sem_average)
                cur = after;
            after = after->sem_p;
        }
        if (cur != prior)
        {
            *temp = *prior;
            *prior = *cur;
            prior->sem_p = temp->sem_p;
            temp->sem_p = cur->sem_p;
            *cur = *temp;
        }
        prior = prior->sem_p;
    }
    
    free(temp);
    lesp = semhd->les_hp;
    
    for (semp = semhd; semp != NULL; semp = semp->sem_p)
    {
        rank += 1;
        for (lesp = semp->les_hp, i=0; i<5 && lesp != NULL; i++, lesp=lesp->les_p)
            grade[i] = lesp->les_grade;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, rank, 1, semp->stu_name, 2, grade[0], 
                           3, grade[1], 4, grade[2], 5, grade[3], 6, grade[4], 7, semp->sem_average,-1);
    }

}

void count_grade(GtkWidget *widget, gpointer *data)
{
 
    GtkWidget *dia_window;
    GtkWidget *scrolled;
    GtkWidget *tree_view;
    GtkListStore *store;
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;
    GtkTreeIter iter;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 600, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "统计结果");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(dia_window), "destroy", G_CALLBACK(destroy), dia_window);

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(dia_window), scrolled);
    gtk_widget_show(scrolled);
    store = gtk_list_store_new(7, G_TYPE_STRING, G_TYPE_UINT, 
                               G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_FLOAT, G_TYPE_FLOAT);
    tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_widget_show(tree_view);
    gtk_container_add(GTK_CONTAINER(scrolled), tree_view);
    renderer = gtk_cell_renderer_text_new();
    g_object_set(G_OBJECT(renderer), "foreground", "black", NULL);
    column = gtk_tree_view_column_new_with_attributes("课程", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("90-100", renderer,  "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("80-89", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("60-79", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("0-59", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("平均分", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("及格率", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    gtk_widget_show(dia_window);    //统计结果显示页面的搭建

    CLASS *clap;
    STUDENT *stup;
    GRADE *subp;
    COUNT_GRA *grap, *grahd = NULL;
    COUNT_GRA *prior, *after, *cur, *temp;

    for (clap = head; clap != NULL; clap = clap->cla_p)
    {
        stup = clap->stu_hp;
        
        while (stup != NULL)
        {
            subp = stup->sub_hp;
            
            while (subp != NULL)
            {
                find:temp = grahd;
                
                while (temp != NULL)
                {
                    if (strcmp(temp->sub_name, subp->sub_name)==0)
                    {
                        temp->stunum += 1;
                        temp->grade_tot += subp->stu_grade;
                        
                        if ((subp->stu_grade <= 100) && (subp->stu_grade >= 90))
                            temp->num_90_100 += 1;
                        else if ((subp->stu_grade >= 80) && (subp->stu_grade < 90))
                            temp->num_80_90 +=1;
                        else if ((subp->stu_grade >= 60) && (subp->stu_grade < 80))
                            temp->num_60_80 +=1;
                        else
                        {
                            temp->num_0_60 +=1;
                            temp->fail_num +=1;
                        }
                        
                        break;
                    }
                    
                    temp = temp-> gra_p;
                }
                
                if (temp == NULL)
                {
                    grap = (COUNT_GRA *)malloc(sizeof(COUNT_GRA));
                    strcpy(grap->sub_name, subp->sub_name);
                    grap->num_90_100 = 0;
                    grap->num_80_90 = 0;
                    grap->num_60_80 = 0;
                    grap->num_0_60 = 0;
                    grap->stunum = 0;
                    grap->fail_num = 0;
                    grap->grade_tot = 0;
                    grap->gra_p = grahd;
                    grahd = grap;
                    goto find;
                }
                
                subp = subp->sub_p;
            }
            
            stup = stup->stu_p;
        }
    }                             //为了下面的操作方便,建立新链表
    
    grap = grahd;
    
    while (grap != NULL)
    {
        grap->sub_average = grap->grade_tot / grap->stunum;
        grap->qualify_rate = 1 - 1.0 * grap->fail_num / grap->stunum;
        grap = grap->gra_p;
    }
    
    prior = grahd;
    temp = (COUNT_GRA *)malloc(sizeof(COUNT_GRA));
    
    while (prior->gra_p != NULL)
    {
        cur = prior;
        after = prior->gra_p;
        
        while (after != NULL)
        {
            if (cur->qualify_rate < after->qualify_rate)
                cur = after;
            
            after = after->gra_p;
        }
        
        if (cur != prior)
        {
            *temp = *prior;
            *prior = *cur;
            prior->gra_p = temp->gra_p;
            temp->gra_p = cur->gra_p;
            *cur = *temp;
        }
        
        prior = prior->gra_p;
    }
    
    free(temp);
    
    for (grap = grahd; grap != NULL; grap = grap->gra_p)
    {    
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, grap->sub_name, 1, grap->num_90_100, 
                           2, grap->num_80_90, 3, grap->num_60_80, 4, grap->num_0_60, 5, grap->sub_average, 6, grap->qualify_rate*100, -1);
    }

}

void count_subject(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *scrolled;
    GtkWidget *tree_view;
    GtkListStore *store;
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;
    GtkTreeIter iter;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 600, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "统计结果");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(dia_window), "destroy", G_CALLBACK(destroy), dia_window);

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(dia_window), scrolled);
    gtk_widget_show(scrolled);
    store = gtk_list_store_new(5, G_TYPE_UINT,G_TYPE_UINT, G_TYPE_UINT, G_TYPE_FLOAT, G_TYPE_UINT);
    tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_widget_show(tree_view);
    gtk_container_add(GTK_CONTAINER(scrolled), tree_view);
    renderer = gtk_cell_renderer_text_new();
    g_object_set(G_OBJECT(renderer), "foreground", "black", NULL);
    column = gtk_tree_view_column_new_with_attributes("学期", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("开课门数", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("总学时数", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("总学分数", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("不及格人数", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    gtk_widget_show(dia_window);

    CLASS *clap;
    STUDENT *stup;
    GRADE *subp;
    COUNT_LES *lesp, *temp, *leshd = NULL;
    COUNT_SUB *csubp, *csubhd = NULL;

    int i;

    for (i=1; i <= SEMMAX; i++)
    {
        leshd = NULL;
        
        if (csubhd == NULL)
        {
            csubhd = (COUNT_SUB *)malloc(sizeof(COUNT_SUB));
            csubp = csubhd;
        }
        else
        {    
            csubp->sub_p = (COUNT_SUB *)malloc(sizeof(COUNT_SUB));
            csubp = csubp->sub_p;
        }
        
        csubp->sub_num = 0;
        csubp->sub_score = 0;
        csubp->sub_hour = 0;
        csubp->fail_num = 0;
        csubp->sub_p = NULL;
        
        for (clap = head; clap != NULL; clap = clap->cla_p)
        {
            stup = clap->stu_hp;
            while (stup != NULL)
            {
                subp = stup->sub_hp;
                
                while (subp != NULL)
                {
                    if (subp->sub_sem == i)
                    {
                        temp = leshd;
                        
                        while (temp != NULL)
                        {
                            if (strcmp(subp->sub_name,temp->les_name)==0)
                                break;
                            temp = temp->les_p;
                        }
                        
                        if (temp == NULL)
                        {
                            lesp = (COUNT_LES *)malloc(sizeof(COUNT_LES));
                            strcpy(lesp->les_name, subp->sub_name);
                            lesp->les_p = leshd;
                            leshd = lesp;
                            csubp->sub_num += 1;
                            csubp->sub_hour += subp->sub_hour;
                            csubp->sub_score += subp->sub_score;
                        }
                        
                        if (subp->stu_grade_sec != -1)
                            csubp->fail_num += 1;
                    }
                    
                    subp = subp->sub_p;
                }
                
                stup = stup->stu_p;
            }
        }
    }
    
    for (i=1, csubp=csubhd; i <= SEMMAX; i++, csubp = csubp->sub_p)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, i, 1, csubp->sub_num, 
                           2, csubp->sub_hour, 3, csubp->sub_score, 4, csubp->fail_num, -1);
    }                        //遍历新的链表,显示统计结果

}

void count_class_event(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button;
    GtkWidget *label;
    CLASS *p = head;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 200, 80);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "按班级和学期统计");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    label = gtk_label_new(" 班级编号:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "请选择");
    
    while (p != NULL)
    {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), p->cla_num);
        p = p->cla_p;
    }
    
    gtk_widget_show(combo);
    gtk_box_pack_start(GTK_BOX(hbox), combo, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 100);
    button = gtk_button_new_with_label("查看结果");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(count_class), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    button = gtk_button_new_with_label("取    消");
    gtk_widget_show(button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy), dia_window);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(dia_window), vbox);
    gtk_widget_show(vbox);
    gtk_widget_show(dia_window);         //显示界面

}

void count_class(GtkWidget *widget, gpointer *data)
{

    GtkWidget *dia_window;
    GtkWidget *scrolled;
    GtkWidget *tree_view;
    GtkListStore *store;
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;
    GtkTreeIter iter;

    dia_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dia_window), 600, 200);  
    gtk_window_set_title(GTK_WINDOW(dia_window), "统计结果");
    gtk_window_set_position(GTK_WINDOW(dia_window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(dia_window), "destroy", G_CALLBACK(destroy), dia_window);

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(dia_window), scrolled);
    gtk_widget_show(scrolled);
    store = gtk_list_store_new(4, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_FLOAT, G_TYPE_FLOAT);
    tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_widget_show(tree_view);
    gtk_container_add(GTK_CONTAINER(scrolled), tree_view);
    renderer = gtk_cell_renderer_text_new();
    g_object_set(G_OBJECT(renderer), "foreground", "black",NULL);
    column = gtk_tree_view_column_new_with_attributes("学期", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("不及格人次", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("不及格比例", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    column = gtk_tree_view_column_new_with_attributes("加权平均分", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    gtk_widget_show(dia_window);

    STUDENT *stup,*stuhp;
    GRADE *subp;
    COUNT_SEM *semp,*semhd = NULL;
    COUNT_LES *lesp;
    COUNT_CLA *cclap, *cclahd = NULL;

    char clanum[10];
    int sem;
    int stunum = 0;
    float sem_avr_tot = 0;

    strcpy(clanum, gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo)));
    stuhp = ((CLASS *)(cla_find(clanum, head).ptr))->stu_hp;

    for (sem = 1; sem <= SEMMAX; sem++)
    {
        if (cclahd == NULL)
        {
            cclahd = (COUNT_CLA *)malloc(sizeof(COUNT_CLA));
            cclap = cclahd;
        }
        else
        {    
            cclap->cla_p = (COUNT_CLA *)malloc(sizeof(COUNT_CLA));
            cclap = cclap->cla_p;
        }
        
        cclap->fail_num = 0;
        cclap->fail_rate = 0;
        cclap->avr_sem_average = 0;
        cclap->cla_p = NULL;
        
        for (stup = stuhp; stup != NULL; stup = stup->stu_p)
        {
            stunum += 1;
            semp = (COUNT_SEM *)malloc(sizeof(COUNT_SEM));
            strcpy(semp->stu_name, stup->stu_name);
            semp->sem_score = 0;
            semp->sem_average = 0;
            semp->les_hp = NULL;
            semp->sem_p = NULL;
            subp = stup->sub_hp;
            
            while (subp != NULL)
            {
                if (subp->sub_sem == sem)
                {
                    lesp = (COUNT_LES *)malloc(sizeof(COUNT_LES));
                    strcpy(lesp->les_name, subp->sub_name);
                    lesp->les_grade = subp->stu_grade;
                    lesp->les_score = subp->sub_score;
                    semp->sem_score += subp->sub_score;
                    lesp->les_p = semp->les_hp;
                    semp->les_hp = lesp;
                    if (subp->stu_grade_sec != -1)
                        cclap->fail_num += 1;
                }
                subp = subp->sub_p;
            }
            
            semp->sem_p = semhd;
            semhd = semp;
        }
        
        for (semp = semhd; semp != NULL; semp = semp->sem_p) 
        {
            lesp = semp->les_hp;
            
            while (lesp != NULL)
            {
                semp->sem_average += lesp->les_grade * lesp->les_score / semp->sem_score;
                lesp = lesp->les_p;
            }
            
            sem_avr_tot += semp->sem_average;
        }
        
        cclap->fail_rate = 1.0 * cclap->fail_num / stunum;
        cclap->avr_sem_average = sem_avr_tot / stunum;
        sem_avr_tot = 0;
        stunum = 0;
        semhd = NULL;
    }
    
    for (sem = 1, cclap = cclahd; sem <= SEMMAX; sem++, cclap = cclap->cla_p)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, sem, 
                           1, cclap->fail_num, 2, cclap->fail_rate*100, 3, cclap->avr_sem_average, -1);
    }

}

void load_event(GtkWidget *widget,gpointer *data)
{

    CLASS *hd = NULL, *cla_node;
    STUDENT *stu_node;
    GRADE *sub_node;

    FILE *pfile;                     //文件读写指针声明

    int find;
    int res = 0;                     //用以标记各文件的打开情况
    
    if ((pfile=fopen(class_info_filename, "rb")) == NULL)
    {
        message_event(NULL, (void **)"班级信息数据文件打开失败！\n");
        return;
    }
    
    while(!feof(pfile))
    {
        cla_node = (CLASS *)malloc(sizeof(CLASS));
        fread(cla_node, sizeof(CLASS), 1, pfile);
        cla_node->stu_hp = NULL;
        cla_node->cla_p = hd;
        hd = cla_node;
    }
    
    fclose(pfile);
    
    if (hd == NULL)
    {
        message_event(NULL, (void **)"班级信息文件加载失败！\n");
        return;
    }
    
    res += 1;
    *hp = hd->cla_p;

    if ((pfile=fopen(student_info_filename, "rb"))==NULL)
    {
        message_event(NULL, (void **)"学生基本信息数据文件打开失败！\n");
        return;
    }
    
    res +=2;
    
    while (!feof(pfile))
    {
        stu_node = (STUDENT *)malloc(sizeof(STUDENT));
        fread(stu_node, sizeof(STUDENT), 1, pfile);
        stu_node->sub_hp = NULL;
        cla_node = hd;
        while (cla_node != NULL && strcmp(cla_node->cla_num, stu_node->cla_num) != 0)
            cla_node = cla_node->cla_p;
        
        if (cla_node != NULL)
        {
            stu_node->stu_p = cla_node->stu_hp;
            cla_node->stu_hp = stu_node;
        }
        else
            free(stu_node);
    }
    
    fclose(pfile);

    if ((pfile=fopen(grade_info_filename, "rb"))==NULL)
    {
        message_event(NULL, (void **)"学生课程成绩基本信息数据文件打开失败！\n");
        return;
    }
    
    res += 4;
    
    while (!feof(pfile))
    {
        sub_node = (GRADE *)malloc(sizeof(GRADE));
        fread(sub_node, sizeof(GRADE), 1, pfile);
        cla_node = hd;
        find = 0;
        
        while (cla_node !=NULL && find == 0)
        {
            stu_node = cla_node->stu_hp;
            
            while (stu_node !=NULL && find == 0)
            {
                if (strcmp(stu_node->stu_num, sub_node->stu_num)==0)
                {
                    find = 1;
                    break;
                }
                
                stu_node = stu_node->stu_p;
            }
            
            cla_node = cla_node->cla_p;
        }
        
        if (find)
        {
            sub_node->sub_p = stu_node->sub_hp;
            stu_node->sub_hp = sub_node;
        }
        else 
            free(sub_node);
    }
    
    fclose(pfile);
    
    if (res == 7)          //只有当所有文件都打开成功时,提示打开成功
        message_event(NULL, (void **)"数据文件打开成功！\n");
    return;

}

void save_event(GtkWidget *widget, gpointer *data)
{

    CLASS *cla_node;
    STUDENT *stu_node;
    GRADE *sub_node;

    FILE *pfout;

    system("mkdir .data");          //建立隐藏文件夹用以保存数据文件
    pfout = fopen(class_info_filename, "wb");
    
    for (cla_node = head; cla_node != NULL; cla_node = cla_node->cla_p)
    {
        fwrite(cla_node, sizeof(CLASS ), 1, pfout);
    }
    
    fclose(pfout);

    pfout = fopen(student_info_filename, "wb");
    
    for (cla_node=head; cla_node != NULL; cla_node = cla_node->cla_p)
    {
        stu_node = cla_node->stu_hp;
        
        while (stu_node != NULL)
        {
            fwrite(stu_node, sizeof(STUDENT), 1, pfout);
            stu_node = stu_node->stu_p;
        }
    }
    
    fclose(pfout);

    pfout = fopen(grade_info_filename, "wb");
    
    for (cla_node = head; cla_node != NULL; cla_node = cla_node->cla_p)
    {
        stu_node = cla_node->stu_hp;
        
        while (stu_node != NULL)
        {
            sub_node = stu_node->sub_hp;
            
            while (sub_node != NULL)
            {
                fwrite(sub_node, sizeof(GRADE), 1, pfout);
                sub_node = sub_node->sub_p;
            }
            
            stu_node = stu_node->stu_p;
        }
    }
    
    fclose(pfout);
    
    message_event(NULL, (void **)"数据文件保存成功！\n");

}

void backup_event(GtkWidget *widget,gpointer *data)
{

    CLASS *cla_node;
    STUDENT *stu_node;
    GRADE *sub_node;

    unsigned long cla_node_num = 0;
    unsigned long stu_node_num = 0;
    unsigned long sub_node_num = 0;
    int handle;

    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;

    dialog = gtk_file_chooser_dialog_new("文件备份", GTK_WINDOW(data), action, 
                                         "取消", GTK_RESPONSE_CANCEL, "备份", GTK_RESPONSE_ACCEPT, NULL);

    chooser = GTK_FILE_CHOOSER(dialog);   //调用系统文件选择对话框

    gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

    if (edited == 0)
        gtk_file_chooser_set_current_name(chooser, "grade.bac");
    else 
        gtk_file_chooser_set_filename(chooser, existing_filename);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        
        filename = gtk_file_chooser_get_filename(chooser);
        
        for (cla_node = head; cla_node != NULL; cla_node = cla_node->cla_p)
        {
            cla_node_num++;
            stu_node = cla_node->stu_hp;
            
            while (stu_node != NULL)
            {
                stu_node_num++;
                sub_node = stu_node->sub_hp;
               
                while (sub_node != NULL)
                {
                    sub_node_num++;
                    sub_node = sub_node->sub_p;
                }
                
                stu_node = stu_node->stu_p;
            }
        }
        
        if ((handle = open(filename, O_WRONLY)) == -1)
        {
            handle = open(filename, O_CREAT|O_WRONLY, 00644);
        }
        write(handle, (char *)&cla_node_num, sizeof(cla_node_num));
        write(handle, (char *)&stu_node_num, sizeof(stu_node_num));
        write(handle, (char *)&sub_node_num, sizeof(sub_node_num));
        
        for (cla_node = head; cla_node != NULL; cla_node = cla_node->cla_p)
            write(handle, (char *)cla_node, sizeof(CLASS));
        
        for (cla_node = head; cla_node != NULL; cla_node = cla_node->cla_p)
        {
            stu_node = cla_node->stu_hp;
            
            while (stu_node != NULL)
            {
                write(handle, (char *)stu_node, sizeof(STUDENT));
                stu_node = stu_node->stu_p;
            }
        }
        
        for (cla_node = head; cla_node != NULL; cla_node = cla_node->cla_p)
        {
            stu_node = cla_node->stu_hp;
            
            while (stu_node != NULL)
            {
                sub_node = stu_node->sub_hp;
                
                while (sub_node != NULL)
                {
                    write(handle, (char *)sub_node, sizeof(GRADE)); 
                    sub_node = sub_node->sub_p;
                }
                
                stu_node = stu_node->stu_p;
            }
        }
        
        close(handle);        //备份时将所有数据存放到一个文件中
        
        g_free(filename);
        message_event(NULL,  (void **)"数据备份成功");
    }
    
    gtk_widget_destroy(dialog);

}

void restore_event(GtkWidget *widget,gpointer *data)
{

    CLASS *hd = NULL;
    CLASS *cla_node;
    STUDENT *stu_node;
    GRADE *sub_node;

    unsigned long cla_node_num;
    unsigned long stu_node_num;
    unsigned long sub_node_num;
    unsigned long num;
    int handle;
    int find;

    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;

    dialog = gtk_file_chooser_dialog_new("数据恢复", GTK_WINDOW(data), action, 
                                         "取消", GTK_RESPONSE_CANCEL, "打开", GTK_RESPONSE_ACCEPT, NULL);
    res = gtk_dialog_run(GTK_DIALOG(dialog));
    
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        strcpy(existing_filename, filename);
        
        if ((handle = open(filename, O_RDONLY)) == -1)
            handle = open(filename, O_CREAT, S_IREAD);
        edited = 1;
        read(handle, (char *)&cla_node_num, sizeof(cla_node_num));
        read(handle, (char *)&stu_node_num, sizeof(stu_node_num));
        read(handle, (char *)&sub_node_num, sizeof(sub_node_num));
        
        for (num = 1; num <= cla_node_num; num++)
        {
            cla_node = (CLASS *)malloc(sizeof(CLASS));
            read(handle, (char *)cla_node, sizeof(CLASS));
            cla_node->stu_hp = NULL;
            cla_node->cla_p = hd;
            hd = cla_node;
        }
        
        *hp = hd->cla_p;
        
        for (num = 1; num <= stu_node_num; num++)
        {
            stu_node = (STUDENT *)malloc(sizeof(STUDENT));
            read(handle, (char *)stu_node, sizeof(STUDENT));
            stu_node->sub_hp = NULL;
            cla_node = hd;
            
            while (cla_node != NULL && strcmp(cla_node->cla_num, stu_node->cla_num) != 0)
                cla_node = cla_node->cla_p;
            
            if (cla_node != NULL)
            {
                stu_node->stu_p = cla_node->stu_hp;
                cla_node->stu_hp = stu_node;
            }
            else 
                free(stu_node);
        }
        
        for (num = 1; num <= sub_node_num; num++)
        {
            sub_node = (GRADE *)malloc(sizeof(GRADE));
            read(handle, (char *)sub_node, sizeof(GRADE));
            cla_node = hd;
            find = 0;
            while (cla_node != NULL && find == 0)
            {
                stu_node = cla_node->stu_hp;
                
                while (stu_node !=NULL && find==0)
                {
                    if (strcmp(stu_node->stu_num, sub_node->stu_num) == 0)
                    {
                        find = 1;
                        break;
                    }
                    
                    stu_node = stu_node->stu_p;
                }
                
                cla_node = cla_node->cla_p;
            }
            
            if (find)
            {
                sub_node->sub_p = stu_node->sub_hp;
                stu_node->sub_hp = sub_node;
            }
            else 
                free(sub_node);
        }
        
        close(handle);
        g_free(filename);
        
        message_event(NULL, (void **)"数据恢复成功");
    }

    gtk_widget_destroy(dialog);

}

void button_event(GtkWidget *widget, gpointer *data)
{

    switch ((int)data)      //单项选择按钮触发函数,改变全局变量choose的值
    {
        case 1:
            choose = 1;
            break;
        case 2:
            choose = 2;
            break;
        case 3:
            choose = 3;
            break;
        case 4:
            choose = 4;
            break;
    }

}

void label_button_event(GtkWidget *widget, gpointer *data)
{

    switch ((int)data) {      //单项选择按钮触发函数,改变标签内容
        case 11:
            choose = 1;
            gtk_label_set_text(GTK_LABEL(label0),"请输入班级编号");
            break;
        case 12:
            choose = 2;
            gtk_label_set_text(GTK_LABEL(label0),"请输入班导师姓名");
            break;
    }

}
