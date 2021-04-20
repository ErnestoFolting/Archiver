#include "converter.h"

using namespace std;

std::string converter::bin(int number, int digitCapacity)
{
	string binary;
	if(number==0) binary="0";
    while(number > 0){
        binary=to_string(number % 2) + binary;
        number/=2;
    }
    int len = binary.length();
    while (len < digitCapacity) {
        binary = "0" + binary;
    	len++;
    }
    return binary;
}

int converter::binToDec(std::string bin)
{
	int dec = 0;
	for (int i = 0; i < bin.length(); i++) {
		if (bin[i] == '1') {
			dec += pow(2, bin.length() - i-1);
		}
	}
	return dec;
}
