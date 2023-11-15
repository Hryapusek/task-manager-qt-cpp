target_sources(${target} PUBLIC
  MainWindow/Model/ProcessTableModel.cpp
  MainWindow/Model/ProcessTableModel.hpp
  
  MainWindow/MainWindow.cpp
  MainWindow/MainWindow.hpp
  MainWindow/UiMainWindow.hpp
  
  Process/Objects/Process.cpp
  Process/Objects/Process.hpp

  Process/ProcessFetchers/Interface/ProcessFetcherI.hpp
  Process/ProcessFetchers/Linux/ProcessFetcherLinux.hpp
  Process/ProcessFetchers/Test/ProcessFetcherTest.hpp
  Process/ProcessFetchers/Test/ProcessFetcherTest.cpp

  main.cpp
)