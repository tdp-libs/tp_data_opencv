DEPENDENCIES += tp_data_image_utils
DEPENDENCIES += tp_data_math_utils
DEPENDENCIES += tp_data_features
INCLUDEPATHS += tp_data_opencv/inc/
LIBRARIES    += tp_data_opencv

LIBS += -lopencv_features2d
LIBS += -lopencv_core
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc
LIBS += -lopencv_flann
