#ifndef tp_data_opencv_Globals_h
#define tp_data_opencv_Globals_h

#include "tp_utils/StringID.h"

namespace tp_data
{
class CollectionFactory;
}

//##################################################################################################
//! Add opencv to the pipeline pipeline.
namespace tp_data_opencv
{
TDP_DECLARE_ID(                        cvMatSID,                           "CV mat")
TDP_DECLARE_ID(                   cvFeaturesSID,                      "CV features")

//TDP_DECLARE_ID(                       opencvSID,                           "Opencv")
//TDP_DECLARE_ID(             featureExtractorSID,                "Feature extractor")
//TDP_DECLARE_ID(                 detectorTypeSID,                    "Detector type")
//TDP_DECLARE_ID(                convertImagesSID,                   "Convert images")

//##################################################################################################
//! Add the collection factories that this module provides to the CollectionFactory
void createCollectionFactories(tp_data::CollectionFactory& collectionFactory);
}

#endif
