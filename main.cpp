#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tgmath.h>
#include <cctype>

using namespace std;

bool vector_check(vector<char> input_vector, char input_key);
bool word_check(vector<char> input_vector, string input_key);
bool action_permission(char input_char);
bool char_unique(string input_string, char input_char);
void display_instructions();
void compute_string(vector<std::string> input_vector);

int main() { //int argc, const char * argv[]
    
    cout<<"fetching data ..."<<endl;
    
    vector<std::string> words{};
    vector<std::string> words_short{};
    vector<std::string> words_expanded{};
    vector<char> chars_excluded{};
    vector<char> used_vowels{};
    vector<char> vowels_excluded{};
    vector<int> words_score{};
    string tmp_word;
    ifstream dictionary_list_expanded("/Users/vladi/Documents/files/files/ideas/dictionary/dictionary/words_definitions.txt");
    ifstream dictionary_list("/Users/vladi/Documents/files/files/ideas/dictionary/dictionary/words_dictionary.txt");
    bool word_match=false, debug_mode=false, definition_found=false;
    char vowels[5]={'a', 'e', 'o', 'i', 'u'};
    char input[5];
    char debug_mode_input, optimal_string_input;
    int output[5];
    int words_coef_match=1;
    int words_coef_contains=1;
    string debug_string;
    
    if (dictionary_list_expanded.is_open()){
        while (getline(dictionary_list_expanded, tmp_word)){
            words_expanded.push_back(tmp_word);
        }
        dictionary_list_expanded.close();
    }else{
        cout<<"error loading dictionary - definitions"<<endl;
        exit (EXIT_FAILURE);
    }
    
    if (dictionary_list.is_open()){
        while (getline(dictionary_list, tmp_word)){
            words.push_back(tmp_word);
        }
        dictionary_list.close();
        cout<<"fetching complete ... "<<words.size()+words_expanded.size()<<" objects loaded"<<endl;
    }else{
        cout<<"error loading dictionary - list"<<endl;
        exit (EXIT_FAILURE);
    }
    
    for (int i=0; i<words.size(); i++){
        if (words[i].size()==8){
            words_short.push_back(words[i]);
        }
    }
    
    for (int i=0; i<words_short.size(); i++){
        words_score.push_back(0);
    }
    
    cout<<"proceed in debug mode (Y/n): ";
    cin>>debug_mode_input;
    
    if (action_permission(debug_mode_input)){
        cout<<"trace word: ";
        cin>>debug_string;
        debug_mode=true;
    }
    
    cout<<"compute optimal starting word (Y/n): ";
    cin>>optimal_string_input;
    
    if (action_permission(optimal_string_input)){
        compute_string(words_short);
    }
    
    if (debug_mode){
        for (int i=0; i<words_expanded.size(); i++){
            cout<<"INDEX ... "<<i<<" ... "<<words_expanded[i]<<endl;
        }
    }
    display_instructions();
    
    while (!word_match){
        
        cout<<"input: ";

        for (int i=0; i<5; i++){
            cin>>input[i];
        }
        
        cout<<"output: ";
        
        for (int i=0; i<5; i++){
            cin>>output[i];
        }
        cout<<"indexing ..."<<endl;
        for (int i=0; i<words_short.size(); i++){
            if (debug_mode){
                if (words_short[i].find(debug_string)!=std::string::npos){
                    string debug_tmp_string=words_short[i];
                    debug_tmp_string.erase(std::remove(debug_tmp_string.begin(), debug_tmp_string.end(), '\n'), debug_tmp_string.cend());
                    cout<<"STRING ... "<<debug_tmp_string;
                }
            }
            for (int c=0; c<5; c++){
                if (debug_mode){
                    if (words_short[i].find(debug_string)!=std::string::npos){
                        string debug_tmp_string=words_short[i];
                        debug_tmp_string.erase(std::remove(debug_tmp_string.begin(), debug_tmp_string.end(), '\n'), debug_tmp_string.cend());
                        cout<<"[CHAR ... "<<input[c]<<" INDEX ... "<<c<<"] ";
                    }
                }
                switch(output[c]){
                    case 0:
                        if (words_short[i].find(input[c])!=std::string::npos){
                            words_score[i]=words_score[i]-36;
                            for (int b=0; b<5; b++){
                                if (input[c]==vowels[b]){
                                    vowels_excluded.push_back(input[c]);
                                }
                            }
                        }else{
                            words_score[i]=words_score[i]+10;
                        }
                        chars_excluded.push_back(input[c]);
                        if (debug_mode){
                            if (words_short[i].find(debug_string)!=std::string::npos){
                                cout<<"[CASE 0 ... VALUE ... "<<words_score[i]<<"] ";
                            }
                        }
                        break;
                    case 1:
                        if (words_short[i].at(c+2)==input[c]){
                            words_score[i]=words_score[i]-36;
                        }else{
                            if (words_short[i].find(input[c])!=std::string::npos){
                                if (word_check(chars_excluded, words_short[i])){
                                    words_score[i]=words_score[i]+2*pow(words_coef_match, 2);
                                    words_coef_match++;
                                }else{
                                words_score[i]=words_score[i]-36;
                                }
                            }
                        }
                        if (debug_mode){
                            if (words_short[i].find(debug_string)!=std::string::npos){
                                cout<<"[CASE 1 ... VALUE ... "<<words_score[i]<<"] ";
                            }
                        }
                        break;
                    case 2:
                        if (words_short[i].at(c+2)==input[c]){
                            if (word_check(chars_excluded, words_short[i])){
                                words_score[i]=words_score[i]+(9*pow(words_coef_contains, 3));
                                words_coef_contains++;
                            }else{
                                words_coef_contains=1;
                                words_score[i]=words_score[i]-67;
                            }
                        }else{
                            if (words_short[i].find(input[c])!=std::string::npos){
                                words_score[i]=words_score[i]+3;
                            }else{
                                words_score[i]=words_score[i]-67;
                            }
                        }
                        if (debug_mode){
                            if (words_short[i].find(debug_string)!=std::string::npos){
                                cout<<"[CASE 2 ... VALUE ... "<<words_score[i]<<" COEF ... "<<words_coef_contains<<"] ";
                            }
                        }
                        break;
                    default:
                        cout<<"input mismatch"<<endl;
                        break;
                }
                if (debug_mode){
                    if (words_short[i].find(debug_string)!=std::string::npos){
                        cout<<endl;
                    }
                }
            }
            for (int b=0; b<5; b++){
                if (!(vector_check(vowels_excluded, vowels[b]))){
                    if (words_short[i].find(vowels[b])!=std::string::npos){
                        if (char_unique(words_short[i], vowels[b])){
                            words_score[i]=words_score[i]+1;
                        }
                    }
                }
            }
            words_coef_contains=1;
            words_coef_match=1;
        }
        
        for (int i=0; i<words_score.size(); i++){
            for (int c=i+1; c<words_score.size(); c++){
                if (words_score[i]<words_score[c]){
                    int tmp_int=words_score[c];
                    words_score[c]=words_score[i];
                    words_score[i]=tmp_int;
                    
                    string tmp_string=words_short[c];
                    words_short[c]=words_short[i];
                    words_short[i]=tmp_string;
                }
            }
        }
        
        cout<<endl;
        if (debug_mode){
            char tmp_char_input;
            cout<<"display matching words (Y/n): ";
            cin>>tmp_char_input;
            if (action_permission(tmp_char_input)){
                for (int i=0; i<20; i++){
                    cout<<words_short[i]<<" ... "<<words_score[i]<<endl;
                }
            }
        }else{
            for (int i=0; i<20; i++){
                //cout<<words_short[i]<<" ... "<<words_score[i]<<endl;
                for (int c=0; c<words_expanded.size(); c++){
                    if (words_expanded[c].size()>5){
                        string tmp_string=words_expanded[c].substr(0, 5);
                        transform(tmp_string.begin(), tmp_string.end(), tmp_string.begin(),
                            [](unsigned char c){ return std::tolower(c); });
                        if (words_short[i].find(tmp_string)!=std::string::npos&&isspace(words_expanded[c].at(5))){
                            cout<<"#  "<<words_score[i]<<words_short[i]<<words_expanded[c].substr(5, words_expanded[c].size()-5)<<" ... "<<endl;
                            definition_found=true;
                            break;
                        }
                    }
                }
                if (!definition_found){
                    cout<<"#  "<<words_score[i]<<words_short[i]<<" no information available ... "<<endl;
                }else{
                    definition_found=false;
                }
                cout<<endl;
            }
        }
        
        if (debug_mode){
            for (int i=0; i<words_short.size(); i++){
                if (words_short[i].find(debug_string)!=std::string::npos){
                    cout<<endl<<"STRING ..."<<words_short[i]<<"FVALUE ...  "<<words_score[i]<<endl;
                }
            }
        }
        
        int tmp=0;
        
        for (int i=0; i<5; i++){
            if (output[i]==2){
                tmp++;
            }
        }
        
        if (tmp==5){
            cout<<"words match successful, restart session (Y/n): ";
            char user_input;
            cin>>user_input;
            switch(user_input){
                case 'Y':
                case 'y':
                    word_match=false;
                    break;
                case 'N':
                case 'n':
                    cout<<"cleaning up ..."<<endl;
                    word_match=true;
                    break;
                default:
                    cout<<"input not recognized ... "<<endl;
                    word_match=true;
                    break;
                    
            }
        }
    }
    return 0;
}

