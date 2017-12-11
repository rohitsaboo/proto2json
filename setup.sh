#! /bin/bash

REPO="$(cd "$(dirname "$0")"; pwd -P)"
echo $REPO

# exit on any error
set -e

# OS-specific settings
OS="$(uname)"
case "$OS" in
  "Linux")
    echo
    echo "Installing essential packages ..."
    sudo apt-get update || true
    sudo apt-get install -y \
        build-essential \
        software-properties-common

    echo "Installing bazel ..."
    sudo add-apt-repository ppa:webupd8team/java
    sudo apt-get update || true
    # accept oracle user agreement in without user interaction
    echo debconf shared/accepted-oracle-license-v1-1 select true | sudo debconf-set-selections
    echo debconf shared/accepted-oracle-license-v1-1 seen true | sudo debconf-set-selections
    sudo apt-get install -y oracle-java8-installer
    echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
    curl https://bazel.build/bazel-release.pub.gpg | sudo apt-key add -
    sudo apt-get update || true
    sudo apt-get install -y bazel

    ;;

  "Darwin")
    brew install bazel
    ;;

  *)
    echo "You are out of luck on OS [$OS]"
    exit 1
    ;;
esac

bazel build ...
