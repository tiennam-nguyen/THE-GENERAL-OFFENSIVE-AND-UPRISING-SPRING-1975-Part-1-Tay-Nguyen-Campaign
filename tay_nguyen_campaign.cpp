#include "tay_nguyen_campaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

const int MAX_LINES = 5;
const int MAX_LINE_LENGTH = 100;

// Task 0: Read input file
bool readFile(
    const string& filename,
    int LF1[], int LF2[],
    int& EXP1, int& EXP2,
    int& T1, int& T2, int& E)
{
    char data[MAX_LINES][MAX_LINE_LENGTH];
    int numLines = 0;

    ifstream ifs("tnc_tc_01_input");
    if (!ifs.is_open())
    {
        return false;
    }

    while (numLines < MAX_LINES && ifs.getline(data[numLines], MAX_LINE_LENGTH))
    {
        numLines++;
    }
    ifs.close();

    if (numLines < MAX_LINES)
    {
        return false;
    }

    // TODO: Extract values from the `data` array and store them in respective variables
        // manage LF1
    string data0_str = string(data[0]);  //convert char array to string to use back()
    if (data0_str[0] != '[' || data0_str.back() != ']') return false;//check the format
    string cut_LF1 = data0_str.substr(1, strlen(data[0]) - 2);//remove [] to stream easily

    int totalnum = 0, count = 0;//run paralel til 17
    string current = "";//blank
    for (char n : cut_LF1) {
        if (isdigit(n)) {//take numbers from string
            current += n;
        }
        else if (n == ',') {//commas are the sign to split nums
            if (!current.empty()) {
                totalnum++;
                if (count < 17) {
                    int num = stoi(current);
                    LF1[count] = (num > 1000) ? 1000 : (num < 0) ? 0 : num;
                    count++;
                }
                current = "";//reset
            }
        }
        else return false;//anything other than those are not allowed
    }
    if (!current.empty()) { // manage the last num without comma after
        totalnum++;
        if (count < 17) {
            int num = stoi(current);
            LF1[count] = (num > 1000) ? 1000 : (num < 0) ? 0 : num;
        }
    }
    if (totalnum != 17) return false;//the last num must be 17th; others are false

    // manage LF2 (similar to LF1)
    string data1_str = string(data[1]);
    if (data1_str[0] != '[' || data1_str.back() != ']') return false;
    string cut_LF2 = data1_str.substr(1, strlen(data[1]) - 2);

    totalnum = 0, count = 0;
    current = "";//reset
    for (char n : cut_LF2) {
        if (isdigit(n)) {
            current += n;
        }
        else if (n == ',') {
            if (!current.empty()) {
                totalnum++;
                if (count < 17) {
                    int num = stoi(current);
                    LF2[count] = (num > 1000) ? 1000 : (num < 0) ? 0 : num;
                    count++;
                }
                current = "";
            }
        }
        else return false;
    }
    if (!current.empty()) {
        totalnum++;
        if (count < 17) {
            int num = stoi(current);
            LF2[count] = (num > 1000) ? 1000 : (num < 0) ? 0 : num;
        }
    }
    if (totalnum != 17) return false;

    // manage EXP1 v� EXP2
    totalnum = 0;//reset
    current = "";
    for (char n : data[2]) {
        if (isdigit(n)) {
            current += n;
        }
        else if (n == ' ') {//whitespace is the sign to split 2 nums
            if (!current.empty()) {
                totalnum++;
                int num = stoi(current);
                if (totalnum == 1) EXP1 = (num > 600) ? 600 : (num < 0) ? 0 : num;
                else if (totalnum == 2) EXP2 = (num > 600) ? 600 : (num < 0) ? 0 : num;
                else return false;//more than 2 is false
                current = "";//reset
            }
        }
        
    }
    if (!current.empty()) {//for last num without anything after
        totalnum++;
        int num = stoi(current);
        if (totalnum == 1) EXP1 = (num > 600) ? 600 : (num < 0) ? 0 : num;
        else if (totalnum == 2) EXP2 = (num > 600) ? 600 : (num < 0) ? 0 : num;
        else return false;//more than 2 is false
    }
    if (totalnum != 2) return false;//make sure there're just 2 nums

    // manage T1 and T2 (similar to EXP1 and EXP2)
    totalnum = 0;
    current = "";
    for (char n : data[3]) {
        if (isdigit(n)) {
            current += n;
        }
        else if (n == ' ') {
            if (!current.empty()) {
                totalnum++;
                int num = stoi(current);
                if (totalnum == 1) T1 = (num > 3000) ? 3000 : (num < 0) ? 0 : num;
                else if (totalnum == 2) T2 = (num > 3000) ? 3000 : (num < 0) ? 0 : num;
                else return false;
                current = "";
            }
        }
        
    }
    if (!current.empty()) {
        totalnum++;
        int num = stoi(current);
        if (totalnum == 1) T1 = (num > 3000) ? 3000 : (num < 0) ? 0 : num;
        else if (totalnum == 2) T2 = (num > 3000) ? 3000 : (num < 0) ? 0 : num;
        else return false;
    }
    if (totalnum != 2) return false;

    // manage E
    totalnum = 0;//reset
    current = "";
    for (char n : data[4]) {
        if (isdigit(n)) {
            current += n;
        }
        
    }
    if (!current.empty()) {//there's no sign to take num, so do this afterwards
        totalnum++;
        int num = stoi(current);
        E = (num > 99) ? 99 : (num < 0) ? 0 : num;
    }
    if (totalnum != 1) return false;//make sure just 1 num

    return true;
}


