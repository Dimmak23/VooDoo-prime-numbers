/*
This code is solution for "Voodoo Primes challenge".
_______________________________________________________________________________
Voodoo Primes.

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
#include <sstream> 
#include <time.h>
#include <math.h>

// 
template <typename T>
void pOL(T word){
	std::cout << word;
}
// 
template <typename T, typename... Args>
void pOL(T first, Args... args){
	std::cout << first;
	pOL(args...);
}
//
template <typename T> inline
std::string tostring(T decimal){
    std::ostringstream os;
    os << decimal;
    return os.str();
}
//
int accurancy = 2500;

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
	std::string modeHeader = "\nEnter number or range here: ";
    std::string incorrect = "\nThis input is incorrect.\n";
    std::string comeAgain = "\nThat's all for now, run again.\n";
    //
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
		pOL(modeHeader);
		// read mode from user
		std::getline (std::cin, answer);
	}
    
    // Method print corresponding message about "correct" or "incorrect" input
	void validateDialog(){
		int i = 0;
		int j = 0;
		//
		while ( answer[j] != '\0' ){
			// increment when find every space
			if ((int)answer[j]==32){
				mode=false;
				i++;
			}
			// more than 1 space
			if (i > 1) approved=false;
			//
			if (i == 0)
				if (((int)answer[j]>=48)
				    && ((int)answer[j]<=57))
					number = number*10+((int)answer[j]-48);
				else if ((int)answer[j]!=32) approved=false;
			//
			if (i == 1)
				if (((int)answer[j]>=48)
				    && ((int)answer[j]<=57))
					rRange = rRange*10+((int)answer[j]-48);
				else if ((int)answer[j]!=32) approved=false;
			// jump to next character
			j++;
		}
		// Immidiately send error message in case wrong input
		if (!approved) pOL(incorrect);
	}
	
	// Destructor simply send message to user asking run program again 
	~storage(){
		pOL(comeAgain);
	}
};

/*
Derrived class numberResearcher contain:
private messages for user, container for collecting number;

protected ;

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
    std::string p1 = "\nCalculating prime divisors for given";
	
	// integer container for collected number from user
	unsigned long long int number;
	//
    std::vector<unsigned long long int> pVec;
    //
    clock_t time_new;
    //
    clock_t start_operate;

	// research method with bool return shared with range research class
	protected:
	//
	std::string timeCalc = "\nTime spend on calculations: ";
	std::string timeSec = " seconds.\n";
    std::string p2 = " number cause time limit failure.\n";
    std::string primeLimit = p1 + p2;
	// bool container, true - time error, false - everything fine
	bool time_p_failure;

	// method recieve number for research and return "true" - if number lab
	void getPrimes(unsigned long long int &point){
		// firsts numbers in the prime container
		pVec.push_back(2);
		//
		start_operate = clock();
		// calculate prime numbers with odd divisors
		for (unsigned long long int i = 3; (( i*i <= point ) && !time_p_failure ); ){
			//
			bool result  = true;
			// first divise number with prime that alreay in the list
			for (std::vector<unsigned long long int>::iterator it = pVec.begin();
			     ( ( it != pVec.end() ) && ( (*it)*(*it) <= i ) && result ); it++){
			     		// if something left from division this not prime
			     		if ( !( i % (*it) ) ) result = false;
			}

			// puch to vector only primes
			if ( result ) pVec.push_back(i);
			//
			time_new = clock() - start_operate;
			//
			if ( time_new*1.0/CLOCKS_PER_SEC > 1 ){
				point = i*i;
				time_p_failure = true;		
			}
			//
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
		//
	    return true;
	}
	
	/*
	bool checkVoodoo(unsigned long long int a){
		//
		int chk = 0;
		//
		int count = 0;
		//
		unsigned long long int c = a;
		//
		while (c > 0){
			chk++;
			c /= 10;
		}
		//
		chk = pow(10, chk);
		//
		for ( double b = 1/(double)a; count < accurancy; count++){
			// check group of digits
			if ( a == (unsigned long long int)(chk*b) ) return true;
			// cut one digit
			b = 10*b - (unsigned long long int)(10*b);
		}
		//
		return false;
	}
	*/

	//
	bool checkVoodoo(unsigned long long int input){
		//
	    int dividend = 1;
	    //
	    int count = 0;
	    //
	    int digits = 0;
	    //
		unsigned long long int temp_number = input;
	    //
	    std::string ans;
		//
	    std::string temp_string;
	    //
	    std::string initial = tostring(input);

	    while (temp_number > 0){
			digits++;
			temp_number /= 10;
		}

	    ans += tostring(dividend/input);
		count = ans.size();
	    ans += '.';

	    while ( count < accurancy ){
	    	
			dividend = (dividend % input)*10;
			temp_string = tostring(dividend/input);
			ans += temp_string;
			count += temp_string.size();

	        if ( ans.find(initial) != std::string::npos ) return true;
			
			if ( (count/(digits) > 1 ) )
				ans.erase(ans.begin(),ans.end()-digits);
	    }
	    return false;
	}


	// Main program need this methods
	public:
	// Method collect number from user
	void setNumber(unsigned long long int x){
		number = x;
	}

	// Method sends result to user
	void closeDialog(clock_t start_calc){
		//
		getPrimes(number);
		//
		if (time_p_failure) pOL(primeLimit);
		else {
			//
			if (checkPrime(number)){
				//
				if (checkVoodoo(number)) pOL(voodoo);
				//
				else pOL(notV);
			}
			//
			else pOL(notPrime);
		}

		time_new = clock() - start_calc;
			
		pOL(timeCalc,time_new*1.0/CLOCKS_PER_SEC,timeSec);
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
    std::string timeLimit = "\nResearch for given range produce time limit failure.";
    std::string voodooCorre = "\n\nAll voodoo prime numbers in the corrected range [";
    std::string back = "] are:\n\n[\n";
    std::string notVRange = "\nNot a single voodoo prime in the given range: ";
    std::string voodooQun = "].\n\nQuantity of voodoo prime numbers: ";
    std::string q1 = "\nCalculating prime divisors for given";
    std::string p2 = " range cause time limit failure.\n";
    std::string primeLimit = q1 + p2;

	// integer container for begin of range
	unsigned long long int lRange;
	// integer container for end of range
	unsigned long long int rRange;
	// integer vector container for all lab numbers in the range
	std::vector<unsigned long long int> voodoo_primes;
    //
    clock_t time_new;
    //
    clock_t start_operate;
	// bool container, true - time error, false - everything fine
	bool time_failure;

	// Method called labCheck() and keep lab number
	void operate(unsigned long long int start, unsigned long long int &end){
		//
		getPrimes(end);
		//
		if (start == 1) start++;
		//
		start_operate = clock();
		//
		for(unsigned long long int next = start; ( (next <= end) && !time_failure ); next++){
			//
			time_new = clock() - start_operate;
			//
			if ( time_new*1.0/CLOCKS_PER_SEC > 60 ){
				//
				end = next-1;
				time_failure = true;	
			}

			if ( checkPrime(next) && checkVoodoo(next) )
				voodoo_primes.push_back(next);
		}
	}

	// Main program need this methods
	public:
	// Method collect range from user
	void setRange(unsigned long long int x, unsigned long long int y){
		lRange = x;
		rRange = y;
	}
	// Method sends result to user
	void closeDialog(clock_t start_calc){
		// temporary integer container
		int i = 0;
		// research in the range starts here
		operate(lRange, rRange);
		// send empty result vector to user
		if (voodoo_primes.empty()){
			pOL(notVRange,'[',lRange,", ",rRange,"].\n");
		}
		else {
			
			if (time_p_failure) pOL(primeLimit);
			
			if (time_failure) pOL(timeLimit);
			
			if (time_p_failure || time_failure)
				pOL(voodooCorre, lRange, ", ", rRange, back);
			else pOL(voodooRange, lRange, ", ", rRange, back);
			// printing by vector iterator in the for-loop
			for (std::vector<unsigned long long int>::iterator
			     it = voodoo_primes.begin(); it!=voodoo_primes.end();
			     it++){
				pOL(*it, '\t');
				if(++i==7){
					pOL('\n');
					i=0;
				}
			}
			if (i) pOL('\n');
			
			pOL(voodooQun, voodoo_primes.size(), ".\n");

			time_new = clock() - start_calc;

			pOL(timeCalc,time_new*1.0/CLOCKS_PER_SEC,timeSec);
		}
	}
};

// Main program starting point
int main() {

	// declaring clock variable
	clock_t calc_t;
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
		numberResearcher *check = new numberResearcher;
		// Initiliazing collecting number from user 
		check -> setNumber(entry -> number);
		// start clock
		calc_t = clock();
		// Closing dialog with user 
		check -> closeDialog(calc_t);
	}

	// range of the numbers mode
	if ( (entry -> approved) && !(entry -> mode) )
	{
		// Initiliazing pointer to rangeResearcher class
		rangeResearcher *check = new rangeResearcher;
		// Initiliazing collecting range from user
		check -> setRange(entry -> number, entry -> rRange);
		// start clock
		calc_t = clock();
		// Closing dialog with user 
		check -> closeDialog(calc_t);
	}
	
	// deleting base class pointer
	delete entry;

    return 0;
}