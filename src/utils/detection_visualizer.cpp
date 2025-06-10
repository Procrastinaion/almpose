#include "../../include/utils/detection_visualizer.hpp"

DetectionVisualizer::DetectionVisualizer(int width_new, int height_new) {
    width = width_new;
    height = height_new;
    ui_ptr = new Metavision::MTWindow("Detection", width, height, Metavision::Window::RenderMode::BGR);
}

DetectionVisualizer::~DetectionVisualizer() {
    if (ui_ptr) {
        ui_ptr->set_close_flag();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        delete ui_ptr;
        ui_ptr = nullptr;
    }
}

void DetectionVisualizer::display(const cv::Mat &threshold_img,
                                  const std::vector<std::vector<cv::Point>> &contours,
                                  const std::vector<double> &frequencies) {
    cv::Mat img_bgr;
    cv::cvtColor(threshold_img, img_bgr, cv::COLOR_GRAY2BGR);

    for (size_t i = 0; i < contours.size() && i < frequencies.size(); ++i) {
        cv::Point2f center;
        float radius = 0.f;
        if (!contours[i].empty()) {
            cv::minEnclosingCircle(contours[i], center, radius);
            cv::circle(img_bgr, center, int(radius), cv::Scalar(0, 255, 0), 1);
            cv::putText(img_bgr, std::to_string(int(frequencies[i])), center,
                        cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(0, 0, 255), 1);
        }
    }

    ui_ptr->show_async(img_bgr);
    Metavision::EventLoop::poll_and_dispatch();
}
