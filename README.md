

## 说明文档

### 前言：

​	本程序是以当下流行的**电商**为范本，基于**C/S框架**的简单模拟程序，其本身远不具有日常使用的能力和商业价值，但是可以当作一个简单的小项目来进行学习和了解其中的知识。

##### 	关于作者与程序来源：

​	作者为jlu的20级软件工程专业卓越工程师班的学生，本程序为本专业课程**《面向对象程序设计(荣誉课)》**的课程设计最终提交程序，写出来源的原因是为将来的卓班以及荣誉课同学在完成本门课程的学习过程中，可以通过本程序来为自己基础知识学习和程序设计和构建提供一定的思路。当然本程序也适合刚刚学习有关知识的编程者进行学习。

### 程序设计

- ##### 微商系统整体架构

​	本微商系统是基于传统C/S框架的程序，因此分为Client端与Server端，且支持多Client端，不支持多Server端。下图为整个程序的大致架构图。

![在这里插入图片描述](https://img-blog.csdnimg.cn/c22fab077dc44a9697a26a90abd04651.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA4oiGODg0,size_20,color_FFFFFF,t_70,g_se,x_16)

- ##### 微商系统的大致功能

  - ###### Client端

    登陆，注册 ，货物商品推荐，促销活动，客服信息，购物车操作，购买记录操作，聊天操作，商品搜索，搜索记录的记录与商品购买，除此之外还有其他附加小功能，会在报告中阐述。

  - ##### Server端

    包括了四大功能：货物综合操作，多人聊天室，活动添加，数据综合分析。每个功能中含有若干个小功能。在报告中有具体的阐述和解释。

- ##### 本程序设计的知识技术和学习路线以及大致规划

  1. 掌握Qt基础编程，包括内容：Qt语法，Qt界面设计,Qt各模块功能函数和API的调用,Qt socket编程，Qt 多线程编程。(默认掌握C++基础知识与语法，学习过面向对象编程)，**时间：10-15天。**

     - 推荐学习资料和视频：《Qt 5.9 C++开发指南》

     - **视频课程**：https://www.bilibili.com/video/BV1g4411H78N?from=search&seid=8225231499875477544&spm_id_from=333.337.0.0  (最新QT从入门到实战完整版|传智教育) -> 了解Qt基础编程方法[3-6天]

     - **视频课程**:   https://www.bilibili.com/video/BV1AX4y1w7Nt?from=search&seid=8225231499875477544&spm_id_from=333.337.0.0  (《Qt 5.9 C++开发指南》2021完整版)-> 完整学习Qt关于QWidget的编程 [8-12天]

     - B站上推荐的开源项目：Qt搭建的网易云客户端界面，主要是学习其界面设计技巧。

       **视频链接**：https://www.bilibili.com/video/BV1ZR4y1x7Qd?from=search&seid=9523622492950225238&spm_id_from=333.337.0.0 ，可以去跟着博客一步一步学习，gitee上的代码是可运行的，且注释完备，可以拿来做参考。

     - 多线程相关，线程池的使用，推荐博客：https://www.dushibaiyu.com/2013/12/qtcpserver%E5%A4%9A%E7%BA%BF%E7%A8%8B%E5%AE%9E%E7%8E%B0.html (讲述了每个Client分配一个线程的操作方法) 仓库：https://github.com/dushibaiyu/QtTcpThreadServer  (如何实现线程管理类，内置线程池，慢慢看，一定能看懂)

  2. 学习数据库方面内容

     - 简单了解数据库(这里选择的是mysql，网上有许多的博客来介绍数据库，直到了解其关键术语，基本使用方法即可)。[<1天]

     - 系统学习sql语句，具体为CRUD的实现。

       **推荐书籍**：《MySQL必知必会》，是一本小绿书。[2-3天]

     - 下载数据库图形界面操作工具，并简单了解该工具的使用方法，这里推荐Navicat，

       **安装教程推荐视频**：https://www.bilibili.com/video/BV1KU4y1F7r9?from=search&seid=350282803923686359&spm_id_from=333.337.0.0  (2021最新navicat15下载安装激活教程)[1天]

  3. 学习java相关内容

     本模块默认学习者已经具有oop基础。

     - 通过百度，google，各网站博客了解java语言，学习编译环境的搭建，学习相关编译器的使用，这里推荐intellij IDEA 2020，网上有专门的破解教程和安装方法。

     - 学习java基础语法，了解java特性和基本的设计思想

       **推荐文档教程**：https://www.runoob.com/java/java-tutorial.html [2-4天]

     - 学习IDEA的使用和配置

       **推荐课程**：https://www.bilibili.com/video/BV1PW411X75p?from=search&seid=7364802674378035162&spm_id_from=333.337.0.0[0.5-1天]

     - 基本了解maven依赖的配置，工程的创建和使用。

       **推荐课程**:https://www.bilibili.com/video/BV1Fz4y167p5?from=search&seid=5807386094391628435&spm_id_from=333.337.0.0[0.5天]，可以只看P7-P9部分。[0.5天]

     - 学习了解持久层的概念，学习常用持久层，进一步学习Mybatis框架。

       **推荐课程**：https://www.bilibili.com/video/BV1NE411Q7Nx?p=3[2-3天]

     - 学习了解spring框架，只需要了解spring的大致结构，xml文件的配置，**对Mybatis的整合**(为之后的Web服务做铺垫)。

       **推荐学习课程**:https://www.bilibili.com/video/BV1WE411d7Dv?from=search&seid=18254683001279879718&spm_id_from=333.337.0.0[1-2天]。

       本系列视频对于本程序的学习了解来说不需要看完，只需要看1-15和23-25即可。(学有余力可以全部看完)

  4. 学习Web服务(涉及多语言混合编程)

     1. 

        - 通过网上博客来了解整个Web服务的概念和基本使用方法，了解其与 TCP/IP(socket通信)的联系，可以加深对其的认知。

        - 通过博客学习java端如何发布普通Web服务，学习如何使用java自带Web服务根据soap协议解析xml文件，并在Test C端测试调用情况。

        - 学习如何用spring整合操作数据库的接口(基于Mybatis框架编写)后通过Web服务发布，并通过java端的Test程序尝试调用。

          **推荐的spring官方中文文档**：https://www.docs4dev.com/docs/zh/spring-framework/4.3.21.RELEASE/reference/remoting.html#remoting-web-services(从Web服务开始看)

        - 学习与C++配套的Web服务解析软件gsoap的使用，并通过gsoap解析之前发布的服务，生成相应的.h文件和.cpp文件，并尝试成功调用java端数据库的操作。[总共需要大概2-3天的时间]，

          **推荐博客教程**：https://blog.csdn.net/yyj108317/article/details/77094863?ops_request_misc=&request_id=&biz_id=102&utm_term=C++%E8%B0%83%E7%94%A8Qt%20%E4%BD%BF%E7%94%A8%20gsoap%20%E8%AE%BF%E9%97%AE%20webservice&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~sobaiduweb~default-0-77094863.pc_v2_rank_blog_default&spm=1018.2226.3001.4450(这是全网搜索到的唯一一个符合本程序要求的调用方法教程)

        ==本部分学习知识点和涉及的新技术和概念比较多，需要仔细学习与认真理解分析，在学习本模块的第三点和第四点时，可以先只学习使用方法，完成任务后，回过头来学习其中的机理和方法。==

  5. 尝试运行本程序

     编译器选择：

     1. Qt creator 5.14.2或者更高版本，不建议使用VS以及clion，如果用Qt6打开后，需要修改一些更新的API(应该没有多少)方可运行。
     2. java程序建议使用专业版 intellij IDEA 2020，本程序是在intellij IDEA 2021上搭建，但是2020更加方便使用，且插件齐全，java端程序使用了lombok插件，需要在插件添加处自行下载和配置(网上有教程IDEA 2020可以直接下载，IDEA 2021需要去官网下载并修改一些参数)。

     编译环境选择：

     1. C++采用winGW(64位)编译器，java采用的是 jdk1.8环境，请自行配置，本文档不再过多叙述配置方面的问题。
     2. 数据库下载最新的即可，应该没有太大问题，导入数据表可以通过navicat进行导入，网上有具体教程，不在过多推荐。

### 程序运行界面

下面大致展示程序运行界面

### 1.1.1 客户端主页面

前面已经展示了登录窗口的界面设计，现在展示在登录成功后的客户端主页面。以及各项功能。

l 客户端推荐页面：

![在这里插入图片描述](https://img-blog.csdnimg.cn/ef375ddf9ed4467e8bf737141fa71dab.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA4oiGODg0,size_20,color_FFFFFF,t_70,g_se,x_16)

图 1 推荐商品界面

在这个界面上我们可以进行多功能化的跳转，整个界面采用白色为主基调，做到尽量简约和操作简便的效果。上栏是微商标志，左右箭头循环跳转，头像，关于，VIP设置(未实现)，换肤色，修改用户的基本信息，最小化，关闭的功能。

l 促销互动界面

![在这里插入图片描述](https://img-blog.csdnimg.cn/7eb69cb608f3406994a11c90d1e440c6.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA4oiGODg0,size_20,color_FFFFFF,t_70,g_se,x_16)

图 2 促销活动界面

促销活动大部分为打折物品，当打折物品没有那么多的时候将非打折物品进行补充。

l 客服消息界面

![在这里插入图片描述](https://img-blog.csdnimg.cn/6f624c9821da4b889e1c4c11f7d4004e.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA4oiGODg0,size_20,color_FFFFFF,t_70,g_se,x_16)

图 3 客服消息界面

客户消息界面主要负责与客服进行通信，客服端是多聊天窗口程序。

l 购物车界面：

![在这里插入图片描述](https://img-blog.csdnimg.cn/b8a6c1f8230d471f8354f2087505cfde.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA4oiGODg0,size_20,color_FFFFFF,t_70,g_se,x_16)

图 4 购物车界面

主要负责购物车的选购，统一结算和删除功能。

l 购买记录(历史信息)功能

 

![在这里插入图片描述](https://img-blog.csdnimg.cn/2f6ed1acee834b689be9f3c3abc40263.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA4oiGODg0,size_20,color_FFFFFF,t_70,g_se,x_16)

图 5 购买记录方面

与购物车相似可以进行退货功能和删除功能。

l 搜索记录显示

![在这里插入图片描述](https://img-blog.csdnimg.cn/1fcd7c92d8af444f8d55d461d19ba7ef.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA4oiGODg0,size_20,color_FFFFFF,t_70,g_se,x_16)

图 6 搜索记录与购买界面

可以进行单商品的单独购买和记录保存功能，可以删除搜索记录，或是一直保留。

l 商品搜索功能

![在这里插入图片描述](https://img-blog.csdnimg.cn/a891dc832b194e3396aeec27204e6683.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA4oiGODg0,size_20,color_FFFFFF,t_70,g_se,x_16)

图 7 商品搜索功能

l 换肤功能和版本信息功能

![在这里插入图片描述](https://img-blog.csdnimg.cn/9b61c204c4764cd098a9dc399df6908e.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA4oiGODg0,size_20,color_FFFFFF,t_70,g_se,x_16)

图 11 版本信息显示

![在这里插入图片描述](https://img-blog.csdnimg.cn/155fee9751094c2ca6622d5bb0114143.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA4oiGODg0,size_20,color_FFFFFF,t_70,g_se,x_16)

图 8 换肤功能

这两项是对客户端的补充和美化，可以选择六种颜色，并且查看当前版本信息。

l 用户信息修改功能

![在这里插入图片描述](https://img-blog.csdnimg.cn/779c0ec5b8484e5f9d5c03e612645541.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA4oiGODg0,size_20,color_FFFFFF,t_70,g_se,x_16)

图 9 用户信息修改功能

右下角的锁打开前，所有信息被锁定，锁打开后，整个用户信息可以开始修改编辑，由于用户姓名是非常关键的信息，所以不给予修改权限。

修改完毕后关锁保存，上方在接受服务端发来的更新成功后，弹出提示。

### 1.1.2 服务端UI设计和实现

l 货物综合处理

n 货物的查询界面：

![在这里插入图片描述](https://img-blog.csdnimg.cn/c21cf4c77b494f48b7197230607fd0b3.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA4oiGODg0,size_20,color_FFFFFF,t_70,g_se,x_16)

图 10 货物的查询

通过下拉框可以给予搜索提示，然后点击放大镜按钮后，可以进行搜索。

n 删除界面：

![在这里插入图片描述](https://img-blog.csdnimg.cn/040387bd7fc7465cb2db3acf17cdb9ad.gif)

图 11 删除界面

可以通过搜索对商品进行删除，右键点击商品，会出现删除效果。

n 商品添加功能

![在这里插入图片描述](https://img-blog.csdnimg.cn/8d987a909d434912bc4635be10ab24f9.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA4oiGODg0,size_20,color_FFFFFF,t_70,g_se,x_16)

图 12 商品添加界面

在本页面中，可以进行商品的添加和修改，并在点击添加后，弹出添加成功操作符。

l 与用户多人聊天功能

![在这里插入图片描述](https://img-blog.csdnimg.cn/207b955adb824a729b5627fb0b3cbed8.gif)

图 13 多人分时聊天功能

一个客服可以转接多个用户，与每个用户聊天，在聊天过程中，可以任意的删除在线或不在线的用户聊天框，当该用户登陆后或者重发消息后，又会进行聊天室的创建。

l 活动功能

![在这里插入图片描述](https://img-blog.csdnimg.cn/7934edd8d3b341a4a3d42f6e7f672593.gif)

图 14 活动打折添加界面

在本页面可以自由添加活动的力度，及折数，然后对应着显示到优惠产品栏中。可以在优惠栏中进行随意的删除。然后点击右上角的刷新，会刷新优惠产品栏中的所有商品信息。

l 数据综合分析模块

n 表格综合信息如下：

![在这里插入图片描述](https://img-blog.csdnimg.cn/ce09b1de9eb640e08a3fd9a29eb6dffe.gif)

图 15 数据分析表格形式

在本页面可以进行表格和页面的拖拽，实现最大化的阅读体验。

n 图表分析功能

![img](https://img-blog.csdnimg.cn/e4c516867a364e98a54e1d123e605864.gif)

图 16 微商购物的数据分析功能

在此页面上可以通过选择分析对象，分析特定查找对象，分析分析全部对象，选择分析区间，进行分析，然后根据数据的综合处理自动生成图表，显示在右侧，且右侧的图标可以拖动以达到图表的放大和缩小功能。



