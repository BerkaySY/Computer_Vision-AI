#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>

/*
    Example: The robot No.1 and the robot No.2 are located in the world coordinate
    system.We use the world coordinate system as W,robot coordinate system as R1
    and R2.The pose of the robot 1 is q1 = [0.35, 0.2, 0.3, 0.1]^T , t1 = [0.3, 0.1, 0.1]^T . The
    pose of the robot 2 is q2 = [−0.5, 0.4, −0.1, 0.2]^T , t2 = [−0.1, 0.5, 0.3]^T . Here q and
    t express TRk ,W , k = 1, 2, which is the world to the robot transform matrix. Now,
    assume that robot 1 sees a point in its own coordinate system with coordinates of
    pR1 = [0.5, 0, 0.2]^T . We want to find the coordinates of the vector in the robot 2’s
    coordinate system.
    */
int main()
{
    //Define the Quaternions for the poses of the robots
    Eigen::Quaterniond q1(0.35, 0.2, 0.3, 0.1),
                       q2(-0.5, 0.4, -0.1, 0.2);
    // Quaternion needs to be normalized before use
    q1.normalize();
    q2.normalize();
    //Define the translation vectors for each robot's pose
    Eigen::Vector3d t1(0.3, 0.1, 0.1),
                    t2(-0.1, 0.5, 0.3);
    
    Eigen::Vector3d p1(0.5, 0, 0.2);
    
    //Find the full pose of each robot in the world coordinate system
    Eigen::Isometry3d T1w(q1), 
                      T2w(q2);
    T1w.pretranslate(t1);
    T2w.pretranslate(t2);

    //Calculate the position of robot 1 in the coordinate system of robot 2.
    Eigen::Vector3d p2 = T2w * T1w.inverse() * p1;
    std::cout << p2.transpose() << '\n';
    
    return 0;
}