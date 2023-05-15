#include<stdio.h>
#include<xmmintrin.h>
#include<time.h>
#include<iostream>
#include<unistd.h>
#include<fstream>
#include<chrono>
#include<string>

std::chrono::high_resolution_clock::time_point timestamp();
double time(std::chrono::high_resolution_clock::time_point p);

__m128 add(__m128 a, __m128 b);
__m128 subtract(__m128 a, __m128 b);
__m128 multiply(__m128 a, __m128 b);
__m128 divide(__m128 a, __m128 b);

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


__m128 add(__m128 a, __m128 b){
    __m128 result;

    asm(
        "movups %1, %%xmm0\n"
        "movups %2, %%xmm1\n"
        "addps %%xmm1, %%xmm0\n"
        "movups %%xmm0 , %0"
        :"=g" (result)
        :"g" (a), "g" (b)
        :"xmm0", "xmm1", "memory"
    );

    return result;
}

__m128 subtract(__m128 a, __m128 b){
        __m128 result;

    asm(
        "movups %1, %%xmm0\n"
        "movups %2, %%xmm1\n"
        "subps %%xmm1, %%xmm0\n"
        "movups %%xmm0 , %0"
        :"=g" (result)
        :"g" (a), "g" (b)
        :"xmm0", "xmm1", "memory"
    );

    return result;
}

__m128 multiply(__m128 a, __m128 b){
        __m128 result;

    asm(
        "movups %1, %%xmm0\n"
        "movups %2, %%xmm1\n"
        "mulps %%xmm1, %%xmm0\n"
        "movups %%xmm0 , %0"
        :"=g" (result)
        :"g" (a), "g" (b)
        :"xmm0", "xmm1", "memory"
    );

    return result;
}

__m128 divide(__m128 a, __m128 b){
        __m128 result;

    asm(
        "movups %1, %%xmm0\n"
        "movups %2, %%xmm1\n"
        "divps %%xmm1, %%xmm0\n"
        "movups %%xmm0 , %0"
        :"=g" (result)
        :"g" (a), "g" (b)
        :"xmm0", "xmm1", "memory"
    );

    return result;
}

double add(int count){
    double totalTime = 0;
    double avgTime;
    __m128 sum = _mm_set_ps(0,0,0,0);
    for(int i = 0; i<10; i++){
        for(int j = 0; j<count; j++){
            float a = rand();
            float b = rand();
            float c = rand();
            float d = rand();
            __m128 vector = _mm_set_ps(a,b,c,d);
            
            std::chrono::high_resolution_clock::time_point x = timestamp();
            sum = add(vector,sum);
            double y = time(x);
            totalTime += y;
        }
    }

    avgTime = (double)totalTime/10;
    return avgTime;
}

double subtract(int count){
    double totalTime = 0;
    double avgTime;
    __m128 dif = _mm_set_ps(0,0,0,0);
    for(int i = 0; i<10; i++){
        for(int j = 0; j<count; j++){
            float a = rand();
            float b = rand();
            float c = rand();
            float d = rand();
            __m128 vector = _mm_set_ps(a,b,c,d);
            
            std::chrono::high_resolution_clock::time_point x = timestamp();
            dif = subtract(dif,vector);
            double y = time(x);
            totalTime += y;
        }
    }

    avgTime = (double)totalTime/10;
    return avgTime;
}

double multiply(int count){
    double totalTime = 0;
    double avgTime;
    __m128 prod = _mm_set_ps(1,1,1,1);
    for(int i = 0; i<10; i++){
        for(int j = 0; j<count; j++){
            float a = rand();
            float b = rand();
            float c = rand();
            float d = rand();
            __m128 vector = _mm_set_ps(a,b,c,d);
            
            std::chrono::high_resolution_clock::time_point x = timestamp();
            prod = multiply(vector,prod);
            double y = time(x);
            totalTime += y;
        }
    }

    avgTime = (double)totalTime/10;
    return avgTime;
}

double divide(int count){
    double totalTime = 0;
    double avgTime;
    __m128 quot = _mm_set_ps(1,1,1,1);
    for(int i = 0; i<10; i++){
        for(int j = 0; j<count; j++){
            float a = rand();
            float b = rand();
            float c = rand();
            float d = rand();
            __m128 vector = _mm_set_ps(a,b,c,d);
            
            std::chrono::high_resolution_clock::time_point x = timestamp();
            quot = divide(vector,quot);
            double y = time(x);
            totalTime += y;
        }
    }

    avgTime = (double)totalTime/10;
    return avgTime;
}


void saveToFile(double a, double b, double c, double d, int count){
    std::string filename = "result" + std::to_string(count) + ".txt";

    std::ofstream file(filename);

    file<<"Typ obliczen: SIMD\n";
    file<<"Liczba liczb: "<<count<<"\n";
    file<<"Sredni czas [us]: \n";
    file<<"+ "<<a<<"\n";
    file<<"- "<<b<<"\n";
    file<<"* "<<c<<"\n";
    file<<"/ "<<d<<"\n";

    file.close();
}
