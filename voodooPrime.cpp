/*
This code is solution for "Voodoo Primes challenge".
_______________________________________________________________________________
Voodoo Primes

A Voodoo prime is a prime number whose reciprocal (in decimal) has the same
number in its digits. For example, 7 is a voodoo prime because its reciprocal
1/7=0.14285714285 contains 7.

Examples:
Input: 3
Output: true (1/3=0.33333333333 contains 3)

Input: 11
Output: false (1/11=0.0909090909 doesn't contain 11)

Write a program to check if the user input is a Voodoo prime or not.

Bonus: Print all the Voodoo primes in a given range.
_______________________________________________________________________________
*/
#include <iostream>
#include <vector>
#include <string>
#include <math.h> 
#include <time.h>

// template function for simple message output
template <class messageType>
void pOL(messageType message){
	std::cout << message;
}

/*
Base class "storage" has private: messages for display, and private container
for answer from user;

public containers, methods and destructor: destructor simply send "come again"
message, boolean "approved" for validating input from user, methods for send
messages input validity or result, boolean "mode" for initilizing mode of
program - number research or range research, also created a virtual empty
methods for overloading it in the derrived class and using that overloaded
methods by the base class pointer to derrived class.
*/
class storage{

    // There is no need to share this containers and methods with derrived
    // class and main program
    private:
    // messages represent as strings, they kept private because doesn't uses
    // in other parts of programm
	std::string modeHeader = "\nEnter number or range: ";
    std::string incorrect = "\nThis input is incorrect.\n";
    std::string comeAgain = "\nThat's all for now, run again.\n";
    
    //
	std::string response;
	std::string answer;


	// Main program need this containers and methods
	public:
	// true - for number, false - for range
	bool mode = true;
	// approved = true - correct input, false - incorrect input
	bool approved = true;
	//
	unsigned long long int number;
	//
	unsigned long long int rRange;

	// Method that show to user options of the program
	void openDialog(){
		// Move to dialog header additional messages
		//modeHeader += "\n\n(s/S) - for varifing single number";
		//modeHeader += " being lab,";
		//modeHeader += "\n(r/R) - for showing all lab numbers";
		//modeHeader += " in the given range.\n\n";
		// output message for user
		pOL(modeHeader);
		// read mode from user
		std::getline (std::cin, answer);
	}
    
    // Method print corresponding message about "correct" or "incorrect" input
	void validateDialog(){
		int i = 0;
		int j = 0;
		mode = true;
		approved = true;

		while ( answer[j] != '\0' ){
			
			// increment when find every space
			if ( (unsigned long long int)answer[j] == 32 ){
				mode = false;
				i++;
			}
			
			// more than 1 space
			if (i > 1) approved = false;

			if (i == 0)
				if ( ( (unsigned long long int)answer[j] >= 48 ) && ( (unsigned long long int)answer[j] <= 57 ) )
					number = number*10 + ((unsigned long long int)answer[j]-48);

			if (i == 1)
				if ( ( (unsigned long long int)answer[j] >= 48 ) && ( (unsigned long long int)answer[j] <= 57 ) ){
					rRange = rRange*10 + ((unsigned long long int)answer[j]-48);
				}

			j++;
		}
		// Immidiately send error message in case wrong input
		if (!approved) pOL(incorrect);
	}
	
	// Prepared virtual empty method for collecting number for research
	virtual void setNumber(unsigned long long int x){}
	// Prepared virtual empty method for collecting range for research
	virtual void setRange(unsigned long long int x, unsigned long long int y){}
	// Virtual empty method for sening result message if base class pointer
	// will initilize it - because of keyword "virtual" derrived class overload
	// method closeDialog() will be used	
	virtual void closeDialog(){}

	// Destructor simply send message to user asking run program again 
	~storage(){
		pOL(comeAgain);
	}
};

