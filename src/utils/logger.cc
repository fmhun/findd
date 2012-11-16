#include "logger.h"

#include <cstddef>
#include <cstring>
#include <ctime>

namespace findd { namespace utils {
  
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
  
} // namespace utils

} // namespace findd