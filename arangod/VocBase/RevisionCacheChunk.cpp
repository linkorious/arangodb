////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2014-2016 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Jan Steemann
////////////////////////////////////////////////////////////////////////////////

#include "RevisionCacheChunk.h"
#include "Basics/MutexLocker.h"

using namespace arangodb;

RevisionCacheChunk::RevisionCacheChunk(uint32_t size)
    : _data(nullptr), _writeOffset(0), _size(size), _refCount(0), _version(0) {
  _data = new uint8_t[size];
}

RevisionCacheChunk::~RevisionCacheChunk() {
  delete[] _data;
}

uint32_t RevisionCacheChunk::advanceWritePosition(uint32_t size) {
  uint32_t offset;
  {
    MUTEX_LOCKER(locker, _writeMutex);

    if (_writeOffset + size > _size) {
      // chunk would be full
      return UINT32_MAX; // means: chunk is full
    }
    offset = _writeOffset;
    _writeOffset += size;
  }

  return offset;
}

bool RevisionCacheChunk::garbageCollect() {
  // TODO
  return false;
}

