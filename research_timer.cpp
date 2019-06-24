#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <cmath>
#include <sys/stat.h>

std::chrono::duration<double> trial_fun()
{
    auto start = std::chrono::high_resolution_clock::now();



    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    return elapsed;
}

void std_calc(std::ostream& out, double& sum, std::vector<double>& times, double& average)
{
    float variance = 0.0, stdDev;
    
    /* calculate variance */
    for (int i = 0; i <  static_cast<int>(times.size()); i++)
    {
        variance += pow(times[i] - average,2);
        variance /= times.size();
    }
    
    stdDev = sqrt(variance);
    out << "stdDev: " << stdDev << " s\n";
    std::cout <<  "stdDev: " << stdDev << " s\n";
}

/* source: https://www.systutorials.com/topic/how-to-test-a-file-or-directory-exists-in-c/ */
bool IsPathExist(const std::string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}

int main()
{
    /* create folder for storing txt files */
    const std::string path = "/home/pablo.say54/graphene/LibOS/shim/test/native";
    if (!IsPathExist(path))
    {
        const int dir_err = mkdir("data_files", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (-1 == dir_err)
        {
            printf("Error creating directory!n");
            exit(1);
        }
    }

    /* declare things */
    std::chrono::duration<double> time;
    std::vector<double> times_vect;
    double sum = 0;
    int num = 0;

    /* Testing input */
    std::cout << "Enter number of trials to run: \n";
    std::cin >> num;
    std::string str_num = std::to_string(num);

    /* trial runs */
    std::ofstream ofs1(path + str_num + "_trials.txt");
    for (int i = 0; i < num; i++)
    {
        time = trial_fun();

        /* update values */
        sum+= time.count();
        times_vect.push_back(time.count());

        /* print info */
        std::cout << "Elapsed Time: " << time.count() << " s\n";
        ofs1 << time.count() << " s\n";  
    }

    /* calculate average & print data to external file */
    double average = sum/num;
    std::cout << "Average Runtime: " << average << " s\n";
    ofs1 << "Average Runtime: " << average << " s\n";
    std::cout << times_vect[0] << std::endl;
    std_calc(ofs1, sum, times_vect, average);
    ofs1.close();
}