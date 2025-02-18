/*
 * Copyright 2020-2023 Toyota Connected North America
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "shell/platform/common/client_wrapper/include/flutter/encodable_value.h"

#include "core/scene/geometry/direction.h"
#include "core/scene/geometry/position.h"
#include "core/scene/material/model/material.h"

namespace plugin_filament_view {
class Shape {
 public:
  Shape(int32_t id,
        ::filament::math::float3 centerPosition,
        ::filament::math::float3 normal,
        Material material);

  Shape(const std::string& flutter_assets_path,
        const flutter::EncodableMap& params);

  void Print(const char* tag) const;

  // Disallow copy and assign.
  Shape(const Shape&) = delete;

  Shape& operator=(const Shape&) = delete;

 private:
  int id{};
  int32_t type_{};
  /// center position of the shape in the world space.
  std::optional<std::unique_ptr<::filament::math::float3>> centerPosition_;
  /// direction of the shape rotation in the world space
  std::optional<std::unique_ptr<::filament::math::float3>> normal_;
  /// material to be used for the shape.
  std::optional<std::unique_ptr<Material>> material_;
};
}  // namespace plugin_filament_view