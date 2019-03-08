#ifndef STOKENIZER_H
#define STOKENIZER_H
#include <const.h>
#include <iostream>
#include <token.h>
using namespace std;

//submission: tokenizer test: tokenize a file
//map test: place tokens in a map
//freq test: value(freq) sorted list
//last word of token
//apostrophe -1
class STokenizer
{
public:
    STokenizer();
    STokenizer(char str[]);

    bool done(); //Stokenizer are you done with the buffer?
    //void set_string(char str[]); //sets the token you get from Token into a string
    friend STokenizer& operator >> (STokenizer& s, Token& t);
                                    //insertion operator
    void print_table();
    void input_buffer(char str[]);
    void printpos();
    void reset_position();


private:
    char buffer[BUFFER_MAX];
    int table[ROW_MAX][COL_MAX];
    int pos;

    void init_table();
    void mark_table();
    void mark_success(int table[][COL_MAX], int state);
    void mark_fail(int table[][COL_MAX], int state);
    void mark_cell(int row, int table[][COL_MAX], char letter, int state);
    void mark_cell(int row, int table[][COL_MAX], const char column[], int state);
    string extractString(char str[], int start, int end);
    bool get_token(int start_state, string& token);
};

STokenizer::STokenizer(){
    //cout<<endl<<"STOKENIZER DEFAULT CTOR"<<endl;
    init_table();
    mark_table();
    pos = 0;
}

STokenizer::STokenizer(char str[]){
    init_table();
    input_buffer(str);
    mark_table();
    pos = 0;
}

//this guy gets one token each time from the string
STokenizer& operator >> (STokenizer& s, Token& t){
    //s.printpos();
    //cout<<endl;
    //cout<<endl<<"{STK: ENTERED >> OPERATOR]";
    string token;
    //cout<<endl<<"[>> token_pos is "<<s.pos<<"]"<<endl;

    if(s.get_token(START_DIGIT, token)){
        t = Token(token, NUMBER);  //zero is words
        return s;
    }
    else if(s.get_token(START_LETTER, token)){
        t = Token(token, WORD);
        return s;
    }
    else if(s.get_token(START_SPACE, token)){
        t = Token(token, SPACE);
        return s;
    }
    else if(s.get_token(START_DECIMAL, token)){
        t = Token(token, UNKNOWN);
        return s;
    }
    else if(s.get_token(START_COMMA, token)){
        t = Token(token, UNKNOWN);
        return s;
    }
    else if(s.get_token(START_EXCLAMATION, token)){
        t = Token(token, UNKNOWN);
        return s;
    }
    else if(s.get_token(START_QUESTION, token)){
        t = Token(token, UNKNOWN);
        return s;
    }
    cout<<endl<<"Unrecognized token: ["<<s.buffer[s.pos]<<"]"<<endl;
    //cout<<"s.pos is currently: "<<s.pos<<endl;
    s.pos++;
}

bool STokenizer::done(){
    if(pos == strlen(buffer)-1){
        return true;
    }
    else{
       return false;
    }
}

void STokenizer::reset_position(){
    pos=0;
}

void STokenizer::printpos(){
    cout<<"SToken_pos: "<<pos<<"  ";
}

void STokenizer::input_buffer(char str[]){
    //cout<<endl<<endl<<"*****************************************";
    //cout<<endl<<"FTK: Inputting buffer -> ["<<str<<"]"; //"stk pos at: "<<pos<<endl;
    //cout<<endl<<"******************************************"<<endl;
    int lengthOfString = strlen(str);

    for(int i=0; i<lengthOfString; i++){
        buffer[i] = str[i];
        //cout<<endl<<"buffer[i] = "<<buffer[i]<<endl;
    }
    buffer[lengthOfString] = NULL;
    //cout<<endl<<"STK: input_buffer: ["<<buffer<<"]"<<endl;
}

