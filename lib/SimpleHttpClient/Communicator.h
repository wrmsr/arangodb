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
/// @author Andreas Streichardt
/// @author Frank Celler
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGODB_SIMPLE_HTTP_CLIENT_COMMUNICATOR_H
#define ARANGODB_SIMPLE_HTTP_CLIENT_COMMUNICATOR_H 1

#include "curl/multi.h"

#include "Basics/Common.h"
#include "Basics/Mutex.h"
#include "Basics/StringBuffer.h"
#include "Rest/GeneralRequest.h"
#include "Rest/HttpResponse.h"
#include "SimpleHttpClient/Callbacks.h"
#include "SimpleHttpClient/Destination.h"
#include "SimpleHttpClient/Options.h"
#include "SimpleHttpClient/Ticket.h"

namespace arangodb {
using namespace basics;

namespace communicator {
class Communicator {
 public:
  Communicator();

 public:
  Ticket addRequest(Destination, std::unique_ptr<GeneralRequest>, Callbacks,
                    Options);

  int work_once();
  void wait();
 
 public:
  struct RequestInProgress {
    CURL* _eh;
    Destination _destination;
    Callbacks _callbacks;
    Options _options;
    uint64_t _ticketId;
    std::unique_ptr<StringBuffer> buffer;
  };

 private:
  struct NewRequest {
    Destination _destination;
    std::unique_ptr<GeneralRequest> _request;
    Callbacks _callbacks;
    Options _options;
    uint64_t _ticketId;
  };

  struct CurlData {
  };

 private:
  Mutex _newRequestsLock;
  std::vector<NewRequest> _newRequests;
  std::unordered_map<uint64_t, std::unique_ptr<RequestInProgress>>
      _requestsInProgress;
  CURLM* _curl;
  CURLMcode _mc;
  curl_waitfd _wakeup;

  int _fds[2];
  int _numFds;

 private:
  void createRequestInProgress(NewRequest const& newRequest);
  void handleResult(CURL* eh, CURLcode rc);
  void transformResult(CURL*, std::unique_ptr<StringBuffer>, HttpResponse*);
};
}
}

#endif
