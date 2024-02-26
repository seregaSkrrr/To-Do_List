#pragma once
#include <wx/wx.h>
#include <string>
#include <vector>
#include <algorithm>
#include "Task.h"

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
private:
	wxPanel* Panel;
	wxStaticText* HeadLineText;
	wxTextCtrl* InputField;
	wxButton* AddButton;
	wxButton* ClearButton;
	wxCheckListBox* CheckListBox;

	void CreateControls();
	void BindEventHandlers();
	void AddSavedTasks();

	void AddTaskFromInput();
	void DeleteSelectedTask();
	void MoveSelectedTask(int offset);
	void SwapTasks(int first, int second);

	void OnAddButtonClicked(wxCommandEvent& evt);
	void OnInputEnter(wxCommandEvent& evt);
	void OnListKeyDown(wxKeyEvent& evt);
	void OnClearButtonClicked(wxCommandEvent& evt);
	void OnWindowClosed(wxCloseEvent& evt);
};