#!/usr/bin/env bash
set -euo pipefail

# Usage: ./build.sh [build-dir]
BUILD_DIR="${1:-build}"

# Configure
cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON

# Build everything
cmake --build "$BUILD_DIR" --parallel

# Run unit tests
ctest --test-dir "$BUILD_DIR" --output-on-failure

echo
echo "✅ Build and tests completed."
echo "Artifacts in: $BUILD_DIR"
