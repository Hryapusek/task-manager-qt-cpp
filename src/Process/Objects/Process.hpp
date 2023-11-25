#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>
#include <QMetaType>

namespace process
{
  class Field
  {
  public:
    enum Field_
    {
      PID = 0,
      WORK_TIME = 1,
      COMMAND = 2
    };
    static int toInt(Field_ col)
    {
      auto res = static_cast< int >(col);
      assert(("Bad column. Can not convert to int.", res >= 0 && res <= 2));
      return res;
    }
    static Field_ fromInt(int col)
    {
      assert(("Bad int. Can not convert to Field_ enum.", col >= 0 && col <= 2));
      return static_cast< Field_ >(col);
    }
    static std::string toString(Field_ col)
    {
      switch (col)
      {
        case Field_::PID:
          return "PID";

        case Field_::WORK_TIME:
          return "Time";

        case Field_::COMMAND:
          return "Command";

        default:
          std::unreachable();
      }
    }
  };

  class Process
  {
  public:
    Process();
    int pid() const;
    void pid(int pid);
    time_t time() const;
    void time(time_t time);
    const std::string &cmd() const;
    void cmd(std::string cmd);
  private:
    int pid_;
    time_t time_;
    std::string cmd_;
  };
}

Q_DECLARE_METATYPE(process::Process)

#endif
