#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <functional>


// the struct(object for the function to take)

struct datum {int start, stop; double sum;};

// some threading function - has to return void - in c++ it can recieve some object 
// thread safe, cannot refer to the same variable in memoery
void harm(datum& d) 
{
    d.sum = 0;
    for (long long int i = d.start+1; i< d.stop; i++)
        {
            d.sum += 1.0/i;
        }
}

double sum2 = 0;

void harm2(int start, int stop) 
{
    for (long long int i = start+1; i< stop; i++)
        {
            sum2 += 1.0/i;
        }
}

int main(int argc, char* argv[]) 
{
    long long int nthreads = 1, nterms = 5e8;
    for(int i = 0; i<argc; i++)
    {
        std::string arg = argv[i];
        if(arg=="-threads" && i+1< argc) nthreads = (long long int)std::stoi(argv[i+1]);
        if(arg=="-terms" && i+1<argc) nterms =(long long int)std::stod(argv[i+1]);
    }
    std::cerr << "nthreads=" << nthreads << " nterms= " << nterms << std::endl;
    std::vector< std::thread > threads(nthreads);
    std::vector< datum > data(nthreads);
    for(long long int i = 0; i < nthreads; i++)
    {
        data[i].start = i*nterms/nthreads;
        data[i].stop = (i+1)*nterms/nthreads;
    }
    for(long long int i=0;i<nthreads;i++)
    {
		threads[i]=std::thread(harm,std::ref(data[i]));
	}
	for(std::thread& thread : threads) thread.join();
	double sum=0;
	for(datum d : data) sum+=d.sum;
	std::cout << "sum=" << sum << std::endl;

    // Forced race condition method - This will basically be the same but now i would just not use some structure
    // instead refering to some shared varaible double sum. I dont know how to do that easy Parallel.For c# loop in c++
    bool race = true;  // turn on or off race conditions...
    if (race) {
        long long int nthreads2 = 1, nterms2 = 5e8;
        for(int i = 0; i<argc; i++)
        {
            std::string arg2 = argv[i];
            if(arg2=="-threads" && i+1< argc) nthreads2 = (long long int)std::stoi(argv[i+1]);
            if(arg2=="-terms" && i+1<argc) nterms2 =(long long int)std::stod(argv[i+1]);
        }
        std::cerr << "nthreads=" << nthreads2 << " nterms= " << nterms2 << std::endl;
        std::vector<std::thread> threads2;
        int chunk_size = nterms2 / nthreads2;

        for (int i = 0; i < nthreads2; ++i) {
            int start = i * chunk_size + 1;
            int end = (i == nthreads2 - 1) ? nthreads2 : (i + 1) * chunk_size;
            threads2.emplace_back(harm2, start, end);
        }
        for (auto& t : threads2) {
            t.join();
        }
        std::cout << "Sum (with race condition):" << sum2 << std::endl;
    }
    if(!race) {std::cout << "Race condition harm summation turned off" << std::endl;}
    return 0;


}