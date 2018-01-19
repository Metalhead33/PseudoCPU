#pragma once
#include "abstract/AbstractProcessor.hpp"

namespace Arithmetic {
// Normal maths-ish
ProcessorState Add(pAbstractProcessor proc); // Addition - 1 byte argument, it's 2 nibbles.
ProcessorState Subtract(pAbstractProcessor proc); // Subtraction - 1 byte argument, it's 2 nibbles.
ProcessorState Multiplicate(pAbstractProcessor proc); // Multiplication - 1 byte argument, it's 2 nibbles.
ProcessorState Divide(pAbstractProcessor proc); // Division - 1 byte argument, it's 2 nibbles.
ProcessorState Modulo(pAbstractProcessor proc); // Modulo - 1 byte argument, it's 2 nibbles.
// Floating point maths
ProcessorState FloatAdd(pAbstractProcessor proc); // Addition - 1 byte argument, it's 2 nibbles.
ProcessorState FloatSubtract(pAbstractProcessor proc); // Subtraction - 1 byte argument, it's 2 nibbles.
ProcessorState FloatMultiplicate(pAbstractProcessor proc); // Multiplication - 1 byte argument, it's 2 nibbles.
ProcessorState FloatDivide(pAbstractProcessor proc); // Division - 1 byte argument, it's 2 nibbles.
// Logical
ProcessorState LogicalNot(pAbstractProcessor proc); // Logical NOT - 1 byte argument, it's 2 nibbles.
ProcessorState LogicalAnd(pAbstractProcessor proc); // Logical AND - 1 byte argument, it's 2 nibbles.
ProcessorState LogicalInclusiveOr(pAbstractProcessor proc); // Logical OR - 1 byte argument, it's 2 nibbles.
ProcessorState LogicalExclusiveOr(pAbstractProcessor proc); // Logical XOR - 1 byte argument, it's 2 nibbles.
// Bitwise
ProcessorState BitwiseNot(pAbstractProcessor proc); // Bitwise NOT - 1 byte argument, it's 2 nibbles.
ProcessorState BitwiseAnd(pAbstractProcessor proc); // Bitwise AND - 1 byte argument, it's 2 nibbles.
ProcessorState BitwiseInclusiveOr(pAbstractProcessor proc); // Bitwise OR - 1 byte argument, it's 2 nibbles.
ProcessorState BitwisexclusiveOr(pAbstractProcessor proc); // Bitwise XOR - 1 byte argument, it's 2 nibbles.
ProcessorState BitwiseLeftShift(pAbstractProcessor proc); // Bitwise Left Shift - 1 byte argument, it's 2 nibbles.
ProcessorState BitwiseRightShift(pAbstractProcessor proc); // Bitwise Right Shift - 1 byte argument, it's 2 nibbles.
}
