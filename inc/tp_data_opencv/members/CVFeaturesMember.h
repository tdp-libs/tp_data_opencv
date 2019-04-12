#ifndef tp_data_opencv_CVFeaturesMember_h
#define tp_data_opencv_CVFeaturesMember_h

#include "tp_data_opencv/Globals.h"

#include "tp_data_features/members/FeaturesMember.h"

#include "tp_data/AbstractMemberFactory.h"

#include <opencv2/features2d.hpp>

namespace tp_data_opencv
{

//##################################################################################################
class CVFeaturesMember : public tp_data_features::FeaturesMember
{
public:
  //################################################################################################
  CVFeaturesMember(const std::string& name=std::string());

  //################################################################################################
  ~CVFeaturesMember() override;

  //################################################################################################
  void populateFeatures();

  //################################################################################################
  static CVFeaturesMember* fromData(std::string& error, const std::string& data);

  //################################################################################################
  std::string toData() const;

  //################################################################################################
  void copyData(const CVFeaturesMember& other);

  static const std::string extension;
  cv::Mat desc;
  std::vector<cv::KeyPoint> kp;
};

//##################################################################################################
using CVFeaturesMemberFactory = tp_data::MultiDataMemberFactoryTemplate<CVFeaturesMember, cvFeaturesSID>;

}

#endif
