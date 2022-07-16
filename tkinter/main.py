import tkinter as tk
import tkinter.ttk
from tkinter import *
from tkinter import messagebox
from tkinter.messagebox import *
import pymysql
import sqlite3

global start, window_width, window_height
start = 0
if start == 0:
    print('use default options')
    window_width = 1200
    window_height = 600
else:
    print('user other options')


class MainWindow(Frame):
    def __init__(self, master=None):
        # 由于Frame为父类，因此需要调用父类的构造器
        super().__init__(master)
        print('__init__mode :width=%d,height=%d' % (window_width, window_height))
        self.value0 = tk.IntVar()  # 第一个界面参数
        self.value0.set(5)  # 初始化第一个界面参数
        self.value1 = tk.IntVar()  # 第二个界面参数
        self.value1.set(6)  # 初始化第二个界面参数
        self.value2 = tk.IntVar()  # 第三个界面参数
        self.value2.set(3)  # 初始化第三个界面参数
        self.start = start  # 判断是否需要初始化
        self.progressbar0 = 25  # 初始化progressbar0的值
        self.progressbar1 = 25  # 初始化progressbar1的值
        self.progressbar2 = 25  # 初始化progressbar2的值
        self.progressbar3 = 25  # 初始化progressbar3的值
        self.window = tk.Tk()  # 窗口
        self.menubar = tk.Menu(self.window)
        self.window.title('应用拉曼光谱的口腔癌诊断系统(build22714version3.0.0)')  # 窗口标题
        self.window_width = window_width
        self.window_height = window_height
        self.window.geometry(str(self.window_width) + 'x' + str(self.window_height))  # 加载时初始值
        self.window.bind('<Configure>', self.window_resize)
        self.create_menu()  # 创建目录
        self.create_widgets()  # 创建组件，在本方法中自定义组件
        self.window.config(menu=self.menubar)
        self.master = master  # Frame构造器
        self.pack()  # 组件定位
        self.window.update()
        self.update()

    def window_resize(self, event=None):
        print('width=%d,height=%d' % (self.window.winfo_width(), self.window.winfo_height()))
        if event is not None:
            if self.window_width != self.window.winfo_width() or self.window_height != self.window.winfo_height():
                if self.window_width != self.window.winfo_width():
                    self.window_width = self.window.winfo_width()
                if self.window_height != self.window.winfo_height():
                    self.window_height = self.window.winfo_height()
                print('new_width=%d,new_height=%d' % (self.window_width, self.window_height))
                global window_height, window_width, start
                window_width = self.window_width
                window_height = self.window_height
                print('width_outer=%d,height_outer=%d' % (window_width, window_height))
                start = start + 1
                self.window.update()
                self.reset()
                # self.create_widgets()
                # self.window.withdraw()
                # self.window.deiconify()
                self.create_widgets()
                # self.window.update()

    def update_progress(self):
        """
        函数功能：更新组件进度条
        :return: 更新成功 true 更新失败false
        """

    def reset(self):
        # 销毁当前页面所有部件
        try:
            self.window.grid_forget()
        except:
            print('reset failed')

    def create_menu(self):
        # 创建目录
        """
        下面为需要创建的菜单栏控件
        :return:
        """
        # 创建第一个菜单栏选项 -> 文件
        menu0 = tk.Menu(self.menubar)
        self.menubar.add_cascade(label='文件', menu=menu0)
        menu0.add_command(label='导出数据', command=self.action_save_data_normal)
        menu0.add_command(label='导出文件所有信息', command=self.action_save_all_data)
        menu0.add_separator()
        menu0.add_command(label='导入文件', command=self.action_input_file)
        menu0.add_command(label='导入文件至数据库', command=self.action_input_file_to_database)
        menu0.add_separator()
        menu0.add_command(label='退出', command=self.action_call_normal_exit)
        # 上述为第一个菜单栏选项 ->文件
        # 创建第二个菜单栏选项 -> 病人信息管理
        menu1 = tk.Menu(self.menubar)
        self.menubar.add_cascade(label='病人信息管理', menu=menu1)
        menu1.add_command(label='导入病人信息', command=self.action_input_information)
        menu1.add_command(label='显示病人信息', command=self.action_show_information)
        # 上述为第二个菜单栏选项 -> 病人信息管理
        # 创建第三个菜单栏选项 -> 程序高级控制
        menu2 = tk.Menu(self.menubar)
        self.menubar.add_cascade(label='程序高级控制', menu=menu2)
        menu2.add_command(label='显示目前程序参数状态', command=self.action_show_status_program)
        menu2.add_separator()
        menu2.add_command(label='程序屏幕状态清除', command=self.action_clear_window)
        menu2.add_command(label='程序功能自检', command=self.action_self_check)
        menu2.add_separator()
        menu2.add_command(label='退出', command=self.action_exit)
        # 上方为第三个菜单栏选项 -> 程序高级控制
        # 创建第四个菜单栏选项 -> 关于
        menu3 = tk.Menu(self.menubar)
        self.menubar.add_cascade(label='关于', menu=menu3)
        menu3.add_command(label='程序信息', command=self.action_program_information)
        menu3.add_command(label='程序官网', command=self.action_visit_website)
        # 上方为第四个菜单栏选项 ->关于

    def create_widgets(self):
        # 创建组件
        """
        下面需要创建的时其他界面控件，与原始尺寸匹配，可实现界面缩放自适应功能
        :return: NONE
        """

        # 下方开始显示主界面
        # 加载主界面框架
        # 创建主界面的第一个框架部件 ->拉曼光谱显示区域
        group0 = tk.LabelFrame(self.window, text='拉曼光谱显示区域', padx=10, pady=10)
        # 放置一个文本框，可以用于显示图片
        group0_text0 = tk.Text(group0, height=30 * self.window_height // 600,
                               width=78 * self.window_width // 1200).pack(anchor='center')
        group0.place(x=10 * self.window_width // 1200, y=10 * self.window_height // 1200)
        # 文本框放置完成
        # 下面为显示程序状态消息
        group1 = tk.LabelFrame(self.window, text='程序状态消息', padx=10, pady=10)
        group1_text0 = tk.Text(group1, height=7 * self.window_height // 600, width=78 * self.window_width // 1200).pack(
            anchor='center')
        group1.place(x=10 * self.window_width // 1200, y=445 * self.window_height // 600)
        # 程序状态消息显示完成
        # 下面为检测结果显示区域
        group2 = tk.LabelFrame(self.window, text='检测结果', padx=10, pady=10, width=600 * self.window_width // 1200,
                               height=200 * self.window_height // 600)
        group2_radiobutton0 = tk.Radiobutton(group2, text='正常组织', variable=self.value0, value=1).place(
            x=10 * self.window_width // 1200, y=10 * self.window_height // 600)
        group2_radiobutton1 = tk.Radiobutton(group2, text='舌癌', variable=self.value0, value=2).place(
            x=150 * self.window_width // 1200, y=10 * self.window_height // 600)
        group2_radiobutton2 = tk.Radiobutton(group2, text='颊癌', variable=self.value0, value=3).place(
            x=300 * self.window_width // 1200, y=10 * self.window_height // 600)
        group2_radiobutton3 = tk.Radiobutton(group2, text='牙龈癌', variable=self.value0, value=4).place(
            x=450 * self.window_width // 1200, y=10 * self.window_height // 600)
        group2_progressbar0 = tkinter.ttk.Progressbar(group2, orient=tkinter.VERTICAL, length=100,
                                                      value=self.progressbar0).place(x=30 * self.window_width // 1200,
                                                                                     y=50 * self.window_height // 600)
        group2_progressbar1 = tkinter.ttk.Progressbar(group2, orient=tkinter.VERTICAL, length=100,
                                                      value=self.progressbar1).place(x=180 * self.window_width // 1200,
                                                                                     y=50 * self.window_height // 600)
        group2_progressbar2 = tkinter.ttk.Progressbar(group2, orient=tkinter.VERTICAL, length=100,
                                                      value=self.progressbar2).place(x=330 * self.window_width // 1200,
                                                                                     y=50 * self.window_height // 600)
        group2_progressbar3 = tkinter.ttk.Progressbar(group2, orient=tkinter.VERTICAL, length=100,
                                                      value=self.progressbar3).place(x=480 * self.window_width // 1200,
                                                                                     y=50 * self.window_height // 600)
        group2.place(x=600 * self.window_width // 1200, y=10 * self.window_height // 600)
        # 检测结果显示区域放置完成
        # 下方为控制部分
        # 控制部分的第一个模块 -> 模型选择
        group3 = tk.LabelFrame(self.window, text='控制部分', padx=10, pady=10, width=600 * self.window_width // 1200,
                               height=360 * self.window_height // 600)
        group3_group0 = tk.LabelFrame(group3, text='模型选择', padx=10, pady=10, width=580 * self.window_width // 1200,
                                      height=100 * self.window_height // 600)
        group3_group0_radiobutton0 = tk.Radiobutton(group3_group0, text='mobilenet', variable=self.value1, value=1,
                                                    command=self.set_radiobutton_0).place(
            x=20 * self.window_width // 1200, y=15 * self.window_height // 600)
        group3_group0_radiobutton1 = tk.Radiobutton(group3_group0, text='resnet50', variable=self.value1, value=2,
                                                    command=self.set_radiobutton_1).place(
            x=120 * self.window_width // 1200, y=15 * self.window_height // 600)
        group3_group0_radiobutton2 = tk.Radiobutton(group3_group0, text='transformer', variable=self.value1, value=3,
                                                    command=self.set_radiobutton_2).place(
            x=220 * self.window_width // 1200, y=15 * self.window_height // 600)
        group3_group0_radiobutton3 = tk.Radiobutton(group3_group0, text='vgg', variable=self.value1, value=4,
                                                    command=self.set_radiobutton_3).place(
            x=320 * self.window_width // 1200, y=15 * self.window_height // 600)
        group3_group0_radiobutton4 = tk.Radiobutton(group3_group0, text='inception', variable=self.value1, value=5,
                                                    command=self.set_radiobutton_4).place(
            x=420 * self.window_width // 1200, y=15 * self.window_height // 600)
        # 开始放置第一个模块 -> 模型选择
        group3_group0.place(x=0 * self.window_width // 1200, y=0 * self.window_height // 600)
        # 开始放置第二个模块 -> 外部设备控制
        group3_group1 = tk.LabelFrame(group3, text='外部设备控制', padx=10, pady=10, width=580 * self.window_width // 1200,
                                      height=150 * self.window_height // 600)
        group3_group1_group0 = tk.LabelFrame(group3_group1, text='拉曼光谱仪控制部分', padx=10, pady=10,
                                             width=560 * self.window_width // 1200,
                                             height=50 * self.window_height // 600)
        group3_group1_group0_button0 = tk.Button(group3_group1_group0, text='启动', width=8 * self.window_width // 1200,
                                                 height=1 * self.window_height // 600, command=self.start_01).place(
            x=10 * self.window_width // 1200, y=-10 * self.window_height // 600)
        group3_group1_group0_button1 = tk.Button(group3_group1_group0, text='关闭', width=8 * self.window_width // 1200,
                                                 height=1 * self.window_height // 600, command=self.close_01).place(
            x=160 * self.window_width // 1200, y=-10 * self.window_height // 600)
        group3_group1_group0_button2 = tk.Button(group3_group1_group0, text='导出文件', width=8 * self.window_width // 1200,
                                                 height=1 * self.window_height // 600, command=self.release_file).place(
            x=310 * self.window_width // 1200, y=-10 * self.window_height // 600)
        group3_group1_group0_button3 = tk.Button(group3_group1_group0, text='波特率调节',
                                                 width=8 * self.window_width // 1200,
                                                 height=1 * self.window_height // 600, command=self.adjust_01).place(
            x=460 * self.window_width // 1200, y=-10 * self.window_height // 600)
        # 开始放置外部设备控制模块中的第一个子模块 -> 拉曼光谱仪控制部分
        group3_group1_group0.place(x=0 * self.window_width // 1200, y=0 * self.window_height // 600)
        # 第一个子模块放置完成 -> 拉曼光谱仪控制部分
        # 开始放置第二个子模块 -> 激光器控制部分
        group3_group1_group1 = tk.LabelFrame(group3_group1, text='激光器控制部分', width=560 * self.window_width // 1200,
                                             height=50 * self.window_height // 600)
        group3_group1_group1_button0 = tk.Button(group3_group1_group1, text='启动', width=8 * self.window_width // 1200,
                                                 height=1 * self.window_height // 600, command=self.start_02).place(
            x=10 * self.window_width // 1200, y=-5 * self.window_height // 600)
        group3_group1_group1_button1 = tk.Button(group3_group1_group1, text='关闭', width=8 * self.window_width // 1200,
                                                 height=1 * self.window_height // 600, command=self.close_02).place(
            x=110 * self.window_width // 1200, y=-5 * self.window_height // 600)
        group3_group1_group1_button2 = tk.Button(group3_group1_group1, text='积分时间设定',
                                                 width=8 * self.window_width // 1200,
                                                 height=1 * self.window_height // 600, command=self.adjust_02).place(
            x=210 * self.window_width // 1200, y=-5 * self.window_height // 600)
        group3_group1_group1_button3 = tk.Button(group3_group1_group1, text='激发波长设定',
                                                 width=10 * self.window_width // 1200,
                                                 height=1 * self.window_height // 600, command=self.adjust_03).place(
            x=330 * self.window_width // 1200, y=-5 * self.window_height // 600)
        group3_group1_group1_button4 = tk.Button(group3_group1_group1, text='距离设定',
                                                 width=10 * self.window_width // 1200,
                                                 height=1 * self.window_height // 600, command=self.adjust_04).place(
            x=450 * self.window_width // 1200, y=-5 * self.window_height // 600)
        # 开始放置外部设备控制模块中的第二个子模块 -> 激光器控制部分
        group3_group1_group1.place(x=0 * self.window_width // 1200, y=60 * self.window_height // 600)
        group3_group1.place(x=0 * self.window_width // 1200, y=100 * self.window_height // 600)
        # 开始放置第三个模块 -> 主程序控制部分
        group3_group2 = tk.LabelFrame(group3, text='主程序控制', padx=10, pady=10, width=580 * self.window_width // 1200,
                                      height=70 * self.window_height // 600)
        group3_group2_button0 = tk.Button(group3_group2, text='选择文件并识别', width=16 * self.window_width // 1200,
                                          height=1 * self.window_height // 600, command=self.choose_file).place(
            x=0 * self.window_width // 1200, y=-10 * self.window_height // 600)
        group3_group2_button1 = tk.Button(group3_group2, text='一键检测（在线）', width=10 * self.window_width // 1200,
                                          height=1 * self.window_height // 600, command=self.detect_online).place(
            x=140 * self.window_width // 1200, y=-10 * self.window_height // 600)
        group3_group2_button2 = tk.Button(group3_group2, text='下载数据（在线）', width=10 * self.window_width // 1200,
                                          height=1 * self.window_height // 600, command=self.download_data).place(
            x=280 * self.window_width // 1200, y=-10 * self.window_height // 600)
        group3_group2_radioButton0 = tk.ttk.Radiobutton(group3_group2, text='离线模式', variable=self.value2, value=1,
                                                        command=self.set_radiobutton_01).place(
            x=420 * self.window_width // 1200, y=-10 * self.window_height // 600)
        group3_group2_radioButton1 = tk.ttk.Radiobutton(group3_group2, text='在线模式', variable=self.value2, value=2,
                                                        command=self.set_radiobutton_02).place(
            x=420 * self.window_width // 1200, y=10 * self.window_height // 600)
        group3_group2.place(x=0 * self.window_width // 1200, y=250 * self.window_height // 600)
        group3.place(x=600 * self.window_width // 1200, y=220 * self.window_height // 600)

    def action_save_data_normal(self):
        """
        函数功能：导出数据
        :return: True ->导出成功 False ->导出失败
        """
        messagebox.showinfo(title='提示', message='数据导出成功')

    def action_save_all_data(self):
        """
        函数功能：导出文件所有信息
        :return: True -> 导出信息成功 False ->导出信息失败
        """
        # 获取病人的六个基本信息+拉曼光谱1044个点位图信息
        """
        在此处链接数据库
        """
        conn = sqlite3.connect("main.db")
        cursor = conn.cursor()
        try:
            sql = "CREATE TABLE INFO(PATIENT_NAME PRIMARY KEY NOT NULL, PATIENT_GENDER TEXT NOT NULL," \
                  " PATIENT_AGE TEXT NOT NULL, PATIENT_TIME TEXT NOT NULL," \
                  " PATIENT_PART TEXT NOT NULL, PATIENT_BAD TEXT NOT NULL," \
                  " LIGHT0000 TEXT NOT NULL, LIGHT0001 TEXT NOT NULL," \
                  " LIGHT0002 TEXT NOT NULL, LIGHT0003 TEXT NOT NULL," \
                  " LIGHT0004 TEXT NOT NULL, LIGHT0005 TEXT NOT NULL," \
                  " LIGHT0006 TEXT NOT NULL, LIGHT0007 TEXT NOT NULL," \
                  " LIGHT0008 TEXT NOT NULL, LIGHT0009 TEXT NOT NULL," \
                  " LIGHT0010 TEXT NOT NULL, LIGHT0011 TEXT NOT NULL," \
                  " LIGHT0012 TEXT NOT NULL, LIGHT0013 TEXT NOT NULL," \
                  " LIGHT0014 TEXT NOT NULL, LIGHT0015 TEXT NOT NULL," \
                  " LIGHT0016 TEXT NOT NULL, LIGHT0017 TEXT NOT NULL," \
                  " LIGHT0018 TEXT NOT NULL, LIGHT0019 TEXT NOT NULL," \
                  " LIGHT0020 TEXT NOT NULL, LIGHT0021 TEXT NOT NULL," \
                  " LIGHT0022 TEXT NOT NULL, LIGHT0023 TEXT NOT NULL," \
                  " LIGHT0024 TEXT NOT NULL, LIGHT0025 TEXT NOT NULL," \
                  " LIGHT0026 TEXT NOT NULL, LIGHT0027 TEXT NOT NULL," \
                  " LIGHT0028 TEXT NOT NULL, LIGHT0029 TEXT NOT NULL," \
                  " LIGHT0030 TEXT NOT NULL, LIGHT0031 TEXT NOT NULL," \
                  " LIGHT0032 TEXT NOT NULL, LIGHT0033 TEXT NOT NULL," \
                  " LIGHT0034 TEXT NOT NULL, LIGHT0035 TEXT NOT NULL," \
                  " LIGHT0036 TEXT NOT NULL, LIGHT0037 TEXT NOT NULL," \
                  " LIGHT0038 TEXT NOT NULL, LIGHT0039 TEXT NOT NULL," \
                  " LIGHT0040 TEXT NOT NULL, LIGHT0041 TEXT NOT NULL," \
                  " LIGHT0042 TEXT NOT NULL, LIGHT0043 TEXT NOT NULL," \
                  " LIGHT0044 TEXT NOT NULL, LIGHT0045 TEXT NOT NULL," \
                  " LIGHT0046 TEXT NOT NULL, LIGHT0047 TEXT NOT NULL," \
                  " LIGHT0048 TEXT NOT NULL, LIGHT0049 TEXT NOT NULL," \
                  " LIGHT0050 TEXT NOT NULL, LIGHT0051 TEXT NOT NULL," \
                  " LIGHT0052 TEXT NOT NULL, LIGHT0053 TEXT NOT NULL," \
                  " LIGHT0054 TEXT NOT NULL, LIGHT0055 TEXT NOT NULL," \
                  " LIGHT0056 TEXT NOT NULL, LIGHT0057 TEXT NOT NULL," \
                  " LIGHT0058 TEXT NOT NULL, LIGHT0059 TEXT NOT NULL," \
                  " LIGHT0060 TEXT NOT NULL, LIGHT0061 TEXT NOT NULL," \
                  " LIGHT0062 TEXT NOT NULL, LIGHT0063 TEXT NOT NULL," \
                  " LIGHT0064 TEXT NOT NULL, LIGHT0065 TEXT NOT NULL," \
                  " LIGHT0066 TEXT NOT NULL, LIGHT0067 TEXT NOT NULL," \
                  " LIGHT0068 TEXT NOT NULL, LIGHT0069 TEXT NOT NULL," \
                  " LIGHT0070 TEXT NOT NULL, LIGHT0071 TEXT NOT NULL," \
                  " LIGHT0072 TEXT NOT NULL, LIGHT0073 TEXT NOT NULL," \
                  " LIGHT0074 TEXT NOT NULL, LIGHT0075 TEXT NOT NULL," \
                  " LIGHT0076 TEXT NOT NULL, LIGHT0077 TEXT NOT NULL," \
                  " LIGHT0078 TEXT NOT NULL, LIGHT0079 TEXT NOT NULL," \
                  " LIGHT0080 TEXT NOT NULL, LIGHT0081 TEXT NOT NULL," \
                  " LIGHT0082 TEXT NOT NULL, LIGHT0083 TEXT NOT NULL," \
                  " LIGHT0084 TEXT NOT NULL, LIGHT0085 TEXT NOT NULL," \
                  " LIGHT0086 TEXT NOT NULL, LIGHT0087 TEXT NOT NULL," \
                  " LIGHT0088 TEXT NOT NULL, LIGHT0089 TEXT NOT NULL," \
                  " LIGHT0090 TEXT NOT NULL, LIGHT0091 TEXT NOT NULL," \
                  " LIGHT0092 TEXT NOT NULL, LIGHT0093 TEXT NOT NULL," \
                  " LIGHT0094 TEXT NOT NULL, LIGHT0095 TEXT NOT NULL," \
                  " LIGHT0096 TEXT NOT NULL, LIGHT0097 TEXT NOT NULL," \
                  " LIGHT0098 TEXT NOT NULL, LIGHT0099 TEXT NOT NULL," \
                  " LIGHT0100 TEXT NOT NULL, LIGHT0101 TEXT NOT NULL," \
                  " LIGHT0102 TEXT NOT NULL, LIGHT0103 TEXT NOT NULL," \
                  " LIGHT0104 TEXT NOT NULL, LIGHT0105 TEXT NOT NULL," \
                  " LIGHT0106 TEXT NOT NULL, LIGHT0107 TEXT NOT NULL," \
                  " LIGHT0108 TEXT NOT NULL, LIGHT0109 TEXT NOT NULL," \
                  " LIGHT0110 TEXT NOT NULL, LIGHT0111 TEXT NOT NULL," \
                  " LIGHT0112 TEXT NOT NULL, LIGHT0113 TEXT NOT NULL," \
                  " LIGHT0114 TEXT NOT NULL, LIGHT0115 TEXT NOT NULL," \
                  " LIGHT0116 TEXT NOT NULL, LIGHT0117 TEXT NOT NULL," \
                  " LIGHT0118 TEXT NOT NULL, LIGHT0119 TEXT NOT NULL," \
                  " LIGHT0120 TEXT NOT NULL, LIGHT0121 TEXT NOT NULL," \
                  " LIGHT0122 TEXT NOT NULL, LIGHT0123 TEXT NOT NULL," \
                  " LIGHT0124 TEXT NOT NULL, LIGHT0125 TEXT NOT NULL," \
                  " LIGHT0126 TEXT NOT NULL, LIGHT0127 TEXT NOT NULL," \
                  " LIGHT0128 TEXT NOT NULL, LIGHT0129 TEXT NOT NULL," \
                  " LIGHT0130 TEXT NOT NULL, LIGHT0131 TEXT NOT NULL," \
                  " LIGHT0132 TEXT NOT NULL, LIGHT0133 TEXT NOT NULL," \
                  " LIGHT0134 TEXT NOT NULL, LIGHT0135 TEXT NOT NULL," \
                  " LIGHT0136 TEXT NOT NULL, LIGHT0137 TEXT NOT NULL," \
                  " LIGHT0138 TEXT NOT NULL, LIGHT0139 TEXT NOT NULL," \
                  " LIGHT0140 TEXT NOT NULL, LIGHT0141 TEXT NOT NULL," \
                  " LIGHT0142 TEXT NOT NULL, LIGHT0143 TEXT NOT NULL," \
                  " LIGHT0144 TEXT NOT NULL, LIGHT0145 TEXT NOT NULL," \
                  " LIGHT0146 TEXT NOT NULL, LIGHT0147 TEXT NOT NULL," \
                  " LIGHT0148 TEXT NOT NULL, LIGHT0149 TEXT NOT NULL," \
                  " LIGHT0150 TEXT NOT NULL, LIGHT0151 TEXT NOT NULL," \
                  " LIGHT0152 TEXT NOT NULL, LIGHT0153 TEXT NOT NULL," \
                  " LIGHT0154 TEXT NOT NULL, LIGHT0155 TEXT NOT NULL," \
                  " LIGHT0156 TEXT NOT NULL, LIGHT0157 TEXT NOT NULL," \
                  " LIGHT0158 TEXT NOT NULL, LIGHT0159 TEXT NOT NULL," \
                  " LIGHT0160 TEXT NOT NULL, LIGHT0161 TEXT NOT NULL," \
                  " LIGHT0162 TEXT NOT NULL, LIGHT0163 TEXT NOT NULL," \
                  " LIGHT0164 TEXT NOT NULL, LIGHT0165 TEXT NOT NULL," \
                  " LIGHT0166 TEXT NOT NULL, LIGHT0167 TEXT NOT NULL," \
                  " LIGHT0168 TEXT NOT NULL, LIGHT0169 TEXT NOT NULL," \
                  " LIGHT0170 TEXT NOT NULL, LIGHT0171 TEXT NOT NULL," \
                  " LIGHT0172 TEXT NOT NULL, LIGHT0173 TEXT NOT NULL," \
                  " LIGHT0174 TEXT NOT NULL, LIGHT0175 TEXT NOT NULL," \
                  " LIGHT0176 TEXT NOT NULL, LIGHT0177 TEXT NOT NULL," \
                  " LIGHT0178 TEXT NOT NULL, LIGHT0179 TEXT NOT NULL," \
                  " LIGHT0180 TEXT NOT NULL, LIGHT0181 TEXT NOT NULL," \
                  " LIGHT0182 TEXT NOT NULL, LIGHT0183 TEXT NOT NULL," \
                  " LIGHT0184 TEXT NOT NULL, LIGHT0185 TEXT NOT NULL," \
                  " LIGHT0186 TEXT NOT NULL, LIGHT0187 TEXT NOT NULL," \
                  " LIGHT0188 TEXT NOT NULL, LIGHT0189 TEXT NOT NULL," \
                  " LIGHT0190 TEXT NOT NULL, LIGHT0191 TEXT NOT NULL," \
                  " LIGHT0192 TEXT NOT NULL, LIGHT0193 TEXT NOT NULL," \
                  " LIGHT0194 TEXT NOT NULL, LIGHT0195 TEXT NOT NULL," \
                  " LIGHT0196 TEXT NOT NULL, LIGHT0197 TEXT NOT NULL," \
                  " LIGHT0198 TEXT NOT NULL, LIGHT0199 TEXT NOT NULL," \
                  " LIGHT0200 TEXT NOT NULL, LIGHT0201 TEXT NOT NULL," \
                  " LIGHT0202 TEXT NOT NULL, LIGHT0203 TEXT NOT NULL," \
                  " LIGHT0204 TEXT NOT NULL, LIGHT0205 TEXT NOT NULL," \
                  " LIGHT0206 TEXT NOT NULL, LIGHT0207 TEXT NOT NULL," \
                  " LIGHT0208 TEXT NOT NULL, LIGHT0209 TEXT NOT NULL," \
                  " LIGHT0210 TEXT NOT NULL, LIGHT0211 TEXT NOT NULL," \
                  " LIGHT0212 TEXT NOT NULL, LIGHT0213 TEXT NOT NULL," \
                  " LIGHT0214 TEXT NOT NULL, LIGHT0215 TEXT NOT NULL," \
                  " LIGHT0216 TEXT NOT NULL, LIGHT0217 TEXT NOT NULL," \
                  " LIGHT0218 TEXT NOT NULL, LIGHT0219 TEXT NOT NULL," \
                  " LIGHT0220 TEXT NOT NULL, LIGHT0221 TEXT NOT NULL," \
                  " LIGHT0222 TEXT NOT NULL, LIGHT0223 TEXT NOT NULL," \
                  " LIGHT0224 TEXT NOT NULL, LIGHT0225 TEXT NOT NULL," \
                  " LIGHT0226 TEXT NOT NULL, LIGHT0227 TEXT NOT NULL," \
                  " LIGHT0228 TEXT NOT NULL, LIGHT0229 TEXT NOT NULL," \
                  " LIGHT0230 TEXT NOT NULL, LIGHT0231 TEXT NOT NULL," \
                  " LIGHT0232 TEXT NOT NULL, LIGHT0233 TEXT NOT NULL," \
                  " LIGHT0234 TEXT NOT NULL, LIGHT0235 TEXT NOT NULL," \
                  " LIGHT0236 TEXT NOT NULL, LIGHT0237 TEXT NOT NULL," \
                  " LIGHT0238 TEXT NOT NULL, LIGHT0239 TEXT NOT NULL," \
                  " LIGHT0240 TEXT NOT NULL, LIGHT0241 TEXT NOT NULL," \
                  " LIGHT0242 TEXT NOT NULL, LIGHT0243 TEXT NOT NULL," \
                  " LIGHT0244 TEXT NOT NULL, LIGHT0245 TEXT NOT NULL," \
                  " LIGHT0246 TEXT NOT NULL, LIGHT0247 TEXT NOT NULL," \
                  " LIGHT0248 TEXT NOT NULL, LIGHT0249 TEXT NOT NULL," \
                  " LIGHT0250 TEXT NOT NULL, LIGHT0251 TEXT NOT NULL," \
                  " LIGHT0252 TEXT NOT NULL, LIGHT0253 TEXT NOT NULL," \
                  " LIGHT0254 TEXT NOT NULL, LIGHT0255 TEXT NOT NULL," \
                  " LIGHT0256 TEXT NOT NULL, LIGHT0257 TEXT NOT NULL," \
                  " LIGHT0258 TEXT NOT NULL, LIGHT0259 TEXT NOT NULL," \
                  " LIGHT0260 TEXT NOT NULL, LIGHT0261 TEXT NOT NULL," \
                  " LIGHT0262 TEXT NOT NULL, LIGHT0263 TEXT NOT NULL," \
                  " LIGHT0264 TEXT NOT NULL, LIGHT0265 TEXT NOT NULL," \
                  " LIGHT0266 TEXT NOT NULL, LIGHT0267 TEXT NOT NULL," \
                  " LIGHT0268 TEXT NOT NULL, LIGHT0269 TEXT NOT NULL," \
                  " LIGHT0270 TEXT NOT NULL, LIGHT0271 TEXT NOT NULL," \
                  " LIGHT0272 TEXT NOT NULL, LIGHT0273 TEXT NOT NULL," \
                  " LIGHT0274 TEXT NOT NULL, LIGHT0275 TEXT NOT NULL," \
                  " LIGHT0276 TEXT NOT NULL, LIGHT0277 TEXT NOT NULL," \
                  " LIGHT0278 TEXT NOT NULL, LIGHT0279 TEXT NOT NULL," \
                  " LIGHT0280 TEXT NOT NULL, LIGHT0281 TEXT NOT NULL," \
                  " LIGHT0282 TEXT NOT NULL, LIGHT0283 TEXT NOT NULL," \
                  " LIGHT0284 TEXT NOT NULL, LIGHT0285 TEXT NOT NULL," \
                  " LIGHT0286 TEXT NOT NULL, LIGHT0287 TEXT NOT NULL," \
                  " LIGHT0288 TEXT NOT NULL, LIGHT0289 TEXT NOT NULL," \
                  " LIGHT0290 TEXT NOT NULL, LIGHT0291 TEXT NOT NULL," \
                  " LIGHT0292 TEXT NOT NULL, LIGHT0293 TEXT NOT NULL," \
                  " LIGHT0294 TEXT NOT NULL, LIGHT0295 TEXT NOT NULL," \
                  " LIGHT0296 TEXT NOT NULL, LIGHT0297 TEXT NOT NULL," \
                  " LIGHT0298 TEXT NOT NULL, LIGHT0299 TEXT NOT NULL," \
                  " LIGHT0300 TEXT NOT NULL, LIGHT0301 TEXT NOT NULL," \
                  " LIGHT0302 TEXT NOT NULL, LIGHT0303 TEXT NOT NULL," \
                  " LIGHT0304 TEXT NOT NULL, LIGHT0305 TEXT NOT NULL," \
                  " LIGHT0306 TEXT NOT NULL, LIGHT0307 TEXT NOT NULL," \
                  " LIGHT0308 TEXT NOT NULL, LIGHT0309 TEXT NOT NULL," \
                  " LIGHT0310 TEXT NOT NULL, LIGHT0311 TEXT NOT NULL," \
                  " LIGHT0312 TEXT NOT NULL, LIGHT0313 TEXT NOT NULL," \
                  " LIGHT0314 TEXT NOT NULL, LIGHT0315 TEXT NOT NULL," \
                  " LIGHT0316 TEXT NOT NULL, LIGHT0317 TEXT NOT NULL," \
                  " LIGHT0318 TEXT NOT NULL, LIGHT0319 TEXT NOT NULL," \
                  " LIGHT0320 TEXT NOT NULL, LIGHT0321 TEXT NOT NULL," \
                  " LIGHT0322 TEXT NOT NULL, LIGHT0323 TEXT NOT NULL," \
                  " LIGHT0324 TEXT NOT NULL, LIGHT0325 TEXT NOT NULL," \
                  " LIGHT0326 TEXT NOT NULL, LIGHT0327 TEXT NOT NULL," \
                  " LIGHT0328 TEXT NOT NULL, LIGHT0329 TEXT NOT NULL," \
                  " LIGHT0330 TEXT NOT NULL, LIGHT0331 TEXT NOT NULL," \
                  " LIGHT0332 TEXT NOT NULL, LIGHT0333 TEXT NOT NULL," \
                  " LIGHT0334 TEXT NOT NULL, LIGHT0335 TEXT NOT NULL," \
                  " LIGHT0336 TEXT NOT NULL, LIGHT0337 TEXT NOT NULL," \
                  " LIGHT0338 TEXT NOT NULL, LIGHT0339 TEXT NOT NULL," \
                  " LIGHT0340 TEXT NOT NULL, LIGHT0341 TEXT NOT NULL," \
                  " LIGHT0342 TEXT NOT NULL, LIGHT0343 TEXT NOT NULL," \
                  " LIGHT0344 TEXT NOT NULL, LIGHT0345 TEXT NOT NULL," \
                  " LIGHT0346 TEXT NOT NULL, LIGHT0347 TEXT NOT NULL," \
                  " LIGHT0348 TEXT NOT NULL, LIGHT0349 TEXT NOT NULL," \
                  " LIGHT0350 TEXT NOT NULL, LIGHT0351 TEXT NOT NULL," \
                  " LIGHT0352 TEXT NOT NULL, LIGHT0353 TEXT NOT NULL," \
                  " LIGHT0354 TEXT NOT NULL, LIGHT0355 TEXT NOT NULL," \
                  " LIGHT0356 TEXT NOT NULL, LIGHT0357 TEXT NOT NULL," \
                  " LIGHT0358 TEXT NOT NULL, LIGHT0359 TEXT NOT NULL," \
                  " LIGHT0360 TEXT NOT NULL, LIGHT0361 TEXT NOT NULL," \
                  " LIGHT0362 TEXT NOT NULL, LIGHT0363 TEXT NOT NULL," \
                  " LIGHT0364 TEXT NOT NULL, LIGHT0365 TEXT NOT NULL," \
                  " LIGHT0366 TEXT NOT NULL, LIGHT0367 TEXT NOT NULL," \
                  " LIGHT0368 TEXT NOT NULL, LIGHT0369 TEXT NOT NULL," \
                  " LIGHT0370 TEXT NOT NULL, LIGHT0371 TEXT NOT NULL," \
                  " LIGHT0372 TEXT NOT NULL, LIGHT0373 TEXT NOT NULL," \
                  " LIGHT0374 TEXT NOT NULL, LIGHT0375 TEXT NOT NULL," \
                  " LIGHT0376 TEXT NOT NULL, LIGHT0377 TEXT NOT NULL," \
                  " LIGHT0378 TEXT NOT NULL, LIGHT0379 TEXT NOT NULL," \
                  " LIGHT0380 TEXT NOT NULL, LIGHT0381 TEXT NOT NULL," \
                  " LIGHT0382 TEXT NOT NULL, LIGHT0383 TEXT NOT NULL," \
                  " LIGHT0384 TEXT NOT NULL, LIGHT0385 TEXT NOT NULL," \
                  " LIGHT0386 TEXT NOT NULL, LIGHT0387 TEXT NOT NULL," \
                  " LIGHT0388 TEXT NOT NULL, LIGHT0389 TEXT NOT NULL," \
                  " LIGHT0390 TEXT NOT NULL, LIGHT0391 TEXT NOT NULL," \
                  " LIGHT0392 TEXT NOT NULL, LIGHT0393 TEXT NOT NULL," \
                  " LIGHT0394 TEXT NOT NULL, LIGHT0395 TEXT NOT NULL," \
                  " LIGHT0396 TEXT NOT NULL, LIGHT0397 TEXT NOT NULL," \
                  " LIGHT0398 TEXT NOT NULL, LIGHT0399 TEXT NOT NULL," \
                  " LIGHT0400 TEXT NOT NULL, LIGHT0401 TEXT NOT NULL," \
                  " LIGHT0402 TEXT NOT NULL, LIGHT0403 TEXT NOT NULL," \
                  " LIGHT0404 TEXT NOT NULL, LIGHT0405 TEXT NOT NULL," \
                  " LIGHT0406 TEXT NOT NULL, LIGHT0407 TEXT NOT NULL," \
                  " LIGHT0408 TEXT NOT NULL, LIGHT0409 TEXT NOT NULL," \
                  " LIGHT0410 TEXT NOT NULL, LIGHT0411 TEXT NOT NULL," \
                  " LIGHT0412 TEXT NOT NULL, LIGHT0413 TEXT NOT NULL," \
                  " LIGHT0414 TEXT NOT NULL, LIGHT0415 TEXT NOT NULL," \
                  " LIGHT0416 TEXT NOT NULL, LIGHT0417 TEXT NOT NULL," \
                  " LIGHT0418 TEXT NOT NULL, LIGHT0419 TEXT NOT NULL," \
                  " LIGHT0420 TEXT NOT NULL, LIGHT0421 TEXT NOT NULL," \
                  " LIGHT0422 TEXT NOT NULL, LIGHT0423 TEXT NOT NULL," \
                  " LIGHT0424 TEXT NOT NULL, LIGHT0425 TEXT NOT NULL," \
                  " LIGHT0426 TEXT NOT NULL, LIGHT0427 TEXT NOT NULL," \
                  " LIGHT0428 TEXT NOT NULL, LIGHT0429 TEXT NOT NULL," \
                  " LIGHT0430 TEXT NOT NULL, LIGHT0431 TEXT NOT NULL," \
                  " LIGHT0432 TEXT NOT NULL, LIGHT0433 TEXT NOT NULL," \
                  " LIGHT0434 TEXT NOT NULL, LIGHT0435 TEXT NOT NULL," \
                  " LIGHT0436 TEXT NOT NULL, LIGHT0437 TEXT NOT NULL," \
                  " LIGHT0438 TEXT NOT NULL, LIGHT0439 TEXT NOT NULL," \
                  " LIGHT0440 TEXT NOT NULL, LIGHT0441 TEXT NOT NULL," \
                  " LIGHT0442 TEXT NOT NULL, LIGHT0443 TEXT NOT NULL," \
                  " LIGHT0444 TEXT NOT NULL, LIGHT0445 TEXT NOT NULL," \
                  " LIGHT0446 TEXT NOT NULL, LIGHT0447 TEXT NOT NULL," \
                  " LIGHT0448 TEXT NOT NULL, LIGHT0449 TEXT NOT NULL," \
                  " LIGHT0450 TEXT NOT NULL, LIGHT0451 TEXT NOT NULL," \
                  " LIGHT0452 TEXT NOT NULL, LIGHT0453 TEXT NOT NULL," \
                  " LIGHT0454 TEXT NOT NULL, LIGHT0455 TEXT NOT NULL," \
                  " LIGHT0456 TEXT NOT NULL, LIGHT0457 TEXT NOT NULL," \
                  " LIGHT0458 TEXT NOT NULL, LIGHT0459 TEXT NOT NULL," \
                  " LIGHT0460 TEXT NOT NULL, LIGHT0461 TEXT NOT NULL," \
                  " LIGHT0462 TEXT NOT NULL, LIGHT0463 TEXT NOT NULL," \
                  " LIGHT0464 TEXT NOT NULL, LIGHT0465 TEXT NOT NULL," \
                  " LIGHT0466 TEXT NOT NULL, LIGHT0467 TEXT NOT NULL," \
                  " LIGHT0468 TEXT NOT NULL, LIGHT0469 TEXT NOT NULL," \
                  " LIGHT0470 TEXT NOT NULL, LIGHT0471 TEXT NOT NULL," \
                  " LIGHT0472 TEXT NOT NULL, LIGHT0473 TEXT NOT NULL," \
                  " LIGHT0474 TEXT NOT NULL, LIGHT0475 TEXT NOT NULL," \
                  " LIGHT0476 TEXT NOT NULL, LIGHT0477 TEXT NOT NULL," \
                  " LIGHT0478 TEXT NOT NULL, LIGHT0479 TEXT NOT NULL," \
                  " LIGHT0480 TEXT NOT NULL, LIGHT0481 TEXT NOT NULL," \
                  " LIGHT0482 TEXT NOT NULL, LIGHT0483 TEXT NOT NULL," \
                  " LIGHT0484 TEXT NOT NULL, LIGHT0485 TEXT NOT NULL," \
                  " LIGHT0486 TEXT NOT NULL, LIGHT0487 TEXT NOT NULL," \
                  " LIGHT0488 TEXT NOT NULL, LIGHT0489 TEXT NOT NULL," \
                  " LIGHT0490 TEXT NOT NULL, LIGHT0491 TEXT NOT NULL," \
                  " LIGHT0492 TEXT NOT NULL, LIGHT0493 TEXT NOT NULL," \
                  " LIGHT0494 TEXT NOT NULL, LIGHT0495 TEXT NOT NULL," \
                  " LIGHT0496 TEXT NOT NULL, LIGHT0497 TEXT NOT NULL," \
                  " LIGHT0498 TEXT NOT NULL, LIGHT0499 TEXT NOT NULL," \
                  " LIGHT0500 TEXT NOT NULL, LIGHT0501 TEXT NOT NULL," \
                  " LIGHT0502 TEXT NOT NULL, LIGHT0503 TEXT NOT NULL," \
                  " LIGHT0504 TEXT NOT NULL, LIGHT0505 TEXT NOT NULL," \
                  " LIGHT0506 TEXT NOT NULL, LIGHT0507 TEXT NOT NULL," \
                  " LIGHT0508 TEXT NOT NULL, LIGHT0509 TEXT NOT NULL," \
                  " LIGHT0510 TEXT NOT NULL, LIGHT0511 TEXT NOT NULL," \
                  " LIGHT0512 TEXT NOT NULL, LIGHT0513 TEXT NOT NULL," \
                  " LIGHT0514 TEXT NOT NULL, LIGHT0515 TEXT NOT NULL," \
                  " LIGHT0516 TEXT NOT NULL, LIGHT0517 TEXT NOT NULL," \
                  " LIGHT0518 TEXT NOT NULL, LIGHT0519 TEXT NOT NULL," \
                  " LIGHT0520 TEXT NOT NULL, LIGHT0521 TEXT NOT NULL," \
                  " LIGHT0522 TEXT NOT NULL, LIGHT0523 TEXT NOT NULL," \
                  " LIGHT0524 TEXT NOT NULL, LIGHT0525 TEXT NOT NULL," \
                  " LIGHT0526 TEXT NOT NULL, LIGHT0527 TEXT NOT NULL," \
                  " LIGHT0528 TEXT NOT NULL, LIGHT0529 TEXT NOT NULL," \
                  " LIGHT0530 TEXT NOT NULL, LIGHT0531 TEXT NOT NULL," \
                  " LIGHT0532 TEXT NOT NULL, LIGHT0533 TEXT NOT NULL," \
                  " LIGHT0534 TEXT NOT NULL, LIGHT0535 TEXT NOT NULL," \
                  " LIGHT0536 TEXT NOT NULL, LIGHT0537 TEXT NOT NULL," \
                  " LIGHT0538 TEXT NOT NULL, LIGHT0539 TEXT NOT NULL," \
                  " LIGHT0540 TEXT NOT NULL, LIGHT0541 TEXT NOT NULL," \
                  " LIGHT0542 TEXT NOT NULL, LIGHT0543 TEXT NOT NULL," \
                  " LIGHT0544 TEXT NOT NULL, LIGHT0545 TEXT NOT NULL," \
                  " LIGHT0546 TEXT NOT NULL, LIGHT0547 TEXT NOT NULL," \
                  " LIGHT0548 TEXT NOT NULL, LIGHT0549 TEXT NOT NULL," \
                  " LIGHT0550 TEXT NOT NULL, LIGHT0551 TEXT NOT NULL," \
                  " LIGHT0552 TEXT NOT NULL, LIGHT0553 TEXT NOT NULL," \
                  " LIGHT0554 TEXT NOT NULL, LIGHT0555 TEXT NOT NULL," \
                  " LIGHT0556 TEXT NOT NULL, LIGHT0557 TEXT NOT NULL," \
                  " LIGHT0558 TEXT NOT NULL, LIGHT0559 TEXT NOT NULL," \
                  " LIGHT0560 TEXT NOT NULL, LIGHT0561 TEXT NOT NULL," \
                  " LIGHT0562 TEXT NOT NULL, LIGHT0563 TEXT NOT NULL," \
                  " LIGHT0564 TEXT NOT NULL, LIGHT0565 TEXT NOT NULL," \
                  " LIGHT0566 TEXT NOT NULL, LIGHT0567 TEXT NOT NULL," \
                  " LIGHT0568 TEXT NOT NULL, LIGHT0569 TEXT NOT NULL," \
                  " LIGHT0570 TEXT NOT NULL, LIGHT0571 TEXT NOT NULL," \
                  " LIGHT0572 TEXT NOT NULL, LIGHT0573 TEXT NOT NULL," \
                  " LIGHT0574 TEXT NOT NULL, LIGHT0575 TEXT NOT NULL," \
                  " LIGHT0576 TEXT NOT NULL, LIGHT0577 TEXT NOT NULL," \
                  " LIGHT0578 TEXT NOT NULL, LIGHT0579 TEXT NOT NULL," \
                  " LIGHT0580 TEXT NOT NULL, LIGHT0581 TEXT NOT NULL," \
                  " LIGHT0582 TEXT NOT NULL, LIGHT0583 TEXT NOT NULL," \
                  " LIGHT0584 TEXT NOT NULL, LIGHT0585 TEXT NOT NULL," \
                  " LIGHT0586 TEXT NOT NULL, LIGHT0587 TEXT NOT NULL," \
                  " LIGHT0588 TEXT NOT NULL, LIGHT0589 TEXT NOT NULL," \
                  " LIGHT0590 TEXT NOT NULL, LIGHT0591 TEXT NOT NULL," \
                  " LIGHT0592 TEXT NOT NULL, LIGHT0593 TEXT NOT NULL," \
                  " LIGHT0594 TEXT NOT NULL, LIGHT0595 TEXT NOT NULL," \
                  " LIGHT0596 TEXT NOT NULL, LIGHT0597 TEXT NOT NULL," \
                  " LIGHT0598 TEXT NOT NULL, LIGHT0599 TEXT NOT NULL," \
                  " LIGHT0600 TEXT NOT NULL, LIGHT0601 TEXT NOT NULL," \
                  " LIGHT0602 TEXT NOT NULL, LIGHT0603 TEXT NOT NULL," \
                  " LIGHT0604 TEXT NOT NULL, LIGHT0605 TEXT NOT NULL," \
                  " LIGHT0606 TEXT NOT NULL, LIGHT0607 TEXT NOT NULL," \
                  " LIGHT0608 TEXT NOT NULL, LIGHT0609 TEXT NOT NULL," \
                  " LIGHT0610 TEXT NOT NULL, LIGHT0611 TEXT NOT NULL," \
                  " LIGHT0612 TEXT NOT NULL, LIGHT0613 TEXT NOT NULL," \
                  " LIGHT0614 TEXT NOT NULL, LIGHT0615 TEXT NOT NULL," \
                  " LIGHT0616 TEXT NOT NULL, LIGHT0617 TEXT NOT NULL," \
                  " LIGHT0618 TEXT NOT NULL, LIGHT0619 TEXT NOT NULL," \
                  " LIGHT0620 TEXT NOT NULL, LIGHT0621 TEXT NOT NULL," \
                  " LIGHT0622 TEXT NOT NULL, LIGHT0623 TEXT NOT NULL," \
                  " LIGHT0624 TEXT NOT NULL, LIGHT0625 TEXT NOT NULL," \
                  " LIGHT0626 TEXT NOT NULL, LIGHT0627 TEXT NOT NULL," \
                  " LIGHT0628 TEXT NOT NULL, LIGHT0629 TEXT NOT NULL," \
                  " LIGHT0630 TEXT NOT NULL, LIGHT0631 TEXT NOT NULL," \
                  " LIGHT0632 TEXT NOT NULL, LIGHT0633 TEXT NOT NULL," \
                  " LIGHT0634 TEXT NOT NULL, LIGHT0635 TEXT NOT NULL," \
                  " LIGHT0636 TEXT NOT NULL, LIGHT0637 TEXT NOT NULL," \
                  " LIGHT0638 TEXT NOT NULL, LIGHT0639 TEXT NOT NULL," \
                  " LIGHT0640 TEXT NOT NULL, LIGHT0641 TEXT NOT NULL," \
                  " LIGHT0642 TEXT NOT NULL, LIGHT0643 TEXT NOT NULL," \
                  " LIGHT0644 TEXT NOT NULL, LIGHT0645 TEXT NOT NULL," \
                  " LIGHT0646 TEXT NOT NULL, LIGHT0647 TEXT NOT NULL," \
                  " LIGHT0648 TEXT NOT NULL, LIGHT0649 TEXT NOT NULL," \
                  " LIGHT0650 TEXT NOT NULL, LIGHT0651 TEXT NOT NULL," \
                  " LIGHT0652 TEXT NOT NULL, LIGHT0653 TEXT NOT NULL," \
                  " LIGHT0654 TEXT NOT NULL, LIGHT0655 TEXT NOT NULL," \
                  " LIGHT0656 TEXT NOT NULL, LIGHT0657 TEXT NOT NULL," \
                  " LIGHT0658 TEXT NOT NULL, LIGHT0659 TEXT NOT NULL," \
                  " LIGHT0660 TEXT NOT NULL, LIGHT0661 TEXT NOT NULL," \
                  " LIGHT0662 TEXT NOT NULL, LIGHT0663 TEXT NOT NULL," \
                  " LIGHT0664 TEXT NOT NULL, LIGHT0665 TEXT NOT NULL," \
                  " LIGHT0666 TEXT NOT NULL, LIGHT0667 TEXT NOT NULL," \
                  " LIGHT0668 TEXT NOT NULL, LIGHT0669 TEXT NOT NULL," \
                  " LIGHT0670 TEXT NOT NULL, LIGHT0671 TEXT NOT NULL," \
                  " LIGHT0672 TEXT NOT NULL, LIGHT0673 TEXT NOT NULL," \
                  " LIGHT0674 TEXT NOT NULL, LIGHT0675 TEXT NOT NULL," \
                  " LIGHT0676 TEXT NOT NULL, LIGHT0677 TEXT NOT NULL," \
                  " LIGHT0678 TEXT NOT NULL, LIGHT0679 TEXT NOT NULL," \
                  " LIGHT0680 TEXT NOT NULL, LIGHT0681 TEXT NOT NULL," \
                  " LIGHT0682 TEXT NOT NULL, LIGHT0683 TEXT NOT NULL," \
                  " LIGHT0684 TEXT NOT NULL, LIGHT0685 TEXT NOT NULL," \
                  " LIGHT0686 TEXT NOT NULL, LIGHT0687 TEXT NOT NULL," \
                  " LIGHT0688 TEXT NOT NULL, LIGHT0689 TEXT NOT NULL," \
                  " LIGHT0690 TEXT NOT NULL, LIGHT0691 TEXT NOT NULL," \
                  " LIGHT0692 TEXT NOT NULL, LIGHT0693 TEXT NOT NULL," \
                  " LIGHT0694 TEXT NOT NULL, LIGHT0695 TEXT NOT NULL," \
                  " LIGHT0696 TEXT NOT NULL, LIGHT0697 TEXT NOT NULL," \
                  " LIGHT0698 TEXT NOT NULL, LIGHT0699 TEXT NOT NULL," \
                  " LIGHT0700 TEXT NOT NULL, LIGHT0701 TEXT NOT NULL," \
                  " LIGHT0702 TEXT NOT NULL, LIGHT0703 TEXT NOT NULL," \
                  " LIGHT0704 TEXT NOT NULL, LIGHT0705 TEXT NOT NULL," \
                  " LIGHT0706 TEXT NOT NULL, LIGHT0707 TEXT NOT NULL," \
                  " LIGHT0708 TEXT NOT NULL, LIGHT0709 TEXT NOT NULL," \
                  " LIGHT0710 TEXT NOT NULL, LIGHT0711 TEXT NOT NULL," \
                  " LIGHT0712 TEXT NOT NULL, LIGHT0713 TEXT NOT NULL," \
                  " LIGHT0714 TEXT NOT NULL, LIGHT0715 TEXT NOT NULL," \
                  " LIGHT0716 TEXT NOT NULL, LIGHT0717 TEXT NOT NULL," \
                  " LIGHT0718 TEXT NOT NULL, LIGHT0719 TEXT NOT NULL," \
                  " LIGHT0720 TEXT NOT NULL, LIGHT0721 TEXT NOT NULL," \
                  " LIGHT0722 TEXT NOT NULL, LIGHT0723 TEXT NOT NULL," \
                  " LIGHT0724 TEXT NOT NULL, LIGHT0725 TEXT NOT NULL," \
                  " LIGHT0726 TEXT NOT NULL, LIGHT0727 TEXT NOT NULL," \
                  " LIGHT0728 TEXT NOT NULL, LIGHT0729 TEXT NOT NULL," \
                  " LIGHT0730 TEXT NOT NULL, LIGHT0731 TEXT NOT NULL," \
                  " LIGHT0732 TEXT NOT NULL, LIGHT0733 TEXT NOT NULL," \
                  " LIGHT0734 TEXT NOT NULL, LIGHT0735 TEXT NOT NULL," \
                  " LIGHT0736 TEXT NOT NULL, LIGHT0737 TEXT NOT NULL," \
                  " LIGHT0738 TEXT NOT NULL, LIGHT0739 TEXT NOT NULL," \
                  " LIGHT0740 TEXT NOT NULL, LIGHT0741 TEXT NOT NULL," \
                  " LIGHT0742 TEXT NOT NULL, LIGHT0743 TEXT NOT NULL," \
                  " LIGHT0744 TEXT NOT NULL, LIGHT0745 TEXT NOT NULL," \
                  " LIGHT0746 TEXT NOT NULL, LIGHT0747 TEXT NOT NULL," \
                  " LIGHT0748 TEXT NOT NULL, LIGHT0749 TEXT NOT NULL," \
                  " LIGHT0750 TEXT NOT NULL, LIGHT0751 TEXT NOT NULL," \
                  " LIGHT0752 TEXT NOT NULL, LIGHT0753 TEXT NOT NULL," \
                  " LIGHT0754 TEXT NOT NULL, LIGHT0755 TEXT NOT NULL," \
                  " LIGHT0756 TEXT NOT NULL, LIGHT0757 TEXT NOT NULL," \
                  " LIGHT0758 TEXT NOT NULL, LIGHT0759 TEXT NOT NULL," \
                  " LIGHT0760 TEXT NOT NULL, LIGHT0761 TEXT NOT NULL," \
                  " LIGHT0762 TEXT NOT NULL, LIGHT0763 TEXT NOT NULL," \
                  " LIGHT0764 TEXT NOT NULL, LIGHT0765 TEXT NOT NULL," \
                  " LIGHT0766 TEXT NOT NULL, LIGHT0767 TEXT NOT NULL," \
                  " LIGHT0768 TEXT NOT NULL, LIGHT0769 TEXT NOT NULL," \
                  " LIGHT0770 TEXT NOT NULL, LIGHT0771 TEXT NOT NULL," \
                  " LIGHT0772 TEXT NOT NULL, LIGHT0773 TEXT NOT NULL," \
                  " LIGHT0774 TEXT NOT NULL, LIGHT0775 TEXT NOT NULL," \
                  " LIGHT0776 TEXT NOT NULL, LIGHT0777 TEXT NOT NULL," \
                  " LIGHT0778 TEXT NOT NULL, LIGHT0779 TEXT NOT NULL," \
                  " LIGHT0780 TEXT NOT NULL, LIGHT0781 TEXT NOT NULL," \
                  " LIGHT0782 TEXT NOT NULL, LIGHT0783 TEXT NOT NULL," \
                  " LIGHT0784 TEXT NOT NULL, LIGHT0785 TEXT NOT NULL," \
                  " LIGHT0786 TEXT NOT NULL, LIGHT0787 TEXT NOT NULL," \
                  " LIGHT0788 TEXT NOT NULL, LIGHT0789 TEXT NOT NULL," \
                  " LIGHT0790 TEXT NOT NULL, LIGHT0791 TEXT NOT NULL," \
                  " LIGHT0792 TEXT NOT NULL, LIGHT0793 TEXT NOT NULL," \
                  " LIGHT0794 TEXT NOT NULL, LIGHT0795 TEXT NOT NULL," \
                  " LIGHT0796 TEXT NOT NULL, LIGHT0797 TEXT NOT NULL," \
                  " LIGHT0798 TEXT NOT NULL, LIGHT0799 TEXT NOT NULL," \
                  " LIGHT0800 TEXT NOT NULL, LIGHT0801 TEXT NOT NULL," \
                  " LIGHT0802 TEXT NOT NULL, LIGHT0803 TEXT NOT NULL," \
                  " LIGHT0804 TEXT NOT NULL, LIGHT0805 TEXT NOT NULL," \
                  " LIGHT0806 TEXT NOT NULL, LIGHT0807 TEXT NOT NULL," \
                  " LIGHT0808 TEXT NOT NULL, LIGHT0809 TEXT NOT NULL," \
                  " LIGHT0810 TEXT NOT NULL, LIGHT0811 TEXT NOT NULL," \
                  " LIGHT0812 TEXT NOT NULL, LIGHT0813 TEXT NOT NULL," \
                  " LIGHT0814 TEXT NOT NULL, LIGHT0815 TEXT NOT NULL," \
                  " LIGHT0816 TEXT NOT NULL, LIGHT0817 TEXT NOT NULL," \
                  " LIGHT0818 TEXT NOT NULL, LIGHT0819 TEXT NOT NULL," \
                  " LIGHT0820 TEXT NOT NULL, LIGHT0821 TEXT NOT NULL," \
                  " LIGHT0822 TEXT NOT NULL, LIGHT0823 TEXT NOT NULL," \
                  " LIGHT0824 TEXT NOT NULL, LIGHT0825 TEXT NOT NULL," \
                  " LIGHT0826 TEXT NOT NULL, LIGHT0827 TEXT NOT NULL," \
                  " LIGHT0828 TEXT NOT NULL, LIGHT0829 TEXT NOT NULL," \
                  " LIGHT0830 TEXT NOT NULL, LIGHT0831 TEXT NOT NULL," \
                  " LIGHT0832 TEXT NOT NULL, LIGHT0833 TEXT NOT NULL," \
                  " LIGHT0834 TEXT NOT NULL, LIGHT0835 TEXT NOT NULL," \
                  " LIGHT0836 TEXT NOT NULL, LIGHT0837 TEXT NOT NULL," \
                  " LIGHT0838 TEXT NOT NULL, LIGHT0839 TEXT NOT NULL," \
                  " LIGHT0840 TEXT NOT NULL, LIGHT0841 TEXT NOT NULL," \
                  " LIGHT0842 TEXT NOT NULL, LIGHT0843 TEXT NOT NULL," \
                  " LIGHT0844 TEXT NOT NULL, LIGHT0845 TEXT NOT NULL," \
                  " LIGHT0846 TEXT NOT NULL, LIGHT0847 TEXT NOT NULL," \
                  " LIGHT0848 TEXT NOT NULL, LIGHT0849 TEXT NOT NULL," \
                  " LIGHT0850 TEXT NOT NULL, LIGHT0851 TEXT NOT NULL," \
                  " LIGHT0852 TEXT NOT NULL, LIGHT0853 TEXT NOT NULL," \
                  " LIGHT0854 TEXT NOT NULL, LIGHT0855 TEXT NOT NULL," \
                  " LIGHT0856 TEXT NOT NULL, LIGHT0857 TEXT NOT NULL," \
                  " LIGHT0858 TEXT NOT NULL, LIGHT0859 TEXT NOT NULL," \
                  " LIGHT0860 TEXT NOT NULL, LIGHT0861 TEXT NOT NULL," \
                  " LIGHT0862 TEXT NOT NULL, LIGHT0863 TEXT NOT NULL," \
                  " LIGHT0864 TEXT NOT NULL, LIGHT0865 TEXT NOT NULL," \
                  " LIGHT0866 TEXT NOT NULL, LIGHT0867 TEXT NOT NULL," \
                  " LIGHT0868 TEXT NOT NULL, LIGHT0869 TEXT NOT NULL," \
                  " LIGHT0870 TEXT NOT NULL, LIGHT0871 TEXT NOT NULL," \
                  " LIGHT0872 TEXT NOT NULL, LIGHT0873 TEXT NOT NULL," \
                  " LIGHT0874 TEXT NOT NULL, LIGHT0875 TEXT NOT NULL," \
                  " LIGHT0876 TEXT NOT NULL, LIGHT0877 TEXT NOT NULL," \
                  " LIGHT0878 TEXT NOT NULL, LIGHT0879 TEXT NOT NULL," \
                  " LIGHT0880 TEXT NOT NULL, LIGHT0881 TEXT NOT NULL," \
                  " LIGHT0882 TEXT NOT NULL, LIGHT0883 TEXT NOT NULL," \
                  " LIGHT0884 TEXT NOT NULL, LIGHT0885 TEXT NOT NULL," \
                  " LIGHT0886 TEXT NOT NULL, LIGHT0887 TEXT NOT NULL," \
                  " LIGHT0888 TEXT NOT NULL, LIGHT0889 TEXT NOT NULL," \
                  " LIGHT0890 TEXT NOT NULL, LIGHT0891 TEXT NOT NULL," \
                  " LIGHT0892 TEXT NOT NULL, LIGHT0893 TEXT NOT NULL," \
                  " LIGHT0894 TEXT NOT NULL, LIGHT0895 TEXT NOT NULL," \
                  " LIGHT0896 TEXT NOT NULL, LIGHT0897 TEXT NOT NULL," \
                  " LIGHT0898 TEXT NOT NULL, LIGHT0899 TEXT NOT NULL," \
                  " LIGHT0900 TEXT NOT NULL, LIGHT0901 TEXT NOT NULL," \
                  " LIGHT0902 TEXT NOT NULL, LIGHT0903 TEXT NOT NULL," \
                  " LIGHT0904 TEXT NOT NULL, LIGHT0905 TEXT NOT NULL," \
                  " LIGHT0906 TEXT NOT NULL, LIGHT0907 TEXT NOT NULL," \
                  " LIGHT0908 TEXT NOT NULL, LIGHT0909 TEXT NOT NULL," \
                  " LIGHT0910 TEXT NOT NULL, LIGHT0911 TEXT NOT NULL," \
                  " LIGHT0912 TEXT NOT NULL, LIGHT0913 TEXT NOT NULL," \
                  " LIGHT0914 TEXT NOT NULL, LIGHT0915 TEXT NOT NULL," \
                  " LIGHT0916 TEXT NOT NULL, LIGHT0917 TEXT NOT NULL," \
                  " LIGHT0918 TEXT NOT NULL, LIGHT0919 TEXT NOT NULL," \
                  " LIGHT0920 TEXT NOT NULL, LIGHT0921 TEXT NOT NULL," \
                  " LIGHT0922 TEXT NOT NULL, LIGHT0923 TEXT NOT NULL," \
                  " LIGHT0924 TEXT NOT NULL, LIGHT0925 TEXT NOT NULL," \
                  " LIGHT0926 TEXT NOT NULL, LIGHT0927 TEXT NOT NULL," \
                  " LIGHT0928 TEXT NOT NULL, LIGHT0929 TEXT NOT NULL," \
                  " LIGHT0930 TEXT NOT NULL, LIGHT0931 TEXT NOT NULL," \
                  " LIGHT0932 TEXT NOT NULL, LIGHT0933 TEXT NOT NULL," \
                  " LIGHT0934 TEXT NOT NULL, LIGHT0935 TEXT NOT NULL," \
                  " LIGHT0936 TEXT NOT NULL, LIGHT0937 TEXT NOT NULL," \
                  " LIGHT0938 TEXT NOT NULL, LIGHT0939 TEXT NOT NULL," \
                  " LIGHT0940 TEXT NOT NULL, LIGHT0941 TEXT NOT NULL," \
                  " LIGHT0942 TEXT NOT NULL, LIGHT0943 TEXT NOT NULL," \
                  " LIGHT0944 TEXT NOT NULL, LIGHT0945 TEXT NOT NULL," \
                  " LIGHT0946 TEXT NOT NULL, LIGHT0947 TEXT NOT NULL," \
                  " LIGHT0948 TEXT NOT NULL, LIGHT0949 TEXT NOT NULL," \
                  " LIGHT0950 TEXT NOT NULL, LIGHT0951 TEXT NOT NULL," \
                  " LIGHT0952 TEXT NOT NULL, LIGHT0953 TEXT NOT NULL," \
                  " LIGHT0954 TEXT NOT NULL, LIGHT0955 TEXT NOT NULL," \
                  " LIGHT0956 TEXT NOT NULL, LIGHT0957 TEXT NOT NULL," \
                  " LIGHT0958 TEXT NOT NULL, LIGHT0959 TEXT NOT NULL," \
                  " LIGHT0960 TEXT NOT NULL, LIGHT0961 TEXT NOT NULL," \
                  " LIGHT0962 TEXT NOT NULL, LIGHT0963 TEXT NOT NULL," \
                  " LIGHT0964 TEXT NOT NULL, LIGHT0965 TEXT NOT NULL," \
                  " LIGHT0966 TEXT NOT NULL, LIGHT0967 TEXT NOT NULL," \
                  " LIGHT0968 TEXT NOT NULL, LIGHT0969 TEXT NOT NULL," \
                  " LIGHT0970 TEXT NOT NULL, LIGHT0971 TEXT NOT NULL," \
                  " LIGHT0972 TEXT NOT NULL, LIGHT0973 TEXT NOT NULL," \
                  " LIGHT0974 TEXT NOT NULL, LIGHT0975 TEXT NOT NULL," \
                  " LIGHT0976 TEXT NOT NULL, LIGHT0977 TEXT NOT NULL," \
                  " LIGHT0978 TEXT NOT NULL, LIGHT0979 TEXT NOT NULL," \
                  " LIGHT0980 TEXT NOT NULL, LIGHT0981 TEXT NOT NULL," \
                  " LIGHT0982 TEXT NOT NULL, LIGHT0983 TEXT NOT NULL," \
                  " LIGHT0984 TEXT NOT NULL, LIGHT0985 TEXT NOT NULL," \
                  " LIGHT0986 TEXT NOT NULL, LIGHT0987 TEXT NOT NULL," \
                  " LIGHT0988 TEXT NOT NULL, LIGHT0989 TEXT NOT NULL," \
                  " LIGHT0990 TEXT NOT NULL, LIGHT0991 TEXT NOT NULL," \
                  " LIGHT0992 TEXT NOT NULL, LIGHT0993 TEXT NOT NULL," \
                  " LIGHT0994 TEXT NOT NULL, LIGHT0995 TEXT NOT NULL," \
                  " LIGHT0996 TEXT NOT NULL, LIGHT0997 TEXT NOT NULL," \
                  " LIGHT0998 TEXT NOT NULL, LIGHT0999 TEXT NOT NULL," \
                  " LIGHT1000 TEXT NOT NULL, LIGHT1001 TEXT NOT NULL," \
                  " LIGHT1002 TEXT NOT NULL, LIGHT1003 TEXT NOT NULL," \
                  " LIGHT1004 TEXT NOT NULL, LIGHT1005 TEXT NOT NULL," \
                  " LIGHT1006 TEXT NOT NULL, LIGHT1007 TEXT NOT NULL," \
                  " LIGHT1008 TEXT NOT NULL, LIGHT1009 TEXT NOT NULL," \
                  " LIGHT1010 TEXT NOT NULL, LIGHT1011 TEXT NOT NULL," \
                  " LIGHT1012 TEXT NOT NULL, LIGHT1013 TEXT NOT NULL," \
                  " LIGHT1014 TEXT NOT NULL, LIGHT1015 TEXT NOT NULL," \
                  " LIGHT1016 TEXT NOT NULL, LIGHT1017 TEXT NOT NULL," \
                  " LIGHT1018 TEXT NOT NULL, LIGHT1019 TEXT NOT NULL," \
                  " LIGHT1020 TEXT NOT NULL, LIGHT1021 TEXT NOT NULL," \
                  " LIGHT1022 TEXT NOT NULL, LIGHT1023 TEXT NOT NULL," \
                  " LIGHT1024 TEXT NOT NULL, LIGHT1025 TEXT NOT NULL," \
                  " LIGHT1026 TEXT NOT NULL, LIGHT1027 TEXT NOT NULL," \
                  " LIGHT1028 TEXT NOT NULL, LIGHT1029 TEXT NOT NULL," \
                  " LIGHT1030 TEXT NOT NULL, LIGHT1031 TEXT NOT NULL," \
                  " LIGHT1032 TEXT NOT NULL, LIGHT1033 TEXT NOT NULL," \
                  " LIGHT1034 TEXT NOT NULL, LIGHT1035 TEXT NOT NULL," \
                  " LIGHT1036 TEXT NOT NULL, LIGHT1037 TEXT NOT NULL," \
                  " LIGHT1038 TEXT NOT NULL, LIGHT1039 TEXT NOT NULL," \
                  " LIGHT1040 TEXT NOT NULL, LIGHT1041 TEXT NOT NULL," \
                  " LIGHT1042 TEXT NOT NULL, LIGHT1043 TEXT NOT NULL)"
            # 创建数据表
            cursor.execute(sql)
            result = cursor.fetchall()
            # 往数据表中写入数据
        except sqlite3.OperationalError as E:
            print(E)

    def action_input_file(self):
        """
        函数功能：导入文件
        :return:
        """

    def action_input_file_to_database(self):
        """
        函数功能：将文件导入到数据库中
        :return:
        """

    def action_call_normal_exit(self):
        """
        函数功能：退出本程序
        :return:
        """
        try:
            self.window.destroy()
            exit(0)
            print('exit successfully')
        except:
            print('exit failed')

    def action_input_information(self):
        """
        函数功能： 弹出一个对话框，提示输入病人的信息，并将其保存到数据库中，如果保存成功，着返回true,否则返回false
        :return: 成功->true 失败->false
        """

    def action_show_information(self):
        """
        函数功能：弹出一个对话框，显示病人信息
        :return: 成功->true 失败->false
        """

    def action_show_status_program(self):
        """
        函数功能：显示当前程序状态
        :return: 成功 ->true 失败 ->false
        """

    def action_clear_window(self):
        """
        函数功能：程序屏幕状态清除
        :return: 成功 ->true 失败 ->false
        """

    def action_self_check(self):
        """
        函数功能：程序自检，检测是否出现错误
        :return: 成功 ->true 失败 ->false
        """

    def action_exit(self):
        """
        函数功能：安全退出本程序
        :return: 成功->true 失败 ->false 并取消退出
        """

    def action_program_information(self):
        """
        函数功能：显示本程序信息
        :return:
        """

    def action_visit_website(self):
        """
        函数功能：访问程序官网
        :return:
        """

    def set_radiobutton_0(self):
        """
        函数功能：选择模型->mobilenet
        :return:
        """

    def set_radiobutton_1(self):
        """
        函数功能：选择模型->resnet50
        :return:
        """

    def set_radiobutton_2(self):
        """
        函数功能：选择模型->transformer
        :return:
        """

    def set_radiobutton_3(self):
        """
        函数功能：选择模型->vgg
        :return:
        """

    def set_radiobutton_4(self):
        """
        函数功能：选择模型->inception
        :return:
        """

    def start_01(self):
        """
        函数功能：启动拉曼光谱仪
        :return: 成功 ->true 失败 -> false
        """

    def close_01(self):
        """
        函数功能：关闭拉曼光谱仪
        :return:
        """

    def release_file(self):
        """
        函数功能：导出文件
        :return:
        """

    def adjust_01(self):
        """
        函数功能：调节波特率
        :return:
        """

    def start_02(self):
        """
        函数功能：启动激光器
        :return:
        """

    def close_02(self):
        """
        函数功能：关闭激光器
        :return:
        """

    def adjust_02(self):
        """
        函数功能：设定积分时间
        :return:
        """

    def adjust_03(self):
        """
        函数功能：设定激发波长
        :return:
        """

    def adjust_04(self):
        """
        函数功能：距离设定
        :return:
        """

    def choose_file(self):
        """
        函数功能：选择文件并识别
        :return:
        """

    def detect_online(self):
        """
        函数功能：一键检测
        :return:
        """

    def download_data(self):
        """
        函数功能：下载数据
        :return:
        """

    def set_radiobutton_01(self):
        """
        函数功能：离线模式
        :return:
        """

    def set_radiobutton_02(self):
        """
        函数功能：在线模式
        :return:
        """


class login(Frame):
    def __init__(self, master=None):
        # 由于Frame为父类，因此需要调用父类的构造器
        super().__init__(master)
        print('__init__mode :width=%d,height=%d' % (window_width, window_height))
        self.window = tk.Tk()  # 窗口
        self.window.title('登录到应用拉曼光谱的口腔癌诊断系统(build22714version3.0.0)')  # 窗口标题
        self.window_width = 600
        self.window_height = 150
        self.window.geometry(str(self.window_width) + 'x' + str(self.window_height))  # 加载时初始值
        self.window.bind('<Configure>', self.window_resize)
        self.create_widgets()  # 创建组件，在本方法中自定义组件
        self.master = master  # Frame构造器
        self.pack()  # 组件定位
        self.window.update()
        self.update()

    def window_resize(self, event=None):
        print('width=%d,height=%d' % (self.window.winfo_width(), self.window.winfo_height()))
        if event is not None:
            if self.window_width != self.window.winfo_width() or self.window_height != self.window.winfo_height():
                if self.window_width != self.window.winfo_width():
                    self.window_width = self.window.winfo_width()
                if self.window_height != self.window.winfo_height():
                    self.window_height = self.window.winfo_height()
                # 此处等率界面应当设定为不可调节窗口大小
                # 因此在此处进行长度，宽度的强制更改<强制更改可以使用withdraw,deiconify方法>
                print('new_width=%d,new_height=%d' % (self.window_width, self.window_height))
                print('width_outer=%d,height_outer=%d' % (window_width, window_height))
                self.window.update()
                self.reset()
                # self.create_widgets()
                # self.window.withdraw()
                # self.window.deiconify()
                self.create_widgets()
                # self.window.update()

    def reset(self):
        # 销毁当前页面所有部件
        try:
            self.window.grid_forget()
        except:
            print('reset failed')

    def create_widgets(self):
        """
        函数功能：绘制登录界面函数
        :return: 本函数没有返回值
        """
        label0 = tk.Label(self.window, text='用户名').place(x=50, y=30)
        label1 = tk.Label(self.window, text='密码').place(x=50, y=70)
        self.text0 = tk.Text(self.window, width=60, height=1)
        self.text0.place(x=100, y=30)
        self.text1 = tk.Text(self.window, width=60, height=1)
        self.text1.place(x=100, y=70)
        button0 = tk.Button(self.window, text='登录', width=20, height=1, command=self.login_sys).place(x=50, y=100)
        button1 = tk.Button(self.window, text='注册', width=20, height=1, command=self.register_sys).place(x=350, y=100)

    def login_sys(self):
        """
        函数功能：获取两个text文本框的内容，并与SQL数据库比对，如果比对成功，则进入主函数界面，如果比对失败，则没有任何操作
        :return:
        """
        user_account = self.text0.get(1.0, tk.END + "-1c")
        print(user_account)
        user_password = self.text1.get(1.0, tk.END + "-1c")
        print(user_password)
        if user_password == "" or user_account == "":
            messagebox.showinfo(title='错误', message='用户名或密码为空')
        else:
            # 此处链接数据库，进行登录用户名，密码匹配，如果成功，则进入主界面，如果失败，则弹窗报错
            """
            如果用户名密码无法匹配，则提示用户名或密码错误，如果匹配成功，则进入主程序界面
            """
            # 开始执行数据库操作
            conn = sqlite3.connect("account.db")
            cursor = conn.cursor()
            sql = "SELECT * from ACCOUNT_AND_PASSWORD WHERE ACCOUNT = '%s' AND PASSWORD='%s'" % (
            user_account, user_password)
            print(sql)
            print(cursor.execute(sql))
            result = cursor.fetchone()
            conn.commit()
            print(result)
            print(type(result))
            cursor.close()
            conn.close()
            if result == None:
                print('error')
                # 此处无需做任何操作
            else:
                print('success')
                # 此处链接主界面mainwindow
                self.window.destroy()
                MainWindow(self.master)
            # self.window.destroy()
            # MainWindow(self.master)

    def register_sys(self):
        """
        函数功能：进入注册界面，跳转到注册界面，执行完注册后，返回登录界面
        :return:
        """
        self.window.destroy()
        register(self.master)


class register(Frame):
    def __init__(self, master=None):
        # 由于Frame为父类，因此需要调用父类的构造器
        super().__init__(master)
        print('__init__mode :width=%d,height=%d' % (window_width, window_height))
        self.window = tk.Tk()  # 窗口
        self.window.title('登录到应用拉曼光谱的口腔癌诊断系统(build22714version3.0.0)')  # 窗口标题
        self.window_width = 600
        self.window_height = 200
        self.window.geometry(str(self.window_width) + 'x' + str(self.window_height))  # 加载时初始值
        self.window.bind('<Configure>', self.window_resize)
        self.create_widgets()  # 创建组件，在本方法中自定义组件
        self.master = master  # Frame构造器
        self.pack()  # 组件定位
        self.window.update()
        self.update()

    def window_resize(self, event=None):
        print('width=%d,height=%d' % (self.window.winfo_width(), self.window.winfo_height()))
        if event is not None:
            if self.window_width != self.window.winfo_width() or self.window_height != self.window.winfo_height():
                if self.window_width != self.window.winfo_width():
                    self.window_width = self.window.winfo_width()
                if self.window_height != self.window.winfo_height():
                    self.window_height = self.window.winfo_height()
                # 此处等率界面应当设定为不可调节窗口大小
                # 因此在此处进行长度，宽度的强制更改<强制更改可以使用withdraw,deiconify方法>
                print('new_width=%d,new_height=%d' % (self.window_width, self.window_height))
                print('width_outer=%d,height_outer=%d' % (window_width, window_height))
                self.window.update()
                self.reset()
                # self.create_widgets()
                # self.window.withdraw()
                # self.window.deiconify()
                self.create_widgets()
                # self.window.update()

    def reset(self):
        # 销毁当前页面所有部件
        try:
            self.window.grid_forget()
        except:
            print('reset failed')

    def create_widgets(self):
        """
        函数功能：绘制登录界面函数
        :return: 本函数没有返回值
        """
        label0 = tk.Label(self.window, text='用户名').place(x=50, y=30)
        label1 = tk.Label(self.window, text='密码').place(x=50, y=70)
        label2 = tk.Label(self.window, text='确认密码').place(x=50, y=110)
        self.text0 = tk.Text(self.window, width=60, height=1)
        self.text0.place(x=150, y=30)
        self.text1 = tk.Text(self.window, width=60, height=1)
        self.text1.place(x=150, y=70)
        self.text2 = tk.Text(self.window, width=60, height=1)
        self.text2.place(x=150, y=110)
        button0 = tk.Button(self.window, text='注册', width=70, height=1, command=self.login_sys).place(x=50, y=155)
        # button1=tk.Button(self.window,text='注册',width=20,height=1,command=self.register_sys).place(x=350,y=100)

    def login_sys(self):
        """
        函数功能：切换到登录界面
        :return:
        """
        # 此处链接数据库，并将数据保存
        account = self.text0.get(1.0, tk.END + "-1c")
        password0 = self.text1.get(1.0, tk.END + "-1c")
        password1 = self.text2.get(1.0, tk.END + "-1c")
        if password0 == password1:
            """
            密码第一次验证通过
            """
            if password0 == account:
                """
                用户名不能和密码相同
                """
                messagebox.showinfo(title='提示', message='用户名不能与密码相同')
            else:
                """
                在此处链接数据库
                """
                conn = sqlite3.connect("account.db")
                cursor = conn.cursor()
                try:
                    sql = "CREATE TABLE ACCOUNT_AND_PASSWORD(ACCOUNT TEXT PRIMARY KEY NOT NULL, PASSWORD TEXT NOT NULL)"
                    # 创建数据表
                    cursor.execute(sql)
                    result = cursor.fetchall()
                    # 往数据表中写入数据
                except sqlite3.OperationalError as E:
                    print(E)
                sql = "insert into ACCOUNT_AND_PASSWORD values('%s', '%s')" % (account, password0)
                print(sql)
                print(cursor.execute(sql))
                result = cursor.fetchall()
                conn.commit()
                # 往数据表中写入数据
                print(result)
                print(type(result))
                cursor.close()
                conn.close()
        else:
            """
            两次密码不一致
            """
            messagebox.showerror(title='错误', message='两次密码输入不一致')
        # 返回登录界面
        self.window.destroy()
        login(self.master)


if __name__ == '__main__':
    root = tk.Tk()
    app = login(master=root)
    app.mainloop()