bool vector_check(vector<char> input_vector, char input_key){
    for (int i=0; i<input_vector.size(); i++){
        if (input_vector[i]==input_key){
            return true;
        }
    }
    return false;
}

bool word_check(vector<char> input_char, string input_key){
    for (int i=0; i<input_char.size(); i++){
        if (input_key.find(input_char[i])!=std::string::npos){
            return false;
        }
    }
    return true;
}

bool action_permission(char input_char){
    switch(input_char){
        case 'Y':
        case 'y':
            return true;
            break;
        case 'N':
        case 'n':
            return false;
            break;
        default:
            cout<<"input mismatch ... proceeding in normal mode ..."<<endl;
            return false;
            break;
    }
}

bool char_unique(string input_string, char input_char){
    int char_occurance=0;
    for (int i=0; i<input_string.size(); i++){
        if (input_string.at(i)==input_char){
            char_occurance++;
        }
    }
    if (char_occurance==1){
        return true;
    }else{
        return false;
    }
}

void display_instructions(){
    cout<<"caution: output 0 - no match, 1 - match/wrong location, 2 - match/right location"<<endl;
    cout<<"caution: use space between charachters for input/output (ex. w o r d / 1 0 2 2)"<<endl;
    cout<<"caution: words scored and displayed in descending order"<<endl;
}

