#ifndef FTOKENIZER_H
#define FTOKENIZER_H
#include "stokenizer.h"
#include <fstream>

//FIX APOSTROPHE
class FTokenizer
{
public:
    FTokenizer();
    FTokenizer(string f);

    friend FTokenizer& operator >> (FTokenizer& f, Token& t);
    Token full_token(Token& t);
    bool done(); //F are you done filling the block
    void new_block(); //gets new block of string
    void close_file();

private:
    STokenizer stk;
    ifstream file;
    string fileName;
    //string hold;
    bool endOfFile;
    int f_pos;
};

FTokenizer::FTokenizer(){
    cout<<"FTok ctor"<<endl;
    f_pos = 0;
    fileName = " ";
    endOfFile = false;

}

FTokenizer::FTokenizer(string f){
    f_pos = 0;
    endOfFile = false;
    fileName = f;

    file.open(fileName);

    if(!file){
        cout<<endl<<"Error"<<endl;
    }
    else{
        cout<<endl<<"Opened"<<endl;
        new_block();
    }

}

//JOB: TELLS STK TO KEEP GIVING ME TOKENS
//     PROVIDED THAT I GIVE STK BLOCKS OF TEXT
FTokenizer& operator >> (FTokenizer& f, Token& t){
    //cout<<endl<<"[FTK >> OPERATOR]";
    //int token_length;

    if(!f.stk.done()){
        //cout<<"stk is not done"<<endl;
        //f.stk.printpos();
        f.stk >> t;
        //cout<<endl<<"got token"<<endl;
        //if STK is not done, get a token
    }
    else{
        //else if file is not done, give a new block
        if(!f.file.eof()){
            //cout<<endl<<"new block"<<endl;
            f.new_block();
            f.stk >> t;
            //need this or it will get the last token of the last
            //block as part of this new block
        }
    }
    return f;
}

bool FTokenizer::done(){
    if(file.eof() && stk.done()){
        return true;
    }
    else{
        return false;
    }
}

void FTokenizer::close_file(){
    file.close();
}

//pre: This function creates a new block for stk
//post: stk must reset its position
void FTokenizer::new_block(){
    //cout<<"pos in new block: ";
    //stk.printpos();
    //cout<<endl<<"NEW_BLOCK ENTERED"<<endl;

    char buffer[BUFFER_MAX+1];
    file.read(buffer, BUFFER_MAX);
    buffer[file.gcount()]=NULL;
    cout<<endl<<"FTK new_block: ["<<buffer<<"]";
    //stk.printpos();

    stk.input_buffer(buffer);
    stk.reset_position();


    //cout<<endl<<"f_pos is at "<<f_pos<<endl;
}


//        token_length = t.token_string().length();
//        cout<<endl<<"f_pos: "<<f.f_pos<<endl;
//        if(f.f_pos == LAST_INDEX - token_length && t.type_string()!="SPACE"){
//            cout<<"entered last_index condition"<<endl;
//            f.hold = t.token_string();
//            t = Token(" ", UNKNOWN);

//            cout<<endl<<"f.hold = "<<f.hold<<endl;
//        }
//        else if(f.f_pos == BUFFER_MAX && t.type_string()!="SPACE"){
//            cout<<"entered first_index condition"<<endl;
//            string combinedToken;
//            combinedToken = f.hold+t.token_string();
//            t = Token(combinedToken, t.get_type());
//        }
#endif // FTOKENIZER_H
