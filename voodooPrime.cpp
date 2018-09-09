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
//#include <math.h>

template <typename T>
void pOL(T word){
	std::cout << word;
}
 
template <typename T, typename... Args>
void pOL(T first, Args... args){
	std::cout << first;
	pOL(args...);
}

template <typename T> inline
std::string tostring(T decimal){
    std::ostringstream os;
    os << decimal;
    return os.str();
}

int accurancy = 2500;

class storage {

    private:
	std::string modeHeader = "\nEnter number or range here: ";
    std::string incorrect = "\nThis input is incorrect.\n";
    std::string comeAgain = "\nThat's all for now, run again.\n";

	std::string answer;

	public:
	bool mode = true;
	bool approved = true;
	unsigned long long int number;
	unsigned long long int rRange;

	void openDialog(){
		pOL(modeHeader);
		std::getline (std::cin, answer);
	}
    
	void validateDialog(){
		int i = 0;
		int j = 0;
		
		while ( answer[j] != '\0' ){
			if ((int)answer[j]==32){
				mode=false;
				i++;
			}
			if (i > 1) approved=false;

			if (i == 0)
				if (((int)answer[j]>=48)
				    && ((int)answer[j]<=57))
					number = number*10+((int)answer[j]-48);
				else if ((int)answer[j]!=32) approved=false;

			if (i == 1)
				if (((int)answer[j]>=48)
				    && ((int)answer[j]<=57))
					rRange = rRange*10+((int)answer[j]-48);
				else if ((int)answer[j]!=32) approved=false;
			
			j++;
		}
		
		if (!approved) pOL(incorrect);
	}
	
	~storage(){
		pOL(comeAgain);
	}
};

class numberResearcher : public storage {
    private:
    std::string enterNumber = "\nEnter number for research: ";
    std::string voodoo = "\nYou enter a voodoo number.\n";
    std::string notV = "\nYou enter just prime, not voodoo.\n";
    std::string notPrime = "\nYou enter not a prime number.\n";
    std::string p1 = "\nCalculating prime divisors for given";
	
	unsigned long long int number;
    std::vector<unsigned long long int> pVec;
    clock_t time_new;
    clock_t start_operate;

	protected:
	std::string timeCalc = "\nTime spend on calculations: ";
	std::string timeSec = " seconds.\n";
    std::string p2 = " number cause time limit failure.\n";
    std::string primeLimit = p1 + p2;

	bool time_p_failure;

	void getPrimes(unsigned long long int &point){
		pVec.push_back(2);
		start_operate = clock();

		for (unsigned long long int i = 3; (( i*i <= point ) && !time_p_failure ); ){
			bool result  = true;

			for (std::vector<unsigned long long int>::iterator it = pVec.begin();
			     ( ( it != pVec.end() ) && ( (*it)*(*it) <= i ) && result ); it++)
			     		if ( !( i % (*it) ) ) result = false;

			if ( result ) pVec.push_back(i);

			time_new = clock() - start_operate;
			if ( time_new*1.0/CLOCKS_PER_SEC > 1 ){
				point = i*i;
				time_p_failure = true;		
			}
			i += 2;
		}
	}

	bool checkPrime(unsigned long long int x){
		for (std::vector<unsigned long long int>::iterator it = pVec.begin();
		     it != pVec.end(); it++){

			if (x == (*it)) return true;
			if ( ( x > (*it) ) && !(x % (*it)) ) return false;
		}
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

	bool checkVoodoo(unsigned long long int input){
	    int dividend = 1;
	    int count = 0;
	    int digits = 0;
		unsigned long long int temp_number = input;
	    std::string ans;
	    std::string temp_string;
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

	        if ( ans.find(initial) != std::string::npos )
	        	return true;
			
			if ( (count/(digits) > 1 ) )
				ans.erase(ans.begin(),ans.end()-digits);
	    }
	    return false;
	}

	public:
	void setNumber(unsigned long long int x){
		number = x;
	}

	void closeDialog(clock_t start_calc){
		getPrimes(number);
		if (time_p_failure) pOL(primeLimit);
		else {
			if (checkPrime(number)){
				if (checkVoodoo(number)) pOL(voodoo);
				else pOL(notV);
			}
			else pOL(notPrime);
		}

		time_new = clock() - start_calc;
		pOL(timeCalc,time_new*1.0/CLOCKS_PER_SEC,timeSec);
	}
};

class rangeResearcher : public numberResearcher {
	private:
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

	unsigned long long int lRange;
	unsigned long long int rRange;
	std::vector<unsigned long long int> voodoo_primes;
    clock_t time_new;
    clock_t start_operate;
	bool time_failure;

	void operate(unsigned long long int start, unsigned long long int &end){
		getPrimes(end);
		if (start == 1) start++;
		start_operate = clock();

		for(unsigned long long int next = start; ( (next <= end) && !time_failure ); next++){
			time_new = clock() - start_operate;
			if ( time_new*1.0/CLOCKS_PER_SEC > 3 ){
				end = next-1;
				time_failure = true;	
			}

			if ( checkPrime(next) && checkVoodoo(next) )
				voodoo_primes.push_back(next);
		}
	}

	public:
	void setRange(unsigned long long int x, unsigned long long int y){
		lRange = x;
		rRange = y;
	}
	void closeDialog(clock_t start_calc){
		int i = 0;
		operate(lRange, rRange);
		if (voodoo_primes.empty()){
			pOL(notVRange,'[',lRange,", ",rRange,"].\n");
		}
		else {			
			if (time_p_failure) pOL(primeLimit);
			if (time_failure) pOL(timeLimit);
			if (time_p_failure || time_failure)
				pOL(voodooCorre, lRange, ", ", rRange, back);
			else pOL(voodooRange, lRange, ", ", rRange, back);
			
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

int main() {

	clock_t calc_t;

	storage *entry = new storage;

	entry -> openDialog();

	entry -> validateDialog();

	if ( (entry -> approved) && (entry -> mode) )
	{
		numberResearcher *check = new numberResearcher;

		check -> setNumber(entry -> number);

		calc_t = clock();

		check -> closeDialog(calc_t);
	}

	if ( (entry -> approved) && !(entry -> mode) )
	{
		rangeResearcher *check = new rangeResearcher;

		check -> setRange(entry -> number, entry -> rRange);

		calc_t = clock();

		check -> closeDialog(calc_t);
	}

	delete entry;

    return 0;
}