#ifndef __RAII__MSGQUEUE_OWNER_H_INCLUDED__
#define __RAII__MSGQUEUE_OWNER_H_INCLUDED__

namespace raii {
  class msgqueue_owner {
    public:
      explicit msgqueue_owner();

      explicit msgqueue_owner(const msgqueue_owner& other) = delete;
      msgqueue_owner &operator=(const msgqueue_owner& other) = delete;

      explicit msgqueue_owner(msgqueue_owner &&other) = delete;
      msgqueue_owner &operator=(msgqueue_owner &&other) = delete;

      int id() const;

      ~msgqueue_owner();

    private:
      int identifier;
  };
}

#endif
