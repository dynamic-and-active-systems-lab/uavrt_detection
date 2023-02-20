function [pulsePub, pulseMsg] = ros2Setup()

fprintf("Preparing ROS2 Node and Messages...")
node = ros2node("detector",0);
pulsePub = ros2publisher(node,"/pulse","uavrt_interfaces/Pulse");
pulseMsg = ros2message(pulsePub);
%pulseMsg = ros2message("uavrt_interfaces/Pulse");
fprintf("complete.\n")

end