#include<stdio.h>
#include<time.h>
#include<iostream>
#include<unistd.h>
#include<fstream>
#include<chrono>
#include<string>

std::chrono::high_resolution_clock::time_point timestamp();
double time(std::chrono::high_resolution_clock::time_point p);

float add(float a, float b);
float subtract(float a, float b);
float multiply(float a, float b);
float divide(float a, float b);

double add(int count);
double subtract(int count);
double multiply(int count);
double divide(int count);

void saveToFile(double a, double b, double c, double d, int count);

int main(){
    srand(time(NULL));

    int count[3] = {2048, 4096, 8192};                       //ile liczb dodajemy


    double timeA, timeS, timeM, timeD;                      //czasy wynikowe

    //pomiary czasow operacji   
    
    
    for(int i = 0; i<3; i++){

        timeA = add(count[i]);
        timeS = subtract(count[i]);
        timeM = multiply(count[i]);
        timeD = divide(count[i]);

        saveToFile(timeA, timeS, timeM, timeD, count[i]);
    }

    return 0;
}

std::chrono::high_resolution_clock::time_point timestamp(){
    return std::chrono::high_resolution_clock::now();
}


double time(std::chrono::high_resolution_clock::time_point p){
    std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> t = time - p;
    return t.count();
}

float add(float a, float b){
    float result;
    asm(
        "finit\n"
        "flds %1\n"
        "fadds %2\n"
        "fsts %0\n"
        :"=m" (result)
        :"m" (a),"m" (b)
        :"memory"
    );
    return result;
}

float subtract(float a, float b){
    float result;
    asm(
        "finit\n"
        "flds %1\n"
        "fsubs %2\n"
        "fsts %0\n"
        :"=m" (result)
        :"m" (a),"m" (b)
        :"memory"
    );
    return result;
}

float multiply(float a, float b){
    float result;
    asm(
        "finit\n"
        "flds %1\n"
        "fmuls %2\n"
        "fsts %0\n"
        :"=m" (result)
        :"m" (a),"m" (b)
        :"memory"
    );
    return result;
}
float divide(float a, float b){
    float result;
    asm(
        "finit\n"
        "flds %1\n"
        "fdivs %2\n"
        "fsts %0\n"
        :"=m" (result)
        :"m" (a),"m" (b)
        :"memory"
    );
    return result;
}

double add(int count){
    double totalTime = 0;
    double avgTime = 0;
    float arr [4] = {0,0,0,0};
    for(int i = 0; i<10; i++){
        for(int j = 0; j<count; j++){
            float array [4];
            for(int k = 0; k<4; k++){
                array[k] = rand();
                std::chrono::high_resolution_clock::time_point x = timestamp();
                arr[k] = add(array[k], arr[k]);
                double y = time(x);
                totalTime+= y;
            }       
        }
    }

    avgTime = totalTime/10;
    return avgTime;
}


double subtract(int count){
    double totalTime = 0;
    double avgTime = 0;
    float arr [4] = {0,0,0,0};
    for(int i = 0; i<10; i++){
        for(int j = 0; j<count; j++){
            float array[4];
            for(int k = 0; k<4; k++){
                array[k] = rand();
                std::chrono::high_resolution_clock::time_point x = timestamp();
                arr[k] = subtract(arr[k], array[k]);
                double y = time(x);
                totalTime+= y;
            }            
        }
    }

    avgTime = totalTime/10;
    return avgTime;
}

double multiply(int count){
    double totalTime = 0;
    double avgTime = 0;
    float arr [4] = {0,0,0,0};
    for(int i = 0; i<10; i++){
        for(int j = 0; j<count; j++){
            float array[4];
            for(int k = 0; k<4; k++){
                array[k] = rand();
                std::chrono::high_resolution_clock::time_point x = timestamp();
                arr[k] = multiply(arr[k], array[k]);
                double y = time(x);
                totalTime+= y;
            }            
        }
    }

    avgTime = totalTime/10;
    return avgTime;
}

double divide(int count){
    double totalTime = 0;
    double avgTime = 0;
    float arr [4] = {1,1,1,1};
    for(int i = 0; i<10; i++){
        for(int j = 0; j<count; j++){
            float array[4];
            for(int k = 0; k<4; k++){
                array[k] = rand();
                std::chrono::high_resolution_clock::time_point x = timestamp();
                arr[k] = divide(arr[k], array[k]);
                double y = time(x);
                totalTime+= y;
            }            
        }
    }

    avgTime = totalTime/10;
    return avgTime;
}

void saveToFile(double a, double b, double c, double d, int count){
    std::string filename = "result" + std::to_string(count) + ".txt";

    std::ofstream file(filename);

    file<<"Typ obliczen: SISD\n";
    file<<"Liczba liczb: "<<count<<"\n";
    file<<"Sredni czas [us]: \n";
    file<<"+ "<<a<<"\n";
    file<<"- "<<b<<"\n";
    file<<"* "<<c<<"\n";
    file<<"/ "<<d<<"\n";

    file.close();
}