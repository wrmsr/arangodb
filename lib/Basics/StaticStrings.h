////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2016 ArangoDB GmbH, Cologne, Germany
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

#ifndef ARANGODB_BASICS_STATIC_STRINGS_H
#define ARANGODB_BASICS_STATIC_STRINGS_H 1

#include "Basics/Common.h"

namespace arangodb {
class StaticStrings {
  StaticStrings() = delete;
 public:
  // system attribute names
  static std::string const IdString;
  static std::string const KeyString;
  static std::string const RevString;
  static std::string const FromString;
  static std::string const ToString;

  // HTTP headers
  static std::string const AcceptHeader;
  static std::string const ContentTypeHeader;

  // mime types
  static std::string const MimeTypeVPack;
  static std::string const MimeTypeJson;
};
}

#endif