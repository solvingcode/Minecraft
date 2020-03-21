#include "time.h"

namespace Time{
    std::chrono::milliseconds GetMTime(){
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    }
}