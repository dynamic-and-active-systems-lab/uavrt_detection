# uavrt_detection

## Instructions for deploying uavrt_detection to Linux

### Pre-reqs
1. Matlab installed with Matlab Coder on machine that isn't the ROS2 target machine.
2. [ROS2 Galactic installed](https://docs.ros.org/en/galactic/Installation.html) on the Linux target machine.
3. [colcon installed](https://docs.ros.org/en/galactic/Tutorials/Beginner-Client-Libraries/Colcon-Tutorial.html)on the Linux target machine
4. [airspyhf_rx](https://github.com/airspy/airspyhf) installed on the Linux target machine.
5. [airspyhf_channelizer](https://github.com/dynamic-and-active-systems-lab/airspyhf_channelize) installed and compiled as an executable. Add the path to the airspyhf_channelizer local repo to your Matlab path so that it can find a dependent function needed for uavrt_detection.
6. OpenSSH installed on the ROS2 target machine. The commands for installing ssh on a Debian based system are:
```
sudo apt update
sudo apt install openssh-server
sudo ufw allow 22
```
This will allow port 22 to be used for [sshd](https://linux.die.net/man/8/sshd).



### Installation Instructions
1. On a Mac (non-ROS target machine) with Matlab installed, clone this repo. 
2. On the target Linux machine, open a terminal window and source ROS2 installation: `source /opt/ros/galactic/setup.bash`. 
3. On the target Linux machine create a ROS2 workspace directory called `~/uavrt_ws`. 
4. Create a `src` folder in the `uavrt_ws`: `cd ~/uavrt_ws` then `mkdir src`.
5. Move back out to `~/uavrt_ws` and build: `cd ..` then `colcon build`. This and the previous set are needed so that Matlab sees it as a valid ROS2 workspace during the remote deployment. 
6. Clone the [uavrt_interface](https://github.com/dynamic-and-active-systems-lab/uavrt_interfaces) repository into the `~/uavrt_ws/src` directory. 
7. Determine the target machine IP address by running `$ ip addr` in terminal.
8. The script `uavrt_detectin/detector/uavrt_detection_codegenerator.m` contains a section `%% Remote ROS2 BUILDING` in which there is set of lines that may need updating:
```
cfg.Hardware.RemoteDeviceAddress = 'XXX.XXX.XXX.XXX';
cfg.Hardware.RemoteDeviceUsername = 'XXXX';
cfg.Hardware.RemoteDevicePassword = 'XXXXXXXX';
cfg.Hardware.ROS2Folder = '/opt/ros/galactic';
cfg.Hardware.ROS2Workspace = '~/uavrt_ws';
```
On these lines, update the IP address, username, and password to that of the target machine. Check that the ros2folder is correct. If you created your `uavrt_ws` in a directory other than `~/` update the ROS2Worksapce line to match. 

NOTE: THERE IS CURRENTLY A BUG IN MATLAB THAT WILL CAUSE AN ERROR WITH THE MAKE FILES THAT IS DISCUSSED [HERE](https://www.mathworks.com/matlabcentral/answers/1831848-coder-ros2-build-error-colcon-with-custom-ros2-message#comment_2433218). As a temporary fix, do the following:
* Type  `>> edit ros.internal.codegen.ros2node` at the Matlab commandline
* Go to constructor of the ros2node class.
* Change `obj.NodeHandle = coder.opaque('rclcpp::Node::SharedPtr','getGlobalNodeHandle','HeaderFile','mlros2_node.h');` to `obj.NodeHandle = coder.opaque('rclcpp::Node::SharedPtr','HeaderFile','mlros2_node.h');`
* Save & close the file. 
* Generate the code

9. On the Mac within Matlab, run the lines of code in the `%% Remote ROS2 BUILDING` section. This will try to run compile, build, and run the code on the remote machine. You should see soemthing like:
```
Connecting to ROS 2 device at '134.114.16.153'.
Using ROS 2 workspace '~/uavrt_ws' to build ROS 2 node.
---
Transferring generated code for 'uavrt_detection' to ROS device.
Starting build for ROS node.
---
ROS 2 project directory: /home/dasl/uavrt_ws/src


Starting >>> uavrt_interfaces

Finished <<< uavrt_interfaces [1.31s]
Starting >>> uavrt_detection

--- stderr: uavrt_detection
:
:
A NUMBER OF WARNINGS
:
:
Code generation successful.
```
The reported [warnings can be igonored](https://www.mathworks.com/matlabcentral/answers/1723340-how-to-run-a-ros2-node-executable-generated-by-coder#comment_2183100). 

10. The code should be available now on the remote machine and ready to run. If you need to rebuild the code on the Linux machine directly, open a terminal window at `~/uavrt_ws` and run the following.
```
source /opt/ros/galactic/setup.bash
colcon build
```

## To run the detector
1. Create a directory for the detector. For example run `$ mkdir ~/exampledetector`.
2. Generate a config folder within the directory. Run `$ mkdir ~/exampledetector/config`.
3. Copy and then update (per your detection needs) the example configuration file in the repository (detectorConfig.txt) into your local config folder (`~/exampledetector/config`). DO NOT FORGET TO CHANGE THE DATA PORT FIELD IN THE CONFIG FILES TO UNIQUE VALUES IF RUNNING MORE THAN ONE DETECTOR. 
4. Open a terminal, navigate to your `exampledetector` directory, and source your ROS2 distribution and uavrt_ws install. Note that this package contains dependencies on libraries within [airspyhf_channelize](). You'll need to add the path the folder than contains the airspyhf_channelize executable to the LD_LIBRARY_PATH environment variable. 
```
$ cd ~/exampledetector
$ source /opt/ros/galactic/setup.bash
$ . ~/uavrt_ws/install/setup.bash
$ export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:<PATH TO DIRETORY CONTAINING AIRSPYHF_CHANNELIZE> (NOT THE EXECUTABLE ITSELF, BUT ITS DIRECTORY)
```
Note that the <PATH TO DIRETORY CONTAINING AIRSPYHF_CHANNELIZE> needs to be the full path. i.e. /home/user/Desktop/portairspyhf_channelize, not ~/Desktop/portairspyhf_channelize. A file error will occur if you use the abbreviated path. 
5. If needed, update the ROS2_DOMAIN_ID environment variable to change from the default of 0. `$ export ROS_DOMAIN_ID=0`
6. Run the detector: `$ ros2 run uavrt_detection uavrt_detection`

Note that before (or after) running the node, you'll need spin up `airspyhf_channelize` and then `airspyhf_rx` to begin the datastream to the detector. It is critical (ie. please double check) that the sample rate argument of the `airspyhf_rx`, the sample rate & decimation factor sent to `airspyhf_channelize`, and the sample rate of the detector config file are all aligned. For example, if you'd like 4000 samples per second into your detector, a sample rate of `airspyhf_rx` can be set to 192000 along with a decimation factor for `airspyhf_channelizer` of 48. 
In separate terminal windows:
1. Spin up the channelizer: `$ ./airspyhf_channelize 192000 48`
2. Spin up the radio/airspyhf_rx: `$ /usr/local/bin/airspyhf_rx -f 91.7 -m on -a 192000 -r stdout -g on -l high -t 0 | netcat -u localhost 10000`
3. Spin up the detector: `$ ros2 run uavrt_detection uavrt_detection`. Note that the directory switch, source, install, and path export commands of step 4 above need to first be run in this terminal. 
4. Command each of the processes with the following commands:
    1. Transition the channelize to 'Run' state: `$ echo -e -n '\x01'| netcat -u -c localhost 10001`
    2. Transition the detector to 'Run' state: `$ echo -e -n '\x01'| netcat -u -c localhost 30000`
    3. When ready, kill the channelize: `$ echo -e -n '\xFF'| netcat -u -c localhost 10001`
    4. When ready, kill the detector: `$ echo -e -n '\xFF'| netcat -u -c localhost 30000`
