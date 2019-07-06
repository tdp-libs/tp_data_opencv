#include "tp_data_opencv/ImageConversion.h"

#include "tp_image_utils_functions/ConvolutionMatrix.h"

#include "tp_image_utils/ColorMap.h"
#include "tp_image_utils/ByteMap.h"

#include <opencv2/core.hpp>

namespace tp_data_opencv
{

//##################################################################################################
void convertImage(const tp_image_utils::ColorMap& in, cv::Mat& out)
{
  int rows = int(in.height());
  int cols = int(in.width());

  out = cv::Mat(rows, cols, CV_8UC4);

  {
    const TPPixel* i = in.constData();
    const TPPixel* iMax = i+(rows*cols);
    uint8_t* o = out.data;
    for(; i<iMax; i++, o+=4)
    {
      o[0] = i->r;
      o[1] = i->g;
      o[2] = i->b;
      o[3] = i->a;
    }
  }
}

//##################################################################################################
void convertImage(const tp_image_utils::ByteMap& in, cv::Mat& out)
{
  int rows = int(in.height());
  int cols = int(in.width());

  out = cv::Mat(rows, cols, CV_8UC1);

  {
    const uint8_t* i = in.constData();
    const uint8_t* iMax = i+(rows*cols);
    uint8_t* o = out.data;
    for(; i<iMax; i++, o++)
    {
      (*o) = (*i);
    }
  }
}

//##################################################################################################
void convertImage(const cv::Mat& in, tp_image_utils::ColorMap& out)
{
  auto rows = size_t(in.rows);
  auto cols = size_t(in.cols);

  out = tp_image_utils::ColorMap(cols, rows);

  TPPixel* o = out.data();
  TPPixel* oMax = o+(rows*cols);
  uint8_t* i = in.data;

  if(in.type() == CV_8UC4)
  {
    for(; o<oMax; i+=4, o++)
    {
      o->r = i[0];
      o->g = i[1];
      o->b = i[2];
      o->a = i[3];
    }
  }

  else if(in.type() == CV_8UC3)
  {
    for(; o<oMax; i+=3, o++)
    {
      o->r = i[0];
      o->g = i[1];
      o->b = i[2];
      o->a = 255;
    }
  }

  else if(in.type() == CV_8UC1)
  {
    for(; o<oMax; i++, o++)
    {
      o->r = *i;
      o->g = *i;
      o->b = *i;
      o->a = 255;
    }
  }
}

//##################################################################################################
void convertImage(const cv::Mat& in, tp_image_utils::ByteMap& out)
{
  auto rows = size_t(in.rows);
  auto cols = size_t(in.cols);

  if(in.type() != CV_8UC1)
    return;

  out = tp_image_utils::ByteMap(cols, rows);

  {
    uint8_t* o = out.data();
    uint8_t* oMax = o+(rows*cols);
    uint8_t* i = in.data;
    for(; o<oMax; i++, o+=4)
      (*o) = (*i);
  }
}

//##################################################################################################
void convertConvolutionMatrix(const tp_image_utils_functions::ConvolutionMatrix& in, cv::Mat& out)
{
  out = cv::Mat_<double>(int(in.height()), int(in.width()));

  for(size_t x=0; x<in.width(); x++)
    for(size_t y=0; y<in.height(); y++)
      out.at<double>(int(y), int(x)) = in.matrixData().at((y*in.width())+x);
}

}
