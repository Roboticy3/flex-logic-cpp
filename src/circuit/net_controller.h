#pragma once

#include "collections/llabeling.h"
#include "circuit/circuit.h"

template<typename S, typename T>
class net_controller {
  circuit<S, T> *nc;

  /*
  Attach pin label `pid` to net `p_net`. If `at` is -1, the pin is attached onto
  the end.

  Returns false if `p_net` is null, or if the pin connected at index `at` is
  already `pid`.

  If `pid` is already connected, but at a different index, it is swapped to `at`

  If a pin is already connected at index `at`, it is disconnected.

  O(q) for q connections on p_net
  */
  bool attach_pin(net *p_net, ll pid, size_t at=-1);
  /*
  Detach pin label `pid` from `p_net`.

  Returns false if `p_net` is null or if `pid` was not already connected.

  O(q) for q connections on p_net
  */
  bool detach_pin(net *p_net, ll pid);
  /*
  Attach net label `nid` to `p_pin`, sorting `nid` into `p_pin`'s connections.
  
  Assumes `p_pin`'s connections are already sorted.

  If `p_pin` does not exist or `nid` is already connected, return false.

  O(q) for q connections on p_pin
  */
  bool attach_net(pin<S> *p_pin, ll nid);
  /*
  Detach net label `nid` from `p_pin`.

  Assumes `p_pin`'s connections are already sorted.

  Returs false if `p_pin` does not exist of `nid` is not already connected.

  O(q) for q connections on p_pin
  */
  bool detach_net(pin<S> *p_pin, ll nid);

  public:
    /*
    Attach net `nid` to pin `pid`. 

    If either labels are invalid, or the connection between `nid` and `pid`
    already exists at socket `at` on net `nid`, return false.

    If a connection already exists, but at a different index, that socket is
    swapped with the socket `at`.

    O(q) for q average connections on circuit components
    */
    bool attach(ll nid, ll pid, size_t at=-1);

    /*
    Detach net `nid` from pin `pid`

    If either labels are invalid, or no connection exists between the ids,
    return false.
    */
    bool detach(ll nid, ll pid);
};
