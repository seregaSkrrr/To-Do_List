#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainFrame* mf = new MainFrame("To-Do List");
    mf->SetClientSize(800, 600);
    mf->Center();
    mf->Show();
    return true;
}