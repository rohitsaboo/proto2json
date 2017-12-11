#! /bin/bash

REPO="$(cd "$(dirname "$0")"; pwd -P)"
echo $REPO

# exit on any error
set -e

pushd "$REPO" > /dev/null

echo "Building protocol buffer compiler..."
bazel build -c opt @com_google_protobuf//:protoc
echo
bazel build -c opt //parser:proto2json 
echo "Building proto2json convertor..."

popd > /dev/null

"$REPO/bazel/bin/parser/proto2json" \
    --protoc="$REPO/bazel/bin/external/com_google_protobuf/protoc" \
    "$@"
