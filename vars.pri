TARGET = tp_data_opencv
TEMPLATE = lib

DEFINES += TP_DATA_OPENCV_LIBRARY

SOURCES += src/Globals.cpp
HEADERS += inc/tp_data_opencv/Globals.h

SOURCES += src/ImageConversion.cpp
HEADERS += inc/tp_data_opencv/ImageConversion.h


#-- Members ----------------------------------------------------------------------------------------
SOURCES += src/members/CVMatMember.cpp
HEADERS += inc/tp_data_opencv/members/CVMatMember.h

SOURCES += src/members/CVFeaturesMember.cpp
HEADERS += inc/tp_data_opencv/members/CVFeaturesMember.h

SOURCES += src/members/CVMatchesMember.cpp
HEADERS += inc/tp_data_opencv/members/CVMatchesMember.h

