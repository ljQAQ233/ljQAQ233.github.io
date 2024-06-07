---
title: 'UEFI数据类型'
date: 2022-03-28 15:01:17
tags:
 - UEFI
 - EDKII
 - Bilibili
 - C语言
---

# UEFI数据类型

- 2022/03/28 15:01:17

---

# 前言

**还未更新完**

欢迎更正：

Bilibili : <a href="https://space.bilibili.com/503518259" >Maouai233</a>

Mail : Maouai233@outlook.com

最初接触EDK2还是在最初的时候了，看谭老师的视频也有一些收获，对于EDKII的一些如**UINTN、CHAR8、CHAR16**不是太在意，后来就越看越奇怪了，去查阅了EDKII官方文档，一大片英文，这对于我并不友好，以我目前的知识，看了个大概，机器翻译再加上我个人的理解，就搞了这篇文章。
还有就是，封城了，停课了...

# 主要

## 全部

| 类         | 描述                                                         |
| ---------- | ------------------------------------------------------------ |
| EFI_STATUS | 状态码，有成功、错误和警告                                   |
| UINT64     | 8字节无符号整型                                              |
| INT64      | 8字节带符号整型                                              |
| UINT32     | 4字节无符号整型                                              |
| INT32      | 4字节带符号整型                                              |
| UINT16     | 2字节无符号整型                                              |
| INT16      | 2字节带符号整型                                              |
| UINT8      | 1字节无符号整型                                              |
| INT8       | 1字节带符号整型                                              |
| CHAR16     | 2字节字符                                                    |
| CHAR8      | 1字节字符                                                    |
| BOOLEAN    | 布尔类型，1字节字符，值可以是FALSE[0]和TRUE[1]，可以用两种方式赋值，但不加单引号 |

## UINTN

|               |X64           |Ia32               |AARCH64          |ARM                  |
|---------------|--------------|-------------------|-----------------|---------------------|
|UINTN          |UINT64        |UINT32             |UINT64           |UINT32               |
|INTN           |INT64         |INT32              |INT64            |INT32                |

# 宏

| 宏   | 描述                |
| ---- | ------------------- |
| VOID | void类型,指针"无敌" |



# 原类型

 **将以GCC / Clang为代表**

| 类型          | 原类型 X64 / AARCH64 | 原类型 Ia32 / ARM32 |
| ------------- | -------------------- | ------------------- |
| RETURN_STATUS | unsigned long long   | unsigned int        |
| EFI_STATUS    | RETURN_STATUS        | RETURN_STATUS       |
| UINTN         | unsigned long long   | unsigned int        |
| INTN          | long long            | int                 |
| UINT64        | unsigned long long   | unsigned long long  |
| INT64         | long long            | long long           |
| UINT32        | unsigned int         | unsigned int        |
| UINT16        | unsigned short       | unsigned short      |
| INT16         | short                | short               |
| UINT8         | unsigned char        | unsigned char       |
| INT8          | signed char          | signed char         |
| CHAR16        | unsigned short       | unsigned short      |
| CHAR8         | char                 | char                |
| BOOLEAN       | unsigned char        | unsigned char       |

 **对于char，char是unsigned还是signed不确定，根据编译器的不同而不同。**

| 宏   | 定义值 |
| ---- | ------ |
| VOID | void   |



# 分条

## EFI_STATUS分条

### 头文件

```c
/* File : MdePkg/Include/Base.h */

typedef UINTN RETURN_STATUS;
```
```c
/* File : MdePkg/Include/Uefi/UefiBaseType.h */

typedef RETURN_STATUS             EFI_STATUS;
```

### 用法

判断程序出错或打印Log必备：通常这样定义一个EFI_STATUS型变量，初始化为成功。
```c
EFI_STATUS Status = EFI_SUCCESS;
```

