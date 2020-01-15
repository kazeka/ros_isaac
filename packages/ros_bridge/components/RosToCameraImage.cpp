#include "RosToCameraImage.hpp"

#include <utility>
#include <vector>

#include "messages/image.hpp"
#include "engine/core/image/image.hpp"
#include "engine/gems/image/utils.hpp"

namespace isaac {
namespace ros_bridge {

// Factor by which to scale images down when displayed in Sight
constexpr int kSightReduceSize = 4;

bool RosToCameraImage::rosToProto(const sensor_msgs::Image::ConstPtr& ros_message,
                                  ImageProto::Builder builder,
                                  std::vector<isaac::SharedBuffer>& buffers) {
//   ImageView3ub image = CreateImageView<uint8_t, 3>(ros_message->data.data(), ros_message->height, ros_message->width);
 
//   CpuBufferConstView color_buffer(reinterpret_cast<const byte*>(color_frame.get_data()),
//                                     color_frame.get_height() * color_frame.get_stride_in_bytes());

//   ImageConstView3ub color_image_view(ros_message->data.data(), ros_message->height, ros_message->width);

  ImageConstView3ub color_image_view = CreateImageView<uint8_t, 3>(ros_message->data.data(), ros_message->height, ros_message->width);

  Image3ub color_image(color_image_view.dimensions());
  
  Copy(color_image_view, color_image);

  show("ros_rgb_thumbnail",
        [&](sight::Sop& sop) { sop.add(Reduce<kSightReduceSize>(color_image)); });
  show("ros_rgb", [&](sight::Sop& sop) { sop.add(color_image); });
  
  ToProto(std::move(color_image), builder, buffers);

//   Image3ub buffer(ros_message->height, ros_message->width);
//   ConvertBgraToRgb(BgraZedImageView(left_image_rgb_), buffer_left_rgb);
//   show("left_rgb_thumbnail",
//         [&](sight::Sop& sop) { sop.add(Reduce<kSightReduceSize>(buffer_left_rgb)); });
//   show("left_rgb", [&](sight::Sop& sop) { sop.add(buffer_left_rgb); });
//   ToProto(std::move(buffer_left_rgb), l_camera.getImage(), tx_left_camera_rgb().buffers());


  return true;
}

}  // namespace ros_bridge
}  // namespace isaac
