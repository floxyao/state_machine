#include <iostream>
#include <fstream>
#include <iomanip>
#include <const.h>
#include <ftokenizer.h>
#include <listclass.h>
#include <mapclass.h>
using namespace std;

/* Name: Flo Yao
 * Project: Tokenizer
 * Notes: -Spliced tokens at the end of the buffer are not combined.
 *
 *        -Program reads apostrophe sign as a ?, giving a -30 ASCII value
 *        and crashes the program.
 *
 *        -At times where there are line breaks or multiple spaces in
 *        between words, STK tokenizes the word preceding that multiple
 *        times.
 *
 */


bool get_Token(int table[ROW_MAX][COL_MAX], char buffer[BUFFER_MAX],
               int start_state, int& token_pos, string& token);

void init_table(int table[][COL_MAX]);
void mark_table(int table[][COL_MAX]);
void print_table(int table[][COL_MAX]);
void mark_cell(int row, int table[][COL_MAX], const char column[], int state);
void load(char nameOfFile[], int w[][COL_MAX]);
void mark_fail(int table[][COL_MAX], int state);
void mark_success(int table[][COL_MAX], int state);
string extractString(char buffer[], int start, int end);
void testState();
void testToken();
void testFTK();
void testList();
void testPair();
void testMap();

int main()
{
    cout <<  endl << "==============START==============" << endl;

    //testMap();
    //testPair();
    //testState();
    //testBoard();
    testFTK();
    //testList();
    //testToken();

    cout << endl << endl << "=================END================" <<endl;
    return 0;
}

void testMap(){
    cout<<endl<<endl;
    FTokenizer f("somefile.txt");
    Token t;
    Map <string, int> m;


    while (!f.done()){
        f>>t;
        cout<<"["<< t << "] ";
        m.Insert(t);
    }
    f.close_file();

    cout<<endl<<m;

//    List<Pair<int, string> >* l;
//    l = m.GetSortByValue();
//    l->Print();
}


void testFTK(){
    FTokenizer f("somefile.txt");
    Token t;

    while (!f.done()){
        f>>t;
        cout<<"["<< t << "] ";
        //cin.get();
    }
    f.close_file();
}


void testList(){
    List<int> l;

    l.InsertSorted(6);
    l.InsertSorted(2);
    l.InsertSorted(1);
    l.InsertSorted(5);
    l.InsertSorted(1);

    cout<<endl;
    cout<<"Your list: "<<l;
//    Map<//Pair's TYPE, occurrence>
}

void testPair(){
    Map<string, int> m;
    m.Insert("apple", 1);
    m.Insert("apple", 1);
    m.Insert("apple", 1);
    m.Insert("pizza", 1);
    m.Insert("pizza", 1);
    m.Insert("pizza", 1);
    m.Insert("chalupa", 1);
    m.Insert("log", 1);
    m.Insert("bat", 1);
    m.Insert("bat", 1);

    cout<<m;
    cout<<endl<<endl;

    List<Pair<int, string> >* l;
    cout<<endl<<"Sort By Value"<<endl;
    l = m.GetSortByValue();
    l->Print();
}

void testToken(){
    Token t;

    STokenizer stk("hi"
                   " there");
    //cout<<"Mary had 45.6 lambs"<<endl;

    //stk>>t;
    while(!stk.done()){
        stk>>t;
        cout<<"Token: ["<<t.token_string()<<"]      Type: ["<<t.type_string()<<"]"<<endl;
    }


}

void testState(){
//    int table[ROW_MAX][COL_MAX];

//    init_table(table);
//    mark_table(table);
    //print_table(table);

    //char buffer[BUFFER_MAX] = " my milkshake, brings";
//    int token_pos = 0;
//    string token;

//    while(token_pos < strlen(buffer)-1){
//        if(get_Token(table, buffer, START_DIGIT, token_pos, token)){
//            cout<<"main: ["<<token<<"]"<<endl;
//            continue;
//        }
//        if(get_Token(table, buffer, START_LETTER, token_pos, token)){
//            cout<<"main: ["<<token<<"]"<<endl;
//            continue;
//        }
//        if(get_Token(table, buffer, START_SPACE, token_pos, token)){
//            cout<<"main: ["<<token<<"]"<<endl;
//            continue;
//        }
//        cout<<endl<<"main: unrecognized token: ["<<buffer[token_pos]<<"] at pos: "<<token_pos<<endl;
//        token_pos++;
//    }
}

