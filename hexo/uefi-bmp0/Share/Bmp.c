/*
    @Description    : 这是一个让Bmp位深转24Bit的事例呀,非完整代码.
 *  @Author         : Maouai233 (canyan233)
 *  @Updated Date   : 2022-08-27
 */

VOID
BmpTranslate(
    IN     VOID                           *BmpFileRaw,
       OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *ImageOut
)
{
    BMP_IMAGE_HEADER               *BmpHeader   = (BMP_IMAGE_HEADER *)BmpFileRaw;
    DEBUG((DEBUG_INFO,"[  GRAPH  ] Width : %d , Height : %d , ImageOffset : %d\n",BmpHeader->Width,BmpHeader->Height,BmpHeader->ImageOffset));
    UINT8                          *ImageIn     = BmpFileRaw + BmpHeader->ImageOffset;
    BMP_COLOR_MAP                  *BmpColorMap = (BMP_COLOR_MAP *)(BmpFileRaw + sizeof(BMP_IMAGE_HEADER));
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *ImagePixel = ImageOut;

    BOOLEAN HeightPositive = (BOOLEAN)(BmpHeader->Height > 0);
    DEBUG((DEBUG_INFO,"[  DEBUG  ] HeightPositive : %d\n",HeightPositive));

    for(UINTN HeightIndex = HeightPositive ? BmpHeader->Height - 1 : 0; HeightPositive ? (HeightIndex > 0) : (HeightIndex < ABS(BmpHeader->Height));HeightPositive ? (HeightIndex--) : (HeightIndex++))
    {
        for(UINTN WidthIndex = 0;WidthIndex < BmpHeader->Width;ImageIn++)
        {
            ImagePixel = &ImageOut[BmpHeader->Width * HeightIndex + WidthIndex];
            if (BmpHeader->ImageBits == 1)
            {
                for(UINTN BitIndex = 0;(BitIndex < 8) && WidthIndex < BmpHeader->Width;BitIndex++,WidthIndex++)
                {
                    ImagePixel->Blue  = BmpColorMap[((*ImageIn) >> (7 - BitIndex)) & 0b1].Blue;
                    ImagePixel->Green = BmpColorMap[((*ImageIn) >> (7 - BitIndex)) & 0b1].Green;
                    ImagePixel->Red   = BmpColorMap[((*ImageIn) >> (7 - BitIndex)) & 0b1].Red;
                }
            }
            else if (BmpHeader->ImageBits == 4)
            {
                ImagePixel->Blue  = BmpColorMap[(*ImageIn) >> 4].Blue;
                ImagePixel->Green = BmpColorMap[(*ImageIn) >> 4].Green;
                ImagePixel->Red   = BmpColorMap[(*ImageIn) >> 4].Red;
                WidthIndex++;
                if (WidthIndex < BmpHeader->Width)
                {
                    ImagePixel        = &ImageOut[BmpHeader->Width * HeightIndex + WidthIndex];
                    ImagePixel->Blue  = BmpColorMap[(*ImageIn) & 0b1111].Blue;
                    ImagePixel->Green = BmpColorMap[(*ImageIn) & 0b1111].Green;
                    ImagePixel->Red   = BmpColorMap[(*ImageIn) & 0b1111].Red;
                    WidthIndex++;
                }
            }
            else if (BmpHeader->ImageBits == 8)
            {
                ImagePixel->Blue  = BmpColorMap[*ImageIn].Blue;
                ImagePixel->Green = BmpColorMap[*ImageIn].Green;
                ImagePixel->Red   = BmpColorMap[*ImageIn].Red;
                WidthIndex++;
            }
            else if (BmpHeader->ImageBits == 24)
            {
                ImagePixel->Blue  = *ImageIn++;
                ImagePixel->Green = *ImageIn++;
                ImagePixel->Red   = *ImageIn;
                WidthIndex++;
            }
        }
    }
}