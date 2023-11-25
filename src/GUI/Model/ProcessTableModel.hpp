#ifndef PROCESS_TABLE_MODEL_HPP
#define PROCESS_TABLE_MODEL_HPP

#include "Process/ProcessFetchers/Interface/ProcessFetcherI.hpp"
#include <memory>
#include <QAbstractTableModel>
#include <future>

class ProcessTableModel: public QAbstractTableModel
{
public:
  /**
   * @throw std::logic_error if can not fetch the processes
   */
  ProcessTableModel(std::unique_ptr< process::ProcessFetcherI > processFetcher);
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  std::expected< void, std::string > kill(int pid);
  std::expected< void, std::string > refresh();
  std::vector< process::Field::Field_ > supportedFields() const;
  int pidColumn() const;
  int toColumn(process::Field::Field_ field) const;
  process::Field::Field_ toField(int column) const;
private:
  std::unique_ptr< process::ProcessFetcherI > processFetcher_;
  std::vector< process::Process > processes_;
  using FutureProcesses_t = std::future< std::expected< std::vector< process::Process >, std::string > >;
  FutureProcesses_t futureProcesses_;
  /**
   * @brief Tells which columns will be displayed
   */
  std::vector< process::Field::Field_ > supportedFields_;
  void mergeProcesses(std::vector< process::Process > oldProcesses);
};

#endif
