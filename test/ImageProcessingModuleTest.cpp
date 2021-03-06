/**
 *  @file    ImageProcessingModuleTest.cpp
 *
 *  @author  Hrishikesh Tawade (Driver)
 *           Kapil Rawal (Navigator)
 *
 *  @copyright 3 Clause BSD License
 *
 *  @brief ENPM808X, Mid semester project
 *
 *  @section DESCRIPTION
 *
 *  This module tests the methods of the ImageProcessingModule class
 */

#include <gtest/gtest.h>
#include <array>
#include "ImageProcessingModule.h"

/**
 * @brief Testing getImagePoint1 method
 *
 * @param ImageProcessingModuleTest Name of the test suite
 *
 * @param getImagePoint1Check Name of the test
 */
TEST(ImageProcessingModuleTest, getImagePoint1Check) {
  ImageProcessingModule imageProcessor;
  EXPECT_EQ(0, imageProcessor.getImagePoint1());
}

/**
 * @brief Testing getImagePoint2 method
 *
 * @param ImageProcessingModuleTest Name of the test suite
 *
 * @param getImagePoint2Check Name of the test
 */
TEST(ImageProcessingModuleTest, getImagePoint2Check) {
  ImageProcessingModule imageProcessor;
  EXPECT_EQ(0, imageProcessor.getImagePoint2());
}

/**
 * @brief Testing getImagePoint3 method
 *
 * @param ImageProcessingModuleTest Name of the test suite
 *
 * @param getImagePoint3Check Name of the test
 */
TEST(ImageProcessingModuleTest, getImagePoint3Check) {
  ImageProcessingModule imageProcessor;
  EXPECT_EQ(0, imageProcessor.getImagePoint3());
}

/**
 * @brief Testing getImagePoint4 method
 *
 * @param ImageProcessingModuleTest Name of the test suite
 *
 * @param getImagePoint4Check Name of the test
 */
TEST(ImageProcessingModuleTest, getImagePoint4Check) {
  ImageProcessingModule imageProcessor;
  EXPECT_EQ(0, imageProcessor.getImagePoint4());
}



/**
 * @brief Testing applyGrayScale method
 *
 * @param ImageProcessingModuleTest Name of the test suite
 *
 * @param applyGrayScaleCheck Name of the test
 */

TEST(ImageProcessingModuleTest, applyGrayScaleCheck) {
  ImageProcessingModule imageProcessor;
  cv::Mat image = cv::imread("../test_images/test_image1.jpg",
                             CV_LOAD_IMAGE_COLOR);

  EXPECT_EQ(1, (imageProcessor.applyGrayScale(image)).channels());
}

/**
 * @brief Testing applyGuassianBlur method
 *
 * @param ImageProcessingModuleTest Name of the test suite
 *
 * @param applyGuassianBlurCheck Name of the test
 */
TEST(ImageProcessingModuleTest, applyGaussianBlurCheck) {
  ImageProcessingModule imageProcessor;
  cv::Mat nonBlurImage = cv::Mat::ones(10, 10, CV_32FC1);
  nonBlurImage.at<float>(1, 1) = 0.5;
  int kernel = 3;
  /// initalise the Blur Image
  cv::Mat BlurImage = imageProcessor.applyGaussianBlur(nonBlurImage, kernel);
  EXPECT_NEAR(0.875, BlurImage.at<float>(1, 1), 0.1);
}

/**
 * @brief Testing applyCanny method
 *
 * @param ImageProcessingModuleTest Name of the test suite
 *
 * @param applyCannyCheck Name of the test
 */
TEST(ImageProcessingModuleTest, applyCannyCheck) {
  ImageProcessingModule imageProcessor;
  cv::Mat nonCannyImage = cv::Mat::ones(10, 10, CV_8UC1);
  nonCannyImage.at < uchar > (1, 1) = 0;
  int kernel = 5;
  double lowThreshold = 1;
  double highThreshold = 2;
  /// Initialise the canny Image
  cv::Mat cannyImage = imageProcessor.applyCanny(nonCannyImage, lowThreshold,
                                                 highThreshold, kernel);
  EXPECT_EQ(255, cannyImage.at < uchar > (0, 0));
}

/**
 * @brief Testing getHoughLines method
 *
 * @param ImageProcessingModuleTest Name of the test suite
 *
 * @param getHoughLinesCheck Name of the test
 */
