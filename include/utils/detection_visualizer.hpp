#ifndef FRAMEWORK_MARKERS_DETECTION_VISUALIZER_HPP
#define FRAMEWORK_MARKERS_DETECTION_VISUALIZER_HPP

#include <opencv2/opencv.hpp>
#include <metavision/sdk/ui/utils/mt_window.h>
#include <metavision/sdk/ui/utils/event_loop.h>

class DetectionVisualizer {
public:
    DetectionVisualizer(int width, int height);
    ~DetectionVisualizer();

    void display(const cv::Mat &threshold_img,
                 const std::vector<std::vector<cv::Point>> &contours,
                 const std::vector<double> &frequencies);

private:
    int width;
    int height;
    Metavision::MTWindow *ui_ptr;
};

#endif //FRAMEWORK_MARKERS_DETECTION_VISUALIZER_HPP
