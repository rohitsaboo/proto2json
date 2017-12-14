#! /bin/bash

REPO="$(cd "$(dirname "$0")"; pwd -P)"

"$REPO/bazel/bin/parser/proto2json" \
    --protoc="$REPO/bazel/bin/external/com_google_protobuf/protoc" \
    --logtostderr --colorlogtostderr --log_prefix=false \
    "$@"