TEST(ImageProcessingModuleTest, getHoughLinesCheck) {
  ImageProcessingModule imageProcessor;
  cv::Mat maskedGrayImage = cv::imread("../test_images/masked_gray.png",
                                     CV_LOAD_IMAGE_GRAYSCALE);
  /// distance resolution in pixels of the Hough grid
  int rho = 1;
  /// angular resolution in radians of the Hough grid
  double theta = 3.14 / 180;
  /// minimum number of votes (intersections in Hough grid cell)
  int threshold = 30;
  /// minimum number of pixels making up a line
  int minLineLen = 5;
  /// maximum gap in pixels between connectable line segments
  int maxLineGap = 50;
  std::vector < cv::Vec4i > lines = imageProcessor.getHoughLines(
      maskedGrayImage, rho, theta, threshold, minLineLen, maxLineGap);
  EXPECT_EQ(590, lines[0][0]);
}

/**
 * @brief Testing getDrawLines method
 *
 * @param ImageProcessingModuleTest Name of the test suite
 *
 * @param getDrawLinesCheck Name of the test
 */
TEST(ImageProcessingModuleTest, getDrawLinesCheck) {
  ImageProcessingModule imageProcessor;
  cv::Mat maskedGrayImage = cv::imread("../test_images/masked_gray.png",
                                     CV_LOAD_IMAGE_GRAYSCALE);
  /// distance resolution in pixels of the Hough grid
  int rho = 1;
  /// angular resolution in radians of the Hough grid
  double theta = 3.14 / 180;
  /// minimum number of votes (intersections in Hough grid cell)
  int threshold = 30;
  /// minimum number of pixels making up a line
  int minLineLen = 5;
  /// maximum gap in pixels between connectable line segments
  int maxLineGap = 50;
  std::vector < cv::Vec4i > lines = imageProcessor.getHoughLines(
      maskedGrayImage, rho, theta, threshold, minLineLen, maxLineGap);
  cv::Mat zerosImage = cv::Mat::zeros(maskedGrayImage.rows,
                                      maskedGrayImage.cols, CV_8UC3);
  cv::Scalar color = { 255, 0, 0 };
  int thickness = 5;
  /// Assigning values to line
  cv::Mat line = imageProcessor.getDrawLines(zerosImage, lines, color,
                                             thickness);
  EXPECT_EQ(0, static_cast<int>(line.at < uchar > (0, 0, 0)));
}

/**
 * @brief Testing getWeightedImage method
 *
 * @param ImageProcessingModuleTest Name of the test suite
 *
 * @param getWeightedImageCheck Name of the test
 */
TEST(ImageProcessingModuleTest, getWeightedImageCheck) {
  ImageProcessingModule imageProcessor;
  cv::Mat image1 = cv::Mat::ones(10, 10, CV_32FC3);
  cv::Mat image2 = cv::Mat::ones(10, 10, CV_32FC3);
  /// Getting weighted image
  cv::Mat newImage = imageProcessor.getWeightedImage(image1, image2);

  EXPECT_NEAR(1.8, newImage.at<float>(0, 0, 0), 0.1);
}

/**
 * @brief Testing generateImageWithText method
 *
 * @param ImageProcessingModuleTest Name of the test suite
 *
 * @param generateImageWithTextCheck Name of the test
 */
TEST(ImageProcessingModuleTest, generateImageWithTextCheck) {
  ImageProcessingModule imageProcessor;
  cv::Mat image1 = cv::imread("../test_images/test_image1.jpg",
                              CV_LOAD_IMAGE_COLOR);
  float value = 0.3;
  /// genertaing image with text
  cv::Mat newImage = imageProcessor.generateImageWithText(image1, value);
  EXPECT_EQ(203, static_cast<int>(newImage.at <uchar> (30, 30)));
}

/**
 * @brief Testing getRegionOfInterest method
 *
 * @param ImageProcessingModuleTest Name of the test suite
 *
 * @param getRegionOfInterestCheck Name of the test
 */
TEST(ImageProcessingModuleTest, getRegionOfInterestCheck) {
  ImageProcessingModule imageProcessor;
  cv::Mat maskedGrayImage = cv::imread("../test_images/masked_gray.png",
                                     CV_LOAD_IMAGE_GRAYSCALE);
  cv::Mat cannyImage = cv::imread("../test_images/canny.png",
                                  CV_LOAD_IMAGE_GRAYSCALE);
  cv::Mat newImage = imageProcessor.getRegionOfInterest(cannyImage);
  cv::Mat result;
  cv::compare(newImage, maskedGrayImage, result, cv::CMP_EQ);
  double percentage = (cv::countNonZero(result) * 1.0
      / (cannyImage.rows * cannyImage.cols)) * 100;
  EXPECT_NEAR(100, percentage, 5);
}
