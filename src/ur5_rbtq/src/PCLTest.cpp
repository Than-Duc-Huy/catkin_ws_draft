#include <iostream>
#include <ros/ros.h>
#include <tf/transform_listener.h>

#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>
#include <pcl/filters/passthrough.h>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/visualization/cloud_viewer.h>

class PCLNode
{
public:
    /*Constructor*/
    PCLNode(ros::NodeHandle n) : nh_(n), view("View")
    {
        std::cout << "PCL Test node running" << std::endl;
        const std::string CLOUD_TOPIC = "/camera/depth/color/points";
        cloud_sub_ = nh_.subscribe<pcl::PointCloud<pcl::PointXYZRGB>>(CLOUD_TOPIC, 1, &PCLNode::cloudCallback, this);

        // Set filter
        range_filter_.setFilterFieldName("z");
        range_filter_.setFilterLimits(0, 2.5);

        world_frame_ = "base_link";
    }

private:
    void cloudCallback(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr &cloud)
    {

        printf("Cloud has %d points\n", static_cast<int>(cloud->points.size()));
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZRGB>);
        range_filter_.setInputCloud(cloud);
        range_filter_.filter(*cloud_filtered);
        printf("Filterd has %d points\n", static_cast<int>(cloud_filtered->points.size()));


        //Transform to world coord
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_transformed(new pcl::PointCloud<pcl::PointXYZRGB>);
        if(!pcl_ros::transformPointCloud(world_frame_, *cloud_filtered, *cloud_transformed, listener_)){
            ROS_ERROR("Cannot transform");
        }
        view.showCloud(cloud_transformed);


    }

    std::string world_frame_;
    tf::TransformListener listener_;
    ros::NodeHandle nh_;
    ros::Subscriber cloud_sub_;
    pcl::PassThrough<pcl::PointXYZRGB> range_filter_;
    pcl::visualization::CloudViewer view;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pcl_node");
    ros::NodeHandle n;
    PCLNode node(n);
    ros::spin();
    return 0;
}