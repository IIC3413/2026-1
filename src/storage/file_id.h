#pragma once

#include <cstdint>

class FileId {
public:
  static constexpr int UNASSIGNED = INT32_MAX;

  int fd;

  FileId(int fd)
      : fd(fd) {}

  bool operator<(const FileId other) const {
    return this->fd < other.fd;
  }

  bool operator==(const FileId other) const {
    return this->fd == other.fd;
  }
};
