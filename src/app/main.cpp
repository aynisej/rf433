#include "rf433/app/main_window.hpp"

#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QStandardPaths>
#include <QVBoxLayout>

namespace {

QString settingsFilePath() {
    const QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appDataPath);
    return QDir(appDataPath).filePath(QStringLiteral("settings.ini"));
}

bool agreementWasAccepted() {
    QSettings settings(settingsFilePath(), QSettings::IniFormat);
    return settings.value(QStringLiteral("agreement/accepted"), false).toBool();
}

void saveAgreementAcceptance() {
    QSettings settings(settingsFilePath(), QSettings::IniFormat);
    settings.setValue(QStringLiteral("agreement/accepted"), true);
    settings.sync();
}

class AgreementDialog final : public QDialog {
public:
    explicit AgreementDialog(QWidget* parent = nullptr)
        : QDialog(parent) {
        setWindowTitle(QStringLiteral("RF433 — Responsible Use"));
        setModal(true);

        auto* layout = new QVBoxLayout(this);
        auto* notice = new QLabel(
            QStringLiteral("Use this application only with devices you are authorized to operate. "
                           "You are responsible for complying with laws and RF regulations in your jurisdiction."),
            this);
        notice->setWordWrap(true);

        auto* acknowledgement = new QCheckBox(
            QStringLiteral("I understand and accept responsibility for lawful use."), this);
        auto* buttons = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
        QPushButton* confirm = buttons->button(QDialogButtonBox::Ok);
        confirm->setEnabled(false);
        confirm->setText(QStringLiteral("Confirm"));

        QObject::connect(acknowledgement, &QCheckBox::toggled, confirm, &QPushButton::setEnabled);
        QObject::connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
        QObject::connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

        layout->addWidget(notice);
        layout->addWidget(acknowledgement);
        layout->addWidget(buttons);
    }
};

class AdapterSelectionDialog final : public QDialog {
public:
    explicit AdapterSelectionDialog(QWidget* parent = nullptr)
        : QDialog(parent) {
        setWindowTitle(QStringLiteral("Select Hardware Interface"));
        setModal(true);

        auto* layout = new QVBoxLayout(this);
        auto* explanation = new QLabel(
            QStringLiteral("Select an adapter family for this session. The selection will be requested again next launch."),
            this);
        explanation->setWordWrap(true);

        auto* choices = new QComboBox(this);
        choices->addItem(QStringLiteral("FT232H"), static_cast<int>(rf433::app::AdapterFamily::Ft232H));
        choices->addItem(QStringLiteral("MCP2210"), static_cast<int>(rf433::app::AdapterFamily::Mcp2210));
        choices->setCurrentIndex(-1);

        auto* buttons = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
        QPushButton* confirm = buttons->button(QDialogButtonBox::Ok);
        confirm->setEnabled(false);
        confirm->setText(QStringLiteral("Continue"));

        QObject::connect(choices, &QComboBox::currentIndexChanged, this,
                         [confirm](const int index) { confirm->setEnabled(index >= 0); });
        QObject::connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
        QObject::connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

        layout->addWidget(explanation);
        layout->addWidget(choices);
        layout->addWidget(buttons);
        choices_ = choices;
    }

    [[nodiscard]] rf433::app::AdapterFamily selectedFamily() const {
        return static_cast<rf433::app::AdapterFamily>(choices_->currentData().toInt());
    }

private:
    QComboBox* choices_{};
};

} // namespace

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);
    QCoreApplication::setOrganizationName(QStringLiteral("RF433"));
    QCoreApplication::setApplicationName(QStringLiteral("RF433"));

    if (!agreementWasAccepted()) {
        AgreementDialog agreement;
        if (agreement.exec() != QDialog::Accepted) {
            return 0;
        }
        saveAgreementAcceptance();
    }

    AdapterSelectionDialog adapterSelection;
    if (adapterSelection.exec() != QDialog::Accepted) {
        return 0;
    }

    rf433::app::MainWindow mainWindow(adapterSelection.selectedFamily());
    mainWindow.show();
    return application.exec();
}