// Task 1
int gatherForces(int LF1[], int LF2[])
{
    // TODO: Implement this function
    const int weights[17] = { 1, 2, 3, 4, 5, 7, 8, 9, 10, 12, 15, 18, 20, 30, 40, 50, 70 };//weight of each level respectively
    int LF1_power = 0, LF2_power = 0;//starter to addition
    for (int i = 0; i < 17; i++) {
        LF1_power = LF1_power + LF1[i] * weights[i];
        LF2_power = LF2_power + LF2[i] * weights[i];
    }
    return LF1_power + LF2_power;
}

// Task 2
string determineRightTarget(const string& target)//Task 2.1
{
    // TODO: Implement this function
    int num[3];//max num allowed
    string tar = "";
    int count = 0;
    int ID = -1;//avoid undefined behavior if ID doesn't contain valid num
    for (char t : target) {
        if (isdigit(t)) {//take nums out of string
            tar += t;
        }
        else {//anything other than digits is the sign to split nums
            if (!tar.empty()) {
                num[count++] = stoi(tar);//take each num and store in array
                if (count > 3 || count == 0) return "INVALID";//index 2 is the 3rd num
                tar = "";//reset
            }
        }
    }
    if (!tar.empty()) {//in case the digits are at last
        num[count++] = stoi(tar);
        if (count > 3 || count == 0) return "INVALID";
    }
    if (count == 1) {
        if ((num[0] >= 0) && (num[0] <= 2))
            return "DECOY";
        else if ((num[0] > 7) || (num[0] < 0))
            return "INVALID";
        else {
            switch (num[0])
            {
            case 3: return "Buon Ma Thuot";
            case 4: return "Duc Lap";
            case 5: return "Dak Lak";
            case 6: return "National Route 21";
            case 7: return "National Route 14";
            default:
                return "INVALID";
            }
        }
    }
    else if (count == 2) {
        ID = (num[0] + num[1]) % 5 + 3;
        switch (ID)
        {
        case 3: return "Buon Ma Thuot";
        case 4: return "Duc Lap";
        case 5: return "Dak Lak";
        case 6: return "National Route 21";
        case 7: return "National Route 14";
        default:
            return "INVALID";
        }
    }
    else if (count == 3) {
        int max_value = (num[0] > num[1]) ? ((num[0] > num[2]) ? num[0] : num[2]) : ((num[1] > num[2]) ? num[1] : num[2]);
        ID = (max_value % 5) + 3;
        switch (ID)
        {
        case 3: return "Buon Ma Thuot";
        case 4: return "Duc Lap";
        case 5: return "Dak Lak";
        case 6: return "National Route 21";
        case 7: return "National Route 14";
        default:
            return "INVALID";
        }
    }
    else
        return "INVALID";//make sure num range is 1 to 3
    return "INVALID";
}
//Task 2.2
string reverseString(string message) {//for reverse cipher
    for (int i = 0; i < (message.length() / 2); i++) {//like flipping a paper
        char temp = message[i];//stream through half and swap with the symmetric ones
        message[i] = message[message.length() - 1 - i];
        message[message.length() - 1 - i] = temp;
    }
    return message;
}
void standardizeWords(string& message) {//uppercase first letter and lowercase the others
    bool newWord = true;//to check letter of a new word
    for (int i = 0; i < message.length(); i++) {
        if (message[i] >= 'a' && message[i] <= 'z') {
            if (newWord) {
                message[i] = message[i] - 'a' + 'A';//uppercase
                newWord = false;//after the first char it must be lowercase
            }
        }
        else if (message[i] >= 'A' && message[i] <= 'Z') {
            if (newWord)
                newWord = false;//change nothing but signify to lowercase char next
            else if (!newWord) {
                message[i] = message[i] - 'A' + 'a';//lowercase
            }
        }
        else
            newWord = true;//signify newword if there's a space or others
    }
}
string decodeTarget(const string& message, int EXP1, int EXP2)
{
    // TODO: Implement this function
    string target = "";//to store decoded string
    string model[5] = { "Buon Ma Thuot","Duc Lap","Dak Lak","National Route 21","National Route 14" };//to compare later
    if (EXP1 >= 300 && EXP2 >= 300) {//caesar cipher
        int shift = (EXP1 + EXP2) % 26;
        char upd;//to update characters ciphered
        for (char c : message) {
            if (c >= 'a' && c <= 'z') {
                upd = (c - 'a' + shift) % 26 + 'a';
                target += upd;
            }
            else if (c >= 'A' && c <= 'Z') {
                upd = (c - 'A' + shift) % 26 + 'A';
                target += upd;
            }
            else if ((c == ' ') || (((int)c >= 0) && ((int)c <= 9)))
                target += c;
            else
                return "INVALID";
        }
        standardizeWords(target);
        bool found = false;
        for (int i = 0; i < 5; i++) {
            if (model[i] == target) {
                found = true;
                break;
            }
        }
        if (found)
            return target;
        return "INVALID";
    }
    else {//reverse cipher
        target = reverseString(message);
        standardizeWords(target);
        bool found = false;
        for (int i = 0; i < 5; i++) {
            if (model[i] == target) {
                found = true;
                break;
            }
        }
        if (found)
            return target;
        return "INVALID";
    }
    return "INVALID";
}

