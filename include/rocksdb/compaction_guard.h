
#ifndef STORAGE_ROCKSDB_INCLUDE_COMPACTION_GUARD_H_
#define STORAGE_ROCKSDB_INCLUDE_COMPACTION_GUARD_H_

#include <vector>
#include <string>

namespace rocksdb {

    class Slice;

    class CompactionGuard {
    public:
        virtual ~CompactionGuard() {}
        // Get guards for compaction, the result must be ordered.
        virtual std::vector<std::string> GetGuardsInRange(Slice *start, Slice *end) = 0;
    };

}

#endif
