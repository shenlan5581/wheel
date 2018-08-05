#include "file.h"

using File::File_S;

using std::cout;

int main() {
File_S file("./file.txt");
cout<<file.GetContent();
file.Addition("yuxinji");
cout<<file.GetContent();


}
