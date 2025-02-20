/*
 * Copyright 2019 Google Inc.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "util/statusor.h"

#include "glog/logging.h"
#include "util/status.h"

namespace util {
namespace internal {

static const char* kInvalidStatusCtorArgMessage =
    "Status::OK is not a valid constructor argument to StatusOr<T>";
static const char* kNullObjectCtorArgMessage =
    "NULL is not a valid constructor argument to StatusOr<T*>";

::util::Status StatusOrHelper::HandleInvalidStatusCtorArg() {
  LOG(DFATAL) << kInvalidStatusCtorArgMessage;
  // In optimized builds, we will fall back to ::util::error::INTERNAL.
  return Status(::private_join_and_compute::StatusCode::kInternal,
                kInvalidStatusCtorArgMessage);
}

::util::Status StatusOrHelper::HandleNullObjectCtorArg() {
  LOG(DFATAL) << kNullObjectCtorArgMessage;
  // In optimized builds, we will fall back to ::util::error::INTERNAL.
  return Status(::private_join_and_compute::StatusCode::kInternal, kNullObjectCtorArgMessage);
}

void StatusOrHelper::Crash(const ::util::Status& status) {
  LOG(FATAL) << "Attempting to fetch value instead of handling error "
             << status;
}

}  // namespace internal
}  // namespace util
