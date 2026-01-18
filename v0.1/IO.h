#pragma once
#include "Studentas.h"
#include <vector>
#include <string>

std::vector<Studentas> nuskaitytiIsFailo(const std::string& f);
Studentas generuotiAtsitiktini(const std::string& v, const std::string& p, int n);
void spausdinti(const std::vector<Studentas>& v, bool vid, bool med, int k);
