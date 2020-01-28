#include "UpdateManager.h"

std::list<Process*> *UpdateManager::spProcessList = nullptr;
std::list<Process*> *UpdateManager::spTimedProcessList = nullptr;
std::vector<Process*> *UpdateManager::spSafeList = nullptr;
std::vector<Process*> *UpdateManager::spTimedSafeList = nullptr;
std::list<Process*> *UpdateManager::spUIUpdateList = nullptr;
bool UpdateManager::sSafeItemToClear = false;
bool UpdateManager::sSafeTimedItemToClear = false;
bool UpdateManager::sPause = false;


void UpdateManager::Init()
{
	UpdateManager::spProcessList = new std::list<Process*>();
	UpdateManager::spTimedProcessList = new std::list<Process*>();
	UpdateManager::spSafeList = new std::vector<Process*>();
	UpdateManager::spTimedSafeList = new std::vector<Process*>();
	static bool m_SafeItemToClear;
	static bool m_SafeTimedItemToClear = false;
}

void UpdateManager::Update(float deltaTime)
{
	if (sPause)
	{
		return;
	}

	for (Process *process : *spProcessList)
	{
		if (process != nullptr)
		{
			process->Update(deltaTime);
		}
	}
	if (sSafeItemToClear)
	{
		for (Process *process : *spSafeList)
		{
			spProcessList->remove(process);
			process->OnSafeClear();
		}
		spSafeList->clear();
		sSafeItemToClear = false;
	}
}

void UpdateManager::TimedUpdate(float deltaTime)
{
	if (sPause)
	{
		return;
	}

 	for (Process *timedProcess : *spTimedProcessList)
	{
		if (timedProcess != nullptr)
		{
			timedProcess->TimedUpdate(deltaTime);
		}
	}
	if (sSafeTimedItemToClear)
	{
		for (Process *process : *spTimedSafeList)
		{
			spTimedProcessList->remove(process);
			process->OnSafeClear();
		}
		spTimedSafeList->clear();
		sSafeTimedItemToClear = false;
	}
}

bool UpdateManager::RegisterUpdate(Process *const process)
{
	if (spProcessList != nullptr && !HasDuplicateProcess(process, spProcessList))
	{
		spProcessList->push_back(process);
		return true;
	}
	return false;
}

bool UpdateManager::ClearUpdate(Process *const process)
{
	if (spProcessList != nullptr)
	{
		spProcessList->remove(process);
		process->OnSafeClear();
		return true;
	}
	return false;
}

bool UpdateManager::RegisterTimedUpdate(Process *process)
{
	if (spTimedProcessList != nullptr && !HasDuplicateProcess(process, spTimedProcessList))
	{
		spTimedProcessList->push_back(process);
		return true;
	}
	return false;
}

bool UpdateManager::ClearTimedUpdate(Process *const process)
{
	if (spTimedProcessList != nullptr)
	{
		spTimedProcessList->remove(process);
		process->OnSafeClear();
		return true;
	}
	return false;
}

bool UpdateManager::SafeClearUpdate(Process *const process)
{
	if (spSafeList != nullptr)
	{
		spSafeList->push_back(process);
		sSafeItemToClear = true;
		return true;
	}
	return false;
}

void UpdateManager::UIUpdate(float deltaTime)
{
	for (Process *UIProcess : *spUIUpdateList)
	{
		if (UIProcess != nullptr)
		{
			UIProcess->TimedUpdate(deltaTime);
		}
	}
}

bool UpdateManager::RegisterUIUpdate(Process * process)
{
	if (spUIUpdateList != nullptr && !HasDuplicateProcess(process, spUIUpdateList))
	{
		spUIUpdateList->push_back(process);
		return true;
	}
	return false;
}

bool UpdateManager::ClearUIUpdate(Process * const process)
{
	if (spTimedProcessList != nullptr)
	{
		spTimedProcessList->remove(process);
		return true;
	}
	return false;
}

bool UpdateManager::SafeClearTimedUpdate(Process *const process)
{
	if (spTimedSafeList != nullptr)
	{
		spTimedSafeList->push_back(process);
		sSafeTimedItemToClear = true;
		return true;
	}
	return false;
}

void UpdateManager::ClearAllUpdates()
{
	if (spProcessList != nullptr)
	{
		spProcessList->clear();
	}
	if (spTimedProcessList != nullptr)
	{
		spTimedProcessList->clear();
	}
	if (spSafeList != nullptr)
	{
		spSafeList->clear();
	}
	if (spTimedSafeList != nullptr)
	{
		spTimedSafeList->clear();
	}
	if (spUIUpdateList != nullptr)
	{
		spUIUpdateList->clear();
	}
}

void UpdateManager::Clean()
{
	ClearAllUpdates();
	SAFE_DELETE(UpdateManager::spProcessList);
	SAFE_DELETE(UpdateManager::spTimedProcessList);
	SAFE_DELETE(UpdateManager::spSafeList);
	SAFE_DELETE(UpdateManager::spTimedSafeList);
	SAFE_DELETE(UpdateManager::spUIUpdateList);
}

bool UpdateManager::HasDuplicateProcess(const Process *const process, std::list<Process*> *const processList)
{
	for (std::list<Process*>::iterator iter = processList->begin(); iter != processList->end(); ++iter)
	{
		if (process == *iter)
		{
			return true;
		}
	}
	return false;
}

void UpdateManager::Pause(bool state)
{
	sPause = state;
}

bool UpdateManager::GetPausedState()
{
	return sPause;
}
