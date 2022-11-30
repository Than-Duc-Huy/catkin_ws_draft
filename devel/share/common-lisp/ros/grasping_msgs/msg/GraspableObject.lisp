; Auto-generated. Do not edit!


(cl:in-package grasping_msgs-msg)


;//! \htmlinclude GraspableObject.msg.html

(cl:defclass <GraspableObject> (roslisp-msg-protocol:ros-message)
  ((object
    :reader object
    :initarg :object
    :type grasping_msgs-msg:Object
    :initform (cl:make-instance 'grasping_msgs-msg:Object))
   (grasps
    :reader grasps
    :initarg :grasps
    :type (cl:vector moveit_msgs-msg:Grasp)
   :initform (cl:make-array 0 :element-type 'moveit_msgs-msg:Grasp :initial-element (cl:make-instance 'moveit_msgs-msg:Grasp))))
)

(cl:defclass GraspableObject (<GraspableObject>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GraspableObject>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GraspableObject)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name grasping_msgs-msg:<GraspableObject> is deprecated: use grasping_msgs-msg:GraspableObject instead.")))

(cl:ensure-generic-function 'object-val :lambda-list '(m))
(cl:defmethod object-val ((m <GraspableObject>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader grasping_msgs-msg:object-val is deprecated.  Use grasping_msgs-msg:object instead.")
  (object m))

(cl:ensure-generic-function 'grasps-val :lambda-list '(m))
(cl:defmethod grasps-val ((m <GraspableObject>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader grasping_msgs-msg:grasps-val is deprecated.  Use grasping_msgs-msg:grasps instead.")
  (grasps m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GraspableObject>) ostream)
  "Serializes a message object of type '<GraspableObject>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'object) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'grasps))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'grasps))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GraspableObject>) istream)
  "Deserializes a message object of type '<GraspableObject>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'object) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'grasps) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'grasps)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'moveit_msgs-msg:Grasp))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GraspableObject>)))
  "Returns string type for a message object of type '<GraspableObject>"
  "grasping_msgs/GraspableObject")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GraspableObject)))
  "Returns string type for a message object of type 'GraspableObject"
  "grasping_msgs/GraspableObject")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GraspableObject>)))
  "Returns md5sum for a message object of type '<GraspableObject>"
  "ec31ebe9db31c8d3ccab1b66aedd1293")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GraspableObject)))
  "Returns md5sum for a message object of type 'GraspableObject"
  "ec31ebe9db31c8d3ccab1b66aedd1293")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GraspableObject>)))
  "Returns full string definition for message of type '<GraspableObject>"
  (cl:format cl:nil "###########################################################~%# This message describes an object + grasp data~%Object object~%moveit_msgs/Grasp[] grasps~%~%================================================================================~%MSG: grasping_msgs/Object~%###########################################################~%# This message describes an object.~%~%# Many of the geometric items below lack a stamp/frame_id,~%# header stamp/frame_id should be used there~%std_msgs/Header header~%~%# An object might have a name~%string name~%~%# An object might have a known (named) support surface~%string support_surface~%~%# Objects might have properties, such as type/class, or color, etc.~%ObjectProperty[] properties~%~%###########################################################~%# Objects have many possible descriptions~%#  The following are the possible description formats~%~%# Perception modules often represent an object as a cluster of points~%#  Is considered valid if number of points > 0~%sensor_msgs/PointCloud2 point_cluster~%~%# MoveIt prefers solid primitives or meshes as a description of objects~%shape_msgs/SolidPrimitive[] primitives~%geometry_msgs/Pose[] primitive_poses~%~%shape_msgs/Mesh[] meshes~%geometry_msgs/Pose[] mesh_poses~%~%# An object representing a support surface might be described by a plane~%# Is considered valid if coefficients are not all 0s.~%shape_msgs/Plane surface~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: grasping_msgs/ObjectProperty~%###########################################################~%# Other generic properties of an object~%string name~%string value~%~%================================================================================~%MSG: sensor_msgs/PointCloud2~%# This message holds a collection of N-dimensional points, which may~%# contain additional information such as normals, intensity, etc. The~%# point data is stored as a binary blob, its layout described by the~%# contents of the \"fields\" array.~%~%# The point cloud data may be organized 2d (image-like) or 1d~%# (unordered). Point clouds organized as 2d images may be produced by~%# camera depth sensors such as stereo or time-of-flight.~%~%# Time of sensor data acquisition, and the coordinate frame ID (for 3d~%# points).~%Header header~%~%# 2D structure of the point cloud. If the cloud is unordered, height is~%# 1 and width is the length of the point cloud.~%uint32 height~%uint32 width~%~%# Describes the channels and their layout in the binary data blob.~%PointField[] fields~%~%bool    is_bigendian # Is this data bigendian?~%uint32  point_step   # Length of a point in bytes~%uint32  row_step     # Length of a row in bytes~%uint8[] data         # Actual point data, size is (row_step*height)~%~%bool is_dense        # True if there are no invalid points~%~%================================================================================~%MSG: sensor_msgs/PointField~%# This message holds the description of one point entry in the~%# PointCloud2 message format.~%uint8 INT8    = 1~%uint8 UINT8   = 2~%uint8 INT16   = 3~%uint8 UINT16  = 4~%uint8 INT32   = 5~%uint8 UINT32  = 6~%uint8 FLOAT32 = 7~%uint8 FLOAT64 = 8~%~%string name      # Name of field~%uint32 offset    # Offset from start of point struct~%uint8  datatype  # Datatype enumeration, see above~%uint32 count     # How many elements in the field~%~%================================================================================~%MSG: shape_msgs/SolidPrimitive~%# Define box, sphere, cylinder, cone ~%# All shapes are defined to have their bounding boxes centered around 0,0,0.~%~%uint8 BOX=1~%uint8 SPHERE=2~%uint8 CYLINDER=3~%uint8 CONE=4~%~%# The type of the shape~%uint8 type~%~%~%# The dimensions of the shape~%float64[] dimensions~%~%# The meaning of the shape dimensions: each constant defines the index in the 'dimensions' array~%~%# For the BOX type, the X, Y, and Z dimensions are the length of the corresponding~%# sides of the box.~%uint8 BOX_X=0~%uint8 BOX_Y=1~%uint8 BOX_Z=2~%~%~%# For the SPHERE type, only one component is used, and it gives the radius of~%# the sphere.~%uint8 SPHERE_RADIUS=0~%~%~%# For the CYLINDER and CONE types, the center line is oriented along~%# the Z axis.  Therefore the CYLINDER_HEIGHT (CONE_HEIGHT) component~%# of dimensions gives the height of the cylinder (cone).  The~%# CYLINDER_RADIUS (CONE_RADIUS) component of dimensions gives the~%# radius of the base of the cylinder (cone).  Cone and cylinder~%# primitives are defined to be circular. The tip of the cone is~%# pointing up, along +Z axis.~%~%uint8 CYLINDER_HEIGHT=0~%uint8 CYLINDER_RADIUS=1~%~%uint8 CONE_HEIGHT=0~%uint8 CONE_RADIUS=1~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: shape_msgs/Mesh~%# Definition of a mesh~%~%# list of triangles; the index values refer to positions in vertices[]~%MeshTriangle[] triangles~%~%# the actual vertices that make up the mesh~%geometry_msgs/Point[] vertices~%~%================================================================================~%MSG: shape_msgs/MeshTriangle~%# Definition of a triangle's vertices~%uint32[3] vertex_indices~%~%================================================================================~%MSG: shape_msgs/Plane~%# Representation of a plane, using the plane equation ax + by + cz + d = 0~%~%# a := coef[0]~%# b := coef[1]~%# c := coef[2]~%# d := coef[3]~%~%float64[4] coef~%~%================================================================================~%MSG: moveit_msgs/Grasp~%# This message contains a description of a grasp that would be used~%# with a particular end-effector to grasp an object, including how to~%# approach it, grip it, etc.  This message does not contain any~%# information about a \"grasp point\" (a position ON the object).~%# Whatever generates this message should have already combined~%# information about grasp points with information about the geometry~%# of the end-effector to compute the grasp_pose in this message.~%~%# A name for this grasp~%string id~%~%# The internal posture of the hand for the pre-grasp~%# only positions are used~%trajectory_msgs/JointTrajectory pre_grasp_posture~%~%# The internal posture of the hand for the grasp~%# positions and efforts are used~%trajectory_msgs/JointTrajectory grasp_posture~%~%# The position of the end-effector for the grasp.  This is the pose of~%# the \"parent_link\" of the end-effector, not actually the pose of any~%# link *in* the end-effector.  Typically this would be the pose of the~%# most distal wrist link before the hand (end-effector) links began.~%geometry_msgs/PoseStamped grasp_pose~%~%# The estimated probability of success for this grasp, or some other~%# measure of how \"good\" it is.~%float64 grasp_quality~%~%# The approach direction to take before picking an object~%GripperTranslation pre_grasp_approach~%~%# The retreat direction to take after a grasp has been completed (object is attached)~%GripperTranslation post_grasp_retreat~%~%# The retreat motion to perform when releasing the object; this information~%# is not necessary for the grasp itself, but when releasing the object,~%# the information will be necessary. The grasp used to perform a pickup~%# is returned as part of the result, so this information is available for~%# later use.~%GripperTranslation post_place_retreat~%~%# the maximum contact force to use while grasping (<=0 to disable)~%float32 max_contact_force~%~%# an optional list of obstacles that we have semantic information about~%# and that can be touched/pushed/moved in the course of grasping~%string[] allowed_touch_objects~%~%================================================================================~%MSG: trajectory_msgs/JointTrajectory~%Header header~%string[] joint_names~%JointTrajectoryPoint[] points~%~%================================================================================~%MSG: trajectory_msgs/JointTrajectoryPoint~%# Each trajectory point specifies either positions[, velocities[, accelerations]]~%# or positions[, effort] for the trajectory to be executed.~%# All specified values are in the same order as the joint names in JointTrajectory.msg~%~%float64[] positions~%float64[] velocities~%float64[] accelerations~%float64[] effort~%duration time_from_start~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: moveit_msgs/GripperTranslation~%# defines a translation for the gripper, used in pickup or place tasks~%# for example for lifting an object off a table or approaching the table for placing~%~%# the direction of the translation~%geometry_msgs/Vector3Stamped direction~%~%# the desired translation distance~%float32 desired_distance~%~%# the min distance that must be considered feasible before the~%# grasp is even attempted~%float32 min_distance~%~%================================================================================~%MSG: geometry_msgs/Vector3Stamped~%# This represents a Vector3 with reference coordinate frame and timestamp~%Header header~%Vector3 vector~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GraspableObject)))
  "Returns full string definition for message of type 'GraspableObject"
  (cl:format cl:nil "###########################################################~%# This message describes an object + grasp data~%Object object~%moveit_msgs/Grasp[] grasps~%~%================================================================================~%MSG: grasping_msgs/Object~%###########################################################~%# This message describes an object.~%~%# Many of the geometric items below lack a stamp/frame_id,~%# header stamp/frame_id should be used there~%std_msgs/Header header~%~%# An object might have a name~%string name~%~%# An object might have a known (named) support surface~%string support_surface~%~%# Objects might have properties, such as type/class, or color, etc.~%ObjectProperty[] properties~%~%###########################################################~%# Objects have many possible descriptions~%#  The following are the possible description formats~%~%# Perception modules often represent an object as a cluster of points~%#  Is considered valid if number of points > 0~%sensor_msgs/PointCloud2 point_cluster~%~%# MoveIt prefers solid primitives or meshes as a description of objects~%shape_msgs/SolidPrimitive[] primitives~%geometry_msgs/Pose[] primitive_poses~%~%shape_msgs/Mesh[] meshes~%geometry_msgs/Pose[] mesh_poses~%~%# An object representing a support surface might be described by a plane~%# Is considered valid if coefficients are not all 0s.~%shape_msgs/Plane surface~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: grasping_msgs/ObjectProperty~%###########################################################~%# Other generic properties of an object~%string name~%string value~%~%================================================================================~%MSG: sensor_msgs/PointCloud2~%# This message holds a collection of N-dimensional points, which may~%# contain additional information such as normals, intensity, etc. The~%# point data is stored as a binary blob, its layout described by the~%# contents of the \"fields\" array.~%~%# The point cloud data may be organized 2d (image-like) or 1d~%# (unordered). Point clouds organized as 2d images may be produced by~%# camera depth sensors such as stereo or time-of-flight.~%~%# Time of sensor data acquisition, and the coordinate frame ID (for 3d~%# points).~%Header header~%~%# 2D structure of the point cloud. If the cloud is unordered, height is~%# 1 and width is the length of the point cloud.~%uint32 height~%uint32 width~%~%# Describes the channels and their layout in the binary data blob.~%PointField[] fields~%~%bool    is_bigendian # Is this data bigendian?~%uint32  point_step   # Length of a point in bytes~%uint32  row_step     # Length of a row in bytes~%uint8[] data         # Actual point data, size is (row_step*height)~%~%bool is_dense        # True if there are no invalid points~%~%================================================================================~%MSG: sensor_msgs/PointField~%# This message holds the description of one point entry in the~%# PointCloud2 message format.~%uint8 INT8    = 1~%uint8 UINT8   = 2~%uint8 INT16   = 3~%uint8 UINT16  = 4~%uint8 INT32   = 5~%uint8 UINT32  = 6~%uint8 FLOAT32 = 7~%uint8 FLOAT64 = 8~%~%string name      # Name of field~%uint32 offset    # Offset from start of point struct~%uint8  datatype  # Datatype enumeration, see above~%uint32 count     # How many elements in the field~%~%================================================================================~%MSG: shape_msgs/SolidPrimitive~%# Define box, sphere, cylinder, cone ~%# All shapes are defined to have their bounding boxes centered around 0,0,0.~%~%uint8 BOX=1~%uint8 SPHERE=2~%uint8 CYLINDER=3~%uint8 CONE=4~%~%# The type of the shape~%uint8 type~%~%~%# The dimensions of the shape~%float64[] dimensions~%~%# The meaning of the shape dimensions: each constant defines the index in the 'dimensions' array~%~%# For the BOX type, the X, Y, and Z dimensions are the length of the corresponding~%# sides of the box.~%uint8 BOX_X=0~%uint8 BOX_Y=1~%uint8 BOX_Z=2~%~%~%# For the SPHERE type, only one component is used, and it gives the radius of~%# the sphere.~%uint8 SPHERE_RADIUS=0~%~%~%# For the CYLINDER and CONE types, the center line is oriented along~%# the Z axis.  Therefore the CYLINDER_HEIGHT (CONE_HEIGHT) component~%# of dimensions gives the height of the cylinder (cone).  The~%# CYLINDER_RADIUS (CONE_RADIUS) component of dimensions gives the~%# radius of the base of the cylinder (cone).  Cone and cylinder~%# primitives are defined to be circular. The tip of the cone is~%# pointing up, along +Z axis.~%~%uint8 CYLINDER_HEIGHT=0~%uint8 CYLINDER_RADIUS=1~%~%uint8 CONE_HEIGHT=0~%uint8 CONE_RADIUS=1~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: shape_msgs/Mesh~%# Definition of a mesh~%~%# list of triangles; the index values refer to positions in vertices[]~%MeshTriangle[] triangles~%~%# the actual vertices that make up the mesh~%geometry_msgs/Point[] vertices~%~%================================================================================~%MSG: shape_msgs/MeshTriangle~%# Definition of a triangle's vertices~%uint32[3] vertex_indices~%~%================================================================================~%MSG: shape_msgs/Plane~%# Representation of a plane, using the plane equation ax + by + cz + d = 0~%~%# a := coef[0]~%# b := coef[1]~%# c := coef[2]~%# d := coef[3]~%~%float64[4] coef~%~%================================================================================~%MSG: moveit_msgs/Grasp~%# This message contains a description of a grasp that would be used~%# with a particular end-effector to grasp an object, including how to~%# approach it, grip it, etc.  This message does not contain any~%# information about a \"grasp point\" (a position ON the object).~%# Whatever generates this message should have already combined~%# information about grasp points with information about the geometry~%# of the end-effector to compute the grasp_pose in this message.~%~%# A name for this grasp~%string id~%~%# The internal posture of the hand for the pre-grasp~%# only positions are used~%trajectory_msgs/JointTrajectory pre_grasp_posture~%~%# The internal posture of the hand for the grasp~%# positions and efforts are used~%trajectory_msgs/JointTrajectory grasp_posture~%~%# The position of the end-effector for the grasp.  This is the pose of~%# the \"parent_link\" of the end-effector, not actually the pose of any~%# link *in* the end-effector.  Typically this would be the pose of the~%# most distal wrist link before the hand (end-effector) links began.~%geometry_msgs/PoseStamped grasp_pose~%~%# The estimated probability of success for this grasp, or some other~%# measure of how \"good\" it is.~%float64 grasp_quality~%~%# The approach direction to take before picking an object~%GripperTranslation pre_grasp_approach~%~%# The retreat direction to take after a grasp has been completed (object is attached)~%GripperTranslation post_grasp_retreat~%~%# The retreat motion to perform when releasing the object; this information~%# is not necessary for the grasp itself, but when releasing the object,~%# the information will be necessary. The grasp used to perform a pickup~%# is returned as part of the result, so this information is available for~%# later use.~%GripperTranslation post_place_retreat~%~%# the maximum contact force to use while grasping (<=0 to disable)~%float32 max_contact_force~%~%# an optional list of obstacles that we have semantic information about~%# and that can be touched/pushed/moved in the course of grasping~%string[] allowed_touch_objects~%~%================================================================================~%MSG: trajectory_msgs/JointTrajectory~%Header header~%string[] joint_names~%JointTrajectoryPoint[] points~%~%================================================================================~%MSG: trajectory_msgs/JointTrajectoryPoint~%# Each trajectory point specifies either positions[, velocities[, accelerations]]~%# or positions[, effort] for the trajectory to be executed.~%# All specified values are in the same order as the joint names in JointTrajectory.msg~%~%float64[] positions~%float64[] velocities~%float64[] accelerations~%float64[] effort~%duration time_from_start~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: moveit_msgs/GripperTranslation~%# defines a translation for the gripper, used in pickup or place tasks~%# for example for lifting an object off a table or approaching the table for placing~%~%# the direction of the translation~%geometry_msgs/Vector3Stamped direction~%~%# the desired translation distance~%float32 desired_distance~%~%# the min distance that must be considered feasible before the~%# grasp is even attempted~%float32 min_distance~%~%================================================================================~%MSG: geometry_msgs/Vector3Stamped~%# This represents a Vector3 with reference coordinate frame and timestamp~%Header header~%Vector3 vector~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GraspableObject>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'object))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'grasps) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GraspableObject>))
  "Converts a ROS message object to a list"
  (cl:list 'GraspableObject
    (cl:cons ':object (object msg))
    (cl:cons ':grasps (grasps msg))
))
