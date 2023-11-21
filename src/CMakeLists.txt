target_sources(${target} PUBLIC
  GUI/Model/ProcessTableModel.cpp
  GUI/Model/ProcessTableModel.hpp
  
  GUI/MainWindow/MainWindow.cpp
  GUI/MainWindow/MainWindow.hpp
  GUI/MainWindow/Ui/UiMainWindow.hpp
  
  Process/Objects/Process.cpp
  Process/Objects/Process.hpp

  Process/ProcessFetchers/Interface/ProcessFetcherI.hpp
  Process/ProcessFetchers/Linux/ProcessFetcherLinux.hpp
  Process/ProcessFetchers/Test/ProcessFetcherTest.hpp
  Process/ProcessFetchers/Test/ProcessFetcherTest.cpp

  main.cpp
)