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

#include "core/scene/camera/camera.h"

#include "core/scene/ground.h"
#include "core/scene/indirect_light/indirect_light.h"
#include "core/scene/light/light.h"
#include "core/scene/scene_controller.h"
#include "core/scene/skybox/skybox.h"

namespace plugin_filament_view {

class IndirectLight;
class Light;
class Camera;
class Ground;
class SceneController;
class SkyBox;

class Scene {
 public:
  Scene(void* parent,
        const std::string& flutter_assets_path,
        const flutter::EncodableValue& val);
  ~Scene();
  void Print(const char* tag) const;

  // Disallow copy and assign.
  Scene(const Scene&) = delete;
  Scene& operator=(const Scene&) = delete;

  friend class Scene;
  friend class SceneController;

 private:
  void* parent_;
  const std::string& flutterAssetsPath_;

  // TODO std::optional<std::unique_ptr<plugin_filament_view::SkyBox>> skybox_;
  std::optional<std::unique_ptr<plugin_filament_view::IndirectLight>>
      indirect_light_;
  std::optional<std::unique_ptr<plugin_filament_view::Light>> light_;
  std::optional<std::unique_ptr<plugin_filament_view::Camera>> camera_;
  std::optional<std::unique_ptr<plugin_filament_view::Ground>> ground_;
};
}  // namespace plugin_filament_view
