/*************************************************************************
	> File Name: struct.h
	> Author: Guanyu Li
	> Mail: guanyuli@hustunique.com
	> Created Time: 2015年03月16日 星期一 23时27分39秒
 ************************************************************************/

#ifndef _GRADE_H
#define _GRADE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include <gtk/gtk.h>

#define STUDYSCOREMAX 100
#define SEMMAX 8
#define FILENAMEMAX 20

/**
 * 学生课程成绩基本信息链结点结构
 */
typedef struct grade {
    char stu_num[12];           //学号
    char sub_name[30];          //课程名
    int sub_sem;                //开课学期
    int sub_hour;               //学时数
    float sub_score;            //学分
    int stu_grade;              //考试成绩
    int stu_grade_sec;          //补考成绩
    struct grade *sub_p;        //指向下一个结点的指针
} GRADE;

/**
 * 学生基本信息链结点结构
 */
typedef struct student {
    char cla_num[10];           //班级编号
    char stu_num[12];           //学号
    char stu_name[20];          //姓名
    char stu_sex;               //性别(m:男 w:女)
    float learn_score;          //已修课程学分
    float get_score;            //已获学分
    float average;              //加权平均分
    struct student *stu_p;      //指向下一个结点的指针
    struct grade *sub_hp;       //指向学生课程成绩基本成绩信息链的头指针
} STUDENT;

/**
 * 班级信息链结点结构
 */
typedef struct classes {
    char cla_num[10];           //班级编号
    char cla_teacher[20];       //班导师
    char cla_tel[15];           //联系电话
    struct classes *cla_p;      //指向下一个结点的指针
    struct student *stu_hp;     //指向学生信息链的头指针
} CLASS;

/**
 * 按班级统计所得信息链结点结构
 */
typedef struct count_tot {
    char cla_num[10];           //班级编号
    int boy_num;                //男生人数 
    int girl_num;               //女生人数
    int fail_num;               //不及格人数
    float fail_rate;            //不及格比例
    float avr_average;          //平均加权平均分
    struct count_tot *tot_p;    //指向下一个结点的指针
} COUNT_TOT;

/**
 * 课程基本信息链结点结构
 */
typedef struct count_les {
    char les_name[30];          //课程名
    float les_score;            //学分
    int les_grade;              //课程成绩
    struct count_les *les_p;    //指向下一个结点的指针
} COUNT_LES;

/**
 * 按学生统计所得信息链结点结构
 */
typedef struct count_sem {
    char stu_name[20];          //姓名
    float sem_score;            //学期已获学分
    float sem_average;          //学期加权
    struct count_sem *sem_p;    //指向下一个结点的指针
    COUNT_LES *les_hp;          //指向课程基本信息链的头指针
} COUNT_SEM;

/**
 * 按课程统计所得信息链结点结构
 */
typedef struct count_gra {
    char sub_name[30];          //课程名
    int num_90_100;             //90-100分的人数
    int num_80_90;              //80-89分的人数
    int num_60_80;              //60-79分的人数
    int num_0_60;               //0-59分的人数
    long stunum;                //学生总人数
    long fail_num;              //不及格人数
    unsigned long grade_tot;    //总分数
    float sub_average;          //平均分
    float qualify_rate;         //及格率
    struct count_gra *gra_p;    //指向下一个结点的指针
} COUNT_GRA;

/**
 * 按学期统计所得信息链结点结构
 */
typedef struct count_sub {
    int sub_num;                //开课门数
    int sub_hour;               //总学时数
    float sub_score;            //总学分数
    int fail_num;               //不及格人数
    struct count_sub *sub_p;    //指向下一个结点的指针
} COUNT_SUB;

/**
 * 按班级与学期统计所得信息链结点结构
 */
typedef struct count_cla {
    int fail_num;               //不及格人数
    float fail_rate;            //不及格比例
    float avr_sem_average;      //学期平均加权平均分
    struct count_cla *cla_p;    //指向下一个结点的指针
} COUNT_CLA;

/**
 * 寻找函数返回值结构
 */
typedef struct result {
    int flag;                   //标记.找到为1,未找到为0
    void *ptr;                  //找到的结点的指针
} result;

/**
 * 默认数据文件存储路径
 */
char *class_info_filename = "./.data/class.dat";
char *student_info_filename = "./.data/student.dat";
char *grade_info_filename = "./.data/grade.dat";

/**
 * gtk用到的全局变量
 */
GtkWidget *entry0;
GtkWidget *entry1;
GtkWidget *entry2;
GtkWidget *entry3;
GtkWidget *entry4;
GtkWidget *entry5;
GtkWidget *entry6;
GtkWidget *combo;
GtkWidget *combo2;
GtkWidget *diawindow;
GtkWidget *button0;
GtkWidget *label0;

char existing_filename[FILENAMEMAX];
int choose = 1;
int edited = 0;

/**
 * 三向链表头指针及其指针
 */
