#include <stdlib.h>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/util/json_util.h>
#include <fstream>
#include <functional>
#include <string>

using google::protobuf::Descriptor;
using google::protobuf::DescriptorPool;
using google::protobuf::DynamicMessageFactory;
using google::protobuf::FileDescriptor;
using google::protobuf::FileDescriptorSet;
using google::protobuf::Message;
using google::protobuf::util::MessageToJsonString;
using std::ifstream;
using std::ofstream;
using std::string;

DEFINE_string(protoc, "protoc", "The path for the protocol buffer compiler");
DEFINE_string(schema, "", "The protobuf schema");
DEFINE_string(in, "", "The serialized protobuf file");
DEFINE_string(root, "", "The root protobuf message");
DEFINE_string(out, "", "The json output file");

template <class T>
bool ReadProtoFromFile(const string& file_name, T* message) {
    std::ifstream ifs(file_name, std::ifstream::binary);
    if (!message->ParseFromIstream(&ifs)) {
        return false;
    }
    ifs.close();
    return true;
}

void WriteStringToFile(const string& file_name, const string& string_data) {
    std::ofstream out(file_name, std::ofstream::binary);
    out << string_data;
    out.close();
}

const Descriptor* GetDescriptor(const FileDescriptorSet& file_descriptor_set, const string& root, DescriptorPool* pool) {
    const FileDescriptor* file_descriptor = pool->BuildFile(file_descriptor_set.file(0));
    for (int i = 0; i != file_descriptor->message_type_count(); i++) {
        const Descriptor* descriptor = file_descriptor->message_type(i);
        if (descriptor->name() == root) {
            return descriptor;
        }
    }
    return nullptr;
}

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    // Generate the descriptor for the proto schema.
    const string descriptor_file = "/tmp/" + std::to_string(std::hash<string>()(FLAGS_schema)) + ".pb";

    if (system((FLAGS_protoc + " --descriptor_set_out=" + descriptor_file + " " + FLAGS_schema).c_str()) != 0) {
        LOG(ERROR) << "Unable to parse proto file [" << FLAGS_schema + "].";
        return 1;
    }

    FileDescriptorSet file_descriptor_set;
    if (!ReadProtoFromFile(descriptor_file, &file_descriptor_set)) {
        LOG(ERROR) << "Unable to read generated descriptor set.";
        return 1;
    }

    DescriptorPool descriptor_pool;
    const Descriptor* descriptor = GetDescriptor(file_descriptor_set, FLAGS_root, &descriptor_pool);
    if (descriptor == nullptr) {
        LOG(ERROR) << "Unable to find root message [" << FLAGS_root << "].";
        return 1;
    }

    // Create a dynamic message from the descriptor.
    DynamicMessageFactory factory;
    Message* message = factory.GetPrototype(descriptor)->New();

    // Parse and dump the serialized file.
    if (!ReadProtoFromFile(FLAGS_in, message)) {
        LOG(ERROR) << "Unable to read serialized proto file [" << FLAGS_in << "].";
        return 1;
    }

    string out;
    MessageToJsonString(*message, &out);
    WriteStringToFile(FLAGS_out, out);

    return 0;
}
