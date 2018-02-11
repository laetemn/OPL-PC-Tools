/***********************************************************************************************
 *                                                                                             *
 * This file is part of the OPL PC Tools project, the graphical PC tools for Open PS2 Loader.  *
 *                                                                                             *
 * OPL PC Tools is free software: you can redistribute it and/or modify it under the terms of  *
 * the GNU General Public License as published by the Free Software Foundation,                *
 * either version 3 of the License, or (at your option) any later version.                     *
 *                                                                                             *
 * OPL PC Tools is distributed in the hope that it will be useful,  but WITHOUT ANY WARRANTY;  *
 * without even the implied warranty of  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  *
 * See the GNU General Public License for more details.                                        *
 *                                                                                             *
 * You should have received a copy of the GNU General Public License along with MailUnit.      *
 * If not, see <http://www.gnu.org/licenses/>.                                                 *
 *                                                                                             *
 ***********************************************************************************************/

#include <QMessageBox>
#include <OplPcTools/ApplicationInfo.h>
#include <OplPcTools/UI/GameCollectionWidget.h>
#include <OplPcTools/UI/Application.h>

using namespace OplPcTools;
using namespace OplPcTools::UI;

namespace {

class PrivateApplication : public Application
{
public:
    PrivateApplication(int & _argc, char ** _argv) :
        Application(_argc, _argv)
    {
    }
};

PrivateApplication * gp_application = nullptr;

} // namespace

Application::Application(int & _argc, char ** _argv) :
    QApplication(_argc, _argv),
    mp_main_window(nullptr),
    mp_game_collection(nullptr)
{
    mp_game_collection = new Core::GameCollection(this);
}

Application::~Application()
{
    delete mp_main_window;
    delete mp_game_collection;
}

Application & Application::instance()
{
    return *gp_application;
}

void Application::showMainWindow()
{
    ensureMainWindow()->show();
}

MainWindow * Application::ensureMainWindow()
{
    if(!mp_main_window)
        mp_main_window = new MainWindow();
    return mp_main_window;
}

void Application::showErrorMessage(const QString &_message)
{
    QMessageBox::critical(ensureMainWindow(), tr("Error"), _message);
}

bool Application::pushActivity(Intent & _intent)
{
    return ensureMainWindow()->pushActivity(_intent);
}

Core::GameCollection & Application::gameCollection() const
{
    return *mp_game_collection;
}

int main(int _argc, char * _argv[])
{
    gp_application = new PrivateApplication(_argc, _argv);
    gp_application->setApplicationName(APPLICATION_NAME);
    gp_application->setApplicationVersion(APPLICATION_VERSION);
    gp_application->setOrganizationName("brainstream");
    QSharedPointer<OplPcTools::UI::Intent> intent = OplPcTools::UI::GameCollectionWidget::createIntent();
    gp_application->pushActivity(*intent);
    gp_application->showMainWindow();
    int result = gp_application->exec();
    delete gp_application;
    gp_application = nullptr;
    return result;
}
