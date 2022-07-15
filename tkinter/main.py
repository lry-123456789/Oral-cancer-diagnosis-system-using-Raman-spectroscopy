import tkinter as tk
import tkinter.ttk
from tkinter import *
from tkinter import messagebox

global start ,window_width,window_height
start =0
if start ==0:
    print('use default options')
    window_width=1200
    window_height=600
else :
    print('user other options')


class MainWindow(Frame):
    def __init__(self,master=None):
        # 由于Frame为父类，因此需要调用父类的构造器
        super().__init__(master)
        print('__init__mode :width=%d,height=%d'%(window_width,window_height))
        self.value0=tk.IntVar()      # 第一个界面参数
        self.value0.set(5)           # 初始化第一个界面参数
        self.value1=tk.IntVar()      # 第二个界面参数
        self.value1.set(6)           # 初始化第二个界面参数
        self.value2=tk.IntVar()      # 第三个界面参数
        self.value2.set(3)           # 初始化第三个界面参数
        self.start=start             # 判断是否需要初始化
        self.progressbar0=25         # 初始化progressbar0的值
        self.progressbar1=25         # 初始化progressbar1的值
        self.progressbar2=25         # 初始化progressbar2的值
        self.progressbar3=25         # 初始化progressbar3的值
        self.window=tk.Tk()     # 窗口
        self.menubar=tk.Menu(self.window)
        self.window.title('应用拉曼光谱的口腔癌诊断系统(build22714version3.0.0)') # 窗口标题
        self.window_width=window_width
        self.window_height=window_height
        self.window.geometry(str(self.window_width)+'x'+str(self.window_height))        # 加载时初始值
        self.window.bind('<Configure>',self.window_resize)
        self.create_menu()      #创建目录
        self.create_widgets()  # 创建组件，在本方法中自定义组件
        self.window.config(menu=self.menubar)
        self.master = master      # Frame构造器
        self.pack()               # 组件定位
        self.window.update()
        self.update()

    def window_resize(self,event=None):
        print('width=%d,height=%d'%(self.window.winfo_width(),self.window.winfo_height()))
        if event is not None:
            if self.window_width != self.window.winfo_width() or self.window_height != self.window.winfo_height():
                if self.window_width != self.window.winfo_width():
                    self.window_width = self.window.winfo_width()
                if self.window_height != self.window.winfo_height():
                    self.window_height = self.window.winfo_height()
                print('new_width=%d,new_height=%d'%(self.window_width,self.window_height))
                global window_height,window_width,start
                window_width=self.window_width
                window_height=self.window_height
                print('width_outer=%d,height_outer=%d'%(window_width,window_height))
                start=start+1
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
        except :
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
        group0=tk.LabelFrame(self.window,text='拉曼光谱显示区域',padx=10,pady=10)
        # 放置一个文本框，可以用于显示图片
        group0_text0=tk.Text(group0,height=30*self.window_height//600,width=78*self.window_width//1200).pack(anchor='center')
        group0.place(x=10*self.window_width//1200,y=10*self.window_height//1200)
        # 文本框放置完成
        # 下面为显示程序状态消息
        group1=tk.LabelFrame(self.window,text='程序状态消息',padx=10,pady=10)
        group1_text0=tk.Text(group1,height=7*self.window_height//600,width=78*self.window_width//1200).pack(anchor='center')
        group1.place(x=10*self.window_width//1200,y=445*self.window_height//600)
        # 程序状态消息显示完成
        # 下面为检测结果显示区域
        group2=tk.LabelFrame(self.window,text='检测结果',padx=10,pady=10,width=600*self.window_width//1200,height=200*self.window_height//600)
        group2_radiobutton0=tk.Radiobutton(group2,text='正常组织',variable=self.value0,value=1).place(x=10*self.window_width//1200,y=10*self.window_height//600)
        group2_radiobutton1=tk.Radiobutton(group2,text='舌癌',variable=self.value0,value=2).place(x=150*self.window_width//1200,y=10*self.window_height//600)
        group2_radiobutton2=tk.Radiobutton(group2,text='颊癌',variable=self.value0,value=3).place(x=300*self.window_width//1200,y=10*self.window_height//600)
        group2_radiobutton3=tk.Radiobutton(group2,text='牙龈癌',variable=self.value0,value=4).place(x=450*self.window_width//1200,y=10*self.window_height//600)
        group2_progressbar0=tkinter.ttk.Progressbar(group2,orient=tkinter.VERTICAL,length=100,value=self.progressbar0).place(x=30*self.window_width//1200,y=50*self.window_height//600)
        group2_progressbar1=tkinter.ttk.Progressbar(group2,orient=tkinter.VERTICAL,length=100,value=self.progressbar1).place(x=180*self.window_width//1200,y=50*self.window_height//600)
        group2_progressbar2=tkinter.ttk.Progressbar(group2,orient=tkinter.VERTICAL,length=100,value=self.progressbar2).place(x=330*self.window_width//1200,y=50*self.window_height//600)
        group2_progressbar3=tkinter.ttk.Progressbar(group2,orient=tkinter.VERTICAL,length=100,value=self.progressbar3).place(x=480*self.window_width//1200,y=50*self.window_height//600)
        group2.place(x=600*self.window_width//1200,y=10*self.window_height//600)
        # 检测结果显示区域放置完成
        # 下方为控制部分
        # 控制部分的第一个模块 -> 模型选择
        group3=tk.LabelFrame(self.window,text='控制部分',padx=10,pady=10,width=600*self.window_width//1200,height=360*self.window_height//600)
        group3_group0=tk.LabelFrame(group3,text='模型选择',padx=10,pady=10,width=580*self.window_width//1200,height=100*self.window_height//600)
        group3_group0_radiobutton0=tk.Radiobutton(group3_group0,text='mobilenet',variable=self.value1,value=1,command=self.set_radiobutton_0).place(x=20*self.window_width//1200,y=15*self.window_height//600)
        group3_group0_radiobutton1=tk.Radiobutton(group3_group0,text='resnet50',variable=self.value1,value=2,command=self.set_radiobutton_1).place(x=120*self.window_width//1200,y=15*self.window_height//600)
        group3_group0_radiobutton2=tk.Radiobutton(group3_group0,text='transformer',variable=self.value1,value=3,command=self.set_radiobutton_2).place(x=220*self.window_width//1200,y=15*self.window_height//600)
        group3_group0_radiobutton3=tk.Radiobutton(group3_group0,text='vgg',variable=self.value1,value=4,command=self.set_radiobutton_3).place(x=320*self.window_width//1200,y=15*self.window_height//600)
        group3_group0_radiobutton4=tk.Radiobutton(group3_group0,text='inception',variable=self.value1,value=5,command=self.set_radiobutton_4).place(x=420*self.window_width//1200,y=15*self.window_height//600)
        # 开始放置第一个模块 -> 模型选择
        group3_group0.place(x=0*self.window_width//1200,y=0*self.window_height//600)
        # 开始放置第二个模块 -> 外部设备控制
        group3_group1=tk.LabelFrame(group3,text='外部设备控制',padx=10,pady=10,width=580*self.window_width//1200,height=150*self.window_height//600)
        group3_group1_group0=tk.LabelFrame(group3_group1,text='拉曼光谱仪控制部分',padx=10,pady=10,width=560*self.window_width//1200,height=50*self.window_height//600)
        group3_group1_group0_button0=tk.Button(group3_group1_group0, text='启动', width=8*self.window_width//1200, height=1*self.window_height//600, command=self.start_01).place(x=10 * self.window_width // 1200, y=-10 * self.window_height // 600)
        group3_group1_group0_button1=tk.Button(group3_group1_group0,text='关闭',width=8*self.window_width//1200,height=1*self.window_height//600,command=self.close_01).place(x=160*self.window_width//1200,y=-10*self.window_height//600)
        group3_group1_group0_button2=tk.Button(group3_group1_group0,text='导出文件',width=8*self.window_width//1200,height=1*self.window_height//600,command=self.release_file).place(x=310*self.window_width//1200,y=-10*self.window_height//600)
        group3_group1_group0_button3=tk.Button(group3_group1_group0,text='波特率调节',width=8*self.window_width//1200,height=1*self.window_height//600,command=self.adjust_01).place(x=460*self.window_width//1200,y=-10*self.window_height//600)
        # 开始放置外部设备控制模块中的第一个子模块 -> 拉曼光谱仪控制部分
        group3_group1_group0.place(x=0*self.window_width//1200,y=0*self.window_height//600)
        # 第一个子模块放置完成 -> 拉曼光谱仪控制部分
        # 开始放置第二个子模块 -> 激光器控制部分
        group3_group1_group1=tk.LabelFrame(group3_group1,text='激光器控制部分',width=560*self.window_width//1200,height=50*self.window_height//600)
        group3_group1_group1_button0=tk.Button(group3_group1_group1,text='启动',width=8*self.window_width//1200,height=1*self.window_height//600,command=self.start_02).place(x=10*self.window_width//1200,y=-5*self.window_height//600)
        group3_group1_group1_button1=tk.Button(group3_group1_group1,text='关闭',width=8*self.window_width//1200,height=1*self.window_height//600,command=self.close_02).place(x=110*self.window_width//1200,y=-5*self.window_height//600)
        group3_group1_group1_button2=tk.Button(group3_group1_group1,text='积分时间设定',width=8*self.window_width//1200,height=1*self.window_height//600,command=self.adjust_02).place(x=210*self.window_width//1200,y=-5*self.window_height//600)
        group3_group1_group1_button3=tk.Button(group3_group1_group1,text='激发波长设定',width=10*self.window_width//1200,height=1*self.window_height//600,command=self.adjust_03).place(x=330*self.window_width//1200,y=-5*self.window_height//600)
        group3_group1_group1_button4=tk.Button(group3_group1_group1,text='距离设定',width=10*self.window_width//1200,height=1*self.window_height//600,command=self.adjust_04).place(x=450*self.window_width//1200,y=-5*self.window_height//600)
        # 开始放置外部设备控制模块中的第二个子模块 -> 激光器控制部分
        group3_group1_group1.place(x=0*self.window_width//1200,y=60*self.window_height//600)
        group3_group1.place(x=0*self.window_width//1200,y=100*self.window_height//600)
        # 开始放置第三个模块 -> 主程序控制部分
        group3_group2=tk.LabelFrame(group3,text='主程序控制',padx=10,pady=10,width=580*self.window_width//1200,height=70*self.window_height//600)
        group3_group2_button0=tk.Button(group3_group2,text='选择文件并识别',width=16*self.window_width//1200,height=1*self.window_height//600,command=self.choose_file).place(x=0*self.window_width//1200,y=-10*self.window_height//600)
        group3_group2_button1=tk.Button(group3_group2,text='一键检测（在线）',width=10*self.window_width//1200,height=1*self.window_height//600,command=self.detect_online).place(x=140*self.window_width//1200,y=-10*self.window_height//600)
        group3_group2_button2=tk.Button(group3_group2,text='下载数据（在线）',width=10*self.window_width//1200,height=1*self.window_height//600,command=self.download_data).place(x=280*self.window_width//1200,y=-10*self.window_height//600)
        group3_group2_radioButton0=tk.ttk.Radiobutton(group3_group2,text='离线模式',variable=self.value2,value=1,command=self.set_radiobutton_01).place(x=420*self.window_width//1200,y=-10*self.window_height//600)
        group3_group2_radioButton1=tk.ttk.Radiobutton(group3_group2,text='在线模式',variable=self.value2,value=2,command=self.set_radiobutton_02).place(x=420*self.window_width//1200,y=-10*self.window_height//600)
        group3_group2.place(x=0*self.window_width//1200,y=250*self.window_height//600)
        group3.place(x=600*self.window_width//1200,y=220*self.window_height//600)

    def action_save_data_normal(self):
        """
        函数功能：导出数据
        :return: True ->导出成功 False ->导出失败
        """

    def action_save_all_data(self):
        """
        函数功能：导出文件所有信息
        :return: True -> 导出信息成功 False ->导出信息失败
        """

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
        except :
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

if __name__=='__main__':
    root=tk.Tk()
    app=MainWindow(master=root)
    app.mainloop()
