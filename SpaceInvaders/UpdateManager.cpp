#include "UpdateManager.h"

std::list<Process*> *UpdateManager::spProcessList = nullptr;
std::list<Process*> *UpdateManager::spTimedProcessList = nullptr;

void UpdateManager::Init()
{
	UpdateManager::spProcessList = new std::list<Process*>();
	UpdateManager::spTimedProcessList = new std::list<Process*>();
}

void UpdateManager::Update(float deltaTime)
{
	for (Process *process : *spProcessList)
	{
		if (process != nullptr)
		{
			process->Update(0);
		}
	}
}

void UpdateManager::TimedUpdate(float deltaTime)
{
	for (Process *timedProcess : *spTimedProcessList)
	{
		if (timedProcess != nullptr)
		{
			timedProcess->Update(0);
		}
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
}

void UpdateManager::Clean()
{
	ClearAllUpdates();
	delete(UpdateManager::spProcessList);
	delete(UpdateManager::spTimedProcessList);
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