CLASS *head = NULL;
CLASS **hp = &head;

/**
 * 链表结点寻找函数
 */
result cla_find(char *clanum, CLASS *head);      //班级寻找
result stu_find(char *stunum, CLASS *head);      //学生寻找
result sub_find(char *subname, CLASS *head);     //课程寻找
void sub_change(int i, char *subchg, char *subname, CLASS *head);//课程修改

/**
 * 主界面相关函数
 */
void loadmenu(void);            //创建主界面窗口       
GtkWidget *CreatMenuItem(GtkWidget *MenuBar,char *test);  //创建菜单

/**
 * 班级信息维护相关函数
 */
void cla_fill_event(GtkWidget *widget, gpointer *data);          //录入
void cla_fill(GtkWidget *widget, gpointer *data);
void cla_amend_event(GtkWidget *widget, gpointer *data);         //修改
void cla_amend(GtkWidget *widget,gpointer *data);
void cla_del_event(GtkWidget *widget, gpointer *data);           //删除
void cla_del_warning_event(GtkWidget *widget, gpointer *data);
void cla_del(GtkWidget *widget, gpointer *data);

/**
 * 学生基本信息维护相关函数
 */
void stu_fill_event(GtkWidget *widget, gpointer *data);          //录入
void stu_fill(GtkWidget *widget, gpointer *data);                
void stu_amend_event(GtkWidget *widget, gpointer *data);         //修改
void stu_amend(GtkWidget *widget, gpointer *data);
void stu_del_event(GtkWidget *widget, gpointer *data);           //删除
void stu_del_warning_event(GtkWidget *widget, gpointer *data);
void stu_del(GtkWidget *widget, gpointer *data);

/**
 * 学生课程成绩基本信息维护相关函数
 */
void grade_fill_event(GtkWidget *widget, gpointer *data);        //成绩录入
void grade_fill(GtkWidget *widget, gpointer *data);              
void sub_fill_event(GtkWidget *widget, gpointer *data);          //课程录入
void sub_fill(GtkWidget *widget, gpointer *data);
void sub_amend_event(GtkWidget *widget, gpointer *data);         //课程修改
void sub_amend(GtkWidget *widget, gpointer *data);
void grade_amend_event(GtkWidget *widget, gpointer *data);       //成绩修改
void grade_amend(GtkWidget *widget, gpointer *data);
void grade_del_event(GtkWidget *widget, gpointer *data);         //删除
void grade_del_warning_event(GtkWidget *widget, gpointer *data);
void grade_del(GtkWidget *widget, gpointer *data);

/**
 * 班级信息查询相关函数
 */
void cla_refer_event(GtkWidget *widget, gpointer *data);
void cla_refer(GtkWidget *widget, gpointer *data);

/**
 * 学生基本信息查询相关函数
 */
void stu_refer1_event(GtkWidget *widget, gpointer *data);    //精确查询
void stu_refer1(GtkWidget *widget, gpointer *data);
void stu_refer2_event(GtkWidget *widget, gpointer *data);    //模糊查询
void stu_refer2(GtkWidget *widget, gpointer *data);


/**
 * 学生课程成绩基本信息查询相关函数
 */
void sub_refer1_event(GtkWidget *widget, gpointer *data);    //精确查询
void sub_refer1(GtkWidget *widget, gpointer *data);
void sub_refer2_event(GtkWidget *widget, gpointer *data);    //模糊查询
void sub_refer2(GtkWidget *widget, gpointer *data);

/**
 * 信息统计相关函数
 */
void count_total(GtkWidget *widget, gpointer *data);         //按班级
void count_semester_event(GtkWidget *widget, gpointer *data);//按学生
void count_semester(GtkWidget *widget, gpointer *data);      
void count_grade(GtkWidget *widget, gpointer *data);         //按课程
void count_subject(GtkWidget *widget, gpointer *data);       //按学期
void count_class_event(GtkWidget *widget, gpointer *data);   //按班级学期
void count_class(GtkWidget *widget, gpointer *data);

/**
 * 文件操作及版权相关函数
 */
void load_event(GtkWidget *widget,gpointer *data);        //数据载入
void save_event(GtkWidget *widget,gpointer *data);        //数据保存
void backup_event(GtkWidget *widget,gpointer *data);      //数据备份
void restore_event(GtkWidget *widget,gpointer *data);     //数据恢复
void exit_event(GtkWidget *widget, gpointer *data);       //退出系统
void about_event(GtkWidget *widget,gpointer *data);       //系统版本全说明

/**
 * 其他函数
 */
void message_event(GtkWidget *widget, gpointer *data);       //提示信息弹出
void destroy(GtkWidget *widget, gpointer *data);             //关闭窗口
void button_event(GtkWidget *widget, gpointer *data);        //选择按钮触发
void label_button_event(GtkWidget *widget, gpointer *data);  //选择改变标签

#endif
