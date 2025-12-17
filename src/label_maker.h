#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

using namespace godot;

/*
Memoryless mapping between a label type and strings.
*/
class LabelMaker : public RefCounted {
  GDCLASS(LabelMaker, RefCounted)

  int base = 26;
  int offset = 'A';
  
  protected:
    static void _bind_methods();
    
  public:
    LabelMaker() = default;
	  ~LabelMaker() override = default;

    /*
      0   ->  A
      .
      .
      25  ->  Z
      26  ->  AA
      .
      .
      51  ->  AZ
    */
    String label(int of);
    /*
      Inverse of label
      A   ->  0
      .
      .
      Z   ->  25
      AA  ->  26
      .
      .
      AZ  ->  51
    */
    int index(String of);
};