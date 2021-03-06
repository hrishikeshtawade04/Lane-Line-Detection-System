/**
 *  @file    LaneLineDetectionSystemTest.cpp
 *
 *  @author  Hrishikesh Tawade(Driver)
 *           Kapil Rawal(Navigator)
 *
 *  @copyright 3 Clause BSD License
 *
 *  @brief ENPM808X, Mid semester project
 *
 *  @section DESCRIPTION
 *
 *  Test all methods of LaneLineDetectionSystem class
 *
 */

#include <gtest/gtest.h>
#include "LaneLineDetectionSystem.h"

/**
 * @brief   Checks detectLaneLineForImage function in LaneLineDetectionSystem
 *          class
 *
 * @param   LaneLineDetectionSystemTest name of test suite
 *
 * @param   detectLaneLineForImageCheck Name of the test
 */
TEST(LaneLineDetectionSystemTest, detectLaneLineForImageCheck) {
  LaneLineDetectionSystem laneLineDetector;
  laneLineDetector.detectLaneLineForImage("../test_images/test_image1.jpg");
  cv::Mat image = cv::imread("../test_images_output/FinalOutput.jpg",
                             CV_LOAD_IMAGE_COLOR);
  EXPECT_EQ(0, image.empty());
  laneLineDetector.detectLaneLineForImage("../test_images/test_image1.png");
  EXPECT_EQ(1, laneLineDetector.notWorking);
}

/**
 * @brief   Checks detectLaneLineForVideo function in LaneLineDetectionSystem
 *          class
 *
 * @param   LaneLineDetectionSystemTest name of test suite
 *
 * @param   detectLaneLineForVideoCheck Name of the test
 */
TEST(LaneLineDetectionSystemTest, detectLaneLineForVideoCheck) {
  LaneLineDetectionSystem laneLineDetector;
  laneLineDetector.detectLaneLineForVideo("../test_videos/test_video1.mp4");
  cv::destroyAllWindows();
  cv::VideoCapture cap("../test_videos_output/final_video_output.avi");
  EXPECT_EQ(true, cap.isOpened());
  laneLineDetector.detectLaneLineForVideo("../test_videos_output/test.mp4");
  EXPECT_EQ(1, laneLineDetector.notWorking);
}

