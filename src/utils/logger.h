#ifndef FINDD_LOGGER_H
#define FINDD_LOGGER_H

#include <iostream>
#include <vector>
#include <string>

namespace findd { namespace utils {
  
  /**
  * Flags of generic message types the logger can handles.
  * @see set_messages_verbosity() to define what types of message you want to output.
  */
  enum LoggerMessageType {
    INFO    = 0x1,
    WARNING = 0x2,
    ERROR   = 0x4,
    FATAL   = 0x8,
    DEBUG   = 0x10
  };
    
  /**
   * Logger class that provides simple and intuitive logging interface
   */
  class Logger {
  public:
	
  /**
   * Singleton invoking
   */
  static Logger *instance();
		
  ~Logger();
	
  /**
   * Log a information message.
   * 
   * @param [std::string&] The message to log
   * @param [unsigned int] Log level, default to 0.
   */
  void info(const std::string&, const unsigned int = 0);

  /**
   * Log a warning message.
   * 
   * @param [std::string&] The message to log
   * @param [unsigned int] Log level, default to 0.
   */
  void warning(const std::string&, const unsigned int = 0);
	
  /**
   * Log a error message.
   * 
   * @param [std::string&] The message to log
   * @param [unsigned int] Log level, default to 0.
   */
  void error(const std::string&, const unsigned int = 0);
	
  /**
   * Log a fatal message.
   * 
   * @param [std::string&] The message to log
   * @param [unsigned int] Log level, default to 0.
   */
  void fatal(const std::string&, const unsigned int = 0);

  /**
   * Log a debug message.
   * 
   * @param [std::string&] The message to log
   * @param [unsigned int] Log level, default to 0.
   */
  void debug(const std::string&, const unsigned int = 0);

  /**
   * Write log message into each registered streams.
   * 
   * @param [LoggerMessageType] message type. 
   * @param [std::string&] message to write.
   * @param [unsigned int] log level, default to 0.
   */
  void log(const LoggerMessageType, const std::string&, const unsigned int = 0);
	
  /**
   * Add a stream to write logs into
   * 
   * @param [std::ostream*] ostream pointer
   */
  void register_stream(std::ostream *);
	
  // --------------------------------- Getters and Setters ---------------------------------
	
  unsigned int verbosity_level() const;
  void set_verbosity_level(unsigned int);
  unsigned int messages_verbosity() const;
  void set_messages_verbosity(unsigned int);
  unsigned int count_messages() const;
  
  private:
  
  Logger();
	
  /**
   * Return current time as string.
   * 
   * @return [std::string]
   */
  std::string currentTime() const;
  
  std::string stringify_message_type (const LoggerMessageType);

  // ----------------------------------- Member variables ----------------------------------
	
  /**
   * Singleton Logger instance
   */
  static Logger *s_instance_;
	
  /**
   * The verbosity level of messages. 
   * If the level of a log message is greater than the verbosity level, the message is not displayed. 
   */
  unsigned int verbosity_level_;
	 
  /**
   * This variable define what types of message are displayed or not. By default all type of messages are enabled.
   * You can create a custom verbosity by using message type flags. For example, if you want only to display Info and Error message,
   * then you must do something like : Logger::instance()->set_messages_verbosity(Logger::INFO | Logger::ERROR).
   * Then, all other messages will be ignored.
   */
  unsigned int messages_verbosity_;
	
  /**
   * A vector of ostream where logs will be written.
   */
  std::vector<std::ostream*> ostreams_;
 
}; // class Logger
  
} // namespace utils
} // namespace findd

#endif