/*
Derrived class numberResearcher contain:
private messages for user, container for collecting number;

protected method labCheck() does actual research of single number;

public methods such as getNumber() for collecting number, closeDialog() for
sending result to user and bunch of empty methods openDialog() and
validateDialog() that accessible from main program. Some methods empty because
they is overloads base non-virtual methods so main program will call base
methods.
*/
class numberResearcher : public storage
{
    // There is no need to share this containers with derrived class
    // and main program
    private:
    // messages represent as strings for number research dialogs
    std::string enterNumber = "\nEnter number for research: ";
    std::string voodoo = "\nYou enter a voodoo number.\n";
    std::string notV = "\nYou enter just prime, not voodoo.\n";
    std::string notPrime = "\nYou enter not a prime number.\n";
	
	// integer container for collected number from user
	unsigned long long int number;
    //
    std::vector<unsigned long long int> pVec;
    //
    clock_t time_new;
    //
    clock_t start_operate;
	// bool container, true - time error, false - everything fine
	bool time_failure = false;

	// research method with bool return shared with range research class
	protected:
	// method recieve number for research and return "true" - if number lab
	void getPrimes(unsigned long long int &point){

		// temporary container
		unsigned long long int y = point/11;
		// first number in the container
		pVec.push_back(2);
		pVec.push_back(3);
		pVec.push_back(5);
		pVec.push_back(7);
		pVec.push_back(11);

		start_operate = clock();

		// calculate prime numbers with odd divisors
		for (unsigned long long int i = 11; (( i <= y ) && !time_failure ); ){

			bool result  = true;

			// first divise number with prime that alreay in the list
			for (std::vector<unsigned long long int>::iterator it = pVec.begin();
			     ( ( it != pVec.end() ) && ( *it <= (i/2) ) && result ); it++){
			     		// if something left from division this not prime
			     		if ( !( i % (*it) ) ) result = false;
			}
			
			// then find divisors from other odd numbers
			for (unsigned long long int j = pVec.back(); ( ( j <= (1+i/2) ) && result ); ){
				// if something left from division this not prime
				if ( !( i % j ) ) result = false;
				// to the next odd number
				j += 2;
			}
			// puch to vector only primes
			if ( result ) pVec.push_back(i);

			time_new = clock() - start_operate;
			if ( time_new*1.0/CLOCKS_PER_SEC > 6 ){
				point = i;
				time_failure = true;		
			}
			i += 2;
		}
	}

	// Method check if number is prime
	bool checkPrime(unsigned long long int x){
	    //
		for (std::vector<unsigned long long int>::iterator it = pVec.begin();
		     it != pVec.end(); it++){
			//
			if (x == (*it)) return true;
			if ( ( x > (*it) ) && !(x % (*it)) ) return false;
		}
	    return true;
	}

	//
	bool checkVoodoo(unsigned long long int a){
		int accurancy = 15;
		//
		int chk = 0;
		//
		unsigned long long int c = a;
		
		while (c > 0){
			chk++;
			c /= 10;
		}
		//
		chk = pow(10, chk);
		//
		for ( double b = 1/(double)a; accurancy > 0; accurancy--){

			if ( a == (unsigned long long int)(chk*b) )
			    return true; // check group of digits
			

			b = 10*b - (unsigned long long int)(10*b);//cut one digit
		}

		return false;
	}

	// Main program need this methods
	public:
	// Empty method for calling bace class openDialog()
	void openDialog(){}
	// Empty method for calling bace class validateInput()
	void validateDialog(){}
	// Method collect number from user
	void setNumber(unsigned long long int x){
		// Send simple message to user
		//pOL(enterNumber);
		//std::cin >> number;
		number = x;
	}

	void operate(){}

	// Prepared virtual empty method for collecting range for research
	virtual void setRange(){}
	// Method sends result to user
	void closeDialog(){
		//
		getPrimes(number);
		//
		if (checkPrime(number)){
			if (checkVoodoo(number)) pOL(voodoo);
			else pOL(notV);
		}
		else pOL(notPrime);
	}
};

