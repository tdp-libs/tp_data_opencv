#include "tp_data_opencv/members/CVFeaturesMember.h"

#include <opencv2/features2d.hpp>

namespace tp_data_opencv
{
const std::string CVFeaturesMember::extension{"bin"};

//##################################################################################################
CVFeaturesMember::CVFeaturesMember(const std::string& name):
  tp_data_features::FeaturesMember(name, cvFeaturesSID())
{

}

//##################################################################################################
CVFeaturesMember::~CVFeaturesMember() = default;

//##################################################################################################
void CVFeaturesMember::populateFeatures()
{
  //    tp_math_utils::RNG rng;
  //    auto randomColor = [&]()
  //    {
  //      return glm::vec4(rng.randF()*0.4f+0.4f, rng.randF()*0.4f+0.4f, rng.randF()*0.4f+0.4f, 1.0f);
  //    };
  //    for(int i=0; i<int(featureCollection->kp.size()); i++)
  //    {
  //      const cv::KeyPoint& featurePoint = featureCollection->kp.at(i);
  //      OpenCVFeature* feature = new OpenCVFeature();
  //      feature->frame = 0;
  //      feature->coord2D = {featurePoint.pt.x, featurePoint.pt.y};
  //      feature->coord2DNormalized = {(f.x*float(feature->coord2D.x))-1.0f, (f.y*float(feature->coord2D.y))+1.0f};
  //      feature->kp = featurePoint;
  //      feature->color = tpGetMapValue(featureColors, feature->coord2D, randomColor());
  //      feature->meanColor = meanColor(image->image, feature->coord2D, 5);
  //      featureCollection->addFeature(feature);
  //    }
  //  }
}

namespace
{
//##################################################################################################
size_t calcWords(size_t nKP)
{
  //kp Point2f pt;     2 2
  //kp float size;     1 3
  //kp float angle;    1 4
  //kp float response; 1 5
  //kp int octave;     1 6
  //kp int class_id;   1 7
  return
      1       + // Count of key points.
      1       + // Desc cols.
      1       + // Desc rows.
      1       + // Desc element size.
      1       + // Desc element type.
      (nKP*7);  // Keypoint data.

}
}

//##################################################################################################
CVFeaturesMember* CVFeaturesMember::fromData(std::string& error, const std::string& data)
{
#if 1 //-- Brutal but fast -------------------------------------------------------------------------
  {
    auto src = data.data();
    auto readFloat = [&]()
    {
      float word{0.0f};
      static_assert (sizeof(word)==4, "This only works with 32bit words.");
      memcpy(&word, src, 4);
      src+=4;
      return word;
    };
    auto readInt = [&]()
    {
      int32_t word{0};
      static_assert (sizeof(word)==4, "This only works with 32bit words.");
      memcpy(&word, src, 4);
      src+=4;
      return word;
    };

    if(data.size()<4)
    {
      error = "CVFeaturesMember::fromData missing header.";
      return nullptr;
    }

    size_t nKP = size_t(readInt());
    size_t words = calcWords(nKP);
    if(data.size()<(words*4))
    {
      error = "CVFeaturesMember::fromData kp size mismatch.";
      return nullptr;
    }

    int cols     = int(readInt());
    int rows     = int(readInt());
    int elemSize = int(readInt());
    int type     = int(readInt());

    if((cols<1 && rows<1) || elemSize<1)
    {
      error = "CVFeaturesMember::fromData non 2D desc.";
      return nullptr;
    }

    size_t descSizeBytes = (size_t(cols) * size_t(rows) * size_t(elemSize));

    size_t bytes = (words*4) +    // The header and kp data
                   descSizeBytes; // The desc data

    if(data.size()<bytes)
    {
      error = "CVFeaturesMember::fromData desc size mismatch.";
      return nullptr;
    }

    auto member = new CVFeaturesMember();
    member->kp.resize(nKP);
    for(auto& k : member->kp)
    {
      k.pt.x     = readFloat();
      k.pt.y     = readFloat();
      k.size     = readFloat();
      k.angle    = readFloat();
      k.response = readFloat();
      k.octave   = readInt();
      k.class_id = readInt();
    }

    member->desc = cv::Mat(rows, cols, type);
    if(member->desc.elemSize() != size_t(elemSize))
    {
      delete member;
      error = "CVFeaturesMember::fromData desc elemSize mismatch.";
      return nullptr;
    }

    memcpy(member->desc.data, src, descSizeBytes);
    return member;
  }
#else //-- Correct but slow ------------------------------------------------------------------------
  {
    TP_UNUSED(error);
    auto member = new CVFeaturesMember();
    cv::FileStorage fileStorage(data, cv::FileStorage::MEMORY | cv::FileStorage::READ);
    cv::read(fileStorage["kp"], member->kp);
    cv::read(fileStorage["desc"], member->desc);
    return member;
  }
#endif
}

//##################################################################################################
std::string CVFeaturesMember::toData() const
{
#if 1 //-- Brutal but fast -------------------------------------------------------------------------
  {
    size_t words = calcWords(kp.size());

    size_t descSizeBytes = (size_t(desc.cols) * size_t(desc.rows) * desc.elemSize());

    size_t bytes = (words*4) +    // The header and kp data
                   descSizeBytes; // The desc data

    std::string data;
    data.resize(bytes);
    auto dst = data.data();
    auto addWord = [&](auto word)
    {
      static_assert (sizeof(word)==4, "This only works with 32bit words.");
      memcpy(dst, &word, 4);
      dst+=4;
    };

    addWord(int32_t(kp.size()));
    addWord(int32_t(desc.cols));
    addWord(int32_t(desc.rows));
    addWord(int32_t(desc.elemSize()));
    addWord(int32_t(desc.type()));

    for(const auto& k : kp)
    {
      addWord(float(k.pt.x));
      addWord(float(k.pt.y));
      addWord(float(k.size));
      addWord(float(k.angle));
      addWord(float(k.response));
      addWord(int32_t(k.octave));
      addWord(int32_t(k.class_id));
    }

    memcpy(dst, desc.data, descSizeBytes);

    return data;
  }
#else //-- Correct but slow ------------------------------------------------------------------------
  {
    cv::FileStorage fileStorage(".json", cv::FileStorage::MEMORY | cv::FileStorage::WRITE);
    write(fileStorage, "kp", kp);
    write(fileStorage, "desc", desc);
    return fileStorage.releaseAndGetString();
  }
#endif
}

//##################################################################################################
void CVFeaturesMember::copyData(const CVFeaturesMember& other)
{
  kp   = other.kp;
  desc = other.desc;
}

}
