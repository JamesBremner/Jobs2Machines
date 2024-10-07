#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wex.h>
#include "cStarterGUI.h"
#include "GraphTheory.h"

/// @brief  A possible assignment of job to machine
class cAssign
{
    int myValue;
    int myJobType;
    int myMachineType;

public:
    cAssign(int job, int machine, int value)
        : myValue(value),
          myJobType(job),
          myMachineType(machine)
    {
    }
    int job() const
    {
        return myJobType;
    }
    int machine() const
    {
        return myMachineType;
    }
};

class cJob
{
public:
    int myType;
    std::string name() const
    {
        return name(myType);
    }
    static std::string name(int type)
    {
        return "job_" + std::to_string(type);
    }
};

class cMachine
{
public:
    int myType;
    static std::string name(int type)
    {
        return "mac_" + std::to_string(type);
    }
};

struct sProblem
{
    std::vector<cAssign> assigns;
    std::vector<cJob> jobs;
    std::vector<cMachine> machines;

    raven::graph::sGraphData gd;

public:
    void addAssign(int job, int machine, int value)
    {
        assigns.emplace_back(job, machine, value);
    }
};

sProblem theProblem;

void makeGraph()
{
    theProblem.gd.g.directed();

    for (auto &a : theProblem.assigns)
    {
        auto job = cJob::name(a.job());
        auto mac = cMachine::name(a.machine());
        theProblem.gd.g.add("src", job);
        theProblem.gd.g.add(job,mac);
        theProblem.gd.g.add(mac,"snk");

    }
}

void textGraph()
{
    for (auto &edge : theProblem.gd.g.edgeList())
        std::cout << theProblem.gd.g.userName(edge.first)
                  << " > " << theProblem.gd.g.userName(edge.second) << "\n";
}

void generate1()
{
    theProblem.addAssign(1, 1, 3);
}

class cGUI : public cStarterGUI
{
public:
    cGUI()
        : cStarterGUI(
              "Starter",
              {50, 50, 1000, 500}),
          lb(wex::maker::make<wex::label>(fm))
    {
        lb.move(50, 50, 100, 30);
        lb.text("Hello World");

        show();
        run();
    }

private:
    wex::label &lb;
};

main()
{
    generate1();
    makeGraph();
    textGraph();

    cGUI theGUI;
    return 0;
}