void compute_string(vector<std::string> input_vector){
    
    cout<<"computing ..."<<endl;
    
    vector<char> alphabet_chars;
    vector<int> words_score;
    int char_frequency[30];
    
    for (int i=0; i<input_vector.size(); i++){
        words_score.push_back(0);
    }
    
    for (int i=0; i<30; i++){
        char_frequency[i]=0;
    }
    
    for (int i=97; i<123; i++){
        char tmp_char=i;
        alphabet_chars.push_back(tmp_char);
    }
    
    for (int i=0; i<input_vector.size(); i++){
        for (int x=0; x<alphabet_chars.size(); x++){
            if (input_vector[i].find(alphabet_chars[x])!=std::string::npos){
                char_frequency[x]++;
            }
        }
    }
    
    for (int i=0; i<input_vector.size(); i++){
        for (int x=0; x<alphabet_chars.size(); x++){
            if (input_vector[i].find(alphabet_chars[x])!=std::string::npos){
                words_score[i]=words_score[i]+char_frequency[x];
            }
        }
    }
    
    for (int i=0; i<words_score.size(); i++){
        for (int c=i+1; c<words_score.size(); c++){
            if (words_score[i]<words_score[c]){
                int tmp_int=words_score[c];
                words_score[c]=words_score[i];
                words_score[i]=tmp_int;
                
                string tmp_string=input_vector[c];
                input_vector[c]=input_vector[i];
                input_vector[i]=tmp_string;
            }
        }
    }
    
    for (int i=0; i<10; i++){
        cout<<input_vector[i]<<" ... "<<words_score[i]<<endl;
    }
}
