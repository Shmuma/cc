#include <iostream> 
#include <vector> 
#include <string> 
using namespace std; 

void print(vector<char> & sequence) 
{ 
    for(int i=0;i<sequence.size()-1;i++) 
        cout << sequence[i] << " "; 
    if(sequence.size()!=0) cout << sequence[sequence.size()-1] << endl; 
} 
void moveback(vector<char> & word) 
{ 
   if(word.size()>0) { 
      for(int i=0;i<word.size()-1;i++) 
         word[i]=word[i+1]; 
      word.pop_back(); 
   } 
} 
void find(const vector<char> original, vector<char> holder, vector<char> objective, 
        vector<char> sequence, int size, vector<vector<char> > & answers) 
{ 
   vector<char> a = original, b = holder, c = objective, d = sequence; 
   d.push_back('o'); 
   b.pop_back(); moveback(c); 
   if(c.size()==0) 
      answers.push_back(d); 
   else { 
      int count = size; 
      for(int i=0;i<=count;i++) { 
          if(c.size () && b.size () && b.back()==c[0]) 
            find(a,b,c,d,size,answers); 
         if(i==count) return; 
         d.push_back('i'); 
         b.push_back(a[0]); 
         moveback(a); 
         size--; 
      } 
   } 
} 
bool missing(vector<char> original, vector<char> objective) 
{ 
   string temp; 
   for(int a=0;a<original.size();a++) 
      temp+=original[a]; 
   for(int i=0;i<objective.size();i++) { 
      int loc = temp.find(objective[i]); 
      if(loc==string::npos) 
         return true; 
   } 
   return false; 
} 
int main() 
{ 
    vector<char> original, objective, sequence; char ch; int length=0; 
   int length2=0; 
    while(cin.get(ch)) { 
        length++; 
        original.push_back(ch); 
        cin.get(ch); 
        while(ch!='\n') { 
            length++; 
            original.push_back(ch); 
            cin.get(ch); 
        } 
        cin.get(ch); 
        while(ch!='\n') { 
            objective.push_back(ch); 
            length2++; 
            cin.get(ch); 
        } 
      cout << "[" << endl; 
      if(!missing(original,objective) && length==length2) { 
         vector<vector<char> > answers; 
         sequence.push_back('i'); 
         vector<char> holder; 
         holder.push_back(original[0]); 
         moveback(original); 
         int size = length-1; 
         int count = size; 
         for(int i=0;i<=count;i++) { 
            if(holder.back()==objective[0]) 
               find(original,holder,objective,sequence,size,answers); 
            if(i!=count) { 
               sequence.push_back('i'); 
               holder.push_back(original[0]); 
               moveback(original); 
               size--; 
            } 
         } 
         if(answers.size()>0) 
            for(int j=answers.size()-1;j>=0;j--) { 
               print(answers[j]); 
               answers[j].clear(); 
            } 
         answers.resize(0); 
      } 
      cout << "]" << endl; 
        length=0; length2=0; objective.clear(); sequence.clear(); original.clear(); 
    } 
    return 0; 
}
