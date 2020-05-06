#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(string str, int target_length)
{
  string left = string(str, 0, target_length);
  string right = string(str, target_length, str.size() - target_length);
  vector<string> res = { left };
  if (right.size() >= target_length)
  {
    vector<string> res1 = split(right, target_length);
    for (auto &i : res1)
    {
      res.push_back(i);
    }
  }
  else
  {
    res.push_back(right);
  }
  return res;
}

vector<string> read(ifstream& input, int target_length)
{
  vector<string> text;
  string line;
  if (input.is_open())
  {
    while (getline(input, line))
    {
      istringstream stream(line);
      while (!stream.eof())
      {
        string word;
        stream >> word;
        if (word.size() >= target_length)
        {
          vector<string> elem = split(word, target_length);
          for (auto &var : elem)
          {
            text.push_back(var);
          }
        }
        else
        {
          text.push_back(word);
        }
      }
    }
  }
  return text;
}

void print(vector<string> text, int target_length)
{
  ofstream out("__FORMATTED__.txt");
  int current_len = 0;
  string lin;
  for (string i : text)
  {
    if (current_len + i.size() > target_length)
    {
      int offset = target_length / 2 - current_len / 2;
      for (int j = 0; j < offset; j++)
      {
        out << " ";
      }
      out << lin << "\n";
      lin = string();
      current_len = 0;
    }
    else
    {
      lin += i += " ";
      current_len += i.size() + 1;
    }
  }
}

int main(int argc, char* argv[])
{
  ifstream input(argv[1]);
  int target_length = atoi(argv[2]);
  vector<string> text = read(input, target_length);
  print(text, target_length);
  return 0;
}