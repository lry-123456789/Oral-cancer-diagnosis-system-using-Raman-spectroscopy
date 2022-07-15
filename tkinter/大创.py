import tkinter as tk
import tkinter.ttk
global root_width
global root_height
global root
global login
global register
root=tk.Tk()
def show_main():
    root.title('应用拉曼光谱的口腔癌诊断系统(build22712version 2.0.0)')
    root.geometry('1200x600')
    root.update()
    root_height=root.winfo_height()
    root_width=root.winfo_width()
    print("width=%d,height=%d"%(root_width,root_height))
    #上述为窗口的创建
    #下面开始绘制菜单
    menubar=tk.Menu(root)
    #root.config(menu=menubar)
    #开始定义一个空的菜单单元
    menu0=tk.Menu(menubar)
    menubar.add_cascade(label='文件',menu=menu0)
    menu0.add_command(label='导出数据',command=lambda: do_nothing(0))
    menu0.add_command(label='导出文件所有信息',command=lambda: do_nothing(1))
    menu0.add_separator()
    menu0.add_command(label='导入文件',command=lambda: do_nothing(2))
    menu0.add_command(label='导入文件至数据库',command=lambda: do_nothing(3))
    menu0.add_separator()
    menu0.add_command(label='退出本程序',command=lambda: do_nothing(4))
    menu1=tk.Menu(menubar)
    menubar.add_cascade(label='病人信息管理',menu=menu1)
    menu1.add_command(label='导入病人信息',command=lambda: do_nothing(5))
    menu1.add_command(label='显示病人信息',command=lambda: do_nothing(6))
    menu2=tk.Menu(menubar)
    menubar.add_cascade(label='程序高级控制',menu=menu2)
    menu2.add_command(label='显示目前程序参数状态',command=lambda: do_nothing(7))
    menu2.add_separator()
    menu2.add_command(label='程序屏幕状态清除',command=lambda: do_nothing(8))
    menu2.add_command(label='程序功能自检',command=lambda: do_nothing(9))
    menu2.add_separator()
    menu2.add_command(label='退出',command=lambda: do_nothing(10))
    menu3=tk.Menu(menubar)
    menubar.add_cascade(label='关于',menu=menu3)
    menu3.add_command(label='程序信息',command=lambda: do_nothing(11))
    menu3.add_command(label='程序官网',command=lambda: do_nothing(12))
    # 上方为菜单栏显示部分
    # 下方为主界面内容
    # 显示框架
    group0= tk.LabelFrame(root,text='拉曼光谱显示区域',padx=10,pady=10)
    group0.place(x=10,y=10)
    group0_text0=tk.Text(group0,height=30,width=78).pack(anchor='center')
    group1= tk.LabelFrame(root,text='程序状态消息',padx=10,pady=10)
    group1.place(x=10,y=445)
    group1_text0=tk.Text(group1,height=7,width=78).pack(anchor='center')
    group2=tk.LabelFrame(root,text='检测结果',padx=10,pady=10,width=600,height=200)
    group2_radiobutton0=tk.Radiobutton(group2,text='正常组织').place(x=10,y=10)
    group2_radiobutton1=tk.Radiobutton(group2,text='舌癌').place(x=150,y=10)
    group2_radiobutton2=tk.Radiobutton(group2,text='颊癌').place(x=300,y=10)
    group2_radiobutton3=tk.Radiobutton(group2,text='牙龈癌').place(x=450,y=10)
    group2_progressbar0 = tk.ttk.Progressbar(group2,orient=tkinter.VERTICAL).place(x=30,y=50)
    group2_progressbar1 = tk.ttk.Progressbar(group2,orient=tkinter.VERTICAL).place(x=180,y=50)
    group2_progressbar2 = tk.ttk.Progressbar(group2,orient=tkinter.VERTICAL).place(x=330,y=50)
    group2_progressbar3 = tk.ttk.Progressbar(group2,orient=tkinter.VERTICAL).place(x=480,y=50)
    group2.place(x=600,y=10)
    group3=tk.LabelFrame(root,text='控制部分',padx=10,pady=10,width=600,height=360)
    group3_group0=tk.LabelFrame(group3,text='模型选择',padx=10,pady=10,width=580,height=100)
    group3_group0_radiobutton0=tk.Radiobutton(group3_group0,text='mobilenet').place(x=20,y=15)
    group3_group0_radiobutton1=tk.Radiobutton(group3_group0,text='resnet50').place(x=120,y=15)
    group3_group0_radiobutton2=tk.Radiobutton(group3_group0,text='transformer').place(x=220,y=15)
    group3_group0_radiobutton3=tk.Radiobutton(group3_group0,text='vgg').place(x=320,y=15)
    group3_group0_radiobutton4=tk.Radiobutton(group3_group0,text='inception').place(x=420,y=15)
    group3_group0.place(x=0,y=0)
    group3_group1=tk.LabelFrame(group3,text='外部设备控制',padx=10,pady=10,width=580,height=150)
    group3_group1.place(x=0,y=100)
    group3_group1_group0=tk.LabelFrame(group3_group1,text='拉曼光谱仪控制部分',padx=10,pady=10,width=560,height=50)
    group3_group1_group0_Button0=tk.Button(group3_group1_group0,text='启动',width=8,height=1).place(x=10,y=-10)
    group3_group1_group0_Button1=tk.Button(group3_group1_group0,text='关闭',width=8,height=1).place(x=160,y=-10)
    group3_group1_group0_Button2=tk.Button(group3_group1_group0,text='导出文件',width=8,height=1).place(x=310,y=-10)
    group3_group1_group0_Button3=tk.Button(group3_group1_group0,text='波特率调节',width=8,height=1).place(x=460,y=-10)
    group3_group1_group0.place(x=0,y=0)
    group3_group1_group1=tk.LabelFrame(group3_group1,text='激光器控制部分',padx=10,pady=10,width=560,height=50)
    group3_group1_group1_Button0=tk.Button(group3_group1_group1,text='启动',width=8,height=1).place(x=10,y=-10)
    group3_group1_group1_Button1=tk.Button(group3_group1_group1,text='关闭',width=8,height=1).place(x=110,y=-10)
    group3_group1_group1_Button2=tk.Button(group3_group1_group1,text='积分时间设定',width=10,height=1).place(x=210,y=-10)
    group3_group1_group1_Button3=tk.Button(group3_group1_group1,text='激发波长设定',width=10,height=1).place(x=330,y=-10)
    group3_group1_group1_Button4=tk.Button(group3_group1_group1,text='距离设定',width=10,height=1).place(x=450,y=-10)
    group3_group1_group1.place(x=0,y=60)
    group3_group2=tk.LabelFrame(group3,text='主程序控制',padx=10,pady=10,width=580,height=70)
    '''
    group3_group2_group0=tk.LabelFrame(group3_group2,text='离线模式',padx=5,pady=5,width=100,height=40)
    group3_group2_group0_Button0=tk.Button(group3_group2_group0,text='选择文件并识别',width=12,height=1).place(x=0,y=-10)
    group3_group2_group0.place(x=0,y=-10)
    '''
    group3_group2_Button0=tk.Button(group3_group2,text='选择文件并识别(离线)',width=16,height=1).place(x=0,y=-10)
    group3_group2_Button1=tk.Button(group3_group2,text='一键检测(在线)',width=10,height=1).place(x=140,y=-10)
    group3_group2_Button2=tk.Button(group3_group2,text='下载数据(在线)',width=10,height=1).place(x=280,y=-10)
    group3_group2_RadioButton0=tk.ttk.Radiobutton(group3_group2,text='离线模式').place(x=420,y=-10)
    group3_group2_RadioButton1=tk.ttk.Radiobutton(group3_group2,text='在线模式').place(x=420,y=10)
    group3_group2.place(x=0,y=250)
    group3.place(x=600,y=220)
    root.config(menu=menubar)
    root.mainloop()

def show_login():
    # do any thing here
    print('start login ...')

def show_register():
    # do any thing here
    print('start register...')

def show_input_information():
    # do any thing here
    print('start input information...')

def do_nothing(a):
    print("do nothing")
    if a==11:
        root.withdraw()
        root.deiconify()
    if a==12:
        root.destroy()
        print("1234567890")


if __name__=='__main__':
    #show_login()
    show_main()
