/*************************************************************
 * argv[1] : camera topic name (for eg: /BB2, /SonyX700_Left 
 * argv[2] : blob topic name 
 *            (will be publshed in /<cam_topic>/Feature/ColoBlobs<blob topic>
 * argv[3] :Minimum are of connected components
 ************************************************************************/

#include <ros/ros.h>
#include <pcl/features/feature.h>
#include <Image_msgs/FeatureMoments2D.h>
#include <feature_tracker/feature_blob_tracker.h>
#include <sensor_msgs/Image.h>
#include <geometry_msgs/Point.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/operations.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>

#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>
#include <pcl/features/feature.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/ros/conversions.h>

//#define DEBUG

using namespace std;
using namespace cv;
namespace enc = sensor_msgs::image_encodings;

#define MAX_FEATURES 10
#define DEFAULT_MIN_CC_THRESHOLD 200
#define DEFAULT_COLOR_BLOB_NUM 1
//#define DEFAULT_SOURCE_IDENTIFIER "/kinect/camera/rgb/points"
#define DEFAULT_SOURCE_IDENTIFIER "/stereo/right/image_raw"
#define DEFAULT_DISPLAY_IMAGE 1 
#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480


const double PI = 3.141592;

int init_primary_mean_color = 7;
int init_secondary_mean_color = 29;
int init_window_size = 2;
int init_blur_kernel = 8;



int mean_color = init_primary_mean_color;    //the color being search for +/- (window_size/2)
int primary_mean_color = init_primary_mean_color;
int secondary_mean_color = init_secondary_mean_color;
int test_color = mean_color;
int window_size = init_window_size;	 
int minCCThreshold = DEFAULT_MIN_CC_THRESHOLD;	//the minimum area (in pixels) for a connected component
const int maxNumComponents = MAX_FEATURES;  //the maximum number of connected components
int blurKernel = init_blur_kernel;    //the size of the Gaussian kernel
int width = DEFAULT_WIDTH;     //the width and height of the input image
int height = DEFAULT_HEIGHT;
    int redMin = 0;
    int redMax = 0;
    int greenMin = 0;
    int greenMax = 0;
    int blueMin = 0;
    int blueMax = 0;


float pos_x;
float pos_y;


typedef pcl::PointCloud<pcl::PointXYZRGB> PointCloudRGB;

void on_trackbar(int h, void *f) {
}

class ConnectedComp {	//class for connected components
public:
  ConnectedComp() {
    rank = 0;		     							
    area = 0;			
    idx = -1;
  }

  ~ConnectedComp() {
  }
	
  ConnectedComp(const ConnectedComp& source) 
  {
    idx = source.idx;
    rank = source.rank;
    area = source.area;
  }

  ConnectedComp& operator = (const ConnectedComp& source)
  {
    if (this != &source)
      {
	rank = source.rank;
	area = source.area;
	idx = source.idx;
      }
    return *this;
  }

  int rank;	       //rank of blob
  double area;         //area of blob
  int idx;	       //contour idx

};

class ColorBlobDetector {
protected:
  
  ros::NodeHandle n_;
  ros::Subscriber pointcloud_sub_;
  image_transport::ImageTransport it_;

  image_transport::Subscriber hue_sub_;
  image_transport::Subscriber rgb_sub_;
  image_transport::Publisher image_pub_;
  ros::Publisher uv_pub_;

  cv_bridge::CvImagePtr ptr_hue;
  cv_bridge::CvImagePtr ptr_rgb;

  VideoCapture cap;
  Mat frame;				    //the current frame being processed
  Mat cv_output_;				//the output image
  
  bool first;				       //first = true => initialize vars
  char color_topic[100];					//name for output topic
  char rgb_topic[100];					//name for input topic
  char hue_topic[100];					//name for input topic
  char pointcloud_topic[100];					//name for input topic
  char uv_topic[100];

  bool display_image_;
  int numCC;				     //the number of valid connected components
  int COLOR_LEGENDS[MAX_FEATURES][3];				//colors for display
  int ccMeans[MAX_FEATURES][2];			 //the means for storage

  vector <ConnectedComp> comps;			//array of connected components
  vector <vector <Point> > contours;	       //storage for linked list contours
  vector <Vec4i> hierarchy;

