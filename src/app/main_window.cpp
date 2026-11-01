#include "rf433/app/main_window.hpp"

#include "rf433/core/action_policy.hpp"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace rf433::app {

MainWindow::MainWindow(const AdapterFamily adapterFamily)
    : adapterFamily_(adapterFamily) {
    setWindowTitle(QStringLiteral("RF433"));
    resize(420, 360);

    auto* centralWidget = new QWidget(this);
    auto* layout = new QVBoxLayout(centralWidget);
    const QString adapterName = adapterFamily_ == AdapterFamily::Ft232H
                                    ? QStringLiteral("FT232H")
                                    : QStringLiteral("MCP2210");
    auto* status = new QLabel(
        QStringLiteral("Session interface: %1. Foundation build: radio operations and saved-key storage are not implemented yet.")
            .arg(adapterName),
        centralWidget);
    status->setWordWrap(true);

    auto* checkRadio = new QPushButton(QStringLiteral("Check Radio Module Functionality"), centralWidget);
    auto* scan = new QPushButton(QStringLiteral("Scan"), centralWidget);
    auto* savedKeys = new QPushButton(QStringLiteral("Saved Keys"), centralWidget);

    const auto availability = core::mainMenuAvailability(
        core::RadioReadiness::Unknown,
        core::ActiveOperation::None);
    checkRadio->setEnabled(availability.checkRadio);
    scan->setEnabled(availability.scan);
    savedKeys->setEnabled(availability.savedKeys);

    QObject::connect(checkRadio, &QPushButton::clicked, status, [status] {
        status->setText(QStringLiteral("Radio-check service is not implemented in this foundation build."));
    });
    QObject::connect(savedKeys, &QPushButton::clicked, status, [status] {
        status->setText(QStringLiteral("Saved-key storage is not implemented in this foundation build."));
    });

    layout->addWidget(status);
    layout->addWidget(checkRadio);
    layout->addWidget(scan);
    layout->addWidget(savedKeys);
    layout->addStretch(1);
    setCentralWidget(centralWidget);
}

} // namespace rf433::app
