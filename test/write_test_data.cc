#include "test/test.pb.h"

#include <fstream>
#include <string>

using google::protobuf::Message;
using test::Recording;

void WriteProtoToFile(const std::string& file, const Message& proto) {
    std::ofstream out(file, std::ofstream::binary);
    proto.SerializeToOstream(&out);
    out.close();
}

int main() {
    Recording recording;
    auto* acc = recording.mutable_acc();
    for (int i = 0; i != 10; i++) {
        acc->add_sensor_ns(i * 1000);
        acc->add_x(i);
        acc->add_y(i);
        acc->add_z(i);
    }
    WriteProtoToFile("test.pb", recording);
    return 0;
}
