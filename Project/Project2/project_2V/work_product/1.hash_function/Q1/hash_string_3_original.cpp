// variation on Program 14.2 from the textbook
// - modified to work with std::string
// for more details see program 12.

#include <cstdlib>
#include <string>

std::size_t hash( std::string const& s ) {
  char const* data = s.c_str();
  std::size_t hash;
  std::size_t a = 31415U;
  std::size_t b = 27183U;

  for ( hash = 0; *data != 0; ++data, a = a * b % 25165843U )
    hash = a * hash + *data;
  
  return hash;
}

int main() {

  std::string s1 = "Tigers";
  std::string s2 = "Tigers are GRRRRREAT!";
  std::string s3 = "Leopards";

  printf( "%x\n", hash( s1 ) );
  printf( "%x\n", hash( s2 ) );
  printf( "%x\n", hash( s3 ) );

  return 0;
}
  