  FeatureBlobTracker *blobTracker;	 //Kalman filter and storage for blobs (across timesteps)
  Mat *flipped;				//image flipped vertically
  Mat *temp_blurred_image; 
  Mat *blurred_image;			//blurred images 
  Mat *color_cc_image;			//connected component image
  Mat* back_img;	       		//unknown use (output image?)
  /*Mat* back_hue;
  Mat* back_hue_two;
  Mat* back_one;
  Mat* back_two;
  Mat* back_three;
  Mat* back_four;
  Mat* back_five;
  Mat* back_red;
  Mat* back_green;
  Mat* back_blue;
  Mat* back_red_two;
  Mat* back_green_two;
  Mat* back_blue_two; */
  Mat back_hue;	
  Mat back_one;
  Mat* hue_image;		       //input image -> hue space
  Mat* sat_image;		       //input image -> satuation space
  Mat* int_image;		       //input image -> intensity space
  Mat* copy_image;	      		//a copy of cv_image
  Mat* rgb_image;	 		// rgb image from cameras
  Mat* hsv_image;		        // hsv image from cameras
  Mat red_img;
  Mat green_img;
  Mat blue_img;
  sensor_msgs::Image img;
  PointCloudRGB pcl_in;
  bool is_running;

public:
  
  ColorBlobDetector(ros::NodeHandle &n, char **argv) :
    n_(n), it_(n_) {
    
    first = true;
    
//Set default parameters if they are not already defined
    if (!n_.getParam("minCCThreshold", minCCThreshold)) {
      ROS_INFO("Could not retrieve 'minCCThreshold' parameter, setting to default value of '%d'", DEFAULT_MIN_CC_THRESHOLD);
      minCCThreshold = DEFAULT_MIN_CC_THRESHOLD;
    }
    
    if (!n_.getParam("display_image", display_image_)) {
      ROS_INFO("Could not retrieve 'display_image' parameter, setting to default value of '%d'", DEFAULT_DISPLAY_IMAGE);
      display_image_ = DEFAULT_DISPLAY_IMAGE;
    }	
    
    int color_blob_num;
    if (!n_.getParam("color_blob_num", color_blob_num)) {
      ROS_INFO("Could not retrieve 'color_blob_num' parameter, setting to default value of '%d'", DEFAULT_COLOR_BLOB_NUM);
      color_blob_num = DEFAULT_COLOR_BLOB_NUM;
    }
    
    std::string source_identifier;

    if (!n_.getParam("source_identifier", source_identifier)) {
      ROS_INFO("Could not retrieve 'source_identifier' parameter, setting to default value of '%s'", DEFAULT_SOURCE_IDENTIFIER);
      source_identifier = DEFAULT_SOURCE_IDENTIFIER;
    }


    
    //Not entirely clear on what this does
    sprintf(hue_topic, "%s", source_identifier.c_str());	//input topic
    sprintf(rgb_topic, "%s", source_identifier.c_str());	//input topic
    
    sprintf(color_topic, "%s/Feature/ColorBlobs%d", source_identifier.c_str(), color_blob_num);		//output topic
    sprintf(uv_topic, "%s/Feature/Center%d", source_identifier.c_str(), color_blob_num);
    
    printf("Topic name : %s\n", color_topic);
    
    //hue_sub_ = it_.subscribe(hue_topic, 1, &ColorBlobDetector::hueCallback, this);


    //Gets the most recently published image from the topic and activates the callback method
    rgb_sub_ = it_.subscribe(rgb_topic, 1, &ColorBlobDetector::rgbCallback, this);
    image_pub_ = it_.advertise(color_topic, 1);
    uv_pub_ = n_.advertise<geometry_msgs::Point>(uv_topic, 1);
    
	//Creates screen display if the boolean is set
    if (display_image_) {
      // Create a window
      namedWindow(color_topic, CV_WINDOW_AUTOSIZE);
      namedWindow("Color Blobs", CV_WINDOW_AUTOSIZE);
      namedWindow("Connected Components", CV_WINDOW_AUTOSIZE);
      
      // create a toolbar
      createTrackbar("Primary Mean Color", color_topic, &primary_mean_color, 255, &on_trackbar);
      //createTrackbar("source", color_topic, &source, 1, &on_trackbar);
      //createTrackbar("Secondary Mean Color", color_topic, &secondary_mean_color, 255, &on_trackbar);
      //createTrackbar("Window Size", color_topic, &window_size, 89, &on_trackbar);
      //createTrackbar("Blur Kernel", color_topic, &blurKernel, 25, &on_trackbar);
      //createTrackbar("redMin", color_topic, &redMin, 257, &on_trackbar);
      //createTrackbar("redMax", color_topic, &redMax, 257, &on_trackbar);
      //createTrackbar("greenMin", color_topic, &greenMin, 257, &on_trackbar);
      //createTrackbar("greenMax", color_topic, &greenMax, 257, &on_trackbar);
      //createTrackbar("blueMin", color_topic, &blueMin, 257, &on_trackbar);
      //createTrackbar("blueMax", color_topic, &blueMax, 257, &on_trackbar);
    }


	//Create matrices to store the three layers of the HSV image	
    hue_image = new Mat(height, width, CV_8UC1);
    sat_image = new Mat(height, width, CV_8UC1);
    int_image = new Mat(height, width, CV_8UC1);
    red_img = Mat(height, width, CV_8UC1);
    green_img = Mat(height, width, CV_8UC1);
    blue_img = Mat(height, width, CV_8UC1);
    back_hue = Mat(height, width, CV_8UC1);
    back_one = Mat(height, width, CV_8UC1);

	//Creates the blurred image, and other modifications
    back_img = new Mat(hue_image->size(), CV_8UC1);
    temp_blurred_image = new Mat(hue_image->size(), CV_8UC1);
    blurred_image = new Mat(hue_image->size(), CV_8UC1);
    color_cc_image = new Mat(hue_image->size(), CV_8UC3, Scalar(0));
    copy_image = new Mat(hue_image->size(), CV_8UC1);
    flipped = new Mat(hue_image->size(), CV_8UC1);
    rgb_image = new Mat(hue_image->size(), CV_8UC3);
    hsv_image = new Mat(hue_image->size(), CV_8UC3);
    
	//Blobtracker records the location of blobs between time frames (
    blobTracker = new FeatureBlobTracker(maxNumComponents, width, height);
    blobTracker->initialize();

    comps = vector<ConnectedComp>(); 
    contours = vector<vector<Point> >();
    hierarchy = vector<Vec4i>();

    comps.resize(maxNumComponents);
    is_running = false;

  }

