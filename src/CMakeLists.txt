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
  GUI/MainWindow/LanguageHelper.hpp
  GUI/MainWindow/LanguageHelper.cpp
  GUI/MainWindow/Ui/mainwindow.ui
  GUI/MainWindow/Settings/SettingsDialog.hpp
  GUI/MainWindow/Settings/SettingsDialog.cpp
  GUI/MainWindow/Settings/Ui/settings.ui
  GUI/MainWindow/Settings/Ui/SettingsUi.hpp
  GUI/MainWindow/Settings/Ui/SettingsUi.cpp
  GUI/MainWindow/Settings/Ui/StyleUi.hpp
  GUI/MainWindow/Settings/Ui/StyleUi.cpp
  GUI/MainWindow/Settings/SettingsMemento/StyleContainer.hpp
  GUI/MainWindow/Settings/SettingsMemento/StyleContainer.cpp
  GUI/MainWindow/Settings/SettingsMemento/SettingsMemento.hpp
  GUI/MainWindow/Settings/SettingsMemento/SettingsMemento.cpp
  GUI/MainWindow/Settings.hpp
  GUI/MainWindow/Settings.cpp
  GUI/MainWindow/Utils/ConditionAction.cpp
  GUI/MainWindow/Utils/ConditionAction.hpp

  Process/Objects/Process.cpp
  Process/Objects/Process.hpp

  Process/ProcessFetchers/Interface/ProcessFetcherI.hpp
  Process/ProcessFetchers/Utils/Utils.hpp
  Process/ProcessFetchers/Utils/Utils.cpp
  Process/ProcessFetchers/Test/ProcessFetcherTest.hpp
  Process/ProcessFetchers/Test/ProcessFetcherTest.cpp
)

if (WIN32)
  list(APPEND SOURCES_FILES
    Process/ProcessFetchers/Windows/ProcessFetcherWindows.cpp
    Process/ProcessFetchers/Windows/ProcessFetcherWindows.hpp
  )
elseif (UNIX)
  list(APPEND SOURCES_FILES
    Process/ProcessFetchers/Linux/ProcessFetcherLinux.cpp
    Process/ProcessFetchers/Linux/ProcessFetcherLinux.hpp
  )
endif()

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
