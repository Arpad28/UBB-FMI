#include "teste/teste.h"
#include "repo/repository.h"
#include "service/service.h"
#include "ui/ui.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <iostream>
#include <crtdbg.h>

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);

    {
        int optiune;
        ruleaza_toate_testele();
        std::cout<<"Alege cu ce Repo sa lucrezi:\n"
                   "1.MemoryRepo\n"
                   "2.FileRepo\n"
                   "3.MapRepo\n";
        std::cin>>optiune;
        if (optiune == 2) {
            FileRepo r("activitati.txt");
            Service s(r);
            UI ui(s);
            ui.run();
        }
        else if (optiune == 3) {
            MapRepo r(0.5);
            Service s(r);
            UI ui(s);
            ui.run();
        }
        else if (optiune == 1) {
            MemoryRepo r;
            Service s(r);
            UI ui(s);
            ui.run();
        }
    }

    _CrtDumpMemoryLeaks();
    return 0;
}