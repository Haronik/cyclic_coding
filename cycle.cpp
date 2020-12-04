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
        std::string tmp{ bits };
        tmp.append(std::string(polinom.size()-1, '0'));

        auto pos = tmp.find("1");
        while (pos <= tmp.size() - polinom.size()) {
            for (auto i = 0; i < polinom.size(); i++) {
                tmp[pos] = '0'+(tmp[pos]-'0') ^ (polinom[i] - '0');
            }
            pos = tmp.find("1",pos);
        }
        return tmp;
    }

    static std::string GetCRC(std::string bits, std::string polinom) {

    }


    static long error(std::string bits) {
        int error = 0;
        for (long pos = 1; pos < bits.size(); pos <<= 1) {
            int count = 0;
            for (int l = pos - 1; l < bits.size(); l += 2 * pos) {
                auto r = ((bits.begin() + l + pos) < bits.end()) ? (bits.begin() + l + pos) : (bits.end());
                count += std::count(bits.begin() + l, r, '1');
            }
            error += (count & 1) * pos;
        }
        return error;
    }

    static std::string decode(std::string bits) {
        if (int err = error(bits)) {
            std::cout << "Error in position " << err << std::endl;
            bits[err - 1] = (bits[err - 1] == '0') ? '1' : '0';
        }
        else {
            std::cout << "Message is correct! \n";
        }

        std::string result;
        int parbit = 1, pos = 0;
        while (pos < bits.size()) {
            if (pos == (parbit - 1)) {
                parbit <<= 1;
            }
            else result.push_back(bits[pos]);
            pos++;
        }
        return result;
    }

private:

};


int main() {
    std::string polinom = "1000011";
    std::string data, datacoded, pol;
    std::cin >> data;
    datacoded = CrcCodingStation::code(data, polinom);
    std::cout << datacoded << std::endl;
    std::cin >> pol;
    
    if (CrcCodingStation.check(datacoded)) {
        std::cout << "Error(s) detected!";
    } else {
        std::cout << "No error(s) detected!";
        std::cout << CrcCodingStation::decode(datacoded, pol);
    }
    CrcCodingStation.GetCRC(datacoded);
}