  ~ColorBlobDetector() {
    comps.clear();
    contours.clear();
    hierarchy.clear(); 

    hue_image->release();
    back_img->release();
    temp_blurred_image->release();
    blurred_image->release();
    color_cc_image->release();
    copy_image->release();
    flipped->release();
    rgb_image->release();

    delete blobTracker;
  }

  int getThresholdConnectedComponents() {
    int count = 0;
    double area;

	//Array of doubles storing the area of each contour
    double contour_areas[(int)contours.size()];
	//
    for(int idx = 0; idx < (int)contours.size(); idx++){
	//Creates a vector of points to store the specific contour in question      
	vector<Point> approx;
      vector<Point> current = contours[idx];
      Mat m(current);
      m = abs(m);
      approxPolyDP(m, approx, 3, true);
      area = fabs(contourArea(Mat(approx)));
      contour_areas[idx] = area;
#ifdef DEBUG
      cout << "contour " << idx << " area: " << contour_areas[idx] << endl;
#endif
    }

	//Add the contours to the comps array by decreasing order of area
    for(count = 0; count < maxNumComponents;){
      int largestIdx = 0;
      int largestArea = 0;
      for(int idx = 0; idx < (int)contours.size(); idx++){
	if ((contour_areas[idx] > minCCThreshold) && (contour_areas[idx] > largestArea)){
	  largestArea = contour_areas[idx];
	  largestIdx = idx;		
	}
      }
      if(largestArea > minCCThreshold){
	comps[count].area = largestArea;
	comps[count].idx = largestIdx;
	//cout << "largest area " << largestArea << " idx: " << largestIdx << " count: " << count << endl;
	contour_areas[largestIdx] = 0;
	count++;
      }	
      else
	break;
    }
    for(int left = (count); left < maxNumComponents; left++){
      comps[left].area = -1;
      comps[left].idx = -1;
    }
#ifdef DEBUG
    cout << "Number of Connected Components " << count << endl;
#endif
    return (count);
  }

