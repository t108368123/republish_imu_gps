#include <ros/ros.h>
#include <string> 
#include <iostream> 
#include <sensor_msgs/NavSatFix.h> 
using namespace std;

ros::Publisher gps_pub;

void gps_callback(const sensor_msgs::NavSatFix::ConstPtr& msg)
{ 
    sensor_msgs:: NavSatFix gps_data;
    gps_data.header.stamp = msg->header.stamp;
    gps_data.header.frame_id = "navsat_link";
    gps_data.status = msg->status;
    gps_data.latitude = msg->latitude;
    gps_data.longitude = msg->longitude;
    gps_data.altitude = msg->altitude;
    gps_data.position_covariance = msg->position_covariance;
    gps_data.position_covariance_type = msg->position_covariance_type;
    gps_pub.publish(gps_data);
}  

int main(int argc, char **argv)
{ 
    ros::init(argc, argv, "republish_frameid_gps");
    cout << "republish_frameid_gps start" << endl;

    ros::NodeHandle nh_;
    gps_pub = nh_.advertise<sensor_msgs::NavSatFix>("/gps/reframe_id", 10);
    ros::Subscriber imu_sub = nh_.subscribe("/fix", 10, gps_callback); 

    ros::spin(); 
    return 0; 
}
