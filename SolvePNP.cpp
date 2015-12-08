#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <string>

std::vector<cv::Point2f> Generate2DPoints();
std::vector<cv::Point3f> Generate3DPoints();

int main( int argc, char* argv[])
{
  // Read points
  std::vector<cv::Point2f> imagePoints = Generate2DPoints();
  std::vector<cv::Point3f> objectPoints = Generate3DPoints();

  std::cout << "There are " << imagePoints.size() << " imagePoints and " << objectPoints.size() << " objectPoints." << std::endl;

    //camera parameters
  double fx = 525.0; //focal length x
  double fy = 525.0; //focal le

  double cx = 319.5; //optical centre x
  double cy = 239.5; //optical centre y

  cv::Mat cameraMatrix(3,3,cv::DataType<double>::type);
  cameraMatrix.at<double>(0,0)=fx;
  cameraMatrix.at<double>(1,1)=fy;
  cameraMatrix.at<double>(2,2)=1;
  cameraMatrix.at<double>(0,2)=cx;
  cameraMatrix.at<double>(1,2)=cy;
  cameraMatrix.at<double>(0,1)=0;
  cameraMatrix.at<double>(1,0)=0;
  cameraMatrix.at<double>(2,0)=0;
  cameraMatrix.at<double>(2,1)=0;


  std::cout << "Initial cameraMatrix: " << cameraMatrix << std::endl;

  cv::Mat distCoeffs(4,1,cv::DataType<double>::type);
  distCoeffs.at<double>(0) = 0;
  distCoeffs.at<double>(1) = 0;
  distCoeffs.at<double>(2) = 0;
  distCoeffs.at<double>(3) = 0;

  cv::Mat rvec(3,1,cv::DataType<double>::type);
  cv::Mat tvec(3,1,cv::DataType<double>::type);

  cv::solvePnP(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec);

  std::cout << "rvec: " << rvec << std::endl;
  std::cout << "tvec: " << tvec << std::endl;

  std::vector<cv::Point2f> projectedPoints;
  cv::projectPoints(objectPoints, rvec, tvec, cameraMatrix, distCoeffs, projectedPoints);

  for(unsigned int i = 0; i < projectedPoints.size(); ++i)
    {
    std::cout << "Image point: " << imagePoints[i] << " Projected to " << projectedPoints[i] << std::endl;
    }

  return 0;
}


std::vector<cv::Point2f> Generate2DPoints()
{
  std::vector<cv::Point2f> points;

  float x,y;

  x=102;y=188;
  points.push_back(cv::Point2f(x,y));

  x=262;y=200;
  points.push_back(cv::Point2f(x,y));

  x=166;y=285;
  points.push_back(cv::Point2f(x,y));

  x=245;y=160;
  points.push_back(cv::Point2f(x,y));

  x=139;y=50;
  points.push_back(cv::Point2f(x,y));

  x=141;y=50;
  points.push_back(cv::Point2f(x,y));

  x=146;y=49;
  points.push_back(cv::Point2f(x,y));

  for(unsigned int i = 0; i < points.size(); ++i)
    {
    std::cout << points[i] << std::endl;
    }

  return points;
}


std::vector<cv::Point3f> Generate3DPoints()
{
  std::vector<cv::Point3f> points;
  float x, y, z;
  x=-0.114755; y=-0.0269169; z=0.278;
  points.push_back(cv::Point3f(x,y,z));

  x=-0.0320858; y=-0.0222269; z=0.2972;
  points.push_back(cv::Point3f(x,y,z));

  x=-0.0955657;	y=0.0290119; z=0.3282;
  points.push_back(cv::Point3f(x,y,z));

  x=0;y=0;z=0;
  points.push_back(cv::Point3f(x,y,z));

  x=-0.127569; y=-0.133924; z=0.3726;
  points.push_back(cv::Point3f(x,y,z));

  x=-0.126061; y=-0.133806; z=0.3726;
  points.push_back(cv::Point3f(x,y,z));

  x=0;y=0;z=0;
  points.push_back(cv::Point3f(x,y,z));

  for(unsigned int i = 0; i < points.size(); ++i)
    {
    std::cout << points[i] << std::endl;
    }

  return points;
}

