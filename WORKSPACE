# gflags for C++
git_repository(
    name = "com_github_gflags_gflags",
    tag = "v2.2.1",  # 2017 Jul 11
    remote = "https://github.com/gflags/gflags.git",
)

bind(
    name = "gflags",
    actual = "@com_github_gflags_gflags//:gflags",
)

# glog for C++
new_git_repository(
    name = "com_github_google_glog",
    tag = "v0.3.5",  # 2017 May 10
    remote = "https://github.com/google/glog.git",
    build_file = "//third_party:glog.BUILD",
)

bind(
    name = "glog",
    actual = "@com_github_google_glog//:glog",
)

# Google test and mock
new_git_repository(
    name = "gtest",
    tag = "release-1.8.0",  # 2016 Aug 22
    remote = "https://github.com/google/googletest.git",
    build_file = "//third_party:gtest.BUILD",
)

# proto_library rules implicitly depend on @com_google_protobuf//:protoc,
# which is the proto-compiler.
git_repository(
    name = "com_google_protobuf",
    remote = "https://github.com/google/protobuf.git",
    tag = "v3.5.0.1",  # 2017 Dec 6
)

# cc_proto_library rules implicitly depend on 
# @com_google_protobuf_cc//:cc_toolchain,
# which is the C++ proto runtime (base classes and common utilities).
git_repository(
    name = "com_google_protobuf_cc",
    remote = "https://github.com/google/protobuf.git",
    tag = "v3.5.0.1",  # 2017 Dec 6
)


