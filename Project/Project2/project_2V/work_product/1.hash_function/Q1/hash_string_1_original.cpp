#include <cstdlib>
#include <string>

std::size_t hash( std::string const& s ) {
  std::size_t value = 0xC965AF37U;
  
  std::string::const_iterator iter = s.begin();
  std::string::const_iterator end = s.end();
  while ( iter != end ) {
    std::size_t mid = ((value & 0x000000FFU) ^ *iter++) << 9;
    std::size_t lo = value >> 23;
    value = ((value << 9) & 0xFFFE0000U) | mid | lo;
  }
  return value;
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
  