/*
Derrived class rangeResearcher contain:
private method for operate with inherited labCheck(), messages for user,
containers for collecting range and vector for lab numbers in the range;

protected method labCheck() does actual research of single number;

public methods such as getNumber() for collecting number, closeDialog() for
sending result to user and bunch of empty methods openDialog() and
validateDialog() that accessible from main program. Some methods empty because
they is overloads base non-virtual methods so main program will call base
methods.
*/
class rangeResearcher : public numberResearcher
{
    // There is no need to share this containers and methods with derrived
    // class and main program
	private:
	// messages represent as strings for range research dialogs
    std::string enterLrange = "\nEnter start number in the range: ";
    std::string enterRrange = "\nEnter end number in the range: ";
    std::string voodooRange = "\nAll voodoo prime numbers in the given range [";
    std::string back = "] are:\n\n[\n";
    std::string notVRange = "\nNot a single voodoo prime in the given range((\n";

	// integer container for begin of range
	unsigned long long int lRange;
	// integer container for end of range
	unsigned long long int rRange;
	// integer vector container for all lab numbers in the range
	std::vector<int> voodoo_primes;
    //
    clock_t time_new;
    //
    clock_t start_operate;
	// bool container, true - time error, false - everything fine
	bool time_failure = false;

	// Method called labCheck() and keep lab number
	void operate(unsigned long long int start, unsigned long long int &end){
		//
		getPrimes(end);
		//
		start_operate = clock();
		for(unsigned long long int next = start; ( (next <= end) && !time_failure ); next++){
			time_new = clock() - start_operate;
			if ( time_new*1.0/CLOCKS_PER_SEC > 1 ){
				end = next-1;
				time_failure = true;		
			}
			if ( checkVoodoo(next) && checkPrime(next) )
				voodoo_primes.push_back(next);
		}
	}

	// Main program need this methods
	public:
	// Empty method for calling bace class openDialog()
	void openDialog(){}
	// Empty method for calling bace class validateInput()
	void validateDialog(){}
	// Method collect range from user
	void setRange(unsigned long long int x, unsigned long long int y){
		//pOL(enterLrange);
		//std::cin >> lRange;
		//pOL(enterRrange);
		//std::cin >> rRange;
		lRange = x;
		rRange = y;
	}
	// Method sends result to user
	void closeDialog(){
		// temporary integer container
		int i = 0;
		// research in the range starts here
		operate(lRange, rRange);
		// send empty result vector to user
		if (voodoo_primes.empty()){
			pOL(notVRange);
			pOL(lRange);
			pOL(',');
			pOL(' ');
			pOL(rRange);
		}
		else {
			// send find any lab number message to user
			pOL(voodooRange);
			pOL(lRange);
			pOL(',');
			pOL(' ');
			pOL(rRange);
			pOL(back);
			// printing by vector iterator in the for-loop
			for (std::vector<int>::iterator it = voodoo_primes.begin();
			     it!=voodoo_primes.end(); it++){
				pOL(*it);
				pOL('\t');
				if(++i==6){
					pOL('\n');
					i=0;
				}
			}
			if (i) pOL('\n');
			pOL("].\n");
		}
	}
};

// Main program starting point
int main() {

	// declaring clock variable
	clock_t t;
	// Initiliazing pointer to base class
	storage *entry = new storage;
	// Initiliazing dialog with user
	entry -> openDialog();
	// Initiliazing analisis of input from user
	entry -> validateDialog();

	// single-number mode
	if ( (entry -> approved) && (entry -> mode) )
	{
		// Initiliazing pointer to numberResearcher class
		storage *check = new numberResearcher;
		//
		unsigned long long int x = entry -> number;
		// Initiliazing collecting number from user 
		check -> setNumber(x);
		// start clock
		t = clock();
		// Closing dialog with user 
		check -> closeDialog();
	}

	// range of the numbers mode
	if ( (entry -> approved) && !(entry -> mode) )
	{
		// Initiliazing pointer to rangeResearcher class
		storage *check = new rangeResearcher;
		//
		unsigned long long int x = entry -> number;
		//
		unsigned long long int y = entry -> rRange;
		// Initiliazing collecting range from user
		check -> setRange(x, y);
		// start clock
		t = clock();
		// Closing dialog with user 
		check -> closeDialog();
	}

	// deleting base class pointer
	delete entry;

	// getting time mesuare
	t = clock() - t;

	// send elapsed time for calculating to user
	pOL("\nTime spend: ");
	pOL(t*1.0/CLOCKS_PER_SEC);
	pOL(" seconds.\n");

    return 0;
}