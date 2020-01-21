#pragma once

#include "Process.h"
#include <list>

class UpdateManager
{
public:
	static void Init();

	static void Update(float deltaTime);
	static void TimedUpdate(float deltaTime);

	static bool RegisterUpdate(Process *process);
	static bool ClearUpdate(Process *const process);

	static bool RegisterTimedUpdate(Process *process);
	static bool ClearTimedUpdate(Process *const process);

	static void ClearAllUpdates();
	static void Clean();

	static bool HasDuplicateProcess(const Process *const process, std::list<Process*> *const processList);

private:
	static std::list<Process*> *spProcessList;
	static std::list<Process*> *spTimedProcessList;
};