# Student Grade Management System
### 运行环境：Linux localhost 3.18.6-1-ARCH 

### 图形化环境配置：gtk3.0

### 编译命令(进入本说明文件所在菜单，在终端下输入命令):
    gcc -o stu_grade stu_grade.c grade.h method.h `pkg-config --cflags --libs gtk+-3.0`

### 说明：
      1.由于不同版本linux的gtk主题不同，窗口显示效果可能会有所不同
      2.编译命令中的`是斜分号不是'
      3.数据文件放在".data"文件夹中，在linux默认是隐藏文件夹
      4.请确保在gtk3.0环境下编译，gtk3.0与gtk2.0有不同，用2.0编译可能会报错
