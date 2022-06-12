# **项目信息介绍**

## **项目名称：荒野乱斗**

## **项目成员：孙亦菲2152085，汪乘羽2153000**

## **成员贡献比例：孙亦菲50%：汪乘羽50%**

## **项目GitHub地址：**https://github.com/guangnianyuji/BrawlStars.git

## **项目进度时间线：**

| 4.30 | 创建项目                                                     |
| ---- | :----------------------------------------------------------- |
| 5.2  | 学习git、cocos2dx 有关知识，环境搭建                         |
| 5.10 | 完成开始游戏场景                                             |
| 5.11 | 完成背景音乐相关的菜单功能                                   |
| 5.15 | 完成移动摇杆的设计                                           |
| 5.22 | 完成第一张地图设计，英雄移动，播放行走动画，视野随玩家移动的功能 |
| 5.26 | 完成向所有实体类增添血条，初步尝试添加碰撞监听               |
| 5.28 | 完成普攻摇杆、大招摇杆                                       |
| 5.29 | 完成创建房间场景，切换场景                                   |
| 5.30 | 放置AI在地图上                                               |
| 5.31 | 添加毒雾效果                                                 |
| 6.3  | 完成宝箱                                                     |
| 6.4  | 完成暂停游戏功能                                             |
| 6.5  | 尝试写AI功能                                                 |
| 6.10 | 添加幸存者人数标签，选择地图功能，结算界面功能               |
| 6.11 | 完成AI，完成项目文档，完成答辩PPT                            |

# **项目开发文档**

## **游戏整体架构设计**

