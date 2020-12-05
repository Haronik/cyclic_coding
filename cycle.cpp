#include<vector>
#include<fstream>
#include<iostream>
#include<ios>
#include<string>
#include<map>
#include<algorithm>
#include<queue>
#include<locale>
#include<bitset>


class CrcCodingStation {
public:

    static std::string code(std::string bits, std::string polinom) {
        std::string checksum = GetCRC(bits, polinom);
        bits.append(checksum);
        return bits;
    }

    static std::string GetCRC(std::string bits, std::string polinom) {
        std::string tmp{ bits };
        tmp.append(std::string(polinom.size() - 1, '0'));

        auto pos = tmp.find("1");
        while (pos <= tmp.size() - polinom.size()) {
            for (auto i = 0; i < polinom.size(); i++) {
                tmp[pos] = '0' + (tmp[pos] - '0') ^ (polinom[i] - '0');
                //std::cout << std::endl << tmp;
                pos++;
            }
            //std::cout << std::endl << "next iteration";
            pos = tmp.find("1");
        }
        return tmp.substr(bits.size(), polinom.size() - 1);
    }

    static bool check(std::string bits, std::string polinom) {
        if (GetCRC(bits, polinom).find('1') == std::string::npos) {
            return 0;
        }
        return 1;
    }

    static std::string decode(std::string bits, std::string polinom) {
        return bits.substr(0, bits.size() - polinom.size()+1);
    }

private:

};


int main() {
    // 1000011 
    std::string polinom = "1000011";
    std::string polinom2 = "11";
    std::string data, datacoded;
    std::cin >> data;
    datacoded = CrcCodingStation::code(data, polinom);
    std::cout << std::endl << "Coded data :" << datacoded << std::endl;
    std::cin >> data;
    
    if ( CrcCodingStation::check(data, polinom)) {
        std::cout << "Error(s) detected!";
    } else {
        std::cout << "No error(s) detected!";
        std::cout << std::endl << "Data : " << CrcCodingStation::decode(data, polinom);
    }
    std::cout << std::endl << "Reminder : " << CrcCodingStation::GetCRC(data, polinom);
   }
