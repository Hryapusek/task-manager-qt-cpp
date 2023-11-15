if ! uic mainwindow.ui > UiMainWindow.hpp
then
  echo "Error generating UiMainWindow.hpp"
else
  echo "File UiMainWindow.hpp generated"
fi