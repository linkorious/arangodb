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
/// @author Dr. Frank Celler
/// @author Achim Brandt
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGOD_SCHEDULER_TASK_H
#define ARANGOD_SCHEDULER_TASK_H 1

#include "Basics/Common.h"

#include "Scheduler/EventLoop.h"

namespace arangodb {
class TaskData;

namespace velocypack {
class Builder;
}

namespace rest {
class Task {
  Task(Task const&) = delete;
  Task& operator=(Task const&) = delete;

 public:
  Task(EventLoop, std::string const& name);
  virtual ~Task() {}

 public:
  uint64_t taskId() const { return _taskId; }
  EventLoop eventLoop() const { return _loop; }
  std::string const& name() const { return _name; }

  // get a VelocyPack representation of the task for reporting
  std::shared_ptr<arangodb::velocypack::Builder> toVelocyPack() const;
  void toVelocyPack(arangodb::velocypack::Builder&) const;

 public:
  virtual void signalTask(std::unique_ptr<TaskData>) = 0;

 protected:
  EventLoop _loop;
  uint64_t const _taskId;

 private:
  std::string const _name;
};
}
}

#endif
