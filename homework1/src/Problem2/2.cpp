#include <iostream>
#include <string>
using namespace std;

void printSubset(string arr[], bool used[], int n) {
    cout << "{";
    bool first = true;
    for (int i = 0; i < n; i++) {
        if (used[i]) {
            if (!first) cout << ",";
            cout << arr[i];
            first = false;
        }
    }
    cout << "}" << endl;
}

void generatePowerSet(string arr[], bool used[], int n, int index) {
    if (index == n) {
        printSubset(arr, used, n);
        return;
    }

    used[index] = false;
    generatePowerSet(arr, used, n, index + 1);

    used[index] = true;
    generatePowerSet(arr, used, n, index + 1);
}

int main() {
    int n;
    string arr[10];
    bool used[10];

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Power set:\n";
    generatePowerSet(arr, used, n, 0);
    return 0;
}
