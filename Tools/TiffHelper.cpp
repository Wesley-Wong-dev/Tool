
#include "TiffHelper.h"
#include <libtiff/tiffio.h>

CTiffHelper::CTiffHelper()
{
}


CTiffHelper::~CTiffHelper()
{
}

void CTiffHelper::WriteMultTiff(VTMats image_stack, const char* lpfile)
{
    TIFF* tif = TIFFOpen(lpfile, "w");

    if (tif)
    {
        for (unsigned int i = 0; i < image_stack.size(); ++i)
        {
            int imagewidth = image_stack[i].cols;

            int imageheight = image_stack[i].rows;

            int nr_channels = image_stack[i].channels();

            bool fp32 = (image_stack[i].type() == CV_32FC1);

            int nTemp = (nr_channels == 3 ? sizeof(uint32) : (fp32 ? sizeof(float) : sizeof(uchar)));

            void* raster = _TIFFmalloc(imagewidth* nTemp);

            TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, imagewidth);

            TIFFSetField(tif, TIFFTAG_IMAGELENGTH, imageheight);

            TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, fp32 ? 32 : 8);

            //TIFFSetField(tif, TIFFTAG_SAMPLEFORMAT, fp32 ? SAMPLEFORMAT_IEEEFP : SAMPLEFORMAT_UINT);

            TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, nr_channels);

            //TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);

            TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

            TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, nr_channels == 3 ? PHOTOMETRIC_RGB : PHOTOMETRIC_MINISBLACK);

            TIFFSetField(tif, TIFFTAG_SUBFILETYPE, FILETYPE_PAGE);

            TIFFSetField(tif, TIFFTAG_PAGENUMBER, i, image_stack.size());

            cv::Mat image = image_stack[i];

            switch (nr_channels)
            {

            case 1:
            {
                if (fp32)
                {
                    for (int y = 0; y < imageheight; ++y)
                    {

                        for (int x = 0; x < imagewidth; ++x) {

                            ((float*)(raster))[x] = image.at<float>(y, x);

                        }

                        TIFFWriteScanline(tif, raster, y, 0);

                    }

                }
                else
                {
                    for (int y = 0; y < imageheight; ++y)
                    {
                        for (int x = 0; x < imagewidth; ++x)
                        {
                            ((uchar*)(raster))[x] = image.at<uchar>(y, x);
                        }
                        TIFFWriteScanline(tif, raster, y, 0);
                    }
                }
            }
            break;
            case 3:
            default:
            {
                for (int y = 0; y < imageheight; ++y)
                {
                    for (int x = 0; x < imagewidth; ++x)
                    {
                        ((uint32*)(raster))[x] = image.at<cv::Vec3b>(y, x)[2] << 16

                            | image.at<cv::Vec3b>(y, x)[1] << 8

                            | image.at<cv::Vec3b>(y, x)[0] << 0;
                    }
                    TIFFWriteScanline(tif, raster, y, 0);
                }
            }
            break;
            }
            TIFFWriteDirectory(tif);

            _TIFFfree(raster);
        }
        TIFFClose(tif);
    }
    
}

VTMats CTiffHelper::ReadMultiPage(const char* lpfile, int nr_channels)
{
    VTMats image_stack;

    TIFF* tif = TIFFOpen(lpfile, "r");

    if (tif)
    {
        
        unsigned int imagewidth, imageheight;

        int dirs = 0;

        TIFFSetDirectory(tif, 0);

        do {
            ++dirs;
        } while (TIFFReadDirectory(tif));

        for (int n = 0; n < dirs; ++n) 
        {

            int is_tiled = TIFFIsTiled(tif);
            TIFFSetDirectory(tif, n);
            TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &imagewidth);

            TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &imageheight);

            uint32* raster = (uint32 *)_TIFFmalloc(imagewidth * imageheight * sizeof(uint32));
            cv::Mat image(imageheight, imagewidth, CV_8UC(nr_channels));

            TIFFReadRGBAImageOriented(tif, imagewidth, imageheight, raster,ORIENTATION_TOPLEFT);

            switch (nr_channels) 
            {

            case 1:
            {
                for (unsigned int y = 0; y < imageheight; ++y) 
                {
                    for (unsigned int x = 0; x < imagewidth; ++x)
                    {
                        image.at<uchar>(y, x) = raster[x + y * imagewidth] & 0xFF;
                    }
                }
            }

                    break;

            case 3:

            default: 
            {
                for (unsigned int y = 0; y < imageheight; ++y) 
                {
                    for (unsigned int x = 0; x < imagewidth; ++x)
                    {
                        image.at<cv::Vec3b>(y, x)[0] = (raster[x + y * imagewidth] >> 0)& 0xFF;

                        image.at<cv::Vec3b>(y, x)[1] = (raster[x + y * imagewidth] >> 8)& 0xFF;

                        image.at<cv::Vec3b>(y, x)[2] = (raster[x + y * imagewidth] >> 16)& 0xFF;
                    }
                }
            }
                     break;
            }
            image_stack.push_back(image);
            _TIFFfree(raster);
        }

        TIFFClose(tif);
    }
    return image_stack;
}
