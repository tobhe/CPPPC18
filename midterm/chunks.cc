#include "chunks.h"
#include <cstdint>
#include <vector>

int main() {
  std::vector<uint16_t> v_us;

  //                                    ,-- wrapped container
  //                                    |
  cpppc::chunks<128, uint16_t, std::vector<uint16_t>> v_chunks(v_us);
  //             |      |
  //             |      '-- element type
  //             |
  //             '-- maximum size of a
  //                 single chunk in bytes

  // Iterate chunks:
  auto first_chunk = v_chunks.begin();
  // auto chunk_size  = std::distance(v_chunks.begin(), v_chunks.end());
  // --> 128/(16/8) = 64

  // Iterators on elements in a chunk:
  uint16_t first_chunk_elem = *(*first_chunk).begin();
  uint16_t third_chunk_elem = first_chunk[2];

  // Pointer to data in second chunk:
  uint16_t * chunk_1_data = v_chunks[1].data();
  // Pointer to data in third chunk (= end pointer of data in second chunk):
  uint16_t * chunk_2_data = v_chunks[2].data();

  return 0;
}
