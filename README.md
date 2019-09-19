# PEInfo
用于读取指定PE文件相关信息

### 开发环境： VS2015 + WIN1064bit + C++

#### 界面库:MFC 

#### 界面库开发语言:C++ 

#### 核心库源文件：core.cpp

#### 核心库功能接口：core.h
核心库目前暴露19个接口，以后优化还会再增加的。

#### 核心开发语言：C++

### 版本：V1.0

### 主要功能：
* 读取数据目录表
* 导出表及导出函数
* 导入表用导入函数
* RVA计算机器
* 读取FileHeader与Optional Header

### 邮箱：zmbilx@163.com

### 编绎好后二制文件下载链接
链接：https://pan.baidu.com/s/1Ly_kIbTJTXaqCc7KZhmfWg 提取码：z4gh 

### 接下来的打算：
* 优化RVA计算器，因为输入数字部分没有做限制。
* 把数据目录表的15个数据内容依次做完。
* 最后把核心功能做成DLL，用于其他语言调用（这个很简单啦，打算在最后做）。
* 增加其他语言调用核心DLL指定PE文件信息。

### 运行截图：
![image](https://github.com/zmbilx/PEInfo/blob/master/images/2019-09-19_193642.png)
![image](https://github.com/zmbilx/PEInfo/blob/master/images/2019-09-19_193712.png)
![image](https://github.com/zmbilx/PEInfo/blob/master/images/2019-09-19_193729.png)
![image](https://github.com/zmbilx/PEInfo/blob/master/images/2019-09-19_193746.png)
![image](https://github.com/zmbilx/PEInfo/blob/master/images/2019-09-19_193808.png)
![image](https://github.com/zmbilx/PEInfo/blob/master/images/2019-09-19_193829.png)
	