//pre: function takes a row in the table, the actual table, from what value
//     to what value, column of specific values and the state you want that
//     location to jump to. the table is already initialized, the row, state
//     and column is given from the outside
//post: marks each cell corresponding to the correct state and column
void mark_cell(int row, int table[][COL_MAX], const char column[], int state){
    for(int i=0; column[i]; i++){
        char c = column[i];
        //stores a character in columns[] at position i
        table[row][c] = state;
        //insert state
    }
}

//pre: takes an initialized 2D array
//post: the array table has now states marked in the correct cells
void mark_table(int table[][COL_MAX]){
    //MARK DIGITS
    mark_fail(table, 0);
    mark_success(table, 1);
    mark_fail(table, 2);
    mark_success(table, 3);

    mark_cell(0, table, DIGITS, 1);
    mark_cell(0, table, PERIOD, 2);
    mark_cell(1, table, DIGITS, 1);
    mark_cell(1, table, PERIOD, 2);
    mark_cell(2, table, DIGITS, 3);
    mark_cell(3, table, DIGITS, 3);

    //MARK SPACES
    mark_fail(table, 4);
    mark_success(table, 5);

    mark_cell(4, table, SPACES, 5);
    mark_cell(5, table, SPACES, 5);

    //MARK ALPHA
    mark_fail(table, 6);
    mark_success(table, 7);

    mark_cell(6, table, UPPER_ALPHA, 7);
    mark_cell(6, table, LOWER_ALPHA, 7);
    mark_cell(7, table, UPPER_ALPHA, 7);
    mark_cell(7, table, LOWER_ALPHA, 7);
}

void mark_fail(int table[][COL_MAX], int state){
    table[state][0]=0;
}

void mark_success(int table[][COL_MAX], int state){
    table[state][0]=1;
}

//pre: takes a state table, buffer(string), the starting
//     state for the particular machine, position of token,
//     and token string

