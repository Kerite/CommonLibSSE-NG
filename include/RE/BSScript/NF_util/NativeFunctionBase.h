#pragma once

#include "skse64/GameRTTI.h"  // RTTI_BSScript__NF_util__NativeFunctionBase

#include "RE/BSScript/IFunction.h"  // BSScript::IFunction
#include "RE/BSScript/Type.h"  // BSScript::Type
#include "RE/BSFixedString.h"  // BSFixedString


namespace RE
{
	namespace BSScript
	{
		class StackFrame;
		class Variable;
		class VMClassInfo;


		namespace NF_util
		{
			class NativeFunctionBase : public IFunction
			{
			public:
				inline static const void* RTTI = RTTI_BSScript__NF_util__NativeFunctionBase;


				struct ParameterInfo
				{
					struct Entry
					{
						// members
						BSFixedString	name;	// 00
						Type			type;	// 08
					};
					STATIC_ASSERT(sizeof(Entry) == 0x10);


					// members
					Entry*	data;		// 00 length = numParams + numVars
					UInt16	numParams;	// 08
					UInt16	numVars;	// 0A
					UInt32	pad0C;		// 0C
				};
				STATIC_ASSERT(sizeof(ParameterInfo) == 0x10);


				NativeFunctionBase() = delete;
				explicit NativeFunctionBase(const char* a_fnName, const char* a_className, bool a_isStatic, UInt32 a_numParams);
				virtual ~NativeFunctionBase();																																	// 00

				// override (IFunction)
				virtual const BSFixedString&	GetFunctionName() const override;																								// 01
				virtual const BSFixedString&	GetScriptName() const override;																									// 02
				virtual const BSFixedString&	GetStateName() const override;																									// 03
				virtual Type&					GetReturnType(Type& a_dst) const override;																						// 04
				virtual UInt32					GetNumParams() const override;																									// 05
				virtual Type&					GetParam(UInt32 a_idx, BSFixedString& a_nameOut, Type& a_typeOut) const override;												// 06
				virtual UInt32					GetNumVars() const override;																									// 07
				virtual bool					IsNative() const override;																										// 08
				virtual bool					IsStatic() const override;																										// 09
				virtual bool					IsEvent() const override;																										// 0A
				virtual UInt32					Unk_0B() override;																												// 0B
				virtual UInt32					GetUnk44() const override;																										// 0C
				virtual const BSFixedString&	GetStr48() const override;																										// 0D
				virtual void					MoveVariablesToStack(StackFrame* a_frame) override;																				// 0E
				virtual UInt32					Invoke(BSTSmartPointer<Stack>& a_stack, ErrorLogger* a_logger, Internal::VirtualMachine* a_vm, bool a_arg4) override;			// 0F
				virtual const BSFixedString&	GetSource() const override;																										// 10
				virtual bool					Unk_11(UInt32 a_arg1, UInt32* a_arg2) override;																					// 11
				virtual bool					GetVarName(UInt32 a_idx, BSFixedString& a_out) const override;																	// 12
				virtual bool					GetUnk41() const override;																										// 13
				virtual void					SetUnk41(bool a_arg) override;																									// 14

				// add
				virtual bool					HasCallback() const = 0;																										// 15
				virtual bool					Run(Variable* a_baseValue, Internal::VirtualMachine* a_vm, UInt32 a_stackID, Variable* a_resultValue, StackFrame* a_frame) = 0;	// 16

			protected:
				// members
				BSFixedString	_fnName;		// 10
				BSFixedString	_scriptName;	// 18
				BSFixedString	_stateName;		// 20
				VMTypeID		_returnType;	// 28
				ParameterInfo	_params;		// 30
				bool			_isStatic;		// 40
				bool			_unk41;			// 41
				bool			_isLatent;		// 42
				UInt8			_pad43;			// 43
				UInt32			_unk44;			// 44
				BSFixedString	_unk48;			// 48

			private:
				NativeFunctionBase* Ctor(const char* a_fnName, const char* a_className, bool a_isStatic, UInt32 a_numParams);
				void				Dtor();
			};
			STATIC_ASSERT(sizeof(NativeFunctionBase) == 0x50);
		}
	}
}
