#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <array>
class MergeSort{

private:
    std::vector<int> listOfInt;
    int width = 1;
    std::vector<int>::size_type sizeOfList;
    void merge(int,int,int);
    void mergeSort();
    void printList(std::string outputFile);
public:
    int main(int argc,char * argv[]);
    void processFile(int argc,char * argv[]);

};

void MergeSort::printList(std::string outputFile){
    std::ofstream outStream;
    outStream.open(outputFile);
    if (outStream.fail()){
        std::cout << "Output file writing process failed." << std::endl;
        exit(1);
    }
    else{
        for (int i=0; i<listOfInt.size();i++){
            outStream << listOfInt[i] << "\n";
        }
    }
    
}
void MergeSort::merge(int leftSetStart, int middleBoundary, int secondSetBoundary){
    std::vector<int> temp1;
    int leftSetCurrentIndex = leftSetStart;
    int tempListCurrentIndex = leftSetStart;
    int rightSetCurrentIndex = middleBoundary+1;
    // Copy over list to temp
    for(int i = 0; i < sizeOfList; i++){
        temp1.push_back(listOfInt[i]);
    }
    //While both sets have elements remaining
    while (leftSetCurrentIndex <= middleBoundary && rightSetCurrentIndex <= secondSetBoundary){
        //Left Set current value is less than or equal to the right set current value
        if (listOfInt[leftSetCurrentIndex] <= listOfInt[rightSetCurrentIndex]){
            temp1[tempListCurrentIndex] = listOfInt[leftSetCurrentIndex];
            tempListCurrentIndex++;
            leftSetCurrentIndex++;
        }
        //Right set current value is less than the right set current value
        else{
            temp1[tempListCurrentIndex] = listOfInt[rightSetCurrentIndex];
            tempListCurrentIndex++;
            rightSetCurrentIndex++;
        }
    }

    //All of left set is copied
    if (leftSetCurrentIndex > middleBoundary){
        while(rightSetCurrentIndex <= secondSetBoundary){
            temp1[tempListCurrentIndex] = listOfInt[rightSetCurrentIndex];
            tempListCurrentIndex++;
            rightSetCurrentIndex++;
        }
    }
    //All of right set is copied
    else if (rightSetCurrentIndex > secondSetBoundary){
        while (leftSetCurrentIndex <= middleBoundary){
            temp1[tempListCurrentIndex] = listOfInt[leftSetCurrentIndex];
            tempListCurrentIndex++;
            leftSetCurrentIndex++;
        }
    }

    // Swap lists
    listOfInt = temp1;

}
void MergeSort::mergeSort(){
    int m;
    int r;
    // Furthest right index of array
    int maxIndex = sizeOfList-1;
    // Width steps
    for (int width = 1; width < maxIndex; width *=2){
        // Left set step
        for (int l = 0; l < maxIndex; l+=2*width){
            // Middle should indicate the last index of the left set
            m = l + width -1;
            // Right should indicate the first index of the right set. If it is larger than the maxIndex, there is no right set
            if (l + 2*width -1 < maxIndex){
                r = l + 2*width -1;
            }
            else{
                r = maxIndex;
            }

            merge(l,m,r);
        }
    }
    
}
void MergeSort::processFile(int argc,char * argv[]){
    std::ifstream fileParse;
    if (argc < 3){
        std::cout << "Please enter the filename as the argument" << std::endl;
    }
    else{
        fileParse.open(argv[1]); 
        if (fileParse.fail()){
            std::cout << "File opening process failed." << std::endl;
            exit(1);
        }
    }

    std::string currentToken;
    try{
        while(fileParse >> currentToken){
            listOfInt.push_back(std::stoi(currentToken));
        }
    }
    catch (const std::exception&){
        std::cout << "An error has occurred while parsing file. Please revise file and try again" << std::endl;
        exit(1);
    }
    sizeOfList = listOfInt.size();
    mergeSort();
    printList(argv[2]);
}
int main(int argc, char * argv[]){
    MergeSort merge;
    merge.processFile(argc,argv);
}