//after fail state, dont move the token
//the token should move from the outside
bool STokenizer::get_token(int start_state, string& token){
    int start_pos = pos;
    int state;
    int rowState = start_state;
    int bufferLength = strlen(buffer);
    char key;


//    cout<<endl<<endl<<"****************************"<<endl;
//    cout<<"ENTERED GET_TOKEN"<<endl;
//    if(start_state == 0){
//        cout<<"[[[DIGIT LOOP]]]"<<endl;
//        cout<<"Starting Rowstate: 0"<<endl;
//    }
//    if(start_state == 4){
//        cout<<"[[[SPACE LOOP]]]"<<endl;
//        cout<<"Starting Rowstate: 4"<<endl;
//    }
//    if(start_state == 6){
//        cout<<"[[[LETTER LOOP]]]"<<endl;
//        cout<<"Starting Rowstate: 6"<<endl;
//    }
//    if(start_state == 8){
//        cout<<"[[[DECIMAL LOOP]]]"<<endl;
//        cout<<"Starting Rowstate: 8"<<endl;
//    }
//    cout<<"****************************"<<endl;
//    cout<<"ENTERED token_pos is "<<pos<<endl;

    for(int walker=pos; walker<bufferLength; walker++){
        key = buffer[walker];

//        cout<<endl<<endl<<"==========FOR LOOP==========="<<endl;
//        cout<<"CURRENT KEY: ["<<key<<"]"<<endl;

        int key_ASCII = (int) key;
        //convert to ASCII
//        cout<<endl<<"ASCII KEY: "<<key_ASCII;
//        cout<<endl<<"Current rowState: "<<rowState<<endl;
//        cout<<endl<<"table[rowState][key_ASCII] = "<<table[rowState][key_ASCII];
        if(key_ASCII<0){
            state=-1;
        }
        else{
            state=table[rowState][key_ASCII];
        }
        state=table[rowState][key_ASCII];

//        cout<<endl<<"Traverse table...Found state: "<<state;
//        cout<<endl<<endl<<"UPDATING ROWSTATE FROM "<<rowState<<" TO "<<table[rowState][key_ASCII];
//        cout<<endl<<endl<<"NEW table[state][key_ASCII] = " <<table[state][key_ASCII];
//        cout<<endl<<"NEW state = "<<state<<endl;

        if(state==FAIL){

//            cout<<endl<<"[STATE HAS FAILED]";
            if(start_pos==walker){
//                cout<<endl<<"[POSITION HASN'T MOVED, RETURNING FALSE]";
//                cout<<endl<<"token_pos is "<<pos<<endl;
                return false;
            }
            else{
//                cout<<endl<<"[POSITION MOVED, TOKEN DETECTED]"<<endl;
                pos=walker;
//                cout<<endl<<"position is "<<pos<<endl;

                token = extractString(buffer, start_pos, pos);
//                cout<<endl<<"exitting TOKEN IS AT: "<<pos<<endl;
                return true;
            }
        }
        else{
//            cout<<endl<<"[STATE IS SUCCESS]"<<endl;
            rowState=table[state][key_ASCII];
            if(walker == bufferLength-1){
                //need a return statement while in a success state
                //and this is only possible if walker is at the end of the buffer
                pos = walker;
                token = extractString(buffer, start_pos, pos+1);
                //pos is at the 2nd to last letter right now
                //so pos+1 for function to get the whole letter

//                cout<<"ENTERED token_pos is "<<pos<<endl;

                //update position after function extracts word
                return true;
            }
        }
    }
}

void STokenizer::init_table(){
    for(int i=0; i<ROW_MAX; i++){
        for(int j=0; j<COL_MAX; j++){
            table[i][j] = -1;
        }
    }
}

void STokenizer::mark_table(){
    //DIGIT
    mark_fail(table, 0);
    mark_success(table, 1);
    mark_fail(table, 2);
    mark_success(table, 3);

    mark_cell(0, table, DIGITS, 1);
    mark_cell(0, table, PERIOD, -1);
    mark_cell(1, table, DIGITS, 1);
    mark_cell(1, table, PERIOD, 2);
    mark_cell(2, table, DIGITS, 3);
    mark_cell(2, table, PERIOD, 3);
    mark_cell(3, table, DIGITS, 3);

    //SPACE
    mark_fail(table, 4);
    mark_success(table, 5);
    mark_cell(4, table, SPACES, 5);
    mark_cell(5, table, SPACES, 5);

    //ALPHA
    mark_fail(table, 6);
    mark_success(table, 7);
    mark_cell(6, table, UPPER_ALPHA, 7);
    mark_cell(6, table, LOWER_ALPHA, 7);
    mark_cell(6, table, APOSTROPHE, 8);
    mark_cell(7, table, UPPER_ALPHA, 7);
    mark_cell(7, table, LOWER_ALPHA, 7);
    mark_cell(7, table, APOSTROPHE, 8);

    //APOSTROPHE
    mark_fail(table, 8);
    mark_success(table, 9);
    mark_cell(8, table, APOSTROPHE, 9);
    mark_cell(9, table, LOWER_ALPHA, 9);
    mark_cell(9, table, UPPER_ALPHA, 9);

    //COMMA
    mark_fail(table, 10);
    mark_cell(10, table, COMMA, 10);

    //EXCLAMATION
    mark_fail(table, 11);
    mark_cell(11, table, EXCLAMATION, 11);

    //QUESTION
    mark_fail(table, 12);
    mark_cell(12, table, QUESTION, 12);
}

void STokenizer::print_table(){
    for(int i=0; i<ROW_MAX; i++){
        for(int j=0; j<COL_MAX; j++){
            if(table[i][j] != -1){
                cout<<""; //alignment
            }
            cout<<table[i][j]<<"   ";
        }
        cout<<endl;
    }
}

void STokenizer::mark_cell(int row, int table[][COL_MAX], const char column[], int state){
    for(int i=0; column[i]; i++){
        char c = column[i];
        //stores a character in columns[] at position i
        table[row][c] = state;
        //insert state
    }
}

void STokenizer::mark_cell(int row, int table[][COL_MAX], char letter, int state){
        table[row][letter] = state;
}

void STokenizer::mark_fail(int table[][COL_MAX], int state){
    table[state][0]=0;
}

void STokenizer::mark_success(int table[][COL_MAX], int state){
    table[state][0]=1;
}

string STokenizer::extractString(char str[], int start, int end){
    int stringLength = end-start;

    //cout<<"end: "<<end<<endl;
    //cout<<"start: "<<start<<endl;
    //cout<<"length: "<<stringLength<<endl;

    char result[stringLength];

    for(int i=0, j=start; i<stringLength; i++, j++){
        //if(end == bufferLength-1){stringLength+=1;}
        result[i] = str[j];
        //cout<<endl<<"i: "<<i<<" j: "<<j<<endl;
        //cout<<"result: "<<result[i];
        //cout<<endl<<"buffer: "<<str[j];
    }
    //cout<<endl<<"EXTRACTED. RETURNING STRING"<<endl;
    //cout<<"***********************************";

    string s(result, stringLength);
    return s;
}

#endif // STOKENIZER_H
