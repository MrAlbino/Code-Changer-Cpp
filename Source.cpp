#include "Operation.h"
using namespace std;

int main() {
	Operation* operation = new Operation();
	operation->begin();
	delete operation;
	return 0;
}