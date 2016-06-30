#ifndef Sleep_H
#define Sleep_H

#include "Capabilities.h"
#ifndef CAPABILITY_THREAD
#error "This header requires <thread>"
#endif

#include <thread>
#include <chrono>

//=============================================================================
namespace DGC {

  void sleep(std::chrono::seconds::rep seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
  }

}

#endif