//post: returns false or true if a token was found.
//      when this function returns a token, the cursor
//      will be left in the position that it hit the
//      fail state.
//      local variable start_position will be set equal
//      to position of token to hold the starting position
//      so after the token reaches a fail state, it will
//      take the length in between start_position and token_pos
bool get_Token(int table[ROW_MAX][COL_MAX], char buffer[BUFFER_MAX],
               int start_state, int& token_pos, string& token){

    int start_pos = token_pos;
    char key;
    int state;
    int rowState = start_state;
    int bufferLength = strlen(buffer);

    cout<<endl<<endl<<"*********DEBUG********"<<endl;
    if(start_state == 0){
        cout<<"[DIGIT LOOP]"<<endl;
    }
    if(start_state == 4){
        cout<<"[SPACE LOOP]"<<endl;
    }
    if(start_state == 6){
        cout<<"[LETTER LOOP]"<<endl;
    }
    cout<<"***********************"<<endl;

    //this for loop starts from the token_pos. the loop will exit
    //once a fail state is reached. a fail state means that you
    //do not have a token, or that you have a token and reached
    //a non-matching token. this will be differentiated by comparing
    //if the starting position and token position
    for(int walker=token_pos; walker<bufferLength; walker++){
        key = buffer[walker];
        //store character into key

        cout<<endl<<"[ENTERED GET_TOKEN FORLOOP]"<<endl;
        cout<<endl<<"**ROW STATE** = "<<start_state<<endl;
        cout<<"CURRENT KEY: "<<key<<endl;
        cout<<"START POSITION: "<<start_pos<<endl;
        cout<<"TOKEN POSITION: "<<walker<<endl;
        cout<<"CURRENT STATE: "<<rowState;
        //cout<<endl<<"==================================================="<<endl;

        int key_ASCII = (int) key+1;
        //convert to ASCII
        cout<<endl<<"ASCII KEY: "<<key_ASCII<<endl;
        cout<<endl<<"table[rowState][key_ASCII] = "<<table[rowState][key_ASCII];

        state=table[rowState][key_ASCII];

        //cout<<endl<<"==============================="<<endl;
        cout<<endl<<"TRAVERSE TABLE, FOUND STATE: "<<state;
        //cout<<endl<<"UPDATING ROWSTATE FROM "<<rowState<<" TO "<<table[rowState][key_ASCII];

        cout<<endl<<"start_pos: "<<start_pos<<endl;
        cout<<"token_pos: "<<token_pos;
        cout<<endl<<"walker_pos: "<<walker<<endl;
        cout<<endl<<"bufferLength: "<<bufferLength;

        cout<<endl<<"CHECKING STATE..." <<table[state][key_ASCII];
        if(state == FAIL){
            cout<<endl<<"[STATE HAS FAILED]";
            if(start_pos==walker){
                cout<<endl<<"[POSITION HASN'T MOVED, RETURNING FALSE]";
                //leave token position
                return false;
            }
            else{
                cout<<endl<<"[POSITION MOVED, TOKEN DETECTED]"<<endl;
                token_pos=walker;
                token = extractString(buffer, start_pos, token_pos);

                cout<<endl<<"TOKEN IS AT: "<<token_pos<<endl;
                cout<<endl<<"EXITING FUNCTION "<<endl;
                return true;
            }
        }
        else{
            cout<<endl<<"[STATE IS SUCCESS]"<<endl;
            rowState=table[state][key_ASCII];
            if(walker == bufferLength-1){
                //need a return statement while in a success state
                //and this is only possible if walker is at the end of the buffer
                token_pos = walker;
                token = extractString(buffer, start_pos, token_pos+1);
                return true;
            }
        }
    }
}

//pre: takes the buffer, starting position of the substring, and ending position of substring
//post: creates a char array with corresponding length and stores the characters individually
//      checks the ending index where loop needs to have 1 more iteration
string extractString(char buffer[], int start, int end){
    cout<<endl<<"*******ENTERED extractString*******"<<endl;
    int bufferLength = strlen(buffer);
    int stringLength = end-start;

    cout<<"end: "<<end<<endl;
    cout<<"start: "<<start<<endl;
    cout<<"length: "<<stringLength<<endl;

    char result[stringLength];

    for(int i=0, j=start; i<stringLength; i++, j++){
        //if(end == bufferLength-1){stringLength+=1;}
        result[i] = buffer[j];
        cout<<endl<<"i: "<<i<<" j: "<<j<<endl;
        cout<<"result: "<<result[i];
        cout<<endl<<"buffer: "<<buffer[j];
    }
    cout<<endl<<"EXTRACTED. RETURNING STRING"<<endl;
    cout<<"***********************************"<<endl;

    string str(result, stringLength);
    return str;
}

void load(char nameOfFile[], int w[][COL_MAX]){
    ifstream openFile;
    openFile.open(nameOfFile);
    //open the file

    for(int i = 0; i<ROW_MAX; i++){
        for(int j = 0; j<COL_MAX; j++){
            openFile >> w[i][j];
            //process each character
        }
    }
    openFile.close();
    //close the file after opening

    //init_table(w);
    for(int i = 0; i<ROW_MAX; i++){
        for(int j = 0; j<COL_MAX; j++){
            cout << w[i][j] << " ";
        }
        cout<<endl;
    }
}


//pre: takes a 2D array size 5x10
//post: initializes every element in the array with -1
void init_table(int table[][COL_MAX]){
    //initialize graph table
    for(int i=0; i<ROW_MAX; i++){
        for(int j=0; j<COL_MAX; j++){
            table[i][j] = -1;
        }
    }
}

//pre: takes a 2D array
//post: outputs the array
void print_table(int table[][COL_MAX]){
    cout<<endl<<"printing table:"<<endl;
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