	//If there are any contours in the image, find them and perform thresholding
  void getConnectedComponents() {
    findContours(*back_img, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, Point());
    if(!contours.empty())
      numCC = getThresholdConnectedComponents();
  }


  void getMoments() {   
 
    blobTracker->reset();
   
	//Calculate moments for each connected component and add to the blob tracker
    Mat first(2,1,CV_32F);
    Mat second(2,2,CV_32F);
    for (int k = 0; (k < numCC) && (k < (int)comps.size()); k++) {
      if((comps[k].idx < (int)contours.size()) && (comps[k].idx >= 0)){
	vector<Point> current = contours[comps[k].idx];
	vector<Point> approx;
	Mat m(current);
	m = abs(m);
	approxPolyDP(m, approx, 3, true);
			
	m = Mat(approx);
	m = abs(m);
	Moments moment = moments(m);

	first.at<float>(0,0) = moment.m10/moment.m00;  //x mean
	first.at<float>(1,0) = moment.m01/moment.m00;	//y mean
	second.at<float>(0,0) = (moment.mu20/moment.m00);
	second.at<float>(0,1) = (moment.mu11/moment.m00);
	second.at<float>(1,0) = (moment.mu11/moment.m00);
	second.at<float>(1,1) = (moment.mu02/moment.m00);
	blobTracker->addNewMeasurement(first, second, k,"color",k);
	
	if (k == 0) {
		pos_x = moment.m10/moment.m00;
		pos_y = moment.m01/moment.m00;
	}
      }
    }

	//Past actual contours, set the other features invalid
    for (int k = numCC; k < MAX_FEATURES; k++)
      {
	
	first.at<float>(0,0) = -1;
	first.at<float>(1,0) = -1;
	second.at<float>(0,0) = 1; second.at<float>(0,1) = 0; second.at<float>(1,0) = 0; second.at<float>(1,1) = 1;
	blobTracker->addNewMeasurement(first, second, k,"color",k);
      }
    

    blobTracker->matchRawDataToEstimates(false, numCC);
  }

