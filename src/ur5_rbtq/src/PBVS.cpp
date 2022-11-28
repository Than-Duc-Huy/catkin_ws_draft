#include <visp/vpImage.h>
#include <visp_ros/vpROSGrabber.h>
#include <visp_ros/vpROSRobot.h>
#include <visp_bridge/image.h>
#include <visp_bridge/3dpose.h>

#include <visp3/gui/vpDisplayGDI.h>
#include <visp3/gui/vpDisplayX.h>
#include <visp3/detection/vpDetectorAprilTag.h>

#include <visp3/visual_features/vpFeatureThetaU.h>
#include <visp3/visual_features/vpFeatureTranslation.h>
#include <visp3/vs/vpServo.h>
#include <visp3/vs/vpServoDisplay.h>

#include <ros/ros.h>
#include <stdio.h>
#include <geometry_msgs/Pose.h>

int main(int argc, char **argv)
{
    vpImage<unsigned char> I; // Gray image container

    const std::string IMAGE_TOPC = "/camera/color/image_raw";
    // const std::string IMAGE_TOPC = "/webcam/image_rect";

    vpROSGrabber g;
    g.setImageTopic(IMAGE_TOPC);
    g.open(I);

    vpDisplayX d(I);

    //============= April Tag
    vpDetectorAprilTag::vpAprilTagFamily tagFamily = vpDetectorAprilTag::TAG_36h11;

    vpDetectorAprilTag::vpPoseEstimationMethod poseEstimationMethod = vpDetectorAprilTag::HOMOGRAPHY_VIRTUAL_VS;

    vpDetectorAprilTag detector(tagFamily);

    detector.setAprilTagPoseEstimationMethod(poseEstimationMethod);
    detector.setDisplayTag(true);
    detector.setAprilTagQuadDecimate(2);

    //  Servo
    vpHomogeneousMatrix cdMc, cMo;

    double opt_tagSize = 0.061;

    // Desired pose
    vpHomogeneousMatrix cdMo(vpTranslationVector(0.05, 0.05, opt_tagSize*4), vpRotationMatrix({1, 0, 0, 0, -1, 0, 0, 0, -1}));

    cdMc = cdMo * cMo.inverse();

    vpFeatureTranslation t(vpFeatureTranslation::cdMc);

    vpFeatureThetaU tu(vpFeatureThetaU::cdRc);

    t.buildFrom(cdMc); // build from the camera desired wrt cam
    tu.buildFrom(cdMc);

    vpFeatureTranslation td(vpFeatureTranslation::cdMc);

    vpFeatureThetaU tud(vpFeatureThetaU::cdRc);

    // Servo
    vpServo task;
    task.addFeature(t, td);
    task.addFeature(tu, tud);
    task.setServo(vpServo::EYEINHAND_CAMERA);
    task.setInteractionMatrixType(vpServo::CURRENT);
    task.setLambda(0.5);

    // Camera intrinsic
    vpCameraParameters cam;

    bool final_quit = false;
    bool has_converged = false;

    double const CONVERGENCE_THRESH_T = 0.0005, CONVERGENCE_THRESH_TU = vpMath::rad(0.5);


    vpColVector v_c(6);


    //ROS Component
    const std::string POSE_CHANGE_TOPIC = "/pose_change";
    const std::string OBJECT_POSE_TOPIC = "/object_pose";
    ros::init(argc, argv,"pbvs_visp");
    ros::NodeHandle n;
    ros::Publisher pub_pose_change = n.advertise<geometry_msgs::Pose>(POSE_CHANGE_TOPIC,100);
    ros::Publisher pub_object_pose = n.advertise<geometry_msgs::Pose>(OBJECT_POSE_TOPIC,100);



    while (!final_quit && !has_converged)
    {
        g.acquire(I);
        vpDisplay::setTitle(I, "ViSP");
        vpDisplay::display(I);
        // Visual Servoing Code

        std::vector<vpHomogeneousMatrix> cMo_vec;
        detector.detect(I, opt_tagSize, cam, cMo_vec);

        if (cMo_vec.size() == 1)
        {
            cMo = cMo_vec[0]; //cMo is from here

            // Visualise
            vpDisplay::displayFrame(I, cdMo, cam, opt_tagSize / 1, vpColor::yellow, 2);
            vpDisplay::displayFrame(I, cMo, cam, opt_tagSize / 1, vpColor::blue, 3);
            std::vector<vpImagePoint> vip = detector.getPolygon(0);


            geometry_msgs::Pose object_pose = visp_bridge::toGeometryMsgsPose(cMo);
            pub_object_pose.publish(object_pose);


            cdMc = cdMo * cMo.inverse();
            t.buildFrom(cdMc);
            tu.buildFrom(cdMc);


            v_c = task.computeControlLaw(); // Camera velocity
            v_c = (v_c);
            // Print out the velocity to console
            for (double i : v_c.toStdVector())
            {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
        else {
            v_c = 0;
        }

        // Velocity to change in position


        vpHomogeneousMatrix a;
        a.buildFrom(v_c[0], v_c[1],v_c[2],v_c[3],v_c[4],v_c[5]);
        // a.buildFrom(v_c[0], v_c[1],v_c[2],0,0,0);
        a.print();
        std::cout << std::endl;
        geometry_msgs::Pose desired_pose = visp_bridge::toGeometryMsgsPose(a);
        pub_pose_change.publish(desired_pose);

        vpDisplay::flush(I);
    }
}