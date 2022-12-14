#include <visp3/core/vpCameraParameters.h>
#include <visp3/detection/vpDetectorAprilTag.h>
#include <visp3/gui/vpDisplayOpenCV.h>
#include <visp3/gui/vpPlot.h>
#include <visp3/io/vpImageIo.h>
#include <visp3/visual_features/vpFeatureThetaU.h>
#include <visp3/visual_features/vpFeatureTranslation.h>
#include <visp3/vs/vpServo.h>
#include <visp3/vs/vpServoDisplay.h>

#include <visp3/robot/vpRobotFranka.h>
#include <visp3/sensor/vpRealSense2.h>

void display_point_trajectory(const vpImage<unsigned char> &I, const std::vector<vpImagePoint> &vip,
                              std::vector<vpImagePoint> *traj_vip)
{
    for (size_t i = 0; i < vip.size(); i++)
    {
        if (traj_vip[i].size())
        {
            // Add the point only if distance with the previous > 1 pixel
            if (vpImagePoint::distance(vip[i], traj_vip[i].back()) > 1.)
            {
                traj_vip[i].push_back(vip[i]);
            }
        }
        else
        {
            traj_vip[i].push_back(vip[i]);
        }
    }
    for (size_t i = 0; i < vip.size(); i++)
    {
        for (size_t j = 1; j < traj_vip[i].size(); j++)
        {
            vpDisplay::displayLine(I, traj_vip[i][j - 1], traj_vip[i][j], vpColor::green, 2);
        }
    }
}