![c1](https://github.com/guangnianyuji/BrawlStars/blob/main/Image/c1.png?raw=true)

![c2](https://github.com/guangnianyuji/BrawlStars/blob/main/Image/c2.png?raw=true)

![c3](https://github.com/guangnianyuji/BrawlStars/blob/main/Image/c3.png?raw=true)

## **小组分工**

| 组员   | 完成项                                                       |
| ------ | ------------------------------------------------------------ |
| 孙亦菲 | 地图素材制作，创建房间，走动摇杆设计，人物走动动画制作，毒雾，宝箱，暂停及恢复功能，选择地图功能 |
| 汪乘羽 | 人物技能设计，攻击大招特效，菜单，背景音乐控制，AI（有限状态机），攻击摇杆设计 |

## **实现的功能点：**

### **基本功能：**

- [x] 游戏开始界面

- [x] 背景音乐

- [x] 音量控制

- [x] 暂停与恢复功能

- [x] 退出功能

- [x] 至少设计一张荒野乱斗地图

- [x] 添加能量宝箱，宝箱能给英雄增加生命值和伤害值

- [x] 至少设计4个英雄，不同英雄普通攻击和超级技能不同

- [x] 普攻可以积累大招

- [x] 支持创建房间

- [x] 键盘控制人物走动操作

- [x] 鼠标控制人物进行普通攻击和超级技能

- [x] 支持添加AI

- [x] 随着时间流逝，地图边缘出现毒圈

- [x] 最终存活的玩家为吃鸡者

- [x] 不同名次获得奖杯不同

### **新开发功能：**

- [x] 支持移动摇杆控制玩家行走（任意角度走动）

- [x] 支持攻击摇杆控制玩家发射技能

- [x] 自由选择地图

- [x] 攻击、大招特效

### **技术难点：**

1、为了便于维护AI的逻辑，选择FSM（有限状态机）设计AI，不主动在update函数里检测AI的状态，利用消息驱动实现AI状态的切换，设计了一个类“NotifyUtil"，以满足本游戏额外的需求，实现事件驱动的功能。

2、cocos封装的chipmunk物理引擎有一定缺陷，将英雄和墙壁都设置成静态刚体较符合正常逻辑，但无法使用碰撞检测。因此为了避免穿透墙壁和障碍物，用检查坐标的方式重新封装了障碍物类的碰撞检测。

 

 

### **加分项和亮点：**

1、脱离了荒野乱斗英雄普攻都是发射子弹的限制，添加了范围攻击（如喷泉攻击，闪电攻击，蝙蝠攻击，迷雾攻击等），每次普攻和大招都有精美动画。

 

2、使用摇杆、攻击使行走更自由顺畅，与荒野乱斗游戏还原度高。

 

3、自行绘制的原创地图和画风一致的精美UI。

 

4、物理引擎的使用。各个物体之间的碰撞消息均由物理引擎发出，而在障碍物上又通过自主设计碰撞算法解决了问题。

 

5、AI的有限状态机的使用，利用消息驱动实现AI状态的切换。

 

### **C++11新特性：**

#### lambda表达式：

![img](file:///D:\Temp\Temp\ksohtml63980\wps24.jpg) 

 

#### std::function

![img](file:///D:\Temp\Temp\ksohtml63980\wps25.jpg) 

#### 基于范围的for循环

 

![img](file:///D:\Temp\Temp\ksohtml63980\wps26.jpg) 

 

 

#### auto 类型推断

项目几乎处处使用

 

 

### **游戏截图**

![](https://github.com/guangnianyuji/BrawlStars/blob/main/Image/p1.png?raw=true) 

![](https://github.com/guangnianyuji/BrawlStars/blob/main/Image/p2.png?raw=true)

![](https://github.com/guangnianyuji/BrawlStars/blob/main/Image/p3.png?raw=true)

![](https://github.com/guangnianyuji/BrawlStars/blob/main/Image/p4.png?raw=true)

# 游戏玩法

## 游戏简介

**Brawl Stars**是一款战术技能类沙盒游戏，玩家选择角色，躲避毒雾，并与地图里的所有敌人进行一场魔法乱斗。winner winner, chicken dinner!

## 游戏玩法

1.  每局最多10名英雄参与，玩家单机游戏，可以选择AI数量，最少一名AI与玩家战斗。
2. 摧毁宝箱，可提升攻击力和生命值。
3. 地图周围会有不断扩大的毒雾，身处毒雾范围内将持续不断的失去生命值。
4. 身处不断缩小的安全区域中，淘汰其他英雄，生存排名越高则得到奖杯越多。
5. 有四名角色供玩家为自己和AI挑选，不同角色技能不同

## 角色介绍

### 菲

![](https://github.com/guangnianyuji/BrawlStars/blob/main/Image/Ff1.png?raw=true)

​	移动速度 = 25.0
​	初始血量= 3640.0

普攻：发射三个火花（遇障碍物消失）。伤害= 56.0（每个火花）；范围 = 200;CD=0.5s;

<img src="https://github.com/guangnianyuji/BrawlStars/blob/main/Image/F_11.png?raw=true" style="zoom: 50%;" />

大招：发射三簇火树银花（遇障碍物不消失）。伤害=75.0（每簇火树银花）；普攻累计次数积累一次=20；持续时间=18s;CD=0.8s;

![](https://github.com/guangnianyuji/BrawlStars/blob/main/Image/FAce(1).png?raw=true)

### 羽

![](https://github.com/guangnianyuji/BrawlStars/blob/main/Image/Yf1.png?raw=true)

移动速度 = 20.0
初始血量= 3780.0

普攻：发射一束水泉（）。伤害=200.0；范围 = 150;CD=0.6s;

<img src="https://github.com/guangnianyuji/BrawlStars/blob/main/Image/Y_02.png?raw=true" style="zoom: 80%;" />

大招：添加保护罩免疫所有伤害。普攻累计次数积累一次=18；持续时间=15s;CD=20s;

<img src="https://github.com/guangnianyuji/BrawlStars/blob/main/Image/1.png?raw=true" style="zoom: 67%;" />

### 怪盗基德

![](https://github.com/guangnianyuji/BrawlStars/blob/main/Image/Jf1.png?raw=true)

移动速度 = 32.0
初始血量= 3360.0

普攻：发射怪盗蝙蝠。伤害=122.0；范围 = 500;CD=0.3s;

![](https://github.com/guangnianyuji/BrawlStars/blob/main/Image/J_01.png?raw=true)



大招：持续在周围形成怪盗迷雾，共为自己加血发动技能时刻血量的50%。普攻累计次数积累一次=12；持续时间=20s;CD=10s;

<img src="https://github.com/guangnianyuji/BrawlStars/blob/main/Image/JAce(1).png?raw=true" style="zoom:67%;" />

### 霖

![](https://github.com/guangnianyuji/BrawlStars/blob/main/Image/Lf1.png?raw=true)

移动速度 = 30.0
初始血量= 4200.0

普攻：召唤天降雷电。伤害=65.0；范围 = 500;CD=0.7s;

<img src="https://github.com/guangnianyuji/BrawlStars/blob/main/Image/L_05.png?raw=true" style="zoom:50%;" />

大招：发动轻功加快移速，翻山越岭。移速=160；普攻累计次数积累一次=10；持续时间=22s;CD=25s;

## 宝箱

地图上持续存在共十个宝箱。宝箱位置随机，一个宝箱被摧毁后会有新的一个宝箱随机出现。

宝箱血量=1400；提供血量=200；提供攻击力=20；

## 毒雾

身处毒雾，每1.5s降低50血量。

## 奖杯

根据存活的名次，玩家从1-10名获得10-1座奖杯。

# 致谢

- 感谢助教老师的温柔帮助和解答疑惑

- 感谢素未谋面的学长们每次听见愚蠢问题都耐心解答

- syf感谢朋友zx提出为本项目画像素人物虽然最后忙于学习不了了之，感谢游戏经验丰富的朋友hqh提出无法实现的游戏设计意见，

  

