/***********************************************************************************************
 *                                                                                             *
 * This file is part of the qpcopl project, the graphical PC tools for Open PS2 Loader.        *
 *                                                                                             *
 * qpcopl is free software: you can redistribute it and/or modify it under the terms of        *
 * the GNU General Public License as published by the Free Software Foundation,                *
 * either version 3 of the License, or (at your option) any later version.                     *
 *                                                                                             *
 * qpcopl is distributed in the hope that it will be useful,  but WITHOUT ANY WARRANTY;        *
 * without even the implied warranty of  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  *
 * See the GNU General Public License for more details.                                        *
 *                                                                                             *
 * You should have received a copy of the GNU General Public License along with MailUnit.      *
 * If not, see <http://www.gnu.org/licenses/>.                                                 *
 *                                                                                             *
 ***********************************************************************************************/

#ifndef __QPCOPL_GAMEINSTALLDIALOG__
#define __QPCOPL_GAMEINSTALLDIALOG__

#include <QAbstractTableModel>
#include "ui_GameInstallDialog.h"
#include "GameInstallThread.h"
#include "GameInstaller.h"
#include "Iso9660GameInstallerSource.h"

class GameInstallDialog : public QDialog, private Ui::GameInstallDialog
{
    Q_OBJECT

public:
    explicit GameInstallDialog(UlConfig & _config, QWidget * _parent = nullptr);
    ~GameInstallDialog() override;

public slots:
    void reject() override;

protected:
    void closeEvent(QCloseEvent * _event) override;

private slots:
    void addTask();
    void install();
    void installProgress(quint64 _total_bytes, quint64 _processed_bytes);
    void rollbackStarted();
    void rollbackFinished();
    void registrationStarted();
    void registrationFinished();
    void threadFinished();
    void installerError(QString _message);
    void taskSelected(const QModelIndex & _index, const QModelIndex & _prev_index);
    void renameGame();
    void removeGame();

private:
    bool startTask();
    void setCurrentProgressBarUnknownStatus(bool _unknown, int _value = 0);
    void setTaskError(const QString & _message, int _index = -1);

private:
    GameInstallThread * mp_work_thread;
    GameInstaller * mp_installer;
    Iso9660GameInstallerSource * mp_source;
    UlConfig & mr_config;
    int m_processing_task_index;
    bool m_is_canceled;
};

#endif // __QPCOPL_GAMEINSTALLDIALOG__