// Task 3
void manageLogistics(int LF1, int LF2, int EXP1, int EXP2, int& T1, int& T2, int E)
{
    // TODO: Implement this function
    double T1_temp = T1, T2_temp = T2;//to avoid uncertainties
    if (E == 0) {
        if (LF1 + LF2 != 0) {
            T1_temp = T1 + ((LF1 / (double)(LF1 + LF2)) * (T1 + T2)) * (1 + (EXP1 - EXP2) / 100.0);//double to avoid uncertainties
            T2_temp = T2 + ((T1 + T2) - ((LF1 / (double)(LF1 + LF2)) * (T1 + T2)) * (1 + (EXP1 - EXP2) / 100.0));
        }
    }
    else if (E >= 1 && E <= 9) {
        T1_temp = T1 - (E * 1 / 100.0) * T1;
        T2_temp = T2 - (E * 0.5 / 100.0) * T2;
    }
    else if (E >= 10 && E <= 29) {
        T1_temp = T1 + E * 50;
        T2_temp = T2 + E * 50;
    }
    else if (E >= 30 && E <= 59) {
        T1_temp = T1 + (E * 0.5 / 100.0) * T1;
        T2_temp = T2 + (E * 0.2 / 100.0) * T2;
    }
    else if (E >= 60 && E <= 99) {
        //change nothing
    }
    T1_temp = min(3000.0, (T1_temp > 0.0 ? T1_temp : 0.0));//limit nums in range
    T2_temp = min(3000.0, (T2_temp > 0.0 ? T2_temp : 0.0));
    T1 = ceil(T1_temp);//round up
    T2 = ceil(T2_temp);
}

// Task 4
int planAttack(int LF1, int LF2, int EXP1, int EXP2, int T1, int T2, int battleField[10][10])
{
    // TODO: Implement this function
    double S;
    int fin;//final S after streaming through
    S = (LF1 + LF2) + (EXP1 + EXP2) * 5 + (T1 + T2) * 2;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i % 2 != 0)//odd rows
                S = S - (battleField[i][j] * 3.0 / 2.0);//use fraction to avoid uncertainties
            else//even rows
                S = S - (battleField[i][j] * 2.0 / 3.0);
        }
    }
    fin = ceil(S);//round up
    return fin;
}

// Task 5
void selectionSort(int arr[], int size) {//to sort nums ascendingly
    for (int i = 0; i < size - 1; i++) {//2 slots simultaneously, so the final set is size-2 and size-1
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {//for each num we compare with each of the forefront num
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        int temp = arr[i];//swap values of the min and the current
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}
int resupply(int shortfall, int supply[5][5])
{
    // TODO: Implement this function
    int reorganized[25], index = 0;
    for (int i = 0; i < 5; i++) {//reorganize the 2D array to 1D array
        for (int j = 0; j < 5; j++) {
            reorganized[index++] = supply[i][j];
        }
    }
    selectionSort(reorganized, 25);//sort them in ascending order for easier management
    for (int a = 0; a < 21; a++) {//the last final group is of indexes 20 21 22 23 24
        for (int b = a + 1; b < 22; b++) {
            for (int c = b + 1; c < 23; c++) {
                for (int d = c + 1; d < 24; d++) {
                    for (int e = d + 1; e < 25; e++) {
                        int sum = reorganized[a] + reorganized[b] + reorganized[c] + reorganized[d] + reorganized[e];
                        if (sum >= shortfall)
                            return sum;//list organized, so we just pick the first 5 nums satisfied
                    }
                }
            }
        }
    }
    return -1;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
