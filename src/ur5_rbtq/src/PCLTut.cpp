#include <pcl/filter.h>

cloud.width = 640;
cloud.height = 480;

pcl::PointCloud<pcl::PointXYZ> cloud; // This is the main type of the point cloud
std::vector<pcl::PointXYZ> data = cloud.points;

cloud.is_dense();
cloud.sensor_origin_(); // Return the origin of the sensor

#include <pcl_ros/point_cloud.h>
#include <ros/ros.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <boost/foreach.hpp>
#include <iostream>

std::string TOPIC = "/points2";

void callback(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &msg)
{
    printf("Cloud: widht %d, height %d\n", msg->width, msg->height);
    BOOST_FOREACH (const pcl::PointXYZ &pt, msg->points)
        printf("\t(%f, %f,%f)\n", pt.x, pt.y, pt.z);
}

int main(int argc, char **argv)
{
    //=================Sub
    ros::init(argc, argv, "sub_pcl");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<pcl::PointCloud<pcl::PointXYZ>>(TOPIC, 1, callback);

    //=================Pub
    ros::Publisher pub = nh.advertice<pcl::PointCloud<pcl::PointXYZ>>(TOPIC, 1);

    pcl::PointCloud<pcl::PointXYZ>::Ptr msg(new pcl::PointCloud<pcl::PointXYZ>) // New = allocate memory for this type with the pointer Ptr

        msg->header.frame_id = "frame";
    msg->height = msg->widt = 1; // Init only
    msg->points.push_back(pcl::PointXYZ(1.0, 2.0, 3.0));

    ros::Rate loop_rate(4);
    while (nh.ok())
    {
        pcl_conversion::toPCL(ros::Time::now(), msg->header.stamp); // Stampt the time to header
        pub.publish(*msg);                                          // Pass the value at the pointer
        ros::spinOnce();
        loop_rate.sleep();
    }

    ros::spin();
}

//============= Conversion between ROS and PCL point cloud type
void cloud_callback(const sensor_msgs::PointCloud2ConstPtr &cloud_msg)
{
    pcl::PCLPointCloud2 *cloud = new pcl::PCLPointCloud2; // WHy do we do this?, This is a reference to a pointer
    // pcl::PCLPointCloud2::Ptr cloud( new pcl::PointCloud2) // Can we do this instead?

    pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
    pcl::PCLPointCloud2 cloud_filtered;
    // Convert message to PCL data type
    pcl_conversion::toPCL(*cloud_msg, *cloud); // from left to right

    sensor_msgs::PointCloud2 output;
pcl_conversion:
    fromPCL(cloud_filtered, output);

    pub.publish(output);
}

#include <pcl/sample_consensus/model_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/segmentation/sac_segmentation.h>

pcl::PointCloud<pcl::PointXYZ> cloud;
pcl::fromROSMsg(*input, cloud);

pcl::ModelCoefficients coefficients;
pcl::PointIndices inliers;
pcl::SACSegmentation<pcl::PointXYZ> seg;
// Optional
seg.setOptimizeCoefficients(true);
// Important
seg.setModelType(pcl::SACMODEL_PLANE);
seg.setMethodType(pcl::SAC_RANSAC);
seg.setDistanceThreshold(0.01);

seg.setInputCloud(cloud.makeShared()); // What does makeShared do?
seg.segment(inliers, coefficients);

pcl_msgs::ModelCoefficients ros_coefficients;
pcl_conversions::fromPCL(coefficients, ros_coefficients);

pub - nh.advertise<pcl_msgs::ModelCoefficients>(TOPIC, 1); // This is a valid message from the catkin package pcl_msgs
// But shouldn't you include before sending? Where is the inclusion?

pub.publish(ros_coefficients);

//==================Filtering

//============= How 3D Feature works

// 3D feature estimation for example normal estimation
pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
ne.setInputCloud(cloudptr); // Pass the input cloud

std::vector<int> indices(10); // Use only 10 points
for (std::size_t i = 0; i < indices.size(); i++)
    indices[i] = i;

ne.setIndices(indice); // Pointer of indices
// Create a kdtree representation

pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>();
ne.setSearchMethod(tree);

pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>); //pointer

ne.setRadiusSearch(0.03); //Set the radius for the KdTree
ne.compute(*cloud_normals) // passing in the value of the pointer? why?



//============Transform the pointcloud

pcl:PointCloud<pcl::PointXYZ>::Ptr source_cloud (new pcl::PointCloud<pcl::PointXYZ>());

pcl:PointCloud<pcl::PointXYZ>::Ptr transformed_cloud (new pcl::PointCloud<pcl::PointXYZ>());
pcl::transformPointCloud (*source_cloud, *transformed_cloud, transform_2); // The transform is in Eigen

//============ Visualization


pcl::visualization::PCLVisualizer viewer ("Matrix transformation example");
// Define R,G,B colors for the point cloud
pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> source_cloud_color_handler (source_cloud, 255, 255, 255);
// We add the point cloud to the viewer and pass the color handler
viewer.addPointCloud (source_cloud, source_cloud_color_handler, "original_cloud");
pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_handler (transformed_cloud, 230, 20, 20); // Red
viewer.addPointCloud (transformed_cloud, transformed_cloud_color_handler, "transformed_cloud");
viewer.addCoordinateSystem (1.0, "cloud", 0);
viewer.setBackgroundColor(0.05, 0.05, 0.05, 0); // Setting background to a dark grey
viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "original_cloud");
viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloud");
 //viewer.setPosition(800, 400); // Setting visualiser window position

  while (!viewer.wasStopped ()) { // Display the visualiser until 'q' key is pressed
    viewer.spinOnce();
  }
