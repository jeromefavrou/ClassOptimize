/*
BSD 3-Clause License

Copyright (c) 2024, SYSJF
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/



#ifndef __UTILITYS_HPP__
#define __UTILITYS_HPP__




#include <vector>
#include <fstream>
#include <string>
#include <locale>
#include <array>
#include <tuple>
#include <filesystem>
#include <iostream>
#include <regex>
#include <functional>
#include <thread>


#include <gtkmm-3.0/gtkmm/container.h>

/// ensemble de fonction static utilitaire
namespace utilitys
{
unsigned long long factorial(int n) 
{
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) 
    {
        result *= i;
    }
    return result;
}


 template<typename K, typename V> K findKeyByValue(const std::map<K, V>& m, const V& value) 
{
    for (const auto& pair : m) 
    {
        if (pair.second == value) {
            return pair.first;
        }
    }
    throw std::runtime_error("Value not found in map");
}

    /// @brief convertie un type en un autre
    /// @tparam T1 type d'entrée
    /// @tparam T2 type de sotrie
    /// @param d variable d'entré
    /// @return valeur convertie
    template<class T1,class T2> T2 ss_cast(T1 const & d)
    {
        std::stringstream _ss_cast;

        _ss_cast << d;

        T2 tps;

        _ss_cast >> tps;

        return tps;
    }

};




#endif