EDKII源代码中许多函数使用EFI_STATUS型，返回的值是EFI_STATUS型，所以可以使用以下来接收函数运行后返回的结果(前提是函数的return的要是EFI_STATUS型)：
```c
Status = Function();
```
也提供了专门来判断是否运行错误即返回错误代码的EFI_ERROR()，使用如下：
```c
if(EFI_ERROR(Status)) {
  return Status;
}
```
意思是如果之前定义的EFI_STATUS类型的Status是错误的结果，就执行大括号中的代码（这里直接返回Status，会回到EFI SHELL或者返回上一个调用此的函数），如果不是则跳过。

它是可以后面手动更改值的：

```c
Status = EFI_SUCCESS;
```

具体如下：

### 具体

#### 成功

高位清除，无符号，没有负数的情况。

|类         |值|描述        |
|-----------|--|------------|
|EFI_SUCCESS|0 |成功完成操作|

#### 失败

不同架构机器下,失败的值可能不同.

这里先将状态码定义成**RETURN等**后在UefiBaseType.h中将**EFI等*定义到对应的**RETURN**上.

##### 辅助宏

```c
/* File : MdePkg/Incude/Base.h */
#define ENCODE_WARNING(StatusCode)       ((RETURN_STATUS)(StatusCode))
#define ENCODE_ERROR(StatusCode)         ((RETURN_STATUS)(MAX_BIT | (StatusCode)))

/* File : MdePkg/Include/Uefi/UefiBaseType.h */
#define EFI_SUCCESS               RETURN_SUCCESS              
#define EFI_LOAD_ERROR            RETURN_LOAD_ERROR
/* ...... */
```

##### 值&描述

具体见**MdePkg/Include/Base.h** & **MdePkg/Include/Uefi/UefiBaseType.h**

|类|值|描述|
|--|--|--|
|EFI_LOAD_ERROR|ENCODE_ERROR(1)|加载镜像Image失败|
|EFI_INVALID_PARAMETER|ENCODE_ERROR(2)|参数不正确|
|EFI_UNSUPPORTED|ENCODE_ERROR(3)|该操作不支持|
|EFI_BAD_BUFFER_SIZE|ENCODE_ERROR(4)|缓冲区Buffer的大小不适用于请求|
|EFI_BUFFER_TOO_SMALL|ENCODE_ERROR(5)|缓冲区不够大，无法容纳请求的数据|
|EFI_NOT_READY|ENCODE_ERROR(6)|There is no data pending upon return|
|EFI_DEVICE_ERROR|ENCODE_ERROR(7)|物理设备在尝试操作时报告错|
|EFI_WRITE_PROTECTED|ENCODE_ERROR(8)|无法写入设备|
|EFI_OUT_OF_RESOURCES|ENCODE_ERROR(9)|资源已用完|
|EFI_VOLUME_CORRUPTED|ENCODE_ERROR(10)|在文件系统上检测到一个不稳定因素，而导致运行失败|
|EFI_VOLUME_FULL|ENCODE_ERROR(11)|文件系统上没有更多空间|
|EFI_NO_MEDIA|ENCODE_ERROR(12)|该设备不包含任何介质来执行操作|
|EFI_MEDIA_CHANGED|ENCODE_ERROR(13)|自上次访问以来，设备中的介质已更改|
|EFI_NOT_FOUND|ENCODE_ERROR(14)|未找到该项|
|EFI_ACCESS_DENIED|ENCODE_ERROR(15)|拒绝访问|
|EFI_NO_RESPONSE|ENCODE_ERROR(16)|未找到服务器或未响应请求|
|EFI_NO_MAPPING|ENCODE_ERROR(17)|到设备的映射不存在|
|EFI_TIMEOUT|ENCODE_ERROR(18)|超时|
|EFI_NOT_STARTED|ENCODE_ERROR(19)|Protocol尚未启动|
|EFI_ALREADY_STARTED|ENCODE_ERROR(20)|Protocol已经启动|
|EFI_ABORTED|ENCODE_ERROR(21)|操作被终止|
|EFI_ICMP_ERROR|ENCODE_ERROR(22)|网络操作期间发生ICMP错误|
|EFI_TFTP_ERROR|ENCODE_ERROR(23)|网络操作期间发生TFTP错误|
|EFI_PROTOCOL_ERROR|ENCODE_ERROR(24)|网络操作期间发生Protocol错误|
|EFI_INCOMPATIBLE_VERSION|ENCODE_ERROR(25)|The function encountered an internal version that was incompatible with a version requested by the caller|
|EFI_SECURITY_VIOLATION|ENCODE_ERROR(26)|由于安全违规，该功能未执行|
|EFI_CRC_ERROR|ENCODE_ERROR(27)|检测到CRC错误|
|EFI_END_OF_MEDIA|ENCODE_ERROR(28)|已到达媒体介质的开头或结尾|
|EFI_END_OF_FILE|ENCODE_ERROR(31)|已到达文件末尾|
|EFI_INVALID_LANGUAGE|ENCODE_ERROR(32)|指定的语言无效|
|EFI_COMPROMISED_DATA|ENCODE_ERROR(33)|数据的安全状态未知或受损，必须更新数据或替换数据以恢复有效的安全状态|
|EFI_IP_ADDRESS_CONFLICT|ENCODE_ERROR(34)|There is an address conflict address allocation|
|EFI_HTTP_ERROR|ENCODE_ERROR(35)|网络操作期间发生 HTTP 错误|

