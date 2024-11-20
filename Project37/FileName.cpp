#include <iostream> 
#include <string> 

using namespace std;

class IOutput {
public:
    virtual void Show() const = 0;
    virtual void Show(const string& info) const = 0;
    virtual ~IOutput() {}
};

class IMath {
public:
    virtual int Max() const = 0;
    virtual int Min() const = 0;
    virtual float Avg() const = 0;
    virtual bool Search(int valueToSearch) const = 0;
    virtual ~IMath() {}
};

class ISort {
public:
    virtual void SortAsc() = 0;
    virtual void SortDesc() = 0;
    virtual void SortByParam(bool isAsc) = 0;
    virtual ~ISort() {}
};

class Array : public IOutput, public IMath, public ISort {
private:
    int* data;
    int size;
 
    void Swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

public:
    Array(int* arr, int size) : size(size) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = arr[i];
        }
    }

    ~Array() {
        delete[] data;
    }

    void Show() const override {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    void Show(const string& info) const override {
        cout << info << ": ";
        Show();
    }

    int Max() const override {
        int maxVal = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] > maxVal) {
                maxVal = data[i];
            }
        }
        return maxVal;
    }

    int Min() const override {
        int minVal = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] < minVal) {
                minVal = data[i];
            }
        }
        return minVal;
    }

    float Avg() const override {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += data[i];
        }
        return static_cast<float>(sum) / size;
    }

    bool Search(int valueToSearch) const override {
        for (int i = 0; i < size; i++) {
            if (data[i] == valueToSearch) {
                return true;
            }
        }
        return false;
    }

    void SortAsc() override {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    Swap(data[j], data[j + 1]);
                }
            }
        }
    }

    void SortDesc() override {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (data[j] < data[j + 1]) {
                    Swap(data[j], data[j + 1]);
                }
            }
        }
    }

    void SortByParam(bool isAsc) override {
        if (isAsc) {
            SortAsc();
        }
        else {
            SortDesc();
        }
    }
};

int main() {
    int arr[] = { 5, 2, 9, 1, 5, 6 };
    int size = sizeof(arr) / sizeof(arr[0]);
    Array array(arr, size);

    array.Show();
    array.Show("Initial Array");

    cout << "Max: " << array.Max() << endl;
    cout << "Min: " << array.Min() << endl;
    cout << "Average: " << array.Avg() << endl;
    cout << "Search 9: " << (array.Search(9) ? "Found" : "Not Found") << endl;

    array.SortAsc();
    array.Show("Sorted Ascending");
    array.SortDesc();
    array.Show("Sorted Descending");
    array.SortByParam(true);
    array.Show("Sorted by Param (Ascending)");
    array.SortByParam(false);
    array.Show("Sorted by Param (Descending)");

    return 0;
}