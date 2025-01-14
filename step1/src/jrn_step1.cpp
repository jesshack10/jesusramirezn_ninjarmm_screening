// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

//Job Abstract Class
class Job {
    public:
    Job(){}
    virtual std::string getName() = 0;
    virtual std::string getDescription() = 0;
    virtual int getRequiredHours() = 0;
    virtual void DoWork() = 0;
    virtual ~Job(){};
    
    protected:
    std::string m_name{"Job"};
    std::string m_description{"This is my Job"};
    int m_requiredHours{8};
};

//Programmer Job's child sub class
class Programmer: public Job {
    
    public:
    Programmer(){
        m_name = "Programmer";
        m_description = " doing my Programmer Job";
        m_requiredHours = 8;
    }
    ~Programmer(){}
    
    std::string getName()  {return m_name;}
    std::string getDescription()  {return m_description;}
    int getRequiredHours()  {return m_requiredHours;}
    void DoWork()  {
        std::cout<<"My work involves" + m_description;
    }

};

//Pilot Job's child sub class
class Pilot: public Job {
    
    public:
    Pilot(){
        m_name = "Pilot";
        m_description = " doing my Pilot Job";
        m_requiredHours = 16;
    }
    ~Pilot(){}
    
    std::string getName() {return m_name;}
    std::string getDescription() {return m_description;}
    int getRequiredHours() {return m_requiredHours;}
    void DoWork() {
       std::cout<<"My work involves" + m_description;
    }
};

int ContainsTheString(const std::function<int(std::string)>& testFunction, const std::vector<std::string>& strList){
    int matchingStrCount = 0;
    
    for_each(strList.begin(), strList.end(),[&](std::string word){
        if(testFunction(word))
            ++matchingStrCount;
    });
    
    return matchingStrCount;
}
/*
* Variadic template
*/
template <typename T, typename ... Args> 
T SumElements(T first, Args... args){
    first = (first + ... + args);
    return first ;
}

/*
* Unit Testing template
*/
template <typename T> void Test(T expected, T current, std::string ctx = ""){
    std::cout<<ctx<<std::endl;
    
    if(expected == current){
        std::cout<<"\t***Execution PASS"<<std::endl;
    } else {
        std::cout<<"\t***Execution FAIL"<<std::endl;
    }
}

int main() {
    /*
    * This whole file can be executed properly at:
    * https://onlinegdb.com/D7Jfq7LHN
    * Flags for C++ 17 MUST BE activated. -std=c++17
    * settings -> extra compiler flags -> write -std=c++17 ->OK
    */
    Job* job1 = new Programmer();
    Job* job2 = new Pilot();
    std::vector<Job*> jobs {job1, job2};
    
    for(auto job : jobs) {
        std::cout<<"My name is "<<job->getName()<<", I work "<< job->getRequiredHours()<<" hours daily";
        std::cout<<"\t"; job->getDescription();
        std::cout<<"\n\t"; job->DoWork();
        std::cout<<std::endl;
    }
    
    std::for_each(jobs.begin(), jobs.end(), [](Job* p){delete p;});
    
    /*
    * Create a function that will take a vector of strings and a test function, 
    * It should return how many items in the collection matched the test. 
    * Then print out the result.
    */
    auto theStrings = std::vector<std::string> { "one", "two",  "test", "test", "test"};
	auto count = ContainsTheString([](const std::string& tested) { return tested == "test";}, theStrings);
	std::cout<<"There were "<<count<<" matches."<<std::endl;
	
	/*
	* Variadic function examples
	*/
	std::cout<<"Integers:"<<SumElements<int>(1,2,3,4,5)<<std::endl;
	std::cout<<"Floats:"<<SumElements<float>(3.5,4.2,5.9,6.1)<<std::endl;
	std::cout<<"Strings:"<<SumElements<std::string>("Hello ", "I ", "am ", "a ", "programmer.")<<std::endl;
	
	/*
	* Unit Tests
	*/
	std::cout<<"\n===Unit Tests===\n";
	
	//Classes
	Job* testJob = new Programmer();
	Test(std::string("Programmer"), testJob->getName(), "Testing programmers default initialization");
	Test(8, testJob->getRequiredHours());
	Test(std::string(" doing my Programmer Job"), testJob->getDescription());
	delete testJob;
	testJob = new Pilot();
	Test(std::string("Pilot"), testJob->getName(), "Testing pilot default initialization");
	Test(16, testJob->getRequiredHours());
	Test(std::string(" doing my Pilot Job"), testJob->getDescription());
	delete testJob;
	
	//ContainsTheString function
	Test(3, ContainsTheString([](const std::string& tested) { return tested == "test";}, theStrings), "Contains 3 matches");
	Test(1, ContainsTheString([](const std::string& tested) { return tested == "one";}, theStrings), "Contains 1 match");
	
	
	//Variadic template
	Test(10 , SumElements<int>(5,5), "Sum of Integers");
	Test(22.4 , SumElements<double>(5,7.4,10), "Sum of Doubles");
	Test(std::string("Hi I am Jesus") , SumElements<std::string>("Hi"," I am", " Jesus"), std::string("Sum of Strings"));
	
    return 0;
}