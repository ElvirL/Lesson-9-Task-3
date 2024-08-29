/*
������� 3. ��������� ������ ��������
��� ����� �������
���������� ��������� ������ ��������. � �������� ���������� ������������ ���������� � ���������. ���� �������� �������, ����������, 
�������� �� �������. � ������ ������� ���� �������� �������� �����. ���� ��������� ��������� ����� ��������. � ���� �����������, 
������� ������������, ���� �����.

����� �������� ��������� �������������� ����������. �� ���������� �������� ������ �������� � ������ �������� ������. ��������� 
�������� ����� ��������� ��� ������ �� ��������� � ������� �� ����� ����������. ���������� ��������� ������.
� ���������� ������ ������ ������ ��������� ���������� �������. �������� ����� �������� ��������� �� ������������ ����� � �������� �� 
����� ��� �������������� ����������������.
� ������ �������������� ������ ������ ��� ���������� ��������� �����. ������ �� ����������, �������� ���� ��� ������������� �������, 
��������� � ��� ���� ���������� ����� � �������� � �������������� ������ ������� std::srand().
� �� ������ ���� ����� ����������� ����� ���������� �����, ������� ��������� ��������� ������ ��������, � �� 1 �� ���������� ���������� 
� ������. ����� ���� ��� ���� ����� ��� ����������: A, B � C. ��� ���� ���������� �������� � �������������� ����� ���������� ��������.
� ��� ������ ��������� ������������ ��������� � ����������� ����� ���������� ������ � ���������� ���������� � ������ �� ������.
� ����� ������������ ������ ����� �����, ������� ������������� ��������� ������������ ��������. ����� �����-�� �������� ��� �������� 
������� �������� ��� ������, �� ���� ���������� � ����������� �����, ������� ��� ����������� ����������. ��������� �����������, 
����� ��� ��������� ������ ������-�� ��������.

������ � ������������
����������� ���� ��������� � ������, ������� �������� ������� ��� ������������� ����������� � ��������� this, ���� �����������.
����� ������������������� ��������� ��������� �����, ����������� std::srand(hash); ��� hash � ����� ��������� � ���������� ��������, 
��������, ID ����� ������ � �������. ��� ��������� ���������� ����� ����������� ���������� ��������� ��������� ����� ���: 
int tasksCount = rand() % (team->workers.size() + 1);
*/

#include <iostream>
#include <ctime>
#include <vector>

enum type_task{
    None,
    A,
    B,
    C
};

std::string print_type_task_enum(type_task type){
    
    if (type == 1)
        return "A";

    if (type == 2)
        return "B";

    if (type == 3)
        return "C";

    return "None";
}

class HeadCompany{
    std::string name;
    int task_number;

public:
    HeadCompany(){
        std::cout << "Enter head name: ";
        std::string in_name;
        std::cin >> in_name;
        name = in_name;
    }

    int get_task(){
        std::cout << "Enter task: ";
        std::cin >> task_number;
        return task_number;
    }
};

class Worker{
    std::string name;
    bool is_busy = false;
    type_task temp_type_task = None;

public:
    Worker(){
        std::cout << "Enter worker name: ";
        std::string in_name;
        std::cin >> in_name;
        name = in_name;
    }

    void get_task(type_task type){
        is_busy = true;
        temp_type_task = type;
    }

    bool get_status(){
        return is_busy;
    }

    void set_status(bool status){
        is_busy = status;
    }

    void set_temp_type_task(type_task task){
        temp_type_task = task;
    }

    std::string get_name_worker(){
        return name;
    }

};

class Manager{
    std::string name;

public:
    Manager(){

    }

    Manager(std::string in_name): name(in_name){
    }
};

class Team{
    Manager manager;
    std::vector<Worker> workers;
    int id_team;

public:
    Team(int in_id_team, std::string manager_name, int number_workers){
        id_team = in_id_team;

        Manager in_manager(manager_name);
        manager = in_manager;
        
        for (int i=0; i<number_workers; ++i){
            Worker w;
            workers.push_back(w);
        }
    }

    int get_cout_free_worker(){
        int count = 0;
        for (size_t i=0; i<workers.size(); ++i){
            if (!workers[i].get_status()){
                ++count;
            }
        }
        return count;
    }

    void get_tasks(int task){
        std::srand(task+id_team);
        int tasksCount = rand() % workers.size() + 1;
        
        size_t index = 0;
        while (tasksCount > 0 && index < workers.size()){
            if (get_cout_free_worker() == 0){
                    break;
                }

            if (!workers[index].get_status()){
                workers[index].set_status(true);
                type_task type;
                int rand_type_task = (rand() % 3) + 1;
                type = static_cast<type_task>(rand_type_task);
                workers[index].set_temp_type_task(type);
                std::cout << workers[index].get_name_worker() << " get task \"" << print_type_task_enum(type) << "\"" << std::endl;
                --tasksCount;
            }
            ++index;
        }

    }

};

int cout_free_workers_in_teams(std::vector<Team> teams){
    int sum = 0;
    for (size_t i=0; i<teams.size(); ++i){
        sum+=teams[i].get_cout_free_worker();
    }
    return sum;
}

int main(){
    HeadCompany head_company;

    std::vector<Team> teams;
    
    std::cout << "Enter number teams: ";
    int number_teams;
    std::cin >> number_teams;

    for (int i=0; i<number_teams; ++i){
        std::cout << "Enter manager name: " << std::endl;
        std::string manager_name;
        std::cin >> manager_name;

        std::cout << "Enter number of workers: ";
        int number_workers;
        std::cin >> number_workers;

        Team team(i,manager_name,number_workers);
        teams.push_back(team);
    }

    while (cout_free_workers_in_teams(teams) >0){
        int head_task = head_company.get_task();
        for (size_t i=0; i<teams.size(); ++i){
            teams[i].get_tasks(head_task);
        }
    }

}