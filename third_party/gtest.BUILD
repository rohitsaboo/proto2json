cc_library(
    name = "gtest",
    testonly = True,
    srcs = glob(
        ["googletest/src/*.cc"],
        exclude = [
            "googletest/src/gtest-all.cc",
            "googletest/src/gtest-main.cc",
        ],
    ),
    hdrs = glob([
        "googletest/include/**/*.h",
        "googletest/src/*.h",
    ]),
    copts = [
        "-Iexternal/gtest/googletest/include",
        "-Iexternal/gtest/googletest",
    ],
    includes = ["googletest/include"],
    linkopts = ["-pthread"],
)

cc_library(
    name = "gmock",
    testonly = True,
    srcs = glob(
        ["googlemock/src/*.cc"],
        exclude = ["googlemock/src/gmock-all.cc"],
    ),
    hdrs = glob([
        "googlemock/include/**/*.h",
    ]),
    copts = ["-Iexternal/gtest/googlemock"],
    includes = ["googlemock/include"],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
    deps = [":gtest"],
)

cc_library(
    name = "gmock_main",
    testonly = True,
    srcs = ["googlemock/src/gmock_main.cc"],
    visibility = ["//visibility:public"],
    deps = [":gmock"],
)
