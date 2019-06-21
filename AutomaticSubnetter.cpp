#include <iostream>
#include <cmath>
#include <string>
#include <Windows.h>
/*
	Only works for Class C for now, which is all my project needs.
	Tested on 4 problems, works 100%.
*/
int main() {
	SetConsoleTitle(L"Evil Automatic Subnetter");
	int ipBeginning, defaultCIDR, determinatingFactor, host, subnetBits, hostBits, customSubnet, customCIDR, increment;
	std::string defaultMask;
	char ipClass;
	std::cout << "Please enter the beginning of the specified IP addr: ";
	while(!(std::cin >> ipBeginning) || ipBeginning < 1 || ipBeginning > 254){
		std::cout << "Please enter a valid number between 1 and 254 for the beginning of the IP.\nEnter the beginning of the specified IP addr: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	// Making defaultMask automatic.
	if ( ipBeginning >= 0 && ipBeginning < 128 ) {
		ipClass = 'A'; // Class A.
		defaultMask = "255.0.0.0";
		defaultCIDR = 8;
	} else if ( ipBeginning > 127 && ipBeginning < 192 ) {
		ipClass = 'B'; // Class B.
		defaultMask = "255.255.0.0";
		defaultCIDR = 16;
	} else if ( ipBeginning > 191 && ipBeginning < 224 ) {
		ipClass = 'C'; // Class C.
		defaultMask = "255.255.255.0";
		defaultCIDR = 24;
	}
	std::cout << "Please enter whether or not the addr. is host or non-host: (0 = N/A, 1 = Host) ";
	while (!(std::cin >> host) || host < 0 || host > 1) {
		std::cout << "Please enter either 1 or 0 for host/non-host. (0 = N/A, 1 = Host)\nEnter whether or not the addr. is host or non-host: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	std::cout << "Please enter the determinating factor: ";
	while (!(std::cin >> determinatingFactor) || determinatingFactor < 0) {
		std::cout << "Please enter a valid number for the determinating factor (>1).\nEnter the determinating factor: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	if (host == 1) { // My project only requires host-only for now.
		determinatingFactor = determinatingFactor + 2; // Add 2 when its per host.
		// Formula for host bits: (2^number = closestToDeterminatingFactor).

		int previousClosest = 256;
		int lastCount = 8;
		for (int count = 0; count < 9; count++) {
			int Value = determinatingFactor - std::pow(2.0, count);
			if (Value < 0)
				Value = -Value;
			if (Value == 0 || Value < previousClosest) {
				previousClosest = Value;
				lastCount = count;
			}
		}
		hostBits = lastCount;
		if (ipClass == 'C') { // Class C method. (8)
			subnetBits = 8 - lastCount;
		}
		// Formula for custom subnet mask: 128, 64, 32, 16, 8, 4, 2, 1 (Host = R->L)
		if (hostBits == 1) { // Yes, I'm hard-coding this for now.
			customSubnet = 254;
		} else if ( hostBits == 2 ) {
			customSubnet = 252;
			increment = 4;
		} else if ( hostBits == 3) {
			customSubnet = 248;
			increment = 8;
		} else if ( hostBits == 4) {
			customSubnet = 240;
			increment = 16;
		} else if ( hostBits == 5) {
			customSubnet = 224;
			increment = 32;
		} else if ( hostBits == 6) {
			customSubnet = 192;
			increment = 64;
		} else if ( hostBits == 7) {
			customSubnet = 128;
			increment = 128;
		}
		// Formula for custom CIDR notation: defaultCIDR + subnetBits
		customCIDR = defaultCIDR + subnetBits;
	} else {
		int previousClosest = 256;
		int lastCount = 8;
		for (int count = 0; count < 9; count++) {
			int Value = determinatingFactor - std::pow(2.0, count);
			if (Value < 0)
				Value = -Value;
			if (Value == 0 || Value < previousClosest) {
				previousClosest = Value;
				lastCount = count;
			}
		}
		subnetBits = lastCount;
		if (ipClass == 'C') { // Class C method. (8)
			hostBits = 8 - lastCount;
		}
		// Formula for custom subnet mask: 128, 64, 32, 16, 8, 4, 2, 1 (Subnet = L->R)
		if (hostBits == 1) { // Yes, I'm hard-coding this for now.
			customSubnet = 254;
			increment = 2;
		} else if (hostBits == 2) {
			customSubnet = 252;
			increment = 4;
		} else if (hostBits == 3) {
			customSubnet = 248;
			increment = 8;
		} else if (hostBits == 4) {
			customSubnet = 240;
			increment = 16;
		} else if (hostBits == 5) {
			customSubnet = 224;
			increment = 32;
		} else if (hostBits == 6) {
			customSubnet = 192;
			increment = 64;
		} else if (hostBits == 7) {
			customSubnet = 128;
			increment = 128;
		}
		// Formula for custom CIDR notation: defaultCIDR + subnetBits
		customCIDR = defaultCIDR + subnetBits;
	}
	if (host == 1) {
		std::cout << "Beginning IP: " << ipBeginning << "\nDefault Mask: " << defaultMask
			<< "\nDefault CIDR: \\" << defaultCIDR << "\nIPClass: " << ipClass
			<< "\nDeterminating Factor: " << determinatingFactor << " hosts per subnet"
			<< "\nSubnet bits: " << subnetBits << "\nHost bits: " << hostBits << "\nCustom subnet: 255.255.255." << customSubnet
			<< "\nCustom CIDR: \\" << customCIDR << "\n";
	} else {
		std::cout << "Beginning IP: " << ipBeginning << "\nDefault Mask: " << defaultMask
			<< "\nDefault CIDR: \\" << defaultCIDR << "\nIPClass: " << ipClass
			<< "\nDeterminating Factor: " << determinatingFactor << " subnets"
			<< "\nSubnet bits: " << subnetBits << "\nHost bits: " << hostBits << "\nCustom subnet: 255.255.255." << customSubnet
			<< "\nCustom CIDR: \\" << customCIDR << "\n";
	}
	for (int count = 0; count < 9; count++) {
		std::cout << "S" << count << ": " << count * increment << " | " << ((count+1) * increment) - 1 << " | " << (count*increment) + 1 << " - " << ((count+1) * increment) - 2 << "\n";
	}
	system("pause");
	return 0;
}