#### 警告

高位清除，无符号，"没有"负数的情况。

|类|值|描述|
|--|--|----|
|EFI_WARN_UNKNOWN_GLYPH|ENCODE_WARNING(1)|该字符串包含了设备的一个或多个字符无法渲染并被跳过|
|EFI_WARN_DELETE_FAILURE|ENCODE_WARNING(2)|Handle已关闭，但文件尚未删除|
|EFI_WARN_WRITE_FAILURE|ENCODE_WARNING(3)|The handle was closed, but the data to the file was not flushed properly|
|EFI_WARN_BUFFER_TOO_SMALL|ENCODE_WARNING(4)|存放结果的缓冲区太小，且数据被截断为缓冲区大小|
|EFI_WARN_STALE_DATA|ENCODE_WARNING(5)|The data has not been updated within the timeframe set by local policy for this type of data|
|EFI_WARN_FILE_SYSTEM|ENCODE_WARNING(6)|生成的缓冲区包含UEFI-compliant的文件系统|
|EFI_WARN_RESET_REQUIRED|ENCODE_WARNING(7)|该操作将在系统重置后被处理|

## BOOLEAN分条

### 头文件
```c
/* File : MdePkg/Include/?/ProcessorBind.h */

typedef unsigned char       BOOLEAN;
```
```c
/* File : MdePkg/Include/Base.h */

#define TRUE  ((BOOLEAN)(1==1))
#define FALSE ((BOOLEAN)(0==1))
```

### 用法

布尔类型，1字节字符，值可以是FALSE和TRUE或者表达成0、1，可以用**两种**方式赋值，但不加单引号 
定义一个BOOLEAN并设置为“真”有两种写法：

```c
/* 第一种 */
BOOLEAN TestBool = 1;

/* 第二种 */
BOOLEAN TestBool = TRUE;
```
与此相反，“假”则是FLASE或者0

可以直接使用if判断之前定义的值是否为真：
```c
if(TestBool) {
  Print(L"TRUE\n");
}

if(!TestBool) {
  Print(L"FALSE\n");
}
```
# 修饰符

顺便讲一下

```c
/* File : MdePkg/Include/Base.h */

#define CONST     const
#define STATIC    static
```

# 资源

EDKII v2.9官方文档：<a href="https://uefi.org/sites/default/files/resources/UEFI_Spec_2_9_2021_03_18.pdf" >点此下载</a>

