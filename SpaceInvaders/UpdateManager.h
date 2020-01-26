#pragma once

#include "Process.h"
#include "Engine.h"
#include <list>
#include <vector>

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

	static bool SafeClearTimedUpdate(Process *const process);
	static bool SafeClearUpdate(Process *const process);

	static void ClearAllUpdates();
	static void Clean();

	static bool HasDuplicateProcess(const Process *const process, std::list<Process*> *const processList);

private:
	static std::list<Process*> *spProcessList;
	static std::list<Process*> *spTimedProcessList;
	static std::vector<Process*> *spTimedSafeList;
	static std::vector<Process*> *spSafeList;
	static bool sSafeItemToClear;
	static bool sSafeTimedItemToClear;
};