nt
main( int argc, char **argv )
{
  double opt_tagSize             = 0.08;
  std::string opt_robot_ip       = "192.168.1.1";
  std::string opt_eMc_filename   = "";
  bool display_tag               = true;
  int opt_quad_decimate          = 2;
  bool opt_verbose               = false;
  bool opt_plot                  = false;
  bool opt_adaptive_gain         = false;
  bool opt_task_sequencing       = false;
  double convergence_threshold_t = 0.0005, convergence_threshold_tu = vpMath::rad( 0.5 );

  for ( int i = 1; i < argc; i++ )
  {
    if ( std::string( argv[i] ) == "--tag_size" && i + 1 < argc )
    {
      opt_tagSize = std::stod( argv[i + 1] );
    }
    else if ( std::string( argv[i] ) == "--ip" && i + 1 < argc )
    {
      opt_robot_ip = std::string( argv[i + 1] );
    }
    else if ( std::string( argv[i] ) == "--eMc" && i + 1 < argc )
    {
      opt_eMc_filename = std::string( argv[i + 1] );
    }
    else if ( std::string( argv[i] ) == "--verbose" )
    {
      opt_verbose = true;
    }
    else if ( std::string( argv[i] ) == "--plot" )
    {
      opt_plot = true;
    }
    else if ( std::string( argv[i] ) == "--adaptive_gain" )
    {
      opt_adaptive_gain = true;
    }
    else if ( std::string( argv[i] ) == "--task_sequencing" )
    {
      opt_task_sequencing = true;
    }
    else if ( std::string( argv[i] ) == "--quad_decimate" && i + 1 < argc )
    {
      opt_quad_decimate = std::stoi( argv[i + 1] );
    }
    else if ( std::string( argv[i] ) == "--no-convergence-threshold" )
    {
      convergence_threshold_t  = 0.;
      convergence_threshold_tu = 0.;
    }
    else if ( std::string( argv[i] ) == "--help" || std::string( argv[i] ) == "-h" )
    {
      std::cout
          << argv[0] << " [--ip <default " << opt_robot_ip << ">] "
          << "[--tag_size <marker size in meter; default " << opt_tagSize << ">] [--eMc <eMc extrinsic file>] "
          << "[--quad_decimate <decimation; default " << opt_quad_decimate
          << ">] [--adaptive_gain] [--plot] [--task_sequencing] [--no-convergence-threshold] [--verbose] [--help] [-h]"
          << "\n";
      return EXIT_SUCCESS;
    }
  }

  vpRobotFranka robot;

  try
  {
    std::cout << "Try to connect to robot ip: " << opt_robot_ip << std::endl;
    robot.connect( opt_robot_ip );
    std::cout << "Panda robot connected" << std::endl;

    vpRealSense2 rs;
    rs2::config config;
    unsigned int width = 640, height = 480;
    config.enable_stream( RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_RGBA8, 30 );
    config.enable_stream( RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30 );
    config.enable_stream( RS2_STREAM_INFRARED, 640, 480, RS2_FORMAT_Y8, 30 );
    std::cout << "Try to connect to Realsense camera " << std::endl;
    rs.open( config );
    std::cout << "Camera connected" << std::endl;

    // Get camera extrinsics
    vpPoseVector ePc;
    // Set camera extrinsics default values corresponding to
    // - an Intel RealSense D435 camera
    // - attached to the Franka end-effector using the mechanical interface corresponding to
    //   the cad model given in franka-rs-D435-camera-holder.stl file
    ePc[0] = 0.0564668;
    ePc[1] = -0.0375079;
    ePc[2] = -0.150416 ;
    ePc[3] = 0.0102548;
    ePc[4] = -0.0012236;
    ePc[5] = 1.5412;

    // If provided, read camera extrinsics from --eMc <file>
    if ( !opt_eMc_filename.empty() )
    {
      ePc.loadYAML( opt_eMc_filename, ePc );
    }
    else
    {
      std::cout << "Warning, opt_eMc_filename is empty! Use hard coded values."
                << "\n";
    }
    vpHomogeneousMatrix eMc( ePc );
    std::cout << "eMc:\n" << eMc << "\n";
    std::cout << "ePc:\n" << vpPoseVector(eMc).t() << "\n";

    // Get camera intrinsics
    vpCameraParameters cam =
        rs.getCameraParameters( RS2_STREAM_COLOR, vpCameraParameters::perspectiveProjWithDistortion );
    std::cout << "cam:\n" << cam << "\n";

    vpImage< unsigned char > I( height, width );

    vpDisplayOpenCV dc( I, 10, 10, "Color image" );

    vpDetectorAprilTag::vpAprilTagFamily tagFamily                  = vpDetectorAprilTag::TAG_36h11;
    vpDetectorAprilTag::vpPoseEstimationMethod poseEstimationMethod = vpDetectorAprilTag::HOMOGRAPHY_VIRTUAL_VS;
    // vpDetectorAprilTag::vpPoseEstimationMethod poseEstimationMethod = vpDetectorAprilTag::BEST_RESIDUAL_VIRTUAL_VS;
    vpDetectorAprilTag detector( tagFamily );
    detector.setAprilTagPoseEstimationMethod( poseEstimationMethod );
    detector.setDisplayTag( display_tag );
    detector.setAprilTagQuadDecimate( opt_quad_decimate );

    // Servo
    vpHomogeneousMatrix cdMc, cMo, oMo;

    // Desired pose to reach
    vpHomogeneousMatrix cdMo( vpTranslationVector( 0, 0, opt_tagSize * 3 ), // 3 times tag with along camera z axis
                              vpRotationMatrix( { 1, 0, 0, 0, -1, 0, 0, 0, -1 } ) );

    cdMc = cdMo * cMo.inverse();
    vpFeatureTranslation t( vpFeatureTranslation::cdMc );
    vpFeatureThetaU tu( vpFeatureThetaU::cdRc );
    t.buildFrom( cdMc );
    tu.buildFrom( cdMc );

    vpFeatureTranslation td( vpFeatureTranslation::cdMc );
    vpFeatureThetaU tud( vpFeatureThetaU::cdRc );

    vpServo task;
    task.addFeature( t, td );
    task.addFeature( tu, tud );
    task.setServo( vpServo::EYEINHAND_CAMERA );
    task.setInteractionMatrixType( vpServo::CURRENT );

    if ( opt_adaptive_gain )
    {
      vpAdaptiveGain lambda( 1.5, 0.4, 30 ); // lambda(0)=4, lambda(oo)=0.4 and lambda'(0)=30
      task.setLambda( lambda );
    }
    else
    {
      task.setLambda( 0.5 );
    }

    vpPlot *plotter = nullptr;
    int iter_plot   = 0;

    if ( opt_plot )
    {
      plotter = new vpPlot( 2, static_cast< int >( 250 * 2 ), 500, static_cast< int >( I.getWidth() ) + 80, 10,
                            "Real time curves plotter" );
      plotter->setTitle( 0, "Visual features error" );
      plotter->setTitle( 1, "Camera velocities" );
      plotter->initGraph( 0, 6 );
      plotter->initGraph( 1, 6 );
      plotter->setLegend( 0, 0, "error_feat_tx" );
      plotter->setLegend( 0, 1, "error_feat_ty" );
      plotter->setLegend( 0, 2, "error_feat_tz" );
      plotter->setLegend( 0, 3, "error_feat_theta_ux" );
      plotter->setLegend( 0, 4, "error_feat_theta_uy" );
      plotter->setLegend( 0, 5, "error_feat_theta_uz" );
      plotter->setLegend( 1, 0, "vc_x" );
      plotter->setLegend( 1, 1, "vc_y" );
      plotter->setLegend( 1, 2, "vc_z" );
      plotter->setLegend( 1, 3, "wc_x" );
      plotter->setLegend( 1, 4, "wc_y" );
      plotter->setLegend( 1, 5, "wc_z" );
    }

    bool final_quit                       = false;
    bool has_converged                    = false;
    bool send_velocities                  = false;
    bool servo_started                    = false;
    std::vector< vpImagePoint > *traj_vip = nullptr; // To memorize point trajectory

    static double t_init_servo = vpTime::measureTimeMs();

    robot.set_eMc( eMc ); // Set location of the camera wrt end-effector frame
    robot.setRobotState( vpRobot::STATE_VELOCITY_CONTROL );

    while ( !has_converged && !final_quit )
    {
      double t_start = vpTime::measureTimeMs();

      rs.acquire( I );

      vpDisplay::display( I );

      std::vector< vpHomogeneousMatrix > cMo_vec;
      detector.detect( I, opt_tagSize, cam, cMo_vec );

      std::stringstream ss;
      ss << "Left click to " << ( send_velocities ? "stop the robot" : "servo the robot" ) << ", right click to quit.";
      vpDisplay::displayText( I, 20, 20, ss.str(), vpColor::red );

      vpColVector v_c( 6 );

      // Only one tag is detected
      if ( cMo_vec.size() == 1 )
      {
        cMo = cMo_vec[0];

        static bool first_time = true;
        if ( first_time )
        {
          // Introduce security wrt tag positionning in order to avoid PI rotation
          std::vector< vpHomogeneousMatrix > v_oMo( 2 ), v_cdMc( 2 );
          v_oMo[1].buildFrom( 0, 0, 0, 0, 0, M_PI );
          for ( size_t i = 0; i < 2; i++ )
          {
            v_cdMc[i] = cdMo * v_oMo[i] * cMo.inverse();
          }
          if ( std::fabs( v_cdMc[0].getThetaUVector().getTheta() ) <
               std::fabs( v_cdMc[1].getThetaUVector().getTheta() ) )
          {
            oMo = v_oMo[0];
          }
          else
          {
            std::cout << "Desired frame modified to avoid PI rotation of the camera" << std::endl;
            oMo = v_oMo[1]; // Introduce PI rotation
          }
        }

        // Update visual features
        cdMc = cdMo * oMo * cMo.inverse();
        t.buildFrom( cdMc );
        tu.buildFrom( cdMc );

        if ( opt_task_sequencing )
        {
          if ( !servo_started )
          {
            if ( send_velocities )
            {
              servo_started = true;
            }
            t_init_servo = vpTime::measureTimeMs();
          }
          v_c = task.computeControlLaw( ( vpTime::measureTimeMs() - t_init_servo ) / 1000. );
        }
        else
        {
          v_c = task.computeControlLaw();
        }

        // Display desired and current pose features
        vpDisplay::displayFrame( I, cdMo * oMo, cam, opt_tagSize / 1.5, vpColor::yellow, 2 );
        vpDisplay::displayFrame( I, cMo, cam, opt_tagSize / 2, vpColor::none, 3 );
        // Get tag corners
        std::vector< vpImagePoint > vip = detector.getPolygon( 0 );
        // Get the tag cog corresponding to the projection of the tag frame in the image
        vip.push_back( detector.getCog( 0 ) );
        // Display the trajectory of the points
        if ( first_time )
        {
          traj_vip = new std::vector< vpImagePoint >[vip.size()];
        }
        display_point_trajectory( I, vip, traj_vip );

        if ( opt_plot )
        {
          plotter->plot( 0, iter_plot, task.getError() );
          plotter->plot( 1, iter_plot, v_c );
          iter_plot++;
        }

        if ( opt_verbose )
        {
          std::cout << "v_c: " << v_c.t() << std::endl;
        }

        vpTranslationVector cd_t_c = cdMc.getTranslationVector();
        vpThetaUVector cd_tu_c     = cdMc.getThetaUVector();
        double error_tr            = sqrt( cd_t_c.sumSquare() );
        double error_tu            = vpMath::deg( sqrt( cd_tu_c.sumSquare() ) );

        ss.str( "" );
        ss << "error_t: " << error_tr;
        vpDisplay::displayText( I, 20, static_cast< int >( I.getWidth() ) - 150, ss.str(), vpColor::red );
        ss.str( "" );
        ss << "error_tu: " << error_tu;
        vpDisplay::displayText( I, 40, static_cast< int >( I.getWidth() ) - 150, ss.str(), vpColor::red );

        if ( opt_verbose )
          std::cout << "error translation: " << error_tr << " ; error rotation: " << error_tu << std::endl;

        if ( error_tr < convergence_threshold_t && error_tu < convergence_threshold_tu )
        {
          has_converged = true;
          std::cout << "Servo task has converged" << std::endl;
          ;
          vpDisplay::displayText( I, 100, 20, "Servo task has converged", vpColor::red );
        }

        if ( first_time )
        {
          first_time = false;
        }
      } // end if (cMo_vec.size() == 1)
      else
      {
        v_c = 0;
      }

      if ( !send_velocities )
      {
        v_c = 0;
      }

      // Send to the robot
      robot.setVelocity( vpRobot::CAMERA_FRAME, v_c );

      ss.str( "" );
      ss << "Loop time: " << vpTime::measureTimeMs() - t_start << " ms";
      vpDisplay::displayText( I, 40, 20, ss.str(), vpColor::red );
      vpDisplay::flush( I );

      vpMouseButton::vpMouseButtonType button;
      if ( vpDisplay::getClick( I, button, false ) )
      {
        switch ( button )
        {
        case vpMouseButton::button1:
          send_velocities = !send_velocities;
          break;

        case vpMouseButton::button3:
          final_quit = true;
          v_c        = 0;
          break;

        default:
          break;
        }
      }
    }
    std::cout << "Stop the robot " << std::endl;
    robot.setRobotState( vpRobot::STATE_STOP );

    if ( opt_plot && plotter != nullptr )
    {
      delete plotter;
      plotter = nullptr;
    }

    if ( !final_quit )
    {
      while ( !final_quit )
      {
        rs.acquire( I );
        vpDisplay::display( I );

        vpDisplay::displayText( I, 20, 20, "Click to quit the program.", vpColor::red );
        vpDisplay::displayText( I, 40, 20, "Visual servo converged.", vpColor::red );

        if ( vpDisplay::getClick( I, false ) )
        {
          final_quit = true;
        }

        vpDisplay::flush( I );
      }
    }

    if ( traj_vip )
    {
      delete[] traj_vip;
    }
  }
  catch ( const vpException &e )
  {
    std::cout << "ViSP exception: " << e.what() << std::endl;
    std::cout << "Stop the robot " << std::endl;
    robot.setRobotState( vpRobot::STATE_STOP );
    return EXIT_FAILURE;
  }
  catch ( const franka::NetworkException &e )
  {
    std::cout << "Franka network exception: " << e.what() << std::endl;
    std::cout << "Check if you are connected to the Franka robot"
              << " or if you specified the right IP using --ip command line option set by default to 192.168.1.1. "
              << std::endl;
    return EXIT_FAILURE;
  }
  catch ( const std::exception &e )
  {
    std::cout << "Franka exception: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return 0;
}