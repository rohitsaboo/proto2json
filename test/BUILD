proto_library(
    name = "test_proto",
    srcs = ["test.proto"],
)

cc_proto_library(
    name = "test_cc_proto",
    deps = [":test_proto"],
)

cc_binary(
    name = "write_test_data",
    srcs = ["write_test_data.cc"],
    deps = [
        ":test_cc_proto",
    ],
)
