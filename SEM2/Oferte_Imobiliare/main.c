#include "ui/ui.h"
#include "repo/repo.h"
#include "service/service.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void ruleaza_teste();

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
    ruleaza_teste();
    Repo repo;
    init_repo(&repo);
    Service service;
    init_service(&service,&repo);
    start_ui(&repo,&service);
    destroy(&repo);
    _CrtDumpMemoryLeaks();
}