#include <iostream>
#include <cassert>
#include <ctime>

class House
{
    bool residentPresence = false;
    std::string residentName = "none";
  public:
    House(std::string inResidentName): residentName(inResidentName)
    {
        if (residentName != "none") residentPresence = true;
    }

    std::string get_name()
    {
        return residentName;
    }

    bool get_status()
    {
        return residentPresence;
    }
};

class Middle_branch
{
    House* house = nullptr;
  public:
    Middle_branch()
    {
        std::string inResidentName = "none";
        std::cout << "Input the resident name: ";
        std::cin >> inResidentName;
        house = new House(inResidentName);
    }

    bool find_resident(std::string name)
    {
        if (house->get_name() == name) return true;
        return false;
    }

    bool get_house_status()
    {
        return house->get_status();
    }
};

class Big_branch
{
    int count = 2;
    Middle_branch** middleBranches = nullptr;
    House* house = nullptr;

    bool check_house(std::string name)
    {
        if (house->get_name() == name) return true;
        return false;
    }

    bool check_branches(std::string name)
    {
        for (int i = 0; i < count; ++i) {
            if (middleBranches[i]->find_resident(name)) return true;
        }
        return false;
    }

    void neighbor_count(std::string name)
    {
        int neighborCount = 0;
        if (house->get_status()) ++neighborCount;
        for (int i = 0; i < count; ++i) {
            if (middleBranches[i]->get_house_status()) ++neighborCount;
        }
        std::cout << name << " has " << neighborCount << " neighbors." << std::endl;
    }

  public:
    Big_branch()
    {
        std::string inResidentName = "none";
        std::cout << "Input the resident name: ";
        std::cin >> inResidentName;
        house = new House(inResidentName);

        srand(time(NULL));
        count = (rand() % 2) + 2;
        middleBranches = new Middle_branch*[count];
        for (int i = 0; i < count; ++i) {
            middleBranches[i] = new Middle_branch();
        }
    }

    bool find_resident(std::string name)
    {
        if (check_house(name) || check_branches(name)) {
            neighbor_count(name);
            return true;
        }
        return false;
    }
};

class Tree
{
    int count = 3;
    Big_branch** bigBranches = nullptr;

  public:
    Tree()
    {
        srand(time(NULL));
        count = (rand() % 3) + 3;
        bigBranches = new Big_branch*[count];
        for (int i = 0; i < count; ++i) {
            bigBranches[i] = new Big_branch();
        }
    }

    bool find_resident(std::string name)
    {
        for (int i = 0; i < count; ++i) {
            if (bigBranches[i]->find_resident(name)) return true;
        }
        return false;
    }
};

class Village
{
    int count = 5;
    Tree** trees = new Tree*[count];

  public:
    Village()
    {
        trees = new Tree*[count];
        for (int i = 0; i < count; ++i) {
            trees[i] = new Tree();
        }
    }

    bool find_resident(std::string name)
    {
        for (int i = 0; i < 5; ++i) {
            if (trees[i]->find_resident(name)) return true;
        }
        return false;
    }
};

int main() {
    Village* village = new Village();
    std::string name;
    while(name != "exit") {
        std::cout << "Input the name: ";
        std::cin >> name;
        if (name != "exit") {
            if (!village->find_resident(name)) std::cout << "Couldn't find anyone with the name " << name << std::endl;
        }
    }
    delete village;
    village = nullptr;
    return 0;
}
