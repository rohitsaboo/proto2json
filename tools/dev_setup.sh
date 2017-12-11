#! /bin/bash
#
# Install some common tools for development.

REPO="$(git rev-parse --show-toplevel)"
echo "$REPO"
TOOLSDIR="$(cd "$(dirname "$0")"; pwd -P)"
# exit on any error
set -e

pushd /tmp > /dev/null

# OS-specific settings
OS="$(uname)"
case "$OS" in
  "Linux")
    echo
    echo "Installing essential packages ..."
    sudo apt-get update || true
    sudo apt-get install -y \
        build-essential clang clang-format golang \
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
    brew install bazel clang-format
    ;;

  *)
    echo "You are out of luck on OS [$OS]"
    exit 1
    ;;
esac

if [ -d "$REPO" ]; then
  echo "Setting up git hooks..."
  cd $REPO
  git config core.hooksPath tools/git/hooks
  # For git versions prior to 2.10, the above core.hooksPath config variable 
  # does not exist.
  rm -rf "$REPO/.git/hooks"
  ln -s "../tools/git/hooks" "$REPO/.git/hooks"
fi

go get github.com/bazelbuild/buildifier/buildifier

popd > /dev/null
