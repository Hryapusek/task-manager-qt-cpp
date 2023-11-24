#ifndef PROCESS_TABLE_MODEL_HPP
#define PROCESS_TABLE_MODEL_HPP

#include "Process/ProcessFetchers/Interface/ProcessFetcherI.hpp"
#include <memory>
#include <QAbstractTableModel>

class ProcessTableModel: public QAbstractTableModel
{
public:
  class Column
  {
  public:
    static const int nColumns = 3;
    enum Column_
    {
      PID = 0,
      TIME = 1,
      CMD = 2
    };
    static int toInt(Column_ col)
    {
      return static_cast<int>(col);
    }
    static Column_ fromInt(int col)
    {
      assert(("Bad int. Can not convert to Column_ enum.", col >= 0 && col <= 2));
      return static_cast<Column_>(col);
    }
    static std::string toString(Column_ col)
    {
      switch (col)
      {
      case Column_::PID:
        return "PID";

      case Column_::TIME:
        return "Time";

      case Column_::CMD:
        return "Command";

      default:
        std::unreachable();
      }
    }
    static Column_ lastColumn()
    {
      return Column_::CMD;
    }
  };
  /**
   * @throw std::logic_error if can not fetch the processes
   */
  ProcessTableModel(std::unique_ptr< ProcessFetcherI > processFetcher);
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  std::expected< void, std::string > kill(int pid);
  std::expected< void, std::string > refresh();
private:
  std::unique_ptr< ProcessFetcherI > processFetcher_;
  std::vector< Process > processes_;
  void mergeProcesses(std::vector< Process > oldProcesses);
};

#endif
