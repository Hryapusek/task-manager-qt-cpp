set(SOURCES_FILES 
  GUI/Model/ProcessTableModel.cpp
  GUI/Model/ProcessTableModel.hpp

  GUI/MainWindow/MainWindow.cpp
  GUI/MainWindow/MainWindow.hpp
  GUI/MainWindow/Actions.cpp
  GUI/MainWindow/Actions.hpp
  GUI/MainWindow/ProcTableSortProxy.cpp
  GUI/MainWindow/ProcTableSortProxy.hpp
  GUI/MainWindow/ProcTableViewHelper.cpp
  GUI/MainWindow/ProcTableViewHelper.hpp
  GUI/MainWindow/MenuBarActions.hpp
  GUI/MainWindow/MenuBarActions.cpp
  GUI/MainWindow/Ui/UiMainWindow.hpp
  GUI/MainWindow/Utils/ConditionAction.cpp
  GUI/MainWindow/Utils/ConditionAction.hpp

  Process/Objects/Process.cpp
  Process/Objects/Process.hpp

  Process/ProcessFetchers/Interface/ProcessFetcherI.hpp
  Process/ProcessFetchers/Linux/ProcessFetcherLinux.cpp
  Process/ProcessFetchers/Linux/ProcessFetcherLinux.hpp
  Process/ProcessFetchers/Test/ProcessFetcherTest.hpp
  Process/ProcessFetchers/Test/ProcessFetcherTest.cpp
)

target_sources(${target} PUBLIC
  ${SOURCES_FILES}
  main.cpp
)

if (build_test_executable)
  target_sources(${test_target} PUBLIC
    ${SOURCES_FILES}
    mainTEST.cpp
  )
  include(FetchContent)
  FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        f8d7d77
  )
  FetchContent_MakeAvailable(googletest)
  cmake_policy(SET CMP0079 NEW)
  target_link_libraries(${test_target} PUBLIC gtest gtest_main)
  target_compile_definitions(${test_target} PRIVATE GTEST_TESTING)
endif()
