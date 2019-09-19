#pragma once
#include"blob.hpp"
#include"priority_queue.hpp"
#include"uid.hpp"
#include"math.hpp"

namespace  util = utility;

namespace utility {
  typedef std::shared_ptr<Blob> SptrBlob;

  template<class Ty> SptrBlob CreateSptrBlob(const Ty &_ojb) {
    return std::make_shared<Blob>(_ojb);
  }
}