#pragma once

#include <QMainWindow>

namespace rf433::app {

enum class AdapterFamily {
    Ft232H,
    Mcp2210,
};

class MainWindow final : public QMainWindow {
public:
    explicit MainWindow(AdapterFamily adapterFamily);

private:
    AdapterFamily adapterFamily_;
};

} // namespace rf433::app
