#include "tp_data_opencv/members/CVMatMember.h"

namespace tp_data_opencv
{

//##################################################################################################
CVMatMember::CVMatMember(const std::string& name):
  tp_data::AbstractMember(name, cvMatSID())
{

}

}
