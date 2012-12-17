/*
This file is part of the Findd project from University of Poitiers (FR).
	
Copyright (C) 2012
	
Florian Mhun <florian.mhun@gmail.com>
Sara Ressam  <sara.ressam@gmail.com>
Bastien Nouhant <bastien.nouhant@gmail.com>
Jérôme Cornet <jerome.cornet@etu.univ-poitiers.fr>
	
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of the <organization> nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "utils.h"

#include <cstddef>
#include <cstring>
#include <ctime>

namespace findd {
  
  namespace utils {
  
    ////////////////////////////////////////////////////////////////////////////
    //  LOGGER                                                                //
    ////////////////////////////////////////////////////////////////////////////
    
    Logger *Logger::s_instance_ = NULL;

    Logger::Logger() {
    	verbosity_level_ = 0;
    	messages_verbosity_ = 0xFF; // Handle all log message types by default.	
    }

    Logger::~Logger() {
    	s_instance_ = NULL;
    }

    Logger *Logger::instance() {
    	if (!s_instance_) {
    		s_instance_ = new Logger();
    	}
    	return s_instance_;
    }

    void Logger::info(const std::string& message, const unsigned int level) {
      log(INFO, message, level);
    }
  
    void Logger::warning(const std::string& message, const unsigned int level) {
      log(WARNING, message, level);
    }
  
    void Logger::error(const std::string& message, const unsigned int level) {
      log(ERROR, message, level);
    }
  
    void Logger::fatal(const std::string& message, const unsigned int level) {
      log(FATAL, message, level);
    }
  
    void Logger::debug(const std::string& message, const unsigned int level) {
      log(DEBUG, message, level);
    }

    void Logger::log(const LoggerMessageType type, const std::string& message, const unsigned int level) {
    	if ((type & (int)messages_verbosity_) == type) {
        const std::string msg = "[" + currentTime() + "] - [" + stringify_message_type(type) + "] " + message;
    
      	if (level <= verbosity_level_) {
      		for (unsigned int i = 0; i < ostreams_.size(); i++) {
      			*ostreams_[i] << msg << std::endl;
      		}
      	}
      }
    }

    unsigned int Logger::verbosity_level() const {
    	return verbosity_level_;
    }

    void Logger::set_verbosity_level(unsigned int level) {
    	verbosity_level_ = level;
    }

    unsigned int Logger::messages_verbosity() const {
    	return messages_verbosity_;
    }

    void Logger::set_messages_verbosity(unsigned int messages_verbosity) {
    	messages_verbosity_ = messages_verbosity;
    }

    void Logger::register_stream(std::ostream *os) {
    	ostreams_.push_back(os);
    }

    std::string Logger::currentTime() const {
    	char s[1000];
	
    	time_t t = time(NULL);
    	struct tm * p = localtime(&t);
    	strftime(s, 1000, "%c", p);
	
    	return std::string(s);
    }
  
    std::string Logger::stringify_message_type (const LoggerMessageType type) {
      switch (type) {
        case INFO:    return "INFO";    break;
        case WARNING: return "WARNING"; break;
        case ERROR:   return "ERROR";   break;
        case FATAL:   return "FATAL";   break;
        case DEBUG:   return "DEBUG";   break;
        default:      return "";        break;
      }
    }
    
    
    ////////////////////////////////////////////////////////////////////////////
    //  TIMER                                                                 //
    ////////////////////////////////////////////////////////////////////////////
  
    Timer::Timer () : _started(false), _elapsed(0.0) {}
    Timer::~Timer () {}
  
    void Timer::start () {
      if( !_started ) {
        _started = true;
        gettimeofday( &_start, NULL );
      }
    }
  
    double Timer::stop () {
      if ( _started ) {
        _started = false;
        timeval stop;
        gettimeofday( &stop, NULL );
        _elapsed = (stop.tv_sec - _start.tv_sec) + 1e-6f*(stop.tv_usec - _start.tv_usec);
      }
      return _elapsed;
    }
    
    double Timer::elapsed () const {
      return _elapsed;
    }
    
  } // namespace utils

} // namespace findd