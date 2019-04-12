#ifndef tp_data_opencv_CVMatchesMember_h
#define tp_data_opencv_CVMatchesMember_h

#include "tp_data_opencv/Globals.h"

#include "tp_data_features/members/MatchesMember.h"

#include <opencv2/core/mat.hpp>

namespace tp_data_opencv
{

//##################################################################################################
class CVMatchesMember : public tp_data_features::MatchesMember
{
public:
  //################################################################################################
  CVMatchesMember(const std::string& name=std::string());

  //################################################################################################
  void populateFields();

  //cv::Mat data;
};

}

#endif
