#include "chunks.h"
#include <cstdint>
#include <vector>
#include <iostream>

int main() {
  std::vector<uint16_t> v_us = {1, 2, 3, 4, 5, 5, 5, 5, 6, 6, 6, 6};

  //                                    ,-- wrapped container
  //                                    |
  cpppc::chunks<8, uint16_t, std::vector<uint16_t>> v_chunks(v_us);
  //             |      |
  //             |      '-- element type
  //             |
  //             '-- maximum size of a
  //                 single chunk in bytes

  // Iterate chunks:
  auto first_chunk = v_chunks.begin();
  auto num_chunks  = std::distance(v_chunks.begin(), v_chunks.end());

  std::cout << "Distance: " << num_chunks << '\n';

  // Iterators on elements in a chunk:
  uint16_t first_chunk_elem = *(*first_chunk).begin();

  std::cout << "First element: " << first_chunk_elem << '\n';

  uint16_t third_chunk_elem = first_chunk[2];

  std::cout << "Third element: " << third_chunk_elem << '\n';

  // Pointer to data in second chunk:
  uint16_t * chunk_1_data = v_chunks[1].data();

  // Pointer to data in third chunk (= end pointer of data in second chunk):
  uint16_t * chunk_2_data = v_chunks[2].data();

  return 0;
}
