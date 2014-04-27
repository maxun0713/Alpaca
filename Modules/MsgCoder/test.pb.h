// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test.proto

#ifndef PROTOBUF_test_2eproto__INCLUDED
#define PROTOBUF_test_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_test_2eproto();
void protobuf_AssignDesc_test_2eproto();
void protobuf_ShutdownFile_test_2eproto();

class TestMsg;

// ===================================================================

class TestMsg : public ::google::protobuf::Message {
 public:
  TestMsg();
  virtual ~TestMsg();

  TestMsg(const TestMsg& from);

  inline TestMsg& operator=(const TestMsg& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TestMsg& default_instance();

  void Swap(TestMsg* other);

  // implements Message ----------------------------------------------

  TestMsg* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TestMsg& from);
  void MergeFrom(const TestMsg& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 dumb = 1;
  inline bool has_dumb() const;
  inline void clear_dumb();
  static const int kDumbFieldNumber = 1;
  inline ::google::protobuf::int32 dumb() const;
  inline void set_dumb(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:TestMsg)
 private:
  inline void set_has_dumb();
  inline void clear_has_dumb();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 dumb_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_test_2eproto();
  friend void protobuf_AssignDesc_test_2eproto();
  friend void protobuf_ShutdownFile_test_2eproto();

  void InitAsDefaultInstance();
  static TestMsg* default_instance_;
};
// ===================================================================


// ===================================================================

// TestMsg

// optional int32 dumb = 1;
inline bool TestMsg::has_dumb() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TestMsg::set_has_dumb() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TestMsg::clear_has_dumb() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TestMsg::clear_dumb() {
  dumb_ = 0;
  clear_has_dumb();
}
inline ::google::protobuf::int32 TestMsg::dumb() const {
  return dumb_;
}
inline void TestMsg::set_dumb(::google::protobuf::int32 value) {
  set_has_dumb();
  dumb_ = value;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_test_2eproto__INCLUDED
