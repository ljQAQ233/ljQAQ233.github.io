---
title: 'Bmp位图转换与显示'
date: 2023-02-04 14:11:36
tags:
 - UEFI
 - EDKII
 - Bilibili
 - C语言
 - Bmp
---

# Bmp位图转换与显示

- 2023/02/04 14:11:36

# 前言

书接上回,讲完了Bmp图片的格式,这下我们来看看具体的转换!

# Transform

这是一个转换的函数, 它可以将 **1/4/8/24bit** 的Bmp图像转换成 24bit 且 Uefi 支持的`EFI_GRAPHICS_OUTPUT_BLT_PIXEL`数组

传入参数是未经过任何处理的Bmp文件`BmpFileRaw`

```cpp

VOID BmpTranslate (
        IN     VOID                           *BmpFileRaw,
           OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Out
           );
```

在正式转换之前,我们先做一些工作.如下:

```cpp

    /* 获取 BmpHeader 即必要的信息 */
    BMP_IMAGE_HEADER               *BmpHeader   = (BMP_IMAGE_HEADER *)BmpFileRaw;
    /* 遍历 BmpFileRaw 的指针 */
    UINT8                          *RawIdx      = BmpFileRaw + BmpHeader->ImageOffset;
    /* 位图调色板,供 转换时 查询 */
    BMP_COLOR_MAP                  *ColorMap    = (BMP_COLOR_MAP *)(BmpFileRaw + sizeof(BMP_IMAGE_HEADER));
    /* 储存输出 Out 的索引 */
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *OutIdx      = Out;

    /* 由于 Bmp位图 的高度有可能为负数,则 BmpFileRaw行的遍历顺序 相反,见上文 */
    BOOLEAN HeightPositive = (BOOLEAN)(BmpHeader->Height > 0);

```

```cpp

    /* 如果 位图高 为正数,则从 位图第一排的像素 在 数组尾部,从 尾部 开始遍历 */
    for (UINTN HeightIndex = HeightPositive ? BmpHeader->Height - 1 : 0
            ; HeightPositive ? (HeightIndex > 0) : (HeightIndex < ABS(BmpHeader->Height))
            ; HeightPositive ? (HeightIndex--) : (HeightIndex++)
            )
    {
        /* 从 行 头部开始遍历 */
        for (UINTN WidthIdx = 0;WidthIdx < BmpHeader->Width;RawIdx++)
        {
            /* 定位 输出索引 */
            OutIdx = &Out[BmpHeader->Width * HeightIndex + WidthIdx];
            /* 分类处理 */
            if (BmpHeader->ImageBits == 1)
            {
                /* 对于1bit位深的,以1bit为单位储存一个像素 */
                for(UINTN BitIndex = 0;(BitIndex < 8) && WidthIdx < BmpHeader->Width;BitIndex++,WidthIdx++)
                {
                    OutIdx->Blue  = ColorMap[((*RawIdx) >> (7 - BitIndex)) & 0b1].Blue;
                    OutIdx->Green = ColorMap[((*RawIdx) >> (7 - BitIndex)) & 0b1].Green;
                    OutIdx->Red   = ColorMap[((*RawIdx) >> (7 - BitIndex)) & 0b1].Red;
                }
            }
            else if (BmpHeader->ImageBits == 4)
            {
                OutIdx->Blue  = ColorMap[(*RawIdx) >> 4].Blue;
                OutIdx->Green = ColorMap[(*RawIdx) >> 4].Green;
                OutIdx->Red   = ColorMap[(*RawIdx) >> 4].Red;
                WidthIdx++;
                /* 防止过界 */
                if (WidthIdx < BmpHeader->Width)
                {
                    OutIdx        = &Out[BmpHeader->Width * HeightIndex + WidthIdx];
                    OutIdx->Blue  = ColorMap[(*RawIdx) & 0b1111].Blue;
                    OutIdx->Green = ColorMap[(*RawIdx) & 0b1111].Green;
                    OutIdx->Red   = ColorMap[(*RawIdx) & 0b1111].Red;
                    WidthIdx++;
                }
            }
            else if (BmpHeader->ImageBits == 8)
            {
                /* 由于使用1byte储存一个像素,直接查表 */
                OutIdx->Blue  = ColorMap[*RawIdx].Blue;
                OutIdx->Green = ColorMap[*RawIdx].Green;
                OutIdx->Red   = ColorMap[*RawIdx].Red;
                WidthIdx++;
            }
            else if (BmpHeader->ImageBits == 24)
            {
                /* 对24bit的位深进行处理,主要是Uefi的 EFI_GRAPHICS_OUTPUT_BLT_PIXEL 有 Reserved保留 */
                OutIdx->Blue  = *RawIdx++;
                OutIdx->Green = *RawIdx++;
                OutIdx->Red   = *RawIdx;
                WidthIdx++;
            }
        }
    }

```

# Package

这里使用`BMP_CONFIG`来保存位图信息.

```cpp
typedef struct {
  BMP_IMAGE_HEADER              Header;            // 位图头
  VOID                          *PixelData;        // 像素数据
  UINTN                         PixelDataPages;    // 像素数据占用的页数
} BMP_CONFIG;
```

# Display

使用`Blt`函数进行显示

模式选择从**缓冲区到屏幕**,`SourceX`与`SourceY`为0

```cpp

Gop->Blt (
        Gop,
        (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)BmpConfig.PixelData,
        EfiBltBufferToVideo,
        0,0,
        X,Y,
        BmpConfig.Header.Width,
        BmpConfig.Header.Height,
        BmpConfig.Header.Width * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
    );

```

