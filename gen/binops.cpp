#include "gen/llvm.h"

#include "declaration.h"

#include "gen/irstate.h"
#include "gen/tollvm.h"
#include "gen/dvalue.h"

//////////////////////////////////////////////////////////////////////////////

DValue* DtoBinAdd(DValue* lhs, DValue* rhs)
{
    LLValue* v = gIR->ir->CreateAdd(lhs->getRVal(), rhs->getRVal(), "tmp");
    return new DImValue( lhs->getType(), v );
}

//////////////////////////////////////////////////////////////////////////////

DValue* DtoBinSub(DValue* lhs, DValue* rhs)
{
    LLValue* v = gIR->ir->CreateSub(lhs->getRVal(), rhs->getRVal(), "tmp");
    return new DImValue( lhs->getType(), v );
}

//////////////////////////////////////////////////////////////////////////////

DValue* DtoBinMul(Type* targettype, DValue* lhs, DValue* rhs)
{
    LLValue* v = gIR->ir->CreateMul(lhs->getRVal(), rhs->getRVal(), "tmp");
    return new DImValue( targettype, v );
}

//////////////////////////////////////////////////////////////////////////////

DValue* DtoBinDiv(Type* targettype, DValue* lhs, DValue* rhs)
{
    Type* t = lhs->getType();
    LLValue *l, *r;
    l = lhs->getRVal();
    r = rhs->getRVal();
    LLValue* res;
    if (t->isfloating())
        res = gIR->ir->CreateFDiv(l, r, "tmp");
    else if (!t->isunsigned())
        res = gIR->ir->CreateSDiv(l, r, "tmp");
    else
        res = gIR->ir->CreateUDiv(l, r, "tmp");
    return new DImValue( targettype, res );
}

//////////////////////////////////////////////////////////////////////////////

DValue* DtoBinRem(Type* targettype, DValue* lhs, DValue* rhs)
{
    Type* t = lhs->getType();
    LLValue *l, *r;
    l = lhs->getRVal();
    r = rhs->getRVal();
    LLValue* res;
    if (t->isfloating())
        res = gIR->ir->CreateFRem(l, r, "tmp");
    else if (!t->isunsigned())
        res = gIR->ir->CreateSRem(l, r, "tmp");
    else
        res = gIR->ir->CreateURem(l, r, "tmp");
    return new DImValue( targettype, res );
}
