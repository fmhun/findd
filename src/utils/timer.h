#ifndef FINDD_UTILS_TIMER_
#define FINDD_UTILS_TIMER_

#include <iostream>
#include <sys/time.h>

namespace findd { namespace utils {

  class Timer {
  private:
    timeval _start;
    bool _started;
    double _elapsed;
    
  public:
    Timer () : _started(false), _elapsed(0.0) {};
    ~Timer () {}
  
    void start () {
      if( !_started ) {
        _started = true;
        gettimeofday( &_start, NULL );
      }
    }
  
    double stop () {
      if ( _started ) {
        _started = false;
        timeval stop;
        gettimeofday( &stop, NULL );
        _elapsed = (stop.tv_sec - _start.tv_sec) + 1e-6f*(stop.tv_usec - _start.tv_usec);
      }
      return _elapsed;
    }
    
    double elapsed () const {
      return _elapsed;
    }
  
  };

}
}

#endif