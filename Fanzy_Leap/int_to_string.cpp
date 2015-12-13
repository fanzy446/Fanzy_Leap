#include "int_to_string.h"

int int_power(int base, int exp);

std::string int_to_string(int num)
{
	bool negative = false;
	if ( num < 0 )
	{
		negative = true;
		num = -num;
	}

	int bitNum = 1;
	for ( int i = num; i > 9; i/=10 )
		bitNum++;

	std::vector<int> eachNum;
	for ( int i = bitNum, temp = num; i > 0; i-- )
	{
		int highBit = int(temp/int_power(10, (i-1)));
		eachNum.push_back(highBit);
		temp-=(highBit*int_power(10, (i-1)));
	}

	std::string str;
	if ( negative == true )
		str = "-";
	for ( std::vector<int>::iterator pTemp = eachNum.begin(); pTemp != eachNum.end(); pTemp++ )
	{
		switch ( *pTemp )
		{
		case 0:
			str+="0";
			break;
		case 1:
			str+="1";
			break;
		case 2:
			str+="2";
			break;
		case 3:
			str+="3";
			break;
		case 4:
			str+="4";
			break;
		case 5:
			str+="5";
			break;
		case 6:
			str+="6";
			break;
		case 7:
			str+="7";
			break;
		case 8:
			str+="8";
			break;
		case 9:
			str+="9";
			break;
		default:
			break;
		}
	}
	return str;
}

int int_power(int base, int exp)
{
	int result = 1;
	for (int i = exp; i > 0; i-- )
		result*=base;
	return result;
}

