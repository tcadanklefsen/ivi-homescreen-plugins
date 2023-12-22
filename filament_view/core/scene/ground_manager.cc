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

#include "ground_manager.h"

#include <filament/Engine.h>
#include <filament/RenderableManager.h>
#include <filament/Scene.h>
#include <filament/TransformManager.h>
#include <filament/View.h>
#include <math/mat3.h>
#include <math/norm.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include "asio/post.hpp"

#include "logging/logging.h"

#include "generated/resources/gltf_demo.h"
#include "materials/uberarchive.h"

namespace plugin_filament_view {

using ::filament::Aabb;
using ::filament::IndexBuffer;
using ::filament::RenderableManager;
using ::filament::VertexAttribute;
using ::filament::VertexBuffer;
using ::filament::math::float3;
using ::filament::math::mat3f;
using ::filament::math::mat4f;
using ::filament::math::packSnorm16;
using ::filament::math::short4;
using ::utils::Entity;

GroundManager::GroundManager(CustomModelViewer* modelViewer,
                             MaterialManager* material_manager,
                             Ground* ground)
    : modelViewer_(modelViewer),
      materialManager_(material_manager),
      engine_(modelViewer->getFilamentEngine()),
      ground_(ground),
      plane_geometry_(nullptr) {
  SPDLOG_TRACE("++GroundManager::GroundManager");
  SPDLOG_TRACE("--GroundManager::GroundManager");
}

mat4f inline fitIntoUnitCube(const Aabb& bounds, float zoffset) {
  float3 minpt = bounds.min;
  float3 maxpt = bounds.max;
  float maxExtent;
  maxExtent = std::max(maxpt.x - minpt.x, maxpt.y - minpt.y);
  maxExtent = std::max(maxExtent, maxpt.z - minpt.z);
  float scaleFactor = 2.0f / maxExtent;
  float3 center = (minpt + maxpt) / 2.0f;
  center.z += zoffset / scaleFactor;
  return mat4f::scaling(float3(scaleFactor)) * mat4f::translation(-center);
}

std::future<Resource<std::string_view>> GroundManager::createGround() {
  SPDLOG_DEBUG("++GroundManager::createGround");
  const auto promise(
      std::make_shared<std::promise<Resource<std::string_view>>>());
  auto future(promise->get_future());

  modelViewer_->setGroundState(SceneState::LOADING);

  if (!ground_) {
    modelViewer_->setGroundState(SceneState::ERROR);
    promise->set_value(
        Resource<std::string_view>::Error("Ground must be provided"));
    SPDLOG_DEBUG("--GroundManager::createGround");
    return future;
  }

  if (!ground_->size_) {
    modelViewer_->setGroundState(SceneState::ERROR);
    promise->set_value(
        Resource<std::string_view>::Error("Size must be provided"));
    SPDLOG_DEBUG("--GroundManager::createGround");
    return future;
  }

  asio::post(modelViewer_->getStrandContext(), [&, promise] {
    auto materialInstanceResult =
        materialManager_->getMaterialInstance(ground_->material_.get());

    // auto modelTransform = modelViewer_->getModelTransform();
#if 0
    auto center = (ground_->isBelowModel_ && modelTransform != nullptr)
                      ? Position(modelTransform[0][3], modelTransform[1][3], modelTransform[2][3])
                      : ground_->center_position_ != nullptr
                            ? ground_->center_position_
                            : promise->set_value("Position must be provided"); return
#endif

#if 0  // TODO

            Position* center;
            if (ground_->getIsBelowModel()) {
              center = new Position(modelTransform[0, 3], modelTransform[1, 3], modelTransform[2, 3]);
            }
            else {
              if (!ground_->getCenterPosition().has_value()) {
                promise->set_value("Position must be provided");
                return;
              }
              center = ground_->getCenterPosition().value();
            }

            plane_geometry_ = PlaneGeometry.Builder(
                                         center = center,
                                         ground_->getSize(),
                                         ground_->getNormal().has_value() ? ground_->getNormal().value() : Direction(y = 1f)).build(engine_);
            delete center;
            plane_geometry_->setupScene(modelViewer_, materialInstanceResult.data);
#endif
    modelViewer_->setGroundState(SceneState::LOADED);
    promise->set_value(
        Resource<std::string_view>::Success("Ground created successfully"));
  });
  SPDLOG_DEBUG("--GroundManager::createGround");
  return future;
}

std::future<Resource<std::string_view>> GroundManager::updateGround(
    Ground* newGround) {
  return std::future<Resource<std::string_view>>();
}

std::future<Resource<std::string_view>> GroundManager::updateGroundMaterial(
    Material* newMaterial) {
  return std::future<Resource<std::string_view>>();
}

void GroundManager::Print(const char* tag) {}

}  // namespace plugin_filament_view