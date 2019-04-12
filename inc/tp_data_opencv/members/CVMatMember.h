#ifndef tp_data_opencv_CVMatMember_h
#define tp_data_opencv_CVMatMember_h

#include "tp_data_opencv/Globals.h"

#include "tp_data/AbstractMember.h"

#include <opencv2/core/mat.hpp>

namespace tp_data_opencv
{

//##################################################################################################
class CVMatMember : public tp_data::AbstractMember
{
public:
  //################################################################################################
  CVMatMember(const std::string& name=std::string());

  cv::Mat data;
};

}

#endif
