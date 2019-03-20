#pragma once

#include <vector>
#include <string>

using namespace std;

class Door {

public:
	Door();

private:

	vector<string> rules_;
	vector<string> passwords_;

};