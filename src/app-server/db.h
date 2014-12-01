#ifndef __SERVER__DB_H_INCLUDED__
#define __SERVER__DB_H_INCLUDED__

#include "shared/data.h"
#include <algorithm>
#include <iterator>

class db {
  public:
    explicit db();

    explicit db(const db& other) = delete;
    db &operator=(const db& other) = delete;

    explicit db(db &&other) = delete;
    db &operator=(db &&other) = delete;

    const shared::people all() const;

    template<typename T>
    const shared::people lookup(const T &query) const {
      shared::people result;
      std::copy_if(
          data.begin(),
          data.end(),
          std::back_inserter(result),
          query);

      return result;
    }

    const shared::stats stats() const;

    void upsert(const shared::person &person);

    ~db();

  private:
    shared::people data;
};

#endif
