#pragma once

#include <string>

#include "packages/ros_bridge/components/RosToProtoConverter.hpp"
#include "sensor_msgs/Image.h"

namespace isaac {
namespace ros_bridge {

// This codelet receives ROS Image and publishes it to ImageProto data within Isaac application.
class RosToCameraImage : public RosToProtoConverter<ImageProto, sensor_msgs::Image> {
 public:
  bool rosToProto(const sensor_msgs::Image::ConstPtr& ros_message, ImageProto::Builder builder,
                  std::vector<isaac::SharedBuffer>& buffers) override;
};

}  // namespace ros_bridge
}  // namespace isaac

ISAAC_ALICE_REGISTER_CODELET(isaac::ros_bridge::RosToCameraImage);
