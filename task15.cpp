#include<iostream>
#include<vector>
#include<fstream>

class SortingStrategy {
   public:
	  virtual void sort (std::vector<int>& data) = 0;
	  virtual ~SortingStrategy(){}
};

class BubbleSort : public SortingStrategy {
public:
    void sort(std::vector<int>& data) override {
        int n = data.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - 1 - i; ++j) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
    }
    
};

class SelectionSort : public SortingStrategy {
public:
    void sort(std::vector<int>& data)  override {
        int n = data.size();
        for (int i = 0; i < n - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                if (data[j] < data[minIndex]) {
                    minIndex = j;
                }
            } 
            if (minIndex != i) {
                std::swap(data[i], data[minIndex]);
            }
        }
    }
};

class FileHandler {
private:
	std::string input_file_name;
	std::string output_file_name;
public:
    FileHandler( const std::string& input_file_name,const std::string& output_file_name) : input_file_name(input_file_name),output_file_name(output_file_name) {}

    std::vector<int> read_array_from_file(const std::string& input_file_name)  {
        std::vector<int> array;
        std::ifstream input_file(input_file_name);

        if (input_file.is_open()) {
            int value;
            while (input_file >> value) {
                array.push_back(value);
            }
            input_file.close();
        } else {
            std::cout << " error::cant opening the file for reading: " << std::endl;
        }

        return array;
    }

    void save_array_to_file( std::vector<int>& array,const std::string& output_file_name) {
        std::ofstream output_file(output_file_name);

        if (output_file.is_open()) {
            for (auto it = array.begin(); it != array.end(); ++it) {
                output_file << *it << " ";
            }
            output_file.close();
            std::cout << "Sorted array saved to file: "  << std::endl;
        } else {
            std::cout << "error::cant opening file for writing: "  << std::endl;
        }
    }
};


class SortingApplication {
	
private:
    SortingStrategy* sortingStrategy;
    FileHandler fileHandler;
public:
    SortingApplication() : sortingStrategy ( nullptr),
        fileHandler("","")   {}

    ~SortingApplication() {
        delete sortingStrategy;
    }

     void prompt() {
        std::cout << "Enter the input file name: ";
        std::string input_file_name;
        std::cin >> input_file_name;
          
	std::cout << "Enter the output file name: ";
        std::string output_file_name;
        std::cin >> output_file_name;


        std::cout << "Choose the sorting algorithm:" << std::endl;
        std::cout << "1.Bubble Sort" << std::endl;
        std::cout << "2.Selection Sort" << std::endl;

        int choice;
        std::cin >> choice;

        setSortingStrategy(choice);
        foo(input_file_name, output_file_name);
    }

private:
    void setSortingStrategy(int choice) {
        delete sortingStrategy;

        switch (choice) {
            case 1:
                sortingStrategy = new BubbleSort();
                break;
            case 2:
                sortingStrategy = new SelectionSort();
                break;
            default:
                std::cout << "Invalid choice:" << std::endl;
                break;
        }
    }

    void foo(const std::string& input_file_name, const std::string& output_file_name) {
        std::vector<int> array = fileHandler.read_array_from_file(input_file_name);

        if (sortingStrategy) {
            sortingStrategy->sort(array);
        } else {
            std::cerr << "Sorting strategy not set:" << std::endl;
        }

        fileHandler.save_array_to_file(array, output_file_name);
    }
};

int main() {
    SortingApplication s;
    s.prompt();

  return 0;
}