	//Called on each new image from the topic
  void rgbCallback(const sensor_msgs::ImageConstPtr& msg_ptr) {
    
	//Convert the image to OpenCV form
    try {
      ptr_rgb = cv_bridge::toCvCopy(msg_ptr, "bgr8");
      ptr_rgb->image.copyTo(*rgb_image);
    } catch (cv_bridge::Exception& e) {
      ROS_ERROR("cv_bridge exception: %s", e.what());
    }
    waitKey(2);

	//Create a test image
     if(first)
      {
	imwrite("test.jpg", *rgb_image);
	//	cvSaveImage("test.jpg" ,cv_image);
	first = false;
      }
    //try {
    //ptr_hue = cv_bridge::toCvCopy(msg_ptr, "8UC1");
    //imshow(ptr_ccs->image);
    //ptr_hue->image.copyTo(*hue_image);
    //} catch (cv_bridge::Exception& e) {
    //	ROS_ERROR("cv_bridge exception: %s", e.what());
    //}

	//Create a HSV image from the RGB image
    cvtColor(*rgb_image, *hsv_image, CV_BGR2HSV);

	//Split the three image channels into separate matrices 
    vector <Mat> planes;
    split(*hsv_image, planes);
    *hue_image = planes[0];
    *sat_image = planes[1];
    *int_image = planes[2];

	//Split the rgb image into red, blue, and green channels
    vector <Mat> rgb_planes;
    split(*rgb_image, rgb_planes);
    red_img = rgb_planes[0];
    green_img = rgb_planes[1];
    blue_img = rgb_planes[2];

	//Upper and lower bounds on hue values
    int rangeMin = (mean_color - window_size)%255;
    int rangeMax = (mean_color + window_size)%255;
    test_color = mean_color;

	
    if(rangeMin > rangeMax){
      int temp = rangeMax;
      rangeMax = rangeMin;
	//It looks like the should be =temp
      rangeMin = rangeMax;
    }

	
	//Create a binary image from the threshold
    //inRange(*hue_image, Scalar((double)rangeMin),Scalar((double)rangeMax),back_hue);
    back_hue = *hue_image;
   for (int i = 0; (i < height ); i++) {
      for (int j = 0; (j < width); j++) {
	if ((back_hue.at<Vec3b>(i,j)[0] >= rangeMin) && (back_hue.at<Vec3b>(i,j)[0] < rangeMax)){
           if ((((red_img.at<Vec3b>(i,j)[0] >= redMin) && (red_img.at<Vec3b>(i,j)[0] < redMax))
		&& ((green_img.at<Vec3b>(i,j)[1] >= greenMin) && (green_img.at<Vec3b>(i,j)[1] < greenMax)))
		&& ((blue_img.at<Vec3b>(i,j)[2] >= blueMin) && (blue_img.at<Vec3b>(i,j)[2] < blueMax))){
	  //if (abs(red_img.at<Vec3b>(i,j)[0] - green_img.at<Vec3b>(i,j)[0]) < 0){
		back_one.at<Vec3b>(i,j)[0] = 0;
	   }
	   else
 		back_one.at<Vec3b>(i,j)[0] = 255;
	};
      };
    }
   back_img = &back_one;
            
    
    *color_cc_image = Scalar(0);

	//Apply blur
    back_img->copyTo(*hue_image);
    Size ksize = Size(2 * blurKernel + 1,2 * blurKernel + 1);
    GaussianBlur(*back_img, *blurred_image, ksize, -1, -1);

    //attempts at adaptive thresholding
    Mat* sat_image;	  //input image -> satuation space
    //adaptiveThreshold(*blurred_image, *temp_blurred_image, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, .5);
    //threshold(*blurred_image, *temp_blurred_image, THRESH_OTSU, 255, THRESH_BINARY); 

    threshold(*blurred_image, *temp_blurred_image, 110, 255, THRESH_BINARY); 
    convertScaleAbs(*temp_blurred_image,*back_img, 1, 0);
    hue_image->copyTo(*copy_image);

    if (display_image_){
      imshow(color_topic, *back_img);
    }

    //Find Connected Components (this will populate the contour vector and perform ordering)
    getConnectedComponents();
    mean_color = primary_mean_color;

    if ((numCC == 0)&&(test_color == primary_mean_color)){
      mean_color = secondary_mean_color;
    }
	
	//Draw connected components	
    for (int i = 0; (i < (int)comps.size()) && (comps[i].idx >= 0) && (comps[i].idx < (int)contours.size()); i++) {
      Scalar color( (rand()&255), (rand()&255), (rand()&255) );
      drawContours(*color_cc_image, contours, comps[i].idx, color, 3, 8, hierarchy,0, Point());
      drawContours(*hue_image, contours, 0, comps[i].idx, 3, 8, hierarchy,0, Point());
    }

   getMoments();

    blobTracker->updateKalmanFiltersConnectedComponents();
    if (numCC > 0)
      blobTracker->getFilteredBlobs(true);
    else
      blobTracker->getFilteredBlobs(false);
    //cv::imshow("cam",hue_image);
    //Draw Filtered Blobs
    
    RotatedRect box;
    Point pt;
    //Image_msgs::FeatureMoments moments;
    //moments.num = 0;
	/*
   for(int i=0; i < 1; i++) //replaced MAX_FEATURES with 1
      {
	FeatureBlob ftemp;
	blobTracker->filters_[i].getFiltered(ftemp);
	//cout << "valid? " << ftemp.getValid() << endl;
	if(ftemp.getValid() && display_image_)
	  {
	    //cout << "Should be displaying something!" << endl;
	    Mat firstTemp, secondTemp;
	    ftemp.getValues(firstTemp, secondTemp);
	    pt.x = firstTemp.at<float>(0,0); pt.y = firstTemp.at<float>(1,0);
	    blobTracker->getBoxFromCov(pt, secondTemp, box);

	    if (box.size.width > 0 && box.size.height > 0 && box.size.width < width && box.size.height < height)
	      {
	      	ellipse(*rgb_image, box, CV_RGB(0,0,255), 3, 8);
		circle(*rgb_image, pt, 3, CV_RGB(255, 0, 0), -1, 8);
	      }	    

	  }
      } */
	pt.x = pos_x;
	pt.y = pos_y; 
	geometry_msgs::Point center;
	center.x = pt.x;
        center.y = pt.y;
        uv_pub_.publish(center);

	circle(*rgb_image, pt, 3, CV_RGB(255, 0, 0), -1, 8);
	

    //image_pub_.publish(moments);
    if (display_image_) {
      imshow("Color Blobs", *rgb_image);
      imshow("Connected Components", *color_cc_image);
    }
    waitKey(2);
  }
/*
	//Hue callback is not currently used
  void hueCallback(const sensor_msgs::ImageConstPtr& msg_ptr) {

    try {
      ptr_hue = cv_bridge::toCvCopy(msg_ptr, "8UC1");
      //imshow(ptr_hue->image);
      ptr_hue->image.copyTo(*hue_image);
    } catch (cv_bridge::Exception& e) {
      ROS_ERROR("cv_bridge exception: %s", e.what());
    }
		
    int rangeMin = (mean_color - window_size)%255;
    int rangeMax = (mean_color + window_size)%255;

    if(rangeMin > rangeMax){
      int temp = rangeMax;
      rangeMax = rangeMin;
      rangeMin = rangeMax;
    }
    cout << "range: " << rangeMin << " " << rangeMax << endl;
    inRange(*hue_image, Scalar((double)rangeMin),Scalar((double)rangeMax), *back_img);
    *color_cc_image = Scalar(0);
    back_img->copyTo(*hue_image);
    Size ksize = Size(2 * blurKernel + 1,2 * blurKernel + 1);
    GaussianBlur(*back_img, *blurred_image, ksize, -1, -1);

    //attempts at adaptive thresholding

    //adaptiveThreshold(*blurred_image, *temp_blurred_image, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, .5);
    //threshold(*blurred_image, *temp_blurred_image, THRESH_OTSU, 255, THRESH_BINARY); 

    threshold(*blurred_image, *temp_blurred_image, 110, 255, THRESH_BINARY); 
    convertScaleAbs(*temp_blurred_image, *back_img, 1, 0);
    hue_image->copyTo(*copy_image);

    if (display_image_){
      imshow(color_topic, *back_img);
    }

    //Find Connected Components
    getConnectedComponents();
		
    for (int i = 0; (i < (int)comps.size()) && (comps[i].idx >= 0) && (comps[i].idx < (int)contours.size()); i++) {
      Scalar color( (rand()&255), (rand()&255), (rand()&255) );
      drawContours(*color_cc_image, contours, comps[i].idx, color, 3, 8, hierarchy,0, Point());
      drawContours(*hue_image, contours, 0, comps[i].idx, 3, 8, hierarchy,0, Point());
    }

    getMoments();

    blobTracker->updateKalmanFiltersConnectedComponents();
    if (numCC > 0)
      blobTracker->getFilteredBlobs(true);
    else
      blobTracker->getFilteredBlobs(false);
    //cv::imshow("cam",hue_image);
    //Draw Filtered Blobs
    
    RotatedRect box;
    Point pt;
    //Image_msgs::FeatureMoments moments;
    //moments.num = 0;
    for(int i=0; i<MAX_FEATURES; i++)
      {
	FeatureBlob ftemp;
	blobTracker->filters_[i].getFiltered(ftemp);
	//cout << "valid? " << ftemp.getValid() << endl;
	if(ftemp.getValid() && display_image_)
	  {
	    //cout << "Should be displaying something!" << endl;
	    Mat firstTemp, secondTemp;
	    ftemp.getValues(firstTemp, secondTemp);
	    pt.x = firstTemp.at<float>(0,0); pt.y = firstTemp.at<float>(1,0);
	    blobTracker->getBoxFromCov(pt, secondTemp, box);

	    if (box.size.width > 0 && box.size.height > 0 && box.size.width < width && box.size.height < height)
	      {
		int octopus; 	      	
		//ellipse(*rgb_image, box, CV_RGB(0,255,255), 3, 8);
		//circle(*rgb_image, pt, 3, CV_RGB(255, 255, 255), -1, 8);
	      }	    

	  }
      }
    //image_pub_.publish(moments);
    if (display_image_) {
      imshow("Color Blobs", *rgb_image);
      imshow("Connected Components", *color_cc_image);
    }
    waitKey(2);
  }*/
  
};


	//Make visible as a ROS node
int main(int argc, char** argv) {
  ros::init(argc, argv, "ColorBlobDetector2D");
  ros::NodeHandle n ("~");

  ColorBlobDetector node(n, argv);
  ros::spin();

  return 0;
}
