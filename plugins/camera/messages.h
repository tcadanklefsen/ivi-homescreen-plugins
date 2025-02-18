/*
 * Copyright 2023 Toyota Connected North America
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

#ifndef PIGEON_MESSAGES_G_H_
#define PIGEON_MESSAGES_G_H_
#include <flutter/basic_message_channel.h>
#include <flutter/binary_messenger.h>
#include <flutter/encodable_value.h>
#include <flutter/standard_method_codec.h>

#include <map>
#include <optional>
#include <string>

namespace camera_plugin {

// Generated class from Pigeon.

class FlutterError {
 public:
  explicit FlutterError(const std::string& code) : code_(code) {}
  explicit FlutterError(const std::string& code, const std::string& message)
      : code_(code), message_(message) {}
  explicit FlutterError(const std::string& code,
                        const std::string& message,
                        const flutter::EncodableValue& details)
      : code_(code), message_(message), details_(details) {}

  const std::string& code() const { return code_; }
  const std::string& message() const { return message_; }
  const flutter::EncodableValue& details() const { return details_; }

 private:
  std::string code_;
  std::string message_;
  flutter::EncodableValue details_;
};

template <class T>
class ErrorOr {
 public:
  ErrorOr(const T& rhs) : v_(rhs) {}
  ErrorOr(const T&& rhs) : v_(std::move(rhs)) {}
  ErrorOr(const FlutterError& rhs) : v_(rhs) {}
  ErrorOr(const FlutterError&& rhs) : v_(std::move(rhs)) {}

  bool has_error() const { return std::holds_alternative<FlutterError>(v_); }
  const T& value() const { return std::get<T>(v_); };
  const FlutterError& error() const { return std::get<FlutterError>(v_); };

 private:
  friend class CameraApi;
  ErrorOr() = default;
  T TakeValue() && { return std::get<T>(std::move(v_)); }

  std::variant<T, FlutterError> v_;
};

// Generated interface from Pigeon that represents a handler of messages from
// Flutter.
class CameraApi {
 public:
  CameraApi(const CameraApi&) = delete;
  CameraApi& operator=(const CameraApi&) = delete;
  virtual ~CameraApi(){};
  virtual void availableCameras(
      std::function<void(ErrorOr<flutter::EncodableList> result)> result) = 0;
  virtual void create(
      const flutter::EncodableMap& args,
      std::function<void(ErrorOr<flutter::EncodableMap> reply)> result) = 0;
  virtual void initialize(
      const flutter::EncodableMap& args,
      std::function<void(ErrorOr<std::string> reply)> result) = 0;
  virtual void takePicture(
      const flutter::EncodableMap& args,
      std::function<void(ErrorOr<std::string> reply)> result) = 0;
  virtual void startVideoRecording(
      const flutter::EncodableMap& args,
      std::function<void(std::optional<FlutterError> reply)> result) = 0;
  virtual void pauseVideoRecording(
      const flutter::EncodableMap& args,
      std::function<void(std::optional<FlutterError> reply)> result) = 0;
  virtual void resumeVideoRecording(
      const flutter::EncodableMap& args,
      std::function<void(std::optional<FlutterError> reply)> result) = 0;
  virtual void stopVideoRecording(
      const flutter::EncodableMap& args,
      std::function<void(ErrorOr<std::string> reply)> result) = 0;
  virtual void pausePreview(
      const flutter::EncodableMap& args,
      std::function<void(ErrorOr<double> reply)> result) = 0;
  virtual void resumePreview(
      const flutter::EncodableMap& args,
      std::function<void(ErrorOr<double> reply)> result) = 0;
  virtual void lockCaptureOrientation(
      const flutter::EncodableMap& args,
      std::function<void(ErrorOr<std::string>)> result) = 0;
  virtual void unlockCaptureOrientation(
      const flutter::EncodableMap& args,
      std::function<void(ErrorOr<std::string>)> result) = 0;
  virtual void setFocusMode(
      const flutter::EncodableMap& args,
      std::function<void(std::optional<FlutterError> reply)> result) = 0;
  virtual void setFlashMode(
      const flutter::EncodableMap& args,
      std::function<void(std::optional<FlutterError> reply)> result) = 0;
  virtual void setExposureMode(
      const flutter::EncodableMap& args,
      std::function<void(std::optional<FlutterError> reply)> result) = 0;
  virtual void setExposurePoint(
      const flutter::EncodableMap& args,
      std::function<void(std::optional<FlutterError> reply)> result) = 0;
  virtual void setFocusPoint(
      const flutter::EncodableMap& args,
      std::function<void(std::optional<FlutterError> reply)> result) = 0;
  virtual void setExposureOffset(
      const flutter::EncodableMap& args,
      std::function<void(ErrorOr<double> reply)> result) = 0;
  virtual void getExposureOffsetStepSize(
      const flutter::EncodableMap& args,
      std::function<void(ErrorOr<double> reply)> result) = 0;
  virtual void getMinExposureOffset(
      const flutter::EncodableMap& args,
      std::function<void(ErrorOr<double> reply)> result) = 0;
  virtual void getMaxExposureOffset(
      const flutter::EncodableMap& args,
      std::function<void(ErrorOr<double> reply)> result) = 0;
  virtual void getMaxZoomLevel(
      const flutter::EncodableMap& args,
      std::function<void(ErrorOr<double> reply)> result) = 0;
  virtual void getMinZoomLevel(
      const flutter::EncodableMap& args,
      std::function<void(ErrorOr<double> reply)> result) = 0;
  virtual void dispose(
      const flutter::EncodableMap& args,
      std::function<void(std::optional<FlutterError> reply)> result) = 0;

  // The codec used by CameraApi.
  static const flutter::StandardMethodCodec& GetCodec();
  // Sets up an instance of `CameraApi` to handle messages through the
  // `binary_messenger`.
  static void SetUp(flutter::BinaryMessenger* binary_messenger, CameraApi* api);
  static flutter::EncodableValue WrapError(std::string_view error_message);
  static flutter::EncodableValue WrapError(const FlutterError& error);

 protected:
  CameraApi() = default;
};

}  // namespace camera_plugin
#endif  // PIGEON_MESSAGES_G_H_
