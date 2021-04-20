#include "converter.h"

using namespace std;

std::string converter::decimalToBinary(int number, int digitCapacity)
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

int converter::binaryToDecimal(std::string binary)
{
	int decimal = 0;
	for (int i = 0; i < binary.length(); i++) {
		if (binary[i] == '1') {
			decimal += pow(2, binary.length() - i-1);
		}
	}
	return decimal;
}
