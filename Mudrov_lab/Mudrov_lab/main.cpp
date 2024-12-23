﻿#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include "cs.h"
#include "pipeline.h"
#include "logs.h"
using std::cin;
using std::cout;
int main()
{
    std::ofstream logfile("log1.txt");
    redirect_output_wrapper redirector(std::cerr);
    redirector.redirect(logfile);
    std::unordered_map<int, Pipeline> pipes;
    std::unordered_map<int, CS> css;
    short int menu_choice = -1;
    while (true)
    {
        cout << "Menu\n" << "Select menu item\n";
        cout << "1 - add pipeline\n";
        cout << "2 - add CS\n";
        cout << "3 - all objects\n";
        cout << "4 - save in file\n";
        cout << "5 - download from file\n";
        cout << "6 - all objects\n";
        cout << "7 - delete pipe\n";
        cout << "9 - delete cs\n";
        cout << "0 - exit\n";
        cout << "--------------------------------------------------------------------\n";

        menu_choice = read_input<short int>("Select menu item: ", 0, 11);
        switch (menu_choice)
        {
        case 1: cin >> pipes; break;
        case 2: cin >> css; break;
        case 3: cout << pipes; cout << css; break;
        case 4: {
            if (css.size() != 0 || pipes.size() != 0)
            {
                std::ofstream outfile(read_input<std::string>("Enter file name: ")); outfile << css; outfile << pipes; outfile.close(); cout << "saved in file\n";
            }
            else { cout << "you don't have pipes and cs\n"; } break;
        }
        case 5: {
            std::ifstream outfile(read_input<std::string>("Enter file name: ")); outfile >> css;
            outfile.clear(); outfile.seekg(0, std::ios::beg); outfile >> pipes; outfile.close(); break;
        }
        case 6: filter_pipes_by_name(pipes); break;
        case 7: filter_pipes_by_repair(pipes); break;
        case 8: filter_cs_by_name(css); break;
        case 9: filter_cs_by_work_percentage(css); break;
        case 10: { cout << pipes; int ch = read_input<int>("Enter ID of pipe: ", 0, pipes.size() - 1); pipes.erase(ch); break; }
        case 11: { cout << css; int ch = read_input<int>("Enter ID of cs: ", 0, css.size() - 1); css.erase(ch); break; }
        case 0: logfile.close(); return 0;
        }
    }
    return 0;
}