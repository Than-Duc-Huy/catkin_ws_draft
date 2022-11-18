#include <visp3/robot/vpSimulatorCamera.h>
#include <visp3/visual_features/vpFeatureBuilder.h>
#include <visp3/vs/vpServo.h>

int main()
{
    vpHomogeneousMatrix cdMo(0, 0, 0.75, 0, 0, 0);
    // Desired Pose of Object wrt to camera
    vpHomogeneousMatrix cMo(0.15, -0.1, 1.,
                            vpMath::rad(10), vpMath::rad(-10), vpMath::rad(50));
    // Object wrt to camera
    // How do you get these from the camera. Pose estimation

    // Set up the point in the simulation
    vpPoint point[4]; // Get the point of the object you are tracking
    point[0].setWorldCoordinates(-0.1, -0.1, 0);
    point[1].setWorldCoordinates(0.1, -0.1, 0);
    point[2].setWorldCoordinates(0.1, 0.1, 0);
    point[3].setWorldCoordinates(-0.1, 0.1, 0);



    vpServo task;
    task.setServo(vpServo::EYEINHAND_CAMERA);
    task.setInteractionMatrixType(vpServo::CURRENT);
    task.setLambda(0.5);

    vpFeaturePoint p[4], pd[4]; // point and desired points
    for (int i = 0; i < 4; i++)
    {
        point[i].track(cdMo);
        vpFeatureBuilder::create(pd[i], point[i]);
        point[i].track(cMo);
        vpFeatureBuilder::create(p[i], point[i]);
        task.addFeature(p[i], pd[i]);
    }

    vpHomogeneousMatrix wMc, wMo;
    vpSimulatorCamera robot;
    robot.setSamplingTime(0.040);
    robot.getPosition(wMc); // World to Camera = 0
    wMo = wMc * cMo;        // World to Object

    for (unsigned int iter = 0; iter < 150; iter++) //Keep looping
    {
        robot.getPosition(wMc);     // Use MoveIt to get this
        cMo = wMc.inverse() * wMo;   // Use Camera esmation
        for (int i = 0; i < 4; i++)
        {
            point[i].track(cMo);
            vpFeatureBuilder::create(p[i], point[i]);
        }
        vpColVector v = task.computeControlLaw();

        //Print out the velocity to console
        for (double i : v.toStdVector())
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;


        //Set the velocity and publish it to the Moveit Control node

        robot.setVelocity(vpRobot::CAMERA_FRAME, v);
    }


    task.kill();
}