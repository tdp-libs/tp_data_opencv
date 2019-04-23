#include "tp_data_opencv/Globals.h"
#include "tp_data_opencv/members/CVFeaturesMember.h"

#include "tp_data/CollectionFactory.h"

//##################################################################################################
namespace tp_data_opencv
{
TDP_DEFINE_ID(                        cvMatSID,                           "CV mat")
TDP_DEFINE_ID(                   cvFeaturesSID,                      "CV features")

//TDP_DEFINE_ID(                       opencvSID,                           "Opencv")
//TDP_DEFINE_ID(             featureExtractorSID,                "Feature extractor")
//TDP_DEFINE_ID(                 detectorTypeSID,                    "Detector type")
//TDP_DEFINE_ID(                         modeSID,                             "Mode")
//TDP_DEFINE_ID(                convertImagesSID,                   "Convert images")

//##################################################################################################
void createCollectionFactories(tp_data::CollectionFactory& collectionFactory)
{
  collectionFactory.addMemberFactory(new CVFeaturesMemberFactory());
}

REGISTER_CREATE_COLLECTION_FACTORIES;

//##################################################################################################
int staticInit()
{
  return 0;
}

}
