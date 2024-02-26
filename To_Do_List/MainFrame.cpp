#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	CreateControls();
	BindEventHandlers();
	AddSavedTasks();
}

void MainFrame::CreateControls() {
	wxFont HeadLineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 24)));

	Panel = new wxPanel(this);
	Panel->SetFont(mainFont);

	HeadLineText = new wxStaticText(Panel, wxID_ANY, "To-Do List", wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	HeadLineText->SetFont(HeadLineFont);
	HeadLineText->SetBackgroundColour(wxNullColour);

	InputField = new wxTextCtrl(Panel, wxID_ANY, "", wxPoint(100, 80), wxSize(495, 35), wxTE_PROCESS_ENTER);
	AddButton = new wxButton(Panel, wxID_ANY, "Add", wxPoint(600, 80), wxSize(100, 35));
	CheckListBox = new wxCheckListBox(Panel, wxID_ANY, wxPoint(100, 120), wxSize(600, 400));
	ClearButton = new wxButton(Panel, wxID_ANY, "Clear", wxPoint(100, 525), wxSize(100, 35));
}

void MainFrame::BindEventHandlers() {
	AddButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddButtonClicked, this);
	InputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputEnter, this);
	CheckListBox->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this);
	ClearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClicked, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClosed, this);
}

void MainFrame::AddSavedTasks(){
	std::vector<Task> tasks = LoadTasksFromFile("C:\\Users\\Public\\Downloads\\Tasks_From_To_Do_List.txt");

	for (const Task& task : tasks) {
		int index = CheckListBox->GetCount();
		CheckListBox->Insert(task.description, index);
		CheckListBox->Check(index, task.done);
	}
}

void MainFrame::AddTaskFromInput() {
	wxString description = InputField->GetValue();
	if (!description.IsEmpty()) {
		CheckListBox->Insert(description, CheckListBox->GetCount());
		InputField->Clear();
	}
	InputField->SetFocus();
}

void MainFrame::DeleteSelectedTask() {
	int SelectedIndex = CheckListBox->GetSelection();

	if (SelectedIndex == wxNOT_FOUND) {
		return;
	}

	CheckListBox->Delete(SelectedIndex);
}

void MainFrame::MoveSelectedTask(int offset) {
	int SelectedIndex = CheckListBox->GetSelection();

	if (SelectedIndex == wxNOT_FOUND) {
		return;
	}

	int NewIndex = SelectedIndex + offset;

	if (NewIndex >= 0 && NewIndex < CheckListBox->GetCount()) {
		SwapTasks(SelectedIndex, NewIndex);
		CheckListBox->SetSelection(NewIndex, true);
	}
}

void MainFrame::SwapTasks(int first, int second) {
	Task task1{ CheckListBox->GetString(first).ToStdString(), CheckListBox->IsChecked(first) };
	Task task2{ CheckListBox->GetString(second).ToStdString(), CheckListBox->IsChecked(second) };

	CheckListBox->SetString(first, task2.description);
	CheckListBox->Check(first, task2.done);

	CheckListBox->SetString(second, task1.description);
	CheckListBox->Check(second, task1.done);
}

void MainFrame::OnAddButtonClicked(wxCommandEvent& evt) {
	AddTaskFromInput();
}

void MainFrame::OnInputEnter(wxCommandEvent& evt){
	AddTaskFromInput();
}

void MainFrame::OnListKeyDown(wxKeyEvent& evt){
	switch (evt.GetKeyCode()){
		case WXK_DELETE:
			DeleteSelectedTask();
			break;
		case WXK_UP:
			MoveSelectedTask(-1);
			break;
		case WXK_DOWN:
			MoveSelectedTask(1);
			break;
	}
}

void MainFrame::OnClearButtonClicked(wxCommandEvent& evt){
	if (CheckListBox->IsEmpty()) return;

	wxMessageDialog Dialog(this, "Are you completely want to clear all the To-Do list?", "Clear", wxYES_NO);
	int result = Dialog.ShowModal();

	if (result == wxID_YES) CheckListBox->Clear();
}

void MainFrame::OnWindowClosed(wxCloseEvent& evt){
	std::vector<Task> tasks;

	for (int temp{ 0 }; temp < CheckListBox->GetCount(); temp++) {
		Task task;
		task.description = CheckListBox->GetString(temp);
		task.done = CheckListBox->IsChecked(temp);
		tasks.push_back(task);
	}

	SaveToFile(tasks, "C:\\Users\\Public\\Downloads\\Tasks_From_To_Do_List.txt");
	evt.Skip();
}