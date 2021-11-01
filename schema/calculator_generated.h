// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_CALCULATOR_CALCULATOR_SCHEMA_H_
#define FLATBUFFERS_GENERATED_CALCULATOR_CALCULATOR_SCHEMA_H_

#include "flatbuffers/flatbuffers.h"

namespace calculator {
namespace schema {

struct CalculatorData;
struct CalculatorDataBuilder;
struct CalculatorDataT;

enum CalculatorType : int8_t {
  CalculatorType_AddCalculator = 0,
  CalculatorType_SubtractCalculator = 1,
  CalculatorType_MultiplyCalculator = 2,
  CalculatorType_DivideCalculator = 3,
  CalculatorType_MIN = CalculatorType_AddCalculator,
  CalculatorType_MAX = CalculatorType_DivideCalculator
};

inline const CalculatorType (&EnumValuesCalculatorType())[4] {
  static const CalculatorType values[] = {
    CalculatorType_AddCalculator,
    CalculatorType_SubtractCalculator,
    CalculatorType_MultiplyCalculator,
    CalculatorType_DivideCalculator
  };
  return values;
}

inline const char * const *EnumNamesCalculatorType() {
  static const char * const names[5] = {
    "AddCalculator",
    "SubtractCalculator",
    "MultiplyCalculator",
    "DivideCalculator",
    nullptr
  };
  return names;
}

inline const char *EnumNameCalculatorType(CalculatorType e) {
  if (flatbuffers::IsOutRange(e, CalculatorType_AddCalculator, CalculatorType_DivideCalculator)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesCalculatorType()[index];
}

struct CalculatorDataT : public flatbuffers::NativeTable {
  typedef CalculatorData TableType;
  std::string originalEquation{};
  float answer = 0.0f;
  calculator::schema::CalculatorType type = calculator::schema::CalculatorType_AddCalculator;
};

struct CalculatorData FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef CalculatorDataT NativeTableType;
  typedef CalculatorDataBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ORIGINALEQUATION = 4,
    VT_ANSWER = 6,
    VT_TYPE = 8
  };
  const flatbuffers::String *originalEquation() const {
    return GetPointer<const flatbuffers::String *>(VT_ORIGINALEQUATION);
  }
  flatbuffers::String *mutable_originalEquation() {
    return GetPointer<flatbuffers::String *>(VT_ORIGINALEQUATION);
  }
  float answer() const {
    return GetField<float>(VT_ANSWER, 0.0f);
  }
  bool mutate_answer(float _answer) {
    return SetField<float>(VT_ANSWER, _answer, 0.0f);
  }
  calculator::schema::CalculatorType type() const {
    return static_cast<calculator::schema::CalculatorType>(GetField<int8_t>(VT_TYPE, 0));
  }
  bool mutate_type(calculator::schema::CalculatorType _type) {
    return SetField<int8_t>(VT_TYPE, static_cast<int8_t>(_type), 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_ORIGINALEQUATION) &&
           verifier.VerifyString(originalEquation()) &&
           VerifyField<float>(verifier, VT_ANSWER) &&
           VerifyField<int8_t>(verifier, VT_TYPE) &&
           verifier.EndTable();
  }
  CalculatorDataT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(CalculatorDataT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<CalculatorData> Pack(flatbuffers::FlatBufferBuilder &_fbb, const CalculatorDataT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct CalculatorDataBuilder {
  typedef CalculatorData Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_originalEquation(flatbuffers::Offset<flatbuffers::String> originalEquation) {
    fbb_.AddOffset(CalculatorData::VT_ORIGINALEQUATION, originalEquation);
  }
  void add_answer(float answer) {
    fbb_.AddElement<float>(CalculatorData::VT_ANSWER, answer, 0.0f);
  }
  void add_type(calculator::schema::CalculatorType type) {
    fbb_.AddElement<int8_t>(CalculatorData::VT_TYPE, static_cast<int8_t>(type), 0);
  }
  explicit CalculatorDataBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<CalculatorData> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<CalculatorData>(end);
    return o;
  }
};

inline flatbuffers::Offset<CalculatorData> CreateCalculatorData(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> originalEquation = 0,
    float answer = 0.0f,
    calculator::schema::CalculatorType type = calculator::schema::CalculatorType_AddCalculator) {
  CalculatorDataBuilder builder_(_fbb);
  builder_.add_answer(answer);
  builder_.add_originalEquation(originalEquation);
  builder_.add_type(type);
  return builder_.Finish();
}

inline flatbuffers::Offset<CalculatorData> CreateCalculatorDataDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *originalEquation = nullptr,
    float answer = 0.0f,
    calculator::schema::CalculatorType type = calculator::schema::CalculatorType_AddCalculator) {
  auto originalEquation__ = originalEquation ? _fbb.CreateString(originalEquation) : 0;
  return calculator::schema::CreateCalculatorData(
      _fbb,
      originalEquation__,
      answer,
      type);
}

flatbuffers::Offset<CalculatorData> CreateCalculatorData(flatbuffers::FlatBufferBuilder &_fbb, const CalculatorDataT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline CalculatorDataT *CalculatorData::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<CalculatorDataT>(new CalculatorDataT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void CalculatorData::UnPackTo(CalculatorDataT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = originalEquation(); if (_e) _o->originalEquation = _e->str(); }
  { auto _e = answer(); _o->answer = _e; }
  { auto _e = type(); _o->type = _e; }
}

inline flatbuffers::Offset<CalculatorData> CalculatorData::Pack(flatbuffers::FlatBufferBuilder &_fbb, const CalculatorDataT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateCalculatorData(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<CalculatorData> CreateCalculatorData(flatbuffers::FlatBufferBuilder &_fbb, const CalculatorDataT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const CalculatorDataT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _originalEquation = _o->originalEquation.empty() ? 0 : _fbb.CreateString(_o->originalEquation);
  auto _answer = _o->answer;
  auto _type = _o->type;
  return calculator::schema::CreateCalculatorData(
      _fbb,
      _originalEquation,
      _answer,
      _type);
}

inline const calculator::schema::CalculatorData *GetCalculatorData(const void *buf) {
  return flatbuffers::GetRoot<calculator::schema::CalculatorData>(buf);
}

inline const calculator::schema::CalculatorData *GetSizePrefixedCalculatorData(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<calculator::schema::CalculatorData>(buf);
}

inline CalculatorData *GetMutableCalculatorData(void *buf) {
  return flatbuffers::GetMutableRoot<CalculatorData>(buf);
}

inline bool VerifyCalculatorDataBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<calculator::schema::CalculatorData>(nullptr);
}

inline bool VerifySizePrefixedCalculatorDataBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<calculator::schema::CalculatorData>(nullptr);
}

inline void FinishCalculatorDataBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<calculator::schema::CalculatorData> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedCalculatorDataBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<calculator::schema::CalculatorData> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<calculator::schema::CalculatorDataT> UnPackCalculatorData(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<calculator::schema::CalculatorDataT>(GetCalculatorData(buf)->UnPack(res));
}

inline std::unique_ptr<calculator::schema::CalculatorDataT> UnPackSizePrefixedCalculatorData(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<calculator::schema::CalculatorDataT>(GetSizePrefixedCalculatorData(buf)->UnPack(res));
}

}  // namespace schema
}  // namespace calculator

#endif  // FLATBUFFERS_GENERATED_CALCULATOR_CALCULATOR_SCHEMA